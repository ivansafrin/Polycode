/*
 *  PolyScene.h
 *  Poly
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
#include "PolySceneMesh.h"
#include <vector>

using std::vector;

namespace Polycode {
		
	class Camera;
	class SceneLight;
	class SceneMesh;
	
	class _PolyExport Scene : public EventDispatcher {
	public:
		
		Scene();
		Scene(bool virtualScene);
		virtual ~Scene();
		
		
		void addEntity(SceneEntity *entity);
		void removeEntity(SceneEntity *entity);
		Camera *getDefaultCamera();
		
		void enableLighting(bool enable);
		void enableFog(bool enable);
		void setFogProperties(int fogMode, Color color, Number density, Number startDepth, Number endDepth);

		virtual void Update();
		void setVirtual(bool val);
		bool isVirtual();
	
		bool isEnabled();
		void setEnabled(bool enabled);
		
		int getNumEntities() { return entities.size(); }
		SceneEntity *getEntity(int index) { return entities[index]; }
		
		SceneEntity *getEntityAtCursor(Number x, Number y);
		
		void Render();
		void RenderDepthOnly(Camera *targetCamera);
//		void addGrid(String gridTexture);
		
		static String readString(OSFILE *inFile);
		void loadScene(String fileName);
		void generateLightmaps(Number lightMapRes, Number lightMapQuality, int numRadPasses);
		
		void addLight(SceneLight *light);
		SceneLight *getNearestLight(Vector3 pos);
		
		void writeEntityMatrix(SceneEntity *entity, OSFILE *outFile);
		void writeString(String str, OSFILE *outFile);
		void saveScene(String fileName);
		
		int getNumStaticGeometry();
		SceneMesh *getStaticGeometry(int index);
		
		virtual void loadCollisionChild(SceneEntity *entity, bool autoCollide=false, int type=0){}
		
		int getNumLights();
		SceneLight *getLight(int index);
		
		SceneEntity *getCustomEntityByType(String type);
		vector<SceneEntity*> getCustomEntitiesByType(String type);		
		
		static const unsigned int ENTITY_MESH = 0;
		static const unsigned int ENTITY_LIGHT = 1;			
		static const unsigned int ENTITY_CAMERA = 2;			
		static const unsigned int ENTITY_ENTITY = 3;
		static const unsigned int ENTITY_COLLMESH = 4;
		
		Color clearColor;
		Color ambientColor;		
		Color fogColor;				
		
		
	protected:
		
		bool useClearColor;
		bool virtualScene;
		bool hasLightmaps;
		//			LightmapPacker *packer;
		
		vector <SceneLight*> lights;				
		vector <SceneMesh*> staticGeometry;
		vector <SceneMesh*> collisionGeometry;
		vector <SceneEntity*> customEntities;
		
		
		bool isSceneVirtual;
		bool enabled;
		
		Camera *defaultCamera;
		vector <SceneEntity*> entities;
		
		bool lightingEnabled;
		bool fogEnabled;
		int fogMode;
		Number fogDensity;
		Number fogStartDepth;
		Number fogEndDepth;
		
	};
}