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
#include <android/sensor.h>
#include <android/log.h>
#include <android/configuration.h>

//Sensor types the NDK supports but are not in the enum of sensor types
#define ASENSOR_TYPE_ORIENTATION 3
#define ASENSOR_TYPE_GRAVITY 9
#define ASENSOR_TYPE_LINEAR_ACCELERATION 10
#define ASENSOR_TYPE_ROTATION_VECTOR 11
#define ASENSOR_TYPE_MAGNETIC_FIELD_UNCALIBRATED 14
#define ASENSOR_TYPE_GAME_ROTATION_VECTOR 15
#define ASENSOR_TYPE_GYROSCOPE_UNCALIBRATED 16
#define ASENSOR_TYPE_SIGNIFICANT_MOTION 17
#define ASESNOR_TYPE_STEP_DETECTOR 18
#define ASESNOR_TYPE_STEP_COUNTER 19
#define ASENSOR_TYPE_GEOMAGNETIC_ROTATION_VECTOR 20

#define LOGI(text) ((void)__android_log_write(ANDROID_LOG_INFO, "TemplateApp", text))
#define LOGE(text) ((void)__android_log_write(ANDROID_LOG_ERROR, "TemplateApp", text))

namespace Polycode {
	
	enum{
		// Android lifecycle status flags.  Not app-specific
		// Set between onResume and onPause
		APP_STATUS_ACTIVE           = 0x00000001,
		// Set between onWindowFocusChanged(true) and (false)
		APP_STATUS_FOCUSED          = 0x00000002,
		// Set when the app's SurfaceHolder points to a 
		// valid, nonzero-sized surface
		APP_STATUS_HAS_REAL_SURFACE  = 0x00000004,
		// Mask of all app lifecycle status flags
		APP_STATUS_INTERACTABLE     = 0x00000007
	};
	
    class PolycodeView : public PolycodeViewBase {
        public:
			PolycodeView(ANativeActivity* native, String title);
			~PolycodeView();

			String windowTitle;
			
			ANativeActivity* native_activity;
			ANativeWindow* native_window;
			AInputQueue* native_input;
			AConfiguration* native_config;
			
			ASensorManager* sensorManager;
			ASensorEventQueue* sensorQueue;
			int64_t gyroTimestamp;
			
			jobject WakeLock;
			
			unsigned int lifecycleFlags;
			bool isInteractable();
			bool firstWindowCreate;
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
static int inputLoop(int fd, int events, void* data);
static int sensorLoop(int fd, int events, void* data);
void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize);
void* startApp(void* data);

int JNIGetUnicodeChar(ANativeActivity* native_activity, int eventType, int keyCode, int metaState);
void JNIAutoHideNavBar(ANativeActivity* native_activity);
void GetAudioInfo(ANativeActivity* native_activity);
void JNIWakeLock(ANativeActivity* native_activity, bool acquire);
