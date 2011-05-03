/*
 *  PolyScreenLabel.h
 *  Poly
 *
 *  Created by Ivan Safrin on 3/16/08.
 *  Copyright 2008 Ivan Safrin. All rights reserved.
 *
 */

// @package Screen

#pragma once
#include "PolyString.h"
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
			
			ScreenLabel(String fontName, String text, int size, int amode);
			~ScreenLabel();		
		
			void addDropShadow(Color color, Number size, Number offsetX, Number offsetY);
			void setText(String newText);
			String getText();
		
			Label *getLabel();
			
		protected:
			
			Label *label;
			ScreenImage *dropShadowImage;
	};
}