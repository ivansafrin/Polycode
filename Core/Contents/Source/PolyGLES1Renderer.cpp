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

#include "PolyGLES1Renderer.h"

using namespace Polycode;

OpenGLES1Renderer::OpenGLES1Renderer() : Renderer() {	
	nearPlane = 0.1f;
	farPlane = 1000.0f;

	glGenFramebuffersOES(1, &defaultFramebuffer);
	glGenRenderbuffersOES(1, &colorRenderbuffer);
	glBindFramebufferOES(GL_FRAMEBUFFER_OES, defaultFramebuffer);
	glBindRenderbufferOES(GL_RENDERBUFFER_OES, colorRenderbuffer);
	glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, colorRenderbuffer);

}

void OpenGLES1Renderer::Resize(int xRes, int yRes) {

	this->xRes = xRes;
	this->yRes = yRes;
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	glClearDepthf(1.0f);

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
	glEnable(GL_LINE_SMOOTH);

	GLint numBuffers = 0;
//	glGetIntegerv(GL_MAX_DRAW_BUFFERS, &numBuffers);
}

void OpenGLES1Renderer::enableAlphaTest(bool val) {
	if(val) {
		glAlphaFunc ( GL_GREATER, 0.01) ;
		glEnable ( GL_ALPHA_TEST ) ;
	} else {
		glDisable( GL_ALPHA_TEST ) ;
	}
}

void OpenGLES1Renderer::setLineSmooth(bool val) {
	if(val)
		glEnable(GL_LINE_SMOOTH);
	else
		glDisable(GL_LINE_SMOOTH);
}

void OpenGLES1Renderer::setFOV(Number fov) {
	this->fov = fov;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov,(GLfloat)xRes/(GLfloat)yRes,nearPlane,farPlane);
	glViewport(0, 0, xRes, yRes);
	glScissor(0, 0, xRes, yRes);
	glMatrixMode(GL_MODELVIEW);
}

void OpenGLES1Renderer::setViewportSize(int w, int h, Number fov) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov,(GLfloat)w/(GLfloat)h,nearPlane,farPlane);
	glViewport(0, 0, w, h);
	glScissor(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
}

Vector3 OpenGLES1Renderer::Unproject(Number x, Number y) {
	Vector3 coords;
	GLfloat wx, wy, wz;
	GLfloat cx, cy, cz;

	GLfloat mv[16];
	glGetFloatv( GL_MODELVIEW_MATRIX, mv );

	GLfloat proj[16];
	glGetFloatv( GL_PROJECTION_MATRIX, proj );

	GLint vp[4];
	glGetIntegerv( GL_VIEWPORT, vp );

	wx = ( Number ) x;
	wy = ( Number ) vp[3] - ( Number ) y;
	glReadPixels( x, wy, 1, 1, GL_DEPTH_COMPONENT16_OES, GL_FLOAT, &wz );

	gluUnProject((GLdouble)wx, (GLdouble)wy, (GLdouble)wz, (GLdouble*)mv, (GLdouble*)proj, vp, (GLdouble*)&cx, (GLdouble*)&cy, (GLdouble*)&cz );

	coords = Vector3( cx, cy, cz );

	return coords;

}

