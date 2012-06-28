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
#include "PolyTexture.h"

#ifdef _WINDOWS
#include <windows.h>
#endif

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/glu.h>	
#else
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#endif

#define FRAMEBUFFER_NULL 999999

namespace Polycode {

	class _PolyExport OpenGLTexture : public Texture {
		public:
			OpenGLTexture(unsigned int width, unsigned int height);
			OpenGLTexture(unsigned int width, unsigned int height, char *textureData, bool clamp, bool createMipmaps, int filteringMode, int type);
			virtual ~OpenGLTexture();
			
			void recreateFromImageData();

			GLuint getTextureID();
			GLuint getFrameBufferID();
			
			void setGLInfo(GLuint textureID, GLuint frameBufferID);
			
			void setTextureData(char *data);
			
		private:
			
			bool glTextureLoaded;
			GLenum glTextureType;
			GLuint glTextureFormat;
			GLenum pixelType;
			
			int filteringMode;
			GLuint textureID;
			GLuint frameBufferID;
	};

}
