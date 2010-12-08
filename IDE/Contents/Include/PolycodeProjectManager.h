

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
	
	void createNewProject(string templateFolder, wstring projectName, wstring projectLocation);
	void openProject(string path);
	void setProjectBrowser(PolycodeProjectBrowser *projectBrowser) { this->projectBrowser = projectBrowser; }
	
protected:
	
	PolycodeProjectBrowser *projectBrowser;
	vector<PolycodeProject*> projects;
	
};	