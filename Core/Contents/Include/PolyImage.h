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
#include "PolyColor.h"
#include "PolyRectangle.h"

namespace Polycode {

	class String;
    
    #define HALF_FLOAT_MIN_BIASED_EXP_AS_SINGLE_FP_EXP 0x38000000
    #define HALF_FLOAT_MAX_BIASED_EXP_AS_SINGLE_FP_EXP 0x47800000
    #define FLOAT_MAX_BIASED_EXP (0xFF << 23)
    #define HALF_FLOAT_MAX_BIASED_EXP (0x1F << 10)
    
    typedef uint16_t hfloat;

    typedef struct POLYIGNORE  {
        int size;
        char **tokens;
    } TokenArray;
    
	/**
	* An image in memory. Basic RGB or RGBA images stored in memory. Can be loaded from PNG files, created into textures and written to file.
	*/
	class _PolyExport Image : public PolyBase {
		public:
		
			/**
			* Create image from file name.
			* @param fileName Path to image file to load.
			*/ 
			explicit Image(const String& fileName);
			
			/**
			* Create a blank image of specified size and type.
			* @param width Width of the image to create.
			* @param height Height of the image to create.			
			* @param type Type of image to create. Can be IMAGE_RGBA or IMAGE_RGB.
			*/ 			
			Image(int width, int height, int type = Image::IMAGE_RGBA);
			
			/**
			* Create an image of specified size and type and set its contents from the specified buffer.
			* @param data Data buffer to set contents from.
			* @param width Width of the image to create.
			* @param height Height of the image to create.			
			* @param type Type of image to create. Can be IMAGE_RGBA or IMAGE_RGB.
			*/ 						
			Image(char *data, int width, int height, int type = Image::IMAGE_RGBA);
			
			/**
			* Create a blank image of specified size and type.
			* @param width Width of the image to create.
			* @param height Height of the image to create.			
			* @param type Type of image to create. Can be IMAGE_RGBA or IMAGE_RGB.
			*/ 			
			static Image *BlankImage(int width, int height, int type = Image::IMAGE_RGBA);
			
			/**
			* Create an image from another image.
			* @param copyImage The image to copy.
			*/ 						
			Image(Image *copyImage);		
			Image();			
			virtual ~Image();

			/**
			* Load an image from a file
			* @param fileName Path to image file to load.
			* @return True if successfully loaded, false otherwise.
			*/ 			
			bool loadImage(const String& fileName);
			bool loadPNG(const String& fileName);
        
            static POLYIGNORE TokenArray readTokens(char *line, const char *tokens);
            static POLYIGNORE void freeTokens(TokenArray tokens);
            bool loadHDR(const String &fileName);
			
			/**
			* Saves the image to a file. Currently only PNG files are supported.
			* @param fileName Path to image file to load.	
			* @return True if successfully loaded, false otherwise.	
			*/
			bool saveImage(const String &fileName);
			bool savePNG(const String &fileName);
			
			/**
			* Pastes another image into the image using a blending mode
			* @param image Image to paste
			* @param x X position of new image within the image 
			* @param y Y position of new image within the image 			
			* @param blendingMode Blending mode to use. Currently not used.
			*/
			void pasteImage(Image *image, int x, int y, int blendingMode = 0, Number blendAmount = 1.0, Color blendColor = Color());
			
			/**
			* Recreate the image as an empty image of specified size. The image type stays the same.
			* @param width Width of the image to create.
			* @param height Height of the image to create.			
			*/ 						
			void createEmpty(int width, int height);

			/**
			* Fills the image with the specified color values.
			* @param color The color to fill it with.
			*/ 									
			void fill(Color color);
			
			/**
			* Sets a pixel at specified coordinates to specified color.
			* @param x X position of pixel.
			* @param y Y position of pixel.			
			* @param r Red value 0-1.
			* @param g Green value 0-1
			* @param b Blue value 0-1
			* @param a Alpha value 0-1												
			*/
			void setPixel(int x, int y, Number r, Number g, Number b, Number a);
			
