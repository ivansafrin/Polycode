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
#include "PolyGlobals.h"
#include <vector>

#define RESOURCE_CHECK_INTERVAL	2000

namespace Polycode {

class Resource;
class PolycodeShaderModule;
class String;

/**
* Manages loading and unloading of resources from directories and archives. Should only be accessed via the CoreServices singleton. 
*/ 
class _PolyExport ResourceManager : public PolyBase {
	public:
		ResourceManager();
		~ResourceManager();

		/** 
		* Adds a new resource.
		* @param resource Resource to add.
		*/ 
		void addResource(Resource *resource);

		/** 
		* Removes a resource.
		* @param resource Resource to resource.
		*/ 
		void removeResource(Resource *resource);


		/**
		* Returns true if the following resource has been adde to the resource manager.
		* @param resource Resource to check.
		*/
		bool hasResource(Resource *resource);
		/**
		* Loads resources from a directory.
		* @param dirPath Path to directory to load resources from.
		* @param recursive If true, will recurse into subdirectories.
		*/
		void addDirResource(const String& dirPath, bool recursive=true);

		/**
		* Adds a zip or folder as a readable source. This doesn't actually load resources from it, just mounts it as a readable source, so you can call addDirResource on the folders inside of it like you would on regular folders. Most other disk IO in the engine (loading images, etc.) will actually check mounted archive files as well.
		*/
		void addArchive(const String& path);

		/**
		* Removes a zip or folder as a readable source.
		*/
		void removeArchive(const String& path);


		bool readFile(const String& fileName) { return false;}

		void parseTextures(const String& dirPath, bool recursive, const String& basePath);
		void parseMaterials(const String& dirPath, bool recursive);
		void parseShaders(const String& dirPath, bool recursive);
		void parsePrograms(const String& dirPath, bool recursive);
		void parseCubemaps(const String& dirPath, bool recursive);
		void parseOthers(const String& dirPath, bool recursive);

		/**
		* Request a loaded resource. You need to manually cast it to its subclass based on its type.
		* @param resourceType Type of resource. See Resource for available resource types.
		* @param resourceName Name of the resource to request.
		*/
		Resource *getResource(int resourceType, const String& resourceName) const;

		Resource *getResourceByPath(const String& resourcePath) const;


		/**
		 * Request a full set of loaded resources. You need to manually cast them to their subclasses based on their type.
		 * @param resourceType Type of resource. See Resource for available resource types.
		 */
		std::vector<Resource *> getResources(int resourceType);

		void addShaderModule(PolycodeShaderModule *module);

		void checkForChangedFiles();

		void Update(int elapsed);

		bool reloadResourcesOnModify;

	private:
		int ticksSinceCheck;

		std::vector <Resource*> resources;
		std::vector <PolycodeShaderModule*> shaderModules;
};

}
