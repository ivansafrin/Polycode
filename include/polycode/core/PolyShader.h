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
#include "polycode/core/PolyString.h"
#include "polycode/core/PolyGlobals.h"
#include "polycode/core/PolyColor.h"
#include "polycode/core/PolyVector2.h"
#include "polycode/core/PolyVector3.h"
#include "polycode/core/PolyMatrix4.h"
#include "polycode/core/PolyResource.h"
#include <string.h>
#include <memory>
#include <mutex>

namespace Polycode {

	class Cubemap;
	class ShaderBinding;
	class Texture;
	class VertexDataArray;
	class LocalShaderParam;
	class RenderBuffer;
    class Core;
	
	class _PolyExport ProgramParam {
		public:
	
		ProgramParam();
		
		String name;
		int type;
		void *platformData;
		LocalShaderParam *globalParam;

		static void *createParamData(int type);
		
		static const int PARAM_UNKNOWN = 0; 
		static const int PARAM_NUMBER = 1;
		static const int PARAM_VECTOR2 = 2;		
		static const int PARAM_VECTOR3 = 3;
		static const int PARAM_COLOR = 4;
		static const int PARAM_MATRIX = 5;
		static const int PARAM_TEXTURE = 6;
		static const int PARAM_CUBEMAP = 7;
	};
	
	class _PolyExport ProgramAttribute {
		public:
			ProgramAttribute();
		
			int size;
			String name;
			int arrayType;
			void *platformData;
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
			explicit ShaderProgram(const String &fileName);
			explicit ShaderProgram(const String &fileName, int type);
			virtual ~ShaderProgram();
			
			virtual void reloadProgram() {}
			static const int TYPE_VERT = 0;
			static const int TYPE_FRAG = 1;
			int type;
			void reloadResource(Core *core);
	};

	class _PolyExport Shader : public Resource {
		public:
			explicit Shader();
			Shader(std::shared_ptr<ShaderProgram> vp, std::shared_ptr<ShaderProgram> fp);
			virtual ~Shader();

			int getType() const;
			void setName(const String& name);
			const String& getName() const;
			
			ProgramParam *getParamPointer(const String &name);
			ProgramAttribute *getAttribPointer(const String &name);
		
			virtual void reload() {}
			
			int getExpectedParamType(String name);

			int numSpotLights;
			int numPointLights;
						
			std::vector<ProgramParam> expectedParams;
			std::vector<ProgramAttribute> expectedAttributes;
								
			bool screenShader;
			
			std::shared_ptr<ShaderProgram> vertexProgram;
			std::shared_ptr<ShaderProgram> fragmentProgram;
		
			String name;
	};
	
	class _PolyExport ShaderRenderTarget : public PolyBase {
		public:
			ShaderRenderTarget();
			
			String id;
			Number width;
			Number height;
			int sizeMode;
			std::shared_ptr<RenderBuffer> buffer;
			
			Number normalizedWidth;
			Number normalizedHeight;
						
			static const int SIZE_MODE_PIXELS = 0;
			static const int SIZE_MODE_NORMALIZED = 1;
	};
	
	class LocalShaderParam : public PolyBase {
		public:
		
			LocalShaderParam();
			~LocalShaderParam();
			std::shared_ptr<LocalShaderParam> Copy();
		
			String name;
			void *data;
			int type;
			bool ownsPointer;
			unsigned int arraySize;
			ProgramParam *param;
		
			std::shared_ptr<Texture> texturePtr;
			std::shared_ptr<Cubemap> cubemapPtr;
		
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
            void setMatrix4Array(std::vector<Matrix4> &x);
			void setColor(Color x);
		
			void setTexture(std::shared_ptr<Texture> texture);
			std::shared_ptr<Texture> getTexture();
		
			void setCubemap(std::shared_ptr<Cubemap> cubemap);
			std::shared_ptr<Cubemap> getCubemap();
		
			void setParamValueFromString(int type, String pvalue);
        
            std::mutex POLYIGNORE accessMutex;
	};
	
	class AttributeBinding : public PolyBase {
		public:
			AttributeBinding();
			String name;
			VertexDataArray *vertexData;
			ProgramAttribute *attribute;
			bool enabled;
	};
	
	class RenderTargetBinding : public PolyBase {
		public:
			String id;
			String name;
			int mode;
			std::shared_ptr<RenderBuffer> buffer;
			static const int MODE_IN = 0;
			static const int MODE_OUT = 1;
			static const int MODE_COLOR = 2;
			static const int MODE_DEPTH = 3;			
	};

	class _PolyExport ShaderBinding : public PolyBase {
		public:
			ShaderBinding();
			virtual ~ShaderBinding();
		
			void copyTo(ShaderBinding *targetBinding);
		
			std::shared_ptr<LocalShaderParam> addParam(int type, const String& name);
			std::shared_ptr<LocalShaderParam> addParamPointer(int type, const String& name, void *ptr);
		
			std::shared_ptr<LocalShaderParam> addParamFromData(const String &name, const String &data);
		
			unsigned int getNumLocalParams();
			std::shared_ptr<LocalShaderParam> getLocalParam(unsigned int index);
			std::shared_ptr<LocalShaderParam> getLocalParamByName(const String& name);
		
			void removeParam(const String &name);
	
			void setTextureForParam(const String &paramName, std::shared_ptr<Texture> texture);
			void setCubemapForParam(const String &paramName, std::shared_ptr<Cubemap> cubemap);
		
			unsigned int getNumAttributeBindings();
			AttributeBinding *getAttributeBinding(unsigned int index);
		
			AttributeBinding *addAttributeBinding(const String &name, VertexDataArray *dataArray);
			AttributeBinding *getAttributeBindingByName(const String &name);
			
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
		
			std::vector<std::shared_ptr<LocalShaderParam> > localParams;
			std::vector<AttributeBinding*> attributes;
		
			std::vector<RenderTargetBinding*> renderTargetBindings;
			std::vector<RenderTargetBinding*> inTargetBindings;
			std::vector<RenderTargetBinding*> outTargetBindings;
			std::vector<RenderTargetBinding*> colorTargetBindings;
			std::vector<RenderTargetBinding*> depthTargetBindings;
		
			std::shared_ptr<Shader> targetShader;		
            std::mutex POLYIGNORE accessMutex;
	};

}
