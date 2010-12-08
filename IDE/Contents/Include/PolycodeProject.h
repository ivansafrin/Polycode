

#pragma once

#include "Polycode.h"

using namespace Polycode;

class PolycodeProject {
	public:
		PolycodeProject(string name, string path);
		~PolycodeProject();	
	
		wstring getProjectName() { return projectName; }
		wstring getRootFolder() { return projectFolder; }	
	
private:
	wstring projectFolder;	
	wstring projectName;
};