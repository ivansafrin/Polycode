#include "Polycode.h"
#include "PolycodeView.h"
#include "PolycodeIDEApp.h"

int main(int argc, char *argv[]) {
	PolycodeView *view = new PolycodeView("Polycode", true);
	PolycodeIDEApp *app = new PolycodeIDEApp(view);
	while(app->Update()) {}
	app->saveConfigFile();
	return 0;
}
