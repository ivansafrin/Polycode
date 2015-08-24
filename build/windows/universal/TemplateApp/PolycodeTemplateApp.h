//
// Polycode template. Write your code here.
//

#include "Polycode.h"

using namespace Polycode;

class PolycodeTemplateApp {
public:
    PolycodeTemplateApp(PolycodeView *view);
    ~PolycodeTemplateApp();
    
    bool Update();
    
private:

	Sound *sound1;
	Sound *sound2;

    Core *core;
};