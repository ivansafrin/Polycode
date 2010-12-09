

#pragma once

#include "Polycode.h"

using namespace Polycode;

class PolycodeProject {
	public:
		PolycodeProject(String name, String path);
		~PolycodeProject();	
	
		String getProjectName() { return projectName; }
		String getRootFolder() { return projectFolder; }	
	
private:
	String projectFolder;	
	String projectName;
};