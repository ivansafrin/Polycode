#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) {

	core = new POLYCODE_CORE(view, 640,480,false,false,0,0,90);

	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

	Screen *hud = new Screen();
	ScreenLabel *label = new ScreenLabel("Click on a shape to select it.", 16);
	hud->addChild(label);	

	scene = new CollisionScene();

	ScenePrimitive *ground = new ScenePrimitive(ScenePrimitive::TYPE_PLANE, 10, 10);
	ground->loadTexture("Resources/green_texture.png");
	scene->addEntity(ground);

	box = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1,1,1);
	box->loadTexture("Resources/pink_texture.png");
	box->setPosition(0,1,0);
	scene->addCollisionChild(box, CollisionSceneEntity::SHAPE_MESH);

	box = new ScenePrimitive(ScenePrimitive::TYPE_CONE, 1,1,10);
	box->loadTexture("Resources/pink_texture.png");
	box->setPosition(1,1,2);
	scene->addCollisionChild(box, CollisionSceneEntity::SHAPE_CONE);

	box = new ScenePrimitive(ScenePrimitive::TYPE_CYLINDER, 2,0.5,10);
	box->loadTexture("Resources/pink_texture.png");
	box->setPosition(2,1,-1);
	scene->addCollisionChild(box, CollisionSceneEntity::SHAPE_CYLINDER);

	
	scene->getDefaultCamera()->setPosition(7,7,7);
	scene->getDefaultCamera()->lookAt(Vector3(0,0,0));
	core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);	
	
	lastEntity = NULL;
}

HelloPolycodeApp::~HelloPolycodeApp() {
}

void HelloPolycodeApp::handleEvent(Event *e) {
	
	if(e->getDispatcher() == core->getInput()) {
		InputEvent *inputEvent = (InputEvent*)e;
		switch(e->getEventCode()) {
			case InputEvent::EVENT_MOUSEDOWN:
				Vector3 dir = CoreServices::getInstance()->getRenderer()->projectRayFrom2DCoordinate(inputEvent->mousePosition.x, inputEvent->mousePosition.y);
				RayTestResult res = scene->getFirstEntityInRay(scene->getDefaultCamera()->getPosition(), dir * 1000);				

				if(lastEntity) {
					lastEntity->setColor(1.0,1.0,1.0,1.0);
				}

				if(res.entity) {
					res.entity->setColor(1.0, 0.0,0.0,1.0);
					lastEntity = res.entity;
				}
			break;			
		}
	}	
}

bool HelloPolycodeApp::Update() {
	Number elapsed = core->getElapsed();
    return core->updateAndRender();
}
