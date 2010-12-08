/*
 *  PolyLightmapPacker.h
 *  Poly
 *
 *  Created by Ivan Safrin on 9/24/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

// @package Scene

#pragma once

#include "PolyGlobals.h"
#include "PolyGenericScene.h"
#include <vector>
#include <string>
#include <sstream>

using std::vector;
using std::string;

namespace Polycode {
	
	class GenericScene;
	struct LightmapFace;
	
	struct Lumel {
		float u;
		float v;
		Vector3 worldPos;
		Vector3 normal;
		Vector3 rEnergy;
		float lumelScale;
		LightmapFace *face;
	};

	struct LightmapFace {
		Polygon *meshPolygon;
		Polygon *flatPolygon;
		Polygon *flatUnscaledPolygon;
		Rectangle area;
		Rectangle actualArea;
		Rectangle pixelArea;
		vector<Lumel*> lumels;
		int numLumels;
		int imageID;
		int projectionAxis;
		static const int X_PROJECTION = 0;
		static const int Y_PROJECTION = 1;
		static const int Z_PROJECTION = 2;		
	};
	
	struct LightmapMesh {
		SceneMesh *mesh;
		int imageID;
		bool processed;
		vector<LightmapFace*> faces;
	};
	
	class _PolyExport PackNode {
	public:
		PackNode() { child[0] = NULL; child[1] = NULL; face = NULL;}
		~PackNode(){}
		
		PackNode *clone();
		int rootRes;
		PackNode *Insert(LightmapFace *img);
		void createRoot(int res);
		PackNode* child[2];
		Rectangle rc;
		LightmapFace *face;
	};
	
	class _PolyExport LightmapPacker {
	public:
		LightmapPacker(GenericScene *targetScene);
		~LightmapPacker();
		
		void generateTextures(int resolution, int quality);
		void unwrapScene();
		void bindTextures();
		void buildTextures();
		
		Vector3 getLumelPos(Lumel *lumel, LightmapFace *face);
		
		void saveLightmaps(string folder);

		vector<LightmapMesh*> lightmapMeshes;
		vector<Texture*> textures;
		vector<Image*> images;
		vector<Lumel*> lumels;
				
		float lightMapRes;
		float lightMapQuality;

		
	private:
		
		void packMesh(LightmapMesh *mesh);
		void generateNewImage();
		bool hasRoomForMesh(LightmapMesh *mesh);
		
		PackNode *cNode;
		Image *currentImage;
		int currentImageID;
		
		GenericScene *targetScene;
	};
	
}