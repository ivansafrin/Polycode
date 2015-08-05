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

#include "png.h"
#include <math.h>
#include "PolyImage.h"
#include "PolyString.h"
#include "PolyLogger.h"
#include "OSBasics.h"
#include "PolyPerlin.h"
#include <algorithm>
#include <stdlib.h>
#include "rgbe.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace Polycode;

void user_read_data(png_structp png_ptr, png_bytep data, png_size_t length) {
	OSFILE *file = (OSFILE*)png_get_io_ptr(png_ptr);
	OSBasics::read(data, length, 1, file);
}

Image::Image(const String& fileName) : imageData(NULL) {
	setPixelType(IMAGE_RGBA);
	loaded = false;
	if(!loadImage(fileName)) {
		Logger::log("Error loading %s\n", fileName.c_str());
	} else {
		loaded = true;
//		Logger::log("image loaded!");
	}
}

Image *Image::BlankImage(int width, int height, int type) {
		return new Image(width, height, type);
}


void Image::setPixelType(int type) {
	imageType = type;
	switch(imageType) {
		case IMAGE_RGB:
			pixelSize = 3;			
			break;
		case IMAGE_RGBA:
			pixelSize = 4;						
		break;
		case IMAGE_FP16:		
			pixelSize = 6;
		break;
		default:
			pixelSize = 4;								
			break;
	}
}

bool Image::isLoaded() const {
	return loaded;
}

Image::Image(int width, int height, int type) : imageData(NULL) {
	setPixelType(type);
	createEmpty(width, height, Color(0.0, 0.0, 0.0, 0.0));
}

Image::Image(Image *copyImage) {
	setPixelType(copyImage->getType());
	width = copyImage->getWidth();
	height = copyImage->getHeight();		
	imageData = (char*)malloc(width*height*pixelSize);
	memcpy(imageData, copyImage->getPixels(), width*height*pixelSize);
}

Image::Image(char *data, int width, int height, int type) {
	setPixelType(type);	
	imageData = (char*)malloc(width*height*pixelSize);
	memcpy(imageData, data, width*height*pixelSize);
	this->width = width;
	this->height = height;
}

void Image::pasteImage(Image *image, int x, int y, int blendingMode , Number blendAmount, Color blendColor ) {
	for(int iy=0; iy<image->getHeight(); iy++) {	
		for(int ix=0; ix<image->getWidth(); ix++) {
			Color src = image->getPixel(ix,iy);
			Color destColor = getPixel(x+ix, y+iy);
			Color finalColor = destColor.blendColor(src, blendingMode, blendAmount, blendColor);
			setPixel(x+ix, y+iy, finalColor);
		}
	}
}

Image::Image() {
	imageData = NULL;
}

Image::~Image() {
	free(imageData);
}

char *Image::getPixels() {
	return imageData;
}

char *Image::getPixelsInRect(int x, int y, int width, int height) {
	transformCoordinates(&x, &y, &width, &height);
	char *retBuf = (char*) malloc(pixelSize * width * height);
	memset(retBuf, 0, pixelSize * width * height);
	
	if(x < this->width-1 && y < this->height-1) {

		width = std::min(width, this->width - x);
		height = std::min(height, this->height - y);

		for(int i=0; i < height; i++) {
			long srcOffset = ((pixelSize*this->width) * (y+i)) + (pixelSize*x);
			long dstOffset = (pixelSize*width) * i;
			memcpy(retBuf + dstOffset, imageData+srcOffset, pixelSize * width);
		}	
	}
		
	return retBuf;
}

Image *Image::getImagePart(Rectangle subRect) {
	char *newData = getPixelsInRect( (int) subRect.x, (int) subRect.y, (int) subRect.w, (int) subRect.h);
	return new Image(newData, subRect.w, subRect.h, this->imageType);
}


