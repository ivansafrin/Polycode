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

#include "PolyGLHeaders.h"

#include "PolyGLTexture.h"
#include "PolyCoreServices.h"
#include "PolyRenderer.h"

using namespace Polycode;

#ifdef _WINDOWS
extern PFNGLDELETEFRAMEBUFFERSEXTPROC glDeleteFramebuffersEXT;
#endif

OpenGLTexture::OpenGLTexture(unsigned int width, unsigned int height, char *textureData, bool clamp, bool createMipmaps, int filteringMode, int type) : Texture(width, height, textureData,clamp, createMipmaps, type) {
	this->filteringMode = filteringMode;
	glTextureLoaded = false;
	frameBufferID = FRAMEBUFFER_NULL;

	switch(type) {
		case Image::IMAGE_RGB:
			glTextureType = GL_RGB;
			glTextureFormat = GL_RGB;
			pixelType = GL_UNSIGNED_BYTE;
		break;
		case Image::IMAGE_FP16:
			glTextureType = GL_RGBA;
			glTextureFormat = GL_RGBA16F_ARB;
			pixelType = GL_FLOAT;
		break;
		default:
			glTextureType = GL_RGBA;
			glTextureFormat = GL_RGBA;
			pixelType = GL_UNSIGNED_BYTE;
		break;
	}

	recreateFromImageData();
}

void OpenGLTexture::recreateFromImageData() {

	Number anisotropy = CoreServices::getInstance()->getRenderer()->getAnisotropyAmount();

	if(glTextureLoaded) {
		glDeleteTextures(1, &textureID);
	}

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	if(clamp) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	} else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	switch(filteringMode) {
		case Renderer::TEX_FILTERING_LINEAR:

			if(anisotropy > 0) {
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropy);
			}

			if(createMipmaps) {
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				if(textureData) {
					gluBuild2DMipmaps(GL_TEXTURE_2D, glTextureFormat, width, height, glTextureType, pixelType, textureData );
				}
			} else {
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				if(textureData) {
					glTexImage2D(GL_TEXTURE_2D, 0, glTextureFormat, width, height, 0, glTextureType, pixelType, textureData);
				}
			}
			break;
		case Renderer::TEX_FILTERING_NEAREST:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			if(textureData) {
				glTexImage2D(GL_TEXTURE_2D, 0, glTextureFormat, width, height, 0, glTextureType, pixelType, textureData);
			}
			break;
	}

	glTextureLoaded = true;
}

OpenGLTexture::OpenGLTexture(unsigned int width, unsigned int height) : Texture(width, height, NULL ,true, true) {

}

void OpenGLTexture::setGLInfo(GLuint textureID, GLuint frameBufferID) {
	this->textureID = textureID;
	this->frameBufferID = frameBufferID;
}

void OpenGLTexture::setTextureData(char *data) {
/*
	glBindTexture(GL_TEXTURE_2D, textureID);
	glDrawBuffer(GL_AUX0);
	glDrawPixels(width, height, glTextureType, pixelType, data);
	glReadBuffer(GL_AUX0);
//	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, 128, 128, 0);
*/
}

OpenGLTexture::~OpenGLTexture() {
	glDeleteTextures(1, &textureID);
	if(frameBufferID != FRAMEBUFFER_NULL) {
		glDeleteFramebuffersEXT(1, &frameBufferID);
	}
}

GLuint OpenGLTexture::getFrameBufferID() {
	return frameBufferID;
}

GLuint OpenGLTexture::getTextureID() {
	return textureID;
}
