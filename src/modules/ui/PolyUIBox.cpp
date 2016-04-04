/*
 Copyright (C) 2012 by Ivan Safrin
 
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

#include "polycode/modules/ui/PolyUIBox.h"
#include "polycode/core/PolyCoreServices.h"
#include "polycode/core/PolyConfig.h"
#include "polycode/core/PolyRenderer.h"
#include "polycode/core/PolyMesh.h"
#include "polycode/core/PolyResourceManager.h"
#include "polycode/core/PolyTexture.h"

using namespace Polycode;

UIBox::UIBox(String imageFile, Number t, Number r, Number b, Number l, Number boxWidth, Number boxHeight) : UIElement() {

    Config *conf = CoreServices::getInstance()->getConfig();
    Number uiScale = conf->getNumericValue("Polycode", "uiScale");
    
	setAnchorPoint(-1.0, -1.0, 0.0);
	
	setWidth(boxWidth);
	setHeight(boxHeight);
    
    MaterialManager *materialManager = CoreServices::getInstance()->getMaterialManager();
    texture = materialManager->createTextureFromFile(imageFile, materialManager->clampDefault, false);
    
    boxMesh = new Mesh(Mesh::TRI_MESH);
    boxMesh->indexedMesh = true;
    
    setMaterial((Material*)CoreServices::getInstance()->getResourceManager()->getGlobalPool()->getResource(Resource::RESOURCE_MATERIAL, "Unlit"));
    
    shaderPasses[0].shaderBinding->setTextureForParam("diffuse", texture);
    
    imageWidth = texture->getWidth();
    imageHeight = texture->getHeight();
    
    this->t = t;
    this->r = r;
    this->b = b;
    this->l = l;
    
    setBlendingMode(Renderer::BLEND_MODE_NORMAL);
    
    redrawMesh();
    
	ownsChildren = true;	
}


void UIBox::redrawMesh() {
    
    boxMesh->clearMesh();

    boxMesh->addVertexWithUV(0.0, 0.0, 0.0, 0.0, 0.0);
    boxMesh->addVertexWithUV(l, 0.0, 0.0, l/imageWidth, 0.0);
    boxMesh->addVertexWithUV(getWidth() - r, 0.0, 0.0, 1.0-r/imageWidth, 0.0);
    boxMesh->addVertexWithUV(getWidth(), 0.0, 0.0, 1.0, 0.0);
    
    boxMesh->addVertexWithUV(0.0, t, 0.0, 0.0, t/imageHeight);
    boxMesh->addVertexWithUV(l, t, 0.0, l/imageWidth, t/imageHeight);
    boxMesh->addVertexWithUV(getWidth() - r, t, 0.0, 1.0-r/imageWidth, t/imageHeight);
    boxMesh->addVertexWithUV(getWidth(), t, 0.0, 1.0, t/imageHeight);
    
    
    boxMesh->addVertexWithUV(0.0, getHeight()-t, 0.0, 0.0, 1.0-b/imageHeight);
    boxMesh->addVertexWithUV(l, getHeight()-t, 0.0, l/imageWidth, 1.0-b/imageHeight);
    boxMesh->addVertexWithUV(getWidth() - r, getHeight()-t, 0.0, 1.0-r/imageWidth, 1.0-b/imageHeight);
    boxMesh->addVertexWithUV(getWidth(), getHeight()-t, 0.0, 1.0, 1.0-b/imageHeight);

    boxMesh->addVertexWithUV(0.0, getHeight(), 0.0, 0.0, 1.0);
    boxMesh->addVertexWithUV(l, getHeight(), 0.0, l/imageWidth, 1.0);
    boxMesh->addVertexWithUV(getWidth() - r, getHeight(), 0.0, 1.0-r/imageWidth, 1.0);
    boxMesh->addVertexWithUV(getWidth(), getHeight(), 0.0, 1.0, 1.0);
    
    boxMesh->addIndexedFace(1, 0, 4);
    boxMesh->addIndexedFace(1, 4, 5);
    
    boxMesh->addIndexedFace(2, 1, 5);
    boxMesh->addIndexedFace(5, 6, 2);
    
    boxMesh->addIndexedFace(3, 2, 6);
    boxMesh->addIndexedFace(3, 6, 7);

    boxMesh->addIndexedFace(5, 4, 8);
    boxMesh->addIndexedFace(5, 8, 9);
    
    boxMesh->addIndexedFace(6, 5, 9);
    boxMesh->addIndexedFace(6, 9, 10);
    
    boxMesh->addIndexedFace(7, 6, 10);
    boxMesh->addIndexedFace(7, 10, 11);
    
    boxMesh->addIndexedFace(9, 8, 12);
    boxMesh->addIndexedFace(9, 12, 13);
    
    boxMesh->addIndexedFace(10, 9, 13);
    boxMesh->addIndexedFace(10, 13, 14);

    boxMesh->addIndexedFace(11, 10, 14);
    boxMesh->addIndexedFace(11, 14, 15);
    
    
    for(int i=0; i < boxMesh->getVertexCount(); i++) {
        Vector3 v = boxMesh->getVertexPosition(i);
        boxMesh->setVertexAtOffset(i, v.x-getWidth()/2.0, v.y-getHeight()/2.0, v.z);
    }

    shaderPasses[0].shaderBinding->resetAttributes = true;
}

void UIBox::setMaterial(Material *material) {
    
    for(int i=0; i < shaderPasses.size(); i++) {
        Services()->getRenderer()->destroyShaderBinding(shaderPasses[i].shaderBinding);
    }
    shaderPasses.clear();
    
    this->material = material;
    
    ShaderPass pass;
    pass.shaderBinding = new ShaderBinding();
    pass.shaderBinding->targetShader = pass.shader;
    pass.shader = material->getShaderPass(0).shader;
    shaderPasses.push_back(pass);
    
    shaderPasses[0].shaderBinding->addParamPointer(ProgramParam::PARAM_COLOR, "entityColor", &color);
    shaderPasses[0].setAttributeArraysFromMesh(boxMesh);
    shaderPasses[0].shaderBinding->resetAttributes = true;
}

void UIBox::Render(GPUDrawBuffer *buffer) {
    drawCall.options.depthTest = false;
    drawCall.options.depthWrite = false;
    drawCall.options.backfaceCull = false;
    
    drawCall.mesh = boxMesh;
    drawCall.material = material;
    drawCall.shaderPasses = shaderPasses;
    
    buffer->drawCalls.push_back(drawCall);
    
}

void UIBox::resizeBox(Number newWidth, Number newHeight) {
	setWidth(newWidth);
	setHeight(newHeight);
    redrawMesh();
	this->rebuildTransformMatrix();
}

UIBox::~UIBox() {
    delete boxMesh;
}
