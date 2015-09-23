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
#include "PolyString.h"
#include "PolyLogger.h"
#include "PolyTexture.h"
#include "PolyVector2.h"
#include "PolyGLTexture.h"
#include "PolyCubemap.h"
#include "PolyGLCubemap.h"
#include "PolyGLVertexBuffer.h"
#include "PolyFixedShader.h"
#include "PolyMaterial.h"
#include "PolyMesh.h"
#include "PolyModule.h"

#if defined(_WINDOWS) && !defined(_MINGW)


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

PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
PFNGLENABLEVERTEXATTRIBARRAYARBPROC glEnableVertexAttribArrayARB;
PFNGLDISABLEVERTEXATTRIBARRAYARBPROC glDisableVertexAttribArrayARB;
PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;

PFNGLGETPROGRAMIVPROC glGetProgramiv;
PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform;

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

inline void polycodeGLGetNumberv( GLenum pname, GLdouble *params ) {
	glGetDoublev(pname, params);
}
inline void polycodeGLGetNumberv( GLenum pname, GLfloat *params ) {
	glGetFloatv(pname, params);
}

OpenGLRenderer::OpenGLRenderer() : Renderer() {

	verticesToDraw = 0;

}

bool OpenGLRenderer::Init() {
	if(!Renderer::Init())
		return false;

	glDisable(GL_SCISSOR_TEST);

	return true;
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

		glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
		glEnableVertexAttribArrayARB = (PFNGLENABLEVERTEXATTRIBARRAYARBPROC)wglGetProcAddress("glEnableVertexAttribArrayARB");
		glDisableVertexAttribArrayARB = (PFNGLDISABLEVERTEXATTRIBARRAYARBPROC)wglGetProcAddress("glDisableVertexAttribArrayARB");
		glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)wglGetProcAddress("glBindAttribLocation");

		
		glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
		glGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC)wglGetProcAddress("glGetActiveUniform");

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
	viewportWidth = xRes;
	viewportHeight = xRes;
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	glClearDepth(1.0f);

	glLineWidth(1);
	glDepthFunc( GL_LEQUAL );
	
	glEnable(GL_DEPTH_TEST);
	
	glLineWidth(1.0f);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	GLint numBuffers;
	glGetIntegerv(GL_MAX_DRAW_BUFFERS, &numBuffers);

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
		glAlphaFunc ( GL_GREATER, alphaTestValue) ;
		glEnable ( GL_ALPHA_TEST ) ;		
	} else {
		glDisable( GL_ALPHA_TEST ) ;
	}
}

void OpenGLRenderer::setPointSmooth(bool val) {
	if(val)
		glEnable( GL_POINT_SMOOTH );
	else
		glDisable( GL_POINT_SMOOTH );

}

void OpenGLRenderer::setLineSmooth(bool val) {
	if(val)
		glEnable(GL_LINE_SMOOTH);
	else
		glDisable(GL_LINE_SMOOTH);
}

void OpenGLRenderer::setProjectionFromFrustum(Number left, Number right, Number bottom, Number top, Number front, Number back) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(left, right, bottom, top, front, back);
	glMatrixMode(GL_MODELVIEW);
	polycodeGLGetNumberv(GL_PROJECTION_MATRIX, sceneProjectionMatrix);

}

void OpenGLRenderer::setProjectionFromFoV(Number fov, Number _near, Number _far) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	Number fW, fH;
	fH = tan( fov / 360.0 * PI ) * _near;
	fW = fH * ((GLfloat)viewportWidth/(GLfloat)viewportHeight);
	glFrustum(-fW + (viewportShift.x*fW*2.0), fW + (viewportShift.x*fW*2.0), -fH + (viewportShift.y*fH*2.0), fH + (viewportShift.y*fH*2.0), _near, _far);
	glMatrixMode(GL_MODELVIEW);
	polycodeGLGetNumberv(GL_PROJECTION_MATRIX, sceneProjectionMatrix);
}

void OpenGLRenderer::resetViewport() {
	glViewport(0, 0, viewportWidth*backingResolutionScaleX, viewportHeight*backingResolutionScaleY);
	glScissor(0, 0,  viewportWidth*backingResolutionScaleX, viewportHeight*backingResolutionScaleY);
}

