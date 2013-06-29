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
#include "PolyResource.h"
#include "PolyImage.h"

namespace Polycode {

class _PolyExport Texture : public Resource {
	public:
	Texture(unsigned int width, unsigned int height, char *textureData,bool clamp, bool createMipmaps, int type=Image::IMAGE_RGBA);
		Texture(Image *image);
		virtual ~Texture();

		Number scrollSpeedX;
		Number scrollSpeedY;

		void reloadResource();

		virtual void setTextureData(char *data) = 0;

		virtual void recreateFromImageData() = 0;

		Number getScrollOffsetX() const;
		Number getScrollOffsetY() const;

		void setImageData(Image *data);

		void updateScroll(int elapsed);
		char *getTextureData() const { return textureData;}

		int getWidth() const;
		int getHeight() const;

		bool clamp;
		char *textureData;

	protected:

		int pixelSize;
		int filteringMode;

		bool createMipmaps;
		int width;
		int height;
		Number scrollOffsetX;
		Number scrollOffsetY;
};

}
