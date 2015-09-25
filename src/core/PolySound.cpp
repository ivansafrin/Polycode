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

#include "polycode/core/PolySound.h"

#ifndef NO_OGG
	#define OV_EXCLUDE_STATIC_CALLBACKS
	#include <vorbis/vorbisfile.h>
#endif

#undef OV_EXCLUDE_STATIC_CALLBACKS
#include "polycode/core/PolyString.h"
#include "polycode/core/PolyLogger.h"
#include "polycode/core/PolySoundManager.h"
#include "polycode/core/PolyCore.h"
#include "polycode/core/PolyCoreServices.h"
#include <string>
#include <vector>
#include <stdint.h>
#include <limits>

#ifndef MAX_FLOAT
	#define MAX_FLOAT (std::numeric_limits<double>::infinity())
#endif

#ifndef INT32_MAX
	#define INT32_MAX (std::numeric_limits<int32_t>::max())
#endif

#ifndef INT16_MAX
	#define INT16_MAX (std::numeric_limits<int16_t>::max())
#endif

using namespace std;
using namespace Polycode;

AudioStreamingSource::AudioStreamingSource(unsigned int channels, unsigned int freq) : channels(channels), freq(freq) {
}

unsigned int AudioStreamingSource::getNumChannels() {
    return channels;
}

unsigned int AudioStreamingSource::getFrequency() {
    return freq;
}

unsigned int AudioStreamingSource::streamData(int16_t *buffer, unsigned int size) {
    return 0;
}

#ifndef NO_OGG
size_t custom_readfunc(void *ptr, size_t size, size_t nmemb, void *datasource) {
    Polycode::CoreFile *file = (Polycode::CoreFile*) datasource;
	return file->read(ptr, size, nmemb);
}

int custom_seekfunc(void *datasource, ogg_int64_t offset, int whence){
	Polycode::CoreFile *file = (Polycode::CoreFile*) datasource;
	return file->seek(offset, whence);
}

int custom_closefunc(void *datasource) {
	Polycode::CoreFile *file = (Polycode::CoreFile*) datasource;
	Services()->getCore()->closeFile(file);
    return 0;
}

long custom_tellfunc(void *datasource) {
	CoreFile *file = (CoreFile*) datasource;
	return file->tell();
}
#endif

Sound::Sound(const String& fileName) :  referenceDistance(1), maxDistance(MAX_FLOAT), pitch(1), volume(1), numSamples(-1), streamingSound(false), playing(false), playbackOffset(0), streamingSource(NULL) {
	soundLoaded = false;
	setIsPositional(false);
	loadFile(fileName);
    if(soundLoaded) {
        Services()->getSoundManager()->registerSound(this);
    }
}

Sound::Sound(int size, const char *data, int channels, unsigned int freq, SoundFormat format) : referenceDistance(1), maxDistance(MAX_FLOAT), pitch(1), volume(1), numSamples(-1), streamingSound(false), playing(false) , playbackOffset(0), streamingSource(NULL) {
	setIsPositional(false);
    soundLoaded = loadBytes(data, size, channels, freq, format);
    if(soundLoaded) {
        Services()->getSoundManager()->registerSound(this);
    }
}

Sound::Sound(AudioStreamingSource *streamingSource) : referenceDistance(1), maxDistance(MAX_FLOAT), pitch(1), volume(1),  numSamples(-1), streamingSound(true), streamingSource(streamingSource), playing(false), playbackOffset(0) {

    soundBuffer = (int16_t*) malloc(sizeof(int16_t) * streamingSource->getNumChannels() * POLY_MIX_BUFFER_SIZE);
    Services()->getSoundManager()->registerSound(this);
    numChannels = streamingSource->getNumChannels();
}

void Sound::updateStream(unsigned int streamCount) {
    if(streamingSource) {
        playbackOffset = 0;
        numSamples = streamCount;
        streamingSource->streamData(soundBuffer, streamCount);
    }
}

void Sound::loadFile(String fileName) {

	if(soundLoaded) {
        free(soundBuffer);
	}

	String actualFilename = fileName;
	CoreFile *test = Services()->getCore()->openFile(fileName, "rb");
	if(!test) {
		actualFilename = "default/default.wav";
	} else {
		Services()->getCore()->closeFile(test);
	}
	
	String extension;
	size_t found;
	found=actualFilename.rfind(".");
	if (found!=string::npos) {
		extension = actualFilename.substr(found+1);
	} else {
		extension = "";
	}
	
	if(extension == "wav" || extension == "WAV") {
		soundLoaded = loadWAV(actualFilename);
	} else if(extension == "ogg" || extension == "OGG") {
		soundLoaded = loadOGG(actualFilename);
	}
	
	this->fileName = actualFilename;
}