Color Image::getPixel(int x, int y) {
	transformCoordinates(&x, &y);
	if(x < 0 || x >= width || y < 0 || y >= height)
		return Color(0,0,0,0);
	unsigned int *imageData32 = (unsigned int*)imageData;	

	unsigned int hex = imageData32[x+(y*width)];
	int ta = (hex >> 24) & 0xFF;
	int tb = (hex >> 16) & 0xFF;
	int tg = (hex >> 8) & 0xFF;
	int tr = (hex ) & 0xFF;
	
	return Color(((Number)tr)/255.0f, ((Number)tg)/255.0f, ((Number)tb)/255.0f,((Number)ta)/255.0f);
}

int Image::getWidth() const {
	return width;
}

int Image::getHeight() const {
	return height;
}

void Image::createEmpty(int width, int height, const Color &fillColor) {
	free(imageData);
		
	imageData = (char*)malloc(width*height*pixelSize);
	this->width = width;
	this->height = height;
	
	fill(fillColor);
}

void Image::perlinNoise(int seed, bool alpha) {
	Perlin perlin = Perlin(12,33,1,seed);
	unsigned int *imageData32 = (unsigned int*)imageData;
	Color pixelColor;
	Number noiseVal;
	
	for(int i=0; i < width*height;i++) {
			noiseVal = fabs(1.0f/perlin.Get( 0.1+(0.9f/((Number)width)) * (i%width), (1.0f/((Number)height)) *   (i - (i%width))));
			if(alpha)
				pixelColor.setColor(noiseVal, noiseVal, noiseVal, noiseVal);
			else
				pixelColor.setColor(noiseVal, noiseVal, noiseVal, 1.0f);
			imageData32[i] = pixelColor.getUint();
	}
}

void Image::fillRect(int x, int y, int w, int h, Color col) {
	for(int i=0; i < w; i++) {
		for(int j=0; j < h; j++) {
			setPixel(x+i,y+j,col);
		}
	}
}

void Image::setPixel(int x, int y, Color col) {
	transformCoordinates(&x, &y);
	if(x < 0 || x >= width || y < 0 || y >= height)
		return;

	unsigned int *imageData32 = (unsigned int*)imageData;
	imageData32[x+(y*width)] = col.getUint();
}


void Image::moveBrush(int x, int y) {
	brushPosX += x;
	brushPosY -= y;
}

void Image::moveBrushTo(int x, int y) {
	brushPosX = x;
	brushPosY = y;
}


int Image::getBrushX() const {
	return brushPosX;
}

int Image::getBrushY() const {
	return brushPosY;
}

void Image::drawLineTo(int x, int y, Color col) {
	drawLine(brushPosX, brushPosY, brushPosX+x, brushPosY+y, col);
}

void Image::setPixel(int x, int y, Number r, Number g, Number b, Number a) {
	transformCoordinates(&x, &y);
	if(x < 0 || x > width || y < 0 || y > height)
		return;

	Color color;
	color.setColor(r,g,b,a);
	unsigned int *imageData32 = (unsigned int*)imageData;
	imageData32[x+(y*width)] = color.getUint();
}

void Image::fastBlurHor(int blurSize) {
	if(blurSize == 0)
		return;
		
	unsigned char *blurImage = (unsigned char*)malloc(width*height*pixelSize);

	int total_r;
	int total_g;
	int total_b;
	int total_a;	
	
	unsigned int *imageData32 = (unsigned int*)imageData;
	unsigned char *pixel;
	int amt;	
		
	for (int y = 1; y < height; y++) {
		for (int x = 0; x < width; x++) {
			total_r = 0;
			total_g = 0;
			total_b = 0;
			total_a = 0;
			amt = 0;
			for (int kx = -blurSize; kx <= blurSize; kx++) {
				if((x+kx > 0 && x+kx < width) && (x+kx+((y)*width) > 0 && x+kx+((y)*width) < width*height)) {
					pixel = (unsigned char*)&(imageData32[(x+kx)+((y)*width)]);
					total_r += pixel[0];
					total_g += pixel[1];
					total_b += pixel[2];
					total_a += pixel[3];
					amt++;
				}
			}
		
//				Logger::log("%d / %d = %d\n",total_r, amt, (total_r/amt));
		
		blurImage[((x+(y*width))*pixelSize)] = (total_r/amt);
		blurImage[((x+(y*width))*pixelSize)+1] = (total_g / amt);
		blurImage[((x+(y*width))*pixelSize)+2] = (total_b / amt);
		blurImage[((x+(y*width))*pixelSize)+3] = (total_a / amt);
			
		}
	}

	free(imageData);	
	imageData = (char*)blurImage;
//	free(imageData32);
}

