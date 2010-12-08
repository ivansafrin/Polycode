/*
 *  PolyShader.h
 *  Poly
 *
 *  Created by Ivan Safrin on 9/20/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
// @package Materials

#pragma once
#include "PolyGlobals.h"
#include "PolyResource.h"
#include "PolyTexture.h"
#include "PolyCubemap.h"

namespace Polycode {

	class ShaderBinding;
	class _PolyExport Shader : public Resource {
		public:
			Shader(int type);
			virtual ~Shader();

			int getType();
			void setName(string name);
			string getName();
			
			virtual ShaderBinding *createBinding() = 0;

			static const int FIXED_SHADER = 0;
			static const int MODULE_SHADER = 1;
							
		protected:
		
			string name;
			int type;
	};
	
	class _PolyExport ShaderRenderTarget {
		public:
			string id;
			float width;
			float height;
			int sizeMode;
			bool hasSize;
			Texture *texture;
			
			static const int SIZE_MODE_PIXELS = 0;
			static const int SIZE_MODE_NORMALIZED = 1;
	};
	
	typedef struct {
		string name;
		void *data;		
	} LocalShaderParam;	
	
	typedef struct {
			string id;
			string name;
			int mode;
			Texture *texture;
			float width;
			float height;			
			static const int MODE_IN= 0;
			static const int MODE_OUT = 1;
	} RenderTargetBinding;

	class _PolyExport ShaderBinding {
		public:
			ShaderBinding(Shader *shader);
			virtual ~ShaderBinding();
			
			virtual void clearTexture(string name){};
			virtual void addTexture(string name, Texture *texture)  {};
			virtual void addParam(string type, string name, string value) {};
			virtual void addCubemap(string name, Cubemap *cubemap) {};
		
			unsigned int getNumLocalParams();
			LocalShaderParam *getLocalParam(unsigned int index);
			LocalShaderParam *getLocalParamByName(string name);
			
			void addRenderTargetBinding(RenderTargetBinding *binding);

			unsigned int getNumRenderTargetBindings();
			RenderTargetBinding *getRenderTargetBinding(unsigned int index);

			unsigned int getNumInTargetBindings();
			RenderTargetBinding *getInTargetBinding(unsigned int index);

			unsigned int getNumOutTargetBindings();
			RenderTargetBinding *getOutTargetBinding(unsigned int index);

			
			Shader* shader;
			vector<LocalShaderParam*> localParams;
			vector<RenderTargetBinding*> renderTargetBindings;
			vector<RenderTargetBinding*> inTargetBindings;
			vector<RenderTargetBinding*> outTargetBindings;
	};

}