/*
 *  PolyFixedShader.h
 *  Poly
 *
 *  Created by Ivan Safrin on 9/20/08.
 *  Copyright 2008 Ivan Safrin. All rights reserved.
 *
 */
// @package Materials

#pragma once
#include "PolyString.h"
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
			
			void addTexture(String name, Texture *texture); 
			void addCubemap(String name, Cubemap *cubemap);		
			void addParam(String type, String name, String value);
			
			Texture *getDiffuseTexture();
			
		protected:

			vector<Texture*> textures;
			vector<Cubemap*> cubemaps;		
			FixedShader *fixedShader;
	};

}