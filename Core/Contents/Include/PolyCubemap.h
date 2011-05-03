/*
 *  PolyCubemap.h
 *  Poly
 *
 *  Created by Ivan Safrin on 9/9/09.
 *  Copyright 2009 Ivan Safrin. All rights reserved.
 *
 */

// @package Materials

#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolyResource.h"
#include "PolyTexture.h"

namespace Polycode {
	
	class _PolyExport Cubemap : public Resource {
		public:
			Cubemap(Texture *t0, Texture *t1, Texture *t2, Texture *t3, Texture *t4, Texture *t5);
			~Cubemap();	
		
		protected:		
		
	};
}