Vector3 OpenGLRenderer::Unproject(Number x, Number y, const Matrix4 &cameraMatrix, const Matrix4 &projectionMatrix, const Polycode::Rectangle &viewport) {
	Vector3 coords;
	GLfloat wx, wy, wz;
	GLdouble cx, cy, cz;

	GLdouble mv[16];
	Matrix4 camInverse = cameraMatrix.Inverse();
	Matrix4 cmv;
	cmv.identity();
	cmv = cmv * camInverse;
    
	for(int i=0; i < 16; i++) {
		mv[i] = cmv.ml[i];
	}
    
	GLint vp[4] = {viewport.x, viewport.y, viewport.w, viewport.h};
    
	GLdouble _sceneProjectionMatrix[16];
	for(int i=0; i < 16; i++) {
		_sceneProjectionMatrix[i] = projectionMatrix.ml[i];
	}	
	
	wx = ( Number ) x;
	wy = ( Number ) vp[3] - ( Number ) y;
	glReadPixels( x * backingResolutionScaleX, wy * backingResolutionScaleY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &wz );
	
	gluUnProject( wx, wy, wz, mv, _sceneProjectionMatrix, vp, &cx, &cy, &cz );
	
	coords = Vector3( cx, cy, cz );
	
	return coords;	
}

Vector2 OpenGLRenderer::Project(const Matrix4 &cameraMatrix, const Matrix4 &projectionMatrix, const Polycode::Rectangle &viewport, const Vector3 &coordiante) const {
    
	GLdouble mv[16];
	Matrix4 camInverse = cameraMatrix.Inverse();	
	Matrix4 cmv;
	cmv.identity();
	cmv = cmv * camInverse;
    
	for(int i=0; i < 16; i++) {
		mv[i] = cmv.ml[i];
	}
    
	GLint vp[4] = {viewport.x, viewport.y, viewport.w, viewport.h};

	GLdouble _sceneProjectionMatrix[16];
	for(int i=0; i < 16; i++) {
		_sceneProjectionMatrix[i] = projectionMatrix.ml[i];
	}	

	GLdouble coords[3];
	
	gluProject(coordiante.x, coordiante.y, coordiante.z, mv, _sceneProjectionMatrix, vp, &coords[0], &coords[1], &coords[2]);
	
    return Vector2(coords[0] / backingResolutionScaleX, (viewport.h-coords[1]) / backingResolutionScaleY);
}

Polycode::Rectangle OpenGLRenderer::getViewport() {
	GLint vp[4];
	glGetIntegerv( GL_VIEWPORT, vp );
	return Polycode::Rectangle(vp[0], vp[1], vp[2], vp[3]); 
}

