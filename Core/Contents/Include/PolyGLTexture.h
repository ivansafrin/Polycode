/*
 *  PolyGLTexture.h
 *  Poly
 *
 *  Created by Ivan Safrin on 3/16/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

// @package Renderer
 
#pragma once

#ifdef _WINDOWS
	#include <windows.h>
#endif

#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolyTexture.h"
#include "PolyGLRenderer.h"
#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/glu.h>	
#else
#include <GL/gl.h>	
#include <GL/glu.h>	
#endif


namespace Polycode {

	class _PolyExport OpenGLTexture : public Texture {
		public:
			OpenGLTexture(unsigned int width, unsigned int height);
			OpenGLTexture(unsigned int width, unsigned int height, char *textureData, bool clamp, int filteringMode, int type);
			virtual ~OpenGLTexture();
			
			void recreateFromImageData();

			GLuint getTextureID();
			GLuint getFrameBufferID();
			
			void setGLInfo(GLuint textureID, GLuint frameBufferID);
			
			void setTextureData(char *data);
			
		private:
			
			bool glTextureLoaded;
			GLuint glTextureType;
			int filteringMode;
			GLuint textureID;
			GLuint frameBufferID;
	};

}