
#include "polybuild.h"
#include "zip.h"

vector<BuildArg> args;
#define MAXFILENAME (256)

String getArg(String argName) {
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
  struct stat s;        /* results of stat() */
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
    if (stat(name,&s)==0)
    {
      tm_t = s.st_mtime;
      ret = 1;
    }
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


void addFolderToZip(zipFile z, String folderPath, String parentFolder) {

	std::vector<OSFileEntry> files = OSBasics::parseFolder(folderPath, false);
	for(int i=0; i < files.size(); i++) {
		if(files[i].type == OSFileEntry::TYPE_FILE) {
			printf("Adding %s\n", files[i].name.c_str());

                	zip_fileinfo zi;
                	zi.tmz_date.tm_sec = zi.tmz_date.tm_min = zi.tmz_date.tm_hour =
			zi.tmz_date.tm_mday = zi.tmz_date.tm_mon = zi.tmz_date.tm_year = 0;
			 zi.dosDate = 0;
              	 	 zi.internal_fa = 0;
             		   zi.external_fa = 0;
             		   filetime(files[i].fullPath.c_str(),&zi.tmz_date,&zi.dosDate);
	
			String pathInZip;
			if(parentFolder == "") {
				pathInZip = files[i].name;
			} else {
				pathInZip = parentFolder + "/" + files[i].name;
			}
			zipOpenNewFileInZip(z, pathInZip.c_str(), &zi, NULL, 0, NULL, 0, NULL, Z_DEFLATED, 2);

			FILE *f = fopen(files[i].fullPath.c_str(), "rb");
			fseek(f, 0, SEEK_END);
			long fileSize = ftell(f);
			fseek(f, 0, SEEK_SET);
			char *buf = (char*) malloc(fileSize);
			fread(buf, fileSize, 1, f);
			zipWriteInFileInZip(z, buf, fileSize);
			free(buf);
			fclose(f);

			zipCloseFileInZip(z);
		} else {
			addFolderToZip(z, files[i].fullPath.c_str(), files[i].name);
		}
	}
}

int main(int argc, char **argv) {

	printf("Polycode build tool v0.1.0\n");

	for(int i=0; i < argc; i++) {
		String argString = String(argv[i]);
		vector<String> bits = argString.split("=");
		if(bits.size() == 2) {
			BuildArg arg;
			arg.name = bits[0];
			arg.value = bits[1];
			args.push_back(arg);
		}
		
	}
	
	if(getArg("--project") == "") {
		printf("\n\nInput project missing. Use --project=projectPath to specify.\n\n");
		return 0;
	}

	if(getArg("--out") == "") {
		printf("\n\nOutput file not specified. Use --out=outfile.polyapp to specify.\n\n");
		return 0;		
	}
	
	zipFile z = zipOpen(getArg("--out").c_str(), 0);
	
	addFolderToZip(z, getArg("--project"), "");
	
	zipClose(z, "");	

	return 1;
}