String Sound::getFileName() {
	return fileName;
}

Number Sound::getVolume() {
	return volume;
}

Number Sound::getPitch() {
	return pitch;
}

Sound::~Sound() {
    free(soundBuffer);
    Services()->getSoundManager()->unregisterSound(this);
}

void Sound::soundCheck(bool result, const String& err) {
	if(!result)
		soundError(err);
}

void Sound::soundError(const String& err) {
	Logger::log("SOUND ERROR: %s\n", err.c_str());
}

unsigned long Sound::readByte32(const unsigned char data[4]) {
#if TAU_BIG_ENDIAN
    return (data[0] << 24) + (data[1] << 16) + (data[2] << 8) + data[3];
#else
    return (data[3] << 24) + (data[2] << 16) + (data[1] << 8) + data[0];
#endif
}

unsigned short Sound::readByte16(const unsigned char data[2]) {
#if TAU_BIG_ENDIAN
    return (data[0] << 8) + data[1];
#else
    return (data[1] << 8) + data[0];
#endif	
}

void Sound::Play(bool loop, bool restartSound) {
    if(restartSound) {
        playbackOffset = 0;
    }
    playing = true;
    looped = loop;
}

bool Sound::isPlaying() {
    return playing;
}

bool Sound::isLooped() {
    return looped;
}


void Sound::setVolume(Number newVolume) {
	this->volume = newVolume;
}

void Sound::setPitch(Number newPitch) {
	this->pitch = newPitch;
}

void Sound::setSoundPosition(Vector3 position) {
    /*
	if(isPositional)
		alSource3f(soundSource,AL_POSITION, position.x, position.y, position.z);
	checkALError("Set sound position");
     */
        //NOAL_TODO
}

void Sound::setSoundVelocity(Vector3 velocity) {
    /*
	if(isPositional)
		alSource3f(soundSource,AL_VELOCITY, velocity.x, velocity.y, velocity.z);
	checkALError("Set sound velocity");
     */
        //NOAL_TODO
}

void Sound::setSoundDirection(Vector3 direction) {
    /*
	if(isPositional)
		alSource3f(soundSource,AL_DIRECTION, direction.x, direction.y, direction.z);
	checkALError("Set sound direction");
     */
        //NOAL_TODO
}


Number Sound::getPlaybackTime() {
    /*
	float result = 0.0;
	alGetSourcef(soundSource, AL_SEC_OFFSET, &result);
	return result;
     */
        //NOAL_TODO
    return 0.0;
}

Number Sound::getPlaybackDuration() {
    /*
	ALint sizeInBytes;
	ALint channels;
	ALint bits;
	ALint bufferID;
	alGetSourcei(soundSource, AL_BUFFER, &bufferID);
	
	alGetBufferi(bufferID, AL_SIZE, &sizeInBytes);
	alGetBufferi(bufferID, AL_CHANNELS, &channels);
	alGetBufferi(bufferID, AL_BITS, &bits);

	int lengthInSamples = sizeInBytes * 8 / (channels * bits);

	ALint frequency;
	alGetBufferi(bufferID, AL_FREQUENCY, &frequency);
	Number durationInSeconds = (float)lengthInSamples / (float)frequency;
	
	return durationInSeconds;
     */
        //NOAL_TODO
    return 0.0;
}
		
int Sound::getOffset() {
    return playbackOffset;
}

void Sound::setOffset(unsigned int offset) {
    playbackOffset = (offset);
    
    Number adjustedOffset = ((Number)playbackOffset) * pitch;
    
    if((unsigned int)adjustedOffset >= numSamples) {
        playbackOffset = 0;
        if(!looped && !streamingSource) {
            playing = false;
        }
    }
}

void Sound::seekTo(Number time) {
    /*
	if(time > getPlaybackDuration())
		return;
	alSourcef(soundSource, AL_SEC_OFFSET, time);
	checkALError("Seek");
     */
            //NOAL_TODO
}

int Sound::getSampleLength() {
	return numSamples;
}

void Sound::setPositionalProperties(Number referenceDistance, Number maxDistance) { 
	setReferenceDistance(referenceDistance);
	setMaxDistance(maxDistance);
}

void Sound::setReferenceDistance(Number referenceDistance) {
	this->referenceDistance = referenceDistance;
	//alSourcef(soundSource, AL_REFERENCE_DISTANCE, referenceDistance);
	//checkALError("Set reference distance");
            //NOAL_TODO
}

void Sound::setMaxDistance(Number maxDistance) {
	this->maxDistance = maxDistance;
	//alSourcef(soundSource,AL_MAX_DISTANCE, maxDistance);
//	checkALError("Set max distance");
            //NOAL_TODO
}
		
