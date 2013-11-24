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
	glGenBuffersARB(1, &vertexBufferID);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vertexBufferID);
	
	meshType = mesh->getMeshType();
	
	long bufferSize = 0;
	long newBufferSize = 0;		
	GLfloat *buffer = (GLfloat*)malloc(1);	
	
	vertexCount = 0;
	for(int i=0; i < mesh->getVertexCount(); i++) {
        vertexCount++;
        newBufferSize = bufferSize + 3;
        buffer = (GLfloat*)realloc(buffer, newBufferSize * sizeof(GLfloat));			
        buffer[bufferSize+0] = mesh->getVertex(i)->x;
        buffer[bufferSize+1] = mesh->getVertex(i)->y;
        buffer[bufferSize+2] = mesh->getVertex(i)->z;
        bufferSize = newBufferSize;
	}
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, bufferSize*sizeof(GLfloat), buffer, GL_STATIC_DRAW_ARB);	
	free(buffer);

	glGenBuffersARB(1, &texCoordBufferID);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, texCoordBufferID);
	
	bufferSize = 0;	
	newBufferSize = 0;		
	buffer = (GLfloat*)malloc(1);	
	
	for(int i=0; i < mesh->getVertexCount(); i++) {
        newBufferSize = bufferSize + 2;
        buffer = (GLfloat*)realloc(buffer, newBufferSize * sizeof(GLfloat));		
        buffer[bufferSize+0] = mesh->getVertex(i)->getTexCoord().x;
        buffer[bufferSize+1] = mesh->getVertex(i)->getTexCoord().y;
        bufferSize = newBufferSize;
	}
	
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, bufferSize*sizeof(GLfloat), buffer, GL_STATIC_DRAW_ARB);	
	free(buffer);
	
	glGenBuffersARB(1, &normalBufferID);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, normalBufferID);
	
	bufferSize = 0;
	newBufferSize = 0;		
	buffer = (GLfloat*)malloc(1);	
	
	for(int i=0; i < mesh->getVertexCount(); i++) {
        newBufferSize = bufferSize + 3;
        buffer = (GLfloat*)realloc(buffer, newBufferSize * sizeof(GLfloat));
        buffer[bufferSize+0] = mesh->getVertex(i)->normal.x;
        buffer[bufferSize+1] = mesh->getVertex(i)->normal.y;
        buffer[bufferSize+2] = mesh->getVertex(i)->normal.z;
        bufferSize = newBufferSize;
	}
	
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, bufferSize*sizeof(GLfloat), buffer, GL_STATIC_DRAW_ARB);	
	free(buffer);	

	glGenBuffersARB(1, &tangentBufferID);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, tangentBufferID);
	
	bufferSize = 0;
	newBufferSize = 0;		
	buffer = (GLfloat*)malloc(1);	
	
	for(int i=0; i < mesh->getVertexCount(); i++) {
        newBufferSize = bufferSize + 3;
        buffer = (GLfloat*)realloc(buffer, newBufferSize * sizeof(GLfloat));		
        buffer[bufferSize+0] = mesh->getVertex(i)->tangent.x;
        buffer[bufferSize+1] = mesh->getVertex(i)->tangent.y;
        buffer[bufferSize+2] = mesh->getVertex(i)->tangent.z;
        bufferSize = newBufferSize;
	}
	
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, bufferSize*sizeof(GLfloat), buffer, GL_STATIC_DRAW_ARB);	
	free(buffer);	
	
	glGenBuffersARB(1, &colorBufferID);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, colorBufferID);
	
	bufferSize = 0;
	newBufferSize = 0;		
	buffer = (GLfloat*)malloc(1);	
	
	for(int i=0; i < mesh->getVertexCount(); i++) {
        newBufferSize = bufferSize + 4;
        buffer = (GLfloat*)realloc(buffer, newBufferSize * sizeof(GLfloat));
        buffer[bufferSize+0] = mesh->getVertex(i)->vertexColor.r;
        buffer[bufferSize+1] = mesh->getVertex(i)->vertexColor.g;
        buffer[bufferSize+2] = mesh->getVertex(i)->vertexColor.b;
        buffer[bufferSize+3] = mesh->getVertex(i)->vertexColor.a;
        bufferSize = newBufferSize;
	}
	
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, bufferSize*sizeof(GLfloat), buffer, GL_STATIC_DRAW_ARB);	
	free(buffer);	
	
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() {
	glDeleteBuffersARB(1, &vertexBufferID);
	glDeleteBuffersARB(1, &texCoordBufferID);
	glDeleteBuffersARB(1, &normalBufferID);
	glDeleteBuffersARB(1, &colorBufferID);	
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
