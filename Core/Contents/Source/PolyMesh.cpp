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
#include "PolyLogger.h"
#include "OSBasics.h"

using std::min;
using std::max;
using std::vector;

using namespace Polycode;

Mesh::Mesh(const String& fileName) {
    
    for(int i=0; i < 16; i++) {
        arrayDirtyMap[i] = false;
        renderDataArrays[i] = NULL;
    }

    indexedMesh = false;
    meshType = TRI_MESH;
    meshHasVertexBuffer = false;
    loadMesh(fileName);
    vertexBuffer = NULL;			
    useVertexColors = false;
    useFaceNormals = false;
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
    indexedMesh = false;
    useFaceNormals = false;
}

Mesh *Mesh::MeshFromFileName(String& fileName) {
    return new Mesh(fileName);
}

Mesh::~Mesh() {
    clearMesh();
}

void Mesh::clearMesh() {
    for(int i=0; i < vertices.size(); i++) {
        delete vertices[i];
    }
    vertices.clear();
    indices.clear();
    faceNormals.clear();
    
    if(vertexBuffer)
        delete vertexBuffer;
    vertexBuffer = NULL;
    
    for(int i=0; i < 16; i++) {
        if(renderDataArrays[i]) {
            free(renderDataArrays[i]->arrayPtr);
            delete renderDataArrays[i];
            renderDataArrays[i] = NULL;
        }
    }

    useFaceNormals = false;
    meshHasVertexBuffer = false;
}

VertexBuffer *Mesh::getVertexBuffer() {
    return vertexBuffer;
}

void Mesh::setUseFaceNormals(bool val) {
    useFaceNormals = val;
    arrayDirtyMap[RenderDataArray::NORMAL_DATA_ARRAY] = true;
}

bool Mesh::getUseFaceNormals() {
    return useFaceNormals;
}


void Mesh::setVertexBuffer(VertexBuffer *buffer) {    
    if(vertexBuffer) {
        delete vertexBuffer;
    }
    vertexBuffer = buffer;
    meshHasVertexBuffer = true;
}

Number Mesh::getRadius() {
    Number hRad = 0;
    Number len;
    for(int i=0; i < vertices.size(); i++) {
        len = vertices[i]->length();
        if(len > hRad) {
            hRad = len;
        }
    }
    return hRad;
}

void Mesh::saveToFile(OSFILE *outFile, bool writeNormals, bool writeTangents, bool writeColors, bool writeBoneWeights, bool writeUVs, bool writeSecondaryUVs) {
    
    unsigned char meshFlags = 0;
    
    if(indexedMesh) {
        meshFlags |= 1 << 0;
    }
    if(writeNormals) {
        meshFlags |= 1 << 1;
    }
    if(writeTangents) {
        meshFlags |= 1 << 2;
    }
    if(writeColors) {
        meshFlags |= 1 << 3;
    }
    if(writeUVs) {
        meshFlags |= 1 << 4;
    }
    if(writeSecondaryUVs) {
        meshFlags |= 1 << 5;
    }
    if(writeBoneWeights) {
        meshFlags |= 1 << 6;
    }
    
    OSBasics::write(&meshFlags, sizeof(unsigned char), 1, outFile);
    
    unsigned int numVertices = vertices.size();
    OSBasics::write(&meshType, sizeof(unsigned int), 1, outFile);
    OSBasics::write(&numVertices, sizeof(unsigned int), 1, outFile);

    Vector3_struct pos;
    Vector3_struct nor;
    Vector3_struct tan;
    Vector4_struct col;
    Vector2_struct tex;
    Vector2_struct tex2;
    
    for(int i=0; i < vertices.size(); i++) {
        pos.x =  vertices[i]->x;
        pos.y =  vertices[i]->y;
        pos.z =  vertices[i]->z;

        nor.x =  vertices[i]->normal.x;
        nor.y =  vertices[i]->normal.y;
        nor.z =  vertices[i]->normal.z;

        tan.x =  vertices[i]->tangent.x;
        tan.y =  vertices[i]->tangent.y;
        tan.z =  vertices[i]->tangent.z;

        col.x =  vertices[i]->vertexColor.r;
        col.y =  vertices[i]->vertexColor.g;
        col.z =  vertices[i]->vertexColor.b;
        col.w =  vertices[i]->vertexColor.a;
        
        tex.x = vertices[i]->getTexCoord().x;
        tex.y = vertices[i]->getTexCoord().y;

        tex2.x = vertices[i]->getSecondaryTexCoord().x;
        tex2.y = vertices[i]->getSecondaryTexCoord().y;

        OSBasics::write(&pos, sizeof(Vector3_struct), 1, outFile);
        
        if(writeNormals) {
            OSBasics::write(&nor, sizeof(Vector3_struct), 1, outFile);
        }
        if(writeTangents) {
            OSBasics::write(&tan, sizeof(Vector3_struct), 1, outFile);
        }
        if(writeColors) {
            OSBasics::write(&col, sizeof(Vector4_struct), 1, outFile);
        }
        if(writeUVs) {
            OSBasics::write(&tex, sizeof(Vector2_struct), 1, outFile);
        }
        if(writeSecondaryUVs) {
            OSBasics::write(&tex2, sizeof(Vector2_struct), 1, outFile);
        }
        
        if(writeBoneWeights) {
            unsigned int numBoneWeights = vertices[i]->getNumBoneAssignments();
            OSBasics::write(&numBoneWeights, sizeof(unsigned int), 1, outFile);					
            for(int b=0; b < numBoneWeights; b++) {
                BoneAssignment *a = vertices[i]->getBoneAssignment(b);
                unsigned int boneID = a->boneID;
                float weight = a->weight;
                OSBasics::write(&boneID, sizeof(unsigned int), 1, outFile);
                OSBasics::write(&weight, sizeof(float), 1, outFile);												
            }
        }
    }
    
    if(indexedMesh) {
        unsigned int numIndices = indices.size();
        OSBasics::write(&numIndices, sizeof(unsigned int), 1, outFile);
        for(int i=0; i < numIndices; i++) {
            OSBasics::write(&indices[i], sizeof(unsigned int), 1, outFile);
        }
    }
}


