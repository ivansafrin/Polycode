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

#pragma once

#include "polycode/core/PolyCore.h"
#import "polycode/view/ios/PolycodeView.h"
#include "polycode/core/PolyInputEvent.h"
#include "polycode/core/PolyOpenGLGraphicsInterface.h"
#include "polycode/core/PolySoundManager.h"
#include <pthread.h>
#include <AudioToolbox/AudioQueue.h>
#include <CoreAudio/CoreAudioTypes.h>

/* CONFIG */

// number of CoreAudio AudioQueue buffers

#define NUM_AQ_BUFFERS 3

/* ------ */

@class PolycodeView;

using namespace Polycode;

#define POLYCODE_CORE IOSCore

class _PolyExport PosixMutex : public CoreMutex {
public:
    void lock();
    void unlock();
    pthread_mutex_t pMutex;
};

class IOSEvent {
    public:
    int eventGroup;
    int eventCode;
    
    int mouseX;
    int mouseY;
    
    std::vector<TouchInfo> touches;
    TouchInfo touch;
    
    PolyKEY keyCode;
    wchar_t unicodeChar;
    
    char mouseButton;
    
    static const int EVENTBASE_PLATFORMEVENT = 0x300;
    static const int INPUT_EVENT = EVENTBASE_PLATFORMEVENT+0;
    static const int FOCUS_EVENT = EVENTBASE_PLATFORMEVENT+1;
};

namespace Polycode {
    
    class IOSCoreAudioInterface : public Polycode::AudioInterface {
    public:
        IOSCoreAudioInterface();
        ~IOSCoreAudioInterface();
        
        static void CoreAudioCallback(void *custom_data, AudioQueueRef queue, AudioQueueBufferRef buffer);
    private:
        AudioQueueBufferRef buffers[NUM_AQ_BUFFERS];
        AudioStreamBasicDescription format;
        AudioQueueRef queue;
        
    };

	class _PolyExport IOSCore : public Core {
	public:

		IOSCore(PolycodeView *view, int xRes, int yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel, int frameRate, int monitorIndex = -1, bool retinaSupport = false);
		~IOSCore();

		void Render();
		bool systemUpdate();
		void setCursor(int cursorType);
		void createThread(Threaded *target);
		CoreMutex *createMutex();
		void copyStringToClipboard(const String& str);
		String getClipboardString();
		void createFolder(const String& folderPath);
		void copyDiskItem(const String& itemPath, const String& destItemPath);
		void moveDiskItem(const String& itemPath, const String& destItemPath);
		void removeDiskItem(const String& itemPath);
		String openFolderPicker();
		std::vector<String> openFilePicker(std::vector<CoreFileExtension> extensions, bool allowMultiple);
		String saveFilePicker(std::vector<CoreFileExtension> extensions);
		void handleVideoModeChange(VideoModeChangeInfo *modeInfo);
		
        void flushRenderContext();
        void prepareRenderContext();
        
		void openURL(String url);
		unsigned int getTicks();
		String executeExternalCommand(String command, String args, String inDirectory);
		bool systemParseFolder(const Polycode::String& pathString, bool showHidden, std::vector<OSFileEntry> &targetVector);
        
        String getResourcePathForFile(const String &fileName);

		void checkEvents();
		void setDeviceSize(Number x, Number y);
        
        void renderTest();

		Number getBackingXRes();
		Number getBackingYRes();
        
        void _setAcceleration(const Vector3 &acceleration);
        void _setGyroRotation(const Vector3 &rotation);
        
        std::vector<IOSEvent> iosEvents;
        
	private:
        
        CADisplayLink *displayLink;
        
        GLuint colorRenderbuffer;
        GLuint depthRenderbuffer;
        GLuint defaultFBOName;
        bool retinaSupport;
        
        EAGLContext *context;
        uint64_t initTime;
        PolycodeView *glView;

	};
}