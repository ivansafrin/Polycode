#include "PolycodeTemplateApp.h"
#include "polycode/view/android/PolycodeView.h"
//#include <android_native_app_glue.h>

void android_main(struct startHelper* helper){
	LOGI("Starting");
	PolycodeView *view = new PolycodeView(helper->activity, "TemplateApp");

	PolycodeTemplateApp *app = new PolycodeTemplateApp(view);

	pthread_mutex_lock(&helper->mutex);
    helper->running = 1;
    pthread_cond_broadcast(&helper->cond);
    pthread_mutex_unlock(&helper->mutex);

	while(app->Update()) {
	}
	return;
}