Number Sound::getReferenceDistance() {
	return referenceDistance;
}

Number Sound::getMaxDistance() {
	return maxDistance;
}

void Sound::setIsPositional(bool isPositional) {
    /*
	this->isPositional = isPositional;
	if(isPositional) {
		alSourcei(soundSource, AL_SOURCE_RELATIVE, AL_FALSE);
	} else {
		alSourcei(soundSource, AL_SOURCE_RELATIVE, AL_TRUE);	
		alSource3f(soundSource,AL_POSITION, 0,0,0);
		alSource3f(soundSource,AL_VELOCITY, 0,0,0);
		alSource3f(soundSource,AL_DIRECTION, 0,0,0);				
	}
	checkALError("Set is-positional");
     */
            //NOAL_TODO
}

void Sound::Stop() {
    playing = false;
}


Number Sound::getSampleAsNumber(unsigned int offset, unsigned int channel) {
    Number adjustedOffset = ((Number)offset) * pitch;
    Number ret = (((Number)(soundBuffer[((((unsigned int )adjustedOffset)%numSamples)*numChannels)+(channel % numChannels)])/((Number)INT16_MAX))) * volume;
    return ret;
}


bool Sound::loadBytes(const char *data, int size, int channels, unsigned int freq, SoundFormat format) {
    
    if(format == SoundFormatUnsupported) {
        Logger::log("[%s] Error: sound format unsupported!\n", fileName.c_str());
        return false;
    }
    
    soundBuffer = (int16_t*) malloc(sizeof(int16_t) * channels * size);
    
    int16_t *soundBufferPtr = soundBuffer;
    
    unsigned int dataOffset = 0;
    
    switch(format) {
        case SoundFormat8:
            numSamples = size / channels;
            break;
        case SoundFormat16:
            numSamples = size / channels / 2;
            break;
        case SoundFormat32:
            numSamples = size / channels / 4;
            break;
        default:
        break;
    }
    
    
    for(int i=0; i < numSamples; i++){
        for(int c=0; c < channels; c++) {
            switch(format) {
                case SoundFormat8:
                    *soundBufferPtr = ((int8_t*)data)[dataOffset];
                break;
                case SoundFormat16:
                    *soundBufferPtr = ((int16_t*)data)[dataOffset];
                break;
                case SoundFormat32:
                    *soundBufferPtr = ((int32_t*)data)[dataOffset];
                break;
                default:
                break;
            }
            soundBufferPtr++;
            dataOffset++;
        }
    }
    
    numChannels = channels;
    frequency = freq;

    return true;
}

unsigned int Sound::getFrequency() {
    return frequency;
}


bool Sound::loadOGG(const String& fileName) {
#ifndef NO_OGG
    /*
//	floatBuffer.clear();
	vector<char> data;
	
	alGenBuffers(1, &buffer);
	int endian = 0;             // 0 for Little-Endian, 1 for Big-Endian
	int bitStream;
	long bytes;
	char array[BUFFER_SIZE];    // Local fixed size array
	CoreFile *f;
	ALenum format;
	ALsizei freq;
	
	// Open for binary reading
	f = Services()->getCore()->openFile(fileName.c_str(), "rb");
	if(!f) {
		soundError("Error loading OGG file!\n");
		return buffer;
	}
	vorbis_info *pInfo;
	OggVorbis_File oggFile;	
	
	ov_callbacks callbacks;
	callbacks.read_func = custom_readfunc;
	callbacks.seek_func = custom_seekfunc;
	callbacks.close_func = custom_closefunc;
	callbacks.tell_func = custom_tellfunc;
	
	ov_open_callbacks( (void*)f, &oggFile, NULL, 0, callbacks);
//	ov_open(f, &oggFile, NULL, 0);
	// Get some information about the OGG file
	pInfo = ov_info(&oggFile, -1);
	
	// Check the number of channels... always use 16-bit samples
	if (pInfo->channels == 1)
		format = AL_FORMAT_MONO16;
	else
		format = AL_FORMAT_STEREO16;
	// end if
	
	// The frequency of the sampling rate
	freq = pInfo->rate;	
	do {
		// Read up to a buffer's worth of decoded sound data
		bytes = ov_read(&oggFile, array, BUFFER_SIZE, endian, 2, 1, &bitStream);
		// Append to end of buffer
		data.insert(data.end(), array, array + bytes);
	} while (bytes > 0);
	ov_clear(&oggFile);
	
	sampleLength = data.size() / sizeof(unsigned short);
	
	alBufferData(buffer, format, &data[0], static_cast<ALsizei>(data.size()), freq);
	
	if(generateFloatBuffer) {
		int32_t *ptr32 = (int32_t*) &data[0];
		for(int i=0; i < data.size()/4; i++ ) {
			floatBuffer.push_back(((Number)ptr32[i])/((Number)INT32_MAX));
		}	
	}
     */
	return false;
#endif
}

