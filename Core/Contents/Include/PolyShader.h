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
#include "PolyColor.h"
#include "PolyVector2.h"
#include "PolyVector3.h"
#include "PolyMatrix4.h"
#include "PolyResource.h"
#include <string.h>

namespace Polycode {

	class Cubemap;
	class ShaderBinding;
	class Texture;
	
	class _PolyExport ProgramParam {
		public:
	
	String name;
	int type;

	static void *createParamData(int type);
	
	static const int PARAM_UNKNOWN = 0;	
	static const int PARAM_NUMBER = 1;
	static const int PARAM_VECTOR2 = 2;		
	static const int PARAM_VECTOR3 = 3;
	static const int PARAM_COLOR = 4;
	static const int PARAM_MATRIX = 5;
	};
	
	typedef struct {
		Texture *texture;
		String name;
	} TextureBinding;
    
	typedef struct {
		Cubemap *cubemap;
		String name;
	} CubemapBinding;

	class _PolyExport ShaderProgram : public Resource {
		public:
			explicit ShaderProgram(int type);
			virtual ~ShaderProgram();
			
			virtual void reloadProgram() {}
			
			static const int TYPE_VERT = 0;
			static const int TYPE_FRAG = 1;		
			
			int type;
			
			void reloadResource();
			
	};

	class _PolyExport Shader : public Resource {
		public:
			explicit Shader(int type);
			virtual ~Shader();

			int getType() const;
			void setName(const String& name);
			const String& getName() const;
			
			ShaderBinding *createBinding();
			virtual void reload() {}
			
			int getExpectedParamType(String name);
			
			virtual void setVertexProgram(ShaderProgram *vp) {}
			virtual void setFragmentProgram(ShaderProgram *fp) {}
			
			static const int FIXED_SHADER = 0;
			static const int MODULE_SHADER = 1;

			int numSpotLights;
			int numPointLights;
			
			std::vector<String> expectedTextures;
			std::vector<String> expectedCubemaps;			
			std::vector<ProgramParam> expectedParams;
								
			bool screenShader;
			
			ShaderProgram *vp;
			ShaderProgram *fp;			
			
		protected:
		
		
			String name;
			int type;
	};
	
	class _PolyExport ShaderRenderTarget : public PolyBase {
		public:
			ShaderRenderTarget();
			
			String id;
			Number width;
			Number height;
			int sizeMode;
			Texture *texture;			
			
			Number normalizedWidth;
			Number normalizedHeight;
						
			static const int SIZE_MODE_PIXELS = 0;
			static const int SIZE_MODE_NORMALIZED = 1;
	};
	
	class LocalShaderParam : public PolyBase {
		public:
        
            LocalShaderParam();
            ~LocalShaderParam();
            LocalShaderParam *Copy();
        
			String name;
			void *data;
			int type;
            bool ownsPointer;
            unsigned int arraySize;
		
            // Convenience getters/setters for Lua users
            Number getNumber();
            Vector2 getVector2();
            Vector3 getVector3();
            Matrix4 getMatrix4();
            Color getColor();
            void setNumber(Number x);
            void setVector2(Vector2 x);
            void setVector3(Vector3 x);
            void setMatrix4(Matrix4 x);
            void setColor(Color x);
        
            void setParamValueFromString(int type, String pvalue);
	};	
	
	class RenderTargetBinding : public PolyBase {
		public:
			String id;
			String name;
			int mode;
			Texture *texture;
			static const int MODE_IN= 0;
			static const int MODE_OUT = 1;
			static const int MODE_COLOR = 2;
			static const int MODE_DEPTH = 3;			
	};

	class _PolyExport ShaderBinding : public PolyBase {
		public:
			ShaderBinding(Shader *shader);
			virtual ~ShaderBinding();
        
            void copyTo(ShaderBinding *targetBinding);

            Texture *getTexture(const String& name);
            Cubemap *getCubemap(const String& name);
			void clearTexture(const String& name);
			void clearCubemap(const String& name);
            void addTexture(const String& name, Texture *texture);
            void addCubemap(const String& name, Cubemap *cubemap);
        
			LocalShaderParam *addParam(int type, const String& name);
			LocalShaderParam *addParamPointer(int type, const String& name, void *ptr);        
			unsigned int getNumLocalParams();
			LocalShaderParam *getLocalParam(unsigned int index);
			LocalShaderParam *getLocalParamByName(const String& name);
			
			void addRenderTargetBinding(RenderTargetBinding *binding);
			void removeRenderTargetBinding(RenderTargetBinding *binding);

			unsigned int getNumRenderTargetBindings();
			RenderTargetBinding *getRenderTargetBinding(unsigned int index);

			unsigned int getNumInTargetBindings();
			RenderTargetBinding *getInTargetBinding(unsigned int index);

			unsigned int getNumColorTargetBindings();
			RenderTargetBinding *getColorTargetBinding(unsigned int index);

			unsigned int getNumDepthTargetBindings();
			RenderTargetBinding *getDepthTargetBinding(unsigned int index);

			unsigned int getNumOutTargetBindings();
			RenderTargetBinding *getOutTargetBinding(unsigned int index);
			            
            std::vector<TextureBinding> textures;
            std::vector<CubemapBinding> cubemaps;
		
			Shader* shader;
			std::vector<LocalShaderParam*> localParams;
			std::vector<RenderTargetBinding*> renderTargetBindings;
			std::vector<RenderTargetBinding*> inTargetBindings;
			std::vector<RenderTargetBinding*> outTargetBindings;
			std::vector<RenderTargetBinding*> colorTargetBindings;
			std::vector<RenderTargetBinding*> depthTargetBindings;			
	};

}
