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
}

PolycodeView::~PolycodeView(){
	
}

void onStart(ANativeActivity* activity){
	Logger::log("onStart");
	if(core)
	core->paused = false;
}

void onResume(ANativeActivity* activity){
	Logger::log("onResume");
	if(core)
	core->paused = false;
}

void onPause(ANativeActivity* activity){
	Logger::log("onPause");
	if(core)
	core->paused = true;
}

void* onSaveInstanceState(ANativeActivity* activity, size_t *outSize){
	
}

void onStop(ANativeActivity* activity){
	Logger::log("onStop");
	if(core)
	core->paused = true;
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
	}else{
		AndroidEvent event = AndroidEvent();
		event.eventGroup = AndroidEvent::SYSTEM_FOCUS_EVENT;
		event.eventCode = Core::EVENT_LOST_FOCUS;
		if(core)
			core->handleSystemEvent(event);		
	}
}

void onNativeWindowCreated(ANativeActivity* activity, ANativeWindow *window){
	Logger::log("onNativeWindowCreated");
	((PolycodeView*)activity->instance)->native_window = window;
	int width = ANativeWindow_getWidth(window);
	int height = ANativeWindow_getHeight(window);
	if (width < 0)
		width = 100;
	if (height < 0)
		height = 100;
	if(core){
		core->recreateContext = true;
 		core->setDeviceSize(width, height);
		//Logger::log("Width: %d, Height; %d", width, height);
		core->getEGLMutex()->unlock();
		core->setVideoMode(width, height, true, false, core->getAALevel(), 0, false);
	}
}

void onNativeWindowResized(ANativeActivity* activity, ANativeWindow *window){
	
}

void onNativeWindowRedrawNeeded(ANativeActivity* activity, ANativeWindow *window){
	
}

void onNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow *window){
	Logger::log("onNativeWindowDestroyed");
	((PolycodeView*)activity->instance)->native_window = NULL;
	if (core){
		core->getEGLMutex()->lock();
		core->recreateContext = true;
		Services()->getRenderer()->getRenderThread()->getFrameInfo();
	}
}

void onInputQueueCreated(ANativeActivity* activity, AInputQueue *queue){
	Logger::log("onInputQueueCreated");
	((PolycodeView*)activity->instance)->native_input = queue;
	ALooper *loop = ALooper_prepare(0);
	AInputQueue_attachLooper(((PolycodeView*)activity->instance)->native_input, loop, ALOOPER_EVENT_INPUT, inputLoop, ((PolycodeView*)activity->instance)->native_input);
}

void onInputQueueDestroyed(ANativeActivity* activity, AInputQueue *queue){
	Logger::log("onInputQueueDestroyed");
	((PolycodeView*)activity->instance)->native_input = NULL;
	AInputQueue_detachLooper(((PolycodeView*)activity->instance)->native_input);
}

void onContentRectChanged(ANativeActivity* activity, const ARect *rect){
	
}

void onConfiguartionChanged(ANativeActivity* activity){
	
}

void onLowMemory(ANativeActivity* activity){
	
}

int inputLoop(int fd, int events, void* data){
	Logger::log("inputLoop");
	AInputQueue* native_input = (AInputQueue*)data;
	AndroidEvent event;
	AInputEvent* aev;
	int type;
	int action;
	
	while(AInputQueue_hasEvents(native_input)>0){
		if(AInputQueue_getEvent(native_input, &aev)>=0){
			event = AndroidEvent();
			event.eventTime = AKeyEvent_getEventTime(aev);
			event.eventGroup = AndroidEvent::INPUT_EVENT;
			type = AInputEvent_getType(aev);
			if(type == AINPUT_EVENT_TYPE_KEY){
				action = AKeyEvent_getAction(aev);
				if(action == AKEY_EVENT_ACTION_DOWN){
					event.eventCode = InputEvent::EVENT_KEYDOWN;
				} else if (action == AKEY_EVENT_ACTION_UP){
					event.eventCode = InputEvent::EVENT_KEYUP;
				}
				
			} else if(type == AINPUT_EVENT_TYPE_MOTION){
				int evSource = AInputEvent_getSource(aev);
				if (evSource & AINPUT_SOURCE_CLASS_POINTER){
					std::vector<TouchInfo> touches;
					int count = AMotionEvent_getPointerCount(aev);
					for (int i = 0; i <count; i++){
						TouchInfo ti;
						ti.position = Vector2(AMotionEvent_getX(aev,i), AMotionEvent_getY(aev,i));
						if(evSource & AINPUT_SOURCE_TOUCHSCREEN){
							ti.type = TouchInfo::TYPE_TOUCH;
						} else {
							ti.type = TouchInfo::TYPE_PEN;
						}
						ti.id = AMotionEvent_getPointerId(aev, i);
						
						touches.push_back(ti);
					}
					event.touches = touches;
					
					action = AMotionEvent_getAction(aev);
					if (action == AMOTION_EVENT_ACTION_UP){
						event.eventCode = InputEvent::EVENT_TOUCHES_ENDED;
						event.touch = touches[0];
						core->handleSystemEvent(event);
					} else if (action == AMOTION_EVENT_ACTION_DOWN){
						event.eventCode = InputEvent::EVENT_TOUCHES_BEGAN;
						event.touch = touches[0];
						core->handleSystemEvent(event);
					} else if (action == AMOTION_EVENT_ACTION_MOVE){
						event.eventCode = InputEvent::EVENT_TOUCHES_MOVED;
						event.touch = touches[action | AMOTION_EVENT_ACTION_POINTER_INDEX_MASK];
						core->handleSystemEvent(event);
					} else if (action == AMOTION_EVENT_ACTION_POINTER_DOWN){
						event.eventCode = InputEvent::EVENT_TOUCHES_BEGAN;
						event.touch = touches[action | AMOTION_EVENT_ACTION_POINTER_INDEX_MASK];
						core->handleSystemEvent(event);
					} else if (action == AMOTION_EVENT_ACTION_POINTER_UP){
						event.eventCode = InputEvent::EVENT_TOUCHES_ENDED;
						event.touch = touches[action | AMOTION_EVENT_ACTION_POINTER_INDEX_MASK];
						core->handleSystemEvent(event);
					}
					
				} else if (evSource & AINPUT_SOURCE_CLASS_POSITION){
					
				}
			}
		}
	}
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