void Mesh::loadFromFile(OSFILE *inFile) {
    
    unsigned char meshFlags;
    OSBasics::read(&meshFlags, sizeof(unsigned char), 1, inFile);
    
    indexedMesh = meshFlags & (1 << 0);
    bool hasNormals = meshFlags & (1 << 1);
    bool hasTangents = meshFlags & (1 << 2);
    bool hasColors = meshFlags & (1 << 3);
    bool hasUV = meshFlags & (1 << 4);
    bool hasSecondaryUVs = meshFlags & (1 << 5);
    bool hasBoneWeights = meshFlags & (1 << 6);
    
    unsigned int meshType;		
    OSBasics::read(&meshType, sizeof(unsigned int), 1, inFile);
    setMeshType(meshType);
    
    unsigned int numVertices;
    OSBasics::read(&numVertices, sizeof(unsigned int), 1, inFile);
    
    Vector3_struct pos;
    Vector3_struct nor;
    Vector3_struct tan;
    Vector4_struct col;			
    Vector2_struct tex;
    
    for(int i=0; i < numVertices; i++) {
        OSBasics::read(&pos, sizeof(Vector3_struct), 1, inFile);
        Vertex *vertex = new Vertex(pos.x, pos.y, pos.z);
        
        if(hasNormals) {
            OSBasics::read(&nor, sizeof(Vector3_struct), 1, inFile);
            vertex->setNormal(nor.x,nor.y, nor.z);
            vertex->restNormal.set(nor.x,nor.y, nor.z);
        }
        if(hasTangents) {
            OSBasics::read(&tan, sizeof(Vector3_struct), 1, inFile);
            vertex->tangent = Vector3(tan.x, tan.y, tan.z);
        }
        
        if(hasColors) {
            OSBasics::read(&col, sizeof(Vector4_struct), 1, inFile);
            vertex->vertexColor.setColor(col.x,col.y, col.z, col.w);
        }
        
        if(hasUV) {
            OSBasics::read(&tex, sizeof(Vector2_struct), 1, inFile);
            vertex->setTexCoord(tex.x, tex.y);
        }
        
        if(hasSecondaryUVs) {
            OSBasics::read(&tex, sizeof(Vector2_struct), 1, inFile);
            vertex->setSecondaryTexCoord(tex.x, tex.y);
        }
        
        if(hasBoneWeights) {
            unsigned int numBoneWeights;
            OSBasics::read(&numBoneWeights, sizeof(unsigned int), 1, inFile);								
            for(int b=0; b < numBoneWeights; b++) {
                float weight;
                unsigned int boneID;
                OSBasics::read(&boneID, sizeof(unsigned int), 1, inFile);													
                OSBasics::read(&weight, sizeof(float), 1, inFile);																		
                vertex->addBoneAssignment(boneID, weight);
            }
            
            Number totalWeight = 0;				
            for(int m=0; m < vertex->getNumBoneAssignments(); m++) {
                BoneAssignment *ba = vertex->getBoneAssignment(m);					
                totalWeight += ba->weight;
            }				

            for(int m=0; m < vertex->getNumBoneAssignments(); m++) {
                BoneAssignment *ba = vertex->getBoneAssignment(m);					
                ba->weight = ba->weight/totalWeight;
            }				
        }
        addVertex(vertex);
    }
    
    if(indexedMesh) {
        unsigned int numIndices;
        OSBasics::read(&numIndices, sizeof(unsigned int), 1, inFile);
        indices.clear();
        unsigned int val;
        for(int i=0; i < numIndices; i++) {
            OSBasics::read(&val, sizeof(unsigned int), 1, inFile);
            indices.push_back(val);
        }
    }

    dirtyArrays();
}

