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
#include "PolyString.h"
#include "PolyLogger.h"
#include "PolyGlobals.h"
#include <stdio.h>
#include "AL/al.h"
#include "AL/alc.h"
#include "PolyVector3.h"

namespace Polycode {
	
	/**
	* Controls global sound settings.
	*/
	class _PolyExport SoundManager {
	public:
		SoundManager();
		~SoundManager();
		
		void setListenerPosition(Vector3 position);
		void setListenerOrientation(Vector3 orientation);	
		void initAL();
		
		/**
		* Sets the global sound volume.
		*/ 
		void setGlobalVolume(Number globalVolume);
		
		
	private:
		
		ALCdevice* device;
		ALCcontext* context;		
	};
}
