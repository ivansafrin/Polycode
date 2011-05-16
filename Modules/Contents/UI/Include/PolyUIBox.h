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
		UIBox(String imageFile, Number t, Number r, Number b, Number l, Number boxWidth, Number boxHeight);
		~UIBox();
		
		void resizeBox(Number newWidth, Number newHeight);		
		
	private:
				
		Number t;
		Number r;
		Number b;
		Number l;
		
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