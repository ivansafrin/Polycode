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

#include "PolycodeProjectManager.h"

PolycodeProjectManager::PolycodeProjectManager() {
	activeProject = NULL;
}

PolycodeProjectManager::~PolycodeProjectManager() {
	
}


PolycodeProject* PolycodeProjectManager::openProject(String path) {
	printf("Opening project  %s\n", path.c_str());
	
	FILE *f = fopen(path.c_str(), "r");
	if(!f) {
		printf("WARNING: PROJECT DOESNT EXIST! (%s)\n", path.c_str());
		return NULL;
	}
	fclose(f);
	
	vector<String> bits = path.split("/");
	
	String projectPath = "";
	for(int i=0; i < bits.size() - 1; i++) {
		projectPath += "/"+bits[i];
	}
	
	vector<String> bits2 = bits[bits.size()-1].split(".");
	String projectName = bits2[bits2.size()-2];
	
	PolycodeProject* newProject = new PolycodeProject(projectName, projectPath, path);
	projects.push_back(newProject);
	
	projectBrowser->addProject(newProject);
	return newProject;
}

int PolycodeProjectManager::removeProject(PolycodeProject *project) {		
	for(int i=0;i<projects.size();i++) {
		if(projects[i] == project) {
			projects.erase(projects.begin()+i);
		}
	}	
	
	if(activeProject == project) {
		activeProject = NULL;
	}
	
	delete project;
	
	return 1;
}


void PolycodeProjectManager::createNewProject(String templateFolder, String projectName, String projectLocation) {	

	CoreServices::getInstance()->getCore()->createFolder(projectLocation);		
	
	if(OSBasics::isFolder(projectLocation+"/"+projectName)) {
		int projectSuffix = 0;
		do {
			projectName = projectName + "_" + String::IntToString(projectSuffix);
			
		} while (OSBasics::isFolder(projectLocation+"/"+projectName));
	}	
	
	CoreServices::getInstance()->getCore()->copyDiskItem(templateFolder, projectLocation+"/"+projectName);
	CoreServices::getInstance()->getCore()->moveDiskItem(projectLocation+"/"+projectName+"/template.polyproject",  projectLocation+"/"+projectName+"/"+projectName+".polyproject");
	openProject(projectLocation+"/"+projectName+"/"+projectName+".polyproject");	
}
