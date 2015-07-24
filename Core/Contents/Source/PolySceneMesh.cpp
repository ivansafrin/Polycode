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

#include "PolySceneMesh.h"
#include "PolyCoreServices.h"
#include "PolyBone.h"
#include "PolyMaterial.h"
#include "PolyRenderer.h"
#include "PolyMaterial.h"
#include "PolyMesh.h"
#include "PolyImage.h"
#include "PolyShader.h"
#include "PolySkeleton.h"
#include "PolyResourceManager.h"
#include "PolyMaterialManager.h"

using namespace Polycode;

SceneMesh *SceneMesh::SceneMeshFromMesh(Mesh *mesh) {
	return new SceneMesh(mesh);
}

SceneMesh *SceneMesh::SceneMeshWithType(int meshType) {
	return new SceneMesh(meshType);
}

SceneMesh::SceneMesh(const String& fileName) : Entity(), texture(NULL), material(NULL), skeleton(NULL), localShaderOptions(NULL), mesh(NULL), skeletalVertexPositions(3, RenderDataArray::VERTEX_DATA_ARRAY), skeletalVertexNormals(3, RenderDataArray::NORMAL_DATA_ARRAY) {
    loadFromFile(fileName);
	useVertexBuffer = false;
	lineSmooth = false;
	ownsMesh = true;
	ownsSkeleton = true;
	lineWidth = 1.0;
	pointSize = 1.0;
	pointSmooth = false;
	overlayWireframe = false;
	useGeometryHitDetection = false;
    forceMaterial = false;
    backfaceCulled = true;
	alphaTest = false;
    sendBoneMatricesToMaterial = false;
    setMaterialByName("Unlit");
}

SceneMesh::SceneMesh(Mesh *mesh) : Entity(), texture(NULL), material(NULL), skeleton(NULL), localShaderOptions(NULL), skeletalVertexPositions(3, RenderDataArray::VERTEX_DATA_ARRAY), skeletalVertexNormals(3, RenderDataArray::NORMAL_DATA_ARRAY) {
	this->mesh = mesh;
	setLocalBoundingBox(mesh->calculateBBox());
	useVertexBuffer = false;
	lineSmooth = false;
	ownsMesh = true;
	ownsSkeleton = true;	
	lineWidth = 1.0;
	pointSize = 1.0;
	pointSmooth = false;
	overlayWireframe = false;	
	useGeometryHitDetection = false;
    forceMaterial = false;
    backfaceCulled = true;
	alphaTest = false;
    sendBoneMatricesToMaterial = false;
    setMaterialByName("Unlit");
}

SceneMesh::SceneMesh(int meshType) : texture(NULL), material(NULL), skeleton(NULL), localShaderOptions(NULL), skeletalVertexPositions(3, RenderDataArray::VERTEX_DATA_ARRAY), skeletalVertexNormals(3, RenderDataArray::NORMAL_DATA_ARRAY) {
	mesh = new Mesh(meshType);
	setLocalBoundingBox(mesh->calculateBBox());
	useVertexBuffer = false;	
	lineSmooth = false;
	ownsMesh = true;
	ownsSkeleton = true;	
	lineWidth = 1.0;
	overlayWireframe = false;
	useGeometryHitDetection = false;
    forceMaterial = false;
    backfaceCulled = true;
	alphaTest = false;
    sendBoneMatricesToMaterial = false;
    setMaterialByName("Unlit");    
}

void SceneMesh::setMesh(Mesh *mesh) {
	this->mesh = mesh;
	setLocalBoundingBox(mesh->calculateBBox());
	useVertexBuffer = false;	
}

SceneMesh::~SceneMesh() {
	if(ownsSkeleton)
		delete skeleton;
	if(ownsMesh)
		delete mesh;	
	delete localShaderOptions;
}

Entity *SceneMesh::Clone(bool deepClone, bool ignoreEditorOnly) const {
    SceneMesh *newEntity = new SceneMesh(mesh->getMeshType());
    applyClone(newEntity, deepClone, ignoreEditorOnly);
    return newEntity;
}

void SceneMesh::applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly) const {
    Entity::applyClone(clone, deepClone, ignoreEditorOnly);
    SceneMesh *_clone = (SceneMesh*) clone;
    
    _clone->lineWidth = lineWidth;
    _clone->lineSmooth = lineSmooth;
    _clone->pointSize = pointSize;
    _clone->pointSmooth = pointSmooth;
    _clone->ownsMesh = ownsMesh;
	_clone->alphaTest = alphaTest;
	_clone->backfaceCulled = backfaceCulled;
    _clone->ownsSkeleton = ownsSkeleton;
    _clone->overlayWireframe = overlayWireframe;
    _clone->wireFrameColor = wireFrameColor;
    _clone->useGeometryHitDetection = useGeometryHitDetection;
    _clone->forceMaterial = forceMaterial;
    _clone->setFilename(fileName);
    
    Mesh *newMesh = mesh->Copy();
    _clone->setMesh(newMesh);
    
    _clone->setMaterial(material);
    if(material) {
        localShaderOptions->copyTo(_clone->getLocalShaderOptions());
    }
}

