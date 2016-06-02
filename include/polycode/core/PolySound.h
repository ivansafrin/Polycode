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
#include "polycode/core/PolyString.h"
#include "polycode/core/PolyCoreServices.h"

#define BUFFER_SIZE 32768
#define STREAMING_BUFFER_SIZE

namespace Polycode {

	enum SoundFormat {SoundFormatUnsupported, SoundFormat8, SoundFormat16, SoundFormat32};
	
	class String;
	class Vector3;
	class Quaternion;
	
	class  AudioStreamingSource {
		public:
			AudioStreamingSource(unsigned int channels, unsigned int freq);		   
			POLYIGNORE virtual unsigned int streamData(int16_t *buffer, unsigned int size);
		
			unsigned int getNumChannels();
			unsigned int getFrequency();
		
		protected:
		
			unsigned int channels;
			unsigned int freq;
		
	};
	
	/**
	* Loads and plays a sound. This class can load and play an OGG or WAV sound file.
	*/
	class _PolyExport Sound : public PolyBase {
	public:
	
		/**
		* Constructor.
		* @param fileName Path to an OGG or WAV file to load.
		*/ 
		Sound(const String& fileName);
		Sound(int size, const char *data, int channels, unsigned int freq, SoundFormat format);
		Sound(AudioStreamingSource *streamingSource);
		
		Number getSampleAsNumber(unsigned int offset, unsigned int channel, const Vector3 &position, const Quaternion &orientation);
		
		virtual ~Sound();
		
		void loadFile(String fileName);
		
		/**
		* Play the sound once or in a loop.
		* @param once If this is true, play it once, otherwise, loop.
		*/
		void Play(bool loop=false, bool restartSound=true);
		
		/**
		* Stop the sound playback.
		*/		
		void Stop();
		
		/**
		* Sets the volume of this sound.
		* @param newVolume A Number 0-1, where 0 is no sound and 1 is the loudest.
		*/
		void setVolume(Number newVolume);

		Number getVolume();

		/**
		* Sets the pitch of this sound.
		* @param newPitch A Number 0-1.
		*/		
		void setPitch(Number newPitch);
		
		Number getPitch();
		
		/**
		* Returns true if the sound is playing.
		* @return True if sound is playing, false if otherwise.
		*/
		bool isPlaying();
		
		bool isLooped();
		
		void setIsPositional(bool isPositional);
		
		void setSoundPosition(const Vector3 &position);
		void setSoundVelocity(const Vector3 &velocity);
		void setSoundDirection(const Vector3 &direction);
		
		/**
		* Sets the current sample offset of this sound.
		* @param off A number 0 <= off < sound sample length
		*/
		void setOffset(unsigned int offset);
		
		String getFileName();
		
		Number getPlaybackDuration();
		
		Number getPlaybackTime();
		
		void seekTo(Number time);
		/**
		* Returns the current sample offset (playback progress) of this sound.
		* @return The sample offset if it is known, -1 otherwise.
		*/
		int getOffset();
		
		/**
		* Returns the number of samples in the sound.
		* @return The sample length if it is known, -1 otherwise.
		*/
		int getSampleLength();
		
		unsigned int getFrequency();
		
		void setPositionalProperties(Number referenceDistance, Number maxDistance);
		
		void setReferenceDistance(Number referenceDistance);
		void setMaxDistance(Number maxDistance);
		
		Number getReferenceDistance();
		Number getMaxDistance();
		

		bool loadBytes(const char *data, int size, int channels, unsigned int freq, SoundFormat format);
		bool loadWAV(const String& fileName);
		bool loadOGG(const String& fileName);
		
		void soundCheck(bool result, const String& err);
		static unsigned long readByte32(const unsigned char buffer[4]);		
		static unsigned short readByte16(const unsigned char buffer[2]);
		
		void updateStream(unsigned int streamCount);

	protected:
		
		Number modulateSampleForListener(Number sample, unsigned int channel, const Vector3 &position, const Quaternion &orientation);
		
		Vector3 position;
		Vector3 velocity;
		Vector3 direction;
		
		Number referenceDistance;
		Number maxDistance;
		
		bool streamingSound;
		AudioStreamingSource *streamingSource;
		
		Number pitch;
		Number frequencyAdjust;
		
		Number volume;
	
		String fileName;
		
		bool soundLoaded;
	
		bool playing;
		bool looped;
		
		bool isPositional;
		unsigned int numSamples;
		unsigned int numChannels;
		unsigned int playbackOffset;
		unsigned int frequency;
	
		int16_t *soundBuffer;

	};
}
