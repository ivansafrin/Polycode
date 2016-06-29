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

OpenSLAudioInterface::OpenSLAudioInterface(){}

OpenSLAudioInterface::~OpenSLAudioInterface(){
	terminateOpenSL();
}

void OpenSLAudioInterface::setMixer(AudioMixer* newMixer){
	mixer = newMixer;
	initOpenSL();
}

void OpenSLAudioInterface::initOpenSL(){
	SLresult lRes;
	
	const SLInterfaceID lEngineMixIIDs[]={SL_IID_ENGINE};
	const SLboolean lEngineMixReqs[]={SL_BOOLEAN_TRUE};
	const SLuint32 lOutputMixIIDCount=0;
	const SLInterfaceID lOutputMixIIDs[]={};
	const SLboolean lOutputMixReqs[]={};
 
	lRes = slCreateEngine(&mEngineObj, 0, NULL, 1, lEngineMixIIDs, lEngineMixReqs);
	lRes = (*mEngineObj)->Realize(mEngineObj,SL_BOOLEAN_FALSE);
	lRes = (*mEngineObj)->GetInterface(mEngineObj, SL_IID_ENGINE, &mEngine);
	
	lRes=(*mEngine)->CreateOutputMix(mEngine, &mOutputMixObj,lOutputMixIIDCount,lOutputMixIIDs, lOutputMixReqs);
	lRes=(*mOutputMixObj)->Realize(mOutputMixObj, SL_BOOLEAN_FALSE);
	
	SLDataLocator_AndroidSimpleBufferQueue lDataLocatorIn;
	lDataLocatorIn.locatorType = SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE;
	lDataLocatorIn.numBuffers = 1;
	
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
	
	lRes = (*mEngine)->CreateAudioPlayer(mEngine, &mPlayerObj, &lDataSource, &lDataSink, lSoundPlayerIIDCount, lSoundPlayerIIDs, lSoundPlayerReqs);
	lRes = (*mPlayerObj)->Realize(mPlayerObj, SL_BOOLEAN_FALSE);
	
	lRes = (*mPlayerObj)->GetInterface(mPlayerObj, SL_IID_PLAY, &mPlayer);
	lRes = (*mPlayerObj)->GetInterface(mPlayerObj, SL_IID_ANDROIDSIMPLEBUFFERQUEUE, &mPlayerQueue);
	
	lRes = (*mPlayerQueue)->RegisterCallback(mPlayerQueue, OpenSLAudioInterface::queueCallback, this);
	
// 	lRes = (*mPlayerObj)->GetInterface(mPlayerObj, SL_IID_VOLUME, &mVolume);
	
	lRes = (*mPlayer)->SetPlayState(mPlayer, SL_PLAYSTATE_PLAYING);
	
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
	if(audioInterface->buffer && audioInterface->getMixer() && !Services()->getCore()->paused) {
		int16_t *out = (int16_t*)audioInterface->buffer;
		audioInterface->getMixer()->mixIntoBuffer(out, POLY_FRAMES_PER_BUFFER);
		(*(audioInterface->mPlayerQueue))->Enqueue(audioInterface->mPlayerQueue, out, sizeof(int16_t)*POLY_FRAMES_PER_BUFFER*POLY_NUM_CHANNELS);
	}
}