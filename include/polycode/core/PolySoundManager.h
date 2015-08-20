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
#include "polycode/core/PolyGlobals.h"
#include "polycode/core/PolyVector3.h"
#include "polycode/core/PolySound.h"

#define POLY_FRAMES_PER_BUFFER 512
#define POLY_AUDIO_FREQ 44100
#define POLY_CIRCULAR_BUFFER_SIZE 32
#define POLY_NUM_CHANNELS 2
#define POLY_MIX_BUFFER_SIZE (POLY_FRAMES_PER_BUFFER*POLY_CIRCULAR_BUFFER_SIZE)

namespace Polycode {
	
    class _PolyExport AudioInterface {
        public:
            AudioInterface();
            void addToBuffer(int16_t *data, unsigned int count);
        
            int16_t bufferData[POLY_NUM_CHANNELS][POLY_FRAMES_PER_BUFFER*POLY_CIRCULAR_BUFFER_SIZE];
            unsigned int readOffset;
            unsigned int writeOffset;
    };
    
    
	/**
	* Controls global sound settings.
	*/
    
	class _PolyExport SoundManager : public PolyBase{
	public:
		SoundManager();
		~SoundManager();
		 
		void setListenerPosition(Vector3 position);
		void setListenerOrientation(Vector3 orientation, Vector3 upVector);	
        
        bool recordSound(unsigned int rate, unsigned int sampleSize);
        Sound *stopRecording(bool generateFloatBuffer = false);
        void setAudioInterface(AudioInterface *audioInterface);
        
        void Update();
		
		/**
		* Sets the global sound volume.
		*/ 
		void setGlobalVolume(Number globalVolume);
        
        void registerSound(Sound *sound);
        void unregisterSound(Sound *sound);
		
	protected:
		
        AudioInterface *audioInterface;
        
        int16_t mixBuffer[POLY_MIX_BUFFER_SIZE*POLY_NUM_CHANNELS];
        
        Number globalVolume;
        Number testVal;
        Number leftOver;
        
        std::vector<Sound*> sounds;
        int recordingBufferSize;
        int recordingBufferRate;
	};
}
