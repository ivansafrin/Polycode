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
#include "PolyResource.h"
#include <string.h>

namespace Polycode {

	class Cubemap;
	class ShaderBinding;
	class Texture;
	
	class _PolyExport ProgramParam {
		public:
	
	String name;
	String typeString;
	String valueString;
	bool isAuto;
	int autoID;
	void *defaultData;
	void *minValue;
	void *maxValue;	
	int paramType;
			
	static const int PARAM_UNKNOWN = 0;	
	static const int PARAM_Number = 1;
	static const int PARAM_Vector2 = 2;		
	static const int PARAM_Vector3 = 3;
	static const int PARAM_Color = 4;
	
	static void createParamData(int *retType, const String& type, const String& value, const String& min, const String& max, void **valueRes, void **minRes, void **maxRes);	
	
	
	};	

	class _PolyExport ShaderProgram : public Resource {
		public:
			ShaderProgram(int type);
			virtual ~ShaderProgram();
			
			static const int TYPE_VERT = 0;
			static const int TYPE_FRAG = 1;		
			
			int type;
			
			std::vector<ProgramParam> params;
			
			ProgramParam addParam(const String& name, const String& typeString, const String& valueString, bool isAuto, int autoID, int paramType, void *defaultData, void *minData, void *maxData);
					
	};

	class _PolyExport Shader : public Resource {
		public:
			Shader(int type);
			virtual ~Shader();

			int getType() const;
			void setName(const String& name);
			const String& getName() const;
			
			virtual ShaderBinding *createBinding() = 0;
			virtual void reload() {}
			
			virtual void setVertexProgram(ShaderProgram *vp) {}
			virtual void setFragmentProgram(ShaderProgram *fp) {}
			
			static const int FIXED_SHADER = 0;
			static const int MODULE_SHADER = 1;

			int numSpotLights;
			int numAreaLights;
			
			std::vector<String> expectedTextures;
			std::vector<ProgramParam> expectedFragmentParams;
			std::vector<ProgramParam> expectedVertexParams;
								
			bool screenShader;
			
			ShaderProgram *vp;
			ShaderProgram *fp;			
			
		protected:
		
		
			String name;
			int type;
	};
	
	class _PolyExport ShaderRenderTarget : public PolyBase {
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
	
	class LocalShaderParam : public PolyBase {
		public:	
			String name;
			void *data;
		
		// Convenience getters/setters for Lua users
		Number getNumber()         { return *((Number *)data); }
		Vector2 getVector2()       { return *((Vector2 *)data); }
		Vector3 getVector3()       { return *((Vector3 *)data); }
		Color getColor()           { return *((Color *)data); }
		void setNumber(Number x)   { memcpy(data, &x, sizeof(x)); }
		void setVector2(Vector2 x) { memcpy(data, &x, sizeof(x)); }
		void setVector3(Vector3 x) { memcpy(data, &x, sizeof(x)); }
		void setColor(Color x)     { memcpy(data, &x, sizeof(x)); }
	};	
	
	class RenderTargetBinding : public PolyBase {
		public:
			String id;
			String name;
			int mode;
			Texture *texture;
			Number width;
			Number height;			
			static const int MODE_IN= 0;
			static const int MODE_OUT = 1;
	};

	class _PolyExport ShaderBinding : public PolyBase {
		public:
			ShaderBinding(Shader *shader);
			virtual ~ShaderBinding();

			virtual Texture *getTexture(const String& name){ return NULL;};
			virtual void clearTexture(const String& name){};
			virtual void addTexture(const String& name, Texture *texture)  {};
			virtual void addParam(const String& type, const String& name, const String& value) {};
			virtual void addCubemap(const String& name, Cubemap *cubemap) {};
		
			unsigned int getNumLocalParams();
			LocalShaderParam *getLocalParam(unsigned int index);
			LocalShaderParam *getLocalParamByName(const String& name);
			
			void addRenderTargetBinding(RenderTargetBinding *binding);

			unsigned int getNumRenderTargetBindings();
			RenderTargetBinding *getRenderTargetBinding(unsigned int index);

			unsigned int getNumInTargetBindings();
			RenderTargetBinding *getInTargetBinding(unsigned int index);

			unsigned int getNumOutTargetBindings();
			RenderTargetBinding *getOutTargetBinding(unsigned int index);
			
			LocalShaderParam *addLocalParam(const String& name, void *ptr);
		
			Shader* shader;
			std::vector<LocalShaderParam*> localParams;
			std::vector<RenderTargetBinding*> renderTargetBindings;
			std::vector<RenderTargetBinding*> inTargetBindings;
			std::vector<RenderTargetBinding*> outTargetBindings;
	};

}