void SceneMesh::setFilename(String fileName) {
    this->fileName = fileName;
}

void SceneMesh::loadFromFile(String fileName) {
    if(mesh && ownsMesh) {
        delete mesh;
    }
	mesh = new Mesh(fileName);
	setLocalBoundingBox(mesh->calculateBBox());
    this->fileName = fileName;
}

String SceneMesh::getFilename() {
    return fileName;
}

Mesh *SceneMesh::getMesh() {
	return mesh;
}

void SceneMesh::setTexture(Texture *texture) {
	this->texture = texture;
}

void SceneMesh::clearMaterial() {
	if(localShaderOptions)
		delete localShaderOptions;
	localShaderOptions = NULL;
	this->material = NULL;
}

void SceneMesh::setMaterial(Material *material) {

	if(this->material)
		clearMaterial();
	
	if(!material)
		return;
		
	if(material->getNumShaders() == 0)
			return;
		
	this->material = material;
    localShaderOptions = new ShaderBinding();
    
    localShaderOptions->addAttributeBinding("texCoord", &mesh->vertexTexCoordArray);
    localShaderOptions->addAttributeBinding("position", &mesh->vertexPositionArray);    
	
}

void SceneMesh::setMaterialByName(const String& materialName, ResourcePool *resourcePool) {
    
    Material *material;
    if(resourcePool) {
        material =  (Material*)resourcePool->getResource(Resource::RESOURCE_MATERIAL, materialName);        
    } else {
        material =  (Material*)CoreServices::getInstance()->getResourceManager()->getGlobalPool()->getResource(Resource::RESOURCE_MATERIAL, materialName);
        
    }
    setMaterial(material);
}

ShaderBinding *SceneMesh::getLocalShaderOptions() {
	return localShaderOptions;
}

Skeleton *SceneMesh::loadSkeleton(const String& fileName) {
	skeleton = new Skeleton(fileName);
	addChild(skeleton);
	setSkeleton(skeleton);
    return skeleton;
}

void SceneMesh::setSkeleton(Skeleton *skeleton) {
	this->skeleton = skeleton;
}

void SceneMesh::setLineWidth(Number newWidth) {
	lineWidth = newWidth;
}

Material *SceneMesh::getMaterial() {
	return material;
}

Skeleton *SceneMesh::getSkeleton() {
	return skeleton;
}

void SceneMesh::renderMeshLocally() {
    /*
	Renderer *renderer = CoreServices::getInstance()->getRenderer();

	
	if(skeleton) {
        
        skeletalVertexPositions.data.clear();
        skeletalVertexNormals.data.clear();
        
		for(int i=0; i < mesh->vertexPositionArray.data.size()/3; i++) {
            
            Vector3 norm;
            Vector3 tPos;
            
            for(int b=0; b < 4; b++) {
            
                PolyRendererVertexType boneWeight = mesh->vertexBoneWeightArray.data[(i*4)+b];
                
                if(boneWeight > 0.0) {
                    
                    Bone *bone = skeleton->getBone(mesh->vertexBoneIndexArray.data[(i*4)+b]);
                    if(bone) {
                        Vector3 restVert(mesh->vertexPositionArray.data[i*3], mesh->vertexPositionArray.data[(i*3)+1], mesh->vertexPositionArray.data[(i*3)+2]);
                        
                        tPos += bone->finalMatrix * restVert * (boneWeight);
                            
                        Vector3 nvec(mesh->vertexNormalArray.data[i*3], mesh->vertexNormalArray.data[(i*3)+1], mesh->vertexNormalArray.data[(i*3)+2]);
                        
                        nvec = bone->finalMatrix.rotateVector(nvec);
                        
                        norm += nvec * (boneWeight);
                    }
                }
            }

            skeletalVertexPositions.data.push_back(tPos.x);
            skeletalVertexPositions.data.push_back(tPos.y);
            skeletalVertexPositions.data.push_back(tPos.z);
        
            norm.Normalize();
            
            skeletalVertexNormals.data.push_back(norm.x);
            skeletalVertexNormals.data.push_back(norm.y);
            skeletalVertexNormals.data.push_back(norm.z);
        }
        
        renderer->pushRenderDataArray(&skeletalVertexPositions);
        renderer->pushRenderDataArray(&skeletalVertexNormals);
        
    } else {
        renderer->pushRenderDataArray(&mesh->vertexPositionArray);
        renderer->pushRenderDataArray(&mesh->vertexNormalArray);
    }
    
    renderer->pushRenderDataArray(&mesh->vertexTangentArray);
    renderer->pushRenderDataArray(&mesh->vertexTexCoordArray);
    
	if(mesh->useVertexColors) {
		renderer->pushRenderDataArray(&mesh->vertexColorArray);
	}
    
    if(mesh->indexedMesh) {
        renderer->drawArrays(mesh->getMeshType(), &mesh->indexArray);
    } else {
        renderer->drawArrays(mesh->getMeshType(), NULL);
    }
     */
}

