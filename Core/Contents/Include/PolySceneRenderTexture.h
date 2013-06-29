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

namespace Polycode {

class Scene;
class Camera;
class Texture;

/**
* Renders scenes to texture. This class automatically renders a scene to a texture every frame that you can use to texture anything else. You can set a scene to virtual (see Scene for details) to only render a scene to a texture if you need to. This class automatically adds itself to the render cycle, so you do not need to do anything manual every frame.
*/
class _PolyExport SceneRenderTexture : public PolyBase {
	public:
		/**
		* Construct a new render texture with parameters.
		* @param targetScene Target scene to render.
		* @param Camera to render from.
		* @param renderWidth Horizontal size of the render texture.
		* @param renderHeight Vertical size of the render texture.
		* @param floatingPoint Pass true if you want fp16 target renders
		*/
		SceneRenderTexture(Scene *targetScene, Camera *targetCamera, int renderWidth,int renderHeight, bool floatingPoint = false);
		virtual ~SceneRenderTexture();

		/**
		* Returns the actual render texture.
		*/
		Texture *getTargetTexture();

		Texture *getFilterColorBufferTexture();
		Texture *getFilterZBufferTexture();

		void resizeRenderTexture(int newWidth, int newHeight);
		/**
		* Returns the target scene.
		*/
		Scene *getTargetScene();

		/**
		* Returns the target camera.
		*/
		Camera *getTargetCamera();

	protected:

		Texture *filterColorBufferTexture;
		Texture *filterZBufferTexture;

		bool floatingPoint;

		Texture *depthTexture;
		Texture *targetTexture;
		Scene *targetScene;
		Camera *targetCamera;
};
}
