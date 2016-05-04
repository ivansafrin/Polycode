//
// Polycode template. Write your code here.
// 

#include "PolycodeTemplateApp.h"


PolycodeTemplateApp::PolycodeTemplateApp(PolycodeView *view) {
    core = new POLYCODE_CORE(view, 1920, 1080,false,false, 0,0,60, 0, true);
    
    core->addFileSource("archive", core->getResourcePathForFile("default.pak"));
    ResourcePool *globalPool = Services()->getResourceManager()->getGlobalPool();
    globalPool->loadResourcesFromFolder("default", true);
    
    // Write your code here!
    
    Scene *scene = new Scene(Scene::SCENE_2D);
    scene->useClearColor = true;
    scene->clearColor.setColor(0.2, 0.0, 0.0, 1.0);
    
    test = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 0.5, 0.2);
    test->setMaterialByName("UnlitUntextured");
    test->color = Color(1.0, 0.0, 0.0, 1.0);
//    test->enableScissor = true;
//    test->scissorBox.setRect(100, 50, 100, 30);
    scene->addChild(test);
    
    Sound *test = new Sound(core->getResourcePathForFile("test.ogg"));
    test->Play(true);
    
    Services()->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
}

void PolycodeTemplateApp::handleEvent(Event *event) {
    InputEvent *inputEvent = (InputEvent*) event;
}

PolycodeTemplateApp::~PolycodeTemplateApp() {
    
}

bool PolycodeTemplateApp::Update() {
    Number elapsed = core->getElapsed();
    
    test->Roll(elapsed * 20.0);
    
    return core->updateAndRender();
}