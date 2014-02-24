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
#include "PolyEntity.h"
#include "PolyVector2.h"

namespace Polycode {

	class Scene;
	class Material;
	class ShaderBinding;
	class Texture;

	/**
	* Camera in a 3D scene. Cameras can be added to a scene and changed between dynamically. You can also set a shader to a camera that will run as a screen shader for post-processing effects.
	*/	
	class _PolyExport Camera : public Entity {
		public:
			
			/** ProjectionMode: Orthographic projection, with manually set size. */
			static const int ORTHO_SIZE_MANUAL = 0;

			/** ProjectionMode: Orthographic projection, with height specified used and width scaled proportionally . */
			static const int ORTHO_SIZE_LOCK_HEIGHT = 1;

			/** ProjectionMode: Orthographic projection, with width specified used and height scaled proportionally. */
			static const int ORTHO_SIZE_LOCK_WIDTH = 2;

			/** ProjectionMode: Orthographic projection, scaled to viewport backing resolution. */
			static const int ORTHO_SIZE_VIEWPORT = 3;

			/** ProjectionMode: Perspective projection, with field of view specified. */
			static const int PERSPECTIVE_FOV = 4;

			/** ProjectionMode: Perspective projection, with bounds set by edges of frustum. */
			static const int PERSPECTIVE_FRUSTUM = 5;

			/**
			* Constructor.
			* @param parentScene Scene to add the camera to.
			*/
			Camera(Scene *parentScene);
			virtual ~Camera();
			
			void buildFrustumPlanes();
			
			/**
			* Checks if the camera can see a sphere.
			* @param pos Position of the sphere to check.
			* @param fRadius Radius of the sphere.
			* @return Returns true if the sphere is within the camera's frustum, or false if it isn't.
			* @see canSee()
			*/								
			bool isSphereInFrustum(Vector3 pos, Number fRadius);
		
			/**
			* Checks if the camera can see an entity based on its bounding radius.
			* @param entity Entity to check.
			* @return Returns true if the entity's bounding radius is within the camera's frustum, or false if it isn't.
			* @see isSphereInFrustum()
			*/					
			bool canSee(Entity *entity);
			
			/**
			* Toggles orthographic projection mode for camera.
			* @param mode If true, sets the camera into orthographic projection mode.
			* @param orthoSizeX Width of the orthographic frustum (defaults to 1.0)
			* @param orthoSizeY Height of the orthographic frustum (defaults to 1.0)				
			*/			
			void setOrthoMode(bool mode);

			void setOrthoSize(Number orthoSizeX, Number orthoSizeY);
			
			/** Switches into frustum mode and sets up the planes. */
			void setFrustumMode(Number left, Number right, Number bottom, Number top, Number front, Number back);

			/**
			* Returns true if camera is in orthographic projection mode.
			* @return True if camera is orthographic, false if otherwise.
			*/
			bool getOrthoMode() {
				return projectionMode == ORTHO_SIZE_MANUAL ||
						projectionMode == ORTHO_SIZE_LOCK_HEIGHT ||
						projectionMode == ORTHO_SIZE_LOCK_WIDTH ||
						projectionMode == ORTHO_SIZE_VIEWPORT;
			}
			
			/**
			* Returns the width of the camera's orthographic frustum.
			* @return Width of the camera's orthographic frustum.
			*/
			Number getOrthoSizeX();
			
			/**
			* Returns the height of the camera's orthographic frustum.
			* @return Height of the camera's orthographic frustum.
			*/			
			Number getOrthoSizeY();
						
			/**
			* Sets the field of view (FOV) for the camera. The larger the field of view, the more the camera can see, the smaller it is, the more zoomed in it is.
			* @param fov The new FOV value.
			*/			
			void setFOV(Number fov);
			
			/**
			* Returns the current FOV value for the camera.
			* @return Current FOV value for the camera.
			*/			
			Number getFOV() {
				return fov;
			}
			
			void setClippingPlanes(Number nearClipPlane, Number farClipPlane);
        
        
			Number getNearClippingPlane();
			Number getFarClippingPlane();
        
			void setParentScene(Scene *parentScene);
            Scene *getParentScene() const;
			
			void doCameraTransform();
			void setLightDepthTexture(Texture *texture);			

			bool hasFilterShader();
			void drawFilter(Texture *targetTexture = NULL, Number targetTextureWidth = 0.0, Number targetTextureHeight = 0.0, Texture *targetColorTexture = NULL, Texture *targetZTexture = NULL);
			
			/**
			* Sets the exposure for the camera. The exposure value can be passed to a shader for HDR rendering.
			* @param level The new exposure value.
			*/						
			void setExposureLevel(Number level) {
				exposureLevel = level;
			}
			
			/**
			* Returns the camera's exposure value.
			* @return Current exposure value.
			*/									
			Number getExposureLevel() {
				return exposureLevel;
			}

			/**
			* Sets the post-processing shader for the camera.
			* @param shaderMaterial Post processing shader material.
			*/
			void setPostFilter(Material *shaderMaterial);
			
			/**
			* Sets the post-processing shader for the camera by name. The material needs have been added as a resource.
			* @param materialName The material name of the post-processing filter.
			*/												
			void setPostFilterByName(const String& shaderName);
			
			/**
			* Removes the currently assigned post filter.
			*/
			void removePostFilter();
			
			/**
			* Returns the local shader options for the camera post processing material.
			*/
			std::vector<ShaderBinding*> getLocalShaderOptions() { return localShaderOptions; }
			
			/**
			* Returns the shader material applied to the camera.
			*/			
			Material *getScreenShaderMaterial() { return filterShaderMaterial; }	
			
        
            virtual Entity *Clone(bool deepClone, bool ignoreEditorOnly) const;
            virtual void applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly) const;
			
			Matrix4 getProjectionMatrix();
			
			Polycode::Rectangle getViewport();
			
			/**
			* Toggles the frustum culling of the camera. (Defaults to true).
			*/
			bool frustumCulling;
			
			bool topLeftOrtho;
		
            /**
            * Shifts camera frustum by factor of the frustum size. (x=-1 will shift the frustum to the left by a whole screen width).
            */
			Vector2 cameraShift;
		      
			/** @deprecated use setProjectionMode(ProjectionMode mode) */
			void setOrthoSizeMode(int orthoSizeMode) { setProjectionMode(orthoSizeMode); }
			/** @deprecated use getProjectionMode() */
			int getOrthoSizeMode() const { return projectionMode; }

			void setProjectionMode(int mode);
			int getProjectionMode() const { return projectionMode; }


		protected:

			int projectionMode;

			Matrix4 projectionMatrix;

			Polycode::Rectangle viewport;
			Number orthoSizeX;
			Number orthoSizeY;

			Number nearClipPlane;
			Number farClipPlane;
								
			Number exposureLevel;
			Number fov;

			Number leftFrustum,rightFrustum,topFrustum,bottomFrustum;

			Number frustumPlanes[6][4];

			Scene *parentScene;

			Material *filterShaderMaterial;			
			Texture *originalSceneTexture;			
			Texture *zBufferSceneTexture;
			std::vector<ShaderBinding*> localShaderOptions;
			bool _hasFilterShader;
	};	
}
