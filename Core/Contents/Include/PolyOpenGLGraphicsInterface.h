    
/*
Copyright (C) 2015 by Ivan Safrin

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
#include "PolyRenderer.h"
#include "PolyTexture.h"

#ifdef _WINDOWS
#include <windows.h>
#endif

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#if defined(_WINDOWS) && !defined(_MINGW)
#include <GL/wglext.h>
#endif
#endif


namespace Polycode {
	class _PolyExport OpenGLGraphicsInterface : public GraphicsInterface {
		
	public:
		
		OpenGLGraphicsInterface();
		~OpenGLGraphicsInterface();

		// implementation
        
        void createTexture(Texture *texture, int filteringMode, int anisotropy, bool createMipmaps);
        void setViewport(unsigned int x,unsigned  int y,unsigned  int width, unsigned height);
        void clearBuffers(bool colorBuffer, bool depthBuffer, bool stencilBuffer);
        void setParamInShader(Shader *shader, const ProgramParam &param, LocalShaderParam *localParam);
        void setAttributeInShader(Shader *shader, const ProgramAttribute &attribute, AttributeBinding *attributeBinding);
        void disableAttribute(Shader *shader, const ProgramAttribute &attribute);
        void useShader(Shader *shader);
        void createProgram(ShaderProgram *program);
        void createShader(Shader *shader);
        
        void drawIndices(int type, IndexDataArray *indexArray);
        void drawArrays(int type, unsigned int vertexCount);
        
        void enableDepthTest(bool val);
        void enableDepthWrite(bool val);
        
	protected:
		
        static GLenum getGLDrawMode(int polycodeMode);
        static int getPolycodeParamType(int glType);
        static int getAttributeSize(int glType);
        void setUniformMatrix(GLint paramLocation, const Polycode::Matrix4& matrix);
        
	};
}

