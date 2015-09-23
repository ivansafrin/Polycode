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

#include <map>

#include "PolyMesh.h"
#include "PolyLogger.h"
#include "PolyRenderer.h"
#include "OSBasics.h"

using std::min;
using std::max;
using std::vector;

using namespace Polycode;

Mesh::Mesh(const String& fileName)
: vertexPositionArray(RenderDataArray::VERTEX_DATA_ARRAY),
vertexColorArray(RenderDataArray::COLOR_DATA_ARRAY),
vertexNormalArray(RenderDataArray::NORMAL_DATA_ARRAY),
vertexTexCoordArray(RenderDataArray::TEXCOORD_DATA_ARRAY),
vertexTexCoord2Array(RenderDataArray::TEXCOORD2_DATA_ARRAY),
vertexTangentArray(RenderDataArray::TANGENT_DATA_ARRAY),
vertexBoneWeightArray(RenderDataArray::BONE_WEIGHT_DATA_ARRAY),
vertexBoneIndexArray(RenderDataArray::BONE_INDEX_DATA_ARRAY),
indexArray(RenderDataArray::INDEX_DATA_ARRAY)
{

    indexedMesh = false;
    meshType = TRI_MESH;
    loadMesh(fileName);
    useVertexColors = false;
}

Mesh::Mesh(int meshType)
: vertexPositionArray(RenderDataArray::VERTEX_DATA_ARRAY),
vertexColorArray(RenderDataArray::COLOR_DATA_ARRAY),
vertexNormalArray(RenderDataArray::NORMAL_DATA_ARRAY),
vertexTexCoordArray(RenderDataArray::TEXCOORD_DATA_ARRAY),
vertexTexCoord2Array(RenderDataArray::TEXCOORD2_DATA_ARRAY),
vertexTangentArray(RenderDataArray::TANGENT_DATA_ARRAY),
vertexBoneWeightArray(RenderDataArray::BONE_WEIGHT_DATA_ARRAY),
vertexBoneIndexArray(RenderDataArray::BONE_INDEX_DATA_ARRAY),
indexArray(RenderDataArray::INDEX_DATA_ARRAY)
{

    this->meshType = meshType;
    useVertexColors = false;
    indexedMesh = false;
}

Mesh *Mesh::MeshFromFileName(String& fileName) {
    return new Mesh(fileName);
}

Mesh::~Mesh() {
    clearMesh();
}

void Mesh::clearMesh() {
    vertexPositionArray.data.clear();
    vertexColorArray.data.clear();
    vertexNormalArray.data.clear();
    vertexTexCoordArray.data.clear();
    vertexTexCoord2Array.data.clear();
    vertexTangentArray.data.clear();
    indexArray.data.clear();
    vertexBoneWeightArray.data.clear();
    vertexBoneIndexArray.data.clear();
}


Number Mesh::getRadius() {
    Number hRad = 0;
    Number len;
    for(int i=0; i < vertexPositionArray.data.size()-2; i += 3) {
        Vector3 vec;
        len = vec.length();
        if(len > hRad) {
            hRad = len;
        }
    }
    return hRad;
}

void Mesh::writeVertexBlock(VertexDataArray *array, OSFILE *outFile) {
    
    if(array->getDataSize() == 0) {
        return;
    }
    
    unsigned char blockType = array->type;
    unsigned int blockCount = array->getDataSize();

    OSBasics::write(&blockType, sizeof(unsigned char), 1, outFile);
    OSBasics::write(&blockCount, sizeof(unsigned int), 1, outFile);
    
    OSBasics::write(array->getArrayData(), sizeof(PolyRendererVertexType), array->getDataSize(), outFile);
}

void Mesh::writeIndexBlock(IndexDataArray *array, OSFILE *outFile) {
    
    if(array->getDataSize() == 0) {
        return;
    }
    
    unsigned char blockType = array->type;
    unsigned int blockCount = array->getDataSize();
    
    OSBasics::write(&blockType, sizeof(unsigned char), 1, outFile);
    OSBasics::write(&blockCount, sizeof(unsigned int), 1, outFile);
    
    OSBasics::write(array->getArrayData(), sizeof(PolyRendererIndexType), array->getDataSize(), outFile);
}

void Mesh::saveToFile(OSFILE *outFile, bool writeNormals, bool writeTangents, bool writeColors, bool writeBoneWeights, bool writeUVs, bool writeSecondaryUVs) {

    // new mesh format
    // IMPORTANT: PolyRendererVertexType type defines mesh format internal type. Consider making floats always. Don't want to cast for now.
    
    const char headerTag[] = "MSH2";
    OSBasics::write(headerTag, 1, 4, outFile);
    
    unsigned char meshFlags = 0;
    
    if(indexedMesh) {
        meshFlags |= 1 << 0;
    }
    
    OSBasics::write(&meshFlags, sizeof(unsigned char), 1, outFile);
    
    writeVertexBlock(&vertexPositionArray, outFile);
    
    if(indexedMesh) {
        writeIndexBlock(&indexArray, outFile);
    }
    
    if(writeColors) {
        writeVertexBlock(&vertexColorArray, outFile);
    }

    if(writeNormals) {
        writeVertexBlock(&vertexNormalArray, outFile);
    }
    
    if(writeUVs) {
        writeVertexBlock(&vertexTexCoordArray, outFile);
    }

    if(writeSecondaryUVs) {
        writeVertexBlock(&vertexTexCoord2Array, outFile);
    }
    
    if(writeTangents) {
        writeVertexBlock(&vertexTangentArray, outFile);
    }
    
    if(writeBoneWeights) {
        writeVertexBlock(&vertexBoneWeightArray, outFile);
        writeVertexBlock(&vertexBoneIndexArray, outFile);
    }
}

void Mesh::loadFromFile(OSFILE *inFile) {
    clearMesh();
    
    char tag[4];
    OSBasics::read(tag, 1, 4, inFile);
    
    if(tag[0] == 'M' && tag[1] == 'S' && tag[2] == 'H' && tag[3] == '2') {
        loadFromFileV2(inFile);
    } else {
        OSBasics::seek(inFile, 0, SEEK_SET);
        loadFromFileLegacyV1(inFile);
    }
}