Vector3 OpenGLRenderer::projectRayFrom2DCoordinate(Number x, Number y, const Matrix4 &cameraMatrix, const Matrix4 &projectionMatrix, const Polycode::Rectangle &viewport) {
	GLdouble nearPlane[3],farPlane[3];

	GLdouble mv[16];
	Matrix4 camInverse = cameraMatrix.Inverse();	
	Matrix4 cmv;
	cmv.identity();
	cmv = cmv * camInverse;

	for(int i=0; i < 16; i++) {
		mv[i] = cmv.ml[i];
	}

	GLint vp[4] = {viewport.x, viewport.y, viewport.w, viewport.h};

	GLdouble _sceneProjectionMatrix[16];
	for(int i=0; i < 16; i++) {
		_sceneProjectionMatrix[i] = projectionMatrix.ml[i];
	}

	gluUnProject(x, (yRes*backingResolutionScaleY) - y, 0.0, mv, _sceneProjectionMatrix, vp, &nearPlane[0], &nearPlane[1], &nearPlane[2]);
	gluUnProject(x, (yRes*backingResolutionScaleY) - y, 1.0, mv, _sceneProjectionMatrix, vp, &farPlane[0], &farPlane[1], &farPlane[2]);

	Vector3 nearVec(nearPlane[0], nearPlane[1], nearPlane[2]);
	Vector3 farVec(farPlane[0], farPlane[1], farPlane[2]);

	Vector3 dirVec = (farVec) - (nearVec);	
	dirVec.Normalize();

	return dirVec;
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

inline void loadMatrixNumber(const GLfloat* m) {
	glLoadMatrixf(m);
}

inline void loadMatrixNumber(const GLdouble* m) {
	glLoadMatrixd(m);
}

inline void multMatrixNumber(const GLfloat* m) {
	glMultMatrixf(m);
}

inline void multMatrixNumber(const GLdouble* m) {
	glMultMatrixd(m);
}

void OpenGLRenderer::setModelviewMatrix(Matrix4 m) {
	loadMatrixNumber(m.ml);
}

void OpenGLRenderer::multModelviewMatrix(Matrix4 m) {
//	glMatrixMode(GL_MODELVIEW);
	multMatrixNumber(m.ml);
}

void OpenGLRenderer::enableLighting(bool enable) {
	lightingEnabled = enable;
}

void OpenGLRenderer::setLineSize(Number lineSize) {
	glLineWidth(lineSize);
}

void OpenGLRenderer::setPointSize(Number pointSize) {
	glPointSize(pointSize);
}

VertexBuffer *OpenGLRenderer::createVertexBufferForMesh(Mesh *mesh) {
	OpenGLVertexBuffer *buffer = new OpenGLVertexBuffer(mesh);
    return buffer;
}

void OpenGLRenderer::drawVertexBuffer(VertexBuffer *buffer, bool enableColorBuffer) {
	OpenGLVertexBuffer *glVertexBuffer = (OpenGLVertexBuffer*)buffer;

	glEnableClientState(GL_VERTEX_ARRAY);		
    glBindBufferARB( GL_ARRAY_BUFFER_ARB, glVertexBuffer->getVertexBufferID());
	glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL );

	if(enableColorBuffer && glVertexBuffer->getColorBufferID() != -1)  {
		glEnableClientState(GL_COLOR_ARRAY);
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, glVertexBuffer->getColorBufferID());
		glColorPointer( 4, GL_FLOAT, 0, (char *) NULL );	
	}
    
    if(glVertexBuffer->getNormalBufferID() != -1) {
        glEnableClientState(GL_NORMAL_ARRAY);
        glBindBufferARB( GL_ARRAY_BUFFER_ARB, glVertexBuffer->getNormalBufferID());
        glNormalPointer(GL_FLOAT, 0, (char *) NULL );
    }
    
    if(glVertexBuffer->getTextCoordBufferID() != -1) {
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glBindBufferARB( GL_ARRAY_BUFFER_ARB, glVertexBuffer->getTextCoordBufferID());
        glTexCoordPointer( 2, GL_FLOAT, 0, (char *) NULL );
    }
    
    if(glVertexBuffer->getTangentBufferID() != -1) {
        glBindBufferARB( GL_ARRAY_BUFFER_ARB, glVertexBuffer->getTangentBufferID());
        glEnableVertexAttribArrayARB(6);	
        glVertexAttribPointer(6, 3, GL_FLOAT, 0, 0,  (char *)NULL);
	}
    
    if(glVertexBuffer->getBoneWeightBufferID() != -1) {
        
        glBindBufferARB( GL_ARRAY_BUFFER_ARB, glVertexBuffer->getBoneWeightBufferID());
        glEnableVertexAttribArrayARB(7);
        glVertexAttribPointer(7, 4, GL_FLOAT, 0, 0,  (char *)NULL);
    }
    
    if(glVertexBuffer->getBoneIndexBufferID() != -1) {
        
        glBindBufferARB( GL_ARRAY_BUFFER_ARB, glVertexBuffer->getBoneIndexBufferID());
        glEnableVertexAttribArrayARB(8);
        glVertexAttribPointer(8, 4, GL_FLOAT, 0, 0,  (char *)NULL);
    }
    
	GLenum mode = GL_TRIANGLES;
	
	switch(buffer->meshType) {
		case Mesh::TRI_MESH:
            mode = GL_TRIANGLES;
			break;
		case Mesh::TRIFAN_MESH:
            mode = GL_TRIANGLE_FAN;
			break;
		case Mesh::QUAD_MESH:
            mode = GL_QUADS;
			break;
		case Mesh::LINE_STRIP_MESH:
			mode = GL_LINE_STRIP;
			break;	
		case Mesh::LINE_LOOP_MESH:
			mode = GL_LINE_LOOP;
			break;				
		case Mesh::LINE_MESH:
			mode = GL_LINES;
			break;				
		case Mesh::POINT_MESH:
			mode = GL_POINTS;
			break;
	}	
	
    if(glVertexBuffer->getIndexBufferID() != -1) {
        glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, glVertexBuffer->getIndexBufferID());
        glDrawElements(mode, glVertexBuffer->getIndexCount(), GL_UNSIGNED_INT, (void*)0);
        glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
    } else {
        glDrawArrays( mode, 0, buffer->getVertexCount() );
	}
    
    glDisableVertexAttribArrayARB(6);
    glDisableVertexAttribArrayARB(7);
    glDisableVertexAttribArrayARB(8);
    
	glDisableClientState( GL_VERTEX_ARRAY);
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );		
	glDisableClientState( GL_NORMAL_ARRAY );
	glDisableClientState( GL_COLOR_ARRAY );
}

