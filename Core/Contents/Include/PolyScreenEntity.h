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
#include "PolyObject.h"
#include "PolyEventDispatcher.h"

namespace Polycode {

class _PolyExport MouseEventResult {
	public:
		bool hit;
		bool blocked;
};

/**
* 2D Entity base.
*
* The ScreenEntity is the base class for all 2D elements in Polycode. They can be added to a screen or to other ScreenEntities and are rendered automatically. If you want to create custom screen objects, subclass this. ScreenEntity subclasses Entity, which use 3d positioning and tranformation, but provides some 2d-only versions of the transformation functions for convenience.
*/
class _PolyExport ScreenEntity : public Entity {

	public:
		using Entity::setPosition;
		using Entity::setScale;

		ScreenEntity();
		virtual ~ScreenEntity();

		virtual Entity *Clone(bool deepClone, bool ignoreEditorOnly);
		virtual void applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly);

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

		MouseEventResult _onMouseDown(Number x, Number y, int mouseButton, int timestamp, Vector2 parentAdjust = Vector2(0,0));
		MouseEventResult _onMouseUp(Number x, Number y, int mouseButton, int timestamp, Vector2 parentAdjust = Vector2(0,0));
		MouseEventResult _onMouseMove(Number x, Number y, int timestamp, Vector2 parentAdjust = Vector2(0,0));
		MouseEventResult _onMouseWheelUp(Number x, Number y, int timestamp, Vector2 parentAdjust = Vector2(0,0));
		MouseEventResult _onMouseWheelDown(Number x, Number y, int timestamp, Vector2 parentAdjust = Vector2(0,0));

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

		If the positioning mode is ScreenEntity::POSITION_TOPLEFT, the entity is translated by half its width and half its height when it's rendered, making all other transformations relative to its top-left corner instead of the center.
		If the mode is ScreenEntity::POSITION_CENTER, the entity is rendered as is.
		Set to POSITION_CENTER by default.
		@param newPositionMode The new positioning mode.
		*/
		void setPositionMode(int newPositionMode);

		/**
		 * Get the position mode.
		 * @see setPositionMode()
		 */
		int getPositionMode();

		/**
		 * Set a rectangle to which dragging will be restricted.
		 *
		 * Dragging the item past the given rectangle will snap it
		 * back to the edge of the rectangle.
		 *
		 * @param rect The rectangle to restrict dragging to. Uses the
		 *              same positioning mode as `this->position`.
		 */
		void setDragLimits(Rectangle rect);

		/**
		 * Disable restricting where `this` can be dragged.
		 * @see setDragLimits()
		 */
		void clearDragLimits();

		/**
		 * Set options for `this` and all children recursively.
		 *
		 * @param snapToPixels Whether to snap entity positions to pixels before rendering.
		 */
		void setDefaultScreenOptions(bool snapToPixels);

		/*
		 * Make `child` take focus, which will cause certain events
		 * to be sent to it.
		 *
		 * Note that this is a global setting. Only one Entity per
		 * running instance can take focus.
		 */
		void focusChild(ScreenEntity *child);

		/*
		 * Make the next child in `this->children`, after the currently
		 * focused child entity take focus.
		 *
		 * Does nothing if no child of `this` has focus.
		 */
		void focusNextChild();

		/**
		 * @name Child position operations.
		 * 
		 * Move a child in the list of children. Affects display
		 * order of entities(entities further down in the list will
		 * appear on top).
		 */
		//@{
		void moveChildUp(ScreenEntity *child);
		void moveChildDown(ScreenEntity *child);
		void moveChildTop(ScreenEntity *child);
		void moveChildBottom(ScreenEntity *child);
		//}@

		/**
		 * Same semantics as getPosition(), but returns only the x and y coordinates.
		 * 
		 * @see getPosition()
		 * @see getScreenPosition()
		 */
		Vector2 getPosition2D() const;

		/**
		 * Get the position of ScreenEntity in relation to the top-left
		 * corner of the Polycode screen it's on.
		 *
		 * This is unlike getPosition(), which will return the position
		 * of an Entity in relation to its parent Entity.
		 *
		 * @see getPosition()
		 */
		Vector2 getScreenPosition() const;

		/**
		 * Same semantics as getScale(), but returns only the x and y scale.
		 *
		 * @see getScale()
		 */
		Vector2 getScale2D() const;

		/**
		 * Positioning mode in which you specify an entity's topleft corner
		 * as coordinate for placement.
		 */
		static const int POSITION_TOPLEFT = 0;

		/**
		 * Positioning mode in which you specify an entity's center as
		 * coordinate for placement.
		 */
		static const int POSITION_CENTER = 1;

		bool isFocusable() const;

		bool hasFocus;

		/**
		 * Does the same as getEntityByID, but casts to ScreenEntity.
		 *
		 * Note: Make sure only entities of type ScreenEntity have the tag you're
		 *       querying, or otherwise you will be treating an Entity as ScreenEntity.
		 */
		ScreenEntity *getScreenEntityById(String id, bool recursive);

		/**
		 * Does the same as getEntitiesByID, but casts each result to ScreenEntity.
		 *
		 * Note: Make sure only entities of type ScreenEntity have the tag you're
		 *       querying, or otherwise you will be treating an Entity as ScreenEntity.
		 */
		std::vector<ScreenEntity*> getScreenEntitiesByTag(String tag, bool recursive);

		/**
		* If set to true, will block mouse events for underlaying entities.
		* (NOTE: processInputEvents must be set to true)
		*/
		bool blockMouseInput;

		/**
		* If this option is true, the screen entity's positions will be roudnded to whole pixels. This only works if the screen is using pixel coordinates.
		*/
		bool snapToPixels;
		bool processInputEvents;

		/**
		 * Get the hitbox of this ScreenEntity.
		 * @see setHitBox()
		 */
		Rectangle getHitbox();


		void setHitbox(Number width, Number height);

		/**
		 * Set the hitbox of this ScreenEntity.
		 *
		 * The hitbox determines the "physical" dimensions of the entity.
		 * 
		 * For instance, when it is checked whether you clicked an entity,
		 * it is checked whether the mouse was pointing inside the hitbox.
		 *
		 * The hitbox is measured from the entity's center, so a hitbox covering
		 * a square would be `(-square.w/2, -square.h/2, square.w, square.h)`
		 *
		 * @param left The left of the hitbox, as measured from the entity's center.
		 * @param top The top of the hitbox, as measured from the entity's center.
		 * @param width The width of the hitbox.
		 * @param height The height of the hitbox.
		 */
		void setHitbox(Number width, Number height, Number left, Number top);

		Number width;
		Number height;

		/**
		 * Get the drag status (true if currently being dragged) of the entity.
		 */
		bool isDragged();

	protected:

		bool focusable;
		bool focusChildren;

		bool dragged;
		Number dragOffsetX;
		Number dragOffsetY;

		bool mouseOver;

		Rectangle hit;

		Number xmouse;
		Number ymouse;

		int positionMode;
		Rectangle *dragLimits;

		int lastClickTicks;

};

}
