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
#include "PolySceneEntity.h"

namespace Polycode {

class Scene;
class Material;
class ShaderBinding;
class Texture;

/**
* Camera in a 3D scene. Cameras can be added to a scene and changed between dynamically. You can also set a shader to a camera that will run as a screen shader for post-processing effects.
*/
class _PolyExport Camera : public SceneEntity {
	public:

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
		bool canSee(SceneEntity *entity);

		/**
		* Toggles orthographic projection mode for camera.
		* @param mode If true, sets the camera into orthographic projection mode.
		* @param orthoSizeX Width of the orthographic frustum (defaults to 1.0)
		* @param orthoSizeY Height of the orthographic frustum (defaults to 1.0)
		*/
		void setOrthoMode(bool mode, Number orthoSizeX = 1.0, Number orthoSizeY = 1.0);

		/**
		* Returns true if camera is in orthographic projection mode.
		* @return True if camera is orthographic, false if otherwise.
		*/
		bool getOrthoMode();

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
		Number getFOV();

		void setParentScene(Scene *parentScene);

		void doCameraTransform();
		void setLightDepthTexture(Texture *texture);

		bool hasFilterShader();
		void drawFilter(Texture *targetTexture = NULL, Number targetTextureWidth = 0.0, Number targetTextureHeight = 0.0, Texture *targetColorTexture = NULL, Texture *targetZTexture = NULL);

		/**
		* Sets the exposure for the camera. The exposure value can be passed to a shader for HDR rendering.
		* @param level The new exposure value.
		*/
		void setExposureLevel(Number level);

		/**
		* Returns the camera's exposure value.
		* @return Current exposure value.
		*/
		Number getExposureLevel();

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

		/**
		* Toggles the frustum culling of the camera. (Defaults to true).
		*/
		bool frustumCulling;

	protected:

		Number orthoSizeX;
		Number orthoSizeY;

		Number exposureLevel;
		bool orthoMode;
		Number fov;
		Number frustumPlanes[6][4];
		Scene *parentScene;

		bool fovSet;

		Material *filterShaderMaterial;
		Texture *originalSceneTexture;
		Texture *zBufferSceneTexture;
		std::vector<ShaderBinding*> localShaderOptions;
		bool _hasFilterShader;
};
}
