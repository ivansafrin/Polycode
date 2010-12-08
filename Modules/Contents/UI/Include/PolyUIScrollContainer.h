/*
 *  PolyUIScrollContainer.h
 *  Poly
 *
 *  Created by Ivan Safrin on 3/25/10.
 *  Copyright 2010 Ivan Safrin. All rights reserved.
 *
 */

// @package UI

#pragma once
#include "PolyGlobals.h"
#include "PolyUIVScrollBar.h"
#include "PolyUIHScrollBar.h"

namespace Polycode {
	
	class _PolyExport UIScrollContainer : public ScreenEntity {
	public:
		UIScrollContainer(ScreenEntity *scrolledEntity, bool hScroll, bool vScroll, float width, float height);
		~UIScrollContainer();
		
		void setContentSize(float newContentWidth, float newContentHeight);
		
		void Resize(int x, int y);
		
		void onMouseWheelDown(float x, float y);
		void onMouseWheelUp(float x, float y);		
		
		void handleEvent(Event *event);
		
	private:		
		
		float defaultScrollSize;
		
		float contentWidth;
		float contentHeight;
		
		ScreenEntity *scrollChild;		
		ScreenShape *maskShape;		
		
		bool hasHScroll;
		bool hasVScroll;
		
		UIVScrollBar *vScrollBar;
		UIHScrollBar *hScrollBar;
	};
	
}