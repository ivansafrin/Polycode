//
// Polycode template. Write your code here.
// 

#include "PolycodeTemplateApp.h"


PolycodeTemplateApp::PolycodeTemplateApp(PolycodeView *view) {
    core = new CocoaCore(view, 1280/2,720/2,false,false, 0,0,60, 0, true);
    
    core->addFileSource("archive", "default.pak");
    ResourcePool *globalPool = Services()->getResourceManager()->getGlobalPool();
    globalPool->loadResourcesFromFolder("default", true);

    core->addFileSource("archive", "hdr.pak");
    globalPool->loadResourcesFromFolder("hdr", true);
    
    
	// Write your code here!
    
    Scene *scene = new Scene(Scene::SCENE_2D);
    scene->useClearColor = true;
    scene->clearColor.setColor(0.0, 0.0, 0.0, 1.0);
    test = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 0.5, 0.5);
    test->setMaterialByName("Unlit");
    test->getShaderPass(0).shaderBinding->loadTextureForParam("diffuse", "main_icon.png");
//    test->color = Color(2.0, 2.0, 2.0, 1.0);
    scene->addChild(test);


    scene->getDefaultCamera()->setPostFilterByName("HDRProcessBloom");
    Camera *camera = scene->getDefaultCamera();

    camera->getShaderPass(0).shaderBinding->addParam(ProgramParam::PARAM_NUMBER, "brightThreshold")->setNumber(0.1);
    camera->getShaderPass(1).shaderBinding->addParam(ProgramParam::PARAM_NUMBER, "blurSize")->setNumber(0.01);
    camera->getShaderPass(2).shaderBinding->addParam(ProgramParam::PARAM_NUMBER, "blurSize")->setNumber(0.01);
    camera->getShaderPass(3).shaderBinding->addParam(ProgramParam::PARAM_NUMBER, "bloomFactor")->setNumber(2.0);
    camera->getShaderPass(3).shaderBinding->addParam(ProgramParam::PARAM_NUMBER, "exposure")->setNumber(0.7);
    
  //  scene->getDefaultCamera()->setPostFilterByName("Invert");
//    Sound *music = new Sound("BUGSHUFFLE.ogg");
  //  music->Play();
    
    Services()->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
}

void PolycodeTemplateApp::handleEvent(Event *event) {
    InputEvent *inputEvent = (InputEvent*) event;
}

PolycodeTemplateApp::~PolycodeTemplateApp() {
    
}

bool PolycodeTemplateApp::Update() {
    Number elapsed = core->getElapsed();
    
    test->Roll(elapsed * 45.0);
    
    return core->updateAndRender();
}