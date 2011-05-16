/*
 *  PolyUIVScrollBar.h
 *  Poly
 *
 *  Created by Ivan Safrin on 3/25/10.
 *  Copyright 2010 Ivan Safrin. All rights reserved.
 *
 */

#pragma once
#include "PolyGlobals.h"
#include "PolyUIBox.h"

namespace Polycode {
	
	class _PolyExport UIVScrollBar : public ScreenEntity {
	public:
		UIVScrollBar(Number width, Number height, Number initialRatio);
		~UIVScrollBar();
		
		void Update();
		Number getScrollValue();
		void handleEvent(Event *event);
		
		void Resize(int newHeight);
		
		void onMouseWheelDown(Number x, Number y);
		void onMouseWheelUp(Number x, Number y);
		
		void scrollUpOneTick();
		void scrollDownOneTick();
		
		Number minHandleSize;
		
		void setHandleRatio(Number newRatio);

		
	private:		
		
		
		Number padding;
		Number scrollValue;
		Number lastPositionY;
		Number scrollHandleHeight;	
		Number dragRectHeight;
		
		UIBox *bgBox;
		UIBox *handleBox;
	};
	
}