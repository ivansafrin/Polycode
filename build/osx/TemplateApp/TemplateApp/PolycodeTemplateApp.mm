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
    
    
    Scene *scene = new Scene(Scene::SCENE_3D);
    scene->useClearColor = true;
    sourceEntity = new Entity();
    
    SceneSound *testSound = new SceneSound("test.wav", 20, 50);
    testSound->getSound()->Play(true);
    sourceEntity->addChild(testSound);
    
    ScenePrimitive *soundShape = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1,1,1);
    sourceEntity->addChild(soundShape);
    scene->addEntity(sourceEntity);
    
    SceneSoundListener *soundListener = new SceneSoundListener();
    scene->addEntity(soundListener);
    
    positionValue = 0;
    
    Services()->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
}

void PolycodeTemplateApp::handleEvent(Event *event) {
    InputEvent *inputEvent = (InputEvent*) event;
}

PolycodeTemplateApp::~PolycodeTemplateApp() {
    
}

bool PolycodeTemplateApp::Update() {
    Number elapsed = core->getElapsed();
    
    positionValue += elapsed;
    sourceEntity->setPosition((sin(positionValue) * 20), 0, cos(positionValue) * 50);
    sourceEntity->Roll(core->getElapsed() * 120);
    sourceEntity->Pitch(core->getElapsed()* 120);
    
    return core->updateAndRender();
}