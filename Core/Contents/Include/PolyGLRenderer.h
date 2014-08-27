    
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
#include "PolyGlobals.h"
#include "PolyRenderer.h"

#ifdef _WINDOWS
#include <windows.h>
#endif

#include "PolyGLHeaders.h"
/*
#ifdef _WINDOWS 
#define GL_EXT_framebuffer_object           1

#if GL_EXT_framebuffer_object
#define GL_FRAMEBUFFER_EXT                 0x8D40
#define GL_RENDERBUFFER_EXT                0x8D41
#define GL_STENCIL_INDEX1_EXT              0x8D46
#define GL_STENCIL_INDEX4_EXT              0x8D47
#define GL_STENCIL_INDEX8_EXT              0x8D48
#define GL_STENCIL_INDEX16_EXT             0x8D49
#define GL_RENDERBUFFER_WIDTH_EXT           0x8D42
#define GL_RENDERBUFFER_HEIGHT_EXT          0x8D43
#define GL_RENDERBUFFER_INTERNAL_FORMAT_EXT 0x8D44
#define GL_RENDERBUFFER_RED_SIZE_EXT        0x8D50
#define GL_RENDERBUFFER_GREEN_SIZE_EXT      0x8D51
#define GL_RENDERBUFFER_BLUE_SIZE_EXT       0x8D52
#define GL_RENDERBUFFER_ALPHA_SIZE_EXT      0x8D53
#define GL_RENDERBUFFER_DEPTH_SIZE_EXT      0x8D54
#define GL_RENDERBUFFER_STENCIL_SIZE_EXT    0x8D55
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_EXT           0x8CD0
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_EXT           0x8CD1
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_EXT         0x8CD2
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_EXT 0x8CD3
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_3D_ZOFFSET_EXT    0x8CD4
#define GL_COLOR_ATTACHMENT0_EXT           0x8CE0
#define GL_COLOR_ATTACHMENT1_EXT           0x8CE1
#define GL_COLOR_ATTACHMENT2_EXT           0x8CE2
#define GL_COLOR_ATTACHMENT3_EXT           0x8CE3
#define GL_COLOR_ATTACHMENT4_EXT           0x8CE4
#define GL_COLOR_ATTACHMENT5_EXT           0x8CE5
#define GL_COLOR_ATTACHMENT6_EXT           0x8CE6
#define GL_COLOR_ATTACHMENT7_EXT           0x8CE7
#define GL_COLOR_ATTACHMENT8_EXT           0x8CE8
#define GL_COLOR_ATTACHMENT9_EXT           0x8CE9
#define GL_COLOR_ATTACHMENT10_EXT          0x8CEA
#define GL_COLOR_ATTACHMENT11_EXT          0x8CEB
#define GL_COLOR_ATTACHMENT12_EXT          0x8CEC
#define GL_COLOR_ATTACHMENT13_EXT          0x8CED
#define GL_COLOR_ATTACHMENT14_EXT          0x8CEE
#define GL_COLOR_ATTACHMENT15_EXT          0x8CEF
#define GL_DEPTH_ATTACHMENT_EXT            0x8D00
#define GL_STENCIL_ATTACHMENT_EXT          0x8D20
#define GL_FRAMEBUFFER_COMPLETE_EXT                        0x8CD5
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT           0x8CD6
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT   0x8CD7
#define GL_FRAMEBUFFER_INCOMPLETE_DUPLICATE_ATTACHMENT_EXT 0x8CD8
#define GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT           0x8CD9
#define GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT              0x8CDA
#define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT          0x8CDB
#define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT          0x8CDC
#define GL_FRAMEBUFFER_UNSUPPORTED_EXT                     0x8CDD
#define GL_FRAMEBUFFER_BINDING_EXT         0x8CA6
#define GL_RENDERBUFFER_BINDING_EXT        0x8CA7
#define GL_MAX_COLOR_ATTACHMENTS_EXT       0x8CDF
#define GL_MAX_RENDERBUFFER_SIZE_EXT       0x84E8
#define GL_INVALID_FRAMEBUFFER_OPERATION_EXT 0x0506

#endif
#endif
*/

namespace Polycode {
	class _PolyExport OpenGLRenderer : public Renderer {
		
	public:
		
		OpenGLRenderer();
		~OpenGLRenderer();

