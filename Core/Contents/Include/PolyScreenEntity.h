/*
 *  PolyScreenEntity.h
 *  TAU
 *
 *  Created by Ivan Safrin on 3/13/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

// @package Screen

#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolyVector2.h"
#include "PolyInputEvent.h"
#include "PolyEventDispatcher.h"
#include "PolyRectangle.h"
#include "PolyEntity.h"


namespace Polycode {

	
class _PolyExport ScreenEntity : public Entity, public EventDispatcher {
		
	public:
		using Entity::setPosition;		
		using Entity::setScale;		
	
		ScreenEntity();
		~ScreenEntity();
		
		void setPosition(Number x, Number y);
		void setScale(Number x, Number y);
		void setRotation(Number roatation);
		Number getRotation();
			
		bool _onMouseDown(Number x, Number y, int mouseButton, int timestamp);
		bool _onMouseUp(Number x, Number y, int mouseButton, int timestamp);
		void _onMouseMove(Number x, Number y, int timestamp);
		void _onMouseWheelUp(Number x, Number y, int timestamp);
		void _onMouseWheelDown(Number x, Number y, int timestamp);
	
		virtual void onMouseDown(Number x, Number y){}
		virtual void onMouseUp(Number x, Number y){}
		virtual	void onMouseMove(Number x, Number y){}
		virtual void onMouseWheelUp(Number x, Number y) {}
		virtual void onMouseWheelDown(Number x, Number y) {}
	
		void _onKeyDown(TAUKey key, wchar_t charCode);	
		void _onKeyUp(TAUKey key, wchar_t charCode);	
		
		virtual void onKeyDown(TAUKey key, wchar_t charCode){}
		virtual void onKeyUp(TAUKey key, wchar_t charCode){}
		
		bool hitTest(Number x, Number y);		
	
		Matrix4 buildPositionMatrix();
		void adjustMatrixForChildren();

		Number getWidth();
		Number getHeight();
	
		void setWidth(Number w) { width = w; hitwidth = w; }
		void setHeight(Number h) { height = h; hitheight = h; }
	
		virtual void onGainFocus(){}
		virtual void onLoseFocus(){}		
		
		void startDrag(Number xOffset, Number yOffset);
		void stopDrag();
				
		void setBlendingMode(int newBlendingMode);
		void setPositionMode(int newPositionMode);
		
		void setDragLimits(Rectangle rect);
		void clearDragLimits();
		
		void focusChild(ScreenEntity *child);
		void focusNextChild();
	
		Vector2 getPosition2D();
		
		static const int POSITION_TOPLEFT = 0;
		static const int POSITION_CENTER = 1;

		bool isFocusable();
		
		bool hasFocus;
		bool blockMouseInput;
		int zindex;	
	
		bool snapToPixels;


	protected:
	
		bool focusable;
		bool focusChildren;
		
		bool isDragged;
		Number dragOffsetX;
		Number dragOffsetY;
		
		bool mouseOver;
		Number width;
		Number height;

		Number hitwidth;
		Number hitheight;
		
		Number xmouse;
		Number ymouse;
		
		int positionMode;		
		Rectangle *dragLimits;
		
		int lastClickTicks;
		ScreenEntity *focusedChild;

};

}