Vertex *Mesh::addVertex(Number x, Number y, Number z) {
    Vertex *vertex = new Vertex(x,y,z);
    vertices.push_back(vertex);
    return vertex;
}

void Mesh::addVertex(Vertex *vertex) {
    vertices.push_back(vertex);
}

Vertex *Mesh::addVertex(Number x, Number y, Number z, Number u, Number v) {
    Vertex *vertex = new Vertex(x,y,z,u,v);
    vertices.push_back(vertex);
    return vertex;
}

void Mesh::saveToFile(const String& fileName, bool writeNormals, bool writeTangents, bool writeColors, bool writeBoneWeights, bool writeUVs, bool writeSecondaryUVs) {
    OSFILE *outFile = OSBasics::open(fileName, "wb");
    if(!outFile) {
        Logger::log("Error opening mesh file for saving: %s\n", fileName.c_str());
        return;
    }
    saveToFile(outFile, writeNormals, writeTangents, writeColors, writeBoneWeights, writeUVs, writeSecondaryUVs);
    OSBasics::close(outFile);	

}

void Mesh::loadMesh(const String& fileName) {
    OSFILE *inFile = OSBasics::open(fileName, "rb");
    if(!inFile) {
        Logger::log("Error opening mesh file %s\n", fileName.c_str());
        return;
    }
    loadFromFile(inFile);
    OSBasics::close(inFile);	
    arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;		
    arrayDirtyMap[RenderDataArray::COLOR_DATA_ARRAY] = true;				
    arrayDirtyMap[RenderDataArray::TEXCOORD_DATA_ARRAY] = true;						
    arrayDirtyMap[RenderDataArray::NORMAL_DATA_ARRAY] = true;										
    arrayDirtyMap[RenderDataArray::TANGENT_DATA_ARRAY] = true;		
}

void Mesh::createCircle(Number w, Number h, unsigned int numSegments) {
    setMeshType(Mesh::TRI_MESH);

    Number lastx = 0;
    Number lasty = 0;
    Number lastv = 0;

    for (int i=0 ; i < numSegments+1; i++) {
        Number v = ((Number)i)/((Number)numSegments);
        Number pos = ((PI*2.0)/((Number)numSegments)) * i;
        Number x = sin(pos) * w * 0.5;
        Number y = cos(pos) * h * 0.5;
        
        if(i > 0) {
            addVertex(0,0,0,0.5,0.5)->setNormal(0.0, 0.0, 1.0);
            addVertex(x,y,0, 0.5+(y/h*0.5), 0.5+(x/w*0.5))->setNormal(0.0, 0.0, 1.0);
            addVertex(lastx,lasty,0, 0.5+(lasty/h*0.5), 0.5+(lastx/w*0.5))->setNormal(0.0, 0.0, 1.0);
        }
        lastx = x;
        lastv = v;
        lasty = y;
    }
    
    
    arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;
    arrayDirtyMap[RenderDataArray::COLOR_DATA_ARRAY] = true;				
    arrayDirtyMap[RenderDataArray::TEXCOORD_DATA_ARRAY] = true;
    arrayDirtyMap[RenderDataArray::NORMAL_DATA_ARRAY] = true;
    arrayDirtyMap[RenderDataArray::TANGENT_DATA_ARRAY] = true;			
}

Mesh *Mesh::Copy() const {
    Mesh *newMesh = new Mesh(meshType);
    newMesh->indexedMesh = indexedMesh;
    newMesh->setUseFaceNormals(useFaceNormals);
    
    for(int i=0; i < vertices.size(); i++) {
        Vertex *v = new Vertex();
        (*v) = *(vertices[i]);
        newMesh->addVertex(v);
    }

    for(int i=0; i < indices.size(); i++) {
        newMesh->addIndex(indices[i]);
    }

    for(int i=0; i < faceNormals.size(); i++) {
        newMesh->addFaceNormal(faceNormals[i]);
    }
    
    newMesh->dirtyArrays();
    return newMesh;
}

void Mesh::addFaceNormal(Vector3 faceNormal) {
    faceNormals.push_back(faceNormal);
}

