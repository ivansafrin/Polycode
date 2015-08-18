
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

#include "polycode/core/PolyDX11GraphicsInterface.h"
#include "polycode/core/PolyLogger.h"
#include "polycode/core/PolyCoreServices.h"

using namespace Polycode;

void DX11GraphicsInterface::setContext(ID3D11DeviceContext2 *context) {
	this->context = context;
}

void DX11GraphicsInterface::setViews(ID3D11RenderTargetView *targetView, ID3D11DepthStencilView *depthStencilView) {
	m_d3dRenderTargetView = targetView;
	m_d3dDepthStencilView = depthStencilView;
}

DX11GraphicsInterface::DX11GraphicsInterface() {

}

DX11GraphicsInterface::~DX11GraphicsInterface() {
    
}

void DX11GraphicsInterface::setParamInShader(Shader *shader, ProgramParam *param, LocalShaderParam *localParam) {
    
}

void DX11GraphicsInterface::setBlendingMode(unsigned int blendingMode) {
   
}

void DX11GraphicsInterface::beginDrawCall() {
}

void DX11GraphicsInterface::endDrawCall() {
}

void DX11GraphicsInterface::useShader(Shader *shader) {
   
}

void DX11GraphicsInterface::setAttributeInShader(Shader *shader, ProgramAttribute *attribute, AttributeBinding *attributeBinding) {

}

void DX11GraphicsInterface::disableAttribute(Shader *shader, const ProgramAttribute &attribute) {

}

void DX11GraphicsInterface::drawIndices(int type, IndexDataArray *indexArray) {
}

void DX11GraphicsInterface::drawArrays(int type, unsigned int vertexCount) {

}

void DX11GraphicsInterface::bindFramebuffer(Texture *framebufferTexture) {
}

void DX11GraphicsInterface::createTexture(Texture *texture) {
}

void DX11GraphicsInterface::setViewport(unsigned int x,unsigned  int y,unsigned  int width, unsigned height) {

}

void DX11GraphicsInterface::createProgram(ShaderProgram *program) {
}

void DX11GraphicsInterface::createVertexBuffer(VertexDataArray *dataArray) {
}

void DX11GraphicsInterface::createIndexBuffer(IndexDataArray *dataArray) {
}

void DX11GraphicsInterface::createShader(Shader *shader) {    
}

void DX11GraphicsInterface::enableBackfaceCulling(bool val) {
}

void DX11GraphicsInterface::enableDepthTest(bool val) {
}

void DX11GraphicsInterface::enableDepthWrite(bool val) {
}

void DX11GraphicsInterface::setLineSize(Number lineSize) {

}

void DX11GraphicsInterface::clearBuffers(const Color &clearColor, bool colorBuffer, bool depthBuffer, bool stencilBuffer) {

	if (colorBuffer) {
		FLOAT ColorRGBA[4] = { clearColor.r, clearColor.g, clearColor.b, clearColor.a};
		context->ClearRenderTargetView(m_d3dRenderTargetView, ColorRGBA);
	}
	UINT clearFlags = 0;
	if (depthBuffer) {
		clearFlags = clearFlags | D3D11_CLEAR_DEPTH;
	}
	if (stencilBuffer) {
		clearFlags = clearFlags | D3D11_CLEAR_STENCIL;
	}
	context->ClearDepthStencilView(m_d3dDepthStencilView, clearFlags, 1.0f, 0);
}
