/*
 *  PolyUIHScrollBar.h
 *  Poly
 *
 *  Created by Ivan Safrin on 3/26/10.
 *  Copyright 2010 Ivan Safrin. All rights reserved.
 *
 */
#pragma once
#include "PolyGlobals.h"
#include "PolyUIBox.h"

namespace Polycode {
	
	class _PolyExport UIHScrollBar : public ScreenEntity {
	public:
		UIHScrollBar(Number width, Number height, Number initialRatio);
		~UIHScrollBar();
		
		void Update();
		Number getScrollValue();
		void handleEvent(Event *event);
		
		Number minHandleSize;
		
		void setHandleRatio(Number newRatio);
		
	private:		
		
		
		Number padding;
		Number scrollValue;
		Number lastPositionX;
		Number scrollHandleWidth;	
		Number dragRectWidth;
		
		UIBox *bgBox;
		UIBox *handleBox;
	};	
}