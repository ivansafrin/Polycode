#include <Polycode.h>
#include "PolycodeView.h"
#include "Polycode3DPhysics.h"

using namespace Polycode;

class HelloPolycodeApp : public EventHandler {
public:
    HelloPolycodeApp(PolycodeView *view);
    ~HelloPolycodeApp();
    bool Update();
    void handleEvent(Event *e);
	
private:
	Core *core;
	PhysicsScene *scene;	
	PhysicsCharacter *playerController;
	ScenePrimitive *player;
	SceneLabel *onGroundLabel;	
	Number walkSpeed;
	Number rotateSpeed;
	Number playerDirection;
	
	ScenePrimitive *testBox;
};