void Image::fastBlurVert(int blurSize) {

	if(blurSize == 0)
		return;


	unsigned char *blurImage = (unsigned char*)malloc(width*height*pixelSize);

	int total_r;
	int total_g;
	int total_b;
	int total_a;	
	
	unsigned int *imageData32 = (unsigned int*)imageData;
	unsigned char *pixel;
	int amt;	
		
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			total_r = 0;
			total_g = 0;
			total_b = 0;
			total_a = 0;
			amt = 0;
			for (int ky = -blurSize; ky <= blurSize; ky++) {
				if((y+ky > 0 && y+ky < height) && (x+((y+ky)*width) > 0 && x+((y+ky)*width) < width*height)) {
					pixel = (unsigned char*)&(imageData32[(x)+((y+ky)*width)]);
					total_r += pixel[0];
					total_g += pixel[1];
					total_b += pixel[2];
					total_a += pixel[3];
					amt++;
				}
			}
				
			//Logger::log("%d / %d = %d\n",total_r, amt, (total_r/amt));
			blurImage[((x+(y*width))*pixelSize)] = (total_r/amt);
			blurImage[((x+(y*width))*pixelSize)+1] = (total_g / amt);
			blurImage[((x+(y*width))*pixelSize)+2] = (total_b / amt);
			blurImage[((x+(y*width))*pixelSize)+3] = (total_a / amt);
				
		}
	}

	free(imageData);	
	imageData = (char*)blurImage;
//	free(imageData32);
}

void Image::fastBlur(int blurSize) {
	fastBlurHor(blurSize);
	fastBlurVert(blurSize);
}

void Image::swap(int *v1, int *v2) {
	int tv = *v1;
	*v1 = *v2;
	*v2 = tv;
}

void Image::drawLine(int x0, int y0, int x1, int y1, Color col) {
	bool steep = abs(y1 - y0) > abs(x1 - x0);
	if(steep) {
		swap(&x0, &y0);
		swap(&x1, &y1);
	}
	if(x0 > x1) {
		swap(&x0, &x1);
		swap(&y0, &y1);
	}
	
	int deltax = x1 - x0;
	int deltay = abs(y1 - y0);
	Number error = 0;

	Number deltaerr = ((Number)deltay) / ((Number)deltax);
	int ystep;
	int y = y0;
	if(y0 < y1)
		ystep = 1;
	else
		ystep = -1;
	
	for(int x=x0; x < x1;x++) {
		if(steep) {
			setPixel(y,x,col);
		} else {
			setPixel(x,y,col);
		}
		error = error + ((Number)deltaerr);
		if(error >= 0.5) {
			y = y + ystep;
			error = error - 1.0;
		}
	}
}

void Image::fill(const Color &color) {
	if(imageType == Image::IMAGE_RGB) {
		for(int i = 0; i < width*height*pixelSize; i+=3) {
			imageData[i] = color.r;
			imageData[i+1] = color.g;
			imageData[i+2] = color.b;
		}
	} else {
		unsigned int val = color.getUint();
		unsigned int *imageData32 = (unsigned int*) imageData;

		for(int i=0; i< width*height; i++) {
			imageData32[i] = val;
		}
	}
}

bool Image::saveImage(const String &fileName) {
	return savePNG(fileName);
}