void OpenGLRenderer::enableScissor(bool val) {
	if(val) {
		glEnable(GL_SCISSOR_TEST);
	} else {
		glDisable(GL_SCISSOR_TEST);	
	}
	Renderer::enableScissor(val);
}

void OpenGLRenderer::setScissorBox(Polycode::Rectangle box) {
	glScissor(box.x*backingResolutionScaleX, (((yRes*backingResolutionScaleY)-(box.y*backingResolutionScaleY))-(box.h*backingResolutionScaleY)), box.w *backingResolutionScaleX, box.h * backingResolutionScaleY);
	Renderer::setScissorBox(box);
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
    
    if(blendingMode == BLEND_MODE_NONE) {
        glDisable(GL_BLEND);
    } else {
        glEnable(GL_BLEND);
    }
    
	switch(blendingMode) {
		case BLEND_MODE_NORMAL:
			if(blendNormalAsPremultiplied) {
				glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);			
			} else{
				glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}
		break;
		case BLEND_MODE_LIGHTEN:
				glBlendFunc (GL_SRC_ALPHA, GL_ONE);
		break;
		case BLEND_MODE_COLOR:
				glBlendFunc (GL_DST_COLOR, GL_SRC_COLOR);
		break;
		case BLEND_MODE_PREMULTIPLIED:
			glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		break;
		case BLEND_MODE_MULTIPLY:
			glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);
		break;
		default:
			glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		break;
	}
}

Matrix4 OpenGLRenderer::getProjectionMatrix() {
	Number m[16];
	polycodeGLGetNumberv( GL_PROJECTION_MATRIX, m);
	return Matrix4(m);
}

Matrix4 OpenGLRenderer::getModelviewMatrix() {
	Number m[16];
	polycodeGLGetNumberv( GL_MODELVIEW_MATRIX, m);
	return Matrix4(m);
}

Image *OpenGLRenderer::renderBufferToImage(Texture *texture) {
    
	OpenGLTexture *glTexture = (OpenGLTexture*)texture;
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, glTexture->getFrameBufferID());
    glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);
    
	char *imageBuffer = (char*)malloc(texture->getWidth() * backingResolutionScaleX * texture->getHeight() * backingResolutionScaleY * 4);
	glReadPixels(0, 0, texture->getWidth() * backingResolutionScaleX, texture->getHeight() * backingResolutionScaleY, GL_RGBA, GL_UNSIGNED_BYTE, imageBuffer);
	Image *retImage = new Image(imageBuffer, texture->getWidth() * backingResolutionScaleX, texture->getHeight() * backingResolutionScaleY, Image::IMAGE_RGBA);
	free(imageBuffer);
    
    unbindFramebuffers();
	return retImage;
}

Image *OpenGLRenderer::renderScreenToImage() {
    glReadBuffer(GL_FRONT);
    
	char *imageBuffer = (char*)malloc(xRes* backingResolutionScaleX * yRes * backingResolutionScaleY * 4);
	glReadPixels(0, 0, xRes * backingResolutionScaleX, yRes * backingResolutionScaleY, GL_RGBA, GL_UNSIGNED_BYTE, imageBuffer);
	Image *retImage = new Image(imageBuffer, xRes * backingResolutionScaleX, yRes * backingResolutionScaleY, Image::IMAGE_RGBA);
	free(imageBuffer);
	return retImage;
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

void OpenGLRenderer::setProjectionOrtho(Number xSize, Number ySize, Number _near, Number _far, bool centered) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
		
	if(centered) {
		glOrtho(-xSize*0.5, xSize*0.5, -ySize*0.5, ySize*0.5, _near, _far);
	} else {
		glOrtho(0.0f, xSize, 0, ySize, _near, _far);
	}
	polycodeGLGetNumberv( GL_PROJECTION_MATRIX, sceneProjectionMatrixOrtho);

	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
}

void OpenGLRenderer::setProjectionMatrix(Matrix4 matrix) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
	loadMatrixNumber(matrix.ml);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OpenGLRenderer::enableBackfaceCulling(bool val) {
	if(val)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);
}

