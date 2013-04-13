
#include "polybuild.h"
#include "string.h"
#include "zip.h"

#ifdef _WINDOWS
	#include <windows.h>
	#include <direct.h>
#else
	#include <dirent.h>
	#include <sys/types.h>
	#include <sys/stat.h>
#endif

#include "physfs.h"

#if defined(__APPLE__) && defined(__MACH__)
#include <mach-o/dyld.h>
#endif

using std::vector;

vector<BuildArg> args;
#define MAXFILENAME (2048)

String getArg(String argName) {
	/*
	if(argName == "--config")
		return "ExampleProject.xml";

	if(argName == "--out")
		return "ExampleProject.polyapp";

		*/

	for(int i=0; i < args.size(); i++) {
		if(args[i].name == argName) {
			return args[i].value;
		}
	}
	return "";
}

uLong filetime(
    const char *f,
    tm_zip *tmzip,
    uLong *dt)
{
  int ret=0;
  struct tm* filedate;
  time_t tm_t=0;

  if (strcmp(f,"-")!=0)
  {
    char name[MAXFILENAME+1];
    int len = strlen(f);
    if (len > MAXFILENAME)
      len = MAXFILENAME;

    strncpy(name, f,MAXFILENAME-1);
    /* strncpy doesnt append the trailing NULL, of the string is too long. */
    name[ MAXFILENAME ] = '\0';

    if (name[len - 1] == '/')
      name[len - 1] = '\0';

    /* not all systems allow stat'ing a file with / appended */
#ifdef _WINDOWS

#else
    if (stat(name,&s)==0)
    {
      tm_t = s.st_mtime;
      ret = 1;
    }
#endif
  }
  filedate = localtime(&tm_t);

  tmzip->tm_sec  = filedate->tm_sec;
  tmzip->tm_min  = filedate->tm_min;
  tmzip->tm_hour = filedate->tm_hour;
  tmzip->tm_mday = filedate->tm_mday;
  tmzip->tm_mon  = filedate->tm_mon ;
  tmzip->tm_year = filedate->tm_year;

  return ret;
}

void addFileToZip(zipFile z, String filePath, String pathInZip, bool silent) {
			if(!silent)
				printf("Packaging %s as %s\n", filePath.c_str(), pathInZip.c_str());

                	zip_fileinfo zi;
                	zi.tmz_date.tm_sec = zi.tmz_date.tm_min = zi.tmz_date.tm_hour =
			zi.tmz_date.tm_mday = zi.tmz_date.tm_mon = zi.tmz_date.tm_year = 0;
			 zi.dosDate = 0;
              	 	 zi.internal_fa = 0;
             		   zi.external_fa = 0;
             		   filetime(filePath.c_str(),&zi.tmz_date,&zi.dosDate);
	
			zipOpenNewFileInZip(z, pathInZip.c_str(), &zi, NULL, 0, NULL, 0, NULL, Z_DEFLATED, 2);

			FILE *f = fopen(filePath.c_str(), "rb");
			fseek(f, 0, SEEK_END);
			long fileSize = ftell(f);
			fseek(f, 0, SEEK_SET);
			char *buf = (char*) malloc(fileSize);
			fread(buf, fileSize, 1, f);
			zipWriteInFileInZip(z, buf, fileSize);
			free(buf);
			fclose(f);

			zipCloseFileInZip(z);

}

void addFolderToZip(zipFile z, String folderPath, String parentFolder, bool silent) {
	std::vector<OSFileEntry> files = OSBasics::parseFolder(folderPath, false);
	for(int i=0; i < files.size(); i++) {
		if(files[i].type == OSFileEntry::TYPE_FILE) {

			String pathInZip;
			if(parentFolder == "") {
				pathInZip = files[i].name;
			} else {
				pathInZip = parentFolder + "/" + files[i].name;
			}

			addFileToZip(z, files[i].fullPath, pathInZip, silent);

		} else {
			if(parentFolder == "") {
				addFolderToZip(z, files[i].fullPath.c_str(), files[i].name, silent);
			} else {
				addFolderToZip(z, files[i].fullPath.c_str(), parentFolder + "/" + files[i].name, silent);
			}
		}
	}
}

#ifdef _WINDOWS
void wtoc(char* Dest, TCHAR* Source, int SourceSize)
{
for(int i = 0; i < SourceSize; ++i)
Dest[i] = (char)Source[i];
}
#endif

