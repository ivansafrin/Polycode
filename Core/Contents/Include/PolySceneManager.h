/*
 *  PolySceneManager.h
 *  TAU
 *
 *  Created by Ivan Safrin on 3/18/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

// @package Services

#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolyScene.h"
#include "PolySceneRenderTexture.h"

#include <vector>

using std::vector;

namespace Polycode {
	
	class Scene;
	class SceneRenderTexture;
	
	class _PolyExport SceneManager {
		public:
		SceneManager();
		~SceneManager();
		
		void addScene(Scene *newScene);
		void Update();
		void UpdateVirtual();
		void removeScene(Scene *scene);	
		void registerRenderTexture(SceneRenderTexture *renderTexture);
		
		private:
		
		void updateRenderTextures(Scene *scene);
		
		vector <Scene*> scenes;
		vector <SceneRenderTexture*> renderTextures;
			
	};

}