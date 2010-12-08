
#include "PolycodeProject.h"

PolycodeProject::PolycodeProject(string name, string path) {
	
	printf("CREATING PROJECT %s %s\n", name.c_str(), path.c_str());
	
	projectName.assign(name.begin(), name.end());
	projectFolder.assign(path.begin(), path.end());
}

PolycodeProject::~PolycodeProject() {
	
}
