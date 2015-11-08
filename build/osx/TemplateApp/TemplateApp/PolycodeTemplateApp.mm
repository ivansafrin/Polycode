//
// Polycode template. Write your code here.
// 

#include "PolycodeTemplateApp.h"


PolycodeTemplateApp::PolycodeTemplateApp(PolycodeView *view) {
    core = new CocoaCore(view, 1280/2,720/2,false,false, 0,0,60, 0, true);
    
    core->addFileSource("archive", "default.pak");
    ResourcePool *globalPool = Services()->getResourceManager()->getGlobalPool();
    globalPool->loadResourcesFromFolder("default", true);
    
	// Write your code here!
    
    Scene *scene = new Scene(Scene::SCENE_3D);
    scene->useClearColor = true;
    
    scene->getDefaultCamera()->setPosition(5.0, 5.0, 5.0);
    scene->getDefaultCamera()->lookAt(Vector3());

    SceneLabel *what = new SceneLabel("Huh?", 12, "mono", Label::ANTIALIAS_FULL, 1.0);
    scene->addChild(what);
    what->setPosition(0.0, 2.0, 0.0);
    
    ScenePrimitive *test = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1.0, 1.0, 1.0);
    test->setMaterialByName("DefaultTextured");
    //test->getShaderPass(0).shaderBinding->loadTextureForParam("diffuse", "white.png");
    //test->getShaderPass(0).shaderBinding->addParam(ProgramParam::PARAM_COLOR, "diffuse_color")->setColor(Color(1.0, 1.0, 1.0, 1.0));
    scene->addChild(test);

    SceneLight *light = new SceneLight(SceneLight::POINT_LIGHT, scene, 500.0);
    scene->addLight(light);
    scene->addChild(light);
    light->setPosition(-10.0, 10.0, 10.0);

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