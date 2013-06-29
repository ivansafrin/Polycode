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

#include "PolyGlobals.h"
#include "PolyString.h"
#include "PolyShader.h"
#include <vector>

namespace Polycode {

class GLSLProgram;

typedef struct {
	Texture *texture;
	String name;
} GLSLTextureBinding;

typedef struct {
	Cubemap *cubemap;
	String name;
} GLSLCubemapBinding;


class _PolyExport GLSLShader : public Shader {
	public:
		GLSLShader(GLSLProgram *vp, GLSLProgram *fp);
		virtual ~GLSLShader();

		ShaderBinding *createBinding();
		virtual void reload();

		void handleEvent(Event *event);

		static int getPolycodeParamType(int glType);

		void setVertexProgram(ShaderProgram *vp);
		void setFragmentProgram(ShaderProgram *fp);

		unsigned int shader_id;

		void linkProgram();
		void unlinkProgram();
};

class _PolyExport GLSLShaderBinding : public ShaderBinding {
	public:
		GLSLShaderBinding(GLSLShader *shader);
		virtual ~GLSLShaderBinding();

		void clearCubemap(const String& name);
		void addTexture(const String& name, Texture *texture);
		void addCubemap(const String& name, Cubemap *cubemap);
		void clearTexture(const String& name);
		Texture *getTexture(const String& name);
		Cubemap *getCubemap(const String& name);

		std::vector<GLSLTextureBinding> textures;
		std::vector<GLSLCubemapBinding> cubemaps;

		GLSLShader *glslShader;
};

}
