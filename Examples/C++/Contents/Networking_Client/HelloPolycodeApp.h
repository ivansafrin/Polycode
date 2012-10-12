#include <Polycode.h>
#include "PolycodeView.h"
#include "NetworkingExampleGlobals.h"

using namespace Polycode;

class ClientPlayer {
	public:
		int clientID;
		char state;
		ScreenEntity *playerEntity;
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
	Screen *gameScreen;
	Client *client;
	ClientData clientData;
	char state;
	
	ScreenLabel *motdLabel;	
	
	vector<ClientPlayer*> players;
};