bool OpenGLES1Renderer::test2DCoordinate(Number x, Number y, Poly::Polygon *poly, const Matrix4 &matrix, bool billboardMode) {
	GLfloat nearPlane[3],farPlane[3];

	GLfloat mv[16];
	Matrix4 camInverse = cameraMatrix.Inverse();
	Matrix4 cmv;
	cmv.identity();
	cmv = cmv * camInverse;

	for(int i=0; i < 16; i++) {
		mv[i] = cmv.ml[i];
	}

	GLint vp[4];
	glGetIntegerv( GL_VIEWPORT, vp );

	gluUnProject((GLdouble)x, (GLdouble)yRes - y, 0.0, (GLdouble*)mv, (GLdouble*)sceneProjectionMatrix, vp, (GLdouble*)&nearPlane[0], (GLdouble*)&nearPlane[1], (GLdouble*)&nearPlane[2]);
	gluUnProject((GLdouble)x, (GLdouble)yRes - y, 1.0, (GLdouble*)mv, (GLdouble*)sceneProjectionMatrix, vp,  (GLdouble*)&farPlane[0], (GLdouble*)&farPlane[1], (GLdouble*)&farPlane[2]);

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

void OpenGLES1Renderer::enableDepthTest(bool val) {
	//	if(val)
	//		glEnable(GL_DEPTH_TEST);
	//	else
	//		glDisable(GL_DEPTH_TEST);
	if(val)
		glDepthMask(GL_TRUE);
	else
		glDepthMask(GL_FALSE);
	
}

void OpenGLES1Renderer::setModelviewMatrix(Matrix4 m) {
	glLoadMatrixf(m.ml);
}

void OpenGLES1Renderer::multModelviewMatrix(Matrix4 m) {
	//	glMatrixMode(GL_MODELVIEW);
	glMultMatrixf(m.ml);
}

void OpenGLES1Renderer::enableLighting(bool enable) {
	lightingEnabled = enable;
}

void OpenGLES1Renderer::setLineSize(Number lineSize) {
	glLineWidth(lineSize);
}

void OpenGLES1Renderer::createVertexBufferForMesh(Mesh *mesh) {
//	OpenGLVertexBuffer *buffer = new OpenGLVertexBuffer(mesh);
//	mesh->setVertexBuffer(buffer);
}

void OpenGLES1Renderer::drawVertexBuffer(VertexBuffer *buffer) {
	/*
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

	glDrawArrays( GL_TRIANGLES, 0, buffer->getVertexCount() );

	glDisableClientState( GL_VERTEX_ARRAY);	
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	glDisableClientState( GL_NORMAL_ARRAY );
	//	glDisableClientState( GL_COLOR_ARRAY );	
	 */
}

void OpenGLES1Renderer::enableFog(bool enable) {
	if(enable)
		glEnable(GL_FOG);
	else {
		glDisable(GL_FOG);
		glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	}
}

void OpenGLES1Renderer::setBlendingMode(int blendingMode) {
	switch(blendingMode) {
		case BLEND_MODE_NORMAL:
			glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			break;
		case BLEND_MODE_LIGHTEN:
			glBlendFunc (GL_SRC_ALPHA, GL_ONE);
			break;
		case BLEND_MODE_COLOR:
			glBlendFunc (GL_DST_COLOR, GL_ONE);
			break;
		default:
			glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			break;
	}
	glEnable(GL_BLEND);
}

Matrix4 OpenGLES1Renderer::getProjectionMatrix() {
	Number m[16];
	glGetFloatv( GL_PROJECTION_MATRIX, m);
	return Matrix4(m);
}

Matrix4 OpenGLES1Renderer::getModelviewMatrix() {
	Number m[16];
	glGetFloatv( GL_MODELVIEW_MATRIX, m);
	return Matrix4(m);
}

void OpenGLES1Renderer::renderZBufferToTexture(Texture *targetTexture) {
	//	OpenGLES1Texture *glTexture = (OpenGLES1Texture*)targetTexture;
	//	glBindTexture (GL_TEXTURE_2D, glTexture->getTextureID());
	//	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 0, 0, targetTexture->getWidth(), targetTexture->getHeight(), 0);
}

void OpenGLES1Renderer::renderToTexture(Texture *targetTexture) {
	OpenGLES1Texture *glTexture = (OpenGLES1Texture*)targetTexture;
	glBindTexture (GL_TEXTURE_2D, glTexture->getTextureID());
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0, targetTexture->getWidth(), targetTexture->getHeight(), 0);

}

