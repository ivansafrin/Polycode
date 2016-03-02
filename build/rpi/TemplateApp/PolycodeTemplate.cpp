#include "PolycodeTemplateApp.h"


int main(int argc, char **argv) {
	PolycodeView *view = new PolycodeView();
	PolycodeTemplateApp *app = new PolycodeTemplateApp(view);
	while(app->Update()) {
	}
	return 0;
}
