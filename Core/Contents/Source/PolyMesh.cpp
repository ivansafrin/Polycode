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

#include "PolyMesh.h"

namespace Polycode {

	Mesh::Mesh(String fileName) {
		
		for(int i=0; i < 16; i++) {
			arrayDirtyMap[i] = false;
			renderDataArrays[i] = NULL;
		}

		
		meshType = TRI_MESH;
		meshHasVertexBuffer = false;
		loadMesh(fileName);
		vertexBuffer = NULL;			
		useVertexColors = false;
	}
	
	Mesh::Mesh(int meshType) {
		for(int i=0; i < 16; i++) {
			arrayDirtyMap[i] = false;
			renderDataArrays[i] = NULL;			
		}		
		this->meshType = meshType;
		meshHasVertexBuffer = false;		
		vertexBuffer = NULL;
		useVertexColors = false;				
	}
	
	
	Mesh::~Mesh() {
		for(int i=0; i < polygons.size(); i++) {	
			delete polygons[i];
		}
		polygons.clear();
		if(vertexBuffer)
			delete vertexBuffer;
		
		for(int i=0; i < 16; i++) {
			if(renderDataArrays[i]) {
				free(renderDataArrays[i]->arrayPtr);
				delete renderDataArrays[i];
			}
		}
	}
	
	VertexBuffer *Mesh::getVertexBuffer() {
		return vertexBuffer;
	}

	void Mesh::setVertexBuffer(VertexBuffer *buffer) {
		vertexBuffer = buffer;
		meshHasVertexBuffer = true;
	}
	
	Number Mesh::getRadius() {
		Number hRad = 0;
		Number len;
		for(int i=0; i < polygons.size(); i++) {	
			for(int j=0; j < polygons[i]->getVertexCount(); j++) {
				len = polygons[i]->getVertex(j)->length();
				if(len > hRad)
					hRad = len;
			}
		}
		return hRad;
	}
	
