/*
 *  GLVertexBuffer.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 9/13/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolyGLVertexBuffer.h"

using namespace Polycode;

OpenGLVertexBuffer::OpenGLVertexBuffer(Mesh *mesh) : VertexBuffer() {
	if(mesh->getMeshType() == Mesh::QUAD_MESH) {
		verticesPerFace = 4;		
	} else {
		verticesPerFace = 3;				
	}
	meshType = mesh->getMeshType();
	
	glGenBuffersARB(1, &vertexBufferID);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vertexBufferID);
	
	long bufferSize = 0;
	long newBufferSize = 0;		
	GLfloat *buffer = (GLfloat*)malloc(1);	
	
	vertexCount = 0;
	for(int i=0; i < mesh->getPolygonCount(); i++) {
		for(int j=0; j < mesh->getPolygon(i)->getVertexCount(); j++) {
			vertexCount++;			
			newBufferSize = bufferSize + 3;
			buffer = (GLfloat*)realloc(buffer, newBufferSize * sizeof(GLfloat));			
			buffer[bufferSize+0] = mesh->getPolygon(i)->getVertex(j)->x;
			buffer[bufferSize+1] = mesh->getPolygon(i)->getVertex(j)->y;
			buffer[bufferSize+2] = mesh->getPolygon(i)->getVertex(j)->z;			
			bufferSize = newBufferSize;	
		}		   
	}
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, bufferSize*sizeof(GLfloat), buffer, GL_STATIC_DRAW_ARB);	
	free(buffer);
	

	glGenBuffersARB(1, &texCoordBufferID);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, texCoordBufferID);
	
	bufferSize = 0;	
	newBufferSize = 0;		
	buffer = (GLfloat*)malloc(1);	
	
	for(int i=0; i < mesh->getPolygonCount(); i++) {
		for(int j=0; j < mesh->getPolygon(i)->getVertexCount(); j++) {
			newBufferSize = bufferSize + 2;			
			buffer = (GLfloat*)realloc(buffer, newBufferSize * sizeof(GLfloat));		
			if(mesh->getPolygon(i)->usesFaceUV()) {
				buffer[bufferSize+0] = mesh->getPolygon(i)->getTexCoord(j).x;
				buffer[bufferSize+1] = mesh->getPolygon(i)->getTexCoord(j).y;
			} else {
				buffer[bufferSize+0] = mesh->getPolygon(i)->getVertex(j)->getTexCoord().x;
				buffer[bufferSize+1] = mesh->getPolygon(i)->getVertex(j)->getTexCoord().y;
			}
			bufferSize = newBufferSize;					
		}		   
	}
	
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, bufferSize*sizeof(GLfloat), buffer, GL_STATIC_DRAW_ARB);	
	free(buffer);
	
	
	glGenBuffersARB(1, &normalBufferID);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, normalBufferID);
	
	bufferSize = 0;
	newBufferSize = 0;		
	buffer = (GLfloat*)malloc(1);	
	
	for(int i=0; i < mesh->getPolygonCount(); i++) {
		for(int j=0; j < mesh->getPolygon(i)->getVertexCount(); j++) {
			newBufferSize = bufferSize + 3;			
			buffer = (GLfloat*)realloc(buffer, newBufferSize * sizeof(GLfloat));		
			if(mesh->getPolygon(i)->useVertexNormals) {
				buffer[bufferSize+0] = mesh->getPolygon(i)->getVertex(j)->normal.x;
				buffer[bufferSize+1] = mesh->getPolygon(i)->getVertex(j)->normal.y;
				buffer[bufferSize+2] = mesh->getPolygon(i)->getVertex(j)->normal.z;				
			} else {
				buffer[bufferSize+0] = mesh->getPolygon(i)->getFaceNormal().x;
				buffer[bufferSize+1] = mesh->getPolygon(i)->getFaceNormal().y;
				buffer[bufferSize+2] = mesh->getPolygon(i)->getFaceNormal().z;
			}
			bufferSize = newBufferSize;					
		}		   
	}
	
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, bufferSize*sizeof(GLfloat), buffer, GL_STATIC_DRAW_ARB);	
	free(buffer);	
		
	
	glGenBuffersARB(1, &colorBufferID);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, colorBufferID);
	
	bufferSize = 0;
	newBufferSize = 0;		
	buffer = (GLfloat*)malloc(1);	
	
	for(int i=0; i < mesh->getPolygonCount(); i++) {
		for(int j=0; j < mesh->getPolygon(i)->getVertexCount(); j++) {
			newBufferSize = bufferSize + 4;			
			buffer = (GLfloat*)realloc(buffer, newBufferSize * sizeof(GLfloat));
			buffer[bufferSize+0] = mesh->getPolygon(i)->getVertex(j)->vertexColor.r;
			buffer[bufferSize+1] = mesh->getPolygon(i)->getVertex(j)->vertexColor.g;
			buffer[bufferSize+2] = mesh->getPolygon(i)->getVertex(j)->vertexColor.b;
			buffer[bufferSize+3] = mesh->getPolygon(i)->getVertex(j)->vertexColor.a;			
			bufferSize = newBufferSize;					
		}		   
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