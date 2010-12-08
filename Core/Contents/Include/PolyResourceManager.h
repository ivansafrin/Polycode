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
			
			void addDirResource(string dirPath, bool recursive);
			void addArchive(string zipPath);
		
			bool readFile(string fileName){ return false;}
		
			void parseTextures(string dirPath, bool recursive);
			void parseMaterials(string dirPath, bool recursive);
			void parseShaders(string dirPath, bool recursive);
			void parsePrograms(string dirPath, bool recursive);
			void parseCubemaps(string dirPath, bool recursive);
		
			Resource *getResource(int resourceType, string resourceName);
		
			void addShaderModule(PolycodeShaderModule *module);
		
		
		private:
			vector <Resource*> resources;
			vector <PolycodeShaderModule*> shaderModules;
	};
}