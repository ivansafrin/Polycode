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

#include "PolyGLHeaders.h"
#include "PolyGLVertexBuffer.h"

#if defined(__APPLE__) && defined(__MACH__)

#else
	#include "malloc.h"
#endif

using namespace Polycode;

#ifdef _WINDOWS
// ARB_vertex_buffer_object
extern PFNGLBINDBUFFERARBPROC glBindBufferARB;
extern PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;
extern PFNGLGENBUFFERSARBPROC glGenBuffersARB;
extern PFNGLISBUFFERARBPROC glIsBufferARB;
extern PFNGLBUFFERDATAARBPROC glBufferDataARB;
extern PFNGLBUFFERSUBDATAARBPROC glBufferSubDataARB;
extern PFNGLGETBUFFERSUBDATAARBPROC glGetBufferSubDataARB;
extern PFNGLMAPBUFFERARBPROC glMapBufferARB;
extern PFNGLUNMAPBUFFERARBPROC glUnmapBufferARB;
extern PFNGLGETBUFFERPARAMETERIVARBPROC glGetBufferParameterivARB;
extern PFNGLGETBUFFERPOINTERVARBPROC glGetBufferPointervARB;
#endif

OpenGLVertexBuffer::OpenGLVertexBuffer(Mesh *mesh) : VertexBuffer() {
	
    vertexBufferID = -1;
    texCoordBufferID = -1;
    normalBufferID = -1;
    colorBufferID = -1;
    tangentBufferID = -1;
    indexBufferID = -1;
    boneWeightBufferID = -1;
    boneIndexBufferID = -1;
    
    
	meshType = mesh->getMeshType();
    vertexCount = mesh->vertexPositionArray.getDataSize() / 3;

	glGenBuffersARB(1, &vertexBufferID);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vertexBufferID);
    
    glBufferDataARB(GL_ARRAY_BUFFER_ARB, mesh->vertexPositionArray.getDataSize() * sizeof(PolyRendererVertexType), mesh->vertexPositionArray.getArrayData(), GL_STATIC_DRAW_ARB);

    
    if(mesh->vertexTexCoordArray.getDataSize() == vertexCount * 2) {
        glGenBuffersARB(1, &texCoordBufferID);
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, texCoordBufferID);
            
        glBufferDataARB(GL_ARRAY_BUFFER_ARB,  mesh->vertexTexCoordArray.getDataSize() * sizeof(PolyRendererVertexType), mesh->vertexTexCoordArray.getArrayData(), GL_STATIC_DRAW_ARB);
    }
    
    if(mesh->vertexNormalArray.getDataSize() == vertexCount * 3) {
        glGenBuffersARB(1, &normalBufferID);
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, normalBufferID);
        glBufferDataARB(GL_ARRAY_BUFFER_ARB,  mesh->vertexNormalArray.getDataSize() * sizeof(PolyRendererVertexType), mesh->vertexNormalArray.getArrayData(), GL_STATIC_DRAW_ARB);
    }
    
    if(mesh->vertexTangentArray.getDataSize() == vertexCount * 3) {
        glGenBuffersARB(1, &tangentBufferID);
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, tangentBufferID);
        
        glBufferDataARB(GL_ARRAY_BUFFER_ARB,  mesh->vertexTangentArray.getDataSize() * sizeof(PolyRendererVertexType), mesh->vertexTangentArray.getArrayData(), GL_STATIC_DRAW_ARB);
    }
    
    if(mesh->vertexBoneWeightArray.getDataSize() == vertexCount * 4) {
        glGenBuffersARB(1, &boneWeightBufferID);
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, boneWeightBufferID);
        
        glBufferDataARB(GL_ARRAY_BUFFER_ARB,  mesh->vertexBoneWeightArray.getDataSize() * sizeof(PolyRendererVertexType), mesh->vertexBoneWeightArray.getArrayData(), GL_STATIC_DRAW_ARB);
    }
    
    if(mesh->vertexBoneIndexArray.getDataSize() == vertexCount * 4) {
        glGenBuffersARB(1, &boneIndexBufferID);
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, boneIndexBufferID);
        
        glBufferDataARB(GL_ARRAY_BUFFER_ARB,  mesh->vertexBoneIndexArray.getDataSize() * sizeof(PolyRendererVertexType), mesh->vertexBoneIndexArray.getArrayData(), GL_STATIC_DRAW_ARB);
    }
    
    if(mesh->vertexColorArray.getDataSize() == vertexCount * 4) {
        glGenBuffersARB(1, &colorBufferID);
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, colorBufferID);
            
        glBufferDataARB(GL_ARRAY_BUFFER_ARB,  mesh->vertexColorArray.getDataSize() * sizeof(PolyRendererVertexType), mesh->vertexColorArray.getArrayData(), GL_STATIC_DRAW_ARB);
    }
    
    if(mesh->indexedMesh && mesh->indexArray.getDataSize() > 0) {
        glGenBuffersARB(1, &indexBufferID);
        glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, indexBufferID);
        glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB,  mesh->indexArray.getDataSize() * sizeof(PolyRendererIndexType), mesh->indexArray.getArrayData(), GL_STATIC_DRAW_ARB);
        indexCount = mesh->indexArray.getDataSize();
    }
    
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() {
	glDeleteBuffersARB(1, &vertexBufferID);
	glDeleteBuffersARB(1, &texCoordBufferID);
	glDeleteBuffersARB(1, &normalBufferID);
	glDeleteBuffersARB(1, &colorBufferID);
	glDeleteBuffersARB(1, &indexBufferID);
	glDeleteBuffersARB(1, &boneWeightBufferID);
	glDeleteBuffersARB(1, &boneIndexBufferID);
}

GLuint OpenGLVertexBuffer::getBoneWeightBufferID() {
    return boneWeightBufferID;
}

GLuint OpenGLVertexBuffer::getBoneIndexBufferID() {
    return boneIndexBufferID;
}

GLuint OpenGLVertexBuffer::getColorBufferID() {
	return colorBufferID;
}

GLuint OpenGLVertexBuffer::getNormalBufferID() {
	return normalBufferID;
}

GLuint OpenGLVertexBuffer::getTextCoordBufferID() {
	return texCoordBufferID;
}

GLuint OpenGLVertexBuffer::getVertexBufferID() {
	return vertexBufferID;
}

GLuint OpenGLVertexBuffer::getTangentBufferID() {
	return tangentBufferID;
}

GLuint OpenGLVertexBuffer::getIndexBufferID() {
    return indexBufferID;
}