void Mesh::createLineCircle(Number w, Number h, unsigned int numSegments) {
    setMeshType(Mesh::TRIFAN_MESH);
 
    int step;
    if(numSegments > 0) {
        step = ceil(360.0/((Number)numSegments));
    } else {
        step = 1;
    }
    
    
    addVertex(cosf(0)*(w/2),sinf(0)*(h/2), 0, (cosf(0)*0.5) + 0.5,(sinf(0) * 0.5)+ 0.5);
    
    for (int i=0; i < 361; i+= step) {
        Number degInRad = i*TORADIANS;
        Vertex *v = addVertex(cos(degInRad)*(w/2),sin(degInRad)*(h/2), 0, (cos(degInRad) * 0.5)+ 0.5 , 1.0- ((sin(degInRad) * 0.5)+ 0.5));
        Vector3 normal = *v;
        normal.Normalize();
        v->normal = normal;
    }
    
    arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;
    arrayDirtyMap[RenderDataArray::COLOR_DATA_ARRAY] = true;
    arrayDirtyMap[RenderDataArray::TEXCOORD_DATA_ARRAY] = true;
    arrayDirtyMap[RenderDataArray::NORMAL_DATA_ARRAY] = true;
}

void Mesh::createVPlane(Number w, Number h) {
    setMeshType(Mesh::TRI_MESH);
    
    addVertex(0,0,0,0,0)->setNormal(0.0, 0.0, 1.0);
    addVertex(w,0,0, 1, 0)->setNormal(0.0, 0.0, 1.0);
    addVertex(w,h,0, 1, 1)->setNormal(0.0, 0.0, 1.0);
    
    addVertex(0,0,0,0,0)->setNormal(0.0, 0.0, 1.0);
    addVertex(w,h,0, 1, 1)->setNormal(0.0, 0.0, 1.0);
    addVertex(0,h,0,0,1)->setNormal(0.0, 0.0, 1.0);
    
    for(int i=0; i < vertices.size(); i++) {
            vertices[i]->x = vertices[i]->x - (w/2.0f);
            vertices[i]->y = vertices[i]->y - (h/2.0f);
    }

    calculateNormals();
    calculateTangents();
    
    arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;
    arrayDirtyMap[RenderDataArray::COLOR_DATA_ARRAY] = true;				
    arrayDirtyMap[RenderDataArray::TEXCOORD_DATA_ARRAY] = true;						
    arrayDirtyMap[RenderDataArray::NORMAL_DATA_ARRAY] = true;				
    arrayDirtyMap[RenderDataArray::TANGENT_DATA_ARRAY] = true;		
}	

void Mesh::createPlane(Number w, Number h) {
    setMeshType(Mesh::TRI_MESH);
    
    addVertex(0,0,h,0,0);
    addVertex(w,0,h, 1, 0);
    addVertex(w,0,0, 1, 1);
    
    addVertex(0,0,h,0,0);
    addVertex(w,0,0, 1, 1);
    addVertex(0,0,0,0,1);
    
    for(int i=0; i < vertices.size(); i++) {
        vertices[i]->x = vertices[i]->x - (w/2.0f);
        vertices[i]->z = vertices[i]->z - (h/2.0f);
    }

    calculateNormals();
    calculateTangents();
    arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;		
    arrayDirtyMap[RenderDataArray::COLOR_DATA_ARRAY] = true;				
    arrayDirtyMap[RenderDataArray::TEXCOORD_DATA_ARRAY] = true;						
    arrayDirtyMap[RenderDataArray::NORMAL_DATA_ARRAY] = true;										
    arrayDirtyMap[RenderDataArray::TANGENT_DATA_ARRAY] = true;		
}

Vector3 Mesh::recenterMesh() {
    Vector3 positiveOffset;
    Vector3 negativeOffset;
    
    for(int i=0; i < vertices.size(); i++) {
        positiveOffset.x = max(positiveOffset.x, vertices[i]->x);
        positiveOffset.y = max(positiveOffset.y, vertices[i]->y);
        positiveOffset.z = max(positiveOffset.z, vertices[i]->z);

        negativeOffset.x = min(negativeOffset.x, vertices[i]->x);
        negativeOffset.y = min(negativeOffset.y, vertices[i]->y);
        negativeOffset.z = min(negativeOffset.z, vertices[i]->z);
    }		
    
    Vector3 finalOffset;
    
    finalOffset.x = (positiveOffset.x + negativeOffset.x)/2.0f;
    finalOffset.y = (positiveOffset.y + negativeOffset.y)/2.0f;
    finalOffset.z = (positiveOffset.z + negativeOffset.z)/2.0f;		
    
    for(int i=0; i < vertices.size(); i++) {
        vertices[i]->x = vertices[i]->x - finalOffset.x;
        vertices[i]->y = vertices[i]->y - finalOffset.y;
        vertices[i]->z = vertices[i]->z - finalOffset.z;
    }		

    
    arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;
    
    return finalOffset;		
}	

