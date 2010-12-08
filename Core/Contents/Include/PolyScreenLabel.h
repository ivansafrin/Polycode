/*
 *  PolyScreenLabel.h
 *  TAU
 *
 *  Created by Ivan Safrin on 3/16/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

// @package Screen

#pragma once

#include "PolyGlobals.h"
#include "PolyCoreServices.h"
#include "PolyScreenShape.h"
#include "PolyScreenImage.h"
#include "PolyFont.h"
#include "PolyLabel.h"
#include "PolyTexture.h"
#include "PolyPolygon.h"
#include "PolyMesh.h"

#include <string>
using std::string;
using std::wstring;

namespace Polycode {

	class _PolyExport ScreenLabel : public ScreenShape {
		public:
			
			ScreenLabel(string fontName, wstring text, int size, int amode);
			~ScreenLabel();		
		
			void addDropShadow(Color color, float size, float offsetX, float offsetY);
			void setText(wstring newText);
			wstring getText();
		
			Label *getLabel();
			
		protected:
			
			Label *label;
			ScreenImage *dropShadowImage;
	};
}