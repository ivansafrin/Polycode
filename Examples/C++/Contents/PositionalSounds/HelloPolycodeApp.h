#include <Polycode.h>
#include "PolycodeView.h"

using namespace Polycode;

class HelloPolycodeApp {
public:
    HelloPolycodeApp(PolycodeView *view);
    ~HelloPolycodeApp();    
    bool Update();
    
private:
	Number positionValue;
	Core *core;	
	SceneEntity *sourceEntity;	
};

