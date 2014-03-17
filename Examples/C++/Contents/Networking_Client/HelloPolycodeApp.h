#include <Polycode.h>
#include "PolycodeView.h"
#include "NetworkingExampleGlobals.h"

using namespace Polycode;

class ClientPlayer {
	public:
		int clientID;
		char state;
		SceneEntity *playerEntity;
};

class HelloPolycodeApp : public EventHandler {
public:
    HelloPolycodeApp(PolycodeView *view);
    ~HelloPolycodeApp();
    bool Update();
	
	void createClientPlayer(int clientID);
	void handleEvent(Event *event);
    
private:
	Core *core;
	Scene *gameScene;
	Client *client;
	ClientData clientData;
	char state;
	
	SceneLabel *motdLabel;	
	
	vector<ClientPlayer*> players;
};
