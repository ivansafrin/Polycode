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

#include "polycode/view/android/PolycodeView.h"
#include "polycode/core/PolyLogger.h"
#include "polycode/core/PolyRenderer.h"
#include <android/looper.h>

using namespace Polycode;

AndroidCore* core = NULL;
extern void android_main(struct startHelper* helper);

PolycodeView::PolycodeView(ANativeActivity* native, String title){
	windowTitle = title;
	
	native_activity = native;
	native_window = NULL;
	native_input = NULL;
	
// 	pthread_mutex_init(windowMutex, NULL);
//     pthread_cond_init(windowCond, NULL);
	
	native_activity->instance = this;
	native_activity->callbacks->onStart 				= onStart;
	native_activity->callbacks->onStop 					= onStop;
	native_activity->callbacks->onDestroy				= onDestroy;
	native_activity->callbacks->onNativeWindowCreated 	= onNativeWindowCreated;
	native_activity->callbacks->onNativeWindowDestroyed = onNativeWindowDestroyed;
	native_activity->callbacks->onResume 				= onResume;
	native_activity->callbacks->onPause 				= onPause;
	native_activity->callbacks->onWindowFocusChanged 	= onWindowFocusChanged;
	native_activity->callbacks->onInputQueueCreated		= onInputQueueCreated;
	native_activity->callbacks->onInputQueueDestroyed	= onInputQueueDestroyed;
	
	native_config = AConfiguration_new();
	AConfiguration_fromAssetManager(native_config, native_activity->assetManager);
// 	AConfiguration* myConfig = AConfiguration_new();
// 	AConfiguration_copy(myConfig, native_config);
// 	AConfiguration_setNavHidden(myConfig,ACONFIGURATION_NAVHIDDEN_YES);
// 	AConfiguration_setKeysHidden(native_config, ACONFIGURATION_KEYSHIDDEN_YES);
	
	sensorManager = ASensorManager_getInstance();		
	
	const ASensor* accelerometer = ASensorManager_getDefaultSensor(sensorManager, ASENSOR_TYPE_ACCELEROMETER);
	const ASensor* gyroscope = ASensorManager_getDefaultSensor(sensorManager, ASENSOR_TYPE_GYROSCOPE);
	const ASensor* orientation = ASensorManager_getDefaultSensor(sensorManager, ASENSOR_TYPE_GAME_ROTATION_VECTOR);
	
	ALooper* looper = ALooper_forThread();
    if(looper == NULL){
		looper = ALooper_prepare(0);
	}
	
	sensorQueue = ASensorManager_createEventQueue(sensorManager, looper, ALOOPER_POLL_CALLBACK, sensorLoop, this);
	
	if(accelerometer){
// 		Logger::log("Accelerometer found. Name: %s, Vendor: %s", ASensor_getName(accelerometer), ASensor_getVendor(accelerometer));
		ASensorEventQueue_enableSensor(sensorQueue, accelerometer);
	}
	
	if(gyroscope){
// 		Logger::log("Gyroscope found. Name: %s, Vendor: %s", ASensor_getName(gyroscope), ASensor_getVendor(gyroscope));
		ASensorEventQueue_enableSensor(sensorQueue, gyroscope);
	}
	
	if(orientation){
// 		Logger::log("Orientation found. Name: %s, Vendor: %s", ASensor_getName(orientation), ASensor_getVendor(orientation));
 		ASensorEventQueue_enableSensor(sensorQueue, orientation);
	}
	gyroTimestamp = 0;
	
}

PolycodeView::~PolycodeView(){}

bool PolycodeView::isInteractable(){
	//Logger::log("isInteractable: %s", ((lifecycleFlags & APP_STATUS_INTERACTABLE) == APP_STATUS_INTERACTABLE) ? "true" : "false");
	return ((lifecycleFlags & APP_STATUS_INTERACTABLE) == APP_STATUS_INTERACTABLE);
}

void onStart(ANativeActivity* activity){
	Logger::log("onStart");
}

void onResume(ANativeActivity* activity){
	Logger::log("onResume");
	if(core)
		core->paused = false;
	((PolycodeView*)activity->instance)->lifecycleFlags |= APP_STATUS_ACTIVE;
}

void onPause(ANativeActivity* activity){
	Logger::log("onPause");
	((PolycodeView*)activity->instance)->lifecycleFlags &= ~APP_STATUS_ACTIVE;
}

void* onSaveInstanceState(ANativeActivity* activity, size_t *outSize){
	Logger::log("onSaveInstanceState");
}

void onStop(ANativeActivity* activity){
	Logger::log("onStop");
}

void onDestroy(ANativeActivity* activity){
	Logger::log("onDestroy");
	if(core)
		core->Shutdown();
}

