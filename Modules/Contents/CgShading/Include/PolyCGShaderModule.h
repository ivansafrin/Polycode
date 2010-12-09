/*
 *  PolyCGShader.h
 *  Poly
 *
 *  Created by Ivan Safrin on 9/20/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
// @package Materials

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
