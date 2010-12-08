/*
 *  PolyFixedShader.h
 *  Poly
 *
 *  Created by Ivan Safrin on 9/20/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
// @package Materials

#pragma once
#include "PolyLogger.h"
#include "PolyGlobals.h"
#include "PolyShader.h"
#include "PolyTexture.h"

namespace Polycode {

	class _PolyExport FixedShader : public Shader {
		public:
			FixedShader();
			~FixedShader();
			
			ShaderBinding *createBinding();

		protected:
			
	};

	class _PolyExport FixedShaderBinding : public ShaderBinding {
		public:
			FixedShaderBinding(FixedShader *shader);
			~FixedShaderBinding();
			
			void addTexture(string name, Texture *texture); 
			void addCubemap(string name, Cubemap *cubemap);		
			void addParam(string type, string name, string value);
			
			Texture *getDiffuseTexture();
			
		protected:

			vector<Texture*> textures;
			vector<Cubemap*> cubemaps;		
			FixedShader *fixedShader;
	};

}