	void Mesh::saveToFile(OSFILE *outFile) {				
		unsigned int numFaces = polygons.size();

		OSBasics::write(&meshType, sizeof(unsigned int), 1, outFile);		
		OSBasics::write(&numFaces, sizeof(unsigned int), 1, outFile);
		for(int i=0; i < polygons.size(); i++) {
			
			Vector3_struct pos;
			Vector3_struct nor;
			Vector4_struct col;			
			Vector2_struct tex;
			
			for(int j=0; j <  polygons[i]->getVertexCount(); j++) {
				
				pos.x =  polygons[i]->getVertex(j)->x;
				pos.y =  polygons[i]->getVertex(j)->y;
				pos.z =  polygons[i]->getVertex(j)->z;

				nor.x =  polygons[i]->getVertex(j)->normal.x;
				nor.y =  polygons[i]->getVertex(j)->normal.y;
				nor.z =  polygons[i]->getVertex(j)->normal.z;

				col.x =  polygons[i]->getVertex(j)->vertexColor.r;
				col.y =  polygons[i]->getVertex(j)->vertexColor.g;
				col.z =  polygons[i]->getVertex(j)->vertexColor.b;
				col.w =  polygons[i]->getVertex(j)->vertexColor.a;
				
				tex.x = polygons[i]->getVertex(j)->getTexCoord().x;
				tex.y = polygons[i]->getVertex(j)->getTexCoord().y;
				
				OSBasics::write(&pos, sizeof(Vector3_struct), 1, outFile);
				OSBasics::write(&nor, sizeof(Vector3_struct), 1, outFile);
				OSBasics::write(&col, sizeof(Vector4_struct), 1, outFile);				
				OSBasics::write(&tex, sizeof(Vector2_struct), 1, outFile);								
				
				unsigned int numBoneWeights = polygons[i]->getVertex(j)->getNumBoneAssignments();
				OSBasics::write(&numBoneWeights, sizeof(unsigned int), 1, outFile);					
				for(int b=0; b < numBoneWeights; b++) {
					BoneAssignment *a = polygons[i]->getVertex(j)->getBoneAssignment(b);
					unsigned int boneID = a->boneID;
					float weight = a->weight;
					OSBasics::write(&boneID, sizeof(unsigned int), 1, outFile);
					OSBasics::write(&weight, sizeof(float), 1, outFile);												
				}
			}
			
		}
	}

	
	void Mesh::loadFromFile(OSFILE *inFile) {

		unsigned int meshType;		
		OSBasics::read(&meshType, sizeof(unsigned int), 1, inFile);				
		setMeshType(meshType);
		
		int verticesPerFace;
		switch(meshType) {
			case TRI_MESH:
				verticesPerFace = 3;
			break;
			case QUAD_MESH:
				verticesPerFace = 4;
			break;
			default:
				verticesPerFace = 1;				
			break;
		}
		
		unsigned int numFaces;		
		OSBasics::read(&numFaces, sizeof(unsigned int), 1, inFile);
		
		Vector3_struct pos;
		Vector3_struct nor;
		Vector4_struct col;			
		Vector2_struct tex;
		
		for(int i=0; i < numFaces; i++) {	
			Polygon *poly = new Polygon();			
			
			for(int j=0; j < verticesPerFace; j++) {
				OSBasics::read(&pos, sizeof(Vector3_struct), 1, inFile);
				OSBasics::read(&nor, sizeof(Vector3_struct), 1, inFile);
				OSBasics::read(&col, sizeof(Vector4_struct), 1, inFile);						
				OSBasics::read(&tex, sizeof(Vector2_struct), 1, inFile);						
				
				Vertex *vertex = new Vertex(pos.x, pos.y, pos.z);
				vertex->setNormal(nor.x,nor.y, nor.z);
				vertex->restNormal.set(nor.x,nor.y, nor.z);
				vertex->vertexColor.setColor(col.x,col.y, col.z, col.w);
				vertex->setTexCoord(tex.x, tex.y);
				
				unsigned int numBoneWeights;
				OSBasics::read(&numBoneWeights, sizeof(unsigned int), 1, inFile);								
				for(int b=0; b < numBoneWeights; b++) {
					float weight;
					unsigned int boneID;
					OSBasics::read(&boneID, sizeof(unsigned int), 1, inFile);													
					OSBasics::read(&weight, sizeof(float), 1, inFile);																		
					vertex->addBoneAssignment(boneID, weight);
				}
				
				
				
				poly->addVertex(vertex);
			}
			addPolygon(poly);
		}
		
		arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;		
		arrayDirtyMap[RenderDataArray::COLOR_DATA_ARRAY] = true;				
		arrayDirtyMap[RenderDataArray::TEXCOORD_DATA_ARRAY] = true;
		arrayDirtyMap[RenderDataArray::NORMAL_DATA_ARRAY] = true;							
	}
	
	void Mesh::saveToFile(String fileName) {
		OSFILE *outFile = OSBasics::open(fileName.c_str(), "wb");
		if(!outFile) {
			Logger::log("Error opening mesh file for saving: %s", fileName.c_str());
		}
		saveToFile(outFile);
		OSBasics::close(outFile);	
	
	}
	