void Image::premultiplyAlpha() {
	unsigned int *imageData32 = (unsigned int*)imageData;
			
	for(int x=0; x < width; x++) {
		for(int y=0; y < height; y++) {
			
			unsigned int hex = imageData32[x+(y*width)];
			
			int ta = (hex >> 24) & 0xFF;
			int tb = (hex >> 16) & 0xFF;
			int tg = (hex >> 8) & 0xFF;
			int tr = (hex ) & 0xFF;
	
			Number r = ((Number)tr)/255.0f;
			Number g = ((Number)tg)/255.0f;
			Number b = ((Number)tb)/255.0f;
			Number a = ((Number)ta)/255.0f;	

			r *= a;
			g *= a;
			b *= a;
						
			unsigned int ir = 255.0f*r;
			unsigned int ig = 255.0f*g;
			unsigned int ib = 255.0f*b;
			unsigned int ia = 255.0f*a;
									
			unsigned int newVal = ((ia & 0xFF) << 24) | ((ib & 0xFF) << 16) | ((ig & 0xFF) << 8) | (ir & 0xFF);
						
			imageData32[x+(y*width)] = newVal;
		}
	}
}

bool Image::savePNG(const String &fileName) {

	printf("Saving %dx%d image\n", width, height);

   FILE *fp;
   png_structp png_ptr;
   png_infop info_ptr;
   
   fp = fopen(fileName.c_str(), "wb");
   if (fp == NULL)
      return false;

   png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);

   if (png_ptr == NULL)
   {
      fclose(fp);
      return false;
   }

   info_ptr = png_create_info_struct(png_ptr);
   if (info_ptr == NULL)
   {
      fclose(fp);
      png_destroy_write_struct(&png_ptr,  NULL);
      return false;
   }

   if (setjmp(png_jmpbuf(png_ptr)))
   {
      /* If we get here, we had a problem writing the file */
      fclose(fp);
      png_destroy_write_struct(&png_ptr, &info_ptr);
      return false;
   }

   png_init_io(png_ptr, fp);
   png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB_ALPHA,
      PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
 
	png_write_info(png_ptr, info_ptr);

   png_uint_32 k;
   png_bytep *row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);

   if (height > PNG_UINT_32_MAX/png_sizeof(png_bytep))
     png_error (png_ptr, "Image is too tall to process in memory");

   for (k = 0; k < height; k++)
     row_pointers[height-k-1] = (png_byte*)(imageData + k*width*4);

   /* One of the following output methods is REQUIRED */

   png_write_image(png_ptr, row_pointers);

   free(row_pointers);
   png_free(png_ptr, 0);
   png_destroy_write_struct(&png_ptr, &info_ptr);
   fclose(fp);
   return true;
}


bool Image::loadImage(const String& fileName) {
    
	String extension;
	size_t found;
	found=fileName.rfind(".");
	if (found != -1) {
		extension = fileName.substr(found+1);
	} else {
		extension = "";
	}

    if(extension == "png") {
        return loadPNG(fileName);
    } else if(extension == "hdr") {
        return loadHDR(fileName);
    } else if(extension == "jpg" || extension == "tga" || extension == "psd") {
        return loadSTB(fileName);
    } else {
        Logger::log("Error: Invalid image format.\n");
        return false;
    }
}

