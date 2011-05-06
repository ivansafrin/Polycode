/*
Copyright (C) 2011 by Ivan Safrin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
 

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

	/**
	* Manages loading and unloading of resources from directories and archives. Should only be accessed via the CoreServices singleton. 
	*/ 
	class _PolyExport ResourceManager {
		public:
			ResourceManager();
			~ResourceManager();
			
			/** 
			* Adds a new resource.
			* @param resource Resource to add.
			*/ 
			void addResource(Resource *resource);
			
			/**
			* Loads resources from a directory.
			* @param dirPath Path to directory to load resources from.
			* @param recursive If true, will recurse into subdirectories.
			*/
			void addDirResource(String dirPath, bool recursive=true);
			
			/**
			* Adds a zip as a readable source. This doesn't actually load resources from it, just mounts it as a readable source, so you can call addDirResource on the folders inside of it like you would on regular folders. Most other disk IO in the engine (loading images, etc.) will actually check mounted archive files as well.
			*/
			void addArchive(String zipPath);
		
			bool readFile(String fileName){ return false;}
		
			void parseTextures(String dirPath, bool recursive);
			void parseMaterials(String dirPath, bool recursive);
			void parseShaders(String dirPath, bool recursive);
			void parsePrograms(String dirPath, bool recursive);
			void parseCubemaps(String dirPath, bool recursive);
			void parseOthers(String dirPath, bool recursive);	
		
			/**
			* Request a loaded resource. You need to manually cast it to its subclass based on its type.
			* @param resourceType Type of resource. See Resource for available resource types.
			* @param resourceName Name of the resource to request.
			*/
			Resource *getResource(int resourceType, String resourceName);
		
			void addShaderModule(PolycodeShaderModule *module);
		
		
		private:
			vector <Resource*> resources;
			vector <PolycodeShaderModule*> shaderModules;
	};
}