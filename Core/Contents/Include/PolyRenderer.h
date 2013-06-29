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
#include "PolyGlobals.h"
#include "PolyMatrix4.h"
#include "PolyVector2.h"
#include "PolyShader.h"
#include "PolyImage.h"
#include "PolyRectangle.h"

namespace Polycode {

class Cubemap;
class Material;
class Mesh;
class PolycodeShaderBinding;
class PolycodeShaderModule;
class Polygon;
class RenderDataArray;
class ShaderBinding;
class Texture;
class VertexBuffer;

class _PolyExport LightInfo : public PolyBase {
	public:
		Vector3 position;
		Vector3 color;
		Color specularColor;
		Vector3 dir;
		Number constantAttenuation;
		Number linearAttenuation;
		Number quadraticAttenuation;
		Number intensity;
		Number spotlightCutoff;
		Number spotlightExponent;
		int type;
		bool shadowsEnabled;
		Matrix4 textureMatrix;
		Texture* shadowMapTexture;
		int lightImportance;
};

class _PolyExport LightSorter : public PolyBase {
	public:
		Vector3 basePosition;
		Matrix4 cameraMatrix;
		bool operator() (LightInfo i,LightInfo j) {
			if(i.lightImportance > j.lightImportance)
				return true;
			if(i.lightImportance == j.lightImportance)
				return ((cameraMatrix*i.position).distance(basePosition)<(cameraMatrix*j.position).distance(basePosition));
			return false; 
		}
};

/**
* Provides low-level settings for the main renderer.
*
* The methods and settings in this class are closely related to OpenGL.
* If you have trouble understanding anything in this class, it is thus suggested to brush up on your OpenGL knowledge.
*
* The renderer should only be accessed from the CoreServices singleton. Renderer operations should only be called from within Render methods of entities so that they can be properly managed.
*
* @see http://www.glprogramming.com/red/
* @see http://nehe.gamedev.net/tutorial/lessons_01__05/22004/
*/
class _PolyExport Renderer : public PolyBase {
	public:
		Renderer();
		virtual ~Renderer();

		virtual void Resize(int xRes, int yRes) = 0;

		virtual void BeginRender() = 0;
		virtual void EndRender() = 0;

		virtual Cubemap *createCubemap(Texture *t0, Texture *t1, Texture *t2, Texture *t3, Texture *t4, Texture *t5) = 0;
		virtual Texture *createTexture(unsigned int width, unsigned int height, char *textureData, bool clamp, bool createMipmaps, int type=Image::IMAGE_RGBA) = 0;
		virtual void destroyTexture(Texture *texture) = 0;
		virtual void createRenderTextures(Texture **colorBuffer, Texture **depthBuffer, int width, int height, bool floatingPointBuffer) = 0;

		virtual Texture *createFramebufferTexture(unsigned int width, unsigned int height) = 0;
		virtual void bindFrameBufferTexture(Texture *texture) = 0;
		virtual void bindFrameBufferTextureDepth(Texture *texture) = 0;
		virtual void unbindFramebuffers() = 0;

		virtual Image *renderScreenToImage() = 0;

		void setFOV(Number fov);
		void setViewportSize(int w, int h);
		void setViewportSizeAndFOV(int w, int h, Number fov);
		virtual void resetViewport() = 0;

		virtual void loadIdentity() = 0;
		virtual void setOrthoMode(Number xSize=0.0f, Number ySize=0.0f, bool centered = false) = 0;
		virtual void _setOrthoMode(Number orthoSizeX, Number orthoSizeY) = 0;
		virtual void setPerspectiveMode() = 0;

		virtual void setTexture(Texture *texture) = 0;
		virtual void enableBackfaceCulling(bool val) = 0;

		virtual void setClearColor(Number r, Number g, Number b, Number a = 1.0);
		virtual void setClearColor(Color color);

		virtual void setAmbientColor(Number r, Number g, Number b);

		virtual void clearScreen() = 0;

