/*
Copyright (C) 2011 by Ivan Safrin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/


#pragma once
#include "PolyGlobals.h"
#include "PolyVector2.h"
#include "PolyMatrix4.h"
#include "PolyRectangle.h"
#include "PolyInputKeys.h"
#include "PolyEntity.h"
#include "PolyEventDispatcher.h"

namespace Polycode {

/**
* 2D Entity base. The ScreenEntity is the base class for all 2D elements in Polycode. They can be added to a screen or to other ScreenEntities and are rendered automatically. If you want to create custom screen objects, subclass this. ScreenEntity subclasses Entity, which use 3d positioning and tranformation, but provides some 2d-only versions of the transformation functions for convenience.
*/
class _PolyExport ScreenEntity : public Entity, public EventDispatcher {
		
	public:
		using Entity::setPosition;		
		using Entity::setScale;		
	
		ScreenEntity();
		virtual ~ScreenEntity();
		
		
		void addEntity(Entity *newChild);
		
		/**
		* Set 2d position.
		* @param x Horizontal position.
		* @param y Vertical position.
		*/
		void setPosition(Number x, Number y);

		/**
		* Set 2d position.
		* @param v New 2D position vector.
		*/
		void setPosition(const Vector2 &v);

		
		/**
		* Set 2d scale.
		* @param x Horizontal scale.
		* @param y Vertical scale.
		*/		
		void setScale(Number x, Number y);
		
		/**
		* Set 2d scale.
		* @param v New 2D scale vector.
		*/
		void setScale(const Vector2 &v);
		
		
		/**
		* Set 2d rotation.
		* @param rotation New rotation value in degrees.
		*/				
		void setRotation(Number rotation);
		
		/**
		* Returns current rotation.
		* @return Current rotation value.
		*/						
		Number getRotation() const;
			
		bool _onMouseDown(Number x, Number y, int mouseButton, int timestamp, Vector2 parentAdjust = Vector2(0,0));
		bool _onMouseUp(Number x, Number y, int mouseButton, int timestamp, Vector2 parentAdjust = Vector2(0,0));
		void _onMouseMove(Number x, Number y, int timestamp, Vector2 parentAdjust = Vector2(0,0));
		void _onMouseWheelUp(Number x, Number y, int timestamp, Vector2 parentAdjust = Vector2(0,0));
		void _onMouseWheelDown(Number x, Number y, int timestamp, Vector2 parentAdjust = Vector2(0,0));
	
		virtual void onMouseDown(Number x, Number y){}
		virtual void onMouseUp(Number x, Number y){}
		virtual	void onMouseMove(Number x, Number y){}
		virtual void onMouseWheelUp(Number x, Number y) {}
		virtual void onMouseWheelDown(Number x, Number y) {}
	
		void _onKeyDown(PolyKEY key, wchar_t charCode);	
		void _onKeyUp(PolyKEY key, wchar_t charCode);	
		
		Matrix4 getScreenConcatenatedMatrix();
		
		virtual void onKeyDown(PolyKEY key, wchar_t charCode){}
		virtual void onKeyUp(PolyKEY key, wchar_t charCode){}
		
		bool hitTest(Number x, Number y);
	
		Matrix4 buildPositionMatrix();
		void adjustMatrixForChildren();
		
		/**
		* Returns the width of the screen entity.
		* @return Height of the screen entity.
		*/									
		Number getWidth() const;
		
		/**
		* Returns the height of the screen entity.
		*/											
		Number getHeight() const;
	
		/**
		* Sets the width of the screen entity.
		* @param w New height value.
		*/									
		void setWidth(Number w) { width = w; hit.w = w; hit.x = -w/2; }
		
		/**
		* Sets the height of the screen entity.
		* @param h New height value.
		*/									
		void setHeight(Number h) { height = h; hit.h = h; hit.y = -h/2; }
	
		virtual void onGainFocus(){}
		virtual void onLoseFocus(){}		
		
		void startDrag(Number xOffset, Number yOffset);
		void stopDrag();
				
		void setBlendingMode(int newBlendingMode);
		
		/** 
		* Changes the positioning mode of the screen entity.		
		
		If the positioning mode is ScreenEntity::POSITION_TOPLEFT, the entity is translated by half its width and half its height when it's rendered, making all other transformations relative to its top-left cornder.instead of the center.		
		If the mode is ScreenEntity::POSITION_CENTER, the entity is rendered as is.
		Set to POSITION_CENTER by default.
		@param newPositionMode The new positioning mode.
		*/
		void setPositionMode(int newPositionMode);
		
		int getPositionMode();
		
		void setDragLimits(Rectangle rect);
		void clearDragLimits();
		
		void setDefaultScreenOptions(bool snapToPixels);
		
		void focusChild(ScreenEntity *child);
		void focusNextChild();
	
		Vector2 getPosition2D() const;
		Vector2 getScreenPosition() const;
		
		static const int POSITION_TOPLEFT = 0;
		static const int POSITION_CENTER = 1;

		bool isFocusable() const;
		
		bool hasFocus;
		bool blockMouseInput;
		int zindex;	
	
		/**
		* If this option is true, the screen entity's positions will be roudnded to whole pixels. This only works if the screen is using pixel coordinates.
		*/
		bool snapToPixels;
		bool processInputEvents;

		Rectangle getHitbox();
		void setHitbox(Number width, Number height);
		void setHitbox(Number width, Number height, Number left, Number top);

	protected:
	
		bool focusable;
		bool focusChildren;
		
		bool isDragged;
		Number dragOffsetX;
		Number dragOffsetY;
		
		bool mouseOver;
		Number width;
		Number height;

		Rectangle hit;
		
		Number xmouse;
		Number ymouse;
		
		int positionMode;		
		Rectangle *dragLimits;
		
		int lastClickTicks;
		ScreenEntity *focusedChild;

};

}