inline hfloat Image::convertFloatToHFloat(float f) {
    float _f = f;
    uint32_t x = *(uint32_t *)(&_f);
    uint32_t sign = (uint32_t)(x >> 31);
    uint32_t mantissa;
    uint32_t exp;
    hfloat          hf;
    
    // get mantissa
    mantissa = x & ((1 << 23) - 1);
    // get exponent bits
    exp = x & FLOAT_MAX_BIASED_EXP;
    if (exp >= HALF_FLOAT_MAX_BIASED_EXP_AS_SINGLE_FP_EXP)
    {
        // check if the original single precision float number is a NaN
        if (mantissa && (exp == FLOAT_MAX_BIASED_EXP))
        {
            // we have a single precision NaN
            mantissa = (1 << 23) - 1;
        }
        else
        {
            // 16-bit half-float representation stores number as Inf
            mantissa = 0;
        }
        hf = (((hfloat)sign) << 15) | (hfloat)(HALF_FLOAT_MAX_BIASED_EXP) |
        (hfloat)(mantissa >> 13);
    }
    // check if exponent is <= -15
    else if (exp <= HALF_FLOAT_MIN_BIASED_EXP_AS_SINGLE_FP_EXP)
    {
        
        // store a denorm half-float value or zero
        exp = (HALF_FLOAT_MIN_BIASED_EXP_AS_SINGLE_FP_EXP - exp) >> 23;
        mantissa >>= (14 + exp);
        
        hf = (((hfloat)sign) << 15) | (hfloat)(mantissa);
    }
    else
    {
        hf = (((hfloat)sign) << 15) |
        (hfloat)((exp - HALF_FLOAT_MIN_BIASED_EXP_AS_SINGLE_FP_EXP) >> 13) |
        (hfloat)(mantissa >> 13);
    }
    
    return hf;
}

TokenArray Image::readTokens(char *line, const char *tokenString) {
	char **tokens = (char**)malloc(sizeof(void*));
	char *pch;
	int numTokens = 0;
	pch = strtok (line, tokenString);
	while (pch != NULL) {
		numTokens++;
		tokens = (char**)realloc(tokens, sizeof(void*) *numTokens);
		tokens[numTokens-1] = (char*) malloc(strlen(pch)+1);
		memcpy(tokens[numTokens-1], pch, strlen(pch)+1);
		pch = strtok (NULL, tokenString);
	}
    
	TokenArray ta;
	ta.size = numTokens;
	ta.tokens = tokens;
	return ta;
}

void Image::freeTokens(TokenArray tokens) {
	int i;
	for(i =0; i < tokens.size; i++) {
		free(tokens.tokens[i]);
	}
	free(tokens.tokens);
}

bool Image::loadSTB(const String &fileName) {
    
    OSFILE *infile = OSBasics::open(fileName.c_str(), "rb");
    
    if(!infile) {
        Logger::log("Error opening image file: %s\n", fileName.c_str());
        return false;
    }
    
    OSBasics::seek(infile, 0, SEEK_END);
    long bufferLen = OSBasics::tell(infile);
    OSBasics::seek(infile, 0, SEEK_SET);
    
    char *buffer = (char*) malloc(bufferLen);
    OSBasics::read(buffer, bufferLen, 1, infile);
    
    int x,y,n;
    stbi_uc *data = stbi_load_from_memory((const stbi_uc*)buffer, bufferLen, &x, &y, &n, 4);
    
    if(!data) {
        Logger::log("Error reading image data: %s\n", fileName.c_str());
        return false;
    }
    
    imageType = Image::IMAGE_RGBA;
    
    width = x;
    height = y;
    
    free(buffer);
    
    imageData = (char*)data;
    
    OSBasics::close(infile);

    return true;
}

bool Image::loadHDR(const String &fileName) {
    
    imageType = Image::IMAGE_FP16;
    
    OSFILE *infile = OSBasics::open(fileName.c_str(), "rb");
    
    if(!infile) {
        Logger::log("Error opening HDR %s\n", fileName.c_str());
        return false;
    }
    
    OSBasics::seek(infile, 0, SEEK_END);
    long bufferLen = OSBasics::tell(infile);
    OSBasics::seek(infile, 0, SEEK_SET);
    
    char *buffer = (char*) malloc(bufferLen);
    OSBasics::read(buffer, bufferLen, 1, infile);
    
    int x,y,n;
    float *data = stbi_loadf_from_memory((const stbi_uc*)buffer, bufferLen, &x, &y, &n, 0);
    
    if(!data) {
        Logger::log("Error reading image data: %s\n", fileName.c_str());
        return false;
    }
    
    width = x;
    height = y;
    
    free(buffer);
    
    imageData = (char*)data;
    
    OSBasics::close(infile);
    
    
    return true;
}

