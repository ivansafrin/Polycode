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
		
		void setPosition(float x, float y);
		void setScale(float x, float y);
		void setRotation(float roatation);
		float getRotation();
			
		bool _onMouseDown(float x, float y, int timestamp);
		bool _onMouseUp(float x, float y, int timestamp);
		void _onMouseMove(float x, float y, int timestamp);
		void _onMouseWheelUp(float x, float y, int timestamp);
		void _onMouseWheelDown(float x, float y, int timestamp);
	
		virtual void onMouseDown(float x, float y){}
		virtual void onMouseUp(float x, float y){}
		virtual	void onMouseMove(float x, float y){}
		virtual void onMouseWheelUp(float x, float y) {}
		virtual void onMouseWheelDown(float x, float y) {}
	
		void _onKeyDown(TAUKey key, wchar_t charCode);	
		void _onKeyUp(TAUKey key, wchar_t charCode);	
		
		virtual void onKeyDown(TAUKey key, wchar_t charCode){}
		virtual void onKeyUp(TAUKey key, wchar_t charCode){}
		
		bool hitTest(float x, float y);		
	
		Matrix4 buildPositionMatrix();
		void adjustMatrixForChildren();

		float getWidth();
		float getHeight();
	
		void setWidth(float w) { width = w; hitwidth = w; }
		void setHeight(float h) { height = h; hitheight = h; }
	
		virtual void onGainFocus(){}
		virtual void onLoseFocus(){}		
		
		void startDrag(float xOffset, float yOffset);
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
		float dragOffsetX;
		float dragOffsetY;
		
		bool mouseOver;
		float width;
		float height;

		float hitwidth;
		float hitheight;
		
		float xmouse;
		float ymouse;
		
		int positionMode;		
		Rectangle *dragLimits;
		
		int lastClickTicks;
		ScreenEntity *focusedChild;

};

}