void onWindowFocusChanged(ANativeActivity* activity, int hasFocus){
	Logger::log("onWindowFocusChanged");
	if(hasFocus){
		AndroidEvent event = AndroidEvent();
		event.eventGroup = AndroidEvent::SYSTEM_FOCUS_EVENT;
		event.eventCode = Core::EVENT_GAINED_FOCUS;
		if(core)
			core->handleSystemEvent(event);
		((PolycodeView*)activity->instance)->lifecycleFlags|=APP_STATUS_FOCUSED;
	}else{
		AndroidEvent event = AndroidEvent();
		event.eventGroup = AndroidEvent::SYSTEM_FOCUS_EVENT;
		event.eventCode = Core::EVENT_LOST_FOCUS;
		if(core)
			core->handleSystemEvent(event);		
		((PolycodeView*)activity->instance)->lifecycleFlags&=~APP_STATUS_FOCUSED;
	}
}

void onNativeWindowCreated(ANativeActivity* activity, ANativeWindow *window){
	Logger::log("onNativeWindowCreated");
	((PolycodeView*)activity->instance)->native_window = window;
	int width = ANativeWindow_getWidth(window);
	int height = ANativeWindow_getHeight(window);
	if (width > 0 && height > 0){
		((PolycodeView*)activity->instance)->lifecycleFlags|=APP_STATUS_HAS_REAL_SURFACE;
		if(core){
			core->recreateContext = true;
			core->setDeviceSize(width, height);
			core->setVideoMode(core->getXRes(), core->getYRes(), true, false, core->getAALevel(), 0, true);
		}
	}
}

void onNativeWindowResized(ANativeActivity* activity, ANativeWindow *window){
	Logger::log("onNativeWindowResized");
}

void onNativeWindowRedrawNeeded(ANativeActivity* activity, ANativeWindow *window){
	Logger::log("onNativeWindowRedrawNeeded");
}

void onNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow *window){
	Logger::log("onNativeWindowDestroyed");
	((PolycodeView*)activity->instance)->native_window = NULL;
	if (core){
		core->recreateContext = true;
	}
	((PolycodeView*)activity->instance)->lifecycleFlags&=~APP_STATUS_HAS_REAL_SURFACE;
}

void onInputQueueCreated(ANativeActivity* activity, AInputQueue *queue){
	Logger::log("onInputQueueCreated");
	if (((PolycodeView*)activity->instance)->native_input != NULL) {
		AInputQueue_detachLooper(((PolycodeView*)activity->instance)->native_input);
	}
	((PolycodeView*)activity->instance)->native_input = queue;
	ALooper *loop = ALooper_prepare(0);
	AInputQueue_attachLooper(((PolycodeView*)activity->instance)->native_input, loop, ALOOPER_EVENT_INPUT, inputLoop, activity->instance);
}

void onInputQueueDestroyed(ANativeActivity* activity, AInputQueue *queue){
	Logger::log("onInputQueueDestroyed");
	AInputQueue_detachLooper(((PolycodeView*)activity->instance)->native_input);
	((PolycodeView*)activity->instance)->native_input = NULL;
}

void onContentRectChanged(ANativeActivity* activity, const ARect *rect){
	Logger::log("onContentRectChanged");
}

void onConfiguartionChanged(ANativeActivity* activity){
	Logger::log("onConfiguartionChanged");
// 	activity->assetManager
}

void onLowMemory(ANativeActivity* activity){
	Logger::log("onLowMemory");
}

