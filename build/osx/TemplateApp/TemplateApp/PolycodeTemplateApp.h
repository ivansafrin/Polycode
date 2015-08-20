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
    
    Sound *bgSound;
    
    Sound *sound1;
    Sound *sound2;
    Sound *sound3;
    
    Core *core;
};