void OpenGLRenderer::setPerspectiveDefaults() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	polycodeGLGetNumberv( GL_PROJECTION_MATRIX, sceneProjectionMatrix);
	currentTexture = NULL;
}

void OpenGLRenderer::BeginRender() {
    
    Renderer::BeginRender();
    
	if(doClearBuffer) {
		glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	glLoadIdentity();
	currentTexture = NULL;
}

void OpenGLRenderer::translate3D(const Vector3 &position) {
	glTranslatef(position.x, position.y, position.z);
}

void OpenGLRenderer::translate3D(Number x, Number y, Number z) {
	glTranslatef(x, y, z);
}

void OpenGLRenderer::scale3D(const Vector3 &scale) {
	glScalef(scale.x, scale.y, scale.z);
}

void OpenGLRenderer::bindFrameBufferTextureDepth(Texture *texture) {
	if(!texture)
		return;
	OpenGLTexture *glTexture = (OpenGLTexture*)texture;
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, glTexture->getFrameBufferID());
    Renderer::bindFrameBufferTextureDepth(texture);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	        
}


void OpenGLRenderer::bindFrameBufferTexture(Texture *texture) {
	if(!texture)
		return;
	OpenGLTexture *glTexture = (OpenGLTexture*)texture;
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, glTexture->getFrameBufferID());
    Renderer::bindFrameBufferTexture(texture);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::unbindFramebuffers() {
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);
    Renderer::unbindFramebuffers();
}

void OpenGLRenderer::createRenderTextures(Texture **colorBuffer, Texture **depthBuffer, int width, int height, bool floatingPointBuffer) {
			
	GLuint depthTexture,colorTexture;
	GLenum status;
	GLuint frameBufferID;
	
	glGenFramebuffersEXT(1, &frameBufferID);   
	
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, frameBufferID);     	
	glGenTextures(1,&colorTexture);
	glBindTexture(GL_TEXTURE_2D,colorTexture);
    if(textureFilteringMode == TEX_FILTERING_NEAREST) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    } else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);	
	
	if(floatingPointBuffer) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F_ARB, width* backingResolutionScaleX, height* backingResolutionScaleY, 0, GL_RGBA, GL_FLOAT, NULL);
	} else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width * backingResolutionScaleX, height * backingResolutionScaleY, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	}
	
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, colorTexture, 0);

	status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if(status == GL_FRAMEBUFFER_COMPLETE_EXT) {
//		Logger::log("color fbo generation successful\n");
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
        if(textureFilteringMode == TEX_FILTERING_NEAREST) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        } else {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE,GL_COMPARE_R_TO_TEXTURE);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);	
		glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE);	
	
		if(floatingPointBuffer) {	
			glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT16,width* backingResolutionScaleX,height * backingResolutionScaleY,0,GL_DEPTH_COMPONENT,GL_FLOAT,0);
		} else {
			glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT,width* backingResolutionScaleX,height* backingResolutionScaleY,0,GL_DEPTH_COMPONENT,GL_UNSIGNED_BYTE,0);
		}
	
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, depthTexture, 0);

		status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);

		if(status == GL_FRAMEBUFFER_COMPLETE_EXT) {
//			Logger::log("depth fbo generation successful\n");
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

Texture *OpenGLRenderer::createTexture(unsigned int width, unsigned int height, char *textureData, bool clamp, bool createMipmaps, int type) {
	OpenGLTexture *newTexture = new OpenGLTexture(width, height, textureData, clamp, createMipmaps, textureFilteringMode, type);
	return newTexture;
}

void OpenGLRenderer::destroyVertexBuffer(VertexBuffer *buffer) {
    OpenGLVertexBuffer *glBuffer = (OpenGLVertexBuffer*)buffer;
    delete glBuffer;
}

void OpenGLRenderer::destroyTexture(Texture *texture) {
	OpenGLTexture *glTex = (OpenGLTexture*)texture;
	delete glTex;
}

void OpenGLRenderer::clearScreen(bool useClearColor, bool useClearDepth) {
	if (useClearColor) {
		glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	}
	GLbitfield mask = 0;
	if (useClearColor) {
		mask |= GL_COLOR_BUFFER_BIT;
	}
	if (useClearDepth) {
		mask |= GL_DEPTH_BUFFER_BIT;
	}
	if (mask) {
		glClear(mask);
	}
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
	
    glActiveTexture(GL_TEXTURE0);
    glEnable (GL_TEXTURE_2D);
            
    if(currentTexture != texture) {			
        OpenGLTexture *glTexture = (OpenGLTexture*)texture;
        glBindTexture (GL_TEXTURE_2D, glTexture->getTextureID());
    }
	
	currentTexture = texture;
}

void OpenGLRenderer::pushMatrix() {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
}

void OpenGLRenderer::popMatrix() {
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void OpenGLRenderer::pushRenderDataArray(RenderDataArray *array) {
	
	switch(array->type) {
		case RenderDataArray::VERTEX_DATA_ARRAY:
			glEnableClientState(GL_VERTEX_ARRAY);
			glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0);
			glVertexPointer(3, GL_FLOAT, 0, array->getArrayData());
			verticesToDraw = array->getDataSize() / 3;
		break;
		case RenderDataArray::COLOR_DATA_ARRAY:
            if(array->getDataSize() != verticesToDraw * 4) {
                return;
            }
			glColorPointer(4, GL_FLOAT, 0, array->getArrayData());
			glEnableClientState(GL_COLOR_ARRAY);
		break;
		case RenderDataArray::TEXCOORD_DATA_ARRAY:
            if(array->getDataSize() != verticesToDraw * 2) {
                return;
            }
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);						
			glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0);			
			glTexCoordPointer(2, GL_FLOAT, 0, array->getArrayData());
		break;
		case RenderDataArray::NORMAL_DATA_ARRAY:
            if(array->getDataSize() != verticesToDraw * 3) {
                return;
            }
			glEnableClientState(GL_NORMAL_ARRAY);	
			glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0);			
			glNormalPointer(GL_FLOAT, 0, array->getArrayData());
		break;
		case RenderDataArray::TANGENT_DATA_ARRAY:
            if(array->getDataSize() != verticesToDraw * 3) {
                return;
            }
			glEnableVertexAttribArrayARB(6);		
			glVertexAttribPointer(6, 3, GL_FLOAT, 0, 0, array->getArrayData());
		break;
		
	}
}

