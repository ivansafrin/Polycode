//
// Polycode template. Write your code here.
//

#include "Polycode.h"

using namespace Polycode;

class PolycodeTemplateApp {
public:
    PolycodeTemplateApp(PolycodeView *view);
    ~PolycodeTemplateApp();
    
	Core *getCore();
    bool Update();
    
private:

	SceneLabel *label;
	Scene *scene;
    Core *core;
};