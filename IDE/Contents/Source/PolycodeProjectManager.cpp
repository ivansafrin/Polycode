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
#include "PolycodeToolLauncher.h"

PolycodeProjectManager::PolycodeProjectManager() : EventDispatcher() {
	activeProject = NULL;
	activeFolder = "";
	selectedFile = "";
}

PolycodeProjectManager::~PolycodeProjectManager() {

}


PolycodeProject* PolycodeProjectManager::openProject(String path) {

	for(int i=0; i < projects.size(); i++) {
		if(projects[i]->getProjectFile() == path) {
			return projects[i];
		}
	}

	printf("Opening project  %s\n", path.c_str());

	FILE *f = fopen(path.c_str(), "r");
	if(!f) {
		printf("WARNING: PROJECT DOESNT EXIST! (%s)\n", path.c_str());
		return NULL;
	}
	fclose(f);

	vector<String> bits = path.split("/");

	String projectPath = bits[0];
	if(bits.size() > 2) {
		for(int i=1; i < bits.size() - 1; i++) {
			projectPath += "/"+bits[i];
		}
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
		this->setActiveProject(NULL);
	}

	delete project;

	return 1;
}

PolycodeProject *PolycodeProjectManager::getProjectByProjectFile(String projectFile) {
	for(int i=0; i < projects.size(); i++) {
		if(projects[i]->getProjectFile() == projectFile) {
			return projects[i];
		}
	}
	return NULL;
}

void PolycodeProjectManager::setActiveProject(PolycodeProject* project) {
	if(project != activeProject) {

		if(activeProject != NULL) {
			CoreServices::getInstance()->getResourceManager()->removeArchive(activeProject->getRootFolder());
		}

		activeProject = project;
		if(project){
			CoreServices::getInstance()->getResourceManager()->addArchive(project->getRootFolder());
		}
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}
}

void PolycodeProjectManager::createNewFile(String templatePath, String newFileName) {
	if(activeFolder == "")
		return;

	std::vector<String> bits = templatePath.split(".");
	String extension = bits[bits.size()-1];

	CoreServices::getInstance()->getCore()->copyDiskItem(templatePath, activeFolder+"/"+newFileName+"."+extension);
}

void PolycodeProjectManager::createNewProject(String templateFolder, String projectName, String projectLocation) {

	CoreServices::getInstance()->getCore()->createFolder(projectLocation);

	if(OSBasics::isFolder(projectLocation+"/"+projectName)) {
		int projectSuffix = 0;
		do {
			projectName = projectName + "_" + String::IntToString(projectSuffix);

		} while (OSBasics::isFolder(projectLocation+"/"+projectName));
	}

	CoreServices::getInstance()->getCore()->copyDiskItem(CoreServices::getInstance()->getCore()->getDefaultWorkingDirectory()+"/"+templateFolder, projectLocation+"/"+projectName);
	CoreServices::getInstance()->getCore()->moveDiskItem(projectLocation+"/"+projectName+"/template.polyproject",  projectLocation+"/"+projectName+"/"+projectName+".polyproject");
	openProject(projectLocation+"/"+projectName+"/"+projectName+".polyproject");	
}

void PolycodeProjectManager::exportProject(PolycodeProject *project, String exportPath, bool macOS, bool windows, bool linux_, bool compileScripts) {

	String polycodeBasePath = CoreServices::getInstance()->getCore()->getDefaultWorkingDirectory();

	String publishPath = polycodeBasePath+"/Standalone/Publish";

	String polyappPath = PolycodeToolLauncher::generateTempPath(project) + ".polyapp";
	PolycodeToolLauncher::buildProject(project, polyappPath, compileScripts);	

	if(macOS) {
		PolycodeConsole::print("Exporting Mac version to "+exportPath+"/Mac \n");

		CoreServices::getInstance()->getCore()->createFolder(exportPath+"/Mac");

		String appPath = exportPath+"/Mac/"+project->getProjectName()+".app";

		CoreServices::getInstance()->getCore()->createFolder(appPath);
		CoreServices::getInstance()->getCore()->createFolder(appPath+"/Contents");
		CoreServices::getInstance()->getCore()->createFolder(appPath+"/Contents/MacOS");
		CoreServices::getInstance()->getCore()->copyDiskItem(publishPath+"/Mac/StandalonePlayer.app/Contents/MacOS/StandalonePlayer", appPath+"/Contents/MacOS/"+project->getProjectName());
		CoreServices::getInstance()->getCore()->copyDiskItem(publishPath+"/Mac/StandalonePlayer.app/Contents/Resources", appPath+"/Contents/Resources");
		CoreServices::getInstance()->getCore()->copyDiskItem(publishPath+"/Mac/StandalonePlayer.app/Contents/Info.plist", appPath+"/Contents/Info.plist");
		CoreServices::getInstance()->getCore()->removeDiskItem(appPath+"/Contents/Resources/main.polyapp");
		CoreServices::getInstance()->getCore()->copyDiskItem(polyappPath, appPath+"/Contents/Resources/main.polyapp");

	}

	if(windows) {
		PolycodeConsole::print("Exporting Windows version to "+exportPath+"/Win \n");
		CoreServices::getInstance()->getCore()->copyDiskItem(publishPath+"/Win", exportPath+"/Win");
		CoreServices::getInstance()->getCore()->moveDiskItem(exportPath+"/Win/StandalonePlayer.exe", exportPath+"/Win/"+project->getProjectName()+".exe");
		CoreServices::getInstance()->getCore()->removeDiskItem(exportPath+"/Win/main.polyapp");
		CoreServices::getInstance()->getCore()->copyDiskItem(polyappPath, exportPath+"/Win/main.polyapp");
	}

	if(linux_) {
		PolycodeConsole::print("Exporting Linux version to "+exportPath+"/Linux \n");
		CoreServices::getInstance()->getCore()->copyDiskItem(publishPath+"/Linux", exportPath+"/Linux");
		CoreServices::getInstance()->getCore()->moveDiskItem(exportPath+"/Linux/StandalonePlayer", exportPath+"/Linux/"+project->getProjectName());
		CoreServices::getInstance()->getCore()->removeDiskItem(exportPath+"/Linux/main.polyapp");
		CoreServices::getInstance()->getCore()->copyDiskItem(polyappPath, exportPath+"/Linux/main.polyapp");
	}
}

