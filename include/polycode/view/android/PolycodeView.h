/*
 Copyright (C) 2016 by Joachim Meyer
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#pragma once

#include "polycode/core/PolyAndroidCore.h"
#include <android/native_activity.h>
#include <android/log.h>

#define LOGI(text) ((void)__android_log_write(ANDROID_LOG_INFO, "TemplateApp", text))
#define LOGE(text) ((void)__android_log_write(ANDROID_LOG_ERROR, "TemplateApp", text))

namespace Polycode {
	
    class PolycodeView : public PolycodeViewBase {
        public:
			PolycodeView(ANativeActivity* native, String title);
			~PolycodeView();

			String windowTitle;
			
			ANativeActivity* native_activity;
			ANativeWindow* native_window;
			AInputQueue* native_input;
			
// 			pthread_mutex_t* windowMutex;
// 			pthread_cond_t* windowCond;
    };
}

struct startHelper{
	pthread_t thread;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	ANativeActivity* activity;
	int running;
};

void onStart(ANativeActivity* activity);
void onResume(ANativeActivity* activity);
void onPause(ANativeActivity* activity);
void* onSaveInstanceState(ANativeActivity* activity, size_t *outSize);
void onStop(ANativeActivity* activity);
void onDestroy(ANativeActivity* activity);
void onWindowFocusChanged(ANativeActivity* activity, int hasFocus);
void onNativeWindowCreated(ANativeActivity* activity, ANativeWindow *window);
void onNativeWindowResized(ANativeActivity* activity, ANativeWindow *window);
void onNativeWindowRedrawNeeded(ANativeActivity* activity, ANativeWindow *window);
void onNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow *window);
void onInputQueueCreated(ANativeActivity* activity, AInputQueue *queue);
void onInputQueueDestroyed(ANativeActivity* activity, AInputQueue *queue);
void onContentRectChanged(ANativeActivity* activity, const ARect *rect);
void onConfiguartionChanged(ANativeActivity* activity);
void onLowMemory(ANativeActivity* activity);
int inputLoop(int fd, int events, void* data);
void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize);
void* startApp(void* data);