static int inputLoop(int fd, int events, void* data){
	Logger::log("inputLoop");
	AInputQueue* native_input = ((PolycodeView*)data)->native_input;
	AndroidEvent event;
	AInputEvent* aev;
	int type;
	int action;
	
	while(AInputQueue_hasEvents(native_input)>0){
		if(AInputQueue_getEvent(native_input, &aev)>=0){
			event = AndroidEvent();
			event.eventGroup = AndroidEvent::INPUT_EVENT;
			type = AInputEvent_getType(aev);
			if(type == AINPUT_EVENT_TYPE_KEY){
				event.eventTime = AKeyEvent_getEventTime(aev);
				int kC = AKeyEvent_getKeyCode(aev);
				if(core)
					event.keyCode = core->mapKey(kC);
				
				action = AKeyEvent_getAction(aev);
				if(action == AKEY_EVENT_ACTION_DOWN){
					event.eventCode = InputEvent::EVENT_KEYDOWN;
					event.unicodeChar = GetUnicodeChar(((PolycodeView*)data)->native_activity, AKEY_EVENT_ACTION_DOWN, kC, AKeyEvent_getMetaState(aev));
				} else if (action == AKEY_EVENT_ACTION_UP){
					event.eventCode = InputEvent::EVENT_KEYUP;
					event.unicodeChar = GetUnicodeChar(((PolycodeView*)data)->native_activity, AKEY_EVENT_ACTION_UP, kC, AKeyEvent_getMetaState(aev));
				}

			} else if(type == AINPUT_EVENT_TYPE_MOTION){
				event.eventTime = AMotionEvent_getEventTime(aev);
				int evSource = AInputEvent_getSource(aev);
				
				if (evSource & AINPUT_SOURCE_CLASS_POINTER){
					action = AMotionEvent_getAction(aev);
					int count = AMotionEvent_getPointerCount(aev);
					
					if (action == AMOTION_EVENT_ACTION_MOVE){
						AndroidEvent hEvent;
						int history = AMotionEvent_getHistorySize(aev);
						
						for (int j = 0; j<history; j++){
							hEvent = AndroidEvent();
							hEvent.eventTime = AMotionEvent_getHistoricalEventTime(aev, j);
							hEvent.eventGroup = AndroidEvent::INPUT_EVENT;
							
							std::vector<TouchInfo> touches;
							
							for (int i = 0; i <count; i++){
								TouchInfo ti;
								ti.position = Vector2(AMotionEvent_getHistoricalX(aev,i,j)/Services()->getRenderer()->getBackingResolutionScaleX(), AMotionEvent_getHistoricalY(aev,i,j)/Services()->getRenderer()->getBackingResolutionScaleY());
								if(evSource & AINPUT_SOURCE_TOUCHSCREEN){
									ti.type = TouchInfo::TYPE_TOUCH;
								} else {
									ti.type = TouchInfo::TYPE_PEN;
								}
								ti.id = AMotionEvent_getPointerId(aev, i);
								if(ti.id == (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) || AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT){
									hEvent.touch = ti;
								}
								touches.push_back(ti);
							}
							hEvent.eventCode = InputEvent::EVENT_TOUCHES_MOVED;
							hEvent.touches = touches;
							
							core->handleSystemEvent(hEvent);
						}
					} else {
						std::vector<TouchInfo> touches;
						for (int i = 0; i <count; i++){
							TouchInfo ti;
							//TODO: slight offset since retina implementation
							ti.position = Vector2(AMotionEvent_getX(aev,i)/(core->getBackingXRes()/core->getXRes()), AMotionEvent_getY(aev,i)/(core->getBackingYRes()/core->getYRes()));
							if(evSource & AINPUT_SOURCE_TOUCHSCREEN){
								ti.type = TouchInfo::TYPE_TOUCH;
							} else {
								ti.type = TouchInfo::TYPE_PEN;
							}
							ti.id = AMotionEvent_getPointerId(aev, i);
							if(ti.id == (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) || AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT){
								event.touch = ti;
							}
							touches.push_back(ti);
						}
						
						if (action == AMOTION_EVENT_ACTION_UP){
							event.eventCode = InputEvent::EVENT_TOUCHES_ENDED;
							event.touch = touches[0];
						} else if (action == AMOTION_EVENT_ACTION_DOWN){
							event.eventCode = InputEvent::EVENT_TOUCHES_BEGAN;
							event.touch = touches[0];
						} else if (action == AMOTION_EVENT_ACTION_POINTER_DOWN){
							event.eventCode = InputEvent::EVENT_TOUCHES_BEGAN;
						} else if (action == AMOTION_EVENT_ACTION_POINTER_UP){
							event.eventCode = InputEvent::EVENT_TOUCHES_ENDED;
						}
						core->handleSystemEvent(event);
					}
				} else if (evSource & AINPUT_SOURCE_CLASS_POSITION){
					
				}
			}
			AInputQueue_finishEvent(native_input, aev, 1);
		}
	}
	return 1;
}

