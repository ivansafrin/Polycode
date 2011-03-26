/*
 *  PolyGLSLShader.h
 *  Poly
 *
 *  Created by Ivan Safrin on 9/20/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
// @package Materials

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
