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

#include "PolyGLRenderer.h"

#ifdef _WINDOWS


PFNGLACTIVETEXTUREPROC   glActiveTexture;
PFNGLMULTITEXCOORD2FPROC glMultiTexCoord2f;
PFNGLMULTITEXCOORD3FPROC glMultiTexCoord3f;


// ARB_vertex_buffer_object
PFNGLBINDBUFFERARBPROC glBindBufferARB;
PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;
PFNGLGENBUFFERSARBPROC glGenBuffersARB;
PFNGLISBUFFERARBPROC glIsBufferARB;
PFNGLBUFFERDATAARBPROC glBufferDataARB;
PFNGLBUFFERSUBDATAARBPROC glBufferSubDataARB;
PFNGLGETBUFFERSUBDATAARBPROC glGetBufferSubDataARB;
PFNGLMAPBUFFERARBPROC glMapBufferARB;
PFNGLUNMAPBUFFERARBPROC glUnmapBufferARB;
PFNGLGETBUFFERPARAMETERIVARBPROC glGetBufferParameterivARB;
PFNGLGETBUFFERPOINTERVARBPROC glGetBufferPointervARB;

// GL_EXT_framebuffer_object
PFNGLISRENDERBUFFEREXTPROC glIsRenderbufferEXT;
PFNGLBINDRENDERBUFFEREXTPROC glBindRenderbufferEXT;
PFNGLDELETERENDERBUFFERSEXTPROC glDeleteRenderbuffersEXT;
PFNGLGENRENDERBUFFERSEXTPROC glGenRenderbuffersEXT;
PFNGLRENDERBUFFERSTORAGEEXTPROC glRenderbufferStorageEXT;
PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC glGetRenderbufferParameterivEXT;
PFNGLISFRAMEBUFFEREXTPROC glIsFramebufferEXT;
PFNGLBINDFRAMEBUFFEREXTPROC glBindFramebufferEXT;
PFNGLDELETEFRAMEBUFFERSEXTPROC glDeleteFramebuffersEXT;
PFNGLGENFRAMEBUFFERSEXTPROC glGenFramebuffersEXT;
PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC glCheckFramebufferStatusEXT;
PFNGLFRAMEBUFFERTEXTURE1DEXTPROC glFramebufferTexture1DEXT;
PFNGLFRAMEBUFFERTEXTURE2DEXTPROC glFramebufferTexture2DEXT;
PFNGLFRAMEBUFFERTEXTURE3DEXTPROC glFramebufferTexture3DEXT;
PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC glFramebufferRenderbufferEXT;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC glGetFramebufferAttachmentParameterivEXT;
PFNGLGENERATEMIPMAPEXTPROC glGenerateMipmapEXT;

#endif
using namespace Polycode;

OpenGLRenderer::OpenGLRenderer() : Renderer() {

	nearPlane = 0.1f;
	farPlane = 100.0f;
	verticesToDraw = 0;
}

void OpenGLRenderer::setClippingPlanes(Number nearPlane_, Number farPlane_) {
	nearPlane = nearPlane_;
	farPlane = farPlane_;
	Resize(xRes,yRes);
}