Vector3 Mesh::calculateBBox() {
    Vector3 retVec;
    
    for(int i=0; i < vertices.size(); i++) {
        retVec.x = max(retVec.x,fabs(vertices[i]->x));
        retVec.y = max(retVec.y,fabs(vertices[i]->y));
        retVec.z = max(retVec.z,fabs(vertices[i]->z));
    }
    
    if(retVec.x == 0.0) {
        retVec.x = 0.001;
    }
    if(retVec.y == 0.0) {
        retVec.y = 0.001;
    }
    if(retVec.z == 0.0) {
        retVec.z = 0.001;
    }

    return retVec*2;
}

void Mesh::createSphere(Number radius, int segmentsH, int segmentsW) {

    segmentsH++;
    segmentsW++;
    
    setMeshType(Mesh::TRI_MESH);
    indexedMesh = true;

    Number tdelta = 360.f/(segmentsW-1);
    Number pdelta = 180.f/(segmentsH-1);
    
    Number phi = -90;
    Number theta = 0;
    
    for(unsigned int i = 0; i< segmentsH; i++) {
        for(unsigned int j = 0; j < segmentsW; j++) {
            Vector3 v;
            v.x = radius * cos(phi*PI/180.f) * cos(theta*PI/180.f);
            v.y = radius * sin(phi*PI/180.f);
            v.z = radius * cos(phi*PI/180.f) * sin(theta*PI/180.f);
            Vertex *vert = addVertex(v.x, v.y, v.z);
            v.Normalize();
            vert->normal = v;
            vert->texCoord = Vector2(-theta/(360.f) , (phi+90.f)/180.f);
            theta += tdelta;
        }
        phi += pdelta;
        theta = 0;
    }
    
    for(unsigned int i = 0; i < segmentsH-1; i++) {
        for(unsigned int j = 0; j< segmentsW-1; j++) {
            addIndexedFace(((i+1)*segmentsW) + j, ((i+1)*segmentsW) + j+1, (i*segmentsW) + j+1);
            addIndexedFace((i*segmentsW) + j+1, (i*segmentsW)+j, ((i+1)*segmentsW) + j);
        }
    }

    calculateTangents();
    arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;
    arrayDirtyMap[RenderDataArray::COLOR_DATA_ARRAY] = true;
    arrayDirtyMap[RenderDataArray::TEXCOORD_DATA_ARRAY] = true;
    arrayDirtyMap[RenderDataArray::NORMAL_DATA_ARRAY] = true;
    arrayDirtyMap[RenderDataArray::TANGENT_DATA_ARRAY] = true;		
}

unsigned int Mesh::getActualVertexCount() const {
    return vertices.size();    
}

unsigned int Mesh::getVertexCount() {
    if(indexedMesh) {
        return indices.size();
    } else {
        return vertices.size();
    }
}

unsigned int Mesh::getIndexCount() {
    return indices.size();
}

unsigned int Mesh::getIndexAt(unsigned int index) {
    if(index < indices.size()) {
        return indices[index];
    }
    return 0;
}

void Mesh::createTorus(Number radius, Number tubeRadius, int segmentsW, int segmentsH) {

    segmentsH++;
    segmentsW++;
    
    setMeshType(Mesh::TRI_MESH);
    indexedMesh = true;
    
    Number tdelta = 360.f/(segmentsW-1);
    Number pdelta = 360.f/(segmentsH-1);
    
    Number phi = -90;
    Number theta = 0;
    
    for(unsigned int i = 0; i< segmentsH; i++) {
        for(unsigned int j = 0; j < segmentsW; j++) {
            Vector3 v;
            
            v.x = (radius + tubeRadius*cos(phi*TORADIANS))*cos(theta*TORADIANS);
            v.y = tubeRadius*sin(phi*TORADIANS);
            v.z = (radius + tubeRadius*cos(phi*TORADIANS))*sin(theta*TORADIANS);
            
            Vertex *vert = addVertex(v.x, v.y, v.z);
            vert->texCoord = Vector2(-theta/(360.f) , (phi/(360.f)) + 0.5);
            theta += tdelta;
        }
        phi += pdelta;
        theta = 0;
    }
    
    for(unsigned int i = 0; i < segmentsH-1; i++) {
        for(unsigned int j = 0; j< segmentsW-1; j++) {
            addIndexedFace(((i+1)*segmentsW) + j, ((i+1)*segmentsW) + j+1, (i*segmentsW) + j+1);
            addIndexedFace((i*segmentsW) + j+1, (i*segmentsW)+j, ((i+1)*segmentsW) + j);
        }
    }
    
    calculateNormals();
    calculateTangents();
    arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;
    arrayDirtyMap[RenderDataArray::COLOR_DATA_ARRAY] = true;				
    arrayDirtyMap[RenderDataArray::TEXCOORD_DATA_ARRAY] = true;						
    arrayDirtyMap[RenderDataArray::NORMAL_DATA_ARRAY] = true;										
    arrayDirtyMap[RenderDataArray::TANGENT_DATA_ARRAY] = true;				
}

