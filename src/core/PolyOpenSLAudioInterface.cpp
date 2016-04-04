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

#include "polycode/core/PolyOpenSLAudioInterface.h"
#include "polycode/core/PolyCore.h"
#include "polycode/core/PolyLogger.h"
#include <unistd.h>

using namespace Polycode;

OpenSLAudioInterface::OpenSLAudioInterface(){
	Logger::log("OpenSL Interface");
	stream = new OpenSLStream();
}

OpenSLAudioInterface::~OpenSLAudioInterface(){ }

void OpenSLAudioInterface::setMixer(AudioMixer* newMixer){
	Logger::log("OpenSL setMixer");
	mixer = newMixer;
	stream->setMixer(mixer);
	Logger::log("OpenSL setMixer2");
	Services()->getCore()->createThread(stream);
	Logger::log("OpenSL setMixer3");
}

OpenSLStream::OpenSLStream(){
	streamMutex = NULL;
}

OpenSLStream::~OpenSLStream(){

}

void OpenSLStream::initOpenSL(){
	SLresult result;
	//create Engine
	Logger::log("OpenSL init");
	slCreateEngine(&engineObject, 0, NULL, 0, NULL, NULL);
	(*engineObject)->Realize(engineObject, SL_BOOLEAN_FALSE);
	(*engineObject)->GetInterface(engineObject, SL_IID_ENGINE, &engineEngine);
	
	//init output
	const SLInterfaceID ids[] = {SL_IID_VOLUME};
	const SLboolean req[] = {SL_BOOLEAN_FALSE};
	Logger::log("OpenSL before outputMixObject %d", result);
	result = (*engineEngine)->CreateOutputMix(engineEngine, &outputMixObject, 0, NULL, NULL);
	Logger::log("OpenSL create outputMixObject %d", result);
	result = (*outputMixObject)->Realize(outputMixObject, SL_BOOLEAN_FALSE);
	Logger::log("OpenSL realize outputMixObject %d", result);
	//some options
	SLDataLocator_AndroidSimpleBufferQueue loc_bufq = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2};
	
	int speakers;
    if(POLY_NUM_CHANNELS > 1) 
		speakers = SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT;
    else
		speakers = SL_SPEAKER_FRONT_CENTER;
	
	SLDataFormat_PCM format_pcm = {SL_DATAFORMAT_PCM,POLY_NUM_CHANNELS,POLY_AUDIO_FREQ*1000,
               SL_PCMSAMPLEFORMAT_FIXED_16, SL_PCMSAMPLEFORMAT_FIXED_16,
               speakers, SL_BYTEORDER_LITTLEENDIAN};

	SLDataSource audioSrc = {&loc_bufq, &format_pcm};
		
	SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX,outputMixObject};
	SLDataSink audioSnk = {&loc_outmix, NULL};
	
	const SLInterfaceID ids1[] = {SL_IID_ANDROIDSIMPLEBUFFERQUEUE};
	const SLboolean req1[] = {SL_BOOLEAN_TRUE};
	
	//init audio player
	Logger::log("OpenSL before AudioPlayer");
	result = (*engineEngine)->CreateAudioPlayer(engineEngine, &bqPlayerObject, &audioSrc, &audioSnk, 1, ids1, req1);
	if(result != SL_RESULT_SUCCESS){
		Logger::log("OpenSL create failed %d", result);
			return;
	}
	Logger::log("OpenSL create AudioPlayer");
	(*bqPlayerObject)->Realize(bqPlayerObject, SL_BOOLEAN_FALSE);
	if (result != SL_RESULT_SUCCESS){
		Logger::log("OpenSL realize failed %d", result);
		return;
	}
	Logger::log("OpenSL realize AudioPlayer");
	
	Logger::log("OpenSL before PLAY");
	(*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_PLAY, &bqPlayerPlay);
	Logger::log("OpenSL before buffer");
	(*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_ANDROIDSIMPLEBUFFERQUEUE, &bqPlayerBufferQueue);
	Logger::log("OpenSL before callback");
	(*bqPlayerBufferQueue)->RegisterCallback(bqPlayerBufferQueue,bqPlayerCallback, this);
	Logger::log("OpenSL after callback");
	
	Logger::log("OpenSL Play");
	result = (*bqPlayerPlay)->SetPlayState(bqPlayerPlay, SL_PLAYSTATE_PLAYING);
	Logger::log("OpenSL init finished %d", result);
}

void OpenSLStream::terminateOpenSL(){
	if (bqPlayerObject != NULL) {
		(*bqPlayerObject)->Destroy(bqPlayerObject);
	}

	if (outputMixObject != NULL) {
		(*outputMixObject)->Destroy(outputMixObject);
	}

	if (engineObject != NULL) {
		(*engineObject)->Destroy(engineObject);
	}
}


void OpenSLStream::setMixer(AudioMixer* newMixer){
	Logger::log("OpenSL StreamMixer");
	if(!streamMutex){
		streamMutex = Services()->getCore()->createMutex();
		Logger::log("OpenSL mutexcreated");
	}
		
	streamMutex->lock();
	mixer = newMixer;
	streamMutex->unlock();
	Logger::log("OpenSL StreamMixer2");
}

void OpenSLStream::runThread(){
	Logger::log("OpenSL runThread");
	
// 	while(!core->isWindowInitialized()){
// 		usleep(1000000);
// 	}
	
	initOpenSL();
	playBuffer = (int16_t*)calloc(POLY_FRAMES_PER_BUFFER * POLY_NUM_CHANNELS, sizeof(int16_t));
	backBuffer = (int16_t*)calloc(POLY_FRAMES_PER_BUFFER * POLY_NUM_CHANNELS, sizeof(int16_t));
	Logger::log("OpenSL before While");
	while(threadRunning){
		Logger::log("OpenSL while");
		streamMutex->lock();
		if(swappedBuffers){
			mixer->mixIntoBuffer(backBuffer, POLY_FRAMES_PER_BUFFER);
			swappedBuffers = false;
		}
		streamMutex->unlock();
	}
	Logger::log("OpenSL after While");
	terminateOpenSL();
	free(playBuffer);
	free(backBuffer);
}

void OpenSLStream::bqPlayerCallback(SLAndroidSimpleBufferQueueItf bq, void* context){
	OpenSLStream *ctx = (OpenSLStream *) context;
	int bytes = POLY_FRAMES_PER_BUFFER*POLY_NUM_CHANNELS*sizeof(int16_t);
 	ctx->swapBuffers();
	(*ctx->bqPlayerBufferQueue)->Enqueue(ctx->bqPlayerBufferQueue,ctx->playBuffer,bytes);
}

void OpenSLStream::swapBuffers(){
	streamMutex->lock();
	int16_t *tmpBuf;
	tmpBuf = playBuffer;
	playBuffer = backBuffer;
	backBuffer = tmpBuf;
	swappedBuffers = true;
	streamMutex->unlock();
}
