/*
 *  PolyMaterial.h
 *  Poly
 *
 *  Created by Ivan Safrin on 9/19/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
// @package Materials

#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"
#include <string>
#include <vector>
#include "PolyTexture.h"
#include "PolyShader.h"
#include "PolyResource.h"


using std::string;
using std::vector;

namespace Polycode {
	
	class _PolyExport Material : public Resource {
		public:
			Material(String name);
			virtual ~Material();
			
			void addShader(Shader *shader,ShaderBinding *shaderBinding);
			unsigned int getNumShaders();
			
			void addShaderRenderTarget(ShaderRenderTarget *newTarget);
			int getNumShaderRenderTargets();
			ShaderRenderTarget *getShaderRenderTarget(unsigned int index);
				
			String getName();
			Shader *getShader(unsigned int index);
			ShaderBinding *getShaderBinding(unsigned int index);
			void loadMaterial(String fileName);
			
		protected:
		
			vector<Shader*> materialShaders;
			vector<ShaderBinding*> shaderBindings;
			vector<ShaderRenderTarget*> renderTargets;
					
			String name;
		
	};
}