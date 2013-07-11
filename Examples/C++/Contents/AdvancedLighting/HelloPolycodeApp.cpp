#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) : EventHandler() {

	core = new POLYCODE_CORE(view, 640,480,false,false,0,0,90);

	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);
	CoreServices::getInstance()->getResourceManager()->addDirResource("Resources", false);
	
	Scene *scene = new Scene();
	ScenePrimitive *ground = new ScenePrimitive(ScenePrimitive::TYPE_PLANE, 5,5);
	ground->setMaterialByName("GroundMaterial");
	scene->addEntity(ground);

	ScenePrimitive *box = new ScenePrimitive(ScenePrimitive::TYPE_TORUS, 0.8,0.3,30,20);
	box->setMaterialByName("CubeMaterial");
	box->setPosition(0.0, 0.5, 0.0);
	scene->addEntity(box);
	
	SceneLight *light = new SceneLight(SceneLight::AREA_LIGHT, scene, 5);
	light->setPosition(3,2,3);
	light->setLightColor(1,0,0);
	scene->addLight(light);

	light = new SceneLight(SceneLight::AREA_LIGHT, scene, 5);
	light->setPosition(-3,2,3);
	light->setLightColor(0,1,0);
	scene->addLight(light);

	light = new SceneLight(SceneLight::AREA_LIGHT, scene, 5);
	light->setPosition(-3,2,-3);
	light->setLightColor(0,0,1);
	scene->addLight(light);

	light = new SceneLight(SceneLight::AREA_LIGHT, scene, 5);
	light->setPosition(3,2,-3);
	light->setLightColor(1,0,1);
	scene->addLight(light);

	light = new SceneLight(SceneLight::SPOT_LIGHT, scene, 4);
	light->setPosition(0,2,2);
	light->setSpotlightProperties(30,6);
	light->setLightColor(1,1,0);
	scene->addLight(light);
	light->lookAt(Vector3(0,0,0));
	light->enableShadows(true);
	
	light = new SceneLight(SceneLight::SPOT_LIGHT, scene, 4);
	light->setPosition(0,2,-2);
	light->setSpotlightProperties(30,6);
	light->setLightColor(0,1,1);
	scene->addLight(light);
	light->lookAt(Vector3(0,0,0));
	light->enableShadows(true);

	scene->getDefaultCamera()->setPosition(7,7,7);
	scene->getDefaultCamera()->lookAt(Vector3(0,0,0));

}

HelloPolycodeApp::~HelloPolycodeApp() {
}

bool HelloPolycodeApp::Update() {
    return core->updateAndRender();
}