	void Mesh::loadMesh(String fileName) {
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
	
	void Mesh::createPlane(Number w, Number h) { 
		Polygon *imagePolygon = new Polygon();
		imagePolygon->addVertex(0,0,h,0,0);	
		imagePolygon->addVertex(w,0,h, 1, 0);			
		imagePolygon->addVertex(w,0,0, 1, 1);		
		imagePolygon->addVertex(0,0,0,0,1);

		addPolygon(imagePolygon);
		
		for(int i=0; i < polygons.size(); i++) {
			for(int j=0; j < polygons[i]->getVertexCount(); j++) {
				polygons[i]->getVertex(j)->x = polygons[i]->getVertex(j)->x - (w/2.0f);
				polygons[i]->getVertex(j)->z = polygons[i]->getVertex(j)->z - (h/2.0f);
			}
		}

		calculateNormals();
		arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;		
		arrayDirtyMap[RenderDataArray::COLOR_DATA_ARRAY] = true;				
		arrayDirtyMap[RenderDataArray::TEXCOORD_DATA_ARRAY] = true;						
		arrayDirtyMap[RenderDataArray::NORMAL_DATA_ARRAY] = true;										
		
	}

	Vector3 Mesh::recenterMesh() {
		Vector3 positiveOffset;
		Vector3 negativeOffset;
		
		for(int i=0; i < polygons.size(); i++) {
			for(int j=0; j < polygons[i]->getVertexCount(); j++) {
				positiveOffset.x = max(positiveOffset.x,polygons[i]->getVertex(j)->x);
				positiveOffset.y = max(positiveOffset.y,polygons[i]->getVertex(j)->y);
				positiveOffset.z = max(positiveOffset.z,polygons[i]->getVertex(j)->z);							
				
			}
		}
		
		for(int i=0; i < polygons.size(); i++) {
			for(int j=0; j < polygons[i]->getVertexCount(); j++) {
				negativeOffset.x = min(negativeOffset.x,polygons[i]->getVertex(j)->x);
				negativeOffset.y = min(negativeOffset.y,polygons[i]->getVertex(j)->y);
				negativeOffset.z = min(negativeOffset.z,polygons[i]->getVertex(j)->z);							
				
			}
		}		
		
		Vector3 finalOffset;
		
		finalOffset.x = (positiveOffset.x + negativeOffset.x)/2.0f;
		finalOffset.y = (positiveOffset.y + negativeOffset.y)/2.0f;
		finalOffset.z = (positiveOffset.z + negativeOffset.z)/2.0f;		
		
		vector<Vertex*> done;
		for(int i=0; i < polygons.size(); i++) {
			for(int j=0; j < polygons[i]->getVertexCount(); j++) {	
				
				bool alreadyDone = false;
				for(int k=0; k < done.size(); k++) {
					if(done[k] == polygons[i]->getVertex(j))
						alreadyDone = true;
				}
				
				if(!alreadyDone) {
					polygons[i]->getVertex(j)->x = polygons[i]->getVertex(j)->x - finalOffset.x;
					polygons[i]->getVertex(j)->y = polygons[i]->getVertex(j)->y - finalOffset.y;
					polygons[i]->getVertex(j)->z = polygons[i]->getVertex(j)->z - finalOffset.z;				
					done.push_back(polygons[i]->getVertex(j));
				}
			}
		}		
	
		
		arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;
		
		return finalOffset;		
	}	
	
	Vector3 Mesh::calculateBBox() {
		Vector3 retVec;
		
		for(int i=0; i < polygons.size(); i++) {
			for(int j=0; j < polygons[i]->getVertexCount(); j++) {				
				retVec.x = max(retVec.x,fabs(polygons[i]->getVertex(j)->x));
				retVec.y = max(retVec.y,fabs(polygons[i]->getVertex(j)->y));
				retVec.z = max(retVec.z,fabs(polygons[i]->getVertex(j)->z));							
				
			}
		}
		
		return retVec*2;
	}
	
	void Mesh::createSphere(Number radius, Number numRings, Number numSegments) {

		Number fDeltaRingAngle = (PI / numRings);
        Number fDeltaSegAngle = (2 * PI / numSegments);
		
		for(int i=0; i < numRings; i++) {
			Number r0 = radius * sinf (i * fDeltaRingAngle);
			Number y0 = radius * cosf (i * fDeltaRingAngle);			
			for(int j=0; j < numSegments; j++) {
				Number x0 = r0 * sinf(j * fDeltaSegAngle);
				Number z0 = r0 * cosf(j * fDeltaSegAngle);
				
				Number tx0 = (Number) j / (Number) numSegments;
				Number tx1 = (Number) i / (Number) numRings;
				
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

	void Mesh::createCylinder(Number height, Number radius, int numSegments) {
	
		setMeshType(Mesh::TRI_MESH);
		Number lastx = -1;
		Number lastz = -1;		
		for (int i=0 ; i < numSegments+1; i++) {
			Number pos = ((PI*2.0)/((Number)numSegments)) * i;
			Number x = sinf(pos) * radius;
			Number z = cosf(pos) * radius;
			
			if(lastx > -1) {
				Polygon *polygon = new Polygon();
				polygon->addVertex(lastx,0,lastz,0,0);				
				polygon->addVertex(x,0,z, 1, 0);
				polygon->addVertex(x,height,z, 1, 1);				
				addPolygon(polygon);							

				polygon = new Polygon();	
				polygon->addVertex(x,height,z, 1, 1);								
				polygon->addVertex(lastx,height,lastz, 1, 1);																												
				polygon->addVertex(lastx,0,lastz,0,0);												
				addPolygon(polygon);	
				
				polygon = new Polygon();	
				polygon->addVertex(lastx,height,lastz, 1, 1);				
				polygon->addVertex(x,height,z, 1, 1);														
				polygon->addVertex(0,height,0,0,0);							
				addPolygon(polygon);			

				polygon = new Polygon();	
				polygon->addVertex(lastx,0,lastz, 1, 1);						
				polygon->addVertex(0,0,0,0,0);																																					
				polygon->addVertex(x,0,z, 1, 1);								
				addPolygon(polygon);			

								
			}
			lastx = x;
			lastz = z;			
		/*
			Polygon *polygon = new Polygon();
			polygon->addVertex(w,0,h, 1, 1);
			polygon->addVertex(0,0,h, 1, 0);
			polygon->addVertex(0,0,0,0,0);
			polygon->addVertex(w,0,0,0,1);
			addPolygon(polygon);			
			*/
        }
		
		for(int i=0; i < polygons.size(); i++) {
			for(int j=0; j < polygons[i]->getVertexCount(); j++) {
//				polygons[i]->getVertex(j)->x = polygons[i]->getVertex(j)->x - (radius/2.0f);
				polygons[i]->getVertex(j)->y = polygons[i]->getVertex(j)->y - (height/2.0f);
//				polygons[i]->getVertex(j)->z = polygons[i]->getVertex(j)->z - (radius/2.0f);	
			}
		}
		
		
		calculateNormals();
		arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;		
		arrayDirtyMap[RenderDataArray::COLOR_DATA_ARRAY] = true;				
		arrayDirtyMap[RenderDataArray::TEXCOORD_DATA_ARRAY] = true;						
		arrayDirtyMap[RenderDataArray::NORMAL_DATA_ARRAY] = true;										
		
	}
	
	void Mesh::createCone(Number height, Number radius, int numSegments) {
	
	
		setMeshType(Mesh::TRI_MESH);
		Number lastx = -1;
		Number lastz = -1;		
		for (int i=0 ; i < numSegments+1; i++) {
			Number pos = ((PI*2.0)/((Number)numSegments)) * i;
			Number x = sinf(pos) * radius;
			Number z = cosf(pos) * radius;
			
			if(lastx > -1) {
				Polygon *polygon = new Polygon();
				polygon->addVertex(lastx,0,lastz,0,0);				
				polygon->addVertex(x,0,z, 1, 0);
				polygon->addVertex(0,height,0, 1, 1);				
				addPolygon(polygon);							
			

				polygon = new Polygon();	
				polygon->addVertex(x,0,z, 1, 1);												
				polygon->addVertex(lastx,0,lastz, 1, 1);																														
				polygon->addVertex(0,0,0,0,0);												
				addPolygon(polygon);			

								
			}
			lastx = x;
			lastz = z;			
		/*
			Polygon *polygon = new Polygon();
			polygon->addVertex(w,0,h, 1, 1);
			polygon->addVertex(0,0,h, 1, 0);
			polygon->addVertex(0,0,0,0,0);
			polygon->addVertex(w,0,0,0,1);
			addPolygon(polygon);			
			*/
        }
		
		for(int i=0; i < polygons.size(); i++) {
			for(int j=0; j < polygons[i]->getVertexCount(); j++) {
//				polygons[i]->getVertex(j)->x = polygons[i]->getVertex(j)->x - (radius/2.0f);
				polygons[i]->getVertex(j)->y = polygons[i]->getVertex(j)->y - (height/2.0f);
//				polygons[i]->getVertex(j)->z = polygons[i]->getVertex(j)->z - (radius/2.0f);	
			}
		}
		
		
		calculateNormals();
		arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;		
		arrayDirtyMap[RenderDataArray::COLOR_DATA_ARRAY] = true;				
		arrayDirtyMap[RenderDataArray::TEXCOORD_DATA_ARRAY] = true;						
		arrayDirtyMap[RenderDataArray::NORMAL_DATA_ARRAY] = true;										
			
	
	}

	void Mesh::createBox(Number w, Number d, Number h) {
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