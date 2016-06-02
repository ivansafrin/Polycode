#include "PolycodeTemplateApp.h"
#include "polycode/view/linux/PolycodeView.h"
#include <emscripten.h>a

PolycodeTemplateApp *app;

void render()
{
	app->Update();
}

int main(int argc, char **argv) {
	PolycodeView *view = new PolycodeView("Polycode Template");
	app = new PolycodeTemplateApp(view);
	emscripten_set_main_loop(render,60,true);
	return 0;
}
