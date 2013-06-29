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
#include "PolyScenePrimitive.h"

namespace Polycode {

class Label;
class Mesh;
class Texture;
class Material;
class ShaderBinding;

/**
* 3D text label. Creates a 3D text label.
*/
class _PolyExport SceneLabel : public ScenePrimitive {
	public:

		/**
		* Constructor.
		* @param fontName Name of a registered font to use. @see FontManager for info on how to register fonts.
		* @param text Text to display.
		* @param size Size in pixels.
		* @param scale Scale to multiply pixel size by for the actual world size of the label.
		* @param Anti-aliasing mode. Can be Label::ANTIALIAS_FULL or Label::ANTIALIAS_NONE.
		*/
		SceneLabel(const String& fontName, const String& text, int size, Number scale, int amode, bool premultiplyAlpha = false);
		virtual ~SceneLabel();

		/**
		* Sets new text for the labe.
		* @param newText New text to display.
		*/ 
		void setText(const String& newText);

		Label *getLabel();

	protected:

		Number scale;
		Label *label;
};

}
