/*
 *  PolyTexture.h
 *  TAU
 *
 *  Created by Ivan Safrin on 3/13/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

// @package Materials

#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolyResource.h"
#include "PolyImage.h"

namespace Polycode {

	class _PolyExport Texture : public Resource {
		public:
		Texture(unsigned int width, unsigned int height, char *textureData,bool clamp, int type=Image::IMAGE_RGBA);
			Texture(Image *image);
			virtual ~Texture();

			float scrollSpeedX;
			float scrollSpeedY;
			
			virtual void setTextureData(char *data) = 0;

			virtual void recreateFromImageData() = 0;

			float getScrollOffsetX();
			float getScrollOffsetY();
			
			void setImageData(Image *data);
		
			void updateScroll(int elapsed);
			void setResourcePath(String newPath);
			String getResourcePath();
		
			char *getTextureData() { return textureData;}
			
			int getWidth();
			int getHeight();
		
			bool clamp;
		
		protected:

			int pixelSize;
			int filteringMode;
		
			int width;
			int height;
			String resourcePath;
			char *textureData;
			float scrollOffsetX;
			float scrollOffsetY;
	};
}