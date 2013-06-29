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
		int type;

		static void *createParamData(int type);

		static const int PARAM_UNKNOWN = 0;
		static const int PARAM_NUMBER = 1;
		static const int PARAM_VECTOR2 = 2;
		static const int PARAM_VECTOR3 = 3;
		static const int PARAM_COLOR = 4;
		static const int PARAM_MATRIX = 5;
};

class _PolyExport ShaderProgram : public Resource {
	public:
		ShaderProgram(int type);
		virtual ~ShaderProgram();

		virtual void reloadProgram() {}

		static const int TYPE_VERT = 0;
		static const int TYPE_FRAG = 1;

		int type;

		void reloadResource();

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

		int getExpectedParamType(String name);

		virtual void setVertexProgram(ShaderProgram *vp) {}
		virtual void setFragmentProgram(ShaderProgram *fp) {}

		static const int FIXED_SHADER = 0;
		static const int MODULE_SHADER = 1;

		int numSpotLights;
		int numAreaLights;

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
		void setColor(Color x)     { static_cast<Color*>(data)->setColor(&x); }
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
		static const int MODE_COLOR = 2;
		static const int MODE_DEPTH = 3;
};

class _PolyExport ShaderBinding : public PolyBase {
	public:
		ShaderBinding(Shader *shader);
		virtual ~ShaderBinding();

		virtual Texture *getTexture(const String& name){ return NULL;};
		virtual Cubemap *getCubemap(const String& name){ return NULL;};
		virtual void clearTexture(const String& name){};
		virtual void clearCubemap(const String& name){};
		virtual void addTexture(const String& name, Texture *texture)  {};
		LocalShaderParam *addParam(int type, const String& name);
		virtual void addCubemap(const String& name, Cubemap *cubemap) {};

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

		LocalShaderParam *addLocalParam(const String& name, void *ptr);

		Shader* shader;
		std::vector<LocalShaderParam*> localParams;
		std::vector<RenderTargetBinding*> renderTargetBindings;
		std::vector<RenderTargetBinding*> inTargetBindings;
		std::vector<RenderTargetBinding*> outTargetBindings;
		std::vector<RenderTargetBinding*> colorTargetBindings;
		std::vector<RenderTargetBinding*> depthTargetBindings;
};

}
