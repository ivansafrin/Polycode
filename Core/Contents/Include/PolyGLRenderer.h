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


#pragma once
#include "PolyString.h"
#include "PolyLogger.h"
#include "PolyGlobals.h"
#include "PolyRenderer.h"
#include "PolyTexture.h"
#include "PolyGLTexture.h"
#include "PolyCubemap.h"
#include "PolyGLCubemap.h"
#include "PolyGLVertexBuffer.h"
#include "PolyFixedShader.h"
#include "PolyMesh.h"

#ifdef _WINDOWS
	#include <windows.h>
#endif

#include "PolyGLHeaders.h"

namespace Polycode {
	class _PolyExport OpenGLRenderer : public Renderer {
		
	public:
		
		OpenGLRenderer();
		~OpenGLRenderer();
		
		void Resize(int xRes, int yRes);
		void BeginRender();
		void EndRender();
		
		Cubemap *createCubemap(Texture *t0, Texture *t1, Texture *t2, Texture *t3, Texture *t4, Texture *t5);
		Texture *createTexture(unsigned int width, unsigned int height, char *textureData, bool clamp, int type = Image::IMAGE_RGBA);
		Texture *createFramebufferTexture(unsigned int width, unsigned int height);
		void createRenderTextures(Texture **colorBuffer, Texture **depthBuffer, int width, int height);
		
		void enableAlphaTest(bool val);
		
		void createVertexBufferForMesh(Mesh *mesh);
		void drawVertexBuffer(VertexBuffer *buffer);						
		void bindFrameBufferTexture(Texture *texture);
		void unbindFramebuffers();
		
		void cullFrontFaces(bool val);
				
		void pushRenderDataArray(RenderDataArray *array);
		RenderDataArray *createRenderDataArrayForMesh(Mesh *mesh, int arrayType);
		RenderDataArray *createRenderDataArray(int arrayType);
		void setRenderArrayData(RenderDataArray *array, Number *arrayData);
		void drawArrays(int drawType);		
				
		void setOrthoMode(Number xSize=0.0f, Number ySize=0.0f);
		void _setOrthoMode();
		void setPerspectiveMode();
		
		void enableBackfaceCulling(bool val);
		void setViewportSize(int w, int h, Number fov=45.0f);
		
		void setLineSmooth(bool val);		
		
		void loadIdentity();
		void setClearColor(Number r, Number g, Number b);
		
		void setTexture(Texture *texture);		
		
		void renderToTexture(Texture *targetTexture);		
		void renderZBufferToTexture(Texture *targetTexture);
		void clearScreen();	
		
		void translate2D(Number x, Number y);
		void rotate2D(Number angle);
		void scale2D(Vector2 *scale);

		void initOSSpecific();
		
		void setLineSize(Number lineSize);
		
		void setVertexColor(Number r, Number g, Number b, Number a);
		
		void setBlendingMode(int blendingMode);
		
		void enableLighting(bool enable);	
		void enableFog(bool enable);
		void setFogProperties(int fogMode, Color color, Number density, Number startDepth, Number endDepth);		
				
		void translate3D(Vector3 *position);
		void translate3D(Number x, Number y, Number z);
		void scale3D(Vector3 *scale);
		
		Matrix4 getProjectionMatrix();
		Matrix4 getModelviewMatrix();		
		void setModelviewMatrix(Matrix4 m);	
		void multModelviewMatrix(Matrix4 m);
		
		void enableDepthTest(bool val);
		void enableDepthWrite(bool val);
				
		void setClippingPlanes(Number near, Number far);
				
		void clearBuffer(bool colorBuffer, bool depthBuffer);	
		void drawToColorBuffer(bool val);
		
		void drawScreenQuad(Number qx, Number qy);
				
		void pushMatrix();
		void popMatrix();
		
		bool test2DCoordinate(Number x, Number y, Polycode::Polygon *poly, const Matrix4 &matrix, bool billboardMode);
		
		void setFOV(Number fov);
		
		Vector3 Unproject(Number x, Number y);
		
		void setDepthFunction(int depthFunction);
						
		void clearShader();
		void applyMaterial(Material *material,  ShaderBinding *localOptions, unsigned int shaderIndex);
		
	protected:

		
		Number nearPlane;
		Number farPlane;
		
		int verticesToDraw;
		
		GLdouble sceneProjectionMatrix[16];
	
		
	};
}

