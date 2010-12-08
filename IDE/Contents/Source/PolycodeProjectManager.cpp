

#include "PolycodeProjectManager.h"

PolycodeProjectManager::PolycodeProjectManager() {
	
}

PolycodeProjectManager::~PolycodeProjectManager() {
	
}


void PolycodeProjectManager::openProject(string path) {
	printf("Opening project  %s\n", path.c_str());
	
	vector<std::string> bits = StringUtil::split(path, "/.");
	
	string projectPath = "";
	for(int i=0; i < bits.size() - 2; i++) {
		projectPath += "/"+bits[i];
	}
	
	string projectName = bits[bits.size()-2];
	
	PolycodeProject* newProject = new PolycodeProject(projectName, projectPath);
	projects.push_back(newProject);
	
	projectBrowser->addProject(newProject);
	
}

void PolycodeProjectManager::createNewProject(string templateFolder, wstring projectName, wstring projectLocation) {
	string _projectName;
	_projectName.assign(projectName.begin(),projectName.end());
	
	string _projectLocation;
	_projectLocation.assign(projectLocation.begin(),projectLocation.end());
	
	CoreServices::getInstance()->getCore()->createFolder(_projectLocation);		
	CoreServices::getInstance()->getCore()->copyDiskItem(templateFolder, _projectLocation+"/"+_projectName);
	CoreServices::getInstance()->getCore()->moveDiskItem(_projectLocation+"/"+_projectName+"/template.polyproject",  _projectLocation+"/"+_projectName+"/"+_projectName+".polyproject");
	openProject(_projectLocation+"/"+_projectName+"/"+_projectName+".polyproject");	
}
