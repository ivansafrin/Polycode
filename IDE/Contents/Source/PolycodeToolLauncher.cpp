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
 
#pragma once

#include "PolycodeToolLauncher.h"

PolycodeToolLauncher::PolycodeToolLauncher() {

}

PolycodeToolLauncher::~PolycodeToolLauncher() {

}

void PolycodeToolLauncher::execLocalBinCommand(String command) {
	system(command.c_str());
}

String PolycodeToolLauncher::generateTempPath() {
	return "/tmp/"+String::IntToString(rand() % 10000000);
}

void PolycodeToolLauncher::buildProject(PolycodeProject *project, String destinationPath) {
	String projectBasePath = project->getRootFolder();
	String projectPath = project->getProjectFile();
	
	String polycodeBasePath = CoreServices::getInstance()->getCore()->getDefaultWorkingDirectory();
	
	execLocalBinCommand("cd "+projectBasePath+" && "+polycodeBasePath+"/Standalone/Bin/polybuild  --config="+projectPath+" --out="+destinationPath);

}

void PolycodeToolLauncher::runPolyapp(String polyappPath) {
	String polycodeBasePath = CoreServices::getInstance()->getCore()->getDefaultWorkingDirectory();

	execLocalBinCommand("cd "+polycodeBasePath+"/Standalone/Player/PolycodePlayer.app/Contents/Resources && ../MacOS/PolycodePlayer "+polyappPath);	
}