void Mesh::loadFromFileV2(OSFILE *inFile) {
    
    unsigned char meshFlags;
    OSBasics::read(&meshFlags, sizeof(unsigned char), 1, inFile);
    
    indexedMesh = meshFlags & (1 << 0);
    
    char blockType;
    unsigned int blockSize;
    while(OSBasics::read(&blockType, sizeof(unsigned char), 1, inFile)) {
        OSBasics::read(&blockSize, sizeof(unsigned int), 1, inFile);
        
        switch(blockType) {
            case RenderDataArray::VERTEX_DATA_ARRAY:
                vertexPositionArray.data.resize(blockSize);
                OSBasics::read(&vertexPositionArray.data[0], sizeof(PolyRendererVertexType), blockSize, inFile);
            break;
            case RenderDataArray::TEXCOORD_DATA_ARRAY:
                vertexTexCoordArray.data.resize(blockSize);
                OSBasics::read(&vertexTexCoordArray.data[0], sizeof(PolyRendererVertexType), blockSize, inFile);
            break;
            case RenderDataArray::NORMAL_DATA_ARRAY:
                vertexNormalArray.data.resize(blockSize);
                OSBasics::read(&vertexNormalArray.data[0], sizeof(PolyRendererVertexType), blockSize, inFile);
            break;
            case RenderDataArray::COLOR_DATA_ARRAY:
                vertexColorArray.data.resize(blockSize);
                OSBasics::read(&vertexColorArray.data[0], sizeof(PolyRendererVertexType), blockSize, inFile);
            break;
            case RenderDataArray::TANGENT_DATA_ARRAY:
                vertexTangentArray.data.resize(blockSize);
                OSBasics::read(&vertexTangentArray.data[0], sizeof(PolyRendererVertexType), blockSize, inFile);
            break;
            case RenderDataArray::BONE_WEIGHT_DATA_ARRAY:
                vertexBoneWeightArray.data.resize(blockSize);
                OSBasics::read(&vertexBoneWeightArray.data[0], sizeof(PolyRendererVertexType), blockSize, inFile);
            break;
            case RenderDataArray::INDEX_DATA_ARRAY:
                indexArray.data.resize(blockSize);
                OSBasics::read(&indexArray.data[0], sizeof(PolyRendererIndexType), blockSize, inFile);
            break;
            case RenderDataArray::BONE_INDEX_DATA_ARRAY:
                vertexBoneIndexArray.data.resize(blockSize);
                OSBasics::read(&vertexBoneIndexArray.data[0], sizeof(PolyRendererVertexType), blockSize, inFile);
            break;
        }
    }
    
    if(vertexBoneIndexArray.getDataSize() > 0) {
        normalizeBoneWeights();
    }
}

void Mesh::normalizeBoneWeights() {
    
    for(int i=0; i < vertexBoneWeightArray.getDataSize()-3; i += 4) {
        Number totalWeight = vertexBoneWeightArray.data[i] + vertexBoneWeightArray.data[i+1] + vertexBoneWeightArray.data[i+2] + vertexBoneWeightArray.data[i+3];
        
        if(totalWeight != 0.0) {
            vertexBoneWeightArray.data[i] = vertexBoneWeightArray.data[i] / totalWeight;
            vertexBoneWeightArray.data[i+1] = vertexBoneWeightArray.data[i+1] / totalWeight;
            vertexBoneWeightArray.data[i+2] = vertexBoneWeightArray.data[i+2] / totalWeight;
            vertexBoneWeightArray.data[i+3] = vertexBoneWeightArray.data[i+3] / totalWeight;
        }
    }
}

void Mesh::loadFromFileLegacyV1(OSFILE *inFile) {
    
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

        vertexPositionArray.data.push_back(pos.x);
        vertexPositionArray.data.push_back(pos.y);
        vertexPositionArray.data.push_back(pos.z);
        
        if(hasNormals) {
            OSBasics::read(&nor, sizeof(Vector3_struct), 1, inFile);

            vertexNormalArray.data.push_back(nor.x);
            vertexNormalArray.data.push_back(nor.y);
            vertexNormalArray.data.push_back(nor.z);
            
            
        }
        if(hasTangents) {
            OSBasics::read(&tan, sizeof(Vector3_struct), 1, inFile);
            
            vertexTangentArray.data.push_back(tan.x);
            vertexTangentArray.data.push_back(tan.y);
            vertexTangentArray.data.push_back(tan.z);
            
        }
        
        if(hasColors) {
            OSBasics::read(&col, sizeof(Vector4_struct), 1, inFile);
            
            vertexColorArray.data.push_back(col.x);
            vertexColorArray.data.push_back(col.y);
            vertexColorArray.data.push_back(col.z);
            vertexColorArray.data.push_back(col.w);
        }
        
        if(hasUV) {
            OSBasics::read(&tex, sizeof(Vector2_struct), 1, inFile);
            vertexTexCoordArray.data.push_back(tex.x);
            vertexTexCoordArray.data.push_back(tex.y);
        }
        
        if(hasSecondaryUVs) {
            OSBasics::read(&tex, sizeof(Vector2_struct), 1, inFile);
            vertexTexCoord2Array.data.push_back(tex.x);
            vertexTexCoord2Array.data.push_back(tex.x);
        }
        
        if(hasBoneWeights) {
            unsigned int numBoneWeights;
            OSBasics::read(&numBoneWeights, sizeof(unsigned int), 1, inFile);
            
            Number totalWeight = 0;
            int numPushed = 0;
            
            for(int b=0; b < numBoneWeights; b++) {
                float weight;
                unsigned int boneID;
                OSBasics::read(&boneID, sizeof(unsigned int), 1, inFile);
                OSBasics::read(&weight, sizeof(float), 1, inFile);
                
                if(b < 4) {
                    vertexBoneWeightArray.data.push_back(weight);
                    vertexBoneIndexArray.data.push_back(boneID);
                    numPushed++;
                }
                totalWeight += weight;
            }
            
            if(numPushed < 4) {
                for(int b=numPushed; b < 4; b++) {
                    vertexBoneWeightArray.data.push_back(0.0);
                    vertexBoneIndexArray.data.push_back(0.0);
                }
            }
            
            for(int m=0; m < 4; m++) {
                vertexBoneWeightArray.data[vertexBoneWeightArray.data.size()-1-m] = vertexBoneWeightArray.data[vertexBoneWeightArray.data.size()-1-m] / totalWeight;
            }				
        }
    }
    
    if(indexedMesh) {
        unsigned int numIndices;
        OSBasics::read(&numIndices, sizeof(unsigned int), 1, inFile);
        unsigned int val;
        for(int i=0; i < numIndices; i++) {
            OSBasics::read(&val, sizeof(unsigned int), 1, inFile);
            indexArray.data.push_back(val);
        }
    }
}