		virtual void translate2D(Number x, Number y) = 0;
		virtual void rotate2D(Number angle) = 0;
		virtual void scale2D(Vector2 *scale) = 0;


		virtual void setVertexColor(Number r, Number g, Number b, Number a) = 0;

		void pushDataArrayForMesh(Mesh *mesh, int arrayType);

		virtual void pushRenderDataArray(RenderDataArray *array) = 0;
		virtual RenderDataArray *createRenderDataArrayForMesh(Mesh *mesh, int arrayType) = 0;
		virtual RenderDataArray *createRenderDataArray(int arrayType) = 0;
		virtual void setRenderArrayData(RenderDataArray *array, Number *arrayData) = 0;
		virtual void drawArrays(int drawType) = 0;

		virtual void translate3D(Vector3 *position) = 0;
		virtual void translate3D(Number x, Number y, Number z) = 0;
		virtual void scale3D(Vector3 *scale) = 0;

		virtual void pushMatrix() = 0;
		virtual void popMatrix() = 0;

		virtual void setLineSmooth(bool val) = 0;
		virtual void setLineSize(Number lineSize) = 0;

		virtual void enableLighting(bool enable) = 0;

		virtual void enableFog(bool enable) = 0;
		virtual void setFogProperties(int fogMode, Color color, Number density, Number startDepth, Number endDepth) = 0;

		virtual void multModelviewMatrix(Matrix4 m) = 0;
		virtual void setModelviewMatrix(Matrix4 m) = 0;

		void setCurrentModelMatrix(Matrix4 m) { currentModelMatrix = m; }
		Matrix4 getCurrentModelMatrix() { return currentModelMatrix; }

		virtual void setBlendingMode(int blendingMode) = 0;

		virtual void applyMaterial(Material *material, ShaderBinding *localOptions, unsigned int shaderIndex) = 0;
		virtual void clearShader() = 0;

		virtual void setDepthFunction(int depthFunction) = 0;

		virtual void createVertexBufferForMesh(Mesh *mesh) = 0;
		virtual void drawVertexBuffer(VertexBuffer *buffer, bool enableColorBuffer) = 0;

		void setRenderMode(int newRenderMode);
		int getRenderMode();

		virtual void enableDepthTest(bool val) = 0;
		virtual void enableDepthWrite(bool val) = 0;

		void billboardMatrix();
		void billboardMatrixWithScale(Vector3 scale);

		void setTextureFilteringMode(int mode);

		/**
		 * Set the near and far clipping planes for the visible frustum.
		 *
		 * Please check the supplied external links for more information
		 * about the problems of a high farPlane/nearPlane setting.
		 *
		 * @param nearPlane The new near clipping plane.
		 * @param farPlane The new far clipping plane.
		 *
		 * @see http://en.wikipedia.org/wiki/Viewing_frustum
		 * @see http://www.opengl.org/sdk/docs/man2/xhtml/glFrustum.xml
		 */
		virtual void setClippingPlanes(Number nearPlane, Number farPlane) = 0;

		/**
		 * Enable/disable alpha tests.
		 *
		 * If alpha tests are enabled, drawn pixels of textures will
		 * be "mixed" with framebuffer pixels based on the drawn pixel's
		 * alpha value. If alpha tests are disabled, they will be drawn
		 * as solid color.
		 *
		 * @param val Whether to enable or disable alpha tests.
		 */
		virtual void enableAlphaTest(bool val) = 0;

		virtual void clearBuffer(bool colorBuffer, bool depthBuffer) = 0;
		virtual void drawToColorBuffer(bool val) = 0;

		const Matrix4& getCameraMatrix() const;
		void setCameraMatrix(const Matrix4& matrix);
		void setCameraPosition(Vector3 pos);

		virtual void drawScreenQuad(Number qx, Number qy) = 0;

		int getXRes();
		int getYRes();

		bool isScissorEnabled();

		virtual void enableScissor(bool val);
		virtual void setScissorBox(Polycode::Rectangle box);

		Polycode::Rectangle getScissorBox();

