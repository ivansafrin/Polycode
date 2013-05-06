//
// Polycode template. Write your code here.
// 

#include "PolycodeTemplateApp.h"


PolycodeTemplateApp::PolycodeTemplateApp(PolycodeView *view) {
    core = new CocoaCore(view, 640,480,false,false, 0,0,60);	  
	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default");

	// Write your code here!
}

PolycodeTemplateApp::~PolycodeTemplateApp() {
    
}

bool PolycodeTemplateApp::Update() {
    return core->updateAndRender();
}