			/**
			* Sets a pixel at specified coordinates to specified color.
			* @param x X position of pixel.
			* @param y Y position of pixel.			
			* @param col Color to set.
			*/			
			void setPixel(int x, int y, Color col);
			
			/**
			* Returns the pixel color at specified position.
			* @param x X position of pixel.
			* @param y Y position of pixel.						
			* @return Pixel color at specified position.
			*/			
			Color getPixel(int x, int y);
						   
			void swap(int *v1, int *v2);
			
			/**
			* Draws a line with specified color.
			* @param x0 Starting x position.
			* @param y0 Starting y position.
			* @param x1 Ending x position.
			* @param y1 Ending y position.
			* @param col Color to use.						
			*/						
			void drawLine(int x0, int y0, int x1, int y1, Color col);

			/**
			* Moves brush to specified position
			* @param x New brush position X
			* @param y New brush position Y
			*/									
			void moveBrushTo(int x, int y);
			
			/**
			* Translates brush a specified amount relative to its current position.
			* @param x Amount to translate on X axis
			* @param y Amount to translate on Y axis
			*/												
			void moveBrush(int x, int y);
			
			/**
			* Draws a line to specified position.
			* @param x Ending x position.
			* @param y Ending y position.
			* @param col Color to use.						
			*/												
			void drawLineTo(int x, int y, Color col);
			
			/**
			* Draws a rectangle with specified color.
			* @param x Rectangle x position.
			* @param y Rectangle y position.
			* @param w Rectangle width.
			* @param h Rectangle height.
			* @param col Color to use.						
			*/									
			void fillRect(int x, int y, int w, int h, Color col);
			
			/**
			* Draws perlin noise in the image
			* @param seed Seed for the noise
			* @param alpha If true, affects alpha, if false only affects the color.
			*/									
			void perlinNoise(int seed, bool alpha);
			
			/**
			* Blurs the image using box blur.
			* @param blurSize Size of the blur in pixels.
			*/												
			void fastBlur(int blurSize);
			void fastBlurVert(int blurSize);
			void fastBlurHor(int blurSize);
			
						
			/**
			* Returns an area of the image buffer. The area can go outside of image bounds, in which case the pixels not within the image are zeroed out. This method allocates new memory for the returned buffer and you must free it manually.
			* @param x X position of the area to return.
			* @param y Y position of the area to return.
			* @param width Width of the area to return.
			* @param height Height of the area to return.
			* @return Raw image data, in the format specified by the constructor.
			*/			
			char *getPixelsInRect(int x, int y, int width, int height);

			/**
			* Returns a copy of the specified subRect part of the image.
			*
			* @param subRect The part of the image to copy. (0, 0) refers to the top left of the image.
			* @return A pointer to an Image object allocated with new. You have to manually delete this
			*         object using free.
			*/
			Image *getImagePart(Rectangle subRect);
			
			/**
			* Returns the x position of the brush.
			*/
			int getBrushX() const;
			
			/**
			* Returns the y position of the brush.
			*/			
			int getBrushY() const;
		
			bool isLoaded() const;
		
			int getType() const { return imageType; }
			
			/**
			* Returns the width of the image.
			*/			
			int getWidth() const;
			
			/**
			* Returns the height of the image.
			*/						
			int getHeight() const;
			
			/**
			* Returns the raw image data
			* @return Pointer to raw image data, in the format specified by the constructor.
			*/						
			char *getPixels();
			
            /**
             * Multiplies the RGB values by alpha for each pixel.
             */
			void premultiplyAlpha();
		
			static const int IMAGE_RGB = 0;
			static const int IMAGE_RGBA = 1;
			static const int IMAGE_FP16 = 2;
		
		protected:
		
        
            static inline hfloat convertFloatToHFloat(float f);
        
			void setPixelType(int type);

			// transform coordinates from external topleft position mode
			// to internal bottomleft position mode
			//
			// results are written directly into the pointers
			void transformCoordinates(int *x, int *y);	
			void transformCoordinates(int *x, int *y, int *w, int *h);	
		
		int imageType;
		int pixelSize;
		
		bool loaded;
		
		Color strokeColor;
		int brushPosX;
		int brushPosY;
		
		char *imageData;
		int width;
		int height;
	};

}
