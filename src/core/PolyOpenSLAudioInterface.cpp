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
// 	stream = new OpenSLStream();
}

OpenSLAudioInterface::~OpenSLAudioInterface(){
	terminateOpenSL();
}

void OpenSLAudioInterface::setMixer(AudioMixer* newMixer){
	mixer = newMixer;
	initOpenSL();
// 	Logger::log("finished init");
// 	stream->setInterface(this);
// 	Logger::log("stream set");
// // 	Services()->getCore()->createThread(stream);
// 	Logger::log("stream running");
}

void OpenSLAudioInterface::initOpenSL(){
	SLresult lRes;
	
	const SLInterfaceID lEngineMixIIDs[]={SL_IID_ENGINE};
	const SLboolean lEngineMixReqs[]={SL_BOOLEAN_TRUE};
	const SLuint32 lOutputMixIIDCount=0;
	const SLInterfaceID lOutputMixIIDs[]={};
	const SLboolean lOutputMixReqs[]={};
 
	lRes = slCreateEngine(&mEngineObj, 0, NULL, 1, lEngineMixIIDs, lEngineMixReqs);
	Logger::log("engine: %d", lRes);
	lRes = (*mEngineObj)->Realize(mEngineObj,SL_BOOLEAN_FALSE);
	Logger::log("engine real: %d", lRes);
	lRes = (*mEngineObj)->GetInterface(mEngineObj, SL_IID_ENGINE, &mEngine);
	Logger::log("engine int: %d", lRes);
	
	lRes=(*mEngine)->CreateOutputMix(mEngine, &mOutputMixObj,lOutputMixIIDCount,lOutputMixIIDs, lOutputMixReqs);
	lRes=(*mOutputMixObj)->Realize(mOutputMixObj, SL_BOOLEAN_FALSE);
	
	SLDataLocator_AndroidSimpleBufferQueue lDataLocatorIn;
	lDataLocatorIn.locatorType = SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE;
	lDataLocatorIn.numBuffers = POLY_CIRCULAR_BUFFER_SIZE;
	
	SLDataFormat_PCM lDataFormat;
	lDataFormat.formatType = SL_DATAFORMAT_PCM;
	lDataFormat.numChannels = POLY_NUM_CHANNELS;
	lDataFormat.samplesPerSec = POLY_AUDIO_FREQ*1000;
	lDataFormat.bitsPerSample = SL_PCMSAMPLEFORMAT_FIXED_16;
	lDataFormat.containerSize = SL_PCMSAMPLEFORMAT_FIXED_16;
	if(POLY_NUM_CHANNELS > 1){
		lDataFormat.channelMask = SL_SPEAKER_FRONT_RIGHT | SL_SPEAKER_FRONT_LEFT;
	} else {
		lDataFormat.channelMask = SL_SPEAKER_FRONT_CENTER;
	}
	lDataFormat.endianness = SL_BYTEORDER_LITTLEENDIAN;
	
	SLDataSource lDataSource;
	lDataSource.pLocator = &lDataLocatorIn;
	lDataSource.pFormat = &lDataFormat;
	
	SLDataLocator_OutputMix lDataLocatorOut;
	lDataLocatorOut.locatorType = SL_DATALOCATOR_OUTPUTMIX;
	lDataLocatorOut.outputMix = mOutputMixObj;
	
	SLDataSink lDataSink;
	lDataSink.pLocator = &lDataLocatorOut;
	lDataSink.pFormat = NULL;
	
	const SLuint32 lSoundPlayerIIDCount = 2;
	const SLInterfaceID lSoundPlayerIIDs[] = { SL_IID_PLAY, SL_IID_ANDROIDSIMPLEBUFFERQUEUE };
	const SLboolean lSoundPlayerReqs[] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };
	
	Logger::log("before player");
	lRes = (*mEngine)->CreateAudioPlayer(mEngine, &mPlayerObj, &lDataSource, &lDataSink, lSoundPlayerIIDCount, lSoundPlayerIIDs, lSoundPlayerReqs);
	Logger::log("player: %d", lRes);
	lRes = (*mPlayerObj)->Realize(mPlayerObj, SL_BOOLEAN_FALSE);
	Logger::log("player real: %d", lRes);
	
	lRes = (*mPlayerObj)->GetInterface(mPlayerObj, SL_IID_PLAY, &mPlayer);
	Logger::log("player getI: %d", lRes);
	lRes = (*mPlayerObj)->GetInterface(mPlayerObj, SL_IID_ANDROIDSIMPLEBUFFERQUEUE, &mPlayerQueue);
	Logger::log("player getBuffer: %d", lRes);
	
	lRes = (*mPlayerQueue)->RegisterCallback(mPlayerQueue, OpenSLAudioInterface::queueCallback, this);
	Logger::log("queue call: %d", lRes);
	
