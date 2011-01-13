

#pragma once

#include "Polycode.h"

using namespace Polycode;

class PolycodeProject {
	public:
		PolycodeProject(String name, String path, String file);
		~PolycodeProject();	
	
		String getProjectName() { return projectName; }
		String getProjectFile() { return projectFile; }	
		String getRootFolder() { return projectFolder; }	
	
private:
	String projectFile;
	String projectFolder;	
	String projectName;
};