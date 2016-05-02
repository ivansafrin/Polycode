/*
Copyright (C) 2015 by Ivan Safrin

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


#include "polycode/core/PolyIOSCore.h"

#include "polycode/core/PolyBasicFileProvider.h"
#include "polycode/core/PolyPhysFSFileProvider.h"
#include <mach/mach.h>
#include <mach/mach_time.h>

using namespace Polycode;

void PosixMutex::lock() {
    pthread_mutex_lock(&pMutex);
}

void PosixMutex::unlock() {
    pthread_mutex_unlock(&pMutex);
}

IOSCore::IOSCore(PolycodeView *view, int xRes, int yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel, int frameRate, int monitorIndex, bool retinaSupport)
	: Core(xRes, yRes, fullScreen, vSync, aaLevel, anisotropyLevel, frameRate, monitorIndex) {
        
        initTime = mach_absolute_time();
        
        eventMutex = createMutex();
        
        fileProviders.push_back(new BasicFileProvider());
        fileProviders.push_back(new PhysFSFileProvider());
        
        glView = view;
        [glView setCore:this];
        
        renderer = new Renderer();
                
        OpenGLGraphicsInterface *interface = new OpenGLGraphicsInterface();
        renderer->setGraphicsInterface(this, interface);
        services->setRenderer(renderer);
        
        CGRect screenBounds = [[UIScreen mainScreen] bounds];
        
        setVideoMode(screenBounds.size.width, screenBounds.size.height, fullScreen, vSync, aaLevel, anisotropyLevel, retinaSupport);

}

IOSCore::~IOSCore() {
    glDeleteFramebuffers(1, &defaultFBOName);
    glDeleteRenderbuffers(1, &colorRenderbuffer);
}

void IOSCore::Render() {
    renderer->beginFrame();
    services->Render(Polycode::Rectangle(0, 0, getBackingXRes(), getBackingYRes()));
    renderer->endFrame();
}

void IOSCore::checkEvents() {
    lockMutex(eventMutex);    
    for(int i=0; i < iosEvents.size(); i++) {
        IOSEvent event = iosEvents[i];
        switch(event.eventGroup) {
            case IOSEvent::INPUT_EVENT:
            {
                    case InputEvent::EVENT_TOUCHES_BEGAN:
                        input->touchesBegan(event.touch, event.touches, getTicks());
                        break;
                    case InputEvent::EVENT_TOUCHES_ENDED:
                        input->touchesEnded(event.touch, event.touches, getTicks());
                        break;
                    case InputEvent::EVENT_TOUCHES_MOVED:
                        input->touchesMoved(event.touch, event.touches, getTicks());
                        break;
            }
            break;
            case IOSEvent::FOCUS_EVENT:
            break;
        }
    }
    iosEvents.clear();
    unlockMutex(eventMutex);
}

bool IOSCore::systemUpdate() {
	if (!running) {
		return false;
	}
	doSleep();
	updateCore();

	checkEvents();
	return running;
}

void IOSCore::setCursor(int cursorType) {

}

void launchThread(Threaded *target) {
	target->runThread();
	target->scheduledForRemoval = true;
}

void *ManagedThreadFunc(void *data) {
    Threaded *target = static_cast<Threaded*>(data);
    target->runThread();
    target->scheduledForRemoval = true;
    return NULL;
}

void IOSCore::createThread(Threaded *target) {
    Core::createThread(target);
    pthread_t thread;
    pthread_create( &thread, NULL, ManagedThreadFunc, (void*)target);
}

CoreMutex *IOSCore::createMutex() {
    PosixMutex *mutex = new PosixMutex();
    pthread_mutex_init(&mutex->pMutex, NULL);
    return mutex;
}

void IOSCore::copyStringToClipboard(const String& str) {

}

String IOSCore::getClipboardString() {
	return "";
}

void IOSCore::createFolder(const String& folderPath) {

}

void IOSCore::copyDiskItem(const String& itemPath, const String& destItemPath) {

}

void IOSCore::moveDiskItem(const String& itemPath, const String& destItemPath) {

}

void IOSCore::removeDiskItem(const String& itemPath) {

}

String IOSCore::openFolderPicker() {
	return "";
}

std::vector<String> IOSCore::openFilePicker(std::vector<CoreFileExtension> extensions, bool allowMultiple) {
	std::vector<String> ret;
	return ret;
}

String IOSCore::saveFilePicker(std::vector<CoreFileExtension> extensions) {
	return "";
}

void IOSCore::_setAcceleration(const Vector3 &acceleration) {
    CoreMotionEvent *event = new CoreMotionEvent();
    event->amount = acceleration;
    dispatchEvent(event, Core::EVENT_ACCELEROMETER_MOTION);
}

void IOSCore::_setGyroRotation(const Vector3 &rotation) {
    CoreMotionEvent *event = new CoreMotionEvent();
    event->amount = rotation;
    dispatchEvent(event, Core::EVENT_GYRO_ROTATION);
}

void IOSCore::handleVideoModeChange(VideoModeChangeInfo *modeInfo) {
    
    // IOS_TODO: Implement CADisplayLink
    
    xRes = modeInfo->xRes;
    yRes = modeInfo->yRes;
    retinaSupport = modeInfo->retinaSupport;
    
    CAEAGLLayer *eaglLayer = (CAEAGLLayer *)glView.layer;
    eaglLayer.opaque = TRUE;
    eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                    [NSNumber numberWithBool:FALSE], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
    
    
    context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    
    if (!context || ![EAGLContext setCurrentContext:context]) {
        printf("ERROR CREATING GL CONTEXT\n");
        return;
    }

    CGFloat screenScale = 1.0;
    if(modeInfo->retinaSupport) {
        screenScale = [[UIScreen mainScreen] scale];
        renderer->setBackingResolutionScale(screenScale, screenScale);
    } else {
        renderer->setBackingResolutionScale(1.0, 1.0);
    }
    
    glGenFramebuffers(1, &defaultFBOName);
    
    glGenRenderbuffers(1, &colorRenderbuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, defaultFBOName);
    glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
    
    glView.layer.contentsScale = screenScale;
    [context renderbufferStorage:GL_RENDERBUFFER fromDrawable: (id<EAGLDrawable>) glView.layer];

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderbuffer);
    
    GLint backingWidth;
    GLint backingHeight;
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &backingWidth);
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &backingHeight);
    
    glGenRenderbuffers(1, &depthRenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, modeInfo->xRes * screenScale, modeInfo->yRes  * screenScale);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderbuffer);
    
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        printf("ERROR CREATING RENDERBUFFER\n");
    }
    
}

String IOSCore::getResourcePathForFile(const String &fileName) {
    NSString* fullFileName = [NSString stringWithUTF8String:fileName.c_str()];
    NSString* fileNameNoExt = [[fullFileName lastPathComponent] stringByDeletingPathExtension];
    NSString* extension = [fullFileName pathExtension];
    NSString *str = [[NSBundle mainBundle] pathForResource: fileNameNoExt ofType: extension];
    return String([str UTF8String]);
}

void IOSCore::prepareRenderContext() {
    while(![glView needsUpdate]) {} // wait for frame sync
    
    glBindFramebuffer(GL_FRAMEBUFFER, defaultFBOName);
}

void IOSCore::flushRenderContext() {
    glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
    [context presentRenderbuffer:GL_RENDERBUFFER];
}

void IOSCore::openURL(String url) {

}

unsigned int IOSCore::getTicks() {
    uint64_t time = mach_absolute_time();
    double conversion = 0.0;
    
    mach_timebase_info_data_t info;
    mach_timebase_info( &info );
    conversion = 1e-9 * (double) info.numer / (double) info.denom;
    
    return (((double)(time - initTime)) * conversion) * 1000.0f;
}

String IOSCore::executeExternalCommand(String command, String args, String inDirectory) {
	return "";
}


bool IOSCore::systemParseFolder(const Polycode::String& pathString, bool showHidden, std::vector<OSFileEntry> &targetVector) {

	return true; 
}


void Core::getScreenInfo(int *width, int *height, int *hz) {

}

void IOSCore::setDeviceSize(Number x, Number y) {

}

Number IOSCore::getBackingXRes() {
    if(!retinaSupport) {
        return getXRes();
    } else {
        return getXRes() * [[UIScreen mainScreen] scale];
    }
}

Number IOSCore::getBackingYRes() {
    if(!retinaSupport) {
        return getYRes();
    } else {
        return getYRes()  * [[UIScreen mainScreen] scale];
    }
}