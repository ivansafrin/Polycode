#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) : EventHandler() {

	core = new POLYCODE_CORE(view, 640,480,false,true,6,16,90, 0, true);

	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);
	CoreServices::getInstance()->getResourceManager()->addDirResource("Resources", false);
	
	scene = new Scene();
	ScenePrimitive *ground = new ScenePrimitive(ScenePrimitive::TYPE_PLANE, 5,5);
	ground->setMaterialByName("GroundMaterial");
	scene->addEntity(ground);

	torus = new ScenePrimitive(ScenePrimitive::TYPE_TORUS, 0.8,0.3,30,20);
	torus->setMaterialByName("CubeMaterial");
	torus->setPosition(0.0, 0.5, 0.0);
	scene->addEntity(torus);

	SceneLight *light = new SceneLight(SceneLight::POINT_LIGHT, scene, 5);
	light->setPosition(3,2,3);
	light->setLightColor(1,0,0);
	scene->addLight(light);

	light = new SceneLight(SceneLight::POINT_LIGHT, scene, 5);
	light->setPosition(-3,2,3);
	light->setLightColor(0,1,0);
	scene->addLight(light);

	light = new SceneLight(SceneLight::POINT_LIGHT, scene, 5);
	light->setPosition(-3,2,-3);
	light->setLightColor(0,0,1);
	scene->addLight(light);

	light = new SceneLight(SceneLight::POINT_LIGHT, scene, 5);
	light->setPosition(3,2,-3);
	light->setLightColor(1,0,1);
	scene->addLight(light);
    
    lights = new Entity();
    scene->addChild(lights);
    
	light = new SceneLight(SceneLight::SPOT_LIGHT, scene, 4);
	light->setPosition(0,4,1);
	light->setLightColor(1,1,0);
	scene->addLight(light);
	lights->addChild(light);
	light->lookAt(Vector3(0,0,0));
	light->enableShadows(true);
    light->getSpotlightCamera()->frustumCulling = false;

	light = new SceneLight(SceneLight::SPOT_LIGHT, scene, 4);
	light->setPosition(0,4,-1);
	light->setLightColor(0,1,1);
	scene->addLight(light);
	lights->addChild(light);
	light->lookAt(Vector3(0,0,0));
	light->enableShadows(true);
    light->getSpotlightCamera()->frustumCulling = false;
    

    cameraRotation = 0.0;
}

HelloPolycodeApp::~HelloPolycodeApp() {
}

bool HelloPolycodeApp::Update() {
    lights->Yaw(core->getElapsed() * 10.0);
    torus->Roll(core->getElapsed() * 10.0);
    
    cameraRotation += core->getElapsed() * 0.1;
    
    scene->getDefaultCamera()->setPosition(sin(cameraRotation) * 7.0, 7.0,cos(cameraRotation) * 7.0);
	scene->getDefaultCamera()->lookAt(Vector3(0,0,0));
    
    return core->updateAndRender();
}
