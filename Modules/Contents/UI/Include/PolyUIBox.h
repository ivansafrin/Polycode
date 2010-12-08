/*
 *  PolyUIBox.h
 *  Poly
 *
 *  Created by Ivan Safrin on 3/16/10.
 *  Copyright 2010 Ivan Safrin. All rights reserved.
 *
 */

// @package UI

#pragma once
#include "PolyGlobals.h"
#include "PolyScreenImage.h"
#include "PolyScreenEntity.h"

namespace Polycode {
	
	class _PolyExport UIBox : public ScreenEntity {
	public:
		UIBox(string imageFile, float t, float r, float b, float l, float boxWidth, float boxHeight);
		~UIBox();
		
		void resizeBox(float newWidth, float newHeight);		
		
	private:
				
		float t;
		float r;
		float b;
		float l;
		
		ScreenImage *tlImage;
		ScreenImage *trImage;		
		ScreenImage *blImage;		
		ScreenImage *brImage;			
		
		ScreenImage *centerImage;
		
		ScreenImage *tImage;
		ScreenImage *rImage;
		ScreenImage *bImage;
		ScreenImage *lImage;		
	};
}