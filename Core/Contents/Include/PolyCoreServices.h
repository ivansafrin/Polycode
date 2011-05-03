/*
 *  CoreServices.h
 *  Poly
 *
 *  Created by Ivan Safrin on 3/13/08.
 *  Copyright 2008 Ivan Safrin. All rights reserved.
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
	
	/**
	* Global services singleton. CoreServices instantiates and provides global Singleton access to all of the main manager classes in Polycode as well as the Renderer and Config classes.
	*/
	class _PolyExport CoreServices : public EventDispatcher {
		public:
		
			/**
			* Returns the singleton instance. NOTE: The singleton instance is unique to each thread and currently Polycode does not support multithreaded access to the core services. The reason for this is being able to run multiple cores in the same application and still have global singleton access to these services.
			*/ 
			static CoreServices *getInstance();		
			static CoreMutex *getRenderMutex();
			
			void setRenderer(Renderer *renderer);

			/**
			* Returns the main renderer.
			* @return The main renderer.
			* @see Renderer
			*/			
			Renderer *getRenderer();
			
			void Update(int elapsed);
			
			void setCore(Core *core);
			
			/**
			* Returns the core. 
			* @return The core.
			* @see Core
			*/																														
			Core *getCore();
			
			void handleEvent(Event *event);
		
			/**
			* Installs a plugin module at runtime.
			* @param module Plugin module to install. See PolygonModule for more details on modules.
			@see PolycodeModule
			*/
			void installModule(PolycodeModule *module);
			
			/**
			* Returns the material manager. The material manager is responsible for loading and managing textures, shaders and materials.
			* @return Material manager.
			* @see MaterialManager
			*/
			MaterialManager *getMaterialManager();
			
			/**
			* Returns the screen manager. The screen manager is responsible for maintaining and rendering 2D screens.
			* @return Screen Manager
			* @see ScreenManager
			*/			
			ScreenManager *getScreenManager();
			
			/**
			* Returns the scene manager. The screen manager is responsible for maintaining and rendering 3D scenes.
			* @return Scene Manager
			* @see SceneManager
			*/						
			SceneManager *getSceneManager();
			
			/**
			* Returns the timer manager. The timer manager is responsible for updating timers in the framework.
			* @return Timer Manager
			* @see TimerManager
			*/									
			TimerManager *getTimerManager();
			
			/**
			* Returns the tween manager. The tween manager is responsible for updating animated tweens in the framework.
			* @return Tween Manager
			* @see TweenManager
			*/												
			TweenManager *getTweenManager();
			
			/**
			* Returns the resource manager. The resource manager is responsible for loading and unloading resources.
			* @return Resource Manager
			* @see ResourceManager
			*/																					
			ResourceManager *getResourceManager();
			
			/**
			* Returns the sound manager. The sound manager is responsible for loading and playing sounds.
			* @return Sound Manager
			* @see SoundManager
			*/																								
			SoundManager *getSoundManager();
			
			/**
			* Returns the font manager. The font manager is responsible for loading and managing fonts.
			* @return Font Manager
			* @see FontManager
			*/																											
			FontManager *getFontManager();

			/**
			* Returns the config. The config loads and saves data to disk.
			* @return Config manager.
			* @see Config
			*/																													
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