Vector2 Mesh::getVertexTexCoord(unsigned int vertexOffset) {
    return Vector2(vertexTexCoordArray.data[(vertexOffset*2)], vertexTexCoordArray.data[(vertexOffset*2)+1]);
}

Vector2 Mesh::getVertexTexCoordAtIndex(unsigned int index) {
    unsigned int vertexOffset = indexArray.data[index]*2;
    return Vector2(vertexTexCoordArray.data[vertexOffset], vertexTexCoordArray.data[vertexOffset+1]);
}


Vector3 Mesh::getVertexPosition(unsigned int vertexOffset) {
    return Vector3(vertexPositionArray.data[(vertexOffset*3)], vertexPositionArray.data[(vertexOffset*3)+1], vertexPositionArray.data[(vertexOffset*3)+2]);
}

Vector3 Mesh::getVertexPositionAtIndex(unsigned int index) {
    unsigned int vertexOffset = indexArray.data[index]*3;
    return Vector3(vertexPositionArray.data[vertexOffset], vertexPositionArray.data[vertexOffset+1], vertexPositionArray.data[vertexOffset+2]);
}


void Mesh::addColor(const Color &color) {
    vertexColorArray.data.push_back(color.r);
    vertexColorArray.data.push_back(color.g);
    vertexColorArray.data.push_back(color.b);
    vertexColorArray.data.push_back(color.a);
}

void Mesh::addColor(Number r, Number g, Number b, Number a) {
    vertexColorArray.data.push_back(r);
    vertexColorArray.data.push_back(g);
    vertexColorArray.data.push_back(b);
    vertexColorArray.data.push_back(a);
}

void Mesh::addVertex(Number x, Number y, Number z) {
    vertexPositionArray.data.push_back(x);
    vertexPositionArray.data.push_back(y);
    vertexPositionArray.data.push_back(z);
}

void Mesh::addTangent(Number x, Number y, Number z) {
    vertexTangentArray.data.push_back(x);
    vertexTangentArray.data.push_back(y);
    vertexTangentArray.data.push_back(z);
}

void Mesh::addTexCoord(Number u, Number v) {
    vertexTexCoordArray.data.push_back(u);
    vertexTexCoordArray.data.push_back(v);
}

void Mesh::addTexCoord2(Number u, Number v) {
    vertexTexCoord2Array.data.push_back(u);
    vertexTexCoord2Array.data.push_back(v);
}

void Mesh::addBoneAssignments(Number b1Weight, unsigned int b1Index, Number b2Weight, unsigned int b2Index, Number b3Weight, unsigned int b3Index, Number b4Weight, unsigned int b4Index) {
 
    vertexBoneWeightArray.data.push_back(b1Weight);
    vertexBoneWeightArray.data.push_back(b2Weight);
    vertexBoneWeightArray.data.push_back(b3Weight);
    vertexBoneWeightArray.data.push_back(b4Weight);
    
    vertexBoneIndexArray.data.push_back(b1Index);
    vertexBoneIndexArray.data.push_back(b2Index);
    vertexBoneIndexArray.data.push_back(b3Index);
    vertexBoneIndexArray.data.push_back(b4Index);
}

void Mesh::setVertexAtOffset(unsigned int offset, Number x, Number y, Number z) {
    if((offset*3)+2 < vertexPositionArray.data.size()) {
        vertexPositionArray.data[(offset*3)] = x;
        vertexPositionArray.data[(offset*3)+1] = y;
        vertexPositionArray.data[(offset*3)+2] = z;
    }
}

void Mesh::addVertexWithUV(Number x, Number y, Number z, Number u, Number v) {
    addVertex(x,y,z);
    addTexCoord(u,v);
}

void Mesh::addVertexWithUVAndNormal(Number x, Number y, Number z, Number u, Number v, Number nx, Number ny, Number nz) {
    addVertexWithUV(x,y,z, u, v);
    addNormal(nx, ny, nz);
}

void Mesh::addNormal(Number nx, Number ny, Number nz) {
    vertexNormalArray.data.push_back(nx);
    vertexNormalArray.data.push_back(ny);
    vertexNormalArray.data.push_back(nz);
}

void Mesh::addNormal(const Vector3 &n) {
    vertexNormalArray.data.push_back(n.x);
    vertexNormalArray.data.push_back(n.y);
    vertexNormalArray.data.push_back(n.z);
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
}

void Mesh::createCircle(Number w, Number h, unsigned int numSegments, Number tilingValue) {
    setMeshType(Mesh::TRI_MESH);
    indexedMesh = false;

    Number lastx = 0;
    Number lasty = 0;
    Number lastv = 0;

    for (int i=0 ; i < numSegments+1; i++) {
        Number v = ((Number)i)/((Number)numSegments);
        Number pos = ((PI*2.0)/((Number)numSegments)) * i;
        Number x = sin(pos) * w * 0.5;
        Number y = cos(pos) * h * 0.5;
        
        if(i > 0) {
			addVertexWithUVAndNormal(0, 0, 0, 0.5*tilingValue, 0.5*tilingValue, 0.0, 0.0, 1.0);
			addVertexWithUVAndNormal(x, y, 0, (0.5 + (y / h*0.5))*tilingValue, (0.5 + (x / w*0.5))*tilingValue, 0.0, 0.0, 1.0);
			addVertexWithUVAndNormal(lastx, lasty, 0, (0.5 + (lasty / h*0.5))*tilingValue, (0.5 + (lastx / w*0.5))*tilingValue, 0.0, 0.0, 1.0);
        }
        lastx = x;
        lastv = v;
        lasty = y;
    }
}

