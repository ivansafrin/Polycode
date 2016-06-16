//
// Polycode template. Write your code here.
// 

#include "PolycodeTemplateApp.h"


PolycodeTemplateApp::PolycodeTemplateApp(PolycodeView *view) {
    core = new CocoaCore(view, 1280/2,720/2,false,false, 0,0,60, 0, true);
    
    core->addFileSource("archive", "lua_Polycode.pak");
    core->addFileSource("archive", "js_Polycode.pak");
    
    core->addFileSource("archive", "default.pak");
    ResourcePool *globalPool = Services()->getResourceManager()->getGlobalPool();
    globalPool->loadResourcesFromFolder("default", true);

    core->addFileSource("archive", "hdr.pak");
    globalPool->loadResourcesFromFolder("hdr", true);
	
	std::shared_ptr<Script>mainScript = std::static_pointer_cast<Script>(globalPool->loadResource("main.js"));
}

void PolycodeTemplateApp::handleEvent(Event *event) {
    InputEvent *inputEvent = (InputEvent*) event;
}

PolycodeTemplateApp::~PolycodeTemplateApp() {
    
}

bool PolycodeTemplateApp::Update() {
    return core->updateAndRender();
}