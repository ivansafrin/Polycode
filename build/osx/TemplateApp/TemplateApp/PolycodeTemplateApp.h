//
// Polycode template. Write your code here.
//

#import "polycode/view/osx/PolycodeView.h"
#include "Polycode.h"

using namespace Polycode;

class PolycodeTemplateApp : public EventHandler {
public:
    PolycodeTemplateApp(PolycodeView *view);
    ~PolycodeTemplateApp();
    
    void handleEvent(Event *event);
    
    bool Update();
    
private:
    ScenePrimitive *test ;
    Core *core;
};