Mesh *Mesh::Copy() const {
    Mesh *newMesh = new Mesh(meshType);
    newMesh->indexedMesh = indexedMesh;
    (*newMesh) = (*this);
    return newMesh;
}

void Mesh::createLineCircle(Number w, Number h, unsigned int numSegments, Number tilingValue) {
    setMeshType(Mesh::TRIFAN_MESH);
    indexedMesh = false;
    
    int step;
    if(numSegments > 0) {
        step = ceil(360.0/((Number)numSegments));
    } else {
        step = 1;
    }
    
	addVertexWithUV(cosf(0)*(w / 2), sinf(0)*(h / 2), 0, ((cosf(0)*0.5) + 0.5)*tilingValue, ((sinf(0) * 0.5) + 0.5)*tilingValue);
    addNormal(0.0, 0.0, 0.0);
    
    for (int i=0; i < 361; i+= step) {
        Number degInRad = i*TORADIANS;
        
        Number x = cos(degInRad)*(w/2);
        Number y = sin(degInRad)*(h/2);
        
		addVertexWithUV(x, y, 0, ((cos(degInRad) * 0.5) + 0.5)*tilingValue, (1.0 - ((sin(degInRad) * 0.5) + 0.5))*tilingValue);
        
        Vector3 normal(x,y, 0.0);
        normal.Normalize();
        addNormal(normal.x, normal.y, normal.z);
    }
}

void Mesh::createVPlane(Number w, Number h, Number tilingValue) {
    setMeshType(Mesh::TRI_MESH);
    indexedMesh = false;
    
    addVertexWithUVAndNormal(0 - (w/2.0f),0 - (h/2.0f), 0,0,0, 0.0, 0.0, 1.0);
    addVertexWithUVAndNormal(w - (w/2.0f), 0- (h/2.0f), 0, tilingValue, 0, 0.0, 0.0, 1.0);
    addVertexWithUVAndNormal(w- (w/2.0f), h- (h/2.0f), 0, tilingValue, tilingValue, 0.0, 0.0, 1.0);
    
    addVertexWithUVAndNormal(0 - (w/2.0f),0- (h/2.0f), 0,0,0, 0.0, 0.0, 1.0);
    addVertexWithUVAndNormal(w - (w/2.0f),h - (h/2.0f), 0, tilingValue, tilingValue, 0.0, 0.0, 1.0);
	addVertexWithUVAndNormal(0 - (w / 2.0f), h - (h / 2.0f), 0, 0, tilingValue, 0.0, 0.0, 1.0);
    
    calculateNormals();
    calculateTangents();
}	

void Mesh::createPlane(Number w, Number h, Number tilingValue) {
    setMeshType(Mesh::TRI_MESH);
    indexedMesh = false;
    
	addVertexWithUV(0 - (w / 2.0f), 0, h - (h / 2.0f), 0, 0);
	addVertexWithUV(w - (w / 2.0f), 0, h - (h / 2.0f), 1 * tilingValue, 0);
	addVertexWithUV(w - (w / 2.0f), 0, 0 - (h / 2.0f), 1 * tilingValue, 1 * tilingValue);
    
	addVertexWithUV(0 - (w / 2.0f), 0, h - (h / 2.0f), 0, 0);
	addVertexWithUV(w - (w / 2.0f), 0, 0 - (h / 2.0f), 1 * tilingValue, 1 * tilingValue);
	addVertexWithUV(0 - (w / 2.0f), 0, 0 - (h / 2.0f), 0, 1 * tilingValue);

    calculateNormals();
    calculateTangents();
}

Vector3 Mesh::recenterMesh() {
    
    // TODO: implement
    

    Vector3 positiveOffset;
    Vector3 negativeOffset;
    Vector3 finalOffset;
    
    /*
    for(int i=0; i < vertices.size(); i++) {
        positiveOffset.x = max(positiveOffset.x, vertices[i]->x);
        positiveOffset.y = max(positiveOffset.y, vertices[i]->y);
        positiveOffset.z = max(positiveOffset.z, vertices[i]->z);

        negativeOffset.x = min(negativeOffset.x, vertices[i]->x);
        negativeOffset.y = min(negativeOffset.y, vertices[i]->y);
        negativeOffset.z = min(negativeOffset.z, vertices[i]->z);
    }		
    

    
    finalOffset.x = (positiveOffset.x + negativeOffset.x)/2.0f;
    finalOffset.y = (positiveOffset.y + negativeOffset.y)/2.0f;
    finalOffset.z = (positiveOffset.z + negativeOffset.z)/2.0f;		
    
    for(int i=0; i < vertices.size(); i++) {
        vertices[i]->x = vertices[i]->x - finalOffset.x;
        vertices[i]->y = vertices[i]->y - finalOffset.y;
        vertices[i]->z = vertices[i]->z - finalOffset.z;
    }		

    */
    
    return finalOffset;		
}	

