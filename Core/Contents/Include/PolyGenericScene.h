/*
 *  PolyGenericScene.h
 *  Poly
 *
 *  Created by Ivan Safrin on 3/18/08.
 *  Copyright 2008 Ivan Safrin. All rights reserved.
 *
 */
// @package Scene
 
#pragma once
#include "PolyString.h"
#include "PolyLogger.h"
#include "PolyGlobals.h"
#include <vector>
#include "PolyScene.h"
#include "PolySceneMesh.h"
#include "PolyScenePrimitive.h"
#include "OSBasics.h"

using std::vector;

namespace Polycode {
	
	class _PolyExport GenericScene : public Scene {
		public:
			GenericScene();
			GenericScene(bool virtualScene);
		
			virtual ~GenericScene();
			
			void Render();
			void RenderDepthOnly(Camera *targetCamera);
			void addGrid(String gridTexture);
	
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
		
		private:
		
			bool useClearColor;
			bool virtualScene;
			bool hasLightmaps;
//			LightmapPacker *packer;
			
			vector <SceneLight*> lights;				
			vector <SceneMesh*> staticGeometry;
			vector <SceneMesh*> collisionGeometry;
			vector <SceneEntity*> customEntities;
	};

}