#include <Polycode.h>
#include "PolycodeView.h"
#include "Polycode3DPhysics.h"

using namespace Polycode;

class HelloPolycodeApp : public EventHandler {
public:
    HelloPolycodeApp(PolycodeView *view);
    ~HelloPolycodeApp();
    bool Update();
	
	void handleEvent(Event *event);
    
private:
	Core *core;
	ScenePrimitive *box;
	ScenePrimitive *bigBox;
	CollisionScene *scene;
	SceneEntity *lastEntity;
};