bool Sound::loadWAV(const String& fileName) {
    
	long bytes;
	vector <char> data;
	
	// Local resources
	CoreFile *f = NULL;
	char *array = NULL;
	
    // Open for binary reading
    f = Services()->getCore()->openFile(fileName.c_str(), "rb");
    if (!f) {
        soundError("LoadWav: Could not load wav from " + fileName);
        return false;
    }
    
    // buffers
    char magic[5];
    magic[4] = '\0';
    unsigned char data32[4];
    unsigned char data16[2];
    
    // check magic
    soundCheck(f->read(magic,4,1) == 1, "LoadWav: Cannot read wav file "+ fileName );
    soundCheck(String(magic) == "RIFF", "LoadWav: Wrong wav file format. This file is not a .wav file (no RIFF magic): "+ fileName );
    
    // skip 4 bytes (file size)
    f->seek(4,SEEK_CUR);
    
    // check file format
    soundCheck(f->read(magic,4,1) == 1, "LoadWav: Cannot read wav file "+ fileName );
    soundCheck(String(magic) == "WAVE", "LoadWav: Wrong wav file format. This file is not a .wav file (no WAVE format): "+ fileName );
    
    // check 'fmt ' sub chunk (1)
    soundCheck(f->read(magic,4,1) == 1, "LoadWav: Cannot read wav file "+ fileName );
    soundCheck(String(magic) == "fmt ", "LoadWav: Wrong wav file format. This file is not a .wav file (no 'fmt ' subchunk): "+ fileName );
    
    // read (1)'s size
    soundCheck(f->read(data32,4,1)   == 1, "LoadWav: Cannot read wav file "+ fileName );
    unsigned long subChunk1Size = readByte32(data32);
    soundCheck(subChunk1Size >= 16, "Wrong wav file format. This file is not a .wav file ('fmt ' chunk too small, truncated file?): "+ fileName );
    
    // check PCM audio format
    soundCheck(f->read(data16,2,1) == 1, "LoadWav: Cannot read wav file "+ fileName );
    unsigned short audioFormat = readByte16(data16);
    soundCheck(audioFormat == 1, "LoadWav: Wrong wav file format. This file is not a .wav file (audio format is not PCM): "+ fileName );
    
    // read number of channels
    soundCheck(f->read(data16,2,1) == 1, "LoadWav: Cannot read wav file "+ fileName );
    unsigned short channels = readByte16(data16);
    
    // read frequency (sample rate)
    soundCheck(f->read(data32,4,1) == 1, "LoadWav: Cannot read wav file "+ fileName );
    unsigned long frequency = readByte32(data32);
    
    // skip 6 bytes (Byte rate (4), Block align (2))
    f->seek(6,SEEK_CUR);
    
    // read bits per sample
    soundCheck(f->read(data16,2,1) == 1, "LoadWav: Cannot read wav file "+ fileName );
    unsigned short bps = readByte16(data16);
    
    SoundFormat format = SoundFormatUnsupported;
    
    switch(bps) {
        case 8:
            format = SoundFormat8;
        break;
        case 16:
            format = SoundFormat16;
        break;
        case 32:
            format = SoundFormat32;
        break;
            
    }
    
    // check 'data' sub chunk (2)
    soundCheck(f->read(magic,4,1) == 1, "LoadWav: Cannot read wav file "+ fileName );
    soundCheck(String(magic) == "data", "LoadWav: Wrong wav file format. This file is not a .wav file (no data subchunk): "+ fileName );
    
    soundCheck(f->read(data32,4,1) == 1, "LoadWav: Cannot read wav file "+ fileName );
    unsigned long subChunk2Size = readByte32(data32);
    
    array = new char[BUFFER_SIZE];
    
    while (data.size() != subChunk2Size) {
        // Read up to a buffer's worth of decoded sound data
        bytes = f->read(array, 1, BUFFER_SIZE);
        
        if (bytes <= 0)
            break;
        
        if (data.size() + bytes > subChunk2Size)
            bytes = subChunk2Size - data.size();
        
        // Append to end of buffer
        data.insert(data.end(), array, array + bytes);
    };
    
    delete []array;
    array = NULL;
    
    Services()->getCore()->closeFile(f);
    f = NULL;
    
    
    
    return loadBytes(&data[0], data.size(), channels, frequency, format);

}
 

//NOAL_TODO
