/*
 *  PolyRenderer.h
 *  TAU
 *
 *  Created by Ivan Safrin on 3/12/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

// @package Renderer

#pragma once
#include "PolyGlobals.h"
#include "PolyColor.h"
#include "PolyPolygon.h"
#include "PolyMesh.h"
#include "PolyTexture.h"
#include "PolyCubemap.h"
#include "PolyMaterial.h"
#include "PolyModule.h"
#include "PolyVector3.h"
#include "PolyQuaternion.h"
#include "PolyMatrix4.h"

namespace Polycode {
	
	class Texture;

	class _PolyExport LightInfo {
		public:
			Vector3 position;
			Vector3 color;
			Vector3 dir;
			float distance;
			float intensity;
			int type;
			Matrix4 textureMatrix;
	};

	class _PolyExport Renderer {
	public:
		Renderer();
		virtual ~Renderer();
		
		virtual void Resize(int xRes, int yRes) = 0;
		
		virtual void BeginRender() = 0;
		virtual void EndRender() = 0;
		
		virtual Cubemap *createCubemap(Texture *t0, Texture *t1, Texture *t2, Texture *t3, Texture *t4, Texture *t5) = 0;		
		virtual Texture *createTexture(unsigned int width, unsigned int height, char *textureData, bool clamp, int type=Image::IMAGE_RGBA) = 0;
		virtual void createRenderTextures(Texture **colorBuffer, Texture **depthBuffer, int width, int height) = 0;
		
		virtual Texture *createFramebufferTexture(unsigned int width, unsigned int height) = 0;
		virtual void bindFrameBufferTexture(Texture *texture) = 0;
		virtual void unbindFramebuffers() = 0;
		
		virtual void renderToTexture(Texture *targetTexture) = 0;
		virtual void renderZBufferToTexture(Texture *targetTexture) = 0;
		virtual void setViewportSize(int w, int h, float fov=45.0f) = 0;
		
		virtual void loadIdentity() = 0;		
		virtual void setOrthoMode() = 0;
		virtual void setPerspectiveMode() = 0;
		
		virtual void setTexture(Texture *texture) = 0;		
		virtual void enableBackfaceCulling(bool val) = 0;
		
		virtual void setClearColor(float r, float g, float b) = 0;
		virtual void setClearColor(Color color);
		
		virtual void setAmbientColor(float r, float g, float b);
		
		virtual void clearScreen() = 0;
		
		virtual void translate2D(float x, float y) = 0;
		virtual void rotate2D(float angle) = 0;
		virtual void scale2D(Vector2 *scale) = 0;
		
		virtual void setFOV(float fov) = 0;		
		
		virtual void setVertexColor(float r, float g, float b, float a) = 0;
		
		void pushDataArrayForMesh(Mesh *mesh, int arrayType);
		
		virtual void pushRenderDataArray(RenderDataArray *array) = 0;
		virtual RenderDataArray *createRenderDataArrayForMesh(Mesh *mesh, int arrayType) = 0;
		virtual RenderDataArray *createRenderDataArray(int arrayType) = 0;
		virtual void setRenderArrayData(RenderDataArray *array, float *arrayData) = 0;
		virtual void drawArrays(int drawType) = 0;
		
		virtual void translate3D(Vector3 *position) = 0;
		virtual void translate3D(float x, float y, float z) = 0;
		virtual void scale3D(Vector3 *scale) = 0;
		
		virtual void pushMatrix() = 0;
		virtual void popMatrix() = 0;
		
		virtual void setLineSmooth(bool val) = 0;
		virtual void setLineSize(float lineSize) = 0;
		
		virtual void enableLighting(bool enable) = 0;
			
		virtual void enableFog(bool enable) = 0;
		virtual void setFogProperties(int fogMode, Color color, float density, float startDepth, float endDepth) = 0;
				
		virtual void multModelviewMatrix(Matrix4 m) = 0;
		virtual void setModelviewMatrix(Matrix4 m) = 0;
		
		virtual void setBlendingMode(int blendingMode) = 0;	
			
		virtual void applyMaterial(Material *material, ShaderBinding *localOptions, unsigned int shaderIndex) = 0;
		virtual void clearShader() = 0;
		
		virtual void setDepthFunction(int depthFunction) = 0;
				
		virtual void createVertexBufferForMesh(Mesh *mesh) = 0;
		virtual void drawVertexBuffer(VertexBuffer *buffer) = 0;
		
		void setRenderMode(int newRenderMode);
		int getRenderMode();
		
		virtual void enableDepthTest(bool val) = 0;
		
		void billboardMatrix();
		void billboardMatrixWithScale(Vector3 scale);
		
		void setTextureFilteringMode(int mode);
		
		virtual void enableAlphaTest(bool val) = 0;
		
		virtual void clearBuffer(bool colorBuffer, bool depthBuffer) = 0;
		virtual void drawToColorBuffer(bool val) = 0;
		
		Matrix4 getCameraMatrix();
		void setCameraMatrix(Matrix4 matrix);
		void setCameraPosition(Vector3 pos);
		
		virtual void drawScreenQuad(float qx, float qy) = 0;
		
		int getXRes();
		int getYRes();
		
		void clearLights();
		void addLight(Vector3 position, Vector3 direction, int type, Color color, float distance, float intensity, Matrix4 *textureMatrix);
		
		void setExposureLevel(float level);
		
		bool rayTriangleIntersect(Vector3 ray_origin, Vector3 ray_direction, Vector3 vert0, Vector3 vert1, Vector3 vert2, Vector3 *hitPoint);
		
		void enableShaders(bool flag);
		
		void addShaderModule(PolycodeShaderModule *module);
		
		virtual bool test2DCoordinate(float x, float y, Polygon *poly, const Matrix4 &matrix, bool billboardMode) = 0;
		
		virtual Matrix4 getProjectionMatrix() = 0;
		virtual Matrix4 getModelviewMatrix() = 0;
		
		static const int RENDER_MODE_NORMAL = 0;
		static const int RENDER_MODE_WIREFRAME = 1;
		
		static const int BLEND_MODE_NORMAL = 0;
		static const int BLEND_MODE_LIGHTEN = 1;
		static const int BLEND_MODE_COLOR = 2;
		
		static const int FOG_LINEAR = 0;
		static const int FOG_EXP = 1;
		static const int FOG_EXP2 = 2;
		
		static const int DEPTH_FUNCTION_GREATER = 0;
		static const int DEPTH_FUNCTION_LEQUAL = 1;	
		
		static const int TEX_FILTERING_NEAREST = 0;
		static const int TEX_FILTERING_LINEAR = 1;
		
		void addShadowMap(Texture *texture);
		vector<Texture*> getShadowMapTextures(){ return shadowMapTextures; };
		
		virtual Vector3 Unproject(float x, float y) = 0;
		
		Color	ambientColor;
		Color	clearColor;		
		float exposureLevel;		
		Vector3 cameraPosition;
		
		int getNumAreaLights() { return numAreaLights; }
		int getNumSpotLights() { return numSpotLights; }
		int getNumLights() { return numLights; }
		
		vector<LightInfo> getAreaLights() { return areaLights; }
		vector<LightInfo> getSpotLights() { return spotLights;	}
		
	protected:
	
				
		Texture *currentTexture;
		Material *currentMaterial;
		
		vector<Texture*> shadowMapTextures;
		
		Texture *currentFrameBufferTexture;
		Texture *previousFrameBufferTexture;
			
		int textureFilteringMode;
		int renderMode;
		
		Matrix4 cameraMatrix;
	
		PolycodeShaderModule* currentShaderModule;
		vector <PolycodeShaderModule*> shaderModules;

		vector<LightInfo> lights;
		vector<LightInfo> areaLights;
		vector<LightInfo> spotLights;		
		int numLights;
		int numAreaLights;
		int numSpotLights;
		
		bool shadersEnabled;
		float fov;
		
		bool lightingEnabled;
		
		bool orthoMode;
	
		int xRes;
		int yRes;
	};
}