int main(int argc, char **argv) {
		
	PHYSFS_init(argv[0]);

#if defined(__APPLE__) && defined(__MACH__)
    uint32_t bufsize = 2048;
	char path[bufsize];
	_NSGetExecutablePath(path, &bufsize);

	String basePath = path;
	vector<String> cpts = basePath.split("/");
	String installPath = "";
	for(int i=0; i < cpts.size() - 2; i++) {
		installPath = installPath + cpts[i];
		installPath += String("/");
	}
#elif defined (_WINDOWS)
	char path[2049];
	TCHAR tpath[2049];
	GetModuleFileName(NULL, (LPWSTR)tpath, 2048);
	wtoc(path, tpath, 2048);
	
	String basePath = path;
	vector<String> cpts = basePath.split("\\");
	String installPath = "";
	for(int i=0; i < cpts.size() - 2; i++) {
		installPath = installPath + cpts[i];
		installPath += String("\\");
	}
#else
	String basePath = PHYSFS_getBaseDir();
	vector<String> cpts = basePath.split("/");
	String installPath = "";
	for(int i=0; i < cpts.size() - 2; i++) {
		installPath = installPath + cpts[i];
		installPath += String("/");
	}
#endif

	printf("Polycode build tool v0.8.2\n");

	for(int i=0; i < argc; i++) {
		String argString = String(argv[i]);
		vector<String> bits = argString.split("=");
		if(bits.size() == 2) {
			BuildArg arg;
			arg.name = bits[0];
			arg.value = bits[1];
		//	printf("arg: %s=%s\n", arg.name.c_str(), arg.value.c_str());
			args.push_back(arg);
		}
		
	}
	
	if(getArg("--config") == "") {
		printf("\n\nInput config XML missing. Use --config=path to specify.\n\n");
		return 1;
	}

	
	if(getArg("--out") == "") {
		printf("\n\nOutput file not specified. Use --out=outfile.polyapp to specify.\n\n");
		return 1;		
	}

	char dirPath[4099];
#if defined(__APPLE__) && defined(__MACH__)
	getcwd(dirPath, sizeof(dirPath));
#elif defined (_WINDOWS)
	TCHAR tdirpath[4099];
	GetCurrentDirectory(4098, (LPWSTR)tdirpath);
	wtoc(dirPath, tdirpath, 4098);
#else
	getcwd(dirPath, sizeof(dirPath));
#endif

	String currentPath = String(dirPath);

	String configPath = getArg("--config");

	String finalPath = configPath;
	if(configPath[0] != '/' && configPath[1] !=':') {

#ifdef _WINDOWS
		finalPath = currentPath+"\\"+configPath;
#else
		finalPath = currentPath+"/"+configPath;
#endif
	}

	printf("Reading config file from %s\n", finalPath.c_str());

	Object configFile;
	if(!configFile.loadFromXML(finalPath)) {
		printf("Specified config file doesn't exist!\n");
		return 1;
	}
	printf("OK!\n");
	// start required params

	String entryPoint;
	int defaultWidth;
	int defaultHeight;
	int frameRate = 60;
	int antiAliasingLevel = 0;
	int anisotropyLevel = 0;
	bool vSync = false;
	bool fullScreen = false;
	float backgroundColorR = 0.2;
	float backgroundColorG = 0.2;
	float backgroundColorB = 0.2;
	String textureFiltering = "linear";

	if(configFile.root["entryPoint"]) {
		printf("Entry point: %s\n", configFile.root["entryPoint"]->stringVal.c_str());
		entryPoint = configFile.root["entryPoint"]->stringVal;
	} else {
		printf("Required parameter: \"entryPoint\" is missing from config file!\n");
		return 1;		
	}

	if(configFile.root["defaultWidth"]) {
		printf("Width: %d\n", configFile.root["defaultWidth"]->intVal);
		defaultWidth = configFile.root["defaultWidth"]->intVal;
	} else {
		printf("Required parameter: \"defaultWidth\" is missing from config file!\n");
		return 1;		
	}

	if(configFile.root["defaultHeight"]) {
		printf("Height: %d\n", configFile.root["defaultHeight"]->intVal);
		defaultHeight = configFile.root["defaultHeight"]->intVal;
	} else {
		printf("Required parameter: \"defaultHeight\" is missing from config file!\n");
		return 1;		
	}

	// start optional params

	if(configFile.root["frameRate"]) {
		printf("Frame rate: %d\n", configFile.root["frameRate"]->intVal);
		frameRate = configFile.root["frameRate"]->intVal;
	}

	if(configFile.root["textureFiltering"]) {
		printf("Filtering mode: %s\n", configFile.root["textureFiltering"]->stringVal.c_str());
		textureFiltering = configFile.root["textureFiltering"]->stringVal;
	}

	if(configFile.root["antiAliasingLevel"]) {
		printf("Anti-aliasing level: %d\n", configFile.root["antiAliasingLevel"]->intVal);
		antiAliasingLevel = configFile.root["antiAliasingLevel"]->intVal;
	}

	if(configFile.root["anisotropyLevel"]) {
		printf("Anisotropy level: %d\n", configFile.root["anisotropyLevel"]->intVal);
		anisotropyLevel = configFile.root["anisotropyLevel"]->intVal;
	}
	
	if(configFile.root["vSync"]) {
		vSync = configFile.root["vSync"]->boolVal;
		if(vSync) {
			printf("V-Sync: true\n");
		} else {
			printf("V-Sync: false\n");
		}
	}	

	if(configFile.root["fullScreen"]) {
		fullScreen = configFile.root["fullScreen"]->boolVal;
		if(fullScreen) {
			printf("Full-screen: true\n");
		} else {
			printf("Full-screen: false\n");
		}
	}

	if(configFile.root["backgroundColor"]) {
		ObjectEntry *color = configFile.root["backgroundColor"];
		if((*color)["red"] && (*color)["green"] && (*color)["blue"]) {
			backgroundColorR = (*color)["red"]->NumberVal;
			backgroundColorG = (*color)["green"]->NumberVal;
			backgroundColorB = (*color)["blue"]->NumberVal;
			printf("Background color: %f %f %f\n", backgroundColorR, backgroundColorG, backgroundColorB);

		} else {
			printf("backgroundColor node specified, but missing all three color attributes (red,green,blue). Ignoring.\n");
		}
	}

	zipFile z = zipOpen(getArg("--out").c_str(), 0);
	

	Object runInfo;
	runInfo.root.name = "PolycodeApp";
	runInfo.root.addChild("entryPoint", entryPoint);
	runInfo.root.addChild("defaultHeight", defaultHeight);
	runInfo.root.addChild("defaultWidth", defaultWidth);
	runInfo.root.addChild("frameRate", frameRate);
	runInfo.root.addChild("antiAliasingLevel", antiAliasingLevel);
	runInfo.root.addChild("anisotropyLevel", anisotropyLevel);
	runInfo.root.addChild("vSync", vSync);	
	runInfo.root.addChild("fullScreen", fullScreen);
	runInfo.root.addChild("textureFiltering", String(textureFiltering));
		
	ObjectEntry *color = runInfo.root.addChild("backgroundColor");
	color->addChild("red", backgroundColorR);
	color->addChild("green", backgroundColorG);
	color->addChild("blue", backgroundColorB);

	addFileToZip(z, entryPoint, entryPoint, false);

	if(configFile.root["fonts"]) {
		runInfo.root.addChild(configFile.root["fonts"]);
	}
	
	if(configFile.root["modules"]) {
#ifdef _WINDOWS
		String modulesPath = installPath + "Modules\\";
#else
		String modulesPath = installPath + "Modules/";
#endif

		ObjectEntry *modules = configFile.root["modules"];
		if(modules) {		
			for(int i=0; i < modules->length; i++) {
				printf("Adding module: %s\n", (*modules)[i]->stringVal.c_str());
				String modulePath = modulesPath + (*modules)[i]->stringVal;
#ifdef _WINDOWS
				String moduleAPIPath = modulePath + "\\API";
				String moduleLibPath = modulePath + "\\Lib";
				moduleAPIPath = moduleAPIPath.replace("\\", "/");
				moduleAPIPath = moduleAPIPath.substr(2, moduleAPIPath.length() - 2);	
				moduleLibPath = moduleLibPath.replace("\\", "/");
				moduleLibPath = moduleLibPath.substr(2, moduleLibPath.length() - 2);	

#else
				String moduleAPIPath = modulePath + "/API";
				String moduleLibPath = modulePath + "/Lib";
#endif
				printf("Path:%s\n", moduleAPIPath.c_str());		


				addFolderToZip(z, moduleAPIPath, "", false);
				addFolderToZip(z, moduleLibPath, "__lib", false);

				//String module = configFile.root["entryPoint"]->stringVal;
			}
			runInfo.root.addChild(configFile.root["modules"]);
		}
	}

	if(configFile.root["packedItems"]) {
		ObjectEntry *packed = configFile.root["packedItems"];
		if(packed) {
			for(int i=0; i < packed->length; i++) {
				ObjectEntry *entryPath = (*(*packed)[i])["path"];
				ObjectEntry *entryType = (*(*packed)[i])["type"];
				if(entryPath && entryType) {
					if(entryType->stringVal == "folder") {
						addFolderToZip(z, entryPath->stringVal, entryPath->stringVal, false);
					} else {
						addFileToZip(z, entryPath->stringVal, entryPath->stringVal, false);
					}
				}
			}
			runInfo.root.addChild(configFile.root["packedItems"]);
		}
	}


	runInfo.saveToXML("runinfo_tmp_zzzz.polyrun");
	addFileToZip(z, "runinfo_tmp_zzzz.polyrun", "runinfo.polyrun", true);

	//addFolderToZip(z, getArg("--project"), "");
	
	zipClose(z, "");	

#ifdef _WINDOWS
	char *buffer = _getcwd(NULL, 0);
	String workingDir = String(buffer);
	free(buffer);
	OSBasics::removeItem(workingDir+"/runinfo_tmp_zzzz.polyrun");
#else
	OSBasics::removeItem("runinfo_tmp_zzzz.polyrun");
#endif
	return 0;
}