bool SceneMesh::customHitDetection(const Ray &ray) {
	if(!useGeometryHitDetection)
		return true;
	
	Ray transformedRay;
	
	Matrix4 adjustedMatrix = getAnchorAdjustedMatrix().Inverse();
	transformedRay.origin = adjustedMatrix * ray.origin;
	transformedRay.direction = adjustedMatrix.rotateVector(ray.direction);
	
    if(mesh->indexedMesh) {
        for(int i=0; i < mesh->getIndexCount(); i+=3) {
            if(i+2 < mesh->getIndexCount()) {
                if(transformedRay.polygonIntersect(mesh->getVertexPositionAtIndex(i), mesh->getVertexPositionAtIndex(i+1), mesh->getVertexPositionAtIndex(i+2))) {
                    return true;
                }
            }
        }
        
    } else {
        for(int i=0; i < mesh->getVertexCount(); i+=3) {
            if(i+2 < mesh->getVertexCount()) {
               if(transformedRay.polygonIntersect(mesh->getVertexPosition(i), mesh->getVertexPosition(i+1), mesh->getVertexPosition(i+2))) {
                    return true;
                }
            }
        }
    }

	return false;
}


void SceneMesh::Render(GPUDrawBuffer *buffer) {
    
    drawCall.options.alphaTest = alphaTest;
    drawCall.options.linePointSize = lineWidth;
    drawCall.options.backfaceCull = backfaceCulled;
    drawCall.options.depthTest = depthTest;
    drawCall.options.depthWrite = depthWrite;

    drawCall.mode = mesh->getMeshType();
    
    
    drawCall.numVertices = mesh->getVertexCount();
    
    if(mesh->indexedMesh) {
        drawCall.indexed = true;
        drawCall.indexArray = &mesh->indexArray;
    } else {
        drawCall.indexed = false;
    }
    
    
    drawCall.material = material;
    drawCall.shaderBinding = localShaderOptions;
    
    buffer->drawCalls.push_back(drawCall);
    
    /*
   	if(material) {
        
		renderer->applyMaterial(material, localShaderOptions,0, forceMaterial);
	} else {
		if(texture)
			renderer->setTexture(texture);
		else
			renderer->setTexture(NULL);
	}
    
    if(sendBoneMatricesToMaterial && localShaderOptions && skeleton) {
        LocalShaderParam *skeletonMatrix = localShaderOptions->getLocalParamByName("skeletonMatrix[0]");
        
        if(skeletonMatrix) {
            for(int i=0; i < skeleton->getNumBones(); i++) {
                materialBoneMatrices[i] = skeleton->getBone(i)->getFinalMatrix();
            }
        } else {
            materialBoneMatrices.resize(skeleton->getNumBones());
            localShaderOptions->addParamPointer(ProgramParam::PARAM_MATRIX, "skeletonMatrix[0]", materialBoneMatrices.data())->arraySize = skeleton->getNumBones();
        }
    }
    
    bool useVertexBuffer = this->useVertexBuffer;

    if(useVertexBuffer && skeleton && !sendBoneMatricesToMaterial) {
        useVertexBuffer = false;
    }
    
	if(useVertexBuffer) {
        VertexBuffer *vb = mesh->getVertexBuffer();
        if(vb){
            renderer->drawVertexBuffer(vb, mesh->useVertexColors);
        }
	} else {
		renderMeshLocally();
	}
	
	if(material)  {
		renderer->clearShader();
	}
    
    renderer->setTexture(NULL);
    
	if(overlayWireframe) {
		bool depthTestVal = depthTest;
		renderer->enableDepthTest(false);
		renderer->setWireframePolygonMode(true);
		renderer->setVertexColor(wireFrameColor.r, wireFrameColor.g, wireFrameColor.b, wireFrameColor.a);
		
		if(useVertexBuffer) {
			renderer->drawVertexBuffer(mesh->getVertexBuffer(), mesh->useVertexColors);
		} else {
			renderMeshLocally();
		}
		renderer->enableDepthTest(depthTestVal);
	}	
    renderer->setWireframePolygonMode(false);    
     */
}