void OpenGLRenderer::setWireframePolygonMode(bool val) {
    if(val) {
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
    }
}

void OpenGLRenderer::drawArrays(int drawType, IndexDataArray *indexArray) {
	
	GLenum mode = GL_TRIANGLES;
	
	switch(drawType) {
		case Mesh::TRI_MESH:
            mode = GL_TRIANGLES;
			break;
		case Mesh::TRIFAN_MESH:
            mode = GL_TRIANGLE_FAN;
			break;
		case Mesh::QUAD_MESH:
            mode = GL_QUADS;
			break;
		case Mesh::LINE_STRIP_MESH:
			mode = GL_LINE_STRIP;
			break;
		case Mesh::LINE_LOOP_MESH:
			mode = GL_LINE_LOOP;
			break;								
		case Mesh::LINE_MESH:
			mode = GL_LINES;
			break;				
		case Mesh::POINT_MESH:
			mode = GL_POINTS;
		break;
	}
	
    if(indexArray) {
        if(indexArray->getDataSize() > 0) {
            glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, 0);            
            glDrawElements(mode, indexArray->getDataSize(), GL_UNSIGNED_INT, indexArray->getArrayData());
        }
    } else {
        glDrawArrays( mode, 0, verticesToDraw);
	}
    
	verticesToDraw = 0;
		
	glDisableClientState( GL_VERTEX_ARRAY);	
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );		
	glDisableClientState( GL_NORMAL_ARRAY );
	glDisableClientState( GL_COLOR_ARRAY );
    glDisableVertexAttribArrayARB(6);
}

void OpenGLRenderer::drawScreenQuad(Number qx, Number qy) {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	setProjectionOrtho(2.0, 2.0, -1.0, 1.0, true);
	

	glBegin(GL_QUADS);
		glColor4f(1.0f,1.0f,1.0f,1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(-1, 1.0);

		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(-1.0f, -1.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(1.0, -1.0f);

		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(1.0, 1.0);
	glEnd();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	setPerspectiveDefaults();
}


void OpenGLRenderer::translate2D(Number x, Number y) {
	glTranslatef(x, y, 0.0f);
}

void OpenGLRenderer::scale2D(const Vector2 &scale) {
	glScalef(scale.x, scale.y, 1.0f);
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
    Renderer::EndRender();
///	glFlush();
//	glFinish();	
}

OpenGLRenderer::~OpenGLRenderer() {

}
