#include <Polycode.h>
#include "PolycodeView.h"

using namespace Polycode;

class HelloPolycodeApp {
public:
    HelloPolycodeApp(PolycodeView *view);
    ~HelloPolycodeApp();
    
    bool Update();
    
private:

	ScreenShape *sun;
	ScreenShape *planet;
	ScreenShape *moon;	
	
	Number planetRotation;
	Number moonRotation;
			
    Core *core;
};
