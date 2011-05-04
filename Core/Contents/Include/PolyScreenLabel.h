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
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolyCoreServices.h"
#include "PolyScreenShape.h"
#include "PolyScreenImage.h"
#include "PolyFont.h"
#include "PolyLabel.h"
#include "PolyTexture.h"
#include "PolyPolygon.h"
#include "PolyMesh.h"

#include <string>
using std::string;
using std::wstring;

namespace Polycode {

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
			ScreenLabel(String fontName, String text, int size, int amode);
			~ScreenLabel();		
		
			/**
			* Adds a drop shadow to the label.
			* @param color Color of the drop shadow.
			* @param size Size of the drop shadow in pixels.
			* @param offsetX Horizontal offset of the drop shadow.
			* @param offsetY Vertical offset of the drop shadow.			
			*/
			void addDropShadow(Color color, Number size, Number offsetX, Number offsetY);
			
			/**
			* Sets a new text to the screen label.
			* @param newText Text to set.
			*/
			void setText(String newText);
			
			/**
			* Returns the label's text as a string.
			* @return The label's text.
			*/
			String getText();
		
			Label *getLabel();
			
		protected:
			
			Label *label;
			ScreenImage *dropShadowImage;
	};
}