/*
 *  CoreServices.h
 *  TAU
 *
 *  Created by Ivan Safrin on 3/13/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

// @package Services
 
#pragma once
#include "PolyString.h"
#include "PolyLogger.h"
#include "PolyGlobals.h"
#include "PolyRenderer.h"
#include "PolyMaterialManager.h"
#include "PolyScreenManager.h"
#include "PolySceneManager.h"
#include "PolyTimerManager.h"
#include "PolyFontManager.h"
#include "PolyTweenManager.h"
#include "PolySoundManager.h"
#include "PolyResourceManager.h"
#include "PolyCore.h"
#include "PolyConfig.h"
#include "PolyModule.h"
#include "PolyBasics.h"

#include <map>

namespace Polycode {

	class Renderer;
	class MaterialManager;
	class SceneManager;
	class ScreenManager;
	class TimerManager;
	class TweenManager;
	class ResourceManager;
	class SoundManager;
	class Core;
	class CoreMutex;
	
	class _PolyExport CoreServices : public EventDispatcher {
		public:
			static CoreServices *getInstance();		
			static CoreMutex *getRenderMutex();
			
			void setRenderer(Renderer *renderer);
			
			Renderer *getRenderer();
			void Update(int elapsed);
			
			void setCore(Core *core);
			Core *getCore();
			
			void handleEvent(Event *event);
		
			void installModule(PolycodeModule *module);
			
			MaterialManager *getMaterialManager();
			ScreenManager *getScreenManager();
			SceneManager *getSceneManager();
			TimerManager *getTimerManager();
			TweenManager *getTweenManager();
			ResourceManager *getResourceManager();
			SoundManager *getSoundManager();
			FontManager *getFontManager();
		
			Config *getConfig();
		
			~CoreServices();
		
		protected:
		
			CoreServices();
					
		private:
		
			static std::map <long, CoreServices*> instanceMap;
			static CoreMutex *renderMutex;
		
			vector<PolycodeModule*> modules;
		
			Core *core;
			Config *config;
			MaterialManager *materialManager;
			ScreenManager *screenManager;		
			SceneManager *sceneManager;
			TimerManager *timerManager;
			TweenManager *tweenManager;
			ResourceManager *resourceManager;
			SoundManager *soundManager;
			FontManager *fontManager;
			Renderer *renderer;
	};
}