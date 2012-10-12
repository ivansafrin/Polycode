#include <Polycode.h>
#include "PolycodeView.h"
#include "NetworkingExampleGlobals.h"

using namespace Polycode;

class Player {
	public:		
		Vector2 position;
		Number angle;
		ScreenEntity *playerEntity;
		ServerClient *client;
		char turning_state;
		char thrusting;
		Number moveSpeed;
		Number rotateSpeed;		
		
		ServerClientInfo getClientInfo() {
			ServerClientInfo info;
			info.clientID = client->clientID;
			info.state = 1;
			info.posX = position.x;
			info.posY = position.y;
			info.angle = angle;
			return info;
		}							
			
};	

class HelloPolycodeApp : public ServerWorld, EventHandler {
public:
    HelloPolycodeApp(PolycodeView *view);
    ~HelloPolycodeApp();
	
	void updateWorld(Number elapsed);
	void getWorldState(ServerClient *client, char **worldData,unsigned int *worldDataSize);				
	
    bool Update();
	
	void handleEvent(Event *event);
    
private:
	Core *core;
	Screen *gameScreen;
	ScreenLabel *infoLabel;
	Server *server;
	vector<Player*> players;
	ServerState serverState;
	
	ServerInfo serverInfo;
};
