//
// Polycode template. Write your code here.
// 

#include "PolycodeTemplateApp.h"
#include "polycode/view/android/PolycodeView.h"


PolycodeTemplateApp::PolycodeTemplateApp(PolycodeView *view) {
    core = new POLYCODE_CORE(view, 800,480,false,false, 0,0,60);

    core->addFileSource("android", "default");
    ResourcePool *globalPool = Services()->getResourceManager()->getGlobalPool();
    globalPool->loadResourcesFromFolder("default", true);

	// Write your code here!
    
    Scene *scene = new Scene(Scene::SCENE_2D);
    scene->useClearColor = true;
    scene->clearColor.setColor(1.0f,1.0f,0.13f,1.0f);

    ScenePrimitive *test = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 2, 2);
    scene->addChild(test);
    test->setColor(1.0,0.0,0.0,1.0);
	test->setPositionY(0.2);
    LOGI("scene prim worked");

    SceneLabel *testLabel = new SceneLabel("Hello Polycode!", 32, "sans", Label::ANTIALIAS_FULL, 0.2);
	testLabel->setPositionY(-0.2);
    scene->addChild(testLabel);
/*
    bgSound = new Sound("bedlayer_main.wav");
    bgSound->Play();
//    bgSound->setPitch(10.0);
    
    
    sound1 = new Sound("marimba-lo.wav");
    
    sound1->setPitch(2.3);
    
    sound2 = new Sound("initial_touch_01.wav");
    sound3 = new Sound("curve_02_c.wav");
    
    //sound2->Play(true);
  */
  
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
    if (!core->paused) {
        //LOGI("Update");
        return core->updateAndRender();
    } else {
        usleep(200*1000);
        return true;
    }
}
