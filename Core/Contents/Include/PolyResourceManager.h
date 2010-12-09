/*
 *  PolyResourceManager.h
 *  Poly
 *
 *  Created by Ivan Safrin on 8/30/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
// @package Services

#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"
#include <vector>
#include <string>
#include "OSBasics.h"
#include "PolyTexture.h"
#include "PolyCubemap.h"
#include "PolyResource.h"
#include "PolyCoreServices.h"
#include "PolyModule.h"
#include "tinyxml.h"
#include "physfs.h"

using std::vector;
using std::string;

namespace Polycode {

	class _PolyExport ResourceManager {
		public:
			ResourceManager();
			~ResourceManager();
			
			void addResource(Resource *resource);
			
			void addDirResource(String dirPath, bool recursive);
			void addArchive(String zipPath);
		
			bool readFile(String fileName){ return false;}
		
			void parseTextures(String dirPath, bool recursive);
			void parseMaterials(String dirPath, bool recursive);
			void parseShaders(String dirPath, bool recursive);
			void parsePrograms(String dirPath, bool recursive);
			void parseCubemaps(String dirPath, bool recursive);
		
			Resource *getResource(int resourceType, String resourceName);
		
			void addShaderModule(PolycodeShaderModule *module);
		
		
		private:
			vector <Resource*> resources;
			vector <PolycodeShaderModule*> shaderModules;
	};
}