static int sensorLoop(int fd, int events, void* data){
// 	Logger::log("sensorLoop");
	ASensorEventQueue* queue = ((PolycodeView*)data)->sensorQueue;
	
	ASensorEvent event;
	while(ASensorEventQueue_getEvents(queue, &event, 1) > 0){
// 		Logger::log("event.type: %d", event.type);
		float dT;
		switch(event.type){
			case ASENSOR_TYPE_ACCELEROMETER:
 				core->_setAcceleration(Vector3(event.acceleration.x,event.acceleration.y,event.acceleration.z));
				//Logger::log("event.type: %d", event.type);
				break;
			case ASENSOR_TYPE_GYROSCOPE:
				if(((PolycodeView*)data)->gyroTimestamp!=0){
					dT = (event.timestamp-((PolycodeView*)data)->gyroTimestamp)/1000000000.0f;
					core->_setGyroRotation(Vector3(event.vector.x*dT*TODEGREES, event.vector.y*dT*TODEGREES, event.vector.z*dT*TODEGREES));
					//core->_setGyroRotation(Vector3(TODEGREES*(event.uncalibrated_gyro.x_uncalib - event.uncalibrated_gyro.x_bias), TODEGREES*(event.uncalibrated_gyro.y_uncalib - event.uncalibrated_gyro.y_bias), TODEGREES*(event.uncalibrated_gyro.z_uncalib - event.uncalibrated_gyro.z_bias)));
					//Logger::log("event.type: %d", event.type);
				}
				((PolycodeView*)data)->gyroTimestamp = event.timestamp;
				break;
			case ASENSOR_TYPE_GAME_ROTATION_VECTOR:
				
//  				Logger::log("event: %f, %f, %f, %f", event.data[3],event.data[0],event.data[1],event.data[2]);
				//q.fromAngleAxis(acos(event.data[3])*2, Vector3(event.data[0], event.data[1], event.data[2]));
				Quaternion q=Quaternion(event.data[3],event.data[0],event.data[1],event.data[2]);
				Vector3 vec = q.toEulerAngles();
// 				Logger::log("event: %f, %f, %f", vec.x, vec.y, vec.z);
//  				core->deviceAttitude = q;
				break;
		}
	}
	
	return 1;
}

void ANativeActivity_onCreate(ANativeActivity* activity, void *savedState, size_t savedStateSize) {
	Logger::log("onCreate");
	
	struct startHelper* helper = new struct startHelper;
	helper->activity = activity;
	helper->running = 0;
	pthread_mutex_init(&helper->mutex, NULL);
    pthread_cond_init(&helper->cond, NULL);
	
	pthread_attr_t attr; 
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&helper->thread, &attr, startApp, helper);

    // Wait for thread to start.
    pthread_mutex_lock(&helper->mutex);
    while (!helper->running) {
        pthread_cond_wait(&helper->cond, &helper->mutex);
    }
    pthread_mutex_unlock(&helper->mutex);
}

void* startApp(void* data){
	Logger::log("startApp");
	startHelper* helper = (startHelper*)data;
	
// 	pthread_mutex_lock(&helper->mutex);
//     helper->running = 1;
//     pthread_cond_broadcast(&helper->cond);
//     pthread_mutex_unlock(&helper->mutex);
	
	android_main(helper);
	Logger::log("startApp4");
    pthread_mutex_lock(&helper->mutex);
    if (((PolycodeView*)helper->activity->instance)->native_input != NULL) {
        AInputQueue_detachLooper(((PolycodeView*)helper->activity->instance)->native_input);
    }
    
    pthread_cond_broadcast(&helper->cond);
    pthread_mutex_unlock(&helper->mutex);
	delete helper;
}

//From http://stackoverflow.com/questions/21124051/receive-complete-android-unicode-input-in-c-c
int GetUnicodeChar(ANativeActivity* native_activity, int eventType, int keyCode, int metaState){
	JavaVM* javaVM = native_activity->vm;
	JNIEnv* jniEnv = native_activity->env;

	JavaVMAttachArgs attachArgs;
	attachArgs.version = JNI_VERSION_1_6;
	attachArgs.name = "NativeThread";
	attachArgs.group = NULL;
	
	jint result = javaVM->AttachCurrentThread(&jniEnv, &attachArgs);
	if(result == JNI_ERR){
		return 0;
	}
	
	jclass class_key_event = jniEnv->FindClass("android/view/KeyEvent");
	int unicodeKey;

	if(metaState == 0){
		jmethodID method_get_unicode_char = jniEnv->GetMethodID(class_key_event, "getUnicodeChar", "()I");
		jmethodID eventConstructor = jniEnv->GetMethodID(class_key_event, "<init>", "(II)V");
		jobject eventObj = jniEnv->NewObject(class_key_event, eventConstructor, eventType, keyCode);

		unicodeKey = jniEnv->CallIntMethod(eventObj, method_get_unicode_char);
	}else{
		jmethodID method_get_unicode_char = jniEnv->GetMethodID(class_key_event, "getUnicodeChar", "(I)I");
		jmethodID eventConstructor = jniEnv->GetMethodID(class_key_event, "<init>", "(II)V");
		jobject eventObj = jniEnv->NewObject(class_key_event, eventConstructor, eventType, keyCode);

		unicodeKey = jniEnv->CallIntMethod(eventObj, method_get_unicode_char, metaState);
	}
// 	javaVM->DetachCurrentThread();

	return unicodeKey;
}