void Mesh::createCylinder(Number height, Number radius, int numSegments, bool capped) {

    setMeshType(Mesh::TRI_MESH);
    indexedMesh = true;
    
    Number lastx = 0;
    Number lastz = 0;
    Number lastv = 0;
    
    numSegments++;
    
    if(capped) {
        addVertex(0,0,0,0.5,0.5)->setNormal(0.0, -1.0, 0.0);
        addVertex(0,height,0,0.5,0.5)->setNormal(0.0, 1.0, 0.0);
    }
    
    for (int i=0 ; i < numSegments; i++) {
        Number v = ((Number)i)/((Number)numSegments-1);
        Number pos = ((PI*2.0)/((Number)numSegments-1)) * i;
        Number x = sin(pos);
        Number z = cos(pos);
        
        addVertex(x*radius,0,z*radius, v, 0)->setNormal(x, 0, z);
        addVertex(x*radius,height,z*radius, v, 1)->setNormal(x,0,z);
        
        if(capped) {
            addVertex(x*radius,0,z*radius, 0.5+(z*0.5), 0.5+(x*0.5))->setNormal(0.0, -1.0, 0.0);
            addVertex(x*radius,height,z*radius, 0.5+(z*0.5), 0.5+(x*0.5))->setNormal(0.0, 1.0, 0.0);
        }

        lastx = x;
        lastz = z;			
        lastv = v;
    }
    
    for(int i=0; i < vertices.size(); i++) {
        vertices[i]->y = vertices[i]->y - (height/2.0f);
    }
    
    int vertexOffset = 2;
    int vertexInterval = 1;
    if(capped) {
        vertexInterval = 3;
        vertexOffset = 6;
    }

    
    for (int i=1 ; i <= numSegments-1; i++) {
        addIndexedFace(vertexOffset, vertexOffset-vertexInterval, vertexOffset-vertexInterval-1 );
        addIndexedFace(vertexOffset, vertexOffset+1, vertexOffset-vertexInterval );
        vertexOffset += 2;
        
        if(capped) {
            addIndexedFace(vertexOffset, vertexOffset-vertexInterval-1, 0);
            addIndexedFace(1, vertexOffset-vertexInterval, vertexOffset+1);
            vertexOffset += 2;
        }
    }
    
    
    calculateTangents();
    arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;		
    arrayDirtyMap[RenderDataArray::COLOR_DATA_ARRAY] = true;				
    arrayDirtyMap[RenderDataArray::TEXCOORD_DATA_ARRAY] = true;						
    arrayDirtyMap[RenderDataArray::NORMAL_DATA_ARRAY] = true;										
    arrayDirtyMap[RenderDataArray::TANGENT_DATA_ARRAY] = true;		
}

void Mesh::createCone(Number height, Number radius, int numSegments) {
    
    setMeshType(Mesh::TRI_MESH);
    indexedMesh = true;
    
    Number lastx = 0;
    Number lastz = 0;
    
    numSegments *= 2;
    
    if(!(numSegments % 2)) {
        numSegments++;
    }
    
    addVertex(0,0,0,0.5,0.5)->setNormal(0.0, -1.0, 0.0);
    
    for (int i=0 ; i < numSegments; i++) {
        Number pos = ((PI*2.0)/((Number)numSegments-1)) * i;
        Number x = sin(pos);
        Number z = cos(pos);

        if(!(i % 2)) {
            addVertex(x*radius,0,z*radius, 0.5+(z*0.5), 0.5+(x*0.5))->setNormal(x, 0.0, z);
            addVertex(x*radius,0,z*radius, 0.5+(z*0.5), 0.5+(x*0.5))->setNormal(0.0, -1.0, 0.0);
        } else {
            addVertex(0,height,0, 0.5, 0.5)->setNormal(0.0, 1.0, 0.0);
        }
        
        lastx = x;
        lastz = z;

    }
    
    for(int i=0; i < vertices.size(); i++) {
        vertices[i]->y = vertices[i]->y - (height/2.0f);
    }
    
    int vertexOffset = 4;
    
    for (int i=1 ; i <= (numSegments-1)/2; i++) {
        addIndexedFace(vertexOffset, vertexOffset-1, vertexOffset-3);
        addIndexedFace(vertexOffset+1, vertexOffset-2, 0);
        vertexOffset += 3;
    }
    
    
    calculateTangents();
    arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;
    arrayDirtyMap[RenderDataArray::COLOR_DATA_ARRAY] = true;
    arrayDirtyMap[RenderDataArray::TEXCOORD_DATA_ARRAY] = true;
    arrayDirtyMap[RenderDataArray::NORMAL_DATA_ARRAY] = true;
    arrayDirtyMap[RenderDataArray::TANGENT_DATA_ARRAY] = true;

}

