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
#include "PolyMesh.h"

using namespace Polycode;

Renderer::Renderer() : clearColor(0.2f, 0.2f, 0.2f, 0.0), currentTexture(NULL), renderMode(0), lightingEnabled(false), orthoMode(false), xRes(0), yRes(0) {
	anisotropy = 0;
	textureFilteringMode = TEX_FILTERING_LINEAR;
	currentMaterial = NULL;
	numLights = 0;
	exposureLevel = 1;
	shadersEnabled = true;
	currentMaterial = NULL;
	numLights = 0;
	numAreaLights = 0;
	numSpotLights = 0;	
	exposureLevel = 1;
	shadersEnabled = true;
	currentShaderModule = NULL;
	fov = 45.0;
	setAmbientColor(0.0,0.0,0.0);
	cullingFrontFaces = false;
	scissorEnabled = false;
	blendNormalAsPremultiplied = false;
	alphaTestValue = 0.01;
	doClearBuffer = true;
    backingResolutionScaleX = 1.0;
    backingResolutionScaleY = 1.0;
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

void Renderer::enableShaders(bool flag) {
	shadersEnabled = flag;
}

void Renderer::setCameraMatrix(const Matrix4& matrix) {
	cameraMatrix = matrix;
}

void Renderer::clearLights() {
	numLights = 0;
	numAreaLights = 0;
	numSpotLights = 0;	
	lights.clear();
	areaLights.clear();
	spotLights.clear();
}

void Renderer::setExposureLevel(Number level) {
	exposureLevel = level;
}

void Renderer::addShaderModule(PolycodeShaderModule *module) {
	shaderModules.push_back(module);
}

void Renderer::sortLights(){

	sorter.basePosition = (getModelviewMatrix()).getPosition();
	sorter.cameraMatrix = getCameraMatrix().Inverse();	
	sort (areaLights.begin(), areaLights.end(), sorter);
	sort (spotLights.begin(), spotLights.end(), sorter);	
}

void Renderer::addLight(int lightImportance, Vector3 position, Vector3 direction, int type, Color color, Color specularColor, Number constantAttenuation, Number linearAttenuation, Number quadraticAttenuation, Number intensity, Number spotlightCutoff, Number spotlightExponent, bool shadowsEnabled, Matrix4 *textureMatrix,Texture *shadowMapTexture) {

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
		case 0: //area light
			areaLights.push_back(info);
			numAreaLights++;
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
			binding->addLocalParam(shader->expectedParams[i].name, dataPtr);
		}
	}
}

void Renderer::pushDataArrayForMesh(Mesh *mesh, int arrayType) {
	if(mesh->arrayDirtyMap[arrayType] == true || mesh->renderDataArrays[arrayType] == NULL) {
		if(mesh->renderDataArrays[arrayType] != NULL) {
			free(mesh->renderDataArrays[arrayType]->arrayPtr);
			delete mesh->renderDataArrays[arrayType];
		}
		mesh->renderDataArrays[arrayType] = createRenderDataArrayForMesh(mesh, arrayType);
		mesh->arrayDirtyMap[arrayType] = false;
	}
	pushRenderDataArray(mesh->renderDataArrays[arrayType]);
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

void Renderer::setRenderMode(int newRenderMode) {
	renderMode = newRenderMode;
}

void Renderer::setTextureFilteringMode(int mode) {
	textureFilteringMode = mode;
}

int Renderer::getRenderMode() {
	return renderMode;
}

void Renderer::setFOV(Number fov) {
	this->fov = fov;
	resetViewport();
}

void Renderer::setViewportSize(int w, int h) {
	viewportWidth = w;
	viewportHeight = h;
	resetViewport();
}

void Renderer::setViewportSizeAndFOV(int w, int h, Number fov) {
	this->fov = fov;
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


