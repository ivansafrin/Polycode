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
#include <stack>

namespace Polycode {
	
	class Cubemap;
	class Material;
	class Mesh;
	class PolycodeShaderBinding;
	class PolycodeShaderModule;
	class Polygon;
	class RenderDataArray;
    class IndexDataArray;
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
			bool operator() (LightInfo i,LightInfo j) {                
				if(i.lightImportance > j.lightImportance)
					return true;
				if(i.lightImportance == j.lightImportance)
					return i.position.distance(basePosition) < j.position.distance(basePosition);
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
	*/
	class _PolyExport Renderer : public PolyBase {
	public:
		Renderer();
		virtual ~Renderer();
		
		virtual bool Init();

		virtual void Resize(int xRes, int yRes) = 0;
		
        virtual void BeginRender();
        virtual void EndRender();
		
		virtual Cubemap *createCubemap(Texture *t0, Texture *t1, Texture *t2, Texture *t3, Texture *t4, Texture *t5) = 0;		
		virtual Texture *createTexture(unsigned int width, unsigned int height, char *textureData, bool clamp, bool createMipmaps, int type=Image::IMAGE_RGBA) = 0;
		virtual void destroyTexture(Texture *texture) = 0;
		virtual void createRenderTextures(Texture **colorBuffer, Texture **depthBuffer, int width, int height, bool floatingPointBuffer) = 0;
		
		virtual Texture *createFramebufferTexture(unsigned int width, unsigned int height) = 0;
		virtual void bindFrameBufferTexture(Texture *texture);
		virtual void bindFrameBufferTextureDepth(Texture *texture);
		virtual void unbindFramebuffers();

		virtual Image *renderScreenToImage() = 0;
		virtual Image *renderBufferToImage(Texture *texture) = 0;
		
		void setViewportSize(int w, int h);
		virtual void resetViewport() = 0;
		
		virtual Polycode::Rectangle getViewport() = 0;
				
		virtual void loadIdentity() = 0;		
		virtual void setProjectionOrtho(Number xSize=0.0f, Number ySize=0.0f, Number near=-256.0f, Number far=256.0f, bool centered = false) = 0;
		virtual void setPerspectiveDefaults() = 0;
        virtual void setProjectionMatrix(Matrix4 matrix) = 0;
		
		virtual void setTexture(Texture *texture) = 0;		
		virtual void enableBackfaceCulling(bool val) = 0;
		
		virtual void setClearColor(Number r, Number g, Number b, Number a = 1.0);
		virtual void setClearColor(Color color);
		
		virtual void setAmbientColor(Number r, Number g, Number b);
		
		virtual void clearScreen(bool clearColor = true, bool clearDepth = true) = 0;
		
		virtual void translate2D(Number x, Number y) = 0;
		virtual void rotate2D(Number angle) = 0;
		virtual void scale2D(const Vector2 &scale) = 0;
			
		
		virtual void setVertexColor(Number r, Number g, Number b, Number a) = 0;
				
		virtual void pushRenderDataArray(RenderDataArray *array) = 0;
		virtual void drawArrays(int drawType, IndexDataArray *indexArray) = 0;
		
		virtual void translate3D(const Vector3 &position) = 0;
		virtual void translate3D(Number x, Number y, Number z) = 0;
		virtual void scale3D(const Vector3 &scale) = 0;
		
		virtual void pushMatrix() = 0;
		virtual void popMatrix() = 0;
		
		virtual void setLineSmooth(bool val) = 0;
		virtual void setLineSize(Number lineSize) = 0;
		virtual void setPointSize(Number pointSize) = 0;
		virtual void setPointSmooth(bool val) = 0;
				
		virtual void enableLighting(bool enable) = 0;
			
		virtual void enableFog(bool enable) = 0;
		virtual void setFogProperties(int fogMode, Color color, Number density, Number startDepth, Number endDepth) = 0;
				
		virtual void multModelviewMatrix(Matrix4 m) = 0;
		virtual void setModelviewMatrix(Matrix4 m) = 0;
				
		virtual void setBlendingMode(int blendingMode) = 0;	
			
		virtual void applyMaterial(Material *material, ShaderBinding *localOptions, unsigned int shaderIndex, bool forceMaterial);
		virtual void clearShader() = 0;
		
		virtual void setDepthFunction(int depthFunction) = 0;
				
		virtual void createVertexBufferForMesh(Mesh *mesh) = 0;
		virtual void drawVertexBuffer(VertexBuffer *buffer, bool enableColorBuffer) = 0;
		
		virtual void enableDepthTest(bool val) = 0;
		virtual void enableDepthWrite(bool val) = 0;
        virtual void setWireframePolygonMode(bool val) = 0;
		
		void billboardMatrix();
		void billboardMatrixWithScale(Vector3 scale);
		
		void setTextureFilteringMode(int mode);

		/**
		 * Set the frustum clipping planes.
		 *
		 * Please check the supplied external links for more information
		 * about the problems of a high farPlane/nearPlane setting.
		 *
		 * @see http://www.opengl.org/sdk/docs/man2/xhtml/glFrustum.xml
		 */
		virtual void setProjectionFromFrustum(Number left, Number right, Number bottom, Number top, Number front, Number back) = 0;


		virtual void setProjectionFromFoV(Number fov, Number near, Number far) = 0;

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
		void addLight(int lightImportance, const Vector3 &position, const Vector3 &direction, int type, const Color &color, const Color &specularColor, Number constantAttenuation, Number linearAttenuation, Number quadraticAttenuation, Number intensity, Number spotlightCutoff, Number spotlightExponent, bool shadowsEnabled, Matrix4 *textureMatrix, Texture *shadowMapTexture);
		
		void setExposureLevel(Number level);
		
		virtual Vector3 projectRayFrom2DCoordinate(Number x, Number y, const Matrix4 &cameraMatrix, const Matrix4 &projectionMatrix, const Polycode::Rectangle &viewport) = 0;
		
		virtual Vector2 Project(const Matrix4 &cameraMatrix, const Matrix4 &projectionMatrix, const Polycode::Rectangle &viewport, const Vector3 &coordiante) const = 0;
		
		void enableShaders(bool flag);
		
		Number getViewportWidth();
		Number getViewportHeight();		
		
		void setViewportShift(Number shiftX, Number shiftY);
		
		void *getDataPointerForName(const String &name);
		void setRendererShaderParams(Shader *shader, ShaderBinding *binding);
		
		void addShaderModule(PolycodeShaderModule *module);
				
		virtual Matrix4 getProjectionMatrix() = 0;
		virtual Matrix4 getModelviewMatrix() = 0;

        static const int BLEND_MODE_NONE = 0;
		static const int BLEND_MODE_NORMAL = 1;
		static const int BLEND_MODE_LIGHTEN = 2;
		static const int BLEND_MODE_COLOR = 3;
		static const int BLEND_MODE_PREMULTIPLIED = 4;
		static const int BLEND_MODE_MULTIPLY = 5;
								
		static const int FOG_LINEAR = 0;
		static const int FOG_EXP = 1;
		static const int FOG_EXP2 = 2;
		
		static const int DEPTH_FUNCTION_GREATER = 0;
		static const int DEPTH_FUNCTION_LEQUAL = 1;	
		
		static const int TEX_FILTERING_NEAREST = 0;
		static const int TEX_FILTERING_LINEAR = 1;
		
		
		virtual Vector3 Unproject(Number x, Number y, const Matrix4 &cameraMatrix, const Matrix4 &projectionMatrix, const Polycode::Rectangle &viewport) = 0;
		
		Color	ambientColor;
		Color	clearColor;		
		Number exposureLevel;		
		Vector3 cameraPosition;
		
		void sortLights();
		
		int getNumPointLights() { return numPointLights; }
		int getNumSpotLights() { return numSpotLights; }
		int getNumLights() { return numLights; }
		
		std::vector<LightInfo> getPointLights() { return pointLights; }
		std::vector<LightInfo> getSpotLights() { return spotLights;	}
		
		bool doClearBuffer;
		
		bool blendNormalAsPremultiplied;
		Number alphaTestValue;
        
        void setBackingResolutionScale(Number xScale, Number yScale);
        
        Number getBackingResolutionScaleX();
        Number getBackingResolutionScaleY();
        
        void setOverrideMaterial(Material *material);
        
        void pushVertexColor();
        void popVertexColor();
        void loadVertexColorIdentity();
        void multiplyVertexColor(const Color &color);
        
        void setRenderToGlobalFramebuffer(bool val);
        bool getRenderToGlobalFramebuffer() const;
        
        Texture *getGlobalColorFramebuffer() const;
        Texture *getGlobalDepthFramebuffer() const;
        
	protected:
		virtual void initOSSpecific() {};
        
        Number backingResolutionScaleX;
        Number backingResolutionScaleY;
        
        std::stack<Color> vertexColorStack;
        Color currentVertexColor;
        
        std::stack<Texture*> framebufferStackColor;
        std::stack<Texture*> framebufferStackDepth;
        
		bool scissorEnabled;
		
		Polycode::Rectangle scissorBox;
	
		Number anisotropy;
		LightSorter sorter;	
	
		Number viewportWidth;
		Number viewportHeight;
		
		Vector2 viewportShift;
			
		bool cullingFrontFaces;
				
		Texture *currentTexture;
		Material *currentMaterial;
		
		int textureFilteringMode;
		
		Matrix4 cameraMatrix;
        Material *overrideMaterial;
        
		PolycodeShaderModule* currentShaderModule;
		std::vector <PolycodeShaderModule*> shaderModules;
        
        bool renderToGlobalFramebuffer;
        Texture *globalColorFramebuffer;
        Texture *globalDepthFramebuffer;

		std::vector<LightInfo> lights;
		std::vector<LightInfo> pointLights;
		std::vector<LightInfo> spotLights;
		int numLights;
		int numPointLights;
		int numSpotLights;
		
		bool shadersEnabled;
		Number fov;
				
		bool lightingEnabled;
	
		int xRes;
		int yRes;
	};
}
