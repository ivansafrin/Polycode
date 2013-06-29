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
#include "PolyString.h"

#if defined(__APPLE__) && defined(__MACH__)
	#include <OpenAL/al.h>
	#include <OpenAL/alc.h>
#else
	#include "al.h"
	#include "alc.h"
#endif

#define ALNoErrorStr "No AL error occurred"
#define ALInvalidNameStr "AL error: a bad name (ID) was passed to an OpenAL function"
#define ALInvalidEnumStr "AL error: an invalid enum value was passed to an OpenAL function"
#define ALInvalidValueStr "AL error: an invalid value was passed to an OpenAL function"
#define ALInvalidOpStr "AL error: the requested operation is not valid"
#define ALOutOfMemoryStr "AL error: the requested operation resulted in OpenAL running out of memory"
#define ALOtherErrorStr "AL error: unknown error"

#define BUFFER_SIZE 32768

namespace Polycode {

class String;

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
		Sound(const char *data, int size, int channels = 1, ALsizei freq = 44100, int bps = 16);
		virtual ~Sound();

		void loadFile(String fileName);

		void reloadProperties();

		/**
		* Play the sound once or in a loop.
		* @param once If this is true, play it once, otherwise, loop.
		*/
		void Play(bool loop=false);

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

		void setIsPositional(bool isPositional);

		void setSoundPosition(Vector3 position);
		void setSoundVelocity(Vector3 velocity);
		void setSoundDirection(Vector3 direction);

		/**
		* Sets the current sample offset of this sound.
		* @param off A number 0 <= off < sound sample length
		*/
		void setOffset(int off);

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

		void setPositionalProperties(Number referenceDistance, Number maxDistance);

		void setReferenceDistance(Number referenceDistance);
		void setMaxDistance(Number maxDistance);

		Number getReferenceDistance();
		Number getMaxDistance();

		ALuint loadBytes(const char *data, int size, int channels = 1, ALsizei freq = 44100, int bps = 16);
		ALuint loadWAV(const String& fileName);
		ALuint loadOGG(const String& fileName);

		ALuint GenSource(ALuint buffer);
		ALuint GenSource();

		ALenum checkALError(const String& operation);
		void soundError(const String& err);
		void soundCheck(bool result, const String& err);
		static unsigned long readByte32(const unsigned char buffer[4]);
		static unsigned short readByte16(const unsigned char buffer[2]);

	protected:

		Number referenceDistance;
		Number maxDistance;

		Number pitch;
		Number volume;

		String fileName;

		bool soundLoaded;

		bool isPositional;
		ALuint buffer; // Kept around only for deletion purposes
		ALuint soundSource;
		int sampleLength;

};

}
