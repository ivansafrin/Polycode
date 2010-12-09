/*
 *  PolyScreenImage.h
 *  TAU
 *
 *  Created by Ivan Safrin on 3/13/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

// @package Screen

#pragma once
#include "PolyString.h"
#include <math.h>
#include "PolyGlobals.h"
#include "PolyScreenShape.h"
#include "PolyCoreServices.h"
#include "PolyImage.h"
#include "PolyMesh.h"
#include "PolyTexture.h"

#include <string>

using std::string;

namespace Polycode {

	class _PolyExport ScreenImage : public ScreenShape {
		public:
		ScreenImage(String fileName);
		ScreenImage(Image *image);		
		~ScreenImage();
		
		void setImageCoordinates(float x, float y, float width, float height);
		float getImageWidth();
		float getImageHeight();
		
		private:

		float imageWidth;
		float imageHeight;
		
	};

}