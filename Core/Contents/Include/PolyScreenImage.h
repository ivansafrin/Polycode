/*
 *  PolyScreenImage.h
 *  Poly
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
		
		void setImageCoordinates(Number x, Number y, Number width, Number height);
		Number getImageWidth();
		Number getImageHeight();
		
		private:

		Number imageWidth;
		Number imageHeight;
		
	};

}