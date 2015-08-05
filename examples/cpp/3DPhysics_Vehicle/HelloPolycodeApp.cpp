#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) : EventHandler() {

	core = new POLYCODE_CORE(view, 640,480,false,true,0,0,90, 0, true);

	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);
	
	scene = new PhysicsScene();

	ScenePrimitive *ground = new ScenePrimitive(ScenePrimitive::TYPE_PLANE, 30, 30);
	ground->loadTexture("Resources/green_texture.png");
	scene->addPhysicsChild(ground, PhysicsSceneEntity::SHAPE_PLANE, 0.0);

	// Some obstacles	
	ScenePrimitive *box = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 4,4,6);	
	box->setPitch(25.0);
	box->setPosition(7,-1.05, 0.0);
	box->setColor(0.5,0.5,1.0,1.0);
	box->loadTexture("Resources/green_texture.png");
	scene->addPhysicsChild(box, PhysicsSceneEntity::SHAPE_BOX, 0.0);

	box = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 4,4,6);	
	box->setPitch(25.0);
	box->setPosition(-7,-1.05, 0.0);
	box->setColor(0.5,0.5,1.0,1.0);
	box->loadTexture("Resources/green_texture.png");
	scene->addPhysicsChild(box, PhysicsSceneEntity::SHAPE_BOX, 0.0);

	box = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 20,2,5);	
	box->setPosition(0.0,1.0, -4.3);
	box->setColor(0.5,0.5,1.0,1.0);
	box->loadTexture("Resources/green_texture.png");
	scene->addPhysicsChild(box, PhysicsSceneEntity::SHAPE_BOX, 0.0);

	for(int i=0; i < 10; i++) {
		ScenePrimitive *box = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.7,0.7,0.7);
		box->loadTexture("Resources/pink_texture.png");
		box->Roll(-45 + (rand() % 90));
		box->Pitch(-45 + (rand() % 90));		
		box->setPosition(-3 + (rand() % 6), 2 + i*0.5, -5 + (rand() % 3));
		scene->addPhysicsChild(box, PhysicsSceneEntity::SHAPE_BOX, 1.0);
	}

	// The vehicle
	vehicle = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1.0,0.5,2.0);
	vehicle->loadTexture("Resources/pink_texture.png");
	vehicle->setColor(1.0, 1.0, 0.0, 1.0);
	vehicle->setPosition(6,1,5);
	vehicleController = scene->addVehicleChild(vehicle, 5.0, 1.0);
	
	ScenePrimitive *wheel = new ScenePrimitive(ScenePrimitive::TYPE_SPHERE, 0.3, 10, 10);
	wheel->loadTexture("Resources/pink_texture.png");
	wheel->setColor(0.0, 1.0, 0.0, 1.0);
	vehicleController->addWheel(wheel, Vector3(0.6,0,-0.5), Vector3(0,-1,0), Vector3(-1,0,0), 0.2,  0.3, true);
	scene->addEntity(wheel);

	wheel = new ScenePrimitive(ScenePrimitive::TYPE_SPHERE, 0.3, 10, 10);
	wheel->loadTexture("Resources/pink_texture.png");
	wheel->setColor(0.0, 1.0, 0.0, 1.0);
	vehicleController->addWheel(wheel, Vector3(-0.6,0,-0.5), Vector3(0,-1,0), Vector3(-1,0,0), 0.2,  0.3, true);
	scene->addEntity(wheel);

	wheel = new ScenePrimitive(ScenePrimitive::TYPE_SPHERE, 0.3, 10, 10);
	wheel->loadTexture("Resources/pink_texture.png");
	wheel->setColor(0.0, 1.0, 0.0, 1.0);
	vehicleController->addWheel(wheel, Vector3(0.6,0,0.5), Vector3(0,-1,0), Vector3(-1,0,0), 0.2,  0.3, false);
	scene->addEntity(wheel);

	wheel = new ScenePrimitive(ScenePrimitive::TYPE_SPHERE, 0.3, 10, 10);
	wheel->loadTexture("Resources/pink_texture.png");
	wheel->setColor(0.0, 1.0, 0.0, 1.0);
	vehicleController->addWheel(wheel, Vector3(-0.6,0,0.5), Vector3(0,-1,0), Vector3(-1,0,0), 0.2,  0.3, false);
	scene->addEntity(wheel);
	
	steeringValue = 0;
	engineForce = 0;
	breaking = false;
	
	testBox = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 4, 4, 4);
	testBox->loadTexture("Resources/pink_texture.png");
	testBox->setColor(0.3,0.5, 1.0,0.4);
	testBox->setPosition(-5,2,7);
	scene->addCollisionChild(testBox, PhysicsSceneEntity::SHAPE_BOX);
	
	
	scene->getDefaultCamera()->setPosition(16,16,16);
	scene->getDefaultCamera()->lookAt(Vector3(0,0,0));
		
	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYUP);	
}

void HelloPolycodeApp::handleEvent(Event *e) {
	if(e->getDispatcher() == core->getInput()) {
		InputEvent *inputEvent = (InputEvent*)e;
		
		switch(e->getEventCode()) {
			case InputEvent::EVENT_KEYDOWN:
				switch (inputEvent->keyCode()) {
					case KEY_r:
						vehicleController->warpVehicle(Vector3(6,1,5));
					break;
					case KEY_UP:
						engineForce = -15;
					break;
					case KEY_DOWN:
						engineForce = 15;					
					break;
					case KEY_LEFT:
						steeringValue = 0.5;											
					break;
					case KEY_RIGHT:
						steeringValue = -0.5;						
					break;					
					case KEY_SPACE:
						breaking = true;
					break;										
				}
			break;
			case InputEvent::EVENT_KEYUP:
				switch (inputEvent->key) {
					case KEY_UP:
					case KEY_DOWN:
						engineForce = 0;										
					break;					
					case KEY_LEFT:
					case KEY_RIGHT:
						steeringValue = 0.0;																
					break;		
					case KEY_SPACE:
						breaking = false;
					break;								
				}
			break;			
		}
		
	}
}

HelloPolycodeApp::~HelloPolycodeApp() {
}

bool HelloPolycodeApp::Update() {
	Number elapsed = core->getElapsed();
	
	if(breaking) {
		vehicleController->setBrake(20, 2);
		vehicleController->setBrake(20, 3);							
		vehicleController->applyEngineForce(0, 2);
		vehicleController->applyEngineForce(0, 3);					
	} else {
		vehicleController->setBrake(0, 2);
		vehicleController->setBrake(0, 3);								
		vehicleController->applyEngineForce(engineForce, 2);
		vehicleController->applyEngineForce(engineForce, 3);			
	}
	
	vehicleController->setSteeringValue(steeringValue, 0);		
	vehicleController->setSteeringValue(steeringValue, 1);			
	
	CollisionResult res = scene->testCollision(vehicle, testBox);
	if(res.collided) {
		testBox->setColor(1.0,1.0,0.0,0.5);		
	} else {
		testBox->setColor(0.0,1.0,1.0,0.5);	
	}
    return core->updateAndRender();
}
