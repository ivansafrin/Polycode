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
		UIHScrollBar(float width, float height, float initialRatio);
		~UIHScrollBar();
		
		void Update();
		float getScrollValue();
		void handleEvent(Event *event);
		
		float minHandleSize;
		
		void setHandleRatio(float newRatio);
		
	private:		
		
		
		float padding;
		float scrollValue;
		float lastPositionX;
		float scrollHandleWidth;	
		float dragRectWidth;
		
		UIBox *bgBox;
		UIBox *handleBox;
	};	
}