bool Image::loadPNG(const String& fileName) {
	OSFILE         *infile;
	
	png_structp   png_ptr;
	png_infop     info_ptr;
	char         *image_data;
	char         sig[8];
	int           bit_depth;
	int           color_type;
	png_uint_32 width;
	png_uint_32 height;
	unsigned int rowbytes;
	image_data = NULL;
	int i;
	png_bytepp row_pointers = NULL;
	
	infile = OSBasics::open(fileName.c_str(), "rb");
	if (!infile) {
		Logger::log("Error opening png file (\"%s\")\n", fileName.c_str());
		return false;
	}
	
	OSBasics::read(sig, 1, 8, infile);
	
	if (!png_check_sig((unsigned char *) sig, 8)) {
		Logger::log("Error reading png signature (\"%s\")\n", fileName.c_str());
		OSBasics::close(infile);
		return false;
	}

	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) {
		Logger::log("Error creating png struct (\"%s\")\n", fileName.c_str());
		OSBasics::close(infile);
		return false;    /* out of memory */
	}
	
	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		Logger::log("Error creating info struct (\"%s\")\n", fileName.c_str());
		png_destroy_read_struct(&png_ptr, (png_infopp) NULL, (png_infopp) NULL);
		OSBasics::close(infile);
		return false;    /* out of memory */
	}
	
	if (setjmp(png_jmpbuf(png_ptr))) {
		Logger::log("Error setting jump thingie (\"%s\")\n", fileName.c_str());
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		OSBasics::close(infile);
		return false;
	}

	//png_init_io(png_ptr, infile);
	png_set_read_fn(png_ptr, (png_voidp)infile, user_read_data);
	
	png_set_sig_bytes(png_ptr, 8);
	png_read_info(png_ptr, info_ptr);
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, 
				 &color_type, NULL, NULL, NULL);
	this->width = width;
	this->height = height;
	
	/* Set up some transforms. */
	if (color_type & PNG_COLOR_MASK_ALPHA) {
		//  png_set_strip_alpha(png_ptr);
	}
	if (bit_depth > 8) {
		png_set_strip_16(png_ptr);
	}
	if (color_type == PNG_COLOR_TYPE_GRAY ||
		color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
		png_set_gray_to_rgb(png_ptr);
	}
	if (color_type == PNG_COLOR_TYPE_PALETTE) {
		png_set_palette_to_rgb(png_ptr);
	}
	
	
	if (color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_RGB_ALPHA) {
		png_set_add_alpha(png_ptr, 0xffffff, PNG_FILLER_AFTER);
	}	
	
	/* Update the png info struct.*/
	png_read_update_info(png_ptr, info_ptr);
	
	/* Rowsize in bytes. */
	rowbytes = png_get_rowbytes(png_ptr, info_ptr);
	
	/* Allocate the image_data buffer. */
	if ((image_data = (char *) malloc(rowbytes * height))==NULL) {
		Logger::log("Error allocating image memory (\"%s\")\n", fileName.c_str());
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		return false;
	}
	
	if ((row_pointers = (png_bytepp)malloc(height*sizeof(png_bytep))) == NULL) {
		Logger::log("Error allocating image memory (\"%s\")\n", fileName.c_str());
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		free(image_data);
		image_data = NULL;
		return false;
	}
	
	for (i = 0;  i < height;  ++i)
		row_pointers[height - 1 - i] = (png_byte*)image_data + i*rowbytes;
	
	png_read_image(png_ptr, row_pointers);
	
	free(row_pointers);
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	OSBasics::close(infile);
	
	imageData = image_data;
	return true;
}

void Image::transformCoordinates(int *x, int *y) {
	*y = this->height - *y - 1;
}

void Image::transformCoordinates(int *x, int *y, int *w, int *h) {
	*y = this->height - *h - *y;
}
