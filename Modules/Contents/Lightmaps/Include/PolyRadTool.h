/*
 *  PolyRadTool.h
 *  Poly
 *
 *  Created by Ivan Safrin on 9/25/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

// @package Scene

#pragma once
#include "PolyGlobals.h"
#include "PolyGenericScene.h"
#include "PolyLightmapPacker.h"
#include "PolyPolygon.h"

namespace Polycode {

	class GenericScene;
	class LightmapPacker;
	class LightmapFace;
	struct Lumel;
	class Polygon;
	
	class _PolyExport RadTool {
		public:
			RadTool(GenericScene *scene, LightmapPacker *packer);
			~RadTool();
			
			void fiatLux(int radPasses);
			
		private:
		
			void applyLight(SceneLight *light);
			void lightLumel(SceneLight *light,Image *image, Lumel *lumel);
			
			void doRadiosityPass();
			void radLumel(Lumel *lumel,Image *image);
					
			bool worldRayTest(Vector3 origin, Vector3 destination, Polygon *hitPolygon);
			static bool rayTriangleIntersect(Vector3 ray_origin, Vector3 ray_direction, Vector3 vert0, Vector3 vert1, Vector3 vert2, Vector3 *hitPoint);
		
			GenericScene *scene;
			LightmapPacker *packer;
	};
}