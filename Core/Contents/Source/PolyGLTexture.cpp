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

#include "PolyGLTexture.h"
#include "PolyRenderer.h"

using namespace Polycode;

OpenGLTexture::OpenGLTexture(unsigned int width, unsigned int height, char *textureData, bool clamp, int filteringMode, int type) : Texture(width, height, textureData,clamp, type) {
	this->filteringMode = filteringMode;
	glTextureLoaded = false;
	
	glTextureType = GL_RGBA;
	if(type == Image::IMAGE_RGB) {
		glTextureType = GL_RGB;		
	} 
	
	recreateFromImageData();
}

void OpenGLTexture::recreateFromImageData() {
	
	if(glTextureLoaded)
		glDeleteTextures(1, &textureID);
	
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
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			break;
		case Renderer::TEX_FILTERING_NEAREST:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);		
			break;
	}	
	
	if(textureData) {
		glTexImage2D(GL_TEXTURE_2D, 0, glTextureType, width, height, 0, glTextureType, GL_UNSIGNED_BYTE, textureData);							
//		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, glTextureType, width, height, glTextureType, GL_UNSIGNED_BYTE, textureData);
	}
	glTextureLoaded = true;
}

OpenGLTexture::OpenGLTexture(unsigned int width, unsigned int height) : Texture(width, height, NULL ,true) {

}

void OpenGLTexture::setGLInfo(GLuint textureID, GLuint frameBufferID) {
	this->textureID = textureID;
	this->frameBufferID = frameBufferID;
}

void OpenGLTexture::setTextureData(char *data) {
	glBindTexture(GL_TEXTURE_2D, textureID);
	glDrawBuffer(GL_AUX0);
	glDrawPixels(width, height, glTextureType, GL_UNSIGNED_BYTE, data);
	glReadBuffer(GL_AUX0);
//	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, 128, 128, 0);
}

OpenGLTexture::~OpenGLTexture() {
	glDeleteTextures(1, &textureID);
}

GLuint OpenGLTexture::getFrameBufferID() {
	return frameBufferID;
}

GLuint OpenGLTexture::getTextureID() {
	return textureID;
}
