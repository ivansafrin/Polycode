//
// Polycode template. Write your code here.
// 

#include "PolycodeTemplateApp.h"
#include "polycode/view/android/PolycodeView.h"


PolycodeTemplateApp::PolycodeTemplateApp(PolycodeView *view) {
    core = new POLYCODE_CORE(view, 800,480,false,false, 0,0,60, -1, true);

    core->addFileSource("archive", "default.pak");
    ResourcePool *globalPool = Services()->getResourceManager()->getGlobalPool();
    globalPool->loadResourcesFromFolder("default", true);

	// Write your code here!
    srand(time(NULL));
    scene = new Scene(Scene::SCENE_2D);
    scene->useClearColor = true;
    scene->clearColor.setColor(1.0f / (float)(rand() % 5),1.0f / (float)(rand()%5),1.0f / (float)(rand() % 5),1.0f);

    test = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 0.5, 0.5);
    test->setPositionY(0.2);
    test->setMaterialByName("Unlit");
    test->getShaderPass(0).shaderBinding->loadTextureForParam("diffuse", "main_icon.png");

    SceneLabel *testLabel = new SceneLabel("Hello Polycode!", 32, "sans", Label::ANTIALIAS_FULL, 0.2);
	testLabel->setPositionY(-0.2);
    scene->addChild(testLabel);

    /*ScenePrimitive* box;
    for(int i = 0; i < 1000; i++){
        box = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.2, 0.2,0.2);
        box->setMaterialByName("UnlitUntextured");
        //box->setColor(1.0, 0.0,0.0, 1.0);
        //box->getShaderPass(0).shaderBinding->loadTextureForParam("diffuse", "default/default.png");
        scene->addChild(box);
    }*/

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

    running = 0;
    rot = Vector3();
    fps = new SceneLabel("0", 32, "sans", Label::ANTIALIAS_FULL, 0.1);
    fps->setPosition(-0.6,0.3);
    scene->addChild(fps);
    scene->addChild(test);

    /*game = new Scene(Scene::SCENE_3D);
    game->useClearColor = true;
    game->getActiveCamera()->setPosition(0, 0, 10);

    box = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 2, 2, 2);
    box->setMaterialByName("UnlitUntextured");
    box->setColor(0.1, 1.0, 1.0, 1.0);
    game->addChild(box);*/

    Services()->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
    Services()->getInput()->addEventListener(this, InputEvent::EVENT_TOUCHES_BEGAN);
    Services()->getInput()->addEventListener(this, InputEvent::EVENT_TOUCHES_ENDED);
    Services()->getInput()->addEventListener(this, InputEvent::EVENT_TOUCHES_MOVED);
    Services()->getCore()->addEventListener(this, Core::EVENT_ACCELEROMETER_MOTION);
    Services()->getCore()->addEventListener(this, Core::EVENT_GYRO_ROTATION);
}

void PolycodeTemplateApp::handleEvent(Event *event) {
    if(event->getEventType()=="InputEvent"){
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
            Ray r = scene->projectRayFromCameraAndViewportCoordinate(scene->getActiveCamera(),inputEvent->touch.position);
            test->setPosition(r.origin.x, r.origin.y);
        } else if(inputEvent->getEventCode() == InputEvent::EVENT_TOUCHES_ENDED){
            Ray r = scene->projectRayFromCameraAndViewportCoordinate(scene->getActiveCamera(),inputEvent->touch.position);
            test->setPosition(r.origin.x, r.origin.y);
        } else if(inputEvent->getEventCode() == InputEvent::EVENT_TOUCHES_MOVED){
            Ray r = scene->projectRayFromCameraAndViewportCoordinate(scene->getActiveCamera(),inputEvent->touch.position);
            test->setPosition(r.origin.x, r.origin.y);
        }
    } else if(event->getEventType() == "CoreMotionEvent"){
        CoreMotionEvent* motionEvent = (CoreMotionEvent*)event;
        if(motionEvent->getEventCode() == Core::EVENT_ACCELEROMETER_MOTION){
        } else if (motionEvent->getEventCode() == Core::EVENT_GYRO_ROTATION){
            test->Translate(motionEvent->amount.x*0.01, motionEvent->amount.y*0.01);
        }
    }
}

PolycodeTemplateApp::~PolycodeTemplateApp() {
    
}

bool PolycodeTemplateApp::Update() {
    if (!core->paused) {
        running += core->getElapsed();
        if(running >= 1){
            fps->setText(String::NumberToString(core->getFPS(),0));
            running = 0;
        }
        return core->updateAndRender();
    } else {
        usleep(200000);
        return true;
    }
}
