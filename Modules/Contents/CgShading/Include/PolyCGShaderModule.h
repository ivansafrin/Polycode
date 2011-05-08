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
#include "PolyCGProgram.h"
#include "PolyCGShader.h"
#include "PolyMaterial.h"
#include "PolyGLTexture.h"
#include <string>
#include <vector>
#include <CG/cgGL.h>


using std::vector;
using std::string;

namespace Polycode {
	
	class _PolyExport CGShaderModule : public PolycodeShaderModule {
		public:
			CGShaderModule();
			virtual ~CGShaderModule();
		
			bool acceptsExtension(String extension);
			Resource* createProgramFromFile(String extension, String fullPath);	
			void reloadPrograms();
			String getShaderType();
			Shader *createShader(TiXmlNode *node);
			bool applyShaderMaterial(Renderer *renderer, Material *material, ShaderBinding *localOptions, unsigned int shaderIndex);	
			void clearShader();
		
	protected:

		void addParamToProgram(CGProgram *program,TiXmlNode *node);		
		void recreateCGProgram(CGProgram *prog, String fileName, int type);
		CGProgram *createCGProgram(String fileName, int type);		
		void updateCGParam(Renderer *renderer, CGProgramParam &param, ShaderBinding *materialOptions, ShaderBinding *localOptions);		
			
		void setCGAreaLightPositionParameter(Renderer *renderer, CGProgramParam &param, int lightIndex);
		void setCGAreaLightColorParameter(Renderer *renderer, CGProgramParam &param, int lightIndex);	
		
		void setCGSpotLightPositionParameter(Renderer *renderer, CGProgramParam &param, int lightIndex);
		void setCGSpotLightDirectionParameter(Renderer *renderer, CGProgramParam &param, int lightIndex);
		void setCGSpotLightColorParameter(Renderer *renderer, CGProgramParam &param, int lightIndex);	
		void setCGSpotLightTextureMatrixParameter(Renderer *renderer, CGProgramParam &param, int lightIndex);		
		
		CGcontext cgContext;
		CGprofile vertexProfile;
		CGprofile fragmentProfile;
		
		vector<CGProgram*> programs;
	};
	
}
