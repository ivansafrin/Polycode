    
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
#include "polycode/core/PolyGlobals.h"
#include "polycode/core/PolyRenderer.h"
#include "polycode/core/PolyTexture.h"

#include "PolyCore.h"

#include <wrl.h>
#include <wrl/client.h>
#include <d3d11_2.h>
#include <d2d1_2.h>
#include <d2d1effects_1.h>
#include <dwrite_2.h>
#include <wincodec.h>
#include <DirectXColors.h>
#include <DirectXMath.h>
#include <memory>
#include <concrt.h>
#include <ppltasks.h>

namespace Polycode {
	class _PolyExport DX11GraphicsInterface : public GraphicsInterface {
		
	public:
		
		DX11GraphicsInterface();
		~DX11GraphicsInterface();

		// implementation
        
        void createTexture(Texture *texture);
        void setViewport(unsigned int x,unsigned  int y,unsigned  int width, unsigned height);
        void clearBuffers(const Color &clearColor, bool colorBuffer, bool depthBuffer, bool stencilBuffer);
        void setParamInShader(Shader *shader, ProgramParam *param, LocalShaderParam *localParam);
        void setAttributeInShader(Shader *shader, ProgramAttribute *attribute, AttributeBinding *attributeBinding);
        void disableAttribute(Shader *shader, const ProgramAttribute &attribute);
        void useShader(Shader *shader);
        void createProgram(ShaderProgram *program);
        void createShader(Shader *shader);
        void beginDrawCall();
        void endDrawCall();
        void setBlendingMode(unsigned int blendingMode);
        
        void bindFramebuffer(Texture *framebufferTexture);
        
        void createVertexBuffer(VertexDataArray *dataArray);
        void createIndexBuffer(IndexDataArray *dataArray);
        
        void drawIndices(int type, IndexDataArray *indexArray);
        void drawArrays(int type, unsigned int vertexCount);
        
        void enableDepthTest(bool val);
        void enableDepthWrite(bool val);
        void enableBackfaceCulling(bool val);
        void setLineSize(Number lineSize);

		void setContext(ID3D11DeviceContext2 *context);
		void setViews(ID3D11RenderTargetView *targetView, ID3D11DepthStencilView *depthStencilView);

	protected:

		ID3D11DeviceContext2 *context;
		ID3D11RenderTargetView	*m_d3dRenderTargetView;
		ID3D11DepthStencilView	*m_d3dDepthStencilView;

	};
}

