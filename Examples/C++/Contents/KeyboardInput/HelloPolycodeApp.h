#include <Polycode.h>
#include "PolycodeView.h"

using namespace Polycode;

class HelloPolycodeApp : public EventHandler {
public:
    HelloPolycodeApp(PolycodeView *view);
    ~HelloPolycodeApp();
    
	void handleEvent(Event *e);
    bool Update();
    
private:
	
	Number rotationSpeed;
	SceneImage *image;
    Core *core;
};
