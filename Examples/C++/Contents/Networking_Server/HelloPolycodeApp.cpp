#include "HelloPolycodeApp.h"
		
HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) : ServerWorld(), EventHandler() {

	core = new POLYCODE_CORE(view, 640,480,false,false,0,0,90);

	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

	memset(serverInfo.motd, 0, 256);
	strcat(serverInfo.motd, "MOTD : ** Welcome to the Network Example server! **");

	gameScreen = new Screen();	

	Screen *hudScreen = new Screen();
	infoLabel = new ScreenLabel("Example server. [0 Players]", 32);
	hudScreen->addChild(infoLabel);
	
	server = new Server(52345, 50, this);
	
	server->addEventListener(this, ServerEvent::EVENT_CLIENT_CONNECTED);
	server->addEventListener(this, ServerEvent::EVENT_CLIENT_DISCONNECTED);		
}

HelloPolycodeApp::~HelloPolycodeApp() {
}

void HelloPolycodeApp::updateWorld(Number elapsed) {

	
	for(int i=0; i < players.size(); i++)  {	
		Player *player = players[i];
		
		// handle input flags
		if(player->thrusting == 1) {
			player->moveSpeed = 80;
		} else {
			player->moveSpeed = 0;
		}
		switch(player->turning_state) {
			case NOT_TURNING:
				player->rotateSpeed = 0;
			break;			
			case TURNING_LEFT:
				player->rotateSpeed = -100;			
			break;
			case TURNING_RIGHT:
				player->rotateSpeed = 100;			
			break;
			
		}
		
		// process movement	
		player->angle += player->rotateSpeed * elapsed;
		player->position.x += sin(player->angle * PI/180.0) * player->moveSpeed * elapsed;
		player->position.y += -cos(player->angle * PI/180.0) * player->moveSpeed * elapsed;
	
		// update the server display
		player->playerEntity->setPosition(player->position.x, player->position.y);
		player->playerEntity->setRotation(player->angle);

										
	}
	
	// set the server state
	for(int i=0; i < MAX_PLAYERS; i++)  {
		if(i < players.size()) {
			serverState.players[i] = players[i]->getClientInfo();
		} else {
			serverState.players[i].state = 0;
		}
	}
}

void HelloPolycodeApp::getWorldState(ServerClient *client, char **worldData,unsigned int *worldDataSize) {
	*worldData = (char*)&serverState;
	*worldDataSize = sizeof(ServerState);	
}

void HelloPolycodeApp::handleEvent(Event *event) {

	for(int i=0; i < players.size(); i++) {
		if(event->getDispatcher() == players[i]->client) {		
			ServerClientEvent *clientEvent = (ServerClientEvent*) event;
			Player *player = players[i];
			switch(clientEvent->getEventCode()) {
				case ServerClientEvent::EVENT_CLIENT_DATA:				
					switch(clientEvent->dataType) {
						case CLIENT_READY:
						{
							ServerClientInfo info = player->getClientInfo();
							server->sendReliableDataToAllClients((char*)&info, sizeof(ServerClientInfo), PLAYER_JOIN);
						}
						break;					
						case PLAYER_SHOOT:
						{
						
						}	
						break;
						case PACKET_TYPE_CLIENT_DATA:
							ClientData *clientData = (ClientData*) clientEvent->data;
							player->turning_state = clientData->turning_state;
							player->thrusting = clientData->thrusting;
						break;
					}
				break;
			}
		}
	}

	if(event->getDispatcher() == server) {
		ServerEvent *serverEvent = (ServerEvent*) event;
		switch(serverEvent->getEventCode()) {
		
			case ServerEvent::EVENT_CLIENT_DISCONNECTED:		
			{
				for(int i=0;i<players.size();i++) {
					if(players[i]->client == serverEvent->client) {			
						Player *player = players[i];
						players.erase(players.begin()+i);						
						
						gameScreen->removeChild(player->playerEntity);
						delete player->playerEntity;
						delete player;
					}
				}
			}	
			break;
			
			case ServerEvent::EVENT_CLIENT_CONNECTED:
			{
				Player *newPlayer = new Player();
				newPlayer->position.x = 640/2;
				newPlayer->position.y = 480/2;				
				newPlayer->client = serverEvent->client;												
				newPlayer->client->addEventListener(this, ServerClientEvent::EVENT_CLIENT_DATA);					
				ScreenEntity *playerEntity = new ScreenEntity();				
				playerEntity->setPositionMode(ScreenEntity::POSITION_CENTER);
				ScreenShape *playerBody = new ScreenShape(ScreenShape::SHAPE_CIRCLE, 30,30,3);				
				playerBody->setRotation(-90.0);
				playerEntity->addChild(playerBody);
				playerEntity->setPosition(640/2,480/2);
				gameScreen->addChild(playerEntity);
				newPlayer->playerEntity = playerEntity;												
				players.push_back(newPlayer);
				printf("Player connected\n");
				serverInfo.initialServerState = serverState;
				server->sendReliableDataToClient(newPlayer->client, (char*) &serverInfo, sizeof(ServerInfo), SERVER_INFO);
			}
			break;
		}
		
	}
}

bool HelloPolycodeApp::Update() {
	updateWorld(core->getElapsed());
	infoLabel->setText("Example server. ["+String::IntToString(players.size())+" Players]");
    return core->updateAndRender();
}
