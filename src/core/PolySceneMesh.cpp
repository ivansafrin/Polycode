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

#include "polycode/core/PolySceneMesh.h"
#include "polycode/core/PolyCoreServices.h"
#include "polycode/core/PolyBone.h"
#include "polycode/core/PolyMaterial.h"
#include "polycode/core/PolyRenderer.h"
#include "polycode/core/PolyMaterial.h"
#include "polycode/core/PolyMesh.h"
#include "polycode/core/PolyImage.h"
#include "polycode/core/PolyShader.h"
#include "polycode/core/PolySkeleton.h"
#include "polycode/core/PolyResourceManager.h"
#include <memory>

using namespace Polycode;

SceneMesh *SceneMesh::SceneMeshFromMesh(std::shared_ptr<Mesh> mesh) {
	return new SceneMesh(mesh);
}

SceneMesh::SceneMesh() : material(NULL), skeleton(NULL) {
	mesh = std::make_shared<Mesh>();
	setLocalBoundingBox(mesh->calculateBBox());
	useVertexBuffer = false;
	lineSmooth = false;
	lineWidth = 1.0;
	useGeometryHitDetection = false;
	backfaceCulled = true;
	alphaTest = false;
	sendBoneMatricesToMaterial = false;
	setMaterialByName("UnlitUntextured");
}


SceneMesh::SceneMesh(const String& fileName) : material(NULL), skeleton(NULL), mesh(NULL) {
	loadFromFile(fileName);
	useVertexBuffer = false;
	lineSmooth = false;
	lineWidth = 1.0;
	pointSmooth = false;
	useGeometryHitDetection = false;
	backfaceCulled = true;
	alphaTest = false;
	sendBoneMatricesToMaterial = false;
	setMaterialByName("UnlitUntextured");
}

SceneMesh::SceneMesh(std::shared_ptr<Mesh> mesh) : material(NULL), skeleton(NULL) {
	this->mesh = mesh;
	setLocalBoundingBox(mesh->calculateBBox());
	useVertexBuffer = false;
	lineSmooth = false;
	lineWidth = 1.0;
	pointSmooth = false;
	useGeometryHitDetection = false;
	backfaceCulled = true;
	alphaTest = false;
	sendBoneMatricesToMaterial = false;
	setMaterialByName("UnlitUntextured");
}

void SceneMesh::setMesh(std::shared_ptr<Mesh> mesh) {
	this->mesh = mesh;
	setLocalBoundingBox(mesh->calculateBBox());
	useVertexBuffer = false;
}

SceneMesh::~SceneMesh() {
}

Entity *SceneMesh::Clone(bool deepClone, bool ignoreEditorOnly) const {
	SceneMesh *newEntity = new SceneMesh();
	applyClone(newEntity, deepClone, ignoreEditorOnly);
	return newEntity;
}

void SceneMesh::setForceMaterial(bool forceMaterial) {
	drawCall.options.forceMaterial = forceMaterial;
}

bool SceneMesh::getForceMaterial() {
	return drawCall.options.forceMaterial;
}

void SceneMesh::applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly) const {
	Entity::applyClone(clone, deepClone, ignoreEditorOnly);
	SceneMesh *_clone = (SceneMesh*) clone;
	
	_clone->lineWidth = lineWidth;
	_clone->lineSmooth = lineSmooth;
	_clone->pointSmooth = pointSmooth;
	_clone->alphaTest = alphaTest;
	_clone->backfaceCulled = backfaceCulled;
	_clone->useGeometryHitDetection = useGeometryHitDetection;
	_clone->setFilename(fileName);
	_clone->setMesh(mesh);
	_clone->setMaterial(material);
	if(material) {
		
		for(int i=0; i < shaderPasses.size(); i++) {
			shaderPasses[i].shaderBinding->copyTo(&*_clone->getShaderPass(i).shaderBinding);
		}
	}
}

void SceneMesh::setFilename(const String &fileName) {
	this->fileName = fileName;
}

void SceneMesh::loadFromFile(const String &fileName) {
	ResourcePool *pool = Services()->getResourceManager()->getGlobalPool();
	mesh = std::static_pointer_cast<Mesh>(pool->loadResourceWithName(fileName, fileName));
	setLocalBoundingBox(mesh->calculateBBox());
	this->fileName = fileName;
}

String SceneMesh::getFilename() {
	return fileName;
}

std::shared_ptr<Mesh> SceneMesh::getMesh() {
	return mesh;
}

void SceneMesh::clearMaterial() {
	shaderPasses.clear();
	colorParams.clear();
    boneMatrixParams.clear();
	this->material = nullptr;
}

void SceneMesh::setMaterial(std::shared_ptr<Material> material) {

	if(this->material)
		clearMaterial();
	
	if(!material)
		return;
		
	if(material->getNumShaderPasses() == 0)
			return;
		
	this->material = material;
	
	for(int i=0; i < material->getNumShaderPasses(); i++)  {
		ShaderPass shaderPass = material->getShaderPass(i);
		shaderPass.materialShaderBinding = shaderPass.shaderBinding;
		shaderPass.shaderBinding = std::make_shared<ShaderBinding>();
		shaderPass.shaderBinding->targetShader = shaderPass.shader;
		std::shared_ptr<LocalShaderParam> colorParam = shaderPass.shaderBinding->addParam(ProgramParam::PARAM_COLOR, "entityColor");
		colorParams.push_back(colorParam);
		if(skeleton) {
            createMaterialBoneParams(&*shaderPass.shaderBinding);
		}
		shaderPasses.push_back(shaderPass);
	}
}