		bool Init();
		
		void Resize(int xRes, int yRes);
		void BeginRender();
		void EndRender();
		
		Cubemap *createCubemap(Texture *t0, Texture *t1, Texture *t2, Texture *t3, Texture *t4, Texture *t5);
		Texture *createTexture(unsigned int width, unsigned int height, char *textureData, bool clamp, bool createMipmaps, int type = Image::IMAGE_RGBA);
		void destroyTexture(Texture *texture);		
		Texture *createFramebufferTexture(unsigned int width, unsigned int height);
		void createRenderTextures(Texture **colorBuffer, Texture **depthBuffer, int width, int height, bool floatingPointBuffer);
		
		void enableAlphaTest(bool val);
		
		void createVertexBufferForMesh(Mesh *mesh);
		void drawVertexBuffer(VertexBuffer *buffer, bool enableColorBuffer);						
		void bindFrameBufferTexture(Texture *texture);
		void bindFrameBufferTextureDepth(Texture *texture);		
		void unbindFramebuffers();
		
		Vector2 Project(const Matrix4 &cameraMatrix, const Matrix4 &projectionMatrix, const Polycode::Rectangle &viewport, const Vector3 &coordiante) const;
		
		void cullFrontFaces(bool val);
				
		void pushRenderDataArray(RenderDataArray *array);
		void drawArrays(int drawType, IndexDataArray *indexArray);
				
		void setProjectionOrtho(Number xSize=0.0f, Number ySize=0.0f, Number near=-256.0f, Number far=256.0f, bool centered = false);
        void setProjectionMatrix(Matrix4 matrix);
		void setPerspectiveDefaults();
		
		void enableBackfaceCulling(bool val);
		
		void resetViewport();
		
		void setLineSmooth(bool val);		
		
		void loadIdentity();
		
		void setTexture(Texture *texture);		

		Image *renderScreenToImage();
		Image *renderBufferToImage(Texture *texture);
		void clearScreen(bool clearColor = true, bool clearDepth = true);
		
		void translate2D(Number x, Number y);
		void rotate2D(Number angle);
		void scale2D(const Vector2 &scale);
		
		void enableScissor(bool val);
		void setScissorBox(Polycode::Rectangle box);		
		
		Vector3 projectRayFrom2DCoordinate(Number x, Number y, const Matrix4 &cameraMatrix, const Matrix4 &projectionMatrix, const Polycode::Rectangle &viewport);
		Polycode::Rectangle getViewport();
		
		void setLineSize(Number lineSize);
		void setPointSize(Number pointSize);
		void setPointSmooth(bool val);
				
		void setVertexColor(Number r, Number g, Number b, Number a);
		
		void setBlendingMode(int blendingMode);
		
		void enableLighting(bool enable);	
		void enableFog(bool enable);
		void setFogProperties(int fogMode, Color color, Number density, Number startDepth, Number endDepth);		
				
		void translate3D(const Vector3 &position);
		void translate3D(Number x, Number y, Number z);
		void scale3D(const Vector3 &scale);
		
		Matrix4 getProjectionMatrix();
		Matrix4 getModelviewMatrix();		
		void setModelviewMatrix(Matrix4 m);	
		void multModelviewMatrix(Matrix4 m);
		
        void setWireframePolygonMode(bool val);
		
		void enableDepthTest(bool val);
		void enableDepthWrite(bool val);
				
		void setProjectionFromFrustum(Number left, Number right, Number bottom, Number top, Number near, Number far);
		void setProjectionFromFoV(Number fov, Number near, Number far);

		void clearBuffer(bool colorBuffer, bool depthBuffer);	
		void drawToColorBuffer(bool val);
		
		void drawScreenQuad(Number qx, Number qy);
				
		void pushMatrix();
		void popMatrix();		
		
		Vector3 Unproject(Number x, Number y, const Matrix4 &cameraMatrix, const Matrix4 &projectionMatrix, const Polycode::Rectangle &viewport);
		
		void setDepthFunction(int depthFunction);
						
		void clearShader();
		
	protected:
		void initOSSpecific();
		
		int verticesToDraw;
		
		GLdouble sceneProjectionMatrix[16];
		GLdouble sceneProjectionMatrixOrtho[16];	
		
	};
}

