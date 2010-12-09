/*
 *  GLVertexBuffer.h
 *  Poly
 *
 *  Created by Ivan Safrin on 9/13/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#ifdef _WINDOWS
#include <windows.h>
#endif
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolyMesh.h"
#include "PolyGLRenderer.h"

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/glu.h>	
#else
#include <GL/gl.h>	
#include <GL/glu.h>	
#endif


namespace Polycode {
	
	class _PolyExport OpenGLVertexBuffer : public VertexBuffer {
	public:
		
		OpenGLVertexBuffer(Mesh *mesh);
		virtual ~OpenGLVertexBuffer();
		
		GLuint getVertexBufferID();		
		GLuint getTextCoordBufferID();	
		GLuint getNormalBufferID();
		GLuint getColorBufferID();
		
	private:
		
		GLuint vertexBufferID;
		GLuint texCoordBufferID;
		GLuint normalBufferID;
		GLuint colorBufferID;		
	};
	
}