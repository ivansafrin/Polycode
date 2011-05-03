/*
 *  PolyScreen.h
 *  Poly
 *
 *  Created by Ivan Safrin on 3/13/08.
 *  Copyright 2008 Ivan Safrin. All rights reserved.
 *
 */

// @package Screen

#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolyScreenEntity.h"
#include "PolyRenderer.h"
#include "PolyInputEvent.h"
#include "PolyCoreServices.h"
#include <vector>
#include <algorithm>
#include "PolyScreenEvent.h"

using namespace std;

namespace Polycode {

	/**
	* 2D rendering base. The Screen is the base class for all 2D rendering in Polycode. Screens are
	*/	
	class _PolyExport Screen : public EventDispatcher {
	public:
		
		Screen();
		~Screen();
		ScreenEntity* addChild(ScreenEntity *newEntity);
		ScreenEntity* removeChild(ScreenEntity *entityToRemove);
		
		void setScreenOffset(Number x, Number y);
		Vector2 getScreenOffset();
		
		virtual void Shutdown();
		virtual void Update();
		ScreenEntity *getEntityAt(Number x, Number y);
		void Render();
		void setRenderer(Renderer *renderer);
		
		void setNormalizedCoordinates(bool newVal, Number yCoordinateSize = 1.0f);
		void setScreenShader(String shaderName);
		
		void handleEvent(Event *event);
		int getHighestZIndex();
		void sortChildren();
		
		static bool cmpZindex(const ScreenEntity *left, const ScreenEntity *right);
		
		void handleInputEvent(InputEvent *inputEvent);
		bool hasFilterShader();
		void drawFilter();
		
		bool usesNormalizedCoordinates() { return useNormalizedCoordinates; }
		Number getYCoordinateSize() { return yCoordinateSize; }	
		
		ScreenEntity *getRootEntity() { return rootEntity; }
		
		bool enabled;
		
	protected:
		
		bool useNormalizedCoordinates;
		Number yCoordinateSize;		
		
		ScreenEntity *rootEntity;
		
		Vector2 offset;
		Renderer *renderer;
		ScreenEntity *focusChild;
		vector <ScreenEntity*> children;
		
		Material *filterShaderMaterial;			
		Texture *originalSceneTexture;			
		Texture *zBufferSceneTexture;						
		vector<ShaderBinding*> localShaderOptions;
		bool _hasFilterShader;
	};
}