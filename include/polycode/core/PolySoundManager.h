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
#include "polycode/core/PolyQuaternion.h"
#include "polycode/core/PolySound.h"

#define POLY_FRAMES_PER_BUFFER 512
#define POLY_AUDIO_FREQ 44100
#define POLY_CIRCULAR_BUFFER_SIZE 32
#if PLATFORM == PLATFORM_ANDROID
#define POLY_NUM_CHANNELS 1
#else
#define POLY_NUM_CHANNELS 2
#endif
#define POLY_MIX_BUFFER_SIZE (POLY_FRAMES_PER_BUFFER*POLY_CIRCULAR_BUFFER_SIZE)

namespace Polycode {
	
	class _PolyExport AudioMixer {
		public:

			AudioMixer();
			~AudioMixer();

			void mixIntoBuffer(int16_t *buffer, unsigned int numSamples);
			std::vector<Sound*> sounds;
			Number globalVolume;
			Vector3 listenerPosition;
			Quaternion listenerOrientation;
			CoreMutex *mixerMutex;
	};
	
	class _PolyExport AudioInterface {
		public:
			AudioInterface();
			//void addToBuffer(int16_t *data, unsigned int count);
			virtual void setMixer(AudioMixer *mixer);
			AudioMixer *getMixer();		   
		protected:
			AudioMixer *mixer;
	};
	
	
	/**
	* Controls global sound settings.
	*/
	
	class _PolyExport SoundManager : public PolyBase{
	public:
		SoundManager();
		~SoundManager();
		 
		void setListenerPosition(const Vector3 &position);
		void setListenerOrientation(const Quaternion &orientation);
		
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
		
		AudioMixer *mixer;
		AudioInterface *audioInterface;
		
		int16_t mixBuffer[POLY_MIX_BUFFER_SIZE*POLY_NUM_CHANNELS];
		
		Number testVal;
		Number leftOver;
		
	   
		int recordingBufferSize;
		int recordingBufferRate;
	};
}
