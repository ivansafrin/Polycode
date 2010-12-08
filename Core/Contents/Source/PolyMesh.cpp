/*
 *  PolyMesh.cpp
 *  TAU
 *
 *  Created by Ivan Safrin on 3/18/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolyMesh.h"

namespace Polycode {

	Mesh::Mesh(string fileName) {
		
		for(int i=0; i < 16; i++) {
			arrayDirtyMap[i] = false;
			renderDataArrays[i] = NULL;
		}

		
		meshType = TRI_MESH;
		numUVs = 1;
		meshHasVertexBuffer = false;
		loadMesh(fileName);
		vertexBuffer = NULL;			
			}
	
	Mesh::Mesh(int meshType) {
		for(int i=0; i < 16; i++) {
			arrayDirtyMap[i] = false;
			renderDataArrays[i] = NULL;			
		}		
		this->meshType = meshType;
		meshHasVertexBuffer = false;		
		numUVs = 1;
		vertexBuffer = NULL;
				
	}
	
	
	Mesh::~Mesh() {
		Logger::log("deleting mesh...\n");
		for(int i=0; i < vertices.size(); i++) {	
			delete vertices[i];
		}
		vertices.clear();
		for(int i=0; i < polygons.size(); i++) {	
//			delete polygons[i];
		}
		polygons.clear();

	}
	
	VertexBuffer *Mesh::getVertexBuffer() {
		return vertexBuffer;
	}

	void Mesh::setVertexBuffer(VertexBuffer *buffer) {
		vertexBuffer = buffer;
		meshHasVertexBuffer = true;
	}
	
	float Mesh::getRadius() {
		float hRad = 0;
		float len;
		for(int i=0; i < vertices.size(); i++) {
			len = vertices[i]->length();
			if(len > hRad)
				hRad = len;
		}
		return hRad;
	}
	
	void Mesh::saveToFile(OSFILE *outFile) {
		unsigned int numVertices = vertices.size();
		OSBasics::write(&numUVs, sizeof(unsigned int), 1, outFile);		
		OSBasics::write(&numVertices, sizeof(unsigned int), 1, outFile);

		Vector3_struct pos;
		Vector3_struct nor;
		
		for(int i=0; i < vertices.size(); i++) {
			pos.x = vertices[i]->x;
			pos.y = vertices[i]->y;
			pos.z = vertices[i]->z;			

			nor.x = vertices[i]->normal->x;
			nor.y = vertices[i]->normal->y;
			nor.z = vertices[i]->normal->z;

			OSBasics::write(&pos, sizeof(Vector3_struct), 1, outFile);
			OSBasics::write(&nor, sizeof(Vector3_struct), 1, outFile);
			
			unsigned int hasWeights = 0;
			OSBasics::write(&hasWeights, sizeof(unsigned int), 1, outFile);

		}

		unsigned int numFaces = polygons.size();
		OSBasics::write(&numFaces, sizeof(unsigned int), 1, outFile);
		
		Face_struct poly;
		for(int i=0; i < polygons.size(); i++) {
			poly.nx = polygons[i]->getFaceNormal().x;
			poly.ny = polygons[i]->getFaceNormal().y;
			poly.nz = polygons[i]->getFaceNormal().z;			
			poly.v1 = getVertexIndex(polygons[i]->getVertex(0));
			poly.v2 = getVertexIndex(polygons[i]->getVertex(1));
			poly.v3 = getVertexIndex(polygons[i]->getVertex(2));			
			poly.uvs[0].x = polygons[i]->getTexCoord(0)->x;
			poly.uvs[0].y = polygons[i]->getTexCoord(0)->y;
			poly.uvs[1].x = polygons[i]->getTexCoord(1)->x;
			poly.uvs[1].y = polygons[i]->getTexCoord(1)->y;
			poly.uvs[2].x = polygons[i]->getTexCoord(2)->x;
			poly.uvs[2].y = polygons[i]->getTexCoord(2)->y;
			OSBasics::write(&poly, sizeof(Face_struct), 1, outFile);
			if(numUVs == 2) {
				Vector2_struct uv2s[3];
				uv2s[0].x = polygons[i]->getTexCoord2(0)->x;
				uv2s[0].y = polygons[i]->getTexCoord2(0)->y;
				uv2s[1].x = polygons[i]->getTexCoord2(1)->x;
				uv2s[1].y = polygons[i]->getTexCoord2(1)->y;
				uv2s[2].x = polygons[i]->getTexCoord2(2)->x;
				uv2s[2].y = polygons[i]->getTexCoord2(2)->y;
				OSBasics::write(uv2s, sizeof(Vector2_struct), 3, outFile);			
			}
		}
	}

	int Mesh::getVertexIndex(Vertex *vertex) {
		for(int i=0; i < vertices.size(); i++) {
			if(vertex == vertices[i])
				return i;
		}
		return 0;
	}
	
	void Mesh::loadFromFile(OSFILE *inFile) {
		int i;
		
		Vertex *newVertex;
		Polygon *polygon;
		unsigned int numVertices, numFaces, hasWeights, numWeights, numUVs;
		
		unsigned int boneID;
		float boneWeight;
		
		OSBasics::read(&numUVs, sizeof(unsigned int), 1, inFile);
		OSBasics::read(&numVertices, sizeof(unsigned int), 1, inFile);
		Vector3_struct pos;
		Vector3_struct nor;
		Face_struct face;
		
		for(i=0; i<numVertices; i++) {
			OSBasics::read(&pos, sizeof(Vector3_struct), 1, inFile);
			OSBasics::read(&nor, sizeof(Vector3_struct), 1, inFile);
			
			newVertex = new Vertex(pos.x, pos.y, pos.z, nor.x, nor.y,nor.z);
			
			OSBasics::read(&hasWeights, sizeof(unsigned int), 1, inFile);
			if(hasWeights == 1) {
					OSBasics::read(&numWeights, sizeof(unsigned int), 1, inFile);
					for(int j=0; j < numWeights; j++) {
						OSBasics::read(&boneID, sizeof(unsigned int), 1, inFile);
						OSBasics::read(&boneWeight, sizeof(float), 1, inFile);
						newVertex->addBoneAssignment(boneID, boneWeight);
					}
					newVertex->normalizeWeights();
			}
			vertices.push_back(newVertex);
		}
		
		OSBasics::read(&numFaces, sizeof(unsigned int), 1, inFile);
		
		for(i=0; i<numFaces; i++) {
			OSBasics::read(&face, sizeof(Face_struct), 1, inFile);
			polygon = new Polygon();
			polygon->addVertex(vertices[face.v1]);
			polygon->addVertex(vertices[face.v2]);
			polygon->addVertex(vertices[face.v3]);
			
			polygon->setNormal(Vector3(face.nx,face.ny,face.nz));
			
			vertices[face.v1]->setTexCoord(face.uvs[0].x,face.uvs[0].y);
			vertices[face.v2]->setTexCoord(face.uvs[1].x,face.uvs[1].y);
			vertices[face.v3]->setTexCoord(face.uvs[2].x,face.uvs[2].y);
			
			polygon->addTexCoord(face.uvs[0].x,face.uvs[0].y);
			polygon->addTexCoord(face.uvs[1].x,face.uvs[1].y);
			polygon->addTexCoord(face.uvs[2].x,face.uvs[2].y);	
			polygon->setUseFaceUV(true);
			
			if(numUVs == 2) {
				Vector2_struct uv2s[3];
				OSBasics::read(uv2s, sizeof(Vector2_struct), 3, inFile);
				polygon->addTexCoord2(uv2s[0].x,uv2s[0].y);
				polygon->addTexCoord2(uv2s[1].x,uv2s[1].y);
				polygon->addTexCoord2(uv2s[2].x,uv2s[2].y);	
			}
			
			polygons.push_back(polygon);
		}
		this->numUVs = numUVs;				
	}
	
	void Mesh::loadMesh(string fileName) {
		OSFILE *inFile = OSBasics::open(fileName.c_str(), "rb");
		if(!inFile) {
			Logger::log("Error opening mesh file %s", fileName.c_str());
		}
		loadFromFile(inFile);
		OSBasics::close(inFile);	
		arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;		
		arrayDirtyMap[RenderDataArray::COLOR_DATA_ARRAY] = true;				
		arrayDirtyMap[RenderDataArray::TEXCOORD_DATA_ARRAY] = true;						
		arrayDirtyMap[RenderDataArray::NORMAL_DATA_ARRAY] = true;										
		
	}
	
	void Mesh::createPlane(float w, float h) { 
		Polygon *imagePolygon = new Polygon();
		imagePolygon->addVertex(0,0,0,0,0);
		imagePolygon->addVertex(w,0,0, 1, 0);
		imagePolygon->addVertex(w,h,0, 1, 1);
		imagePolygon->addVertex(0,h,0,0,1);
		addPolygon(imagePolygon);
		
		for(int i=0; i < polygons.size(); i++) {
			for(int j=0; j < polygons[i]->getVertexCount(); j++) {
				polygons[i]->getVertex(j)->x = polygons[i]->getVertex(j)->x - (w/2.0f);
				polygons[i]->getVertex(j)->y = polygons[i]->getVertex(j)->y - (h/2.0f);
			}
		}

		calculateNormals();
		arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;		
		arrayDirtyMap[RenderDataArray::COLOR_DATA_ARRAY] = true;				
		arrayDirtyMap[RenderDataArray::TEXCOORD_DATA_ARRAY] = true;						
		arrayDirtyMap[RenderDataArray::NORMAL_DATA_ARRAY] = true;										
		
	}
	
	void Mesh::addVertex(Vertex* vertex) {
		vertices.push_back(vertex);
		arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;		
		arrayDirtyMap[RenderDataArray::COLOR_DATA_ARRAY] = true;				
		arrayDirtyMap[RenderDataArray::TEXCOORD_DATA_ARRAY] = true;						
		arrayDirtyMap[RenderDataArray::NORMAL_DATA_ARRAY] = true;												
	}
	
	unsigned int Mesh::getNumVertices() {
		return vertices.size();
	}
	
	Vertex *Mesh::getVertex(unsigned int index) {
		return vertices[index];
	}
	
	Vector3 Mesh::calculateBBox() {
		Vector3 retVec;
		for(int i=0; i < vertices.size(); i++) {
			retVec.x = max(retVec.x,fabsf(vertices[i]->x));
			retVec.y = max(retVec.y,fabsf(vertices[i]->y));
			retVec.z = max(retVec.z,fabsf(vertices[i]->z));			
		}
		return retVec*2;
	}
	
	void Mesh::createSphere(float radius, float numRings, float numSegments) {

		float fDeltaRingAngle = (PI / numRings);
        float fDeltaSegAngle = (2 * PI / numSegments);
		
		for(int i=0; i < numRings; i++) {
			float r0 = radius * sinf (i * fDeltaRingAngle);
			float y0 = radius * cosf (i * fDeltaRingAngle);			
			for(int j=0; j < numSegments; j++) {
				float x0 = r0 * sinf(j * fDeltaSegAngle);
				float z0 = r0 * cosf(j * fDeltaSegAngle);
				
				float tx0 = (float) j / (float) numSegments;
				float tx1 = (float) i / (float) numRings;
				
				Vector3 nor = Vector3(x0, y0, z0);
				nor.Normalize();
				
				
			}
		}
		
		useVertexNormals(true);
		arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;		
		arrayDirtyMap[RenderDataArray::COLOR_DATA_ARRAY] = true;				
		arrayDirtyMap[RenderDataArray::TEXCOORD_DATA_ARRAY] = true;						
		arrayDirtyMap[RenderDataArray::NORMAL_DATA_ARRAY] = true;										
		
	}

	void Mesh::createBox(float w, float d, float h) {
		Polygon *polygon = new Polygon();
		polygon->addVertex(w,0,h, 1, 1);
		polygon->addVertex(0,0,h, 1, 0);
		polygon->addVertex(0,0,0,0,0);
		polygon->addVertex(w,0,0,0,1);
		addPolygon(polygon);

		polygon = new Polygon();
		polygon->addVertex(w,d,h, 1, 1);
		polygon->addVertex(w,d,0, 1, 0);
		polygon->addVertex(0,d,0,0,0);
		polygon->addVertex(0,d,h,0,1);
		addPolygon(polygon);

		polygon = new Polygon();
		polygon->addVertex(0,d,0,0,1);
		polygon->addVertex(w,d,0, 1, 1);
		polygon->addVertex(w,0,0, 1, 0);
		polygon->addVertex(0,0,0,0,0);
		addPolygon(polygon);

		polygon = new Polygon();
		polygon->addVertex(0,0,h,0,0);
		polygon->addVertex(w,0,h, 1, 0);
		polygon->addVertex(w,d,h, 1, 1);
		polygon->addVertex(0,d,h,0,1);
		addPolygon(polygon);

		polygon = new Polygon();
		polygon->addVertex(0,0,h,0,1);
		polygon->addVertex(0,d,h, 1, 1);
		polygon->addVertex(0,d,0, 1, 0);
		polygon->addVertex(0,0,0,0,0);
		addPolygon(polygon);

		polygon = new Polygon();
		polygon->addVertex(w,0,h,0,1);
		polygon->addVertex(w,0,0, 1, 1);
		polygon->addVertex(w,d,0, 1, 0);
		polygon->addVertex(w,d,h,0,0);
		addPolygon(polygon);

		for(int i=0; i < polygons.size(); i++) {
			for(int j=0; j < polygons[i]->getVertexCount(); j++) {
				polygons[i]->getVertex(j)->x = polygons[i]->getVertex(j)->x - (w/2.0f);
				polygons[i]->getVertex(j)->y = polygons[i]->getVertex(j)->y - (d/2.0f);
				polygons[i]->getVertex(j)->z = polygons[i]->getVertex(j)->z - (h/2.0f);	
			}
		}

		calculateNormals();
		arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;		
		arrayDirtyMap[RenderDataArray::COLOR_DATA_ARRAY] = true;				
		arrayDirtyMap[RenderDataArray::TEXCOORD_DATA_ARRAY] = true;						
		arrayDirtyMap[RenderDataArray::NORMAL_DATA_ARRAY] = true;										
	}
	
	void Mesh::useVertexNormals(bool val) {
		for(int i =0; i < polygons.size(); i++) {
			polygons[i]->useVertexNormals = val;
		}		
		arrayDirtyMap[RenderDataArray::NORMAL_DATA_ARRAY] = true;										
	}
	
	void Mesh::calculateNormals() {
		for(int i =0; i < polygons.size(); i++) {
			polygons[i]->calculateNormal();
		}
		arrayDirtyMap[RenderDataArray::NORMAL_DATA_ARRAY] = true;										
	}
	
	int Mesh::getMeshType() {
		return meshType;
	}
	
	void Mesh::setMeshType(int newType) {
		meshType = newType;
	}
	
	void Mesh::addPolygon(Polygon *newPolygon) {
		polygons.push_back(newPolygon);
		arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;		
		arrayDirtyMap[RenderDataArray::COLOR_DATA_ARRAY] = true;				
		arrayDirtyMap[RenderDataArray::TEXCOORD_DATA_ARRAY] = true;						
		arrayDirtyMap[RenderDataArray::NORMAL_DATA_ARRAY] = true;								
	}
	
	
	unsigned int Mesh::getPolygonCount() {
		return polygons.size();
	}
	
	Polygon *Mesh::getPolygon(unsigned int index) {
		return polygons[index];
	}
}