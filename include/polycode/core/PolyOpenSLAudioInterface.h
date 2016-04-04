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

#include "polycode/core/PolyGlobals.h"
#include "polycode/core/PolySoundManager.h"
#include "polycode/core/PolyThreaded.h"

// #if PLATFORM == PLATFORM_ANDROID
#include <SLES/OpenSLES_Android.h>
// #else
// #include <SLES/OpenSLES.h>
// #endif

namespace Polycode {
	
	class OpenSLStream : public Threaded {
	public:
		OpenSLStream();
		virtual ~OpenSLStream();
		
		void runThread();
		void setMixer(AudioMixer* newMixer);
		
		static void bqPlayerCallback(SLAndroidSimpleBufferQueueItf bq, void* context);
		
	private:
		AudioMixer* mixer;
		int16_t *playBuffer;
		int16_t *backBuffer;
		
		// engine interfaces
		SLObjectItf engineObject;
		SLEngineItf engineEngine;

		// output mix interfaces
		SLObjectItf outputMixObject;

		// buffer queue player interfaces
		SLObjectItf bqPlayerObject;
		SLPlayItf bqPlayerPlay;
		SLAndroidSimpleBufferQueueItf bqPlayerBufferQueue;
		SLEffectSendItf bqPlayerEffectSend;
		
 		void swapBuffers();
		bool swappedBuffers;
		
		void initOpenSL();
		void terminateOpenSL();
		CoreMutex* streamMutex;
	};
	
    class OpenSLAudioInterface : public AudioInterface {
	public:
		OpenSLAudioInterface();
		~OpenSLAudioInterface();
			
		void setMixer(AudioMixer* newMixer);
			
	private:
		OpenSLStream* stream;
    };
}

