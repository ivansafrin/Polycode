//
// Polycode template. Write your code here.
//

#import "PolycodeView.h"
#include "Polycode.h"

using namespace Polycode;

class PolycodeTemplateApp {
public:
    PolycodeTemplateApp(PolycodeView *view);
    ~PolycodeTemplateApp();
    
    bool Update();
    
private:
    Core *core;
};