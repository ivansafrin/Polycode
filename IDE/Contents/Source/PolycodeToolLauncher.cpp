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
 
#include "PolycodeToolLauncher.h"

#if defined(__APPLE__) && defined(__MACH__)
	#include "PolyCocoaCore.h"
#endif

GenericRunner::GenericRunner(String app, String file, String inFolder) : Threaded() {
	this->app = app;
	this->file = file;
	this->inFolder = inFolder;
}

void GenericRunner::runThread() {
#if defined(__APPLE__) && defined(__MACH__)
	CocoaCore *cocoaCore = (CocoaCore*) CoreServices::getInstance()->getCore();
	cocoaCore->openFileWithApplication(file, app);
#else
	String ret = CoreServices::getInstance()->getCore()->executeExternalCommand(app, file, inFolder);
#endif
}

PolycodeRunner::PolycodeRunner(String polyappPath) : Threaded() {
	this->polyappPath = polyappPath;
}

void PolycodeRunner::runThread() {
	String polycodeBasePath = CoreServices::getInstance()->getCore()->getDefaultWorkingDirectory();

#if defined(__APPLE__) && defined(__MACH__)
	String command = "../MacOS/PolycodePlayer";
	String inFolder = polycodeBasePath+"/Standalone/Player/PolycodePlayer.app/Contents/Resources";
	String args = polyappPath;
#elif defined _WINDOWS
	String command = polycodeBasePath+"/Standalone/Player/PolycodePlayer.exe";
	String args = polyappPath;
	String inFolder = polycodeBasePath+"/Standalone/Player";
#else
	String command = "./PolycodePlayer";	
	String inFolder = polycodeBasePath+"/Standalone/Player";
	String args = polyappPath;
#endif

	String ret = CoreServices::getInstance()->getCore()->executeExternalCommand(command, args, inFolder);
	CoreServices::getInstance()->getCore()->removeDiskItem(polyappPath);	
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

void PolycodeToolLauncher::buildProject(PolycodeProject *project, String destinationPath, bool compileScripts) {

	PolycodeConsole::print("Building project: "+project->getProjectName() + "\n");	

	project->saveFile();

	String projectBasePath = project->getRootFolder();
	String projectPath = project->getProjectFile();


	String polycodeBasePath = CoreServices::getInstance()->getCore()->getDefaultWorkingDirectory();

#ifdef _WINDOWS
	String targetFolder = projectBasePath;
	String command = "\""+polycodeBasePath+"/Standalone/Bin/polybuild.exe\"";
	String args =  "--config=\""+projectPath+"\" --out=\""+destinationPath+"\" --compileScripts=\""+((compileScripts)?"true":"false")+"\"";
	String ret = CoreServices::getInstance()->getCore()->executeExternalCommand(command, args, targetFolder);
#else
	String command = polycodeBasePath+"/Standalone/Bin/polybuild";
	String inFolder = projectBasePath; 
	String args = "--config=\""+projectPath+"\" --out=\""+destinationPath+"\" --compileScripts=\""+((compileScripts)?"true":"false")+"\"";
	String ret = CoreServices::getInstance()->getCore()->executeExternalCommand(command, args, inFolder);
//	PolycodeConsole::print(ret);
#endif

}

void PolycodeToolLauncher::openExternalEditor(String app, String file, String inFolder) {
	GenericRunner *runner = new GenericRunner(app, file, inFolder);
	CoreServices::getInstance()->getCore()->createThread(runner);
}

void PolycodeToolLauncher::runPolyapp(String polyappPath) {

	PolycodeConsole::clearBacktraces();

#if defined(__APPLE__) && defined(__MACH__)
	CocoaCore *cocoaCore = (CocoaCore*) CoreServices::getInstance()->getCore();

	String polycodeBasePath = CoreServices::getInstance()->getCore()->getDefaultWorkingDirectory();
	String command = polycodeBasePath+"/Standalone/Player/PolycodePlayer.app"; 

	cocoaCore->openFileWithApplication(polyappPath, command);
#else
	PolycodeRunner *runner = new PolycodeRunner(polyappPath);
	CoreServices::getInstance()->getCore()->createThread(runner);

#endif

}
