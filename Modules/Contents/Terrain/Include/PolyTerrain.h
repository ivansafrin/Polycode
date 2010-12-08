/*
 *  PolyTerrain.h
 *  Poly
 *
 *  Created by Ivan Safrin on 2/20/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

// @package Scene

#pragma once
#include "PolyGlobals.h"
#include "PolySceneMesh.h"
#include "PolyCoreServices.h"

#include <string>
using std::string;

namespace Polycode {
	
	class _PolyExport Terrain : public SceneMesh {
	public:
		
		Terrain(int type, string heightmapFile, bool smooth, float tileAmt, float xDensity, float zDensity, float sx, float sz, float height);
		~Terrain();
		Vector3 getTerrainDataScale() { return terrainDataScale; }		
		
		static const int BASIC = 0;
		
		
	private:
		
		void createBasic(string heightmapFile, bool smooth, float tileAmt, float xDensity, float zDensity, float sx, float sz, float height);
		
		Vector3 terrainDataScale;
	};
	
	
}