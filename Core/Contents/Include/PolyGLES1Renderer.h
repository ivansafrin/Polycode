/*
 *  PolyGLES1Renderer.h
 *  Poly
 *
 *  Created by Ivan Safrin on 2/1/10.
 *  Copyright 2010 Ivan Safrin. All rights reserved.
 *
 */

// @package Renderer

#pragma once
#include "PolyString.h"
#include "PolyLogger.h"
#include "PolyGlobals.h"
#include "PolyRenderer.h"
#include "PolyTexture.h"
#include "PolyGLES1Texture.h"
#include "PolyCubemap.h"
#include "PolyFixedShader.h"
#include "PolyMesh.h"

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include <glu.h>

namespace Polycode {
	class _PolyExport OpenGLES1Renderer : public Renderer {
		
	public:
		
		OpenGLES1Renderer();
		virtual ~OpenGLES1Renderer();
		
		void Resize(int xRes, int yRes);
		void BeginRender();
		void EndRender();
		
		Cubemap *createCubemap(Texture *t0, Texture *t1, Texture *t2, Texture *t3, Texture *t4, Texture *t5);
		Texture *createTexture(unsigned int width, unsigned int height, char *textureData, bool clamp, int type=Image::IMAGE_RGBA);
		Texture *createFramebufferTexture(unsigned int width, unsigned int height);
		void createRenderTextures(Texture **colorBuffer, Texture **depthBuffer, int width, int height);
		
		void enableAlphaTest(bool val);
		
		void createVertexBufferForMesh(Mesh *mesh);
		void drawVertexBuffer(VertexBuffer *buffer);		
		
		void bindFrameBufferTexture(Texture *texture);
		void unbindFramebuffers();
		
		void setOrthoMode();
		void setPerspectiveMode();
		
		void enableBackfaceCulling(bool val);
		void setViewportSize(int w, int h, Number fov=45.0f);
		
		void setLineSmooth(bool val);		
		
		void loadIdentity();
		void setClearColor(Number r, Number g, Number b);
		
		void setTexture(Texture *texture);		
		void draw2DPolygon(Polygon *polygon);
		void draw2DVertex(Vertex *vertex);
		
		void renderToTexture(Texture *targetTexture);		
		void renderZBufferToTexture(Texture *targetTexture);
		void clearScreen();	
		
		void translate2D(Number x, Number y);
		void rotate2D(Number angle);
		void scale2D(Vector2 *scale);
		
		void setLineSize(Number lineSize);
		
		void setVertexColor(Number r, Number g, Number b, Number a);
		
		void setBlendingMode(int blendingMode);
		
		void enableLighting(bool enable);	
		void enableFog(bool enable);
		void setFogProperties(int fogMode, Color color, Number density, Number startDepth, Number endDepth);		
		
		void draw3DPolygon(Polygon *polygon);
		void draw3DVertex(Vertex *vertex, Vector2 *faceUV);
		void draw3DVertex2UV(Vertex *vertex, Vector2 *faceUV1, Vector2 *faceUV2);
		void draw3DLine(Vector3 origin, Vector3 direction, Number length, Color color);
		
		virtual void setNormal(const Vector3 &normal);
		
		void translate3D(Vector3 *position);
		void translate3D(Number x, Number y, Number z);
		void scale3D(Vector3 *scale);
		
		Matrix4 getProjectionMatrix();
		Matrix4 getModelviewMatrix();		
		void setModelviewMatrix(Matrix4 m);	
		void multModelviewMatrix(Matrix4 m);
		
		void enableDepthTest(bool val);		
		void drawScreenQuad(Number qx, Number qy);
		
		void beginRenderOperation(int meshType);
		void endRenderOperation();
		
		void pushMatrix();
		void popMatrix();
		
		bool test2DCoordinate(Number x, Number y, Polygon *poly, const Matrix4 &matrix, bool billboardMode);
		
		void setFOV(Number fov);
		
		Vector3 Unproject(Number x, Number y);
		
		void clearShader();
		void applyMaterial(Material *material,  ShaderBinding *localOptions, unsigned int shaderIndex);
		
	private:
				
		GLuint defaultFramebuffer, colorRenderbuffer;		
		
		Number nearPlane;
		Number farPlane;
		
		GLfloat sceneProjectionMatrix[16];
		
		
	};
}

