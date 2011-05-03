/*
 *  PolySceneRenderTexture.h
 *  Poly
 *
 *  Created by Ivan Safrin on 8/6/08.
 *  Copyright 2008 Ivan Safrin. All rights reserved.
 *
 */

// @package Scene

#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolyScene.h"
#include "PolyTexture.h"

namespace Polycode {
	class Scene;
	class Camera;
	
	class _PolyExport SceneRenderTexture {
		public:
			SceneRenderTexture(Scene *targetScene, Camera *targetCamera, int renderWidth,int renderHeight);
			~SceneRenderTexture();
			
			void drawScreen();
			
			Texture *getTargetTexture();
			Scene *getTargetScene();
			Camera *getTargetCamera();	
				
		protected:
		
			Texture *targetTexture;
			Scene *targetScene;
			Camera *targetCamera;
	};
}