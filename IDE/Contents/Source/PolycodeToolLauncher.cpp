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

PolycodeRunner::PolycodeRunner(String polyappPath) : Threaded() {
	this->polyappPath = polyappPath;
}

void PolycodeRunner::runThread() {
	String polycodeBasePath = CoreServices::getInstance()->getCore()->getDefaultWorkingDirectory();

	String command = "cd "+polycodeBasePath+"/Standalone/Player/PolycodePlayer.app/Contents/Resources && ../MacOS/PolycodePlayer "+polyappPath;
		;		

	String ret = CoreServices::getInstance()->getCore()->executeExternalCommand(command);
		core->removeDiskItem(polyappPath);	
}

PolycodeToolLauncher::PolycodeToolLauncher() {

}

PolycodeToolLauncher::~PolycodeToolLauncher() {

}

String PolycodeToolLauncher::generateTempPath() {
	return "/tmp/"+String::IntToString(rand() % 10000000);
}

void PolycodeToolLauncher::buildProject(PolycodeProject *project, String destinationPath) {

	project->saveFile();

	String projectBasePath = project->getRootFolder();
	String projectPath = project->getProjectFile();
	
	
	String polycodeBasePath = CoreServices::getInstance()->getCore()->getDefaultWorkingDirectory();
	
	String command = "cd "+projectBasePath+" && "+polycodeBasePath+"/Standalone/Bin/polybuild  --config="+projectPath+" --out="+destinationPath;	
	String ret = CoreServices::getInstance()->getCore()->executeExternalCommand(command);
	PolycodeConsole::print(ret);	

}

void PolycodeToolLauncher::runPolyapp(String polyappPath) {		
//	PolycodeRunner *runner = new PolycodeRunner(polyappPath);
//	CoreServices::getInstance()->getCore()->createThread(runner);

#if defined(__APPLE__) && defined(__MACH__)
	CocoaCore *cocoaCore = (CocoaCore*) CoreServices::getInstance()->getCore();

	String polycodeBasePath = CoreServices::getInstance()->getCore()->getDefaultWorkingDirectory();
	String command = polycodeBasePath+"/Standalone/Player/PolycodePlayer.app";
	
	cocoaCore->launchApplicationWithFile(command, polyappPath);
#else

#endif

}