void OpenGLRenderer::initOSSpecific(){
		
#ifdef _WINDOWS
	glActiveTexture   = (PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture");
	glMultiTexCoord2f = (PFNGLMULTITEXCOORD2FPROC)wglGetProcAddress("glMultiTexCoord2f");
	glMultiTexCoord3f = (PFNGLMULTITEXCOORD3FPROC)wglGetProcAddress("glMultiTexCoord3f");

   // ARB_vertex_buffer_object
        glBindBufferARB = (PFNGLBINDBUFFERARBPROC)wglGetProcAddress("glBindBufferARB");
        glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC)wglGetProcAddress("glDeleteBuffersARB");
        glGenBuffersARB = (PFNGLGENBUFFERSARBPROC)wglGetProcAddress("glGenBuffersARB");
        glIsBufferARB = (PFNGLISBUFFERARBPROC)wglGetProcAddress("glIsBufferARB");
        glBufferDataARB = (PFNGLBUFFERDATAARBPROC)wglGetProcAddress("glBufferDataARB");
        glBufferSubDataARB = (PFNGLBUFFERSUBDATAARBPROC)wglGetProcAddress("glBufferSubDataARB");
        glGetBufferSubDataARB = (PFNGLGETBUFFERSUBDATAARBPROC)wglGetProcAddress("glGetBufferSubDataARB");
        glMapBufferARB = (PFNGLMAPBUFFERARBPROC)wglGetProcAddress("glMapBufferARB");
        glUnmapBufferARB = (PFNGLUNMAPBUFFERARBPROC)wglGetProcAddress("glUnmapBufferARB");
        glGetBufferParameterivARB = (PFNGLGETBUFFERPARAMETERIVARBPROC)wglGetProcAddress("glGetBufferParameterivARB");
        glGetBufferPointervARB = (PFNGLGETBUFFERPOINTERVARBPROC)wglGetProcAddress("glGetBufferPointervARB");

        glIsRenderbufferEXT = (PFNGLISRENDERBUFFEREXTPROC)wglGetProcAddress("glIsRenderbufferEXT");
        glBindRenderbufferEXT = (PFNGLBINDRENDERBUFFEREXTPROC)wglGetProcAddress("glBindRenderbufferEXT");
        glDeleteRenderbuffersEXT = (PFNGLDELETERENDERBUFFERSEXTPROC)wglGetProcAddress("glDeleteRenderbuffersEXT");
        glGenRenderbuffersEXT = (PFNGLGENRENDERBUFFERSEXTPROC)wglGetProcAddress("glGenRenderbuffersEXT");
        glRenderbufferStorageEXT = (PFNGLRENDERBUFFERSTORAGEEXTPROC)wglGetProcAddress("glRenderbufferStorageEXT");
        glGetRenderbufferParameterivEXT = (PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC)wglGetProcAddress("glGetRenderbufferParameterivEXT");
        glIsFramebufferEXT = (PFNGLISFRAMEBUFFEREXTPROC)wglGetProcAddress("glIsFramebufferEXT");
        glBindFramebufferEXT = (PFNGLBINDFRAMEBUFFEREXTPROC)wglGetProcAddress("glBindFramebufferEXT");
        glDeleteFramebuffersEXT = (PFNGLDELETEFRAMEBUFFERSEXTPROC)wglGetProcAddress("glDeleteFramebuffersEXT");
        glGenFramebuffersEXT = (PFNGLGENFRAMEBUFFERSEXTPROC)wglGetProcAddress("glGenFramebuffersEXT");
        glCheckFramebufferStatusEXT = (PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC)wglGetProcAddress("glCheckFramebufferStatusEXT");
        glFramebufferTexture1DEXT = (PFNGLFRAMEBUFFERTEXTURE1DEXTPROC)wglGetProcAddress("glFramebufferTexture1DEXT");
        glFramebufferTexture2DEXT = (PFNGLFRAMEBUFFERTEXTURE2DEXTPROC)wglGetProcAddress("glFramebufferTexture2DEXT");
        glFramebufferTexture3DEXT = (PFNGLFRAMEBUFFERTEXTURE3DEXTPROC)wglGetProcAddress("glFramebufferTexture3DEXT");
        glFramebufferRenderbufferEXT = (PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC)wglGetProcAddress("glFramebufferRenderbufferEXT");
        glGetFramebufferAttachmentParameterivEXT = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC)wglGetProcAddress("glGetFramebufferAttachmentParameterivEXT");
        glGenerateMipmapEXT = (PFNGLGENERATEMIPMAPEXTPROC)wglGetProcAddress("glGenerateMipmapEXT");

#endif
}

void OpenGLRenderer::Resize(int xRes, int yRes) {
	this->xRes = xRes;
	this->yRes = yRes;
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	glClearDepth(1.0f);
	
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective(fov,(GLfloat)xRes/(GLfloat)yRes,nearPlane,farPlane);
	glViewport(0, 0, xRes, yRes);
	glScissor(0, 0, xRes, yRes);
	
	glMatrixMode(GL_MODELVIEW);
	glLineWidth(1);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glShadeModel(GL_SMOOTH);
	glDepthFunc( GL_LEQUAL );
	
	glEnable(GL_DEPTH_TEST);
	
	glLineWidth(1.0f);
	
//	glEnable(GL_LINE_SMOOTH);
	
	GLint numBuffers;
	glGetIntegerv(GL_MAX_DRAW_BUFFERS, &numBuffers);
//	Logger::log("MAX_DRAW_BUFFERS: %d \n", numBuffers);
	
}

void OpenGLRenderer::setDepthFunction(int depthFunction) {
	switch(depthFunction) {
		case DEPTH_FUNCTION_LEQUAL:
			glDepthFunc(GL_LEQUAL);
		break;
		case DEPTH_FUNCTION_GREATER:
			glDepthFunc(GL_GREATER);			
		break;
	}
}

void OpenGLRenderer::enableAlphaTest(bool val) {
	if(val) {
		glAlphaFunc ( GL_GREATER, 0.01) ;
		glEnable ( GL_ALPHA_TEST ) ;		
	} else {
		glDisable( GL_ALPHA_TEST ) ;
	}
}

