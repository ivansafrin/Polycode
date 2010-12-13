

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
	
protected:
	
	PolycodeProject* activeProject;
	
	PolycodeProjectBrowser *projectBrowser;
	vector<PolycodeProject*> projects;
	
};	