Vector3 Mesh::calculateBBox() {
    Vector3 retVec;
    
    if(vertexPositionArray.data.size() == 0) {
        return retVec;
    }
    
    for(int i=0; i < vertexPositionArray.data.size()-2; i += 3) {
		retVec.x = max(retVec.x,(Number)fabs(vertexPositionArray.data[i]));
		retVec.y = max(retVec.y,(Number)fabs(vertexPositionArray.data[i+1]));
		retVec.z = max(retVec.z,(Number)fabs(vertexPositionArray.data[i+2]));
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

void Mesh::createSphere(Number radius, int segmentsH, int segmentsW, Number tilingValue) {

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
            addVertex(v.x, v.y, v.z);
            v.Normalize();
            addNormal(v.x, v.y, v.z);
			addTexCoord((-theta / (360.f))*tilingValue, ((phi + 90.f) / 180.f)*tilingValue);
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
}

void Mesh::subdivideToRadius(Number radius, int subdivisions)
{
	typedef std::map<std::pair<int,int>, int> EdgeSet;
	for (int s = 0; s < subdivisions; s++) {
		EdgeSet dividedEdges;
		//Take a copy of the number of face indices at the BEGINNING, so we don't go on forever
		for (int i = 0, n = indexArray.data.size(); i < n; i += 3) {

			int vi0 = indexArray.data[i];
			int vi1 = indexArray.data[i+1];
			int vi2 = indexArray.data[i+2];

			Vector3 v0 = Vector3(vertexPositionArray.data[(vi0*3)], vertexPositionArray.data[(vi0*3)+1], vertexPositionArray.data[(vi0*3)+2]);
			Vector3 v1 = Vector3(vertexPositionArray.data[(vi1*3)], vertexPositionArray.data[(vi1*3)+1], vertexPositionArray.data[(vi1*3)+2]);
			Vector3 v2 = Vector3(vertexPositionArray.data[(vi2*3)], vertexPositionArray.data[(vi2*3)+1], vertexPositionArray.data[(vi2*3)+2]);

			//Midpoints
			Vector3 vm01 = (v0 + v1) * 0.5f;
			Vector3 vm12 = (v1 + v2) * 0.5f;
			Vector3 vm20 = (v2 + v0) * 0.5f;

			//Normalize so they're pushed outwards to the sphere
			vm01 = vm01 * (radius / vm01.length());
			vm12 = vm12 * (radius / vm12.length());
			vm20 = vm20 * (radius / vm20.length());

			std::pair<int,int>
				key01 = vi0 < vi1 ? std::pair<int,int>(vi0, vi1) : std::pair<int,int>(vi1, vi0),
				key12 = vi1 < vi2 ? std::pair<int,int>(vi1, vi2) : std::pair<int,int>(vi2, vi1),
				key20 = vi2 < vi0 ? std::pair<int,int>(vi2, vi0) : std::pair<int,int>(vi0, vi2);

			EdgeSet::iterator it01 = dividedEdges.find(key01);
			int vmi01;
			if (it01 != dividedEdges.end()) {
				vmi01 = it01->second;
			}
			else {
				vmi01 = vertexPositionArray.data.size()/3;
				addVertex(vm01.x, vm01.y, vm01.z);
                addTexCoord(0.0, 0.0);
				dividedEdges[key01] = vmi01;
			}
			EdgeSet::iterator it12 = dividedEdges.find(key12);
			int vmi12;
			if (it12 != dividedEdges.end()) {
				vmi12 = it12->second;
			}
			else {
				vmi12 = vertexPositionArray.data.size()/3;
				addVertex(vm12.x, vm12.y, vm12.z);
                addTexCoord(0.0, 0.0);
				dividedEdges[key12] = vmi12;
			}
			EdgeSet::iterator it20 = dividedEdges.find(key20);
			int vmi20;
			if (it20 != dividedEdges.end()) {
				vmi20 = it20->second;
			}
			else {
				vmi20 = vertexPositionArray.data.size()/3;
				addVertex(vm20.x, vm20.y, vm20.z);
                addTexCoord(0.0, 0.0);                
				dividedEdges[key20] = vmi20;
			}

			addIndexedFace(vi0, vmi01, vmi20);
			addIndexedFace(vi1, vmi12, vmi01);
			addIndexedFace(vi2, vmi20, vmi12);

			//Recycle the original face to be the new central face
			indexArray.data[i] = vmi01;
			indexArray.data[i+1] = vmi12;
			indexArray.data[i+2] = vmi20;
		}
	}
}

void Mesh::createOctosphere(Number radius, int subdivisions) {

    setMeshType(Mesh::TRI_MESH);
    
	indexedMesh = true;

	Vector3 points[6]={
		Vector3(0,0,-1),
		Vector3(0,0,1),
		Vector3(-1,0,0),
		Vector3(1,0,0),
		Vector3(0,-1,0),
		Vector3(0,1,0)
	};

	for(int i =0;i<6;i++) {
		Vector3 n = points[i];
		Vector3 v = n * radius;
		addVertex(v.x, v.y, v.z);
        addNormal(n.x, n.y, n.z);
        addTexCoord(0.0, 0.0);
	}

	addIndexedFace(0, 4, 2);
	addIndexedFace(0, 2, 5);
	addIndexedFace(0, 5, 3);
	addIndexedFace(0, 3, 4);
	addIndexedFace(1, 2, 4);
	addIndexedFace(1, 4, 3);
	addIndexedFace(1, 3, 5);
	addIndexedFace(1, 5, 2);

	subdivideToRadius(radius, subdivisions);
    
    calculateNormals();
	calculateTangents();
}

void Mesh::createIcosphere(Number radius, int subdivisions) {

    setMeshType(Mesh::TRI_MESH);
    
	const float a = 0.5257311121191336;
	const float b = 0.85065080835204;

	indexedMesh = true;

	Vector3 icosahedron_points[12]={
		Vector3(-a,  b, 0),
		Vector3( a,  b, 0),
		Vector3(-a, -b, 0),
		Vector3( a, -b, 0),
		Vector3(0, -a,  b),
		Vector3(0,  a,  b),
		Vector3(0, -a, -b),
		Vector3(0,  a, -b),
		Vector3( b, 0, -a),
		Vector3( b, 0,  a),
		Vector3(-b, 0, -a),
		Vector3(-b, 0,  a)
	};

	for(int i =0;i<12;i++) {
		Vector3 n = icosahedron_points[i];
		Vector3 v = n * radius;
		addVertex(v.x, v.y, v.z);
        addNormal(n.x, n.y, n.z);
        addTexCoord(0.0, 0.0);
	}

	addIndexedFace(0, 11, 5);
	addIndexedFace(0, 5, 1);
	addIndexedFace(0, 1, 7);
	addIndexedFace(0, 7, 10);
	addIndexedFace(0, 10, 11);
	addIndexedFace(1, 5, 9);
	addIndexedFace(5, 11, 4);
	addIndexedFace(11, 10, 2);
	addIndexedFace(10, 7, 6);
	addIndexedFace(7, 1, 8);
	addIndexedFace(3, 9, 4);
	addIndexedFace(3, 4, 2);
	addIndexedFace(3, 2, 6);
	addIndexedFace(3, 6, 8);
	addIndexedFace(3, 8, 9);
	addIndexedFace(4, 9, 5);
	addIndexedFace(2, 4, 11);
	addIndexedFace(6, 2, 10);
	addIndexedFace(8, 6, 7);
	addIndexedFace(9, 8, 1);

	subdivideToRadius(radius, subdivisions);

    calculateNormals();
	calculateTangents();
}

unsigned int Mesh::getVertexCount() {
    return vertexPositionArray.data.size()/3;
}

unsigned int Mesh::getIndexCount() {
    return indexArray.data.size();
}

void Mesh::createTorus(Number radius, Number tubeRadius, int segmentsW, int segmentsH, Number tilingValue) {

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
            
            addVertex(v.x, v.y, v.z);
			addTexCoord((-theta / (360.f))*tilingValue, ((phi / (360.f)) + 0.5)*tilingValue);
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
}

void Mesh::createCylinder(Number height, Number radius, int numSegments, bool capped, Number tilingValue) {

    setMeshType(Mesh::TRI_MESH);
    indexedMesh = true;
    
    Number lastx = 0;
    Number lastz = 0;
    Number lastv = 0;
    
    numSegments++;
    
    if(capped) {
		addVertexWithUVAndNormal(0, 0 - (height / 2.0f), 0, 0.5*tilingValue, 0.5*tilingValue, 0.0, -1.0, 0.0);
		addVertexWithUVAndNormal(0, height - (height / 2.0f), 0, 0.5*tilingValue, 0.5*tilingValue, 0.0, 1.0, 0.0);
    }
    
    for (int i=0 ; i < numSegments; i++) {
        Number v = ((Number)i)/((Number)numSegments-1);
        Number pos = ((PI*2.0)/((Number)numSegments-1)) * i;
        Number x = sin(pos);
        Number z = cos(pos);
        
		addVertexWithUVAndNormal(x*radius, 0 - (height / 2.0f), z*radius, v*tilingValue, 0, x, 0, z);
		addVertexWithUVAndNormal(x*radius, height - (height / 2.0f), z*radius, v*tilingValue, tilingValue, x, 0, z);
        
        if(capped) {
			addVertexWithUVAndNormal(x*radius, 0 - (height / 2.0f), z*radius, (0.5 + (z*0.5))*tilingValue, (0.5 + (x*0.5))*tilingValue, 0.0, -1.0, 0.0);
			addVertexWithUVAndNormal(x*radius, height - (height / 2.0f), z*radius, (0.5 + (z*0.5))*tilingValue, (0.5 + (x*0.5))*tilingValue, 0.0, 1.0, 0.0);
        }

        lastx = x;
        lastz = z;			
        lastv = v;
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
}

void Mesh::createCone(Number height, Number radius, int numSegments, Number tilingValue) {
    
    setMeshType(Mesh::TRI_MESH);
    indexedMesh = true;
    
    Number lastx = 0;
    Number lastz = 0;
    
    numSegments *= 2;
    
    if(!(numSegments % 2)) {
        numSegments++;
    }
    
	addVertexWithUVAndNormal(0, 0 - (height / 2.0f), 0, 0.5*tilingValue, 0.5*tilingValue, 0.0, -1.0, 0.0);
    
    for (int i=0 ; i < numSegments; i++) {
        Number pos = ((PI*2.0)/((Number)numSegments-1)) * i;
        Number x = sin(pos);
        Number z = cos(pos);

        if(!(i % 2)) {
			addVertexWithUVAndNormal(x*radius, 0 - (height / 2.0f), z*radius, (0.5 + (z*0.5))*tilingValue, (0.5 + (x*0.5))*tilingValue, x, 0.0, z);
			addVertexWithUVAndNormal(x*radius, 0 - (height / 2.0f), z*radius, (0.5 + (z*0.5))*tilingValue, (0.5 + (x*0.5))*tilingValue, 0.0, -1.0, 0.0);
        } else {
			addVertexWithUVAndNormal(0, height - (height / 2.0f), 0, 0.5*tilingValue, 0.5*tilingValue, 0.0, 1.0, 0.0);
        }
        
        lastx = x;
        lastz = z;

    }
    
    
    int vertexOffset = 4;
    
    for (int i=1 ; i <= (numSegments-1)/2; i++) {
        addIndexedFace(vertexOffset, vertexOffset-1, vertexOffset-3);
        addIndexedFace(vertexOffset+1, vertexOffset-2, 0);
        vertexOffset += 3;
    }
    
    
    calculateTangents();
}

void Mesh::addIndex(unsigned int index) {
    indexArray.data.push_back(index);
}

void Mesh::addIndexedFace(unsigned int i1, unsigned int i2, unsigned int i3) {
    indexArray.data.push_back(i1);
    indexArray.data.push_back(i2);
    indexArray.data.push_back(i3);
}

void Mesh::addIndexedFace(unsigned int i1, unsigned int i2) {
    indexArray.data.push_back(i1);
    indexArray.data.push_back(i2);
}

void Mesh::addIndexedFace(unsigned int i1, unsigned int i2, unsigned int i3, unsigned int i4) {
    indexArray.data.push_back(i1);
    indexArray.data.push_back(i2);
    indexArray.data.push_back(i3);
    indexArray.data.push_back(i4);
}

void Mesh::removeFace(unsigned int faceIndex) {
	unsigned int groupSize = getIndexGroupSize();
	unsigned int startOffset = faceIndex * groupSize;
	if (indexedMesh) {
		std::vector<PolyRendererIndexType>::iterator start = indexArray.data.begin() + startOffset;
		indexArray.data.erase(start, start+groupSize);
	}
	else {
		removeVertexRange(startOffset, startOffset + groupSize);
	}
}

void Mesh::removeVertexRange(unsigned int beginRemoveVertex, int vertexRemovalCount) {
    // TODO: fix
    /*
	if (!vertices.size()) return;
	unsigned int endRemoveVertex = beginRemoveVertex + vertexRemovalCount;
	vertices.erase(vertices.begin() + beginRemoveVertex, vertices.begin() + endRemoveVertex);
	if (indexedMesh) {
		unsigned int groupSize = getIndexGroupSize();
		for (unsigned int i = 0; i < indices.size(); ) {
			unsigned int faceVertexIndex = indices[i];
			//Encountered a face that references an index being removed
			if (faceVertexIndex >= beginRemoveVertex && faceVertexIndex < endRemoveVertex) {
				//Rewind to beginning of group, going to remove entire face
				unsigned int faceIndex = i/groupSize;
				i = faceIndex * groupSize;
				indices.erase(indices.begin() + i, indices.begin() + i + groupSize);
			}
			else {
				if (faceVertexIndex > beginRemoveVertex) {
					indices[i] = faceVertexIndex - vertexRemovalCount;
				}
				i++;
			}
		}
	}
     */
}

int Mesh::removeUnusedVertices() {
	int removals = 0;
        // TODO: fix
    /*
	if (indexedMesh) {
		std::vector<unsigned int> vertexMap(vertices.size());
		//Mark all used vertices first
		for (unsigned int i = 0; i < indices.size(); i++) {
			vertexMap[indices[i]] = 1;
		}
		//Create relocation map, move vertices
		unsigned int dst = 0;
		for (unsigned int src = 0; src < vertexMap.size(); src++) {
			if (vertexMap[src]) {
				vertices[dst] = vertices[src];
				vertexMap[src] = dst;
				dst++;
			}
		}
		removals = dst - vertices.size();
		vertices.resize(dst);
		//Apply map to indices
		for (unsigned int i = 0; i < indices.size(); i++) {
			indices[i] = vertexMap[indices[i]];
		}
	}
     */
	return removals;
}

void Mesh::createBox(Number w, Number d, Number h, Number tilingValue) {
    setMeshType(Mesh::TRI_MESH);
    indexedMesh = false;
    
    addVertexWithUV(w,0,h, tilingValue, tilingValue);
    addVertexWithUV(0,0,h, tilingValue, 0);
    addVertexWithUV(0,0,0,0,0);
    
    addVertexWithUV(w,0,h, tilingValue, tilingValue);
    addVertexWithUV(0,0,0,0,0);
    addVertexWithUV(w,0,0,0,tilingValue);
    
    addVertexWithUV(w,d,h, tilingValue, tilingValue);
    addVertexWithUV(w,d,0, tilingValue, 0);
    addVertexWithUV(0,d,0,0,0);
    
    addVertexWithUV(w,d,h, tilingValue, tilingValue);
    addVertexWithUV(0,d,0,0,0);
    addVertexWithUV(0,d,h,0,tilingValue);
    
    addVertexWithUV(0,d,0,0,tilingValue);
    addVertexWithUV(w,d,0, tilingValue, tilingValue);
    addVertexWithUV(w,0,0, tilingValue, 0);
    
    addVertexWithUV(0,d,0,0,tilingValue);
    addVertexWithUV(w,0,0, tilingValue, 0);
    addVertexWithUV(0,0,0,0,0);
    
    addVertexWithUV(0,0,h,0,0);
    addVertexWithUV(w,0,h, tilingValue, 0);
    addVertexWithUV(w,d,h, tilingValue, tilingValue);
    
    addVertexWithUV(0,0,h,0,0);
    addVertexWithUV(w,d,h, tilingValue, tilingValue);
    addVertexWithUV(0,d,h,0,tilingValue);
    
    addVertexWithUV(0,0,h,0,tilingValue);
    addVertexWithUV(0,d,h, tilingValue, tilingValue);
    addVertexWithUV(0,d,0, tilingValue, 0);
    
    addVertexWithUV(0,0,h,0,tilingValue);
    addVertexWithUV(0,d,0, tilingValue, 0);
    addVertexWithUV(0,0,0,0,0);
    
    addVertexWithUV(w,0,h,0,tilingValue);
    addVertexWithUV(w,0,0, tilingValue, tilingValue);
    addVertexWithUV(w,d,0, tilingValue, 0);
    
    addVertexWithUV(w,0,h,0,tilingValue);
    addVertexWithUV(w,d,0, tilingValue, 0);
    addVertexWithUV(w,d,h,0,0);
    
    for(int i=0; i < vertexPositionArray.data.size()-2; i += 3) {
        vertexPositionArray.data[i] = vertexPositionArray.data[i] - (w/2.0f);
        vertexPositionArray.data[i+1] = vertexPositionArray.data[i+1] - (d/2.0f);
        vertexPositionArray.data[i+2] = vertexPositionArray.data[i+2] - (h/2.0f);
    }
    
    calculateNormals();
    calculateTangents();
}

Vector3 Mesh::calculateFaceTangent(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, const Vector2 &texCoord1, const Vector2 &texCoord2, const Vector2 &texCoord3) {
    Vector3 tangent;
    Vector3 side0 = v1 - v2;
    Vector3 side1 = v3 - v1;
    Vector3 normal = side1.crossProduct(side0);
    normal.Normalize();
    Number deltaV0 = texCoord1.y - texCoord2.y;
    Number deltaV1 = texCoord3.y - texCoord1.y;
    tangent = side0 * deltaV1 - side1 * deltaV0;
    tangent.Normalize();
    
    Number deltaU0 = texCoord1.x - texCoord2.x;
    Number deltaU1 = texCoord3.x - texCoord1.x;
    
    Vector3 binormal = side0 * deltaU1 - side1 * deltaU0;
    binormal.Normalize();
    Vector3 tangentCross = tangent.crossProduct(binormal);
    
    if (tangentCross.dot(normal) < 0.0f) {
        tangent = tangent * -1;
    }

    return tangent;
}


void Mesh::calculateTangents() {

    vertexTangentArray.data.clear();
    
    int polySize = 3;
    if(meshType == Mesh::QUAD_MESH) {
        polySize = 4;
    }
    
    for(int i=0; i < vertexPositionArray.data.size() / 3; i++) {
        addTangent(0.0, 0.0, 0.0);
    }
    
    if(indexedMesh) {
        for(int i=0; i+polySize-1 < indexArray.data.size(); i += polySize) {
            
            Vector3 tangent = calculateFaceTangent(getVertexPositionAtIndex(i), getVertexPositionAtIndex(i+1), getVertexPositionAtIndex(i+2), getVertexTexCoordAtIndex(i), getVertexTexCoordAtIndex(i+1), getVertexTexCoordAtIndex(i+2));
            
            for(int j=0; j < polySize; j++) {
                unsigned int index= indexArray.data[i+j];
                vertexTangentArray.data[(index*3)] -= tangent.x;
                vertexTangentArray.data[(index*3)+1] -= tangent.y;
                vertexTangentArray.data[(index*3)+2] -= tangent.z;
            }
        }
    } else {
        for(int i=0; i+polySize-1 < vertexPositionArray.data.size() / 3; i += polySize) {
            Vector3 tangent = calculateFaceTangent(getVertexPosition(i), getVertexPosition(i+1), getVertexPosition(i+2), getVertexTexCoord(i), getVertexTexCoord(i+1), getVertexTexCoord(i+2));
            
            for(int j=0; j < polySize; j++) {
                vertexTangentArray.data[(i+j) * 3] = tangent.x;
                vertexTangentArray.data[((i+j) * 3) + 1] = tangent.y;
                vertexTangentArray.data[((i+j) * 3) + 2] = tangent.z;
            }
        }
    }
    
    // normalize tangents
    for(int i=0; i < vertexTangentArray.data.size()-2; i += 3) {
        Vector3 v(vertexTangentArray.data[i], vertexTangentArray.data[i+1], vertexTangentArray.data[i+2]);
        v.Normalize();
        vertexTangentArray.data[i] = v.x;
        vertexTangentArray.data[i+1] = v.y;
        vertexTangentArray.data[i+2] = v.z;
    }

}

void Mesh::calculateNormals() {

    int polySize = 3;
    if(meshType == Mesh::QUAD_MESH) {
        polySize = 4;
    }
    
    vertexNormalArray.data.clear();
    
    for(int i=0; i < vertexPositionArray.data.size()-2; i += 3) {
        addNormal(0.0, 0.0, 0.0);
    }

    if(indexedMesh) {
        for(int i=0; i+polySize-1 < indexArray.data.size(); i += polySize) {
            const Vector3 e1 = getVertexPositionAtIndex(i) - getVertexPositionAtIndex(i+1);
            const Vector3 e2 = getVertexPositionAtIndex(i+2) - getVertexPositionAtIndex(i+1);
            const Vector3 no = e1.crossProduct(e2);
            
            for(int j=0; j < polySize; j++) {
                unsigned int index= indexArray.data[i+j];
                vertexNormalArray.data[(index*3)] -= no.x;
                vertexNormalArray.data[(index*3)+1] -= no.y;
                vertexNormalArray.data[(index*3)+2] -= no.z;
            }
        }
    } else {
        for(int i=0; i+polySize-1 < vertexPositionArray.data.size() / 3; i += polySize) {
            const Vector3 e1 = getVertexPosition(i) - getVertexPosition(i+1);
            const Vector3 e2 = getVertexPosition(i+2) - getVertexPosition(i+1);
            const Vector3 no = e1.crossProduct(e2);
            
            for(int j=0; j < polySize; j++) {
                vertexNormalArray.data[(i+j) * 3] = -no.x;
                vertexNormalArray.data[((i+j) * 3) + 1] = -no.y;
                vertexNormalArray.data[((i+j) * 3) + 2] = -no.z;
            }
        }
    }
    
    // normalize normals
    for(int i=0; i < vertexNormalArray.data.size()-2; i += 3) {
        Vector3 v(vertexNormalArray.data[i], vertexNormalArray.data[i+1], vertexNormalArray.data[i+2]);
        v.Normalize();
        vertexNormalArray.data[i] = v.x;
        vertexNormalArray.data[i+1] = v.y;
        vertexNormalArray.data[i+2] = v.z;
    }
}

void Mesh::saveAsOBJ(const String fileName) {
	FILE *f = fopen(fileName.c_str(), "w");
    
	if (!f) {
		return;
	}
    
	char buffer[256];

    if(vertexPositionArray.data.size() > 2) {
        for(int i=0; i < vertexPositionArray.data.size()-2; i += 3) {
            sprintf(buffer, "v %f %f %f\n", vertexPositionArray.data[i], vertexPositionArray.data[i+1], vertexPositionArray.data[i+2]);
            fputs(buffer, f);
        }
    }
    
    if(vertexTexCoordArray.data.size() > 1) {
        for(int i=0; i < vertexTexCoordArray.data.size()-1; i += 2) {
            sprintf(buffer, "vt %f %f\n", vertexTexCoordArray.data[i], vertexTexCoordArray.data[i+1]);
            fputs(buffer, f);
        }
    }

    if(vertexNormalArray.data.size() > 2) {
        for(int i=0; i < vertexNormalArray.data.size()-2; i += 3) {
            sprintf(buffer, "vn %f %f %f\n", vertexNormalArray.data[i], vertexNormalArray.data[i+1], vertexNormalArray.data[i+2]);
            fputs(buffer, f);
        }
    }
    
    if(indexArray.data.size() > 2) {
        for(int i=0; i < indexArray.data.size()-2; i += 3) {
            sprintf(buffer, "f %d %d %d\n", indexArray.data[i]+1, indexArray.data[i+1]+1, indexArray.data[i+2]+1);
            fputs(buffer, f);
        }
    }
    
	fclose(f);
}

int Mesh::getMeshType() {
    return meshType;
}

void Mesh::setMeshType(int newType) {
    meshType = newType;
}
