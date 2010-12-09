/*
 *  PolySceneMesh.cpp
 *  TAU
 *
 *  Created by Ivan Safrin on 3/18/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolySceneMesh.h"

using namespace Polycode;

SceneMesh::SceneMesh(String fileName) : SceneEntity(), texture(NULL), material(NULL) {
	mesh = new Mesh(fileName);
	bBoxRadius = mesh->getRadius();
	bBox = mesh->calculateBBox();
	skeleton = NULL;
	lightmapIndex=0;
	showVertexNormals = false;
	useVertexBuffer = false;
}

SceneMesh::SceneMesh(Mesh *mesh) : SceneEntity(), texture(NULL), material(NULL) {
	this->mesh = mesh;
	bBoxRadius = mesh->getRadius();
	bBox = mesh->calculateBBox();
	skeleton = NULL;
	lightmapIndex=0;
	showVertexNormals = false;	
	useVertexBuffer = false;	
}

SceneMesh::SceneMesh(int meshType) : texture(NULL), material(NULL) {
	mesh = new Mesh(meshType);
	bBoxRadius = mesh->getRadius();
	bBox = mesh->calculateBBox();
	skeleton = NULL;
	lightmapIndex=0;
	showVertexNormals = false;	
	useVertexBuffer = false;	
}


SceneMesh::~SceneMesh() {
	Logger::log("Destroying Scene Mesh...\n");
	//delete mesh;
}

Mesh *SceneMesh::getMesh() {
	return mesh;
}

void SceneMesh::setTexture(Texture *texture) {
	this->texture = texture;
}

void SceneMesh::setMaterial(Material *material) {
	this->material = material;
	localShaderOptions = material->getShader(0)->createBinding();
}

void SceneMesh::setMaterial(String materialName) {
	Material *material =  (Material*)CoreServices::getInstance()->getResourceManager()->getResource(Resource::RESOURCE_MATERIAL, materialName);
	if(!material)
		return;
	setMaterial(material);
}

Texture *SceneMesh::getTexture() {
	return texture;
}


void SceneMesh::loadTexture(String fileName) {
	texture = CoreServices::getInstance()->getMaterialManager()->createTextureFromFile(fileName);
}

ShaderBinding *SceneMesh::getLocalShaderOptions() {
	return localShaderOptions;
}

void SceneMesh::loadSkeleton(String fileName) {
	skeleton = new Skeleton(fileName);
	addEntity(skeleton);
	
	setSkeleton(skeleton);
}

void SceneMesh::setSkeleton(Skeleton *skeleton) {
	this->skeleton = skeleton;
	for(int i=0; i < mesh->getPolygonCount(); i++) {
		Polygon *polygon = mesh->getPolygon(i);
		unsigned int vCount = polygon->getVertexCount();
		for(int j=0; j < vCount; j++) {
			Vertex *vertex = polygon->getVertex(j);
			for(int k=0; k < vertex->getNumBoneAssignments(); k++) {
				vertex->getBoneAssignment(k)->bone = skeleton->getBone(vertex->getBoneAssignment(k)->boneID);
			}
		}
	}	
}

Material *SceneMesh::getMaterial() {
	return material;
}

Skeleton *SceneMesh::getSkeleton() {
	return skeleton;
}

void SceneMesh::renderMeshLocally() {
	Renderer *renderer = CoreServices::getInstance()->getRenderer();
	
	/*
	Matrix4 boneMat;
	for(int i=0; i < mesh->getPolygonCount(); i++) {
		Polygon *polygon = mesh->getPolygon(i);
		CoreServices::getInstance()->getRenderer()->setNormal(polygon->getFaceNormal());
		
		unsigned int vCount = polygon->getVertexCount();
		for(int j=0; j < vCount; j++) {
			Vertex *vert = polygon->getVertex(j);
			Vector3 norm = *vert->normal;
			if(skeleton) {
				Vector3 aPos = vert->restPosition;
				Vector3 tPos;
				for(int b =0; b < vert->getNumBoneAssignments(); b++) {
					BoneAssignment *bas = vert->getBoneAssignment(b);
					Bone *bone = bas->bone;
					if(bone) {
						Vector3 vec = bone->getFullRestMatrix().inverse() * aPos;
						tPos += bone->getFinalMatrix() * vec * bas->weight;
					}
				}
				
				vert->x = tPos.x;
				vert->y = tPos.y;
				vert->z = tPos.z;
				
				norm.x += tPos.x;
				norm.y += tPos.y;
				norm.z += tPos.z;									
			}
			
			if(polygon->useVertexNormals) {
				CoreServices::getInstance()->getRenderer()->setNormal(norm);
			}
			
			if(polygon->usesFaceUV()) {
				if(polygon->hasSecUVs)
					CoreServices::getInstance()->getRenderer()->draw3DVertex2UV(vert, polygon->getTexCoord(j), polygon->getTexCoord2(j));
				elseBitworld is gonna be included on next month's PC Gamer CD!
					CoreServices::getInstance()->getRenderer()->draw3DVertex(vert, polygon->getTexCoord(j));
			} else {
				CoreServices::getInstance()->getRenderer()->draw3DVertex(vert, NULL);
			}
			
		}
		//CoreServices::getInstance()->getRenderer()->draw3DPolygon(mesh->getPolygon(i));
	}
*/
	
//	renderer->pushDataArrayForMesh(mesh, RenderDataArray::COLOR_DATA_ARRAY);
	 
	renderer->pushDataArrayForMesh(mesh, RenderDataArray::VERTEX_DATA_ARRAY);
	renderer->pushDataArrayForMesh(mesh, RenderDataArray::NORMAL_DATA_ARRAY);		
	renderer->pushDataArrayForMesh(mesh, RenderDataArray::TEXCOORD_DATA_ARRAY);	
	
	renderer->drawArrays(mesh->getMeshType());
}

void SceneMesh::cacheToVertexBuffer(bool cache) {

	if(cache && !mesh->hasVertexBuffer()) {
		CoreServices::getInstance()->getRenderer()->createVertexBufferForMesh(mesh);
	}
	useVertexBuffer = cache;
}

void SceneMesh::Render() {
	
	Renderer *renderer = CoreServices::getInstance()->getRenderer();
	
	if(material) {
		renderer->applyMaterial(material, localShaderOptions,0);
	} else {
		if(texture)
			renderer->setTexture(texture);
		else
			renderer->setTexture(NULL);
	}
	
	if(useVertexBuffer) {
		renderer->drawVertexBuffer(mesh->getVertexBuffer());
	} else {
		renderMeshLocally();
	}
	
	if(material) 
		renderer->clearShader();
	
	if(showVertexNormals) {	
		renderer->setTexture(NULL);
		/*
		for(int i=0; i < mesh->getPolygonCount(); i++) {
			Polygon *polygon = mesh->getPolygon(i);			
			unsigned int vCount = polygon->getVertexCount();
			for(int j=0; j < vCount; j++) {
				Vertex *vert = polygon->getVertex(j);
				Vector3 norm = *vert->normal;				
				CoreServices::getInstance()->getRenderer()->draw3DLine(*vert, norm, 0.4f, Color(0.0f,0.7f,1.0f,0.5f));				
			}
		}
		 */
	}	
}