/*
 *  PolySceneMesh.h
 *  Poly
 *
 *  Created by Ivan Safrin on 3/18/08.
 *  Copyright 2008 Ivan Safrin. All rights reserved.
 *
 */

// @package Scene
 
#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolyCoreServices.h"
#include "PolySceneEntity.h"
#include "PolyMesh.h"
#include "PolySkeleton.h"
#include "PolyMaterial.h"
#include "PolyImage.h"
#include <string>

using namespace std;

namespace Polycode {

	class Texture;
	class Skeleton;
	
	class _PolyExport SceneMesh : public SceneEntity {
		public:
			SceneMesh(String fileName);
			SceneMesh(int meshType);
			SceneMesh(Mesh *mesh);
			virtual ~SceneMesh();
			
			void Render();
			
			ShaderBinding *getLocalShaderOptions();
			
			Mesh *getMesh();
			Texture *getTexture();
			Material *getMaterial();
			void loadTexture(String fileName, bool clamp=true);
			void loadSkeleton(String fileName);
			void setTexture(Texture *texture);
			void setMaterial(Material *material);
			void setMaterialByName(String materialName);
			void setMesh(Mesh *mesh);
		
			void setSkeleton(Skeleton *skeleton);
			Skeleton *getSkeleton();
		
			void renderMeshLocally();
			void cacheToVertexBuffer(bool cache);
	
			// for static lightmaps
			unsigned int lightmapIndex;
			
			bool showVertexNormals;
			
		
		protected:
		
			bool useVertexBuffer;
			Mesh *mesh;
			Texture *texture;
			Material *material;
			Skeleton *skeleton;
			ShaderBinding *localShaderOptions;
	};
}