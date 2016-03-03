//
// Polycode template. Write your code here.
// 

#include "PolycodeTemplateApp.h"


PolycodeTemplateApp::PolycodeTemplateApp(PolycodeView *view) {
    core = new POLYCODE_CORE(view, 64,64,false,false, 0,0,60, 0, true);
    
    NSString *str = [[NSBundle mainBundle] pathForResource: @"default" ofType: @"pak"];
    
    core->addFileSource("archive", [str UTF8String]);
    ResourcePool *globalPool = Services()->getResourceManager()->getGlobalPool();
    globalPool->loadResourcesFromFolder("default", true);
    
    // Write your code here!
    
    Scene *scene = new Scene(Scene::SCENE_2D);
    scene->useClearColor = true;
    scene->clearColor.setColor(0.2, 0.0, 0.0, 1.0);
    
    ScenePrimitive *test = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 10.0, 10.0);
    test->setMaterialByName("UnlitUntextured");
    test->color = Color(1.0, 0.0, 0.0, 1.0);
    test->enableScissor = true;
    test->scissorBox.setRect(100, 50, 100, 30);
    scene->addChild(test);
    
//    Sound *music = new Sound("BUGSHUFFLE.ogg");
//    music->Play();
    
    Services()->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
}

void PolycodeTemplateApp::handleEvent(Event *event) {
    InputEvent *inputEvent = (InputEvent*) event;
}

PolycodeTemplateApp::~PolycodeTemplateApp() {
    
}

bool PolycodeTemplateApp::Update() {
    return core->updateAndRender();
}