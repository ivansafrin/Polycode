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

#include "PolyModule.h"

namespace Polycode {
	
	class GLSLProgram;
	class ProgramParam;
	class GLSLShader;
	class ShaderProgram;
    class ResourcePool;

	class _PolyExport GLSLShaderModule : public PolycodeShaderModule {
		public:
			GLSLShaderModule();
			virtual ~GLSLShaderModule();
		
			bool acceptsExtension(const String& extension);
			ShaderProgram* createProgramFromFile(const String& extension, const String& fullPath);
			void reloadPrograms();
			String getShaderType();
			Shader *createShader(ResourcePool *resourcePool, TiXmlNode *node);
			Shader *createShader(ResourcePool *resourcePool, String name, String vpName, String fpName);
			bool applyShaderMaterial(Renderer *renderer, Material *material, ShaderBinding *localOptions, unsigned int shaderIndex);	
			void clearShader();
		
	protected:
		
		GLSLProgram *createGLSLProgram(const String& fileName, int type);
		void updateGLSLParam(Renderer *renderer, GLSLShader *glslShader, ProgramParam &param, ShaderBinding *materialOptions, ShaderBinding *localOptions);			
		
		std::vector<GLSLProgram*> programs;
	};
	
}
