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
		UIVScrollBar(float width, float height, float initialRatio);
		~UIVScrollBar();
		
		void Update();
		float getScrollValue();
		void handleEvent(Event *event);
		
		void Resize(int newHeight);
		
		void onMouseWheelDown(float x, float y);
		void onMouseWheelUp(float x, float y);
		
		void scrollUpOneTick();
		void scrollDownOneTick();
		
		float minHandleSize;
		
		void setHandleRatio(float newRatio);

		
	private:		
		
		
		float padding;
		float scrollValue;
		float lastPositionY;
		float scrollHandleHeight;	
		float dragRectHeight;
		
		UIBox *bgBox;
		UIBox *handleBox;
	};
	
}