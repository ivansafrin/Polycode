//
// Polycode template. Write your code here.
// 

#include "PolycodeTemplateApp.h"
#include "polycode/view/android/PolycodeView.h"


PolycodeTemplateApp::PolycodeTemplateApp(PolycodeView *view) {
    core = new POLYCODE_CORE(view, 800,480,false,false, 0,0,60);

    ResourcePool *globalPool = Services()->getResourceManager()->getGlobalPool();
    globalPool->loadResourcesFromFolder("default", true);

	// Write your code here!
    srand(time(NULL));
    Scene *scene = new Scene(Scene::SCENE_2D);
    scene->useClearColor = true;
    scene->clearColor.setColor(1.0f / (float)(rand() % 5),1.0f / (float)(rand()%5),1.0f / (float)(rand() % 5),1.0f);

    ScenePrimitive *test = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 0.5, 0.5);
    scene->addChild(test);
    test->setPositionY(0.2);
    test->setMaterialByName("Unlit");
    test->getShaderPass(0).shaderBinding->loadTextureForParam("diffuse", "main_icon.png");
    //test->setColor(1.0,0.0,0.0,1.0);

    SceneLabel *testLabel = new SceneLabel("Hello Polycode!", 32, "sans", Label::ANTIALIAS_FULL, 0.2);
	testLabel->setPositionY(-0.2);
    scene->addChild(testLabel);

//    bgSound = new Sound("FightBG.WAV");
//    bgSound->Play();
//    bgSound->setPitch(10.0);


    //sound1 = new Sound("hit.wav");
    //Logger::log("before Play");
    //sound1->Play(true);
    //Logger::log("after Play");
//    sound1->setPitch(2.3);

//    sound2 = new Sound("test.wav");
//     sound3 = new Sound("curve_02_c.wav");

    //sound2->Play(true);
  
    Services()->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
    Services()->getInput()->addEventListener(this, InputEvent::EVENT_TOUCHES_BEGAN);
    Services()->getInput()->addEventListener(this, InputEvent::EVENT_TOUCHES_ENDED);
    Services()->getInput()->addEventListener(this, InputEvent::EVENT_TOUCHES_MOVED);
}

void PolycodeTemplateApp::handleEvent(Event *event) {
    InputEvent *inputEvent = (InputEvent*) event;
    if(inputEvent->getEventCode() == InputEvent::EVENT_KEYDOWN){
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
    } else if (inputEvent->getEventCode() == InputEvent::EVENT_TOUCHES_BEGAN){
        Logger::log("Touch began: %f, %f", inputEvent->touch.position.x, inputEvent->touch.position.y);
    } else if(inputEvent->getEventCode() == InputEvent::EVENT_TOUCHES_ENDED){
        Logger::log("Touch ended: %f, %f", inputEvent->touch.position.x, inputEvent->touch.position.y);
    } else if(inputEvent->getEventCode() == InputEvent::EVENT_TOUCHES_MOVED){
        Logger::log("Touch moved: %f, %f", inputEvent->touch.position.x, inputEvent->touch.position.y);
    }
}

PolycodeTemplateApp::~PolycodeTemplateApp() {
    
}

bool PolycodeTemplateApp::Update() {
    if (!core->paused) {
        return core->updateAndRender();
    } else {
        usleep(200000);
        return true;
    }
}