		void setAnisotropyAmount(Number amount);
		Number getAnisotropyAmount();

		virtual void cullFrontFaces(bool val) = 0;

		void clearLights();
		void addLight(int lightImportance, Vector3 position, Vector3 direction, int type, Color color, Color specularColor, Number constantAttenuation, Number linearAttenuation, Number quadraticAttenuation, Number intensity, Number spotlightCutoff, Number spotlightExponent, bool shadowsEnabled, Matrix4 *textureMatrix, Texture *shadowMapTexture);

		void setExposureLevel(Number level);

		bool rayTriangleIntersect(Vector3 ray_origin, Vector3 ray_direction, Vector3 vert0, Vector3 vert1, Vector3 vert2, Vector3 *hitPoint);

		virtual Vector3 projectRayFrom2DCoordinate(Number x, Number y) = 0;

		void enableShaders(bool flag);

		Number getViewportWidth();
		Number getViewportHeight();

		void *getDataPointerForName(const String &name);
		void setRendererShaderParams(Shader *shader, ShaderBinding *binding);

		virtual void initOSSpecific() {};

		void addShaderModule(PolycodeShaderModule *module);

		virtual bool test2DCoordinateInPolygon(Number x, Number y, Polygon *poly, const Matrix4 &matrix, bool ortho, bool testBackfacing, bool billboardMode, bool reverseDirection = false, Matrix4 *adjustMatrix = NULL);

		virtual Matrix4 getProjectionMatrix() = 0;
		virtual Matrix4 getModelviewMatrix() = 0;

		static const int RENDER_MODE_NORMAL = 0;
		static const int RENDER_MODE_WIREFRAME = 1;

		static const int BLEND_MODE_NORMAL = 0;
		static const int BLEND_MODE_LIGHTEN = 1;
		static const int BLEND_MODE_COLOR = 2;
		static const int BLEND_MODE_PREMULTIPLIED = 3;
		static const int BLEND_MODE_MULTIPLY = 4;

		static const int FOG_LINEAR = 0;
		static const int FOG_EXP = 1;
		static const int FOG_EXP2 = 2;

		static const int DEPTH_FUNCTION_GREATER = 0;
		static const int DEPTH_FUNCTION_LEQUAL = 1;

		static const int TEX_FILTERING_NEAREST = 0;
		static const int TEX_FILTERING_LINEAR = 1;

	//		void addShadowMap(Texture *texture);
	//		vector<Texture*> getShadowMapTextures(){ return shadowMapTextures; };

		virtual Vector3 Unproject(Number x, Number y) = 0;

		Color	ambientColor;
		Color	clearColor;
		Number exposureLevel;
		Vector3 cameraPosition;

		void sortLights();

		int getNumAreaLights() { return numAreaLights; }
		int getNumSpotLights() { return numSpotLights; }
		int getNumLights() { return numLights; }

		std::vector<LightInfo> getAreaLights() { return areaLights; }
		std::vector<LightInfo> getSpotLights() { return spotLights; }

		bool doClearBuffer;

		bool blendNormalAsPremultiplied;

	protected:

		bool scissorEnabled;
		
		Polycode::Rectangle scissorBox;

		Number anisotropy;
		Matrix4 currentModelMatrix;
		LightSorter sorter;

		Number viewportWidth;
		Number viewportHeight;

		bool cullingFrontFaces;

		Texture *currentTexture;
		Material *currentMaterial;

		int textureFilteringMode;
		int renderMode;

		Matrix4 cameraMatrix;

		PolycodeShaderModule* currentShaderModule;
		std::vector <PolycodeShaderModule*> shaderModules;

		std::vector<LightInfo> lights;
		std::vector<LightInfo> areaLights;
		std::vector<LightInfo> spotLights;
		int numLights;
		int numAreaLights;
		int numSpotLights;

		bool shadersEnabled;
		Number fov;

		Number orthoSizeX;
		Number orthoSizeY;

		bool lightingEnabled;

		bool orthoMode;

		int xRes;
		int yRes;
};

}
