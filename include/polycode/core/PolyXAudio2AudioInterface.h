    
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

#include <xaudio2.h>

#include "polycode/core/PolyGlobals.h"
#include "polycode/core/PolyThreaded.h"
#include "polycode/core/PolySoundManager.h"

#include <queue>

#define MAX_XAUDIO_BUFFER_COUNT 4

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=nullptr; } }
#endif


namespace Polycode {

	class XAudioInterfaceBuffer {
		public:
			int16_t bufferData[POLY_FRAMES_PER_BUFFER * POLY_NUM_CHANNELS];
	};

	class XAudio2FillThread : public Threaded {
		public:

			void runThread();

			AudioMixer *mixer;
			std::queue<XAudioInterfaceBuffer*> bufferQueue;
			CoreMutex *bufferMutex;
	};

	class XAudio2Stream : public Threaded, IXAudio2VoiceCallback {
		public:

			XAudio2Stream();

			STDMETHOD_(void, OnVoiceProcessingPassStart)(UINT32) override
			{
			}
			STDMETHOD_(void, OnVoiceProcessingPassEnd)() override
			{
			}
			STDMETHOD_(void, OnStreamEnd)() override
			{
			}
			STDMETHOD_(void, OnBufferStart)(void*) override
			{
			}
			STDMETHOD_(void, OnBufferEnd)(void*) override
			{
				SetEvent(hBufferEndEvent);
			}
			STDMETHOD_(void, OnLoopEnd)(void*) override
			{
			}
			STDMETHOD_(void, OnVoiceError)(void*, HRESULT) override
			{
			}

			void setMixer(AudioMixer *mixer);
			HRESULT initXAudio2();
			void runThread();

				
		private:
				
				XAudioInterfaceBuffer *lastBuffer;
				XAudioInterfaceBuffer *lastBuffer2;

				AudioMixer *mixer;

				HANDLE hBufferEndEvent;

				XAudio2FillThread *fillThread;

				IXAudio2* pXAudio2;
				IXAudio2MasteringVoice* pMasterVoice;
				IXAudio2SourceVoice* pSourceVoice;

	};

    class XAudio2AudioInterface : public Polycode::AudioInterface {
        public:
			XAudio2AudioInterface();
            ~XAudio2AudioInterface();
			void setMixer(AudioMixer *mixer);

        private:
			
			XAudio2Stream *xAudioStream;
    };
    
}