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
    meshHasVertexBuffer = false;
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
    for(int i=0; i < vertices.size(); i++) {
        len = vertices[i]->length();
        if(len > hRad) {
            hRad = len;
        }
    }
    return hRad;
}

void Mesh::saveToFile(OSFILE *outFile) {				
    unsigned int numVertices = vertices.size();

    OSBasics::write(&meshType, sizeof(unsigned int), 1, outFile);		
    OSBasics::write(&numVertices, sizeof(unsigned int), 1, outFile);

    Vector3_struct pos;
    Vector3_struct nor;
    Vector3_struct tan;
    Vector4_struct col;
    Vector2_struct tex;

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
        
        OSBasics::write(&pos, sizeof(Vector3_struct), 1, outFile);
        OSBasics::write(&nor, sizeof(Vector3_struct), 1, outFile);
        OSBasics::write(&tan, sizeof(Vector3_struct), 1, outFile);				
        OSBasics::write(&col, sizeof(Vector4_struct), 1, outFile);				
        OSBasics::write(&tex, sizeof(Vector2_struct), 1, outFile);

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


void Mesh::loadFromFile(OSFILE *inFile) {

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
        OSBasics::read(&nor, sizeof(Vector3_struct), 1, inFile);
        OSBasics::read(&tan, sizeof(Vector3_struct), 1, inFile);				
        OSBasics::read(&col, sizeof(Vector4_struct), 1, inFile);						
        OSBasics::read(&tex, sizeof(Vector2_struct), 1, inFile);						
        
        Vertex *vertex = new Vertex(pos.x, pos.y, pos.z);
        vertex->setNormal(nor.x,nor.y, nor.z);
        vertex->tangent = Vector3(tan.x, tan.y, tan.z);
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
        
        Number totalWeight = 0;				
        for(int m=0; m < vertex->getNumBoneAssignments(); m++) {
            BoneAssignment *ba = vertex->getBoneAssignment(m);					
            totalWeight += ba->weight;
        }				

        for(int m=0; m < vertex->getNumBoneAssignments(); m++) {
            BoneAssignment *ba = vertex->getBoneAssignment(m);					
            ba->weight = ba->weight/totalWeight;
        }				
        
        addVertex(vertex);
    }

    arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;		
    arrayDirtyMap[RenderDataArray::COLOR_DATA_ARRAY] = true;				
    arrayDirtyMap[RenderDataArray::TEXCOORD_DATA_ARRAY] = true;
    arrayDirtyMap[RenderDataArray::NORMAL_DATA_ARRAY] = true;	
    arrayDirtyMap[RenderDataArray::TANGENT_DATA_ARRAY] = true;								
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

void Mesh::saveToFile(const String& fileName) {
    OSFILE *outFile = OSBasics::open(fileName, "wb");
    if(!outFile) {
        Logger::log("Error opening mesh file for saving: %s", fileName.c_str());
    }
    saveToFile(outFile);
    OSBasics::close(outFile);	

}

void Mesh::loadMesh(const String& fileName) {
    OSFILE *inFile = OSBasics::open(fileName, "rb");
    if(!inFile) {
        Logger::log("Error opening mesh file %s", fileName.c_str());
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

void Mesh::createLineCircle(Number w, Number h, unsigned int numSegments) {
    setMeshType(Mesh::TRIFAN_MESH);
 
    int step;
    if(numSegments > 0) {
        step = ceil(360/numSegments);
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
    
    return retVec*2;
}

void Mesh::createSphere(Number _radius, int _segmentsH, int _segmentsW) {

    setMeshType(Mesh::TRI_MESH);

    Vector3 **grid = (Vector3 **) malloc(sizeof(Vector3*) * (_segmentsH+1));
    for (int i=0 ; i < _segmentsH+1; i++) {
        grid[i] = (Vector3*) malloc(sizeof(Vector3) * _segmentsW+1);		
    }
    
    for (int i = 0; i < _segmentsW; i++) {
        grid[0][i] = Vector3(0,-_radius,0);
    }
        
    for (int j = 1; j < _segmentsH; j++) {
        Number horangle = ((float)j) / ((float)_segmentsH) * PI;
        Number z = -_radius * cos(horangle);
        Number ringradius = _radius * sin(horangle);

        for (int i = 0; i < _segmentsW; i++) {
            Number verangle = 2.0 * ((float)i) / ((float)_segmentsW) * PI;
            Number x = ringradius * sin(verangle);
            Number y = ringradius * cos(verangle);
            grid[j][i] = Vector3(y, z, x);
        }
    }

    for (int i = 0; i < _segmentsW; i++) {
            grid[_segmentsH][i] = Vector3(0,_radius, 0);
    }

    for (int j = 1; j <= _segmentsH; j++) {
        for (int i = 0; i < _segmentsW; i++) {
            Vector3 a = grid[j][i];
            Vector3 b = grid[j][(i-1+_segmentsW) % _segmentsW];
            Vector3 c = grid[j-1][(i-1+_segmentsW) % _segmentsW];
            Vector3 d = grid[j-1][i];

            int i2 = i;
            if (i == 0) i2 = _segmentsW;

            Number vab = ((float)j) / ((float)_segmentsH);
            Number vcd = (((float)j)-1.0) / ((float)_segmentsH);
            Number uad = ((float)i2) / ((float)_segmentsW);
            Number ubc = (((float)i2)-1.0) / ((float)_segmentsW);
            Vector2 uva = Vector2(uad,vab);
            Vector2 uvb = Vector2(ubc,vab);
            Vector2 uvc = Vector2(ubc,vcd);
            Vector2 uvd = Vector2(uad,vcd);

            if (j < _segmentsH) {
                addVertex(c.x, c.y, c.z, uvc.x ,uvc.y);
                addVertex(b.x, b.y, b.z, uvb.x ,uvb.y);							
                addVertex(a.x, a.y, a.z, uva.x ,uva.y);
            }
            if (j > 1) {
                addVertex(d.x, d.y, d.z, uvd.x ,uvd.y);
                addVertex(c.x, c.y, c.z, uvc.x ,uvc.y);
                addVertex(a.x, a.y, a.z, uva.x ,uva.y);
            }
        }
    }
    
    for (int i=0 ; i < _segmentsH+1; i++) {
        free(grid[i]);
    }
    free(grid);

    calculateNormals();
    calculateTangents();
    arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;		
    arrayDirtyMap[RenderDataArray::COLOR_DATA_ARRAY] = true;				
    arrayDirtyMap[RenderDataArray::TEXCOORD_DATA_ARRAY] = true;						
    arrayDirtyMap[RenderDataArray::NORMAL_DATA_ARRAY] = true;
    arrayDirtyMap[RenderDataArray::TANGENT_DATA_ARRAY] = true;		
}

unsigned int Mesh::getVertexCount() {
    return vertices.size();
}

void Mesh::createTorus(Number radius, Number tubeRadius, int rSegments, int tSegments) {

    setMeshType(Mesh::TRI_MESH);
        
    Vector3 **grid = (Vector3 **) malloc(sizeof(Vector3*) * rSegments);
    for (int i=0 ; i < rSegments; i++) {
        grid[i] = (Vector3*) malloc(sizeof(Vector3) * tSegments);		
    }
    
    for (int i=0 ; i < rSegments; i++) {
        for (int j = 0; j < tSegments; ++j) {
            Number u = ((Number)i) / rSegments * 2.0 * PI;
            Number v = ((Number)j) / tSegments * 2.0 * PI;	

            grid[i][j] = Vector3((radius + tubeRadius*cos(v))*cos(u), tubeRadius*sin(v), (radius + tubeRadius*cos(v))*sin(u));							
                                                
        }
    }	
    
    for (int i=0 ; i < rSegments; i++) {
        for (int j = 0; j < tSegments; ++j) {

            int ip = (i+1) % rSegments;
            int jp = (j+1) % tSegments;
                
            Vector3 a = grid[i ][j];
            Vector3 b = grid[ip][j];
            Vector3 c = grid[i ][jp];
            Vector3 d = grid[ip][jp];

            Vector2 uva = Vector2(((Number)i)     / ((Number)rSegments), ((Number)j)     / ((Number)tSegments));
            Vector2 uvb = Vector2((((Number)i)+1.0) / ((Number)rSegments), ((Number)j)     / ((Number)tSegments));
            Vector2 uvc = Vector2(((Number)i)    / ((Number)rSegments), (((Number)j)+1.0) / ((Number)tSegments));
            Vector2 uvd = Vector2((((Number)i)+1.0) / ((Number)rSegments), (((Number)j)+1.0) / ((Number)tSegments));


            addVertex(c.x, c.y, c.z, uvc.x ,uvc.y);
            addVertex(b.x, b.y, b.z, uvb.x ,uvb.y);							
            addVertex(a.x, a.y, a.z, uva.x ,uva.y);

            addVertex(b.x, b.y, b.z, uvb.x ,uvb.y);
            addVertex(c.x, c.y, c.z, uvc.x ,uvc.y);					
            addVertex(d.x, d.y, d.z, uvd.x ,uvd.y);
        }
    }
    
    for (int i=0 ; i < rSegments; i++) {
        free(grid[i]);
    }		
    free(grid);
    

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
    Number lastx = 0;
    Number lastz = 0;
    Number lastv = 0;		
    for (int i=0 ; i < numSegments+1; i++) {
        Number v = ((Number)i)/((Number)numSegments);
        Number pos = ((PI*2.0)/((Number)numSegments)) * i;
        Number x = sin(pos) * radius;
        Number z = cos(pos) * radius;
        
        if(i > 0) {
            addVertex(lastx,0,lastz,lastv,0);				
            addVertex(x,0,z, v, 0);
            addVertex(x,height,z, v, 1);

            addVertex(x,height,z, v, 1);							
            addVertex(lastx,height,lastz, lastv, 1);
            addVertex(lastx,0,lastz,lastv,0);
            
            if(capped) {
                addVertex(lastx,height,lastz, 0.5+(lastz/radius*0.5), 0.5+(lastx/radius*0.5));			
                addVertex(x,height,z, 0.5+(z/radius*0.5), 0.5+(x/radius*0.5));
                addVertex(0,height,0,0.5,0.5);

                addVertex(lastx,0,lastz, 0.5+(lastz/radius*0.5), 0.5+(lastx/radius*0.5));						
                addVertex(0,0,0,0.5,0.5);
                addVertex(x,0,z, 0.5+(z/radius*0.5), 0.5+(x/radius*0.5));
            }
                            
        }
        lastx = x;
        lastz = z;			
        lastv = v;
    }
    
    for(int i=0; i < vertices.size(); i++) {
        vertices[i]->y = vertices[i]->y - (height/2.0f);
    }
    
    
    calculateNormals();
    calculateTangents();
    arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;		
    arrayDirtyMap[RenderDataArray::COLOR_DATA_ARRAY] = true;				
    arrayDirtyMap[RenderDataArray::TEXCOORD_DATA_ARRAY] = true;						
    arrayDirtyMap[RenderDataArray::NORMAL_DATA_ARRAY] = true;										
    arrayDirtyMap[RenderDataArray::TANGENT_DATA_ARRAY] = true;		
}

void Mesh::createCone(Number height, Number radius, int numSegments) {

    setMeshType(Mesh::TRI_MESH);
    
    Number lastx = 0;
    Number lasty = 0;
    Number lastv = 0;
    
    for (int i=0 ; i < numSegments+1; i++) {
        Number v = ((Number)i)/((Number)numSegments);
        Number pos = ((PI*2.0)/((Number)numSegments)) * i;
        Number x = sin(pos) * radius * 0.5;
        Number y = cos(pos) * radius * 0.5;
        
        if(i > 0) {
            
            addVertex(lastx,0, lasty, 0.5+(lasty/radius*0.5), 0.5+(lastx/radius*0.5))->setNormal(0.0, -1.0, 0.0);
            addVertex(x,0,y, 0.5+(y/radius*0.5), 0.5+(x/radius*0.5))->setNormal(0.0, -1.0, 0.0);                
            addVertex(0,height,0,0.5,0.5)->setNormal(0.0, -1.0, 0.0);
            
            addVertex(0,0,0,0.5,0.5)->setNormal(0.0, -1.0, 0.0);
            addVertex(x,0,y, 0.5+(y/radius*0.5), 0.5+(x/radius*0.5))->setNormal(0.0, -1.0, 0.0);
            addVertex(lastx,0, lasty, 0.5+(lasty/radius*0.5), 0.5+(lastx/radius*0.5))->setNormal(0.0, -1.0, 0.0);
        }
        lastx = x;
        lastv = v;
        lasty = y;
    }
    
    for(int i=0; i < vertices.size(); i++) {
        vertices[i]->y = vertices[i]->y - (height/2.0f);
    }
    
    calculateNormals();
    calculateTangents();
    arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;		
    arrayDirtyMap[RenderDataArray::COLOR_DATA_ARRAY] = true;				
    arrayDirtyMap[RenderDataArray::TEXCOORD_DATA_ARRAY] = true;
    arrayDirtyMap[RenderDataArray::NORMAL_DATA_ARRAY] = true;
    arrayDirtyMap[RenderDataArray::TANGENT_DATA_ARRAY] = true;			

}

void Mesh::createBox(Number w, Number d, Number h) {
    setMeshType(Mesh::TRI_MESH);
    
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

    calculateNormals(false);
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
    return vertices[index];
}

void Mesh::calculateTangents() {

    arrayDirtyMap[RenderDataArray::TANGENT_DATA_ARRAY] = true;		
}

void Mesh::calculateNormals(bool smooth, Number smoothAngle) {
    
    int polySize = 3;
    if(meshType == Mesh::QUAD_MESH) {
        polySize = 4;
    }
    
    for(int i=0; i < vertices.size(); i++) {
        vertices[i]->normal = Vector3();
    }

    for(int i=0; i+2 < vertices.size(); i += polySize) {
        const Vector3 e1 = *(vertices[i]) - *(vertices[i+1]);
        const Vector3 e2 = *(vertices[i+2]) - *(vertices[i+1]);
        const Vector3 no = e1.crossProduct(e2);
            
        vertices[i]->normal -= no;
        vertices[i+1]->normal -= no;
        vertices[i+2]->normal -= no;
    }
    
    arrayDirtyMap[RenderDataArray::NORMAL_DATA_ARRAY] = true;		
}

int Mesh::getMeshType() {
    return meshType;
}

void Mesh::setMeshType(int newType) {
    meshType = newType;
}
