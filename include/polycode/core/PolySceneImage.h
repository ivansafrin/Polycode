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
#include "PolyImage.h"
#include "PolyScenePrimitive.h"

namespace Polycode {

	/**
	* 2D screen image display. This ScreenEntity can load and display and image.
	*/
	class _PolyExport SceneImage : public ScenePrimitive {
		public:
		/**
		* Create screen image from file.
		* @param fileName 
		*/
		explicit SceneImage(const String& fileName);

		/**
		* Create screen image from Image.
		* @param image Image to create from.
		*/		
		explicit SceneImage(Image *image);

		/**
		 * Create screen image from Texture.
		 * @param texture Texture to create from.
		 */		
		explicit SceneImage(Texture *texture);

		/**
		* Create screen image from Image.
		* @param image Image to create from.
		*/				
		static SceneImage* SceneImageWithImage(Image *image);

		/**
		 * Create screen image from Texture.
		 * @param texture Texture to create from.
		 */				
		static SceneImage* SceneImageWithTexture(Texture *texture);

		virtual ~SceneImage();

		virtual Entity *Clone(bool deepClone, bool ignoreEditorOnly) const;
		virtual void applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly) const;

		/**
		* Changes which part of the image is displayed.
		* @param x X position of the display rectangle.
		* @param y Y position of the display rectangle.
		* @param width Width of the display rectangle.
		* @param height Height of the display rectangle.
		*/				
		void setImageCoordinates(Number x, Number y, Number width, Number height, Number realWidth=-1, Number realHeight=-1);

		/**
		* Returns the image width.
		*/ 
		Number getImageWidth() const;

		/**
		* Returns the image height.
		*/ 		
		Number getImageHeight() const;

		protected:

		Number imageWidth;
		Number imageHeight;

	};

}