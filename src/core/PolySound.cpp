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
#include <stdlib.h>
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

Sound::Sound(const String& fileName) :  referenceDistance(1), maxDistance(MAX_FLOAT), pitch(1), volume(1), numSamples(-1), streamingSound(false), playing(false), playbackOffset(0), streamingSource(NULL), frequencyAdjust(1.0) {
	soundLoaded = false;
	setIsPositional(false);
	loadFile(fileName);
    if(soundLoaded) {
        Services()->getSoundManager()->registerSound(this);
    }
}

Sound::Sound(int size, const char *data, int channels, unsigned int freq, SoundFormat format) : referenceDistance(1), maxDistance(MAX_FLOAT), pitch(1), volume(1), numSamples(-1), streamingSound(false), playing(false) , playbackOffset(0), streamingSource(NULL), frequencyAdjust(1.0) {
	setIsPositional(false);
    soundLoaded = loadBytes(data, size, channels, freq, format);
    if(soundLoaded) {
        Services()->getSoundManager()->registerSound(this);
    }
}

Sound::Sound(AudioStreamingSource *streamingSource) : referenceDistance(1), maxDistance(MAX_FLOAT), pitch(1), volume(1),  numSamples(-1), streamingSound(true), streamingSource(streamingSource), playing(false), playbackOffset(0), frequencyAdjust(1.0) {

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
		Logger::log(err);
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

void Sound::setSoundPosition(const Vector3 &position) {
    this->position = position;
}

void Sound::setSoundVelocity(const Vector3 &velocity) {
    this->velocity = velocity;
}

void Sound::setSoundDirection(const Vector3 &direction) {
    this->direction = direction;
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
    
    Number adjustedOffset = ((Number)playbackOffset) * pitch * frequencyAdjust;
    
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
}

void Sound::setMaxDistance(Number maxDistance) {
	this->maxDistance = maxDistance;
}
		
Number Sound::getReferenceDistance() {
	return referenceDistance;
}

Number Sound::getMaxDistance() {
	return maxDistance;
}

void Sound::setIsPositional(bool isPositional) {
	this->isPositional = isPositional;
}

void Sound::Stop() {
    playing = false;
}


Number Sound::getSampleAsNumber(unsigned int offset, unsigned int channel, const Vector3 &position, const Quaternion &orientation) {
    Number adjustedOffset = ((Number)offset) * pitch * frequencyAdjust;
    Number ret;
    if(isPositional) {
        ret = (((Number)(soundBuffer[((((unsigned int )adjustedOffset)%numSamples)*numChannels)])/((Number)INT16_MAX))) * volume;
        ret = modulateSampleForListener(ret, channel, position, orientation);
    } else {
        ret = (((Number)(soundBuffer[((((unsigned int )adjustedOffset)%numSamples)*numChannels)+(channel % numChannels)])/((Number)INT16_MAX))) * volume;
    }
    return ret;
}

Number Sound::modulateSampleForListener(Number sample, unsigned int channel, const Vector3 &position, const Quaternion &orientation) {
    
    // setup different channel configurations here
    // if(STEREO) {
    Vector3 earDirection;
    if(channel) {
        earDirection = Vector3(-1.0, 0.0, 0.0);
    } else {
        earDirection = Vector3(1.0, 0.0, 0.0);
    }
    earDirection = orientation.applyTo(earDirection);
    
    Vector3 dir = position - this->position;
    dir.Normalize();
    Number muliplier = earDirection.dot(dir);
    if(muliplier < 0.0) {
        muliplier = 0.0;
    }
    
    Number ret = sample * (0.1 + (muliplier * 0.9)); // bleed 0.1 into the other ear
    Number distance = position.distance(this->position);
    Number attenuate = 0.5 * pow(referenceDistance/distance, 2.0);
    
    attenuate = min(attenuate, 1.0);
    attenuate = max(attenuate, 0.0);
    ret *= attenuate;
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
    
    // adjust for different frequency
    frequencyAdjust = (Number)freq/(Number)POLY_AUDIO_FREQ;
    
    return true;
}

unsigned int Sound::getFrequency() {
    return frequency;
}


bool Sound::loadOGG(const String& fileName) {
#ifndef NO_OGG

	vector<char> data;
	int bitStream;
	long bytes;
	char array[BUFFER_SIZE];
	
	CoreFile *f = Services()->getCore()->openFile(fileName.c_str(), "rb");
	if(!f) {
        Logger::log("Error loading OGG file!\n");
        return false;
	}
	vorbis_info *pInfo;
	OggVorbis_File oggFile;	
	
	ov_callbacks callbacks;
	callbacks.read_func = custom_readfunc;
	callbacks.seek_func = custom_seekfunc;
	callbacks.close_func = custom_closefunc;
	callbacks.tell_func = custom_tellfunc;
	
	ov_open_callbacks( (void*)f, &oggFile, NULL, 0, callbacks);
	pInfo = ov_info(&oggFile, -1);

	do {
		bytes = ov_read(&oggFile, array, BUFFER_SIZE, 0, 2, 1, &bitStream);
		data.insert(data.end(), array, array + bytes);
	} while (bytes > 0);
    
    bool retVal = loadBytes(data.data(), data.size(), pInfo->channels, pInfo->rate, SoundFormat16);
	ov_clear(&oggFile);
    return retVal;
#else
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
        Logger::log("LoadWav: Could not load wav from " + fileName);
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