void SceneMesh::createMaterialBoneParams(ShaderBinding *shaderBinding) {
    if(!skeleton) {
        return;
    }
    boneMatrixParams.clear();
    
    for(int i=0; i < skeleton->getNumBones(); i++) {
        String paramName = "skeletonMatrix[0]";
        std::shared_ptr<LocalShaderParam> param = shaderBinding->getLocalParamByName(paramName);
        if(!param) {
            param = shaderBinding->addParam(ProgramParam::PARAM_MATRIX, paramName);
        }
        boneMatrixParams.push_back(param);
    }
}

void SceneMesh::setMaterialByName(const String& materialName, ResourcePool *resourcePool) {
	std::shared_ptr<Material> material;
	if(resourcePool) {
		material =	std::static_pointer_cast<Material>(resourcePool->getResource(Resource::RESOURCE_MATERIAL, materialName));		
	} else {
		material = std::static_pointer_cast<Material>(Services()->getResourceManager()->getGlobalPool()->getResource(Resource::RESOURCE_MATERIAL, materialName));
		
	}
	setMaterial(material);
}

ShaderPass SceneMesh::getShaderPass(unsigned int index) {
	if(index >= shaderPasses.size()) {
		printf("WARNING: ACCESSING NON EXISTING SHADER PASS!\n");
		return ShaderPass();
	}
	return shaderPasses[index];
}

unsigned int SceneMesh::getNumShaderPasses() {
	return shaderPasses.size();
}

void SceneMesh::addShaderPass(ShaderPass pass) {
	shaderPasses.push_back(pass);
}

std::shared_ptr<Skeleton> SceneMesh::loadSkeleton(const String& fileName) {
	skeleton = std::make_shared<Skeleton>(fileName);
	addChild(&*skeleton);
	setSkeleton(skeleton);
	return skeleton;
}

void SceneMesh::setSkeleton(std::shared_ptr<Skeleton> skeleton) {
	this->skeleton = skeleton;
    if(material) {
        for(auto pass:shaderPasses) {
            createMaterialBoneParams(&*pass.shaderBinding);
        }
    }
}

void SceneMesh::setLineWidth(Number newWidth) {
	lineWidth = newWidth;
}

std::shared_ptr<Material> SceneMesh::getMaterial() {
	return material;
}

std::shared_ptr<Skeleton> SceneMesh::getSkeleton() {
	return skeleton;
}

bool SceneMesh::customHitDetection(const Ray &ray) {
	if(!useGeometryHitDetection)
		return true;
	
	Ray transformedRay;
	
	Matrix4 adjustedMatrix = getAnchorAdjustedMatrix().Inverse();
	transformedRay.origin = adjustedMatrix * ray.origin;
	transformedRay.direction = adjustedMatrix.rotateVector(ray.direction);
	
	if(mesh->getNumSubmeshes() == 0) {
		return false;
	}
	
	for(int m=0; m < mesh->getNumSubmeshes(); m++) {
		std::shared_ptr<MeshGeometry> subMesh = mesh->getSubmeshPointer(m);
		if(subMesh->indexedMesh) {
			for(int i=0; i < subMesh->getIndexCount(); i+=3) {
				if(i+2 < subMesh->getIndexCount()) {
					if(transformedRay.polygonIntersect(subMesh->getVertexPositionAtIndex(i), subMesh->getVertexPositionAtIndex(i+1), subMesh->getVertexPositionAtIndex(i+2))) {
						return true;
					}
				}
			}
			
		} else {
			for(int i=0; i < subMesh->getVertexCount(); i+=3) {
				if(i+2 < subMesh->getVertexCount()) {
				   if(transformedRay.polygonIntersect(subMesh->getVertexPosition(i), subMesh->getVertexPosition(i+1), subMesh->getVertexPosition(i+2))) {
						return true;
					}
				}
			}
		}
	}
	return false;
}


void SceneMesh::removeShaderPass(int shaderIndex) {
	if(shaderIndex >= 0 && shaderIndex < shaderPasses.size()) {
		shaderPasses.erase(shaderPasses.begin() + shaderIndex);
	}
}

void SceneMesh::Render(GPUDrawBuffer *buffer) {

	if(!mesh) {
		return;
	}
	
	for (auto param : colorParams) {
		param->setColor(color);
	}
    
    if(skeleton) {
        
        std::vector<Matrix4> matrices;
        for(int i =0; i < skeleton->getNumBones(); i++) {
            matrices.push_back(skeleton->getBone(i)->getFinalMatrix());
        }
        
        for(auto param:boneMatrixParams) {
            param->setMatrix4Array(matrices);
        }
    }

	for(int i=0; i < mesh->getNumSubmeshes(); i++) {
		drawCall.options.alphaTest = alphaTest;
		drawCall.options.linePointSize = lineWidth;
		drawCall.options.backfaceCull = backfaceCulled;
		drawCall.options.depthTest = depthTest;
		drawCall.options.depthWrite = depthWrite;
		drawCall.submesh = mesh->getSubmeshPointer(i);		  
		drawCall.material = material;
		drawCall.shaderPasses = shaderPasses;
		buffer->drawCalls.push_back(drawCall);
	}
}