// 	lRes = (*mPlayerObj)->GetInterface(mPlayerObj, SL_IID_VOLUME, &mVolume);
// 	Logger::log("player itf: %d", lRes);
	
	lRes = (*mPlayer)->SetPlayState(mPlayer, SL_PLAYSTATE_PLAYING);
	Logger::log("play: %d", lRes);
	
	buffer = (int16_t*)malloc(sizeof(int16_t)*POLY_FRAMES_PER_BUFFER*POLY_NUM_CHANNELS);
	int16_t *out = buffer;
	mixer->mixIntoBuffer(out, POLY_FRAMES_PER_BUFFER);
	(*(mPlayerQueue))->Enqueue(mPlayerQueue, out, POLY_FRAMES_PER_BUFFER);
}

void OpenSLAudioInterface::terminateOpenSL(){
	if (mPlayerObj != NULL) {
		(*mPlayerObj)->Destroy(mPlayerObj);
	}

	if (mOutputMixObj != NULL) {
		(*mOutputMixObj)->Destroy(mOutputMixObj);
	}
 
	if (mEngineObj != NULL) {
		(*mEngineObj)->Destroy(mEngineObj);
	}
}

void OpenSLAudioInterface::queueCallback(SLAndroidSimpleBufferQueueItf caller, void* pContext){
	OpenSLAudioInterface *audioInterface = (OpenSLAudioInterface*) pContext;
	if(audioInterface->buffer && audioInterface->getMixer()) {
		int16_t *out = (int16_t*)audioInterface->buffer;
		audioInterface->getMixer()->mixIntoBuffer(out, POLY_FRAMES_PER_BUFFER);
		(*(audioInterface->mPlayerQueue))->Enqueue(audioInterface->mPlayerQueue, out, POLY_FRAMES_PER_BUFFER);
	}
}

// void OpenSLStream::queueCallback(SLAndroidSimpleBufferQueueItf caller, void* pContext){
// 	OpenSLStream *stream = (OpenSLStream*) pContext;
// 	stream->queueMutex->lock();
// 	Logger::log("callback %d", stream->currentBufferCount);
// 	stream->currentBufferCount--;
// 	stream->queueMutex->unlock();
// }

// OpenSLStream::OpenSLStream() : Threaded(){}

// void OpenSLStream::setInterface(OpenSLAudioInterface* itf){
// 	this->itf = itf;
// 	queueMutex = Services()->getCore()->createMutex();
// }

// void OpenSLStream::runThread(){
// 	int16_t *buffer;
// 	Logger::log("in run");
// 	buffer = (int16_t*)malloc(POLY_MIX_BUFFER_SIZE*POLY_NUM_CHANNELS*sizeof(int16_t));
// 	Logger::log("allocated");
// 	currentBufferCount = 0;
// 	while(threadRunning){
// // 		Logger::log("while");
// 		updateThread(buffer);
// // 		usleep(20000000);
// 	}
// }
// 
// void OpenSLStream::updateThread(int16_t *buf){
// 	Logger::log("in update");
// 	if(itf->getMixer()){
// 		int16_t* out;
// // 		Logger::log("in mixer");
// 		
// 		while(currentBufferCount < POLY_CIRCULAR_BUFFER_SIZE){
// 			queueMutex->lock();
// // 			Logger::log("mix %d", currentBufferCount);
// 			out = buf + sizeof(int16_t)*POLY_FRAMES_PER_BUFFER*POLY_NUM_CHANNELS*currentBufferCount++;
// 			itf->getMixer()->mixIntoBuffer(out, POLY_FRAMES_PER_BUFFER);
// 			(*(itf->mPlayerQueue))->Enqueue(itf->mPlayerQueue, out, POLY_FRAMES_PER_BUFFER);
// 			queueMutex->unlock();
// // 			queueMutex->lock();
// 		}
// // 		queueMutex->unlock();
// // 		Logger::log("unlocked");
// 	}
// }
