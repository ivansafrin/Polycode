#include <Polycode.h>
#include "PolycodeView.h"
#include "Polycode2DPhysics.h"

using namespace Polycode;

class HelloPolycodeApp : EventHandler {
public:
    HelloPolycodeApp(PolycodeView *view);
    ~HelloPolycodeApp();    
    bool Update();
	void handleEvent(Event *e);
	
private:
    Core *core;	
	PhysicsScene2D *scene;
	ScenePrimitive *checkShape;
};