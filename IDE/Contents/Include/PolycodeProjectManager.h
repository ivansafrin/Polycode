

#include "Polycode.h"
#include "PolycodeGlobals.h"
#include "PolycodeProject.h"
#include "PolycodeProjectBrowser.h"

#pragma once 


using namespace Polycode;

class PolycodeProjectManager {
	public:
		PolycodeProjectManager();
		~PolycodeProjectManager();
	
	void createNewProject(String templateFolder, String projectName, String projectLocation);
	PolycodeProject* openProject(String path);
	void setProjectBrowser(PolycodeProjectBrowser *projectBrowser) { this->projectBrowser = projectBrowser; }
	
	PolycodeProject* getActiveProject() { return activeProject; }
	void setActiveProject(PolycodeProject* project) { activeProject = project; }
	
	int getProjectCount() { return projects.size(); }
	PolycodeProject *getProjectByIndex(int index) { return projects[index]; }
	
protected:
	
	PolycodeProject* activeProject;
	
	PolycodeProjectBrowser *projectBrowser;
	vector<PolycodeProject*> projects;
	
};	