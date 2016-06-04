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

#include <SLES/OpenSLES_Android.h>

namespace Polycode {
	
	class OpenSLAudioInterface : public AudioInterface {
	public:
		OpenSLAudioInterface();
		~OpenSLAudioInterface();
		
		void setMixer(AudioMixer* newMixer);
		
		void initOpenSL();
		void terminateOpenSL();
		
		static void queueCallback(SLAndroidSimpleBufferQueueItf caller, void *pContext);
		
		SLAndroidSimpleBufferQueueItf mPlayerQueue;
	private:
		int16_t* buffer;
		
		SLObjectItf mEngineObj;
		SLEngineItf mEngine;
		SLObjectItf mOutputMixObj;
		
		SLObjectItf mPlayerObj; 
		SLPlayItf mPlayer;
		SLVolumeItf mVolume;
    };
}

