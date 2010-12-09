/*
 *  PolySoundManager.h
 *  Poly
 *
 *  Created by Ivan Safrin on 10/12/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
// @package Sound

#pragma once
#include "PolyString.h"
#include "PolyLogger.h"
#include "PolyGlobals.h"
#include <stdio.h>
#include "al.h"
#include "alc.h"

namespace Polycode {
	
	class _PolyExport SoundManager {
	public:
		SoundManager();
		~SoundManager();
		
		void initAL();
		
		
	private:
		
		ALCdevice* device;
		ALCcontext* context;		
	};
}