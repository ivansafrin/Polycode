//
// Polycode template. Write your code here.
// 

#include "PolycodeTemplateApp.h"


PolycodeTemplateApp::PolycodeTemplateApp(PolycodeView *view) {
    core = new POLYCODE_CORE(view, 1280,720,false,false, 0,0,60);
    
    core->addFileSource("archive", "default.pak");
    ResourcePool *globalPool = Services()->getResourceManager()->getGlobalPool();
    globalPool->loadResourcesFromFolder("default", true);
    
	// Write your code here!
    
    Scene *scene = new Scene(Scene::SCENE_3D);
    scene->useClearColor = true;
    
    scene->getDefaultCamera()->setPosition(5.0, 5.0, 5.0);
    scene->getDefaultCamera()->lookAt(Vector3());
    
	test = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1.0, 1.0, 1.0);
	test->setMaterialByName("DefaultTextured");
	test->getShaderPass(0).shaderBinding->loadTextureForParam("diffuse", "white.png");
	test->getShaderPass(0).shaderBinding->addParam(ProgramParam::PARAM_COLOR, "diffuse_color")->setColor(Color(1.0, 1.0, 1.0, 1.0));
    scene->addChild(test);
    

    SceneLight *light = new SceneLight(SceneLight::POINT_LIGHT, scene, 200.0);
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
	test->Yaw(core->getElapsed() * 30.0);
    return core->updateAndRender();
}