/*
 *  PolyScene.h
 *  TAU
 *
 *  Created by Ivan Safrin on 3/18/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
// @package Scene

#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolyRenderer.h"
#include "PolySceneEntity.h"
#include "PolyCamera.h"
#include "PolySceneLight.h"
#include <vector>

using std::vector;

namespace Polycode {
		
	class Camera;
	class SceneLight;
	
	class _PolyExport Scene : public EventDispatcher {
	public:
		
		Scene();
		virtual ~Scene();
		
		virtual void Render() = 0;
		virtual void RenderDepthOnly(Camera *targetCamera) = 0;
		
		void addEntity(SceneEntity *entity);
		void removeEntity(SceneEntity *entity);
		Camera *getDefaultCamera();
		
		void enableLighting(bool enable);
		void enableFog(bool enable);
		void setFogProperties(int fogMode, Color color, float density, float startDepth, float endDepth);

		virtual void Update();
		void setVirtual(bool val);
		bool isVirtual();
	
		bool isEnabled();
		void setEnabled(bool enabled);
		
		int getNumEntities() { return entities.size(); }
		SceneEntity *getEntity(int index) { return entities[index]; }
		
		SceneEntity *getEntityAtCursor(float x, float y);
		
	protected:
		
		bool isSceneVirtual;
		bool enabled;
		
		Camera *defaultCamera;
		vector <SceneEntity*> entities;
		
		bool lightingEnabled;
		bool fogEnabled;
		int fogMode;
		Color fogColor;
		float fogDensity;
		float fogStartDepth;
		float fogEndDepth;
		
	};
}