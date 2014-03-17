#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) : EventHandler() {

	core = new POLYCODE_CORE(view, 640,480,false,false,0,0,90);

	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);
	
	Scene *scene = new Scene(Scene::SCENE_2D_TOPLEFT);

	ScenePrimitive *shape = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 100,100);
	shape->setColor(1.0, 0.0, 0.0, 1.0);
	shape->setPosition(150,240);
	scene->addChild(shape);

	shape = new ScenePrimitive(ScenePrimitive::TYPE_CIRCLE, 100,100,100);
	shape->setColor(0.0, 1.0, 0.0, 1.0);
	shape->setPosition(260,240);
	scene->addChild(shape);

	shape = new ScenePrimitive(ScenePrimitive::TYPE_CIRCLE, 100,100,3);
	shape->setColor(1.0, 0.0, 1.0, 1.0);
	shape->setPosition(350,240);
	scene->addChild(shape);

	shape = new ScenePrimitive(ScenePrimitive::TYPE_CIRCLE, 100,100,6);
	shape->setColor(0.0, 1.0, 1.0, 1.0);
	shape->setPosition(460,240);
	scene->addChild(shape);
}

bool HelloPolycodeApp::Update() {
    return core->updateAndRender();
}
