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

#include "PolyRenderer.h"
#include "PolyFixedShader.h"
#include "PolyMaterial.h"
#include "PolyModule.h"
#include "PolyMesh.h"

using namespace Polycode;

Renderer::Renderer() : clearColor(0.2, 0.2, 0.2, 0.0), currentTexture(NULL), lightingEnabled(false), xRes(0), yRes(0) {
	anisotropy = 0;
	textureFilteringMode = TEX_FILTERING_LINEAR;
	currentMaterial = NULL;
	numLights = 0;
	exposureLevel = 1;
	shadersEnabled = true;
	currentMaterial = NULL;
	numLights = 0;
	numPointLights = 0;
	numSpotLights = 0;	
	exposureLevel = 1;
	shadersEnabled = true;
	currentShaderModule = NULL;
	setAmbientColor(0.0,0.0,0.0);
	cullingFrontFaces = false;
	scissorEnabled = false;
	blendNormalAsPremultiplied = false;
	alphaTestValue = 0.01;
	doClearBuffer = true;
    backingResolutionScaleX = 1.0;
    backingResolutionScaleY = 1.0;
    overrideMaterial = NULL;
    renderToGlobalFramebuffer = false;
    globalColorFramebuffer = NULL;
    globalDepthFramebuffer = NULL;
}

void Renderer::setRenderToGlobalFramebuffer(bool val) {
    
    if(val == renderToGlobalFramebuffer) {
        return;
    }
    
    renderToGlobalFramebuffer = val;
    
    if(renderToGlobalFramebuffer) {
        createRenderTextures(&globalColorFramebuffer, &globalDepthFramebuffer, getXRes(), getYRes(), false);
    } else {
        delete globalColorFramebuffer;
        delete globalDepthFramebuffer;
    }
}

void Renderer::BeginRender() {
    if(renderToGlobalFramebuffer) {
        bindFrameBufferTexture(globalColorFramebuffer);
        bindFrameBufferTextureDepth(globalDepthFramebuffer);
    }
}

void Renderer::EndRender() {
    if(renderToGlobalFramebuffer) {
        unbindFramebuffers();
    }
}

bool Renderer::getRenderToGlobalFramebuffer() const {
    return renderToGlobalFramebuffer;
}

Texture *Renderer::getGlobalColorFramebuffer() const {
    return globalColorFramebuffer;
}

Texture *Renderer::getGlobalDepthFramebuffer() const {
    return globalDepthFramebuffer;
}

void Renderer::setOverrideMaterial(Material *material) {
    overrideMaterial = material;
}

Number Renderer::getBackingResolutionScaleX() {
    return backingResolutionScaleX;
}

Number Renderer::getBackingResolutionScaleY() {
    return backingResolutionScaleY;
}

Renderer::~Renderer() {
}

bool Renderer::Init() {
	initOSSpecific();

	return true;
}

void Renderer::pushVertexColor() {
    vertexColorStack.push(currentVertexColor);
}

void Renderer::popVertexColor() {
    currentVertexColor = vertexColorStack.top();
    vertexColorStack.pop();
}

void Renderer::multiplyVertexColor(const Color &color) {
    currentVertexColor = currentVertexColor * color;
    setVertexColor(currentVertexColor.r, currentVertexColor.g, currentVertexColor.b, currentVertexColor.a);
}

void Renderer::loadVertexColorIdentity() {
    currentVertexColor = Color(1.0, 1.0, 1.0, 1.0);
    setVertexColor(currentVertexColor.r, currentVertexColor.g, currentVertexColor.b, currentVertexColor.a);
}

void Renderer::enableShaders(bool flag) {
	shadersEnabled = flag;
}

void Renderer::setCameraMatrix(const Matrix4& matrix) {
	cameraMatrix = matrix;
}

void Renderer::clearLights() {
	numLights = 0;
	numPointLights = 0;
	numSpotLights = 0;	
	lights.clear();
	pointLights.clear();
	spotLights.clear();
}


