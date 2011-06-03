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

#include "Polycode.h"
#include "PolyGLSLProgram.h"
#include "PolyGLSLShader.h"
#include "PolyMaterial.h"
#include "PolyGLTexture.h"
#include <string>
#include <vector>

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/glu.h>	
#else
#include <GL/gl.h>	
#include <GL/glu.h>	
#include <GL/glext.h>
#endif


using std::vector;
using std::string;

namespace Polycode {
	
	class _PolyExport GLSLShaderModule : public PolycodeShaderModule {
		public:
			GLSLShaderModule();
			virtual ~GLSLShaderModule();
		
			bool acceptsExtension(String extension);
			Resource* createProgramFromFile(String extension, String fullPath);	
			void reloadPrograms();
			String getShaderType();
			Shader *createShader(TiXmlNode *node);
			bool applyShaderMaterial(Renderer *renderer, Material *material, ShaderBinding *localOptions, unsigned int shaderIndex);	
			void clearShader();
		
	protected:

		void addParamToProgram(GLSLProgram *program,TiXmlNode *node);		
		void recreateGLSLProgram(GLSLProgram *prog, String fileName, int type);
		GLSLProgram *createGLSLProgram(String fileName, int type);		
		void updateGLSLParam(Renderer *renderer, GLSLProgramParam &param, ShaderBinding *materialOptions, ShaderBinding *localOptions);		
			
		void setGLSLAreaLightPositionParameter(Renderer *renderer, GLSLProgramParam &param, int lightIndex);
		void setGLSLAreaLightColorParameter(Renderer *renderer, GLSLProgramParam &param, int lightIndex);	
		
		void setGLSLSpotLightPositionParameter(Renderer *renderer, GLSLProgramParam &param, int lightIndex);
		void setGLSLSpotLightDirectionParameter(Renderer *renderer, GLSLProgramParam &param, int lightIndex);
		void setGLSLSpotLightColorParameter(Renderer *renderer, GLSLProgramParam &param, int lightIndex);	
		void setGLSLSpotLightTextureMatrixParameter(Renderer *renderer, GLSLProgramParam &param, int lightIndex);		
		
//		GLSLcontext GLSLContext;
//		GLSLprofile vertexProfile;
//		GLSLprofile fragmentProfile;
		
		vector<GLSLProgram*> programs;
	};
	
}
