/*
 Copyright (C) 2012 by Ivan Safrin

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
#include "PolyUIVScrollBar.h"
#include "PolyUIHScrollBar.h"
#include "PolyUIElement.h"

namespace Polycode {

	/**
	 * A container for UI elements that adds scroll bars if necessary.
	 *
	 * Internally, this class simply moves the scrolled child, and uses scissorBox
	 * to cut off the parts going over the edges.
	 */
	class _PolyExport UIScrollContainer : public UIElement {
	public:
        /**
        * Create a scroll container.
        * @param scrolledEntity The Entity that should be scrolled using this element.
        * @param hScroll Whether the child should be scrolled horizontally.
        * @param vScroll Whether the child should be scrolled vertically.
        * @param width The width of the scroll container.
        * @param height The height of the scroll container.
        */
		UIScrollContainer(Entity *scrolledEntity, bool hScroll, bool vScroll, Number width, Number height);
		virtual ~UIScrollContainer();

        /**
        * Update what size the content child is expected to have.
        *
        * This doesn't do anything to the child, it just updates scroll bar
        * positions etc.
        *
        * @param newContentWidth Width of the content.
        * @param newContentHeight Height of the content.
        */
		void setContentSize(Number newContentWidth, Number newContentHeight);

		void Resize(Number width, Number height);

        /**
        * Set how far the content child should be scrolled.
        *
        * @param xScroll New horizontal scroll position.
        * @param yScroll New vertical scroll position.
        */
		void setScrollValue(Number xScroll, Number yScroll);

        /**
        * Set how far the content child should be scrolled.
        *
        * @param amount New vertical scroll position.
        */
		void scrollVertical(Number amount);

        /**
        * Set how far the content child should be scrolled.
        *
        * @param amount New horizontal scroll position.
        */
		void scrollHorizontal(Number amount);

		void Update();

        /** Get the assumed size of the content.
        *
        * Note that this doesn't actually look at the contained
        * element, but rather just returns what was earlier set
        * by setContentSize()
        *
        * @return The currently assumed size of the content.
        */
		Vector2 getContentSize();

		void _onMouseWheelDown();
		void _onMouseWheelUp();

		void handleEvent(Event *event);

        /**
        * Get the width of the vertical scroll bar.
        */
		Number getVScrollWidth();

		UIVScrollBar *getVScrollBar() { return vScrollBar; }
		UIHScrollBar *getHScrollBar() { return hScrollBar; }
		
	private:		
		
		Number defaultScrollSize;

		Number contentWidth;
		Number contentHeight;

		Entity *scrollChild;

		bool hasHScroll;
		bool hasVScroll;

		UIVScrollBar *vScrollBar;
		UIHScrollBar *hScrollBar;
	};

}
