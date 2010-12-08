/*
 *  PolyGLCubemap.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 9/9/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolyGLCubemap.h"

using namespace Polycode;

OpenGLCubemap::OpenGLCubemap(Texture *t0, Texture *t1, Texture *t2, Texture *t3, Texture *t4, Texture *t5) : Cubemap(t0,t1,t2,t3,t4,t5) {
	
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);	
	
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+0, 0, GL_RGBA, t0->getWidth(), t0->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t0->getTextureData());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+1, 0, GL_RGBA, t1->getWidth(), t1->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t1->getTextureData());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+2, 0, GL_RGBA, t2->getWidth(), t2->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t2->getTextureData());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+3, 0, GL_RGBA, t3->getWidth(), t3->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t3->getTextureData());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+4, 0, GL_RGBA, t4->getWidth(), t4->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t4->getTextureData());	
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+5, 0, GL_RGBA, t5->getWidth(), t5->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t5->getTextureData());		
	
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

OpenGLCubemap::~OpenGLCubemap() {

}

GLuint OpenGLCubemap::getTextureID() {
	return textureID;
}