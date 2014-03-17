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
	PhysicsVehicle *vehicleController;
	ScenePrimitive *testBox;
	ScenePrimitive *vehicle;	
	SceneLabel *onGroundLabel;	
	Number steeringValue;
	Number engineForce;
	bool breaking;
};