void Renderer::bindFrameBufferTexture(Texture *texture) {
    framebufferStackColor.push(texture);
}

void Renderer::bindFrameBufferTextureDepth(Texture *texture) {
    framebufferStackDepth.push(texture);
}

void Renderer::unbindFramebuffers() {
    if(framebufferStackColor.size() > 0) {
        framebufferStackColor.pop();
    }
    if(framebufferStackDepth.size() > 0) {
        framebufferStackDepth.pop();
    }

    if(framebufferStackColor.size() > 0) {
        Texture *rebindTexture = framebufferStackColor.top();
        framebufferStackColor.pop();
        bindFrameBufferTexture(rebindTexture);
    }

    if(framebufferStackDepth.size() > 0) {
        Texture *rebindTexture = framebufferStackDepth.top();
        framebufferStackDepth.pop();
        bindFrameBufferTextureDepth(rebindTexture);
    }
    
}

void Renderer::setExposureLevel(Number level) {
	exposureLevel = level;
}

void Renderer::addShaderModule(PolycodeShaderModule *module) {
	shaderModules.push_back(module);
}

void Renderer::sortLights(){
    sorter.basePosition = (getModelviewMatrix() * cameraMatrix).getPosition();
	sort (pointLights.begin(), pointLights.end(), sorter);
	sort (spotLights.begin(), spotLights.end(), sorter);	
}

void Renderer::addLight(int lightImportance, const Vector3 &position, const Vector3 &direction, int type, const Color &color, const Color &specularColor, Number constantAttenuation, Number linearAttenuation, Number quadraticAttenuation, Number intensity, Number spotlightCutoff, Number spotlightExponent, bool shadowsEnabled, Matrix4 *textureMatrix,Texture *shadowMapTexture) {

	numLights++;
	
	LightInfo info;
	if(textureMatrix != NULL) {
		info.textureMatrix = *textureMatrix;
	}
	
	info.lightImportance = lightImportance;
	info.shadowMapTexture = shadowMapTexture;
	info.shadowsEnabled = shadowsEnabled;
	info.spotlightCutoff = spotlightCutoff;
	info.spotlightExponent = spotlightExponent;	
	info.intensity = intensity;
	info.type = type;
	info.dir = direction;
	info.constantAttenuation = constantAttenuation;
	info.linearAttenuation = linearAttenuation;
	info.quadraticAttenuation = quadraticAttenuation;
			
	info.color.set(color.r, color.g, color.b);
	info.specularColor = specularColor;
	info.position = position;
	lights.push_back(info);
	switch(type) {
		case 0: //point light
			pointLights.push_back(info);
			numPointLights++;
		break;
		case 1: //spot light
			spotLights.push_back(info);			
			numSpotLights++;
		break;			
	}
}

Number Renderer::getAnisotropyAmount() {
	return anisotropy;
}

void Renderer::setAnisotropyAmount(Number amount) {
	anisotropy = amount;
}

const Matrix4& Renderer::getCameraMatrix() const {
	return cameraMatrix;
}

void Renderer::enableScissor(bool val) {
	scissorEnabled = val;
}

void Renderer::setScissorBox(Polycode::Rectangle box) {
	scissorBox = box;
}

Polycode::Rectangle Renderer::getScissorBox() {
	return scissorBox;
}

void Renderer::setViewportShift(Number shiftX, Number shiftY) {
	viewportShift.x = shiftX;
	viewportShift.y = shiftY;
	resetViewport();
}

bool Renderer::isScissorEnabled() {
	return scissorEnabled;
}

void Renderer::billboardMatrixWithScale(Vector3 scale) {
	Matrix4 matrix = getModelviewMatrix();
	matrix.m[0][0] = 1.0f*scale.x;
	matrix.m[0][1] = 0;
	matrix.m[0][2] = 0;

	matrix.m[1][0] = 0;
	matrix.m[1][1] = 1.0f*scale.y;
	matrix.m[1][2] = 0;

	matrix.m[2][0] = 0;
	matrix.m[2][1] = 0;
	matrix.m[2][2] = 1.0f*scale.z;
	
	setModelviewMatrix(matrix);
}