void OpenGLES1Renderer::setFogProperties(int fogMode, Color color, Number density, Number startDepth, Number endDepth) {
	switch(fogMode) {
		case FOG_LINEAR:
			glFogx(GL_FOG_MODE, GL_LINEAR);
			break;
		case FOG_EXP:
			glFogx(GL_FOG_MODE, GL_EXP);
			break;
		case FOG_EXP2:
			glFogx(GL_FOG_MODE, GL_EXP2);
			break;
		default:
			glFogx(GL_FOG_MODE, GL_LINEAR);
			break;
	}

	GLfloat fogColor[4]= {color.r, color.g, color.b, color.a};
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, density);
	glHint(GL_FOG_HINT, GL_DONT_CARE);
	glFogf(GL_FOG_START, startDepth);
	glFogf(GL_FOG_END, endDepth);
	glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLES1Renderer::setOrthoMode() {
	setBlendingMode(BLEND_MODE_NORMAL);
	if(!orthoMode) {
		glDisable(GL_LIGHTING);
		glMatrixMode(GL_PROJECTION);
		glDisable(GL_CULL_FACE);
		glPushMatrix();
		glLoadIdentity();
		glOrthox(0.0f,xRes,yRes,0,-1.0f,1.0f);
		//		glOrtho(0.0f,2500.0f,2500.0f,0,-1.0f,1.0f);
		orthoMode = true;
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void OpenGLES1Renderer::enableBackfaceCulling(bool val) {
	if(val)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);
}

void OpenGLES1Renderer::setPerspectiveMode() {
	setBlendingMode(BLEND_MODE_NORMAL);
	if(orthoMode) {
		if(lightingEnabled) { // what?
		}
		glEnable (GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glMatrixMode( GL_PROJECTION );
		glPopMatrix();
		glMatrixMode( GL_MODELVIEW );
		orthoMode = false;
	}
	glLoadIdentity();

	glGetFloatv( GL_PROJECTION_MATRIX, sceneProjectionMatrix);
	currentTexture = NULL;
}

void OpenGLES1Renderer::BeginRender() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	currentTexture = NULL;
}

void OpenGLES1Renderer::setClearColor(Number r, Number g, Number b) {
	clearColor.setColor(r,g,b,1.0f);
	glClearColor(r,g,b,0.0f);
}

void OpenGLES1Renderer::translate3D(Vector3 *position) {
	glTranslatef(position->x, position->y, position->z);
}

void OpenGLES1Renderer::translate3D(Number x, Number y, Number z) {
	glTranslatef(x, y, z);
}

void OpenGLES1Renderer::scale3D(Vector3 *scale) {
	glScalef(scale->x, scale->y, scale->z);
}

void OpenGLES1Renderer::bindFrameBufferTexture(Texture *texture) {
	/*
	if(currentFrameBufferTexture) {
		previousFrameBufferTexture = currentFrameBufferTexture;
	}
	OpenGLES1Texture *glTexture = (OpenGLES1Texture*)texture;

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, glTexture->getFrameBufferID());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	currentFrameBufferTexture = texture;
	 */
}

void OpenGLES1Renderer::unbindFramebuffers() {
	/*
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	currentFrameBufferTexture = NULL;
	if(previousFrameBufferTexture) {
		bindFrameBufferTexture(previousFrameBufferTexture);
		previousFrameBufferTexture = NULL;
	}
	 */
}


void OpenGLES1Renderer::createRenderTextures(Texture **colorBuffer, Texture **depthBuffer, int width, int height) {
	/*
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
		OpenGLES1Texture *colorBufferTexture = new OpenGLES1Texture(width, height);
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

		OpenGLES1Texture *depthBufferTexture = new OpenGLES1Texture(width, height);
		depthBufferTexture->setGLInfo(depthTexture, frameBufferID);
		*depthBuffer = ((Texture*)depthBufferTexture);
	}

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
*/
}

Texture *OpenGLES1Renderer::createFramebufferTexture(unsigned int width, unsigned int height) {
	OpenGLES1Texture *newTexture = new OpenGLES1Texture(width, height);
	return newTexture;
}

Cubemap *OpenGLES1Renderer::createCubemap(Texture *t0, Texture *t1, Texture *t2, Texture *t3, Texture *t4, Texture *t5) {
//	OpenGLCubemap *newCubemap = new OpenGLCubemap(t0,t1,t2,t3,t4,t5);
//	return newCubemap;
	return NULL;
}

Texture *OpenGLES1Renderer::createTexture(unsigned int width, unsigned int height, char *textureData, bool clamp, int type) {
	OpenGLES1Texture *newTexture = new OpenGLES1Texture(width, height, textureData, clamp, textureFilteringMode);
	return newTexture;
}

void OpenGLES1Renderer::clearScreen() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLES1Renderer::applyMaterial(Material *material,  ShaderBinding *localOptions,unsigned int shaderIndex) {
	if(!material->getShader(shaderIndex) || !shadersEnabled) {
		setTexture(NULL);
		return;
	}

	FixedShaderBinding *fBinding;

	switch(material->getShader(shaderIndex)->getType()) {
		case Shader::FIXED_SHADER:
			//			FixedShader *fShader = (FixedShader*)material->getShader();
			fBinding = (FixedShaderBinding*)material->getShaderBinding(shaderIndex);
			setTexture(fBinding->getDiffuseTexture());
			//			setTexture(fShader->getDiffuseTexture());
			break;
		case Shader::CG_SHADER:
			break;
	}
}

void OpenGLES1Renderer::clearShader() {
	currentMaterial = NULL;
}

void OpenGLES1Renderer::setTexture(Texture *texture) {
	if(texture == NULL) {
		glDisable(GL_TEXTURE_2D);
		return;
	}
	
	if(renderMode == RENDER_MODE_NORMAL) {
		glEnable (GL_TEXTURE_2D);
		if(currentTexture != texture) {
			OpenGLES1Texture *glTexture = (OpenGLES1Texture*)texture;
			glBindTexture (GL_TEXTURE_2D, glTexture->getTextureID());
		}
	} else {
		glDisable(GL_TEXTURE_2D);
	}

	currentTexture = texture;
}

void OpenGLES1Renderer::beginRenderOperation(int meshType) {
	/*
	switch(meshType) {
		case Mesh::TRI_MESH:
			switch(renderMode) {
				case RENDER_MODE_NORMAL:
					Begin(GL_TRIANGLES);
					break;
				case RENDER_MODE_WIREFRAME:
					glBegin(GL_LINE_LOOP);
					break;
			}
			break;
		case Mesh::TRIFAN_MESH:
			switch(renderMode) {
				case RENDER_MODE_NORMAL:
					glBegin(GL_TRIANGLE_FAN);
					break;
				case RENDER_MODE_WIREFRAME:
					glBegin(GL_LINE_LOOP);
					break;
			}
			break;
		case Mesh::QUAD_MESH:
			switch(renderMode) {
				case RENDER_MODE_NORMAL:
					glBegin(GL_QUADS);
					break;
				case RENDER_MODE_WIREFRAME:
					glBegin(GL_LINE_LOOP);
					break;
			}
			break;
		case Mesh::LINE_MESH:
			glBegin(GL_LINES);
			break;
	}
	 */
}

void OpenGLES1Renderer::pushMatrix() {
	glPushMatrix();
}

void OpenGLES1Renderer::popMatrix() {
	glPopMatrix();
}


void OpenGLES1Renderer::endRenderOperation() {
//	glEnd();
}

void OpenGLES1Renderer::draw3DPolygon(Poly::Polygon *polygon) {
	unsigned int vCount = polygon->getVertexCount();
	for(int i=0; i < vCount; i++) {
		if(polygon->usesFaceUV())
			draw3DVertex(polygon->getVertex(i), polygon->getTexCoord(i));
		else
			draw3DVertex(polygon->getVertex(i), NULL);
	}
}

void OpenGLES1Renderer::draw3DVertex2UV(Vertex *vertex, Vector2 *faceUV1, Vector2 *faceUV2) {
	/*
	if(vertex->useVertexColor)
		glColor4f(vertex->vertexColor.r, vertex->vertexColor.g, vertex->vertexColor.b, vertex->vertexColor.a);

	if(currentTexture || currentMaterial) {
		glMultiTexCoord4x(GL_TEXTURE0, faceUV1->x, faceUV1->y,0,0);
		glMultiTexCoord4x(GL_TEXTURE1, faceUV2->x, faceUV2->y,0,0);
	}

	//	glNormal3f(vertex->normal->x, vertex->normal->y, vertex->normal->z);
	glVertex3f(vertex->x, vertex->y, vertex->z);
	 */
}

void OpenGLES1Renderer::setNormal(const Vector3 &normal) {
	glNormal3f(normal.x, normal.y, normal.z);
}

void OpenGLES1Renderer::draw3DVertex(Vertex *vertex, Vector2 *faceUV) {
	/*
	if(vertex->useVertexColor)
		glColor4f(vertex->vertexColor.r, vertex->vertexColor.g, vertex->vertexColor.b, vertex->vertexColor.a);

	if(currentTexture || currentMaterial) {
		if(faceUV != NULL)
			glTexCoord2f(faceUV->x, faceUV->y);
		else
			glTexCoord2f(vertex->getTexCoord()->x, vertex->getTexCoord()->y);
	}

	//	glNormal3f(vertex->normal->x, vertex->normal->y, vertex->normal->z);
	glVertex3f(vertex->x, vertex->y, vertex->z);
	 */
}

void OpenGLES1Renderer::drawScreenQuad(Number qx, Number qy) {
	/*
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
	 */
}

void OpenGLES1Renderer::draw2DVertex(Vertex *vertex) {
	/*
	//	glColor4f(0,0,0,0);
	if(vertex->useVertexColor)
		glColor4f(vertex->vertexColor.r, vertex->vertexColor.g, vertex->vertexColor.b, vertex->vertexColor.a);
	if(currentTexture)
		glTexCoord2f(vertex->getTexCoord()->x+currentTexture->getScrollOffsetX(), vertex->getTexCoord()->y+currentTexture->getScrollOffsetY());
	glVertex2f(vertex->x, vertex->y);
	 */
}

void OpenGLES1Renderer::draw3DLine(Vector3 origin, Vector3 direction, Number length, Color color)  {
	/*
	glColor4f(color.r,color.g,color.b,color.a);
	//	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glVertex3f(origin.x, origin.y, origin.z);

	Vector3 lineEnd = origin + (direction * length);
	glVertex3f(lineEnd.x, lineEnd.y, lineEnd.z);
	 */
}

void OpenGLES1Renderer::translate2D(Number x, Number y) {
	glTranslatef(x, y, 0.0f);
}

void OpenGLES1Renderer::scale2D(Vector2 *scale) {
	glScalef(scale->x, scale->y, 1.0f);
}

void OpenGLES1Renderer::loadIdentity() {
	setBlendingMode(BLEND_MODE_NORMAL);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void OpenGLES1Renderer::rotate2D(Number angle) {
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
}

void OpenGLES1Renderer::setVertexColor(Number r, Number g, Number b, Number a) {
	glColor4f(r,g,b,a);
}

void OpenGLES1Renderer::draw2DPolygon(Poly::Polygon *polygon) {
	unsigned int vCount = polygon->getVertexCount();
	for(int i=0; i < vCount; i++) {
		draw2DVertex(polygon->getVertex(i));
	}
}

void OpenGLES1Renderer::EndRender() {
}

OpenGLES1Renderer::~OpenGLES1Renderer() {

}
