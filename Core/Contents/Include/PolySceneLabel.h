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
#include "PolyFont.h"
#include "PolyLabel.h"
#include "PolyMesh.h"
#include "PolyTexture.h"
#include "PolyPolygon.h"
#include "PolySceneEntity.h"

#include <string>
using std::string;

namespace Polycode {
	
	/**
	* 3D text label. Creates a 3D text label.
	*/
	class _PolyExport SceneLabel : public SceneEntity {
		public:
			
			/**
			* Constructor.
			* @param fontName Name of a registered font to use. @see FontManager for info on how to register fonts.
			* @param text Text to display.
			* @param size Size in pixels.
			* @param scale Scale to multiply pixel size by for the actual world size of the label.
			* @param Anti-aliasing mode. Can be Label::ANTIALIAS_FULL or Label::ANTIALIAS_NONE.
			*/			
			SceneLabel(const String& fontName, const String& text, int size, Number scale, int amode);
			~SceneLabel();			
		
			bool testMouseCollision(Number x, Number y);
		
			/**
			* Sets new text for the labe.
			* @param newText New text to display.
			*/ 
			void setText(const String& newText);
			
			Label *getLabel();
			void Render();
			
		protected:
			
			Mesh *mesh;
			Texture *texture;		
		
			Number scale;
			Label *label;
	};
}
