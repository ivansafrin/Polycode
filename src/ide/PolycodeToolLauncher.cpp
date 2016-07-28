/*
 Copyright (C) 2012 by Ivan Safrin
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */
 
#include "polycode/ide/PolycodeToolLauncher.h"

#if defined(__APPLE__) && defined(__MACH__)
	#include "polycode/core/PolyCocoaCore.h"
#endif

GenericRunner::GenericRunner(String app, String file, String inFolder) : Threaded() {
	this->app = app;
	this->file = file;
	this->inFolder = inFolder;
}

void GenericRunner::runThread() {
#if defined(__APPLE__) && defined(__MACH__)
	CocoaCore *cocoaCore = (CocoaCore*) core;
	cocoaCore->openFileWithApplication(file.replace("\"", ""), app.replace("\"", ""));
#else
	String ret = core->executeExternalCommand(app, file, inFolder);	
#endif
}

PolycodeRunner::PolycodeRunner(String polyappPath) : Threaded() {
	this->polyappPath = polyappPath;
}

void PolycodeRunner::runThread() {
	String polycodeBasePath = core->getDefaultWorkingDirectory();

#if defined(__APPLE__) && defined(__MACH__)
	String command = "../MacOS/PolycodePlayer"; 
	String inFolder = polycodeBasePath+"/Standalone/Player/PolycodePlayer.app/Contents/Resources";
	String args = "\""+polyappPath+"\"";
#elif defined _WINDOWS
	String command = "\""+polycodeBasePath+"/Standalone/Player/PolycodePlayer.exe\"";
	String args = "\""+polyappPath+"\"";
	String inFolder = polycodeBasePath+"/Standalone/Player";
#else
	String command = "./PolycodePlayer";	
	String inFolder = polycodeBasePath+"/Standalone/Player";
	String args = "\""+polyappPath+"\"";
#endif

	String ret = core->executeExternalCommand(command, args, inFolder);
	core->removeDiskItem(polyappPath);
}

PolycodeToolLauncher::PolycodeToolLauncher() {

}

PolycodeToolLauncher::~PolycodeToolLauncher() {

}

String PolycodeToolLauncher::generateTempPath(PolycodeProject *project) {
#ifdef _WINDOWS
		wchar_t buf[2048];
		GetTempPath(2048, buf);
		String retString = String(buf)+project->getProjectName();
		printf("TEMP_PATH: %s\n", retString.c_str());
		return retString;
#else
	return "/tmp/"+project->getProjectName();
#endif
}

void PolycodeToolLauncher::buildProject(Core *core, PolycodeProject *project, String destinationPath, bool compileScripts) {

	PolycodeConsole::print("Building project: "+project->getProjectName() + "\n");	

	project->saveFile();

	String projectBasePath = project->getRootFolder();
	String projectPath = project->getProjectFile();
	
	
	String polycodeBasePath = core->getDefaultWorkingDirectory();
	
#ifdef _WINDOWS
	String targetFolder = projectBasePath;
	String command = "\""+polycodeBasePath+"/bin/polybuild.exe\"";
	String args =  "--config=\""+projectPath+"\" --out=\""+destinationPath+"\" --compileScripts=\""+((compileScripts)?"true":"false")+"\"";
	String ret = core->executeExternalCommand(command, args, targetFolder);
#else
	String command = polycodeBasePath+"/bin/polybuild";
	String inFolder = projectBasePath; 
	String args = "--config=\""+projectPath+"\" --out=\""+destinationPath+"\" --compileScripts=\""+((compileScripts)?"true":"false")+"\"";
	String ret = core->executeExternalCommand(command, args, inFolder);
//	PolycodeConsole::print(ret);
#endif

}

String PolycodeToolLauncher::importAssets(Core *core, String sourceFile, String inFolder, bool addMeshes, String prefix, bool swapZY, bool generateNormals, bool generateTangents, bool listOnly, bool writeNormals, bool writeTangents, bool writeColors, bool writeBoneWeights, bool writeUVs, bool writeSecondaryUVs, bool exportScene, bool generateMaterialFile, bool overrideMaterials, String materialOverrideName, bool specifyBaseAssetPath, String baseAssetPath) {

	String ret;
	String polycodeBasePath = core->getDefaultWorkingDirectory();
	
	String args = "\""+sourceFile+"\"";
	if(listOnly) {
		args = "-l "+args;
	}		
	if(addMeshes) {
		args = "-a "+args;
	}
	if(swapZY) {
		args = "-s "+args;
	}
	if(generateNormals) {
		args = "-m "+args;
	}
	if(generateTangents) {
		args = "-t "+args;
	}
	if(writeNormals) {
		args = "-n "+args;
	}
	if(writeTangents) {
		args = "-g "+args;
	}
	if(writeColors) {
		args = "-c "+args;
	}
	if(writeBoneWeights) {
		args = "-w "+args;
	}
	if(writeUVs) {
		args = "-u "+args;
	}
	if(writeSecondaryUVs) {
		args = "-v "+args;
	}
	if(exportScene) {
		args = "-e "+args;
	}
	if(generateMaterialFile) {
		args = "-f "+args;
	}
	if(overrideMaterials) {
		args = "-o \""+materialOverrideName+"\" "+args;
	}
	if(specifyBaseAssetPath) {
		args = "-x \""+baseAssetPath+"\" "+args;		
	}
	if(prefix != "") {
		args = "-p \""+prefix+"\" "+args;
	}
	

	
#ifdef _WINDOWS
	String command = "\""+polycodeBasePath+"/bin/polyimport.exe\"";
	ret = core->executeExternalCommand(command, args, inFolder);
#else
	String command = polycodeBasePath+"/bin/polyimport";
	ret = core->executeExternalCommand(command, args, inFolder);
#endif
	return ret;
}

void PolycodeToolLauncher::openExternalEditor(Core *core, String app, String file, String inFolder) {
	GenericRunner *runner = new GenericRunner("\"" + app + "\"", "\"" + file + "\"", "\"" + inFolder + "\"");
	core->createThread(runner);
}

void PolycodeToolLauncher::runPolyapp(Core *core, String polyappPath) {

	PolycodeConsole::clearBacktraces();
							
#if defined(__APPLE__) && defined(__MACH__)
	CocoaCore *cocoaCore = (CocoaCore*) core;

	String polycodeBasePath = core->getDefaultWorkingDirectory();
	String command = polycodeBasePath+"/Standalone/Player/PolycodePlayer.app"; 
	
	cocoaCore->openFileWithApplication(polyappPath, command);
#else
	PolycodeRunner *runner = new PolycodeRunner(polyappPath);
	core->createThread(runner);

#endif

}
