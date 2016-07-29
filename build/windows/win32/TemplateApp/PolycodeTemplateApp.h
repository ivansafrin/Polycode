//
// Polycode template. Write your code here.
//

#include "polycode/view/win32/PolycodeView.h"
#include "Polycode.h"

using namespace Polycode;

class PolycodeTemplateApp : public EventHandler {
public:
	PolycodeTemplateApp(PolycodeView *view);
	~PolycodeTemplateApp();

	void handleEvent(Event *event);
	bool Update();

private:
	Core *core;
	Scene *scene;
	SceneLabel *label;

};