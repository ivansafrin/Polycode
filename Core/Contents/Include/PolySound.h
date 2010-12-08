/*
 *  PolySound.h
 *  Poly
 *
 *  Created by Ivan Safrin on 3/15/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
// @package Sound

#pragma once
#include <vorbis/vorbisfile.h>

#include "PolyLogger.h"
#include "PolyGlobals.h"
#include <string>
#include <vector>
#include "al.h"
#include "alc.h"
#include "OSBasics.h"

using std::string;
using std::vector;

#define ALNoErrorStr "No AL error occurred"
#define ALInvalidNameStr "AL error: a bad name (ID) was passed to an OpenAL function"
#define ALInvalidEnumStr "AL error: an invalid enum value was passed to an OpenAL function"
#define ALInvalidValueStr "AL error: an invalid value was passed to an OpenAL function"
#define ALInvalidOpStr "AL error: the requested operation is not valid"
#define ALOutOfMemoryStr "AL error: the requested operation resulted in OpenAL running out of memory"
#define ALOtherErrorStr "AL error: unknown error"

#define BUFFER_SIZE 32768

namespace Polycode {
	
	class _PolyExport Sound {
	public:
		Sound(string fileName);
		~Sound();
		
		void Play(bool once);
		void Stop();
		
		ALuint loadWAV(string fileName);
		ALuint loadOGG(string fileName);
		
		ALuint GenSource(ALuint buffer);
		ALuint GenSource();
	
		void checkALError(string operation);
		void soundError(string err);
		void soundCheck(bool result, string err);
		static unsigned long readByte32(const unsigned char buffer[4]);		
		static unsigned short readByte16(const unsigned char buffer[2]);

	private:
	
		ALuint soundSource;
		
	};
}