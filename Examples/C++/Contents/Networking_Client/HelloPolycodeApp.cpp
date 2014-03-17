#include "HelloPolycodeApp.h"
		
HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) : EventHandler() {

	core = new POLYCODE_CORE(view, 640,480,false,false,0,0,90);

	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

	gameScene = new Scene(Scene::SCENE_2D);	

	Scene *hudScene = new Scene(Scene::SCENE_2D);
	SceneLabel *label = new SceneLabel("Example client.  Press escape to exit.", 16);
	hudScene->addChild(label);
	
	motdLabel =  new SceneLabel("", 16);
	motdLabel->setPosition(0, -480/2+20);
	hudScene->addChild(motdLabel);
		
	client = new Client(6543, 50);
	client->setPersistentData(&clientData, sizeof(ClientData));
	
	client->addEventListener(this, ClientEvent::EVENT_CLIENT_READY);
	client->addEventListener(this, ClientEvent::EVENT_SERVER_DATA);	
	client->addEventListener(this, ClientEvent::EVENT_SERVER_DISCONNECTED);		
	
	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYUP);
	
	client->Connect("127.0.0.1", 52345);
	state = 0;
}	

HelloPolycodeApp::~HelloPolycodeApp() {
}

void HelloPolycodeApp::createClientPlayer(int clientID) {
	ClientPlayer *player = new ClientPlayer();
	player->clientID = clientID;
	
	SceneEntity *playerEntity = new SceneEntity();				
	ScenePrimitive *playerBody = new ScenePrimitive(ScenePrimitive::TYPE_CIRCLE, 30,30,3);				
	playerBody->setRoll(-90.0);	
	playerEntity->addChild(playerBody);
	gameScene->addChild(playerEntity);
	player->playerEntity = playerEntity;												
	
	player->state = 0;
	players.push_back(player);						
}

void HelloPolycodeApp::handleEvent(Event *event) {

	if(event->getDispatcher() == core->getInput()) {
		InputEvent *inputEvent = (InputEvent*)event;		
		switch(event->getEventCode()) {
			case InputEvent::EVENT_KEYDOWN:
				switch (inputEvent->keyCode()) {
					case KEY_ESCAPE:
						client->Disconnect();
					break;
					case KEY_UP:
						clientData.thrusting = 1;
					break;				
					case KEY_LEFT:
						clientData.turning_state = TURNING_LEFT;
					break;
					case KEY_RIGHT:
						clientData.turning_state = TURNING_RIGHT;
					break;
				}
			break;
			case InputEvent::EVENT_KEYUP:
				switch (inputEvent->key) {
					case KEY_UP:
						clientData.thrusting = 0;						
					break;				
					case KEY_LEFT:
					case KEY_RIGHT:
						clientData.turning_state = NOT_TURNING;
					break;					
				}
			break;			
		}
		
	}

	if(event->getDispatcher() == client) {
		ClientEvent *clientEvent = (ClientEvent*) event;
		
		switch(clientEvent->getEventCode()) {
			case ClientEvent::EVENT_CLIENT_READY:
				Logger::log("Connected to server with client ID: %d!\n", client->getClientID());
			break;
			case ClientEvent::EVENT_SERVER_DISCONNECTED:
				core->Shutdown();
			break;
			case ClientEvent::EVENT_SERVER_DATA:
			{
				switch(clientEvent->dataType) {
					case PACKET_TYPE_SERVER_DATA:
					{
						ServerState *serverState = (ServerState*) clientEvent->data;
						for(int i=0; i < players.size(); i++) {
							ClientPlayer *clientPlayer = players[i];
							for(int j=0; j < MAX_PLAYERS; j++) {
								if(clientPlayer->clientID == serverState->players[j].clientID && serverState->players[j].state != 0) {
									clientPlayer->playerEntity->setPosition(serverState->players[j].posX, serverState->players[j].posY);
									clientPlayer->playerEntity->setRoll(serverState->players[j].angle);								
								}
							}							
						}
					}
					break;
					case PLAYER_JOIN:
					{
						ServerClientInfo *newClientInfo = (ServerClientInfo*) clientEvent->data;
						createClientPlayer(newClientInfo->clientID);
					}
					break;
					case SERVER_INFO:
					{
						ServerInfo *info = (ServerInfo*) clientEvent->data;
						motdLabel->setText(info->motd);
						ServerState *serverState = &info->initialServerState;
												
						// create initial players
						for(int j=0; j < MAX_PLAYERS; j++) {
							if(serverState->players[j].state != 0) {
								createClientPlayer(serverState->players[j].clientID);
							}
						}							
						
						
						client->sendReliableDataToServer(NULL, 0, CLIENT_READY);
					}
					break;
				}
			}
			break;
		}
	}
}

bool HelloPolycodeApp::Update() {

    return core->updateAndRender();
}
