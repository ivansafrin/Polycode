#include <Polycode.h>
#include "PolycodeView.h"

using namespace Polycode;

class HelloPolycodeApp : public EventHandler {
public:
    HelloPolycodeApp(PolycodeView *view);
    ~HelloPolycodeApp();
    bool Update();
    
private:
	Core *core;
};
