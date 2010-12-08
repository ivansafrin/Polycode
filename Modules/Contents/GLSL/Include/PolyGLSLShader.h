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

#include "PolyGlobals.h"
#ifdef COMPILE_CG_SUPPORT

#include "PolyLogger.h"
#include "PolyShader.h"
#include "PolyCGProgram.h"
#include "PolyTexture.h"
#include "PolyCubemap.h"
#include <vector>
#include <CG/cg.h>

using std::vector;

namespace Polycode {

	typedef struct {
		Texture *texture;
		string name;
		CGparameter vpParam;
	} CGTextureBinding;

	typedef struct {
		Cubemap *cubemap;
		string name;
		CGparameter vpParam;
	} CGCubemapBinding;
	
	
	class _PolyExport CGShader : public Shader {
		public:
			CGShader(CGProgram *vp, CGProgram *fp);
			virtual ~CGShader();

			ShaderBinding *createBinding();
			
			CGProgram *vp;
			CGProgram *fp;			
			
		protected:
			
	};
	
	class _PolyExport CGShaderBinding : public ShaderBinding {
		public:
			CGShaderBinding(CGShader *shader);
			virtual ~CGShaderBinding();
			
			void addTexture(string name, Texture *texture); 
			void addCubemap(string name, Cubemap *cubemap);				
			void clearTexture(string name);			
			void addParam(string type, string name, string value);
			
			vector<CGTextureBinding> textures;
			vector<CGCubemapBinding> cubemaps;		
		
			CGShader *cgShader;
	};
}

#endif