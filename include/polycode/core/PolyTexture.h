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
#include "polycode/core/PolyString.h"
#include "polycode/core/PolyGlobals.h"
#include "polycode/core/PolyResource.h"
#include "polycode/core/PolyImage.h"

namespace Polycode {

	class _PolyExport Texture : public Resource {
		public:
			Texture(unsigned int width, unsigned int height, char *textureData,bool clamp, bool createMipmaps, int type=Image::IMAGE_RGBA, bool framebufferTexture=false);
			Texture(Image *image);
			virtual ~Texture();
			
			void reloadResource();
			
			void setImageData(Image *data);
			char *getTextureData() const { return textureData;}
			
			int getWidth() const;
			int getHeight() const;

			void setCreateMipmaps(bool createMipmapsIn) { createMipmaps = createMipmapsIn; }
			bool getCreateMipmaps() const { return createMipmaps; }
		
			bool clamp;
			char *textureData;
			int type;
			int filteringMode;
			bool createMipmaps;
			unsigned int anisotropy;
			bool framebufferTexture;
			bool depthTexture;
		
			static const int FILTERING_NEAREST = 0;
			static const int FILTERING_LINEAR = 1;
		
		protected:

			int pixelSize;
			int width;
			int height;
	};
	
	class _PolyExport RenderBuffer {
		public:
			RenderBuffer(unsigned int width, unsigned int height, bool attachDepthBuffer, bool floatingPoint);

			unsigned int getWidth();
			unsigned int getHeight();
		
			Texture *colorTexture;
			Texture *depthTexture;

			void *platformData;
			void *depthBufferPlatformData;
	
		private:
		
			bool floatingPoint;
		
			unsigned int width;
			unsigned int height;
	};
	
}