void Mesh::addIndex(unsigned int index) {
    if(!vertices.size()) {
        return;
    }
    indices.push_back(index % vertices.size());
}

Vertex *Mesh::getActualVertex(unsigned int index) const {
    if(index < vertices.size()) {
        return vertices[index];
    } else {
        return NULL;
    }
}

void Mesh::addIndexedFace(unsigned int i1, unsigned int i2, unsigned int i3) {
    if(!vertices.size()) {
        return;
    }
    indices.push_back(i1 % vertices.size());
    indices.push_back(i2 % vertices.size());
    indices.push_back(i3 % vertices.size());
}

void Mesh::addIndexedFace(unsigned int i1, unsigned int i2) {
    if(!vertices.size()) {
        return;
    }
    indices.push_back(i1 % vertices.size());
    indices.push_back(i2 % vertices.size());
}

void Mesh::addIndexedFace(unsigned int i1, unsigned int i2, unsigned int i3, unsigned int i4) {
    if(!vertices.size()) {
        return;
    }
    indices.push_back(i1 % vertices.size());
    indices.push_back(i2 % vertices.size());
    indices.push_back(i3 % vertices.size());
    indices.push_back(i4 % vertices.size());
}

void Mesh::createBox(Number w, Number d, Number h) {
    setMeshType(Mesh::TRI_MESH);
    indexedMesh = false;
    
    addVertex(w,0,h, 1, 1);
    addVertex(0,0,h, 1, 0);
    addVertex(0,0,0,0,0);
    
    addVertex(w,0,h, 1, 1);
    addVertex(0,0,0,0,0);
    addVertex(w,0,0,0,1);
    
    addVertex(w,d,h, 1, 1);
    addVertex(w,d,0, 1, 0);
    addVertex(0,d,0,0,0);
    
    addVertex(w,d,h, 1, 1);
    addVertex(0,d,0,0,0);
    addVertex(0,d,h,0,1);
    
    addVertex(0,d,0,0,1);
    addVertex(w,d,0, 1, 1);
    addVertex(w,0,0, 1, 0);
    
    addVertex(0,d,0,0,1);
    addVertex(w,0,0, 1, 0);
    addVertex(0,0,0,0,0);
    
    addVertex(0,0,h,0,0);
    addVertex(w,0,h, 1, 0);
    addVertex(w,d,h, 1, 1);
    
    addVertex(0,0,h,0,0);
    addVertex(w,d,h, 1, 1);
    addVertex(0,d,h,0,1);
    
    addVertex(0,0,h,0,1);
    addVertex(0,d,h, 1, 1);
    addVertex(0,d,0, 1, 0);
    
    addVertex(0,0,h,0,1);
    addVertex(0,d,0, 1, 0);
    addVertex(0,0,0,0,0);
    
    addVertex(w,0,h,0,1);
    addVertex(w,0,0, 1, 1);
    addVertex(w,d,0, 1, 0);
    
    addVertex(w,0,h,0,1);
    addVertex(w,d,0, 1, 0);
    addVertex(w,d,h,0,0);
    
    for(int i=0; i < vertices.size(); i++) {
        vertices[i]->x = vertices[i]->x - (w/2.0f);
        vertices[i]->y = vertices[i]->y - (d/2.0f);
        vertices[i]->z = vertices[i]->z - (h/2.0f);
    }
    
    calculateNormals();
    calculateTangents();
    
    arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;		
    arrayDirtyMap[RenderDataArray::COLOR_DATA_ARRAY] = true;				
    arrayDirtyMap[RenderDataArray::TEXCOORD_DATA_ARRAY] = true;						
    arrayDirtyMap[RenderDataArray::NORMAL_DATA_ARRAY] = true;		
    arrayDirtyMap[RenderDataArray::TANGENT_DATA_ARRAY] = true;									
}

void Mesh::dirtyArray(unsigned int arrayIndex) {
    if(arrayIndex < 16)
        arrayDirtyMap[arrayIndex] = true;				
}

void Mesh::dirtyArrays() {
    for(int i=0; i < 16; i++) {
        arrayDirtyMap[i] = true;
    }
}

Vertex *Mesh::getVertex(unsigned int index) const {
    if(indexedMesh) {
        return vertices[indices[index]];
    } else {
        return vertices[index];
    }
}

