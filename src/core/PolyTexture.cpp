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

#include "string.h"
#include "polycode/core/PolyTexture.h"
#include "polycode/core/PolyImage.h"
#include "polycode/core/PolyCoreServices.h"
#include "polycode/core/PolyRenderer.h"
#include <stdlib.h>

using namespace Polycode;

bool Texture::premultiplyAlphaOnLoad = false;
bool Texture::clampDefault = true;
bool Texture::mipmapsDefault = true;
bool Texture::keepTextureData = true;
int Texture::defaultTextureFiltering = 1;

Texture::Texture() : Resource(Resource::RESOURCE_TEXTURE), width(0), height(0), clamp(false), type(Image::IMAGE_RGBA), createMipmaps(false), filteringMode(defaultTextureFiltering), anisotropy(0), framebufferTexture(false), depthTexture(false) {
	filteringMode = defaultTextureFiltering;
}

Texture::Texture(unsigned int width, unsigned int height, char *textureData,bool clamp, bool createMipmaps, int type, bool framebufferTexture) : Resource(Resource::RESOURCE_TEXTURE), width(width), height(height), clamp(clamp), type(type), createMipmaps(createMipmaps), filteringMode(defaultTextureFiltering), anisotropy(0), framebufferTexture(framebufferTexture), depthTexture(false) {
	
	switch(type) {
		case Image::IMAGE_RGB:
			pixelSize = 3;			
			break;
		case Image::IMAGE_RGBA:
			pixelSize = 4;						
		break;
		case Image::IMAGE_FP16:		
			pixelSize = 6;
		break;
		default:
			pixelSize = 4;								
		break;
	}
	
	if(!framebufferTexture) {
		this->textureData = (char*)malloc(width*height*pixelSize);
		if(textureData)
			memcpy(this->textureData, textureData, width*height*pixelSize); 
		else
			memset(this->textureData, 0, width*height*pixelSize);
	} else {
		this->textureData = NULL;
	}

}

void Texture::reloadResource() {
	Image *image = new Image(getResourcePath());
	setImageData(image);
	delete image;
	Resource::reloadResource(); 
}

int Texture::getWidth() const {
	return width;
}

int Texture::getHeight() const {
	return height;
}

Texture::~Texture(){
	if(platformData) {
		Services()->getRenderer()->destroyTexturePlatformData(platformData);
	}
	free(textureData);
}

void Texture::setImageData(Image *data) {

	switch (data->getType()) {
		case Image::IMAGE_RGB:
			pixelSize = 3;			
		break;
		case Image::IMAGE_RGBA:
			pixelSize = 4;						
		break;
		case Image::IMAGE_FP16:		
			pixelSize = 6;
		break;
		default:
			pixelSize = 4;								
		break;
	}

	width = data->getWidth();
	height = data->getHeight();
	
	if(this->textureData)
		free(this->textureData);
	this->textureData = (char*)malloc(width*height*pixelSize);
	memcpy(this->textureData, data->getPixels(), width*height*pixelSize);

}

Texture::Texture(Image *image, bool clamp, bool createMipmaps) : Resource(Resource::RESOURCE_TEXTURE), clamp(clamp),  createMipmaps(createMipmaps), filteringMode(defaultTextureFiltering), anisotropy(0), framebufferTexture(false), depthTexture(false) {

	Image *targetImage = image;
	pixelSize = 4;

	switch (image->getType()) {
		case Image::IMAGE_RGB:
			pixelSize = 3;
			break;
		case Image::IMAGE_RGBA:
			pixelSize = 4;
			break;
		case Image::IMAGE_FP16:
			pixelSize = 6;
			break;
		default:
			pixelSize = 4;
			break;
	}

	if (premultiplyAlphaOnLoad) {
		targetImage = new Image(image);
		targetImage->premultiplyAlpha();
	}
	
	width = image->getWidth();
	height = image->getHeight();


	type = targetImage->getType();
	this->textureData = (char*)malloc(targetImage->getWidth()*targetImage->getHeight()*pixelSize);
	memcpy(this->textureData, targetImage->getPixels(), targetImage->getWidth()*targetImage->getHeight()*pixelSize);

	if (premultiplyAlphaOnLoad) {
		delete targetImage;
	}

}

RenderBuffer::RenderBuffer(unsigned int width, unsigned int height, bool attachDepthBuffer, bool floatingPoint) : platformData(NULL), width(width), height(height), depthBufferPlatformData(NULL), floatingPoint(floatingPoint) {
	
	int imageType = Image::IMAGE_RGBA;
	if(floatingPoint) {
		imageType = Image::IMAGE_FP16;
	}
	colorTexture = std::make_shared<Texture>(width, height, nullptr, false, false, imageType, true);
	if(attachDepthBuffer) {
		depthTexture = std::make_shared<Texture>(width, height, nullptr, false, false, 1, true);
	} else {
		depthTexture = nullptr;
	}
	
}

RenderBuffer::~RenderBuffer() {
	if(platformData) {
		Services()->getRenderer()->destroyRenderBufferPlatformData(platformData);
	}
	if(depthBufferPlatformData) {
		Services()->getRenderer()->destroyRenderBufferPlatformData(depthBufferPlatformData);
	}
}

unsigned int RenderBuffer::getWidth() {
	return width;
}

unsigned int RenderBuffer::getHeight() {
	return height;
}