void Renderer::billboardMatrix() {
	Matrix4 matrix = getModelviewMatrix();
	matrix.m[0][0] = 1;
	matrix.m[0][1] = 0;
	matrix.m[0][2] = 0;

	matrix.m[1][0] = 0;
	matrix.m[1][1] = 1;
	matrix.m[1][2] = 0;

	matrix.m[2][0] = 0;
	matrix.m[2][1] = 0;
	matrix.m[2][2] = 1;
	setModelviewMatrix(matrix);
}

void *Renderer::getDataPointerForName(const String &name) {
	if(name == "ambient_color") {
		return (void*)&ambientColor;
	}
	return NULL;
}

void Renderer::setRendererShaderParams(Shader *shader, ShaderBinding *binding) {
	for(int i=0; i < shader->expectedParams.size(); i++) {
		void *dataPtr = getDataPointerForName(shader->expectedParams[i].name);
		if(dataPtr) {
			binding->addParamPointer(shader->expectedParams[i].type, shader->expectedParams[i].name, dataPtr);
		}
	}
}

void Renderer::applyMaterial(Material *material,  ShaderBinding *localOptions,unsigned int shaderIndex, bool forceMaterial) {
    
    if(overrideMaterial) {
        if(!forceMaterial) {
            material = overrideMaterial;
        }
    }
    
	if(!material->getShader(shaderIndex) || !shadersEnabled) {
		setTexture(NULL);
		return;
	}
	
	FixedShaderBinding *fBinding;
    
    Shader *shader = material->getShader(shaderIndex);
	if(shader->numPointLights + shader->numSpotLights > 0) {
		sortLights();
	}
	
	switch(material->getShader(shaderIndex)->getType()) {
		case Shader::FIXED_SHADER:
			fBinding = (FixedShaderBinding*)material->getShaderBinding(shaderIndex);
			setTexture(fBinding->getDiffuseTexture());
            break;
		case Shader::MODULE_SHADER:
			currentMaterial = material;
			if(material->shaderModule == NULL) {
				for(int m=0; m < shaderModules.size(); m++) {
					PolycodeShaderModule *shaderModule = shaderModules[m];
					if(shaderModule->hasShader(material->getShader(shaderIndex))) {
						material->shaderModule = (void*)shaderModule;
					}
				}
			} else {
				PolycodeShaderModule *shaderModule = (PolycodeShaderModule*)material->shaderModule;
				shaderModule->applyShaderMaterial(this, material, localOptions, shaderIndex);
				currentShaderModule = shaderModule;
			}
            break;
	}
	
	setBlendingMode(material->blendingMode);
    setWireframePolygonMode(material->wireframe);
}

void Renderer::setBackingResolutionScale(Number xScale, Number yScale) {
    backingResolutionScaleX = xScale;
    backingResolutionScaleY = yScale;
}

int Renderer::getXRes() {
	return xRes;
}

int Renderer::getYRes() {
	return yRes;
}

void Renderer::setAmbientColor(Number r, Number g, Number b) {
	ambientColor.setColor(r,g,b,1.0f);
}

void Renderer::setClearColor(Number r, Number g, Number b, Number a) {
	clearColor.setColor(r,g,b,a);	
}

void Renderer::setClearColor(Color color) {
	setClearColor(color.r, color.g, color.b, color.a);
}

void Renderer::setTextureFilteringMode(int mode) {
	textureFilteringMode = mode;
}

void Renderer::setViewportSize(int w, int h) {
	viewportWidth = w;
	viewportHeight = h;
	resetViewport();
}

Number Renderer::getViewportWidth() {
	return viewportWidth;
}

Number Renderer::getViewportHeight() {
	return viewportHeight;
}


