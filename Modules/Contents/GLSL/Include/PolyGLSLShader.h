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

#include "PolyLogger.h"
#include "PolyShader.h"
#include "PolyGLSLProgram.h"
#include "PolyTexture.h"
#include "PolyCubemap.h"
#include <vector>

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/glu.h>	
#else
#include <GL/gl.h>	
#include <GL/glu.h>	
#include <GL/glext.h>
#ifdef _WINDOWS
#include <GL/wglext.h>
#endif
#endif


using std::vector;

namespace Polycode {

	typedef struct {
		Texture *texture;
		String name;
	} GLSLTextureBinding;

	typedef struct {
		Cubemap *cubemap;
		String name;
	} GLSLCubemapBinding;
	
	
	class _PolyExport GLSLShader : public Shader {
		public:
			GLSLShader(GLSLProgram *vp, GLSLProgram *fp);
			virtual ~GLSLShader();

			ShaderBinding *createBinding();
			
			unsigned int shader_id;		
			GLSLProgram *vp;
			GLSLProgram *fp;			
			
		protected:
			
	};
	
	class _PolyExport GLSLShaderBinding : public ShaderBinding {
		public:
			GLSLShaderBinding(GLSLShader *shader);
			virtual ~GLSLShaderBinding();
			
			void addTexture(String name, Texture *texture); 
			void addCubemap(String name, Cubemap *cubemap);				
			void clearTexture(String name);			
			void addParam(String type, String name, String value);
			
			vector<GLSLTextureBinding> textures;
			vector<GLSLCubemapBinding> cubemaps;		
		
			GLSLShader *glslShader;
	};
}
