#include <Polycode.h>
#include "PolycodeView.h"

using namespace Polycode;

class HelloPolycodeApp {
public:
    HelloPolycodeApp(PolycodeView *view);
    ~HelloPolycodeApp();
    
    bool Update();
    
private:

	ScenePrimitive *sun;
	ScenePrimitive *planet;
	ScenePrimitive *moon;	
	
	Number planetRoll;
	Number moonRoll;
			
    Core *core;
};
