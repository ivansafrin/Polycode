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
#include "PolyString.h"
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
			void setName(String name);
			String getName();
			
			virtual ShaderBinding *createBinding() = 0;

			static const int FIXED_SHADER = 0;
			static const int MODULE_SHADER = 1;

			int numSpotLights;
			int numAreaLights;
							
		protected:
		
			String name;
			int type;
	};
	
	class _PolyExport ShaderRenderTarget {
		public:
			String id;
			Number width;
			Number height;
			int sizeMode;
			bool hasSize;
			Texture *texture;
			
			static const int SIZE_MODE_PIXELS = 0;
			static const int SIZE_MODE_NORMALIZED = 1;
	};
	
	typedef struct {
		String name;
		void *data;		
	} LocalShaderParam;	
	
	typedef struct {
			String id;
			String name;
			int mode;
			Texture *texture;
			Number width;
			Number height;			
			static const int MODE_IN= 0;
			static const int MODE_OUT = 1;
	} RenderTargetBinding;

	class _PolyExport ShaderBinding {
		public:
			ShaderBinding(Shader *shader);
			virtual ~ShaderBinding();
			
			virtual void clearTexture(String name){};
			virtual void addTexture(String name, Texture *texture)  {};
			virtual void addParam(String type, String name, String value) {};
			virtual void addCubemap(String name, Cubemap *cubemap) {};
		
			unsigned int getNumLocalParams();
			LocalShaderParam *getLocalParam(unsigned int index);
			LocalShaderParam *getLocalParamByName(String name);
			
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