Vector3 Mesh::calculateFaceTangent(Vertex *v1, Vertex *v2, Vertex *v3) {
    Vector3 tangent;
    Vector3 side0 = *v1 - *v2;
    Vector3 side1 = *v3 - *v1;
    Vector3 normal = side1.crossProduct(side0);
    normal.Normalize();
    Number deltaV0 = v1->texCoord.y - v2->texCoord.y;
    Number deltaV1 = v3->texCoord.y - v1->texCoord.y;
    tangent = side0 * deltaV1 - side1 * deltaV0;
    tangent.Normalize();
    
    Number deltaU0 = v1->texCoord.x - v2->texCoord.x;
    Number deltaU1 = v3->texCoord.x - v1->texCoord.x;
    Vector3 binormal = side0 * deltaU1 - side1 * deltaU0;
    binormal.Normalize();
    Vector3 tangentCross = tangent.crossProduct(binormal);
    
    if (tangentCross.dot(normal) < 0.0f) {
        tangent = tangent * -1;
    }
    return tangent;
}

void Mesh::calculateTangents() {
    
    int polySize = 3;
    if(meshType == Mesh::QUAD_MESH) {
        polySize = 4;
    }
    
    faceNormals.clear();
    for(int i=0; i < vertices.size(); i++) {
        vertices[i]->tangent = Vector3();
    }
    
    if(indexedMesh) {
        for(int i=0; i+polySize-1 < indices.size(); i += polySize) {
            Vector3 tangent = calculateFaceTangent(vertices[indices[i]], vertices[indices[i+1]], vertices[indices[i+2]]);
            
            for(int j=0; j < polySize; j++) {
                vertices[indices[i+j]]->tangent -= tangent;
            }
        }
    } else {
        for(int i=0; i+polySize-1 < vertices.size(); i += polySize) {
            Vector3 tangent = calculateFaceTangent(vertices[i], vertices[i+1], vertices[i+2]);
            
            for(int j=0; j < polySize; j++) {
                vertices[i+j]->tangent = tangent * 1.0;
            }
        }
    }
    
    for(int i=0; i < vertices.size(); i++) {
        vertices[i]->tangent.Normalize();
    }

    arrayDirtyMap[RenderDataArray::TANGENT_DATA_ARRAY] = true;		
}

Vector3 Mesh::getFaceNormalForVertex(unsigned int index) {
    unsigned int faceNormalIndex;
    if(meshType == Mesh::QUAD_MESH) {
        faceNormalIndex = floor(((Number)index)/4.0);
    } else {
        faceNormalIndex = floor(((Number)index)/3.0);
    }
    
    if(faceNormalIndex < faceNormals.size()) {
        return faceNormals[faceNormalIndex];
    } else {
        return Vector3();
    }
}

void Mesh::calculateNormals(bool generateFaceNormals) {
    
    int polySize = 3;
    if(meshType == Mesh::QUAD_MESH) {
        polySize = 4;
    }
    
    faceNormals.clear();
    for(int i=0; i < vertices.size(); i++) {
        vertices[i]->normal = Vector3();
    }

    if(indexedMesh) {
        for(int i=0; i+polySize-1 < indices.size(); i += polySize) {
            const Vector3 e1 = *(vertices[indices[i]]) - *(vertices[indices[i+1]]);
            const Vector3 e2 = *(vertices[indices[i+2]]) - *(vertices[indices[i+1]]);
            const Vector3 no = e1.crossProduct(e2);
            
            for(int j=0; j < polySize; j++) {
                vertices[indices[i+j]]->normal -= no;
            }
            
            if(generateFaceNormals) {
                faceNormals.push_back(no * -1.0);
            }
        }
    } else {
        for(int i=0; i+polySize-1 < vertices.size(); i += polySize) {
            const Vector3 e1 = *(vertices[i]) - *(vertices[i+1]);
            const Vector3 e2 = *(vertices[i+2]) - *(vertices[i+1]);
            const Vector3 no = e1.crossProduct(e2);
            
            for(int j=0; j < polySize; j++) {
                vertices[i+j]->normal = no * -1.0;
            }
            
            if(generateFaceNormals) {
                faceNormals.push_back(no * -1.0);
            }
        }
    }
    
    for(int i=0; i < vertices.size(); i++) {
        vertices[i]->normal.Normalize();
    }
    for(int i=0; i < faceNormals.size(); i++) {
        faceNormals[i].Normalize();
    }
    
    arrayDirtyMap[RenderDataArray::NORMAL_DATA_ARRAY] = true;		
}

int Mesh::getMeshType() {
    return meshType;
}

void Mesh::setMeshType(int newType) {
    meshType = newType;
}
