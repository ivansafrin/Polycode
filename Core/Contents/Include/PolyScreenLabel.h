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
#include "PolyScreenShape.h"

namespace Polycode {

class Label;
class ScreenImage;

/**
* 2D screen label display. Displays 2d text in a specified font.
*/ 
class _PolyExport ScreenLabel : public ScreenShape {
	public:

		/**
		* Constructor.
		* @param fontName Name of a registered font to use. @see FontManager for info on how to register fonts.
		* @param text Text to display.
		* @param size Size in pixels.
		* @param Anti-aliasing mode.
		*/
		ScreenLabel(const String& text, int size, const String& fontName = "sans", int amode = 0, bool premultiplyAlpha = false);
		virtual ~ScreenLabel();

		virtual Entity *Clone(bool deepClone, bool ignoreEditorOnly);
		virtual void applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly);

		/**
		* Sets a new text to the screen label.
		* @param newText Text to set.
		*/
		void setText(const String& newText);

		/**
		* Returns the label's text as a string.
		* @return The label's text.
		*/
		const String& getText() const;

		Label *getLabel() const;

		void Render();
		bool positionAtBaseline;

	protected:

		void updateTexture();
		Label *label;
};
}
