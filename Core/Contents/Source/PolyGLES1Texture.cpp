/*
 *  PolyGLES1Texture.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 2/1/10.
 *  Copyright 2010 Ivan Safrin. All rights reserved.
 *
 */

#include "PolyGLES1Texture.h"

using namespace Polycode;

OpenGLES1Texture::OpenGLES1Texture(unsigned int width, unsigned int height, char *textureData, bool clamp, int filteringMode) : Texture(width, height, textureData,clamp) {
	this->filteringMode = filteringMode;
	recreateFromImageData();
}

void OpenGLES1Texture::recreateFromImageData() {
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	if(clamp) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
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
	
	if(textureData)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);	
}

OpenGLES1Texture::OpenGLES1Texture(unsigned int width, unsigned int height) : Texture(width, height, NULL ,true) {
	
}

void OpenGLES1Texture::setGLInfo(GLuint textureID, GLuint frameBufferID) {
	this->textureID = textureID;
	this->frameBufferID = frameBufferID;
}

void OpenGLES1Texture::setTextureData(char *data) {
	/*
	glBindTexture(GL_TEXTURE_2D, textureID);
	glDrawBuffer(GL_AUX0);
	glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glReadBuffer(GL_AUX0);
	//	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, 128, 128, 0);
	 */
}

OpenGLES1Texture::~OpenGLES1Texture() {
	glDeleteTextures(1, &textureID);
}

GLuint OpenGLES1Texture::getFrameBufferID() {
	return frameBufferID;
}

GLuint OpenGLES1Texture::getTextureID() {
	return textureID;
}