void OpenGLRenderer::setLineSmooth(bool val) {
	if(val)
		glEnable(GL_LINE_SMOOTH);
	else
		glDisable(GL_LINE_SMOOTH);
}

void OpenGLRenderer::setFOV(Number fov) {
	this->fov = fov;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov,(GLfloat)xRes/(GLfloat)yRes,nearPlane,farPlane);	
	glViewport(0, 0, xRes, yRes);
	glScissor(0, 0, xRes, yRes);
	glMatrixMode(GL_MODELVIEW);	
}

void OpenGLRenderer::setViewportSize(int w, int h, Number fov) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov,(GLfloat)w/(GLfloat)h,nearPlane,farPlane);
	glViewport(0, 0, w, h);
	glScissor(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
}

Vector3 OpenGLRenderer::Unproject(Number x, Number y) {
	Vector3 coords;
	GLfloat wx, wy, wz;
	GLdouble cx, cy, cz;
	
	GLdouble mv[16];
	glGetDoublev( GL_MODELVIEW_MATRIX, mv );
	
	GLdouble proj[16];
	glGetDoublev( GL_PROJECTION_MATRIX, proj );
	
	GLint vp[4];
	glGetIntegerv( GL_VIEWPORT, vp );
	
	wx = ( Number ) x;
	wy = ( Number ) vp[3] - ( Number ) y;
	glReadPixels( x, wy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &wz );
	
	gluUnProject( wx, wy, wz, mv, proj, vp, &cx, &cy, &cz );
	
	coords = Vector3( cx, cy, cz );
	
	return coords;
	
}

Vector3 OpenGLRenderer::projectRayFrom2DCoordinate(Number x, Number y) {
	GLdouble nearPlane[3],farPlane[3];
	
	GLdouble mv[16];
	Matrix4 camInverse = cameraMatrix.inverse();	
	Matrix4 cmv;
	cmv.identity();
	cmv = cmv * camInverse;
	
	for(int i=0; i < 16; i++) {
		mv[i] = cmv.ml[i];
	}
	
	GLint vp[4];
	glGetIntegerv( GL_VIEWPORT, vp );
	
	gluUnProject(x, yRes - y, 0.0, mv, sceneProjectionMatrix, vp,  &nearPlane[0], &nearPlane[1], &nearPlane[2]);
	gluUnProject(x, yRes - y, 1.0, mv, sceneProjectionMatrix, vp,  &farPlane[0], &farPlane[1], &farPlane[2]);
	
	Vector3 nearVec(nearPlane[0], nearPlane[1], nearPlane[2]);
	Vector3 farVec(farPlane[0], farPlane[1], farPlane[2]);
		
	Vector3 dirVec = (farVec) - (nearVec);	
	dirVec.Normalize();
	
	return dirVec;
}

bool OpenGLRenderer::test2DCoordinate(Number x, Number y, Polycode::Polygon *poly, const Matrix4 &matrix, bool billboardMode) {
	GLdouble nearPlane[3],farPlane[3];
	
	GLdouble mv[16];
	Matrix4 camInverse = cameraMatrix.inverse();	
	Matrix4 cmv;
	cmv.identity();
	cmv = cmv * camInverse;
	
	for(int i=0; i < 16; i++) {
		mv[i] = cmv.ml[i];
	}
	
	GLint vp[4];
	glGetIntegerv( GL_VIEWPORT, vp );
	
	gluUnProject(x, yRes - y, 0.0, mv, sceneProjectionMatrix, vp,  &nearPlane[0], &nearPlane[1], &nearPlane[2]);
	gluUnProject(x, yRes - y, 1.0, mv, sceneProjectionMatrix, vp,  &farPlane[0], &farPlane[1], &farPlane[2]);
	
	Vector3 nearVec(nearPlane[0], nearPlane[1], nearPlane[2]);
	Vector3 farVec(farPlane[0], farPlane[1], farPlane[2]);
		
	Vector3 dirVec = farVec - nearVec;	
	dirVec.Normalize();
	
	Vector3 hitPoint;
	
	Matrix4 fullMatrix = matrix;
	
	if(poly->getVertexCount() == 3) {
		return rayTriangleIntersect(Vector3(0,0,0), dirVec, fullMatrix * (*poly->getVertex(0)), fullMatrix  * (*poly->getVertex(1)), fullMatrix *  (*poly->getVertex(2)), &hitPoint);
	} else if(poly->getVertexCount() == 4) {
		return (rayTriangleIntersect(Vector3(0,0,0), dirVec, fullMatrix * (*poly->getVertex(2)), fullMatrix  * (*poly->getVertex(1)), fullMatrix *  (*poly->getVertex(0)), &hitPoint) ||
				rayTriangleIntersect(Vector3(0,0,0), dirVec, fullMatrix * (*poly->getVertex(0)), fullMatrix  * (*poly->getVertex(3)), fullMatrix *  (*poly->getVertex(2)), &hitPoint));
	} else {
		return false;
	}
}

void OpenGLRenderer::enableDepthWrite(bool val) {
	if(val)
		glDepthMask(GL_TRUE);
	else
		glDepthMask(GL_FALSE);	
}

void OpenGLRenderer::enableDepthTest(bool val) {
	if(val)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);	
}

void OpenGLRenderer::setModelviewMatrix(Matrix4 m) {
	glLoadMatrixd(m.ml);
}

void OpenGLRenderer::multModelviewMatrix(Matrix4 m) {
//	glMatrixMode(GL_MODELVIEW);
	glMultMatrixd(m.ml);
}

void OpenGLRenderer::enableLighting(bool enable) {
	lightingEnabled = enable;
}

void OpenGLRenderer::setLineSize(Number lineSize) {
	glLineWidth(lineSize);
}

void OpenGLRenderer::createVertexBufferForMesh(Mesh *mesh) {
	OpenGLVertexBuffer *buffer = new OpenGLVertexBuffer(mesh);
	mesh->setVertexBuffer(buffer);
}

void OpenGLRenderer::drawVertexBuffer(VertexBuffer *buffer) {
	OpenGLVertexBuffer *glVertexBuffer = (OpenGLVertexBuffer*)buffer;

	glEnableClientState(GL_VERTEX_ARRAY);		
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);	
//	glEnableClientState(GL_COLOR_ARRAY);		
		
//	glBindBufferARB( GL_ARRAY_BUFFER_ARB, glVertexBuffer->getColorBufferID());
//	glTexCoordPointer( 4, GL_FLOAT, 0, (char *) NULL );	
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, glVertexBuffer->getVertexBufferID());
	glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL );	
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, glVertexBuffer->getNormalBufferID());
	glNormalPointer(GL_FLOAT, 0, (char *) NULL );			
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, glVertexBuffer->getTextCoordBufferID());
	glTexCoordPointer( 2, GL_FLOAT, 0, (char *) NULL );
	
	
	GLenum mode = GL_TRIANGLES;
	
	switch(buffer->meshType) {
		case Mesh::TRI_MESH:
			switch(renderMode) {
				case RENDER_MODE_NORMAL:
					mode = GL_TRIANGLES;
					break;
				case RENDER_MODE_WIREFRAME:
					mode = GL_LINE_LOOP;
					break;
			}
			break;
		case Mesh::TRIFAN_MESH:
			switch(renderMode) {
				case RENDER_MODE_NORMAL:
					mode = GL_TRIANGLE_FAN;
					break;
				case RENDER_MODE_WIREFRAME:
					mode = GL_LINE_LOOP;
					break;
			}
			break;
		case Mesh::QUAD_MESH:
			switch(renderMode) {
				case RENDER_MODE_NORMAL:
					mode = GL_QUADS;
					break;
				case RENDER_MODE_WIREFRAME:
					mode = GL_LINE_LOOP;
					break;
			}
			break;
		case Mesh::LINE_MESH:
			mode = GL_LINES;
			break;	
		case Mesh::POINT_MESH:
			mode = GL_POINTS;
			break;
	}	
	
	glDrawArrays( mode, 0, buffer->getVertexCount() );
	
	glDisableClientState( GL_VERTEX_ARRAY);	
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );		
	glDisableClientState( GL_NORMAL_ARRAY );
//	glDisableClientState( GL_COLOR_ARRAY );	
}

void OpenGLRenderer::enableFog(bool enable) {
	if(enable)
		glEnable(GL_FOG);
	else {
		glDisable(GL_FOG);
		glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	}
}

void OpenGLRenderer::setBlendingMode(int blendingMode) {
	switch(blendingMode) {
		case BLEND_MODE_NORMAL:
				glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		break;
		case BLEND_MODE_LIGHTEN:
				glBlendFunc (GL_SRC_ALPHA, GL_ONE);
		break;
		case BLEND_MODE_COLOR:
				glBlendFunc (GL_SRC_ALPHA_SATURATE, GL_ONE);
		break;
		default:
			glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		break;
	}
	glEnable(GL_BLEND);
}

Matrix4 OpenGLRenderer::getProjectionMatrix() {
	Number m[16];
	glGetDoublev( GL_PROJECTION_MATRIX, m);
	return Matrix4(m);
}

Matrix4 OpenGLRenderer::getModelviewMatrix() {
	Number m[16];
    glGetDoublev( GL_MODELVIEW_MATRIX, m);
	return Matrix4(m);
}

void OpenGLRenderer::renderZBufferToTexture(Texture *targetTexture) {
//	OpenGLTexture *glTexture = (OpenGLTexture*)targetTexture;
//	glBindTexture (GL_TEXTURE_2D, glTexture->getTextureID());
//	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 0, 0, targetTexture->getWidth(), targetTexture->getHeight(), 0);	
}

void OpenGLRenderer::renderToTexture(Texture *targetTexture) {
	OpenGLTexture *glTexture = (OpenGLTexture*)targetTexture;
	glBindTexture (GL_TEXTURE_2D, glTexture->getTextureID());
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0, targetTexture->getWidth(), targetTexture->getHeight(), 0);	

}

void OpenGLRenderer::setFogProperties(int fogMode, Color color, Number density, Number startDepth, Number endDepth) {
	switch(fogMode) {
		case FOG_LINEAR:
			glFogi(GL_FOG_MODE, GL_LINEAR);
		break;
		case FOG_EXP:
				glFogi(GL_FOG_MODE, GL_EXP);
		break;
		case FOG_EXP2:
				glFogi(GL_FOG_MODE, GL_EXP2);
		break;
		default:
				glFogi(GL_FOG_MODE, GL_LINEAR);
		break;
	}

	GLfloat fogColor[4]= {color.r, color.g, color.b, color.a};
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, density);
	glHint(GL_FOG_HINT, GL_DONT_CARE);
	glFogf(GL_FOG_START, startDepth);
	glFogf(GL_FOG_END, endDepth);
}


void OpenGLRenderer::_setOrthoMode() {
	if(!orthoMode) {
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(-1,1,-1,1,nearPlane,farPlane);
		orthoMode = true;
	}
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();	
}

void OpenGLRenderer::setOrthoMode(Number xSize, Number ySize) {
	
	if(xSize == 0)
		xSize = xRes;

	if(ySize == 0)
		ySize = yRes;
		
	setBlendingMode(BLEND_MODE_NORMAL);
	if(!orthoMode) {
		glDisable(GL_LIGHTING);
		glMatrixMode(GL_PROJECTION);
		glDisable(GL_CULL_FACE);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0.0f,xSize,ySize,0,-1.0f,1.0f);
		orthoMode = true;
	}
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
}

void OpenGLRenderer::enableBackfaceCulling(bool val) {
	if(val)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);
}

void OpenGLRenderer::setPerspectiveMode() {
	setBlendingMode(BLEND_MODE_NORMAL);
	if(orthoMode) {
		if(lightingEnabled) {
		}
		glEnable (GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glMatrixMode( GL_PROJECTION );
		glPopMatrix();
		glMatrixMode( GL_MODELVIEW );
		orthoMode = false;
	}
	glLoadIdentity();
	
	glGetDoublev( GL_PROJECTION_MATRIX, sceneProjectionMatrix);
	currentTexture = NULL;
}

void OpenGLRenderer::BeginRender() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	currentTexture = NULL;
}

void OpenGLRenderer::setClearColor(Number r, Number g, Number b) {
	clearColor.setColor(r,g,b,1.0f);	
	glClearColor(r,g,b,0.0f);
}

void OpenGLRenderer::translate3D(Vector3 *position) {
	glTranslatef(position->x, position->y, position->z);
}

void OpenGLRenderer::translate3D(Number x, Number y, Number z) {
	glTranslatef(x, y, z);
}

void OpenGLRenderer::scale3D(Vector3 *scale) {
	glScalef(scale->x, scale->y, scale->z);
}

void OpenGLRenderer::bindFrameBufferTexture(Texture *texture) {
	if(currentFrameBufferTexture) {
		previousFrameBufferTexture = currentFrameBufferTexture;
	}
	OpenGLTexture *glTexture = (OpenGLTexture*)texture;

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, glTexture->getFrameBufferID());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	currentFrameBufferTexture = texture;
}

void OpenGLRenderer::unbindFramebuffers() {
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);	
	currentFrameBufferTexture = NULL;
	if(previousFrameBufferTexture) {
		bindFrameBufferTexture(previousFrameBufferTexture);
		previousFrameBufferTexture = NULL;
	}
}


void OpenGLRenderer::createRenderTextures(Texture **colorBuffer, Texture **depthBuffer, int width, int height) {
	
	Logger::log("generating fbo textures %d %d\n", colorBuffer, depthBuffer);	
		
	GLuint depthTexture,colorTexture;
	GLenum status;
	GLuint frameBufferID;
	
	glGenFramebuffersEXT(1, &frameBufferID);   
	
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, frameBufferID);     	
	glGenTextures(1,&colorTexture);
	glBindTexture(GL_TEXTURE_2D,colorTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, colorTexture, 0);

	status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if(status == GL_FRAMEBUFFER_COMPLETE_EXT) {
		Logger::log("color fbo generation successful\n");
	} else {
		Logger::log("color fbo generation failed\n");	
	}

	if(colorBuffer) {
		OpenGLTexture *colorBufferTexture = new OpenGLTexture(width, height);
		colorBufferTexture->setGLInfo(colorTexture, frameBufferID);
		*colorBuffer = ((Texture*)colorBufferTexture);
	}
	
	if(depthBuffer) {
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, frameBufferID);     
		glGenTextures(1,&depthTexture);
		glBindTexture(GL_TEXTURE_2D,depthTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE,GL_COMPARE_R_TO_TEXTURE);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);	
		glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE);	
	
		glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT,width,height,0,GL_DEPTH_COMPONENT,GL_UNSIGNED_BYTE,0);
	
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, depthTexture, 0);

		status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);

		if(status == GL_FRAMEBUFFER_COMPLETE_EXT) {
			Logger::log("depth fbo generation successful\n");
		} else {
			Logger::log("depth fbo generation failed\n");	
		}
		
		OpenGLTexture *depthBufferTexture = new OpenGLTexture(width, height);
		depthBufferTexture->setGLInfo(depthTexture, frameBufferID);	
		*depthBuffer = ((Texture*)depthBufferTexture);		
	}
	
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

Texture *OpenGLRenderer::createFramebufferTexture(unsigned int width, unsigned int height) {
	OpenGLTexture *newTexture = new OpenGLTexture(width, height);	
	return newTexture;
}

Cubemap *OpenGLRenderer::createCubemap(Texture *t0, Texture *t1, Texture *t2, Texture *t3, Texture *t4, Texture *t5) {
	OpenGLCubemap *newCubemap = new OpenGLCubemap(t0,t1,t2,t3,t4,t5);
	return newCubemap;
}

Texture *OpenGLRenderer::createTexture(unsigned int width, unsigned int height, char *textureData, bool clamp, int type) {
	OpenGLTexture *newTexture = new OpenGLTexture(width, height, textureData, clamp, textureFilteringMode, type);	
	return newTexture;
}

void OpenGLRenderer::clearScreen() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::drawToColorBuffer(bool val) {
	if(val) {
		glDrawBuffer(GL_BACK);
	} else {
		glDrawBuffer(GL_NONE);		
	}
}

void OpenGLRenderer::cullFrontFaces(bool val) {
	if(val) {
		glCullFace(GL_FRONT);
		cullingFrontFaces = true;
	} else {
		glCullFace(GL_BACK);	
		cullingFrontFaces = false;	
	}
}

void OpenGLRenderer::clearBuffer(bool colorBuffer, bool depthBuffer) {
	GLbitfield clearMask = 0;
	
	if(colorBuffer) {
		clearMask = clearMask | GL_COLOR_BUFFER_BIT;
	} 
	
	if(depthBuffer) {
		clearMask = clearMask | GL_DEPTH_BUFFER_BIT;
	} 
	
	glClear(clearMask);	
}

void OpenGLRenderer::applyMaterial(Material *material,  ShaderBinding *localOptions,unsigned int shaderIndex) {
	if(!material->getShader(shaderIndex) || !shadersEnabled) {
		setTexture(NULL);
		return;
	}
	

	GLfloat data4[] = {material->diffuseColor.r, material->diffuseColor.g, material->diffuseColor.b, material->diffuseColor.a};					
	glMaterialfv(GL_FRONT, GL_DIFFUSE, data4);

	data4[0] = material->specularColor.r;
	data4[1] = material->specularColor.g;
	data4[2] = material->specularColor.b;
	data4[3] = material->specularColor.a;
				
	glMaterialfv(GL_FRONT, GL_SPECULAR, data4);

	glMaterialf(GL_FRONT, GL_SHININESS, material->specularValue);



	data4[0] = ambientColor.r;
	data4[1] = ambientColor.g;
	data4[2] = ambientColor.b;
	data4[3] = 1.0;
	glMaterialfv(GL_FRONT, GL_AMBIENT, data4);

	FixedShaderBinding *fBinding;

	switch(material->getShader(shaderIndex)->getType()) {
		case Shader::FIXED_SHADER:
//			FixedShader *fShader = (FixedShader*)material->getShader();
			fBinding = (FixedShaderBinding*)material->getShaderBinding(shaderIndex);
			setTexture(fBinding->getDiffuseTexture());
//			setTexture(fShader->getDiffuseTexture());
		break;	
		case Shader::MODULE_SHADER:		
			currentMaterial = material;			
			for(int m=0; m < shaderModules.size(); m++) {
				PolycodeShaderModule *shaderModule = shaderModules[m];	
				if(shaderModule->hasShader(material->getShader(shaderIndex))) {
					shaderModule->applyShaderMaterial(this, material, localOptions, shaderIndex);
					currentShaderModule = shaderModule;
				}
			}
		break;
	}
}

void OpenGLRenderer::clearShader() {

	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);
	glDisable(GL_FOG);
	
	for(int i=0; i < 4; i++)  {
		glActiveTexture(GL_TEXTURE0+i);		
		glDisable(GL_TEXTURE_2D);
	}
		
	if(currentShaderModule) {
		currentShaderModule->clearShader();
		currentShaderModule = NULL;
	}
	currentMaterial = NULL;
}

void OpenGLRenderer::setTexture(Texture *texture) {

	if(texture == NULL) {
		glActiveTexture(GL_TEXTURE0);		
		glDisable(GL_TEXTURE_2D);
		return;
	}
	
	if(renderMode == RENDER_MODE_NORMAL) {
		glActiveTexture(GL_TEXTURE0);	
		glEnable (GL_TEXTURE_2D);
				
		if(currentTexture != texture) {			
			OpenGLTexture *glTexture = (OpenGLTexture*)texture;
			glBindTexture (GL_TEXTURE_2D, glTexture->getTextureID());
		}
	} else {
		glDisable(GL_TEXTURE_2D);
	}
	
	currentTexture = texture;
}

void OpenGLRenderer::pushMatrix() {
	glPushMatrix();
}

void OpenGLRenderer::popMatrix() {
	glPopMatrix();
}

void OpenGLRenderer::pushRenderDataArray(RenderDataArray *array) {
		
	
	switch(array->arrayType) {
		case RenderDataArray::VERTEX_DATA_ARRAY:
			glEnableClientState(GL_VERTEX_ARRAY);			
			glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0);
			glVertexPointer(array->size, GL_FLOAT, 0, array->arrayPtr);
			verticesToDraw = array->count;
		break;
		case RenderDataArray::COLOR_DATA_ARRAY:		
			glColorPointer(array->size, GL_FLOAT, 0, array->arrayPtr);			
			glEnableClientState(GL_COLOR_ARRAY);
		break;
		case RenderDataArray::TEXCOORD_DATA_ARRAY:
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);						
			glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0);			
			glTexCoordPointer(array->size, GL_FLOAT, 0, array->arrayPtr);
		break;
		case RenderDataArray::NORMAL_DATA_ARRAY:
			glEnableClientState(GL_NORMAL_ARRAY);	
			glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0);			
			glNormalPointer(GL_FLOAT, 0, array->arrayPtr);	
		break;
	}
}

RenderDataArray *OpenGLRenderer::createRenderDataArrayForMesh(Mesh *mesh, int arrayType) {
	RenderDataArray *newArray = createRenderDataArray(arrayType);
		
	newArray->count = 0;
	long bufferSize = 0;
	long newBufferSize = 0;		
	GLfloat* buffer = NULL;
	
	switch (arrayType) {
		case RenderDataArray::VERTEX_DATA_ARRAY:
		{		
			buffer = (GLfloat*)malloc(1);							
			for(int i=0; i < mesh->getPolygonCount(); i++) {
				for(int j=0; j < mesh->getPolygon(i)->getVertexCount(); j++) {
					newArray->count++;			
					newBufferSize = bufferSize + 3;
					buffer = (GLfloat*)realloc(buffer, newBufferSize * sizeof(GLfloat));
					buffer[bufferSize+0] = mesh->getPolygon(i)->getVertex(j)->x;
					buffer[bufferSize+1] = mesh->getPolygon(i)->getVertex(j)->y;
					buffer[bufferSize+2] = mesh->getPolygon(i)->getVertex(j)->z;			
					bufferSize = newBufferSize;	
				}		   
			}
		}
		break;
		case RenderDataArray::COLOR_DATA_ARRAY:
		{
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
		}
		break;
		case RenderDataArray::NORMAL_DATA_ARRAY:
		{
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
		}
		break;
		case RenderDataArray::TEXCOORD_DATA_ARRAY:
		{
			buffer = (GLfloat*)malloc(1);				
			for(int i=0; i < mesh->getPolygonCount(); i++) {
				for(int j=0; j < mesh->getPolygon(i)->getVertexCount(); j++) {
					newBufferSize = bufferSize + 2;			
					buffer = (GLfloat*)realloc(buffer, newBufferSize * sizeof(GLfloat));		
					buffer[bufferSize+0] = mesh->getPolygon(i)->getVertex(j)->getTexCoord().x;											
					buffer[bufferSize+1] = mesh->getPolygon(i)->getVertex(j)->getTexCoord().y;							
					bufferSize = newBufferSize;					
				}		   
			}			
		}
		break;
		default:
		break;
	}
	
	if(buffer != NULL) {
		free(newArray->arrayPtr);
		newArray->arrayPtr = buffer;		
	}
	
	return newArray;
}

RenderDataArray *OpenGLRenderer::createRenderDataArray(int arrayType) {
	RenderDataArray *newArray = new RenderDataArray();
	newArray->arrayType = arrayType;
	newArray->arrayPtr = malloc(1);
	newArray->stride = 0;
	newArray->count = 0;
	
	switch (arrayType) {
		case RenderDataArray::VERTEX_DATA_ARRAY:
			newArray->size = 3;
			break;
		case RenderDataArray::COLOR_DATA_ARRAY:
			newArray->size = 4;
			break;			
		case RenderDataArray::NORMAL_DATA_ARRAY:
			newArray->size = 3;
			break;						
		case RenderDataArray::TEXCOORD_DATA_ARRAY:
			newArray->size = 2;
			break;									
		default:
			break;
	}
	
	return newArray;
}

void OpenGLRenderer::setRenderArrayData(RenderDataArray *array, Number *arrayData) {
	
}

void OpenGLRenderer::drawArrays(int drawType) {
	
	GLenum mode = GL_TRIANGLES;
	
	switch(drawType) {
		case Mesh::TRI_MESH:
			switch(renderMode) {
				case RENDER_MODE_NORMAL:
					mode = GL_TRIANGLES;
					break;
				case RENDER_MODE_WIREFRAME:
					mode = GL_LINE_LOOP;
					break;
			}
			break;
		case Mesh::TRIFAN_MESH:
			switch(renderMode) {
				case RENDER_MODE_NORMAL:
					mode = GL_TRIANGLE_FAN;
					break;
				case RENDER_MODE_WIREFRAME:
					mode = GL_LINE_LOOP;
					break;
			}
			break;
		case Mesh::QUAD_MESH:
			switch(renderMode) {
				case RENDER_MODE_NORMAL:
					mode = GL_QUADS;
					break;
				case RENDER_MODE_WIREFRAME:
					mode = GL_LINE_LOOP;
					break;
			}
			break;
		case Mesh::LINE_MESH:
			mode = GL_LINES;
			break;	
		case Mesh::POINT_MESH:
			mode = GL_POINTS;
		break;
	}
	
	glDrawArrays( mode, 0, verticesToDraw);	
	
	verticesToDraw = 0;
		
	glDisableClientState( GL_VERTEX_ARRAY);	
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );		
	glDisableClientState( GL_NORMAL_ARRAY );
	glDisableClientState( GL_COLOR_ARRAY );		
}

/*
void OpenGLRenderer::draw3DVertex2UV(Vertex *vertex, Vector2 *faceUV1, Vector2 *faceUV2) {
	if(vertex->useVertexColor)
		glColor4f(vertex->vertexColor.r, vertex->vertexColor.g, vertex->vertexColor.b, vertex->vertexColor.a);

	if(currentTexture || currentMaterial) {
		glMultiTexCoord2f(GL_TEXTURE0, faceUV1->x, faceUV1->y);
		glMultiTexCoord2f(GL_TEXTURE1, faceUV2->x, faceUV2->y);
	}

//	glNormal3f(vertex->normal->x, vertex->normal->y, vertex->normal->z);
	glVertex3f(vertex->x, vertex->y, vertex->z);
}
*/

void OpenGLRenderer::drawScreenQuad(Number qx, Number qy) {
	setOrthoMode();
	
	Number xscale = qx/((Number)getXRes()) * 2.0f;
	Number yscale = qy/((Number)getYRes()) * 2.0f;

	glBegin(GL_QUADS);
		glColor4f(1.0f,1.0f,1.0f,1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(-1, -1+(1.0f*yscale));

		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(-1.0f, -1.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(-1+(1.0f*xscale), -1.0f);

		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(-1+(1.0f*xscale), -1+(1.0f*yscale));
	glEnd();
	setPerspectiveMode();
}


void OpenGLRenderer::translate2D(Number x, Number y) {
	glTranslatef(x, y, 0.0f);
}

void OpenGLRenderer::scale2D(Vector2 *scale) {
	glScalef(scale->x, scale->y, 1.0f);
}

void OpenGLRenderer::loadIdentity() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void OpenGLRenderer::rotate2D(Number angle) {
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
}

void OpenGLRenderer::setVertexColor(Number r, Number g, Number b, Number a) {
	glColor4f(r,g,b,a);
}

void OpenGLRenderer::EndRender() {
///	glFlush();
//	glFinish();	
}

OpenGLRenderer::~OpenGLRenderer() {

}