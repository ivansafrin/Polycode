/*
 *  PolyImage.h
 *  Poly
 *
 *  Created by Ivan Safrin on 3/13/08.
 *  Copyright 2008 Ivan Safrin. All rights reserved.
 *
 */
// @package BasicTypes

#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"
#include "png.h"
#include "PolyColor.h"
#include "PolyPerlin.h"
#include <string>
#include <math.h>
#include "OSBasics.h"

using std::string;

namespace Polycode {
	class _PolyExport Image {
		public:
			Image(String fileName);
			Image(int width, int height, int type = IMAGE_RGBA);
			Image(char *data, int width, int height, int type = IMAGE_RGBA);
			Image(Image *copyImage);		
			Image();			
			~Image();

			bool loadImage(String fileName);
			bool loadPNG(String fileName);
		
			
			void createEmpty(unsigned int width, unsigned int height);
			void fill(Number r, Number g, Number b, Number a);
			
			// drawing
			void setPixel(int x, int y, Number r, Number g, Number b, Number a);
			void setPixel(int x, int y, Color col);
			Color getPixel(int x, int y);
						   
			void setAAPixel(int x, int y, Color col);
			void swap(int *v1, int *v2);
			void line(int x0, int y0, int x1, int y1, Color col);
			void moveTo(int x, int y);
			void move(int x, int y);
			void lineTo(int x, int y, Color col);
			void drawRect(int x, int y, int w, int h, Color col);
			
			// effex
			void perlinNoise(int seed, bool alpha);
			void fastBlur(int blurSize);
			void fastBlurVert(int blurSize);
			void fastBlurHor(int blurSize);
			void darken(Number amt, bool color, bool alpha);
			void lighten(Number amt, bool color, bool alpha);
			void multiply(Number amt, bool color, bool alpha);
			
			int getBrushX();
			int getBrushY();
		
			bool isLoaded();
		
			int getType() { return imageType; }
			
			void writeBMP(String fileName);
			
			unsigned int getWidth();
			unsigned int getHeight();
			char *getPixels();
		
			static const int IMAGE_RGB = 0;
			static const int IMAGE_RGBA = 1;
		
		protected:
		
			void setPixelType(int type);		
		
		int imageType;
		int pixelSize;
		
		bool loaded;
		
		Color strokeColor;
		int brushPosX;
		int brushPosY;
		
		char *imageData;
		unsigned int width;
		unsigned int height;
	};

}