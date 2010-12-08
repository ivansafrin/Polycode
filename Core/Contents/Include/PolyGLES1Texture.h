/*
 *  PolyGLES1Texture.h
 *  Poly
 *
 *  Created by Ivan Safrin on 2/1/10.
 *  Copyright 2010 Ivan Safrin. All rights reserved.
 *
 */

// @package Renderer

#pragma once

#include "PolyGlobals.h"
#include "PolyTexture.h"
#include "PolyGLES1Renderer.h"

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

namespace Polycode {
	
	class _PolyExport OpenGLES1Texture : public Texture {
	public:
		OpenGLES1Texture(unsigned int width, unsigned int height);
		OpenGLES1Texture(unsigned int width, unsigned int height, char *textureData, bool clamp, int filteringMode);
		virtual ~OpenGLES1Texture();
		
		void recreateFromImageData();
		
		GLuint getTextureID();
		GLuint getFrameBufferID();
		
		void setGLInfo(GLuint textureID, GLuint frameBufferID);
		
		void setTextureData(char *data);
		
	private:
		
		int filteringMode;
		GLuint textureID;
		GLuint frameBufferID;
	};
	
}