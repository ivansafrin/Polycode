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
		UIScrollContainer(ScreenEntity *scrolledEntity, bool hScroll, bool vScroll, Number width, Number height);
		~UIScrollContainer();
		
		void setContentSize(Number newContentWidth, Number newContentHeight);
		
		void Resize(int x, int y);
		
		void onMouseWheelDown(Number x, Number y);
		void onMouseWheelUp(Number x, Number y);		
		
		void handleEvent(Event *event);
		
	private:		
		
		Number defaultScrollSize;
		
		Number contentWidth;
		Number contentHeight;
		
		ScreenEntity *scrollChild;		
		ScreenShape *maskShape;		
		
		bool hasHScroll;
		bool hasVScroll;
		
		UIVScrollBar *vScrollBar;
		UIHScrollBar *hScrollBar;
	};
	
}