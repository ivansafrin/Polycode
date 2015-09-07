#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) : EventHandler() {

	core = new POLYCODE_CORE(view, 640,480,false,true,0,0,90, 0, true);

	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);


	scene = new PhysicsScene();

	ScenePrimitive *ground = new ScenePrimitive(ScenePrimitive::TYPE_PLANE, 10, 10);
	ground->loadTexture("Resources/green_texture.png");
	scene->addPhysicsChild(ground, PhysicsSceneEntity::SHAPE_PLANE, 0.0);

	for(int i=0; i < 10; i++) {
		ScenePrimitive *box = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.8,0.8,0.8);
		box->loadTexture("Resources/pink_texture.png");
		box->Roll(-45 + (rand() % 90));
		box->Pitch(-45 + (rand() % 90));		
		box->setPosition(-2 + (rand() % 4), i*0.5, -2 + (rand() % 4));
		scene->addPhysicsChild(box, PhysicsSceneEntity::SHAPE_BOX, 1.0);
	}

	player = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.5,1.0,0.5);
	player->loadTexture("Resources/pink_texture.png");
	player->setColor(1.0, 1.0, 0.0, 1.0);
	player->setPosition(2,1,2);
	playerController = scene->addCharacterChild(player, 10.0, 1.0, 0.5);	
	walkSpeed = 0;
	rotateSpeed = 0;
	playerDirection = 0;
	
	testBox = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 2, 2, 2);
	testBox->loadTexture("Resources/pink_texture.png");
	testBox->setColor(0.3,0.5, 1.0,0.4);
	testBox->setPosition(2,1,-2);
	scene->addCollisionChild(testBox, PhysicsSceneEntity::SHAPE_BOX);
		
	Scene *hud = new Scene(Scene::SCENE_2D_TOPLEFT);
	onGroundLabel = new SceneLabel("Arrow keys to control, spacebar to jump, press R to reset", 16);
    onGroundLabel->setAnchorPoint(-1.0, -1.0, 0.0);
	onGroundLabel->setPosition(0,0);
	hud->addChild(onGroundLabel);
	onGroundLabel = new SceneLabel("On Ground:", 16);
    onGroundLabel->setAnchorPoint(-1.0, -1.0, 0.0);
	onGroundLabel->setPosition(0,32);
	hud->addChild(onGroundLabel);
    
	
	scene->getDefaultCamera()->setPosition(7,7,7);
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
						playerController->warpCharacter(Vector3(2,1,2));
					break;				
					case KEY_UP:
						walkSpeed = 0.05;
					break;
					case KEY_DOWN:
						walkSpeed = -0.05;
					break;
					case KEY_LEFT:
						rotateSpeed = 3.0;
					break;
					case KEY_RIGHT:
						rotateSpeed = -3.0;
					break;					
					case KEY_SPACE:
						playerController->jump();
					break;										
				}
			break;
			case InputEvent::EVENT_KEYUP:
				switch (inputEvent->key) {
					case KEY_UP:
					case KEY_DOWN:
						walkSpeed = 0;					
					break;					
					case KEY_LEFT:
					case KEY_RIGHT:
						rotateSpeed = 0;					
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
	playerDirection += rotateSpeed * elapsed;
	
	player->setYaw(playerDirection*(180/PI));
	playerController->setWalkDirection(Vector3(walkSpeed * cos(playerDirection),0,walkSpeed * sin(-playerDirection)));
	
	if(playerController->onGround()) {
		onGroundLabel->setText("On Ground: YES");
	} else {
		onGroundLabel->setText("On Ground: NO");	
	}
	
	CollisionResult res = scene->testCollision(player, testBox);
	if(res.collided) {
		testBox->setColor(1.0,1.0,0.0,0.5);		
	} else {
		testBox->setColor(0.0,1.0,1.0,0.5);	
	}
	
	
    return core->updateAndRender();
}
