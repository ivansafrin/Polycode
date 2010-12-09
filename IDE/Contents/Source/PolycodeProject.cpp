
#include "PolycodeProject.h"

PolycodeProject::PolycodeProject(String name, String path) {
	
	printf("CREATING PROJECT %s %s\n", name.c_str(), path.c_str());
	
	projectName = name;
	projectFolder = path;
	
}

PolycodeProject::~PolycodeProject() {
	
}
