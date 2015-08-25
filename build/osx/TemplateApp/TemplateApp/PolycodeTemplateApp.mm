//
// Polycode template. Write your code here.
// 

#include "PolycodeTemplateApp.h"


PolycodeTemplateApp::PolycodeTemplateApp(PolycodeView *view) {
    core = new CocoaCore(view, 1280,720,false,false, 0,0,60);
    
    core->addFileSource("archive", "default.pak");
    ResourcePool *globalPool = Services()->getResourceManager()->getGlobalPool();
    globalPool->loadResourcesFromFolder("default", true);
    
	// Write your code here!
    
    Scene *scene = new Scene(Scene::SCENE_2D);
    scene->useClearColor = true;
    
    ScenePrimitive *test = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 0.5, 0.5);
    test->setMaterialByName("Unlit");
    test->getLocalShaderOptions()->loadTextureForParam("diffuse", "main_icon.png");
    scene->addChild(test);
    
    SceneLabel *testLabel = new SceneLabel("Test!", 32, "sans", Label::ANTIALIAS_FULL, 0.2);
    scene->addChild(testLabel);
    
    bgSound = new Sound("bedlayer_main.wav");
    bgSound->Play();
//    bgSound->setPitch(10.0);
    
    
    sound1 = new Sound("marimba-lo.wav");
    
    sound1->setPitch(2.3);
    
    sound2 = new Sound("initial_touch_01.wav");
    sound3 = new Sound("curve_02_c.wav");
    
    //sound2->Play(true);
    
    Services()->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
}

void PolycodeTemplateApp::handleEvent(Event *event) {
    InputEvent *inputEvent = (InputEvent*) event;
    
    switch(inputEvent->getKey()) {
        case KEY_z:
            sound1->Play(true);
        break;
        case KEY_x:
            sound2->Play();
        break;
        case KEY_c:
            sound3->Play();
        break;
            
    }
}

PolycodeTemplateApp::~PolycodeTemplateApp() {
    
}

bool PolycodeTemplateApp::Update() {
    return core->updateAndRender();
}