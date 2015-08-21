
/*
 Copyright (C) 2015 by Ivan Safrin
 
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

#include "polycode/core/PolyPAAudioInterface.h"
#include "polycode/core/PolyLogger.h"

using namespace Polycode;

PAAudioInterface::PAAudioInterface() {
    
    
    PaError error = Pa_Initialize();
    if(error != paNoError) {
        String portAudioError = Pa_GetErrorText(error);
        Logger::log("Error initializing PortAudio interface:"+portAudioError+"\n");
    }
    
    error = Pa_OpenDefaultStream( &stream,
                               0,
                               POLY_NUM_CHANNELS,
                               paInt16,
                               POLY_AUDIO_FREQ,
                               POLY_FRAMES_PER_BUFFER,
                               PAAudioInterface::paCallback,
                               this);
    if( error != paNoError ) {
        String portAudioError = Pa_GetErrorText(error);
        Logger::log("Error opening PortAudio stream:"+portAudioError+"\n");
    }
    
    error = Pa_StartStream(stream);
    if( error != paNoError ) {
        String portAudioError = Pa_GetErrorText(error);
        Logger::log("Error starting PortAudio stream:"+portAudioError+"\n");
    }
}

PAAudioInterface::~PAAudioInterface() {
    PaError error;
    
    error = Pa_CloseStream( stream );
    if(error != paNoError)  {
        String portAudioError = Pa_GetErrorText(error);
        Logger::log("Error terminating PortAudio stream:"+portAudioError+"\n");
    }
    
    error = Pa_Terminate();
    if(error != paNoError) {
        String portAudioError = Pa_GetErrorText(error);
        Logger::log("Error terminating PortAudio interface:"+portAudioError+"\n");
    }
}

int PAAudioInterface::paCallback(const void *inputBuffer, void *outputBuffer,
                      unsigned long framesPerBuffer,
                      const PaStreamCallbackTimeInfo* timeInfo,
                      PaStreamCallbackFlags statusFlags,
                                 void *userData) {
    PAAudioInterface *audioInterface = (PAAudioInterface*) userData;
    if(outputBuffer) {
        int16_t *out = (int16_t*)outputBuffer;
        audioInterface->getMixer()->mixIntoBuffer(out, framesPerBuffer);
    }
    return 0;
}
