/*
 Copyright (C) 2011 by Ivan Safrin
 
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
#include "PolyGlobals.h"
#include "PolyVector3.h"
#include "PolySound.h"

#if defined(__APPLE__) && defined(__MACH__)
    #include <OpenAL/al.h>
    #include <OpenAL/alc.h>
#else
    #include "al.h"
    #include "alc.h"
#endif

namespace Polycode {
	
	/**
	* Controls global sound settings.
	*/
	class _PolyExport SoundManager : public PolyBase{
	public:
		SoundManager();
		~SoundManager();
		
		void setListenerPosition(Vector3 position);
		void setListenerOrientation(Vector3 orientation, Vector3 upVector);	
		void initAL();
        
        bool recordSound(unsigned int rate, unsigned int sampleSize);
        Sound *stopRecording(bool generateFloatBuffer = false);

        void Update();
		
		/**
		* Sets the global sound volume.
		*/ 
		void setGlobalVolume(Number globalVolume);
		
		
	protected:
		
		ALCdevice* device;
        ALCdevice* captureDevice;
        ALbyte *recordingBuffer;
        int recordingBufferSize;
        int recordingBufferRate;
		ALCcontext* context;		
	};
}
