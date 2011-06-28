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
#include "PolyImage.h"


using namespace Polycode;

void user_read_data(png_structp png_ptr, png_bytep data, png_size_t length) {
	OSFILE *file = (OSFILE*)png_get_io_ptr(png_ptr);
	OSBasics::read(data, length, 1, file);
}

Image::Image(String fileName) : imageData(NULL) {
	setPixelType(IMAGE_RGBA);
	loaded = false;
	if(!loadImage(fileName)) {
		Logger::log("Error loading %s\n", fileName.c_str());
	} else {
		loaded = true;
//		Logger::log("image loaded!");
	}
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
			pixelSize = 4;						
		default:
			break;
	}
}

bool Image::isLoaded() {
	return loaded;
}

Image::Image(int width, int height, int type) : imageData(NULL) {
	setPixelType(type);
	createEmpty(width, height);
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

Image::Image() {
	imageData = NULL;
}

Image::~Image() {
	if(imageData != NULL)
		free(imageData);
}

char *Image::getPixels() {
	return imageData;
}

Color Image::getPixel(int x, int y) {
	if(x < 0 || x >= width || y < 0 || y >= height)
		return Color(0,0,0,0);
	unsigned int *imageData32 = (unsigned int*)imageData;	
	return Color(imageData32[x+(y*width)]);
}

unsigned int Image::getWidth() {
	return width;
}

unsigned int Image::getHeight() {
	return height;
}

void Image::createEmpty(unsigned int width, unsigned int height) {
	if(imageData != NULL)
		free(imageData);
		
	imageData = (char*)malloc(width*height*pixelSize);
	this->width = width;
	this->height = height;
	
	fill(0,0,0,0);
}

void Image::perlinNoise(int seed, bool alpha) {
	Perlin *perlin = new Perlin(12,33,1,seed);
	unsigned int *imageData32 = (unsigned int*)imageData;
	Color pixelColor;
	Number noiseVal;
	
	for(int i=0; i < width*height;i++) {
			noiseVal = fabs(1.0f/perlin->Get( 0.1+(0.9f/((Number)width)) * (i%width), (1.0f/((Number)height)) *   (i - (i%width))));
			if(alpha)
				pixelColor.setColor(noiseVal, noiseVal, noiseVal, noiseVal);
			else
				pixelColor.setColor(noiseVal, noiseVal, noiseVal, 1.0f);
			imageData32[i] = pixelColor.getUint();
	}
}

void Image::writeBMP(String fileName) {
//	SDL_Surface *image;
//	image = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, 0x0000FF, 0x00FF00, 0xFF0000, 0x000000);
//	memcpy(image->pixels,imageData,width * height * 4);
//	SDL_SaveBMP(image, fileName.c_str());
}

void Image::drawRect(int x, int y, int w, int h, Color col) {
	for(int i=0; i < w; i++) {
		for(int j=0; j < h; j++) {
			setPixel(x+i,y+j,col);
		}
	}
}

void Image::setPixel(int x, int y, Color col) {
	if(x < 0 || x >= width || y < 0 || y >= height)
		return;

	unsigned int *imageData32 = (unsigned int*)imageData;
	imageData32[x+(y*width)] = col.getUint();
}


void Image::move(int x, int y) {
	brushPosX += x;
	brushPosY += y;
}

void Image::moveTo(int x, int y) {
	brushPosX = x;
	brushPosY = y;
}


int Image::getBrushX() {
	return brushPosX;
}

int Image::getBrushY() {
	return brushPosY;
}

void Image::lineTo(int x, int y, Color col) {
	line(brushPosX, brushPosY, brushPosX+x, brushPosY+y, col);
}

void Image::setPixel(int x, int y, Number r, Number g, Number b, Number a) {
	if(x < 0 || x > width || y < 0 || y > height)
		return;

	Color color;
	color.setColor(r,g,b,a);
	unsigned int *imageData32 = (unsigned int*)imageData;
	imageData32[x+(y*width)] = color.getUint();
}

void Image::multiply(Number amt, bool color, bool alpha) {
	int startIndex = 0;
	int endIndex = 3;
	if(!color)
		startIndex = 3;
	if(!alpha)
		endIndex = 2;
		
	for (int i = 0; i < height*width*pixelSize; i+=pixelSize) {
		for(int j = startIndex; j < endIndex+1;j++) {
			if(((Number)imageData[i+j]) * amt< 0)
				imageData[i+j] = 0;
			else if(((Number)imageData[i+j]) * amt > 255)
				imageData[i+j] = 255;
			else
				imageData[i+j] = (char)(((Number)imageData[i+j]) * amt);
		}
	}
}

void Image::darken(Number amt, bool color, bool alpha) {
	char decAmt = 255.0f * amt;
	int startIndex = 0;
	int endIndex = 3;
	if(!color)
		startIndex = 3;
	if(!alpha)
		endIndex = 2;
		
	for (int i = 0; i < height*width*pixelSize; i+=pixelSize) {
		for(int j = startIndex; j < endIndex+1;j++) {
			if(imageData[i+j]-decAmt < 0)
				imageData[i+j] = 0;
			else
				imageData[i+j] -= decAmt;
		}
	}
}

void Image::lighten(Number amt, bool color, bool alpha) {
	char decAmt = 255.0f * amt;
	int startIndex = 0;
	int endIndex = 3;
	if(!color)
		startIndex = 3;
	if(!alpha)
		endIndex = 2;
		
	for (int i = 0; i < height*width*pixelSize; i+=pixelSize) {
		for(int j = startIndex; j < endIndex+1;j++) {
			if(imageData[i+j]+decAmt > 255)
				imageData[i+j] = 255;
			else
				imageData[i+j] += decAmt;
		}
	}
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

void Image::fastBlur(int blurSize) {
	fastBlurHor(blurSize);
	fastBlurVert(blurSize);
/*
	unsigned char *blurImage = (unsigned char*)malloc(width*height*4);

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
					for (int kx = -blurSize; kx <= blurSize ; kx++) {
						if(x+kx+((y+ky)*width) > 0 && x+kx+((y+ky)*width) < width*height) {
							pixel = (unsigned char*)&(imageData32[(x+kx)+((y+ky)*width)]);
							total_r += pixel[0];
							total_g += pixel[1];
							total_b += pixel[2];
							total_a += pixel[3];
							amt++;
						}
					}
				}
				
//				Logger::log("%d / %d = %d\n",total_r, amt, (total_r/amt));
				blurImage[((x+(y*width))*4)] = (total_r/amt);
				blurImage[((x+(y*width))*4)+1] = (total_g / amt);
				blurImage[((x+(y*width))*4)+2] = (total_b / amt);
				blurImage[((x+(y*width))*4)+3] = (total_a / amt);
				
            }
        }

	imageData = (char*)blurImage;
//	free(imageData32);
*/
}

void Image::swap(int *v1, int *v2) {
	int tv = *v1;
	*v1 = *v2;
	*v2 = tv;
}

void Image::line(int x0, int y0, int x1, int y1, Color col) {
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

void Image::fill(Number r, Number g, Number b, Number a) {
	Color *color = new Color(r,g,b,a);
	unsigned int val = color->getUint();
	unsigned int *imageData32 = (unsigned int*) imageData;
	for(int i=0; i< width*height; i++) {
		imageData32[i] = val;
	}
}

bool Image::loadImage(String fileName) {
	return loadPNG(fileName);
}

bool Image::loadPNG(String fileName) {
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
		Logger::log("Error opening png file\n");	
		return false;
	}
	
	OSBasics::read(sig, 1, 8, infile);
	
	if (!png_check_sig((unsigned char *) sig, 8)) {
		Logger::log("Error reading png signature\n");
		OSBasics::close(infile);
		return false;
	}

	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) {
		Logger::log("Error creating png struct\n");
		OSBasics::close(infile);
		return false;    /* out of memory */
	}
	
	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		Logger::log("Error creating info struct\n");		
		png_destroy_read_struct(&png_ptr, (png_infopp) NULL, (png_infopp) NULL);
		OSBasics::close(infile);
		return false;    /* out of memory */
	}
	
	if (setjmp(png_jmpbuf(png_ptr))) {
		Logger::log("Error setting jump thingie\n");
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
		Logger::log("Error allocating image memory\n");		
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		return false;
    }
	
	if ((row_pointers = (png_bytepp)malloc(height*sizeof(png_bytep))) == NULL) {
		Logger::log("Error allocating image memory\n");
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
