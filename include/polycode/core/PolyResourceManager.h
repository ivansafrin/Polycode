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
#include "polycode/core/PolyGlobals.h"
#include "polycode/core/PolyEventDispatcher.h"
#include <vector>

#define RESOURCE_CHECK_INTERVAL	2000

namespace Polycode {

	class Resource;
	class PolycodeShaderModule;
	class String;
    
    class _PolyExport ResourcePool : public EventDispatcher {
        public:
            ResourcePool(const String &name, ResourcePool *fallbackPool);
            ~ResourcePool();
        
            void setFallbackPool(ResourcePool *pool);
        
			void addResource(Resource *resource);
			void removeResource(Resource *resource);
            bool hasResource(Resource *resource);
        
			Resource *getResource(int resourceType, const String& resourceName) const;
        
            String getName();
            void setName(const String &name);
        
            Resource *getResourceByPath(const String& resourcePath) const;
			void Update(int elapsed);
        
			std::vector<Resource *> getResources(int resourceType);
        
			void checkForChangedFiles();
        
			bool reloadResourcesOnModify;
            bool dispatchChangeEvents;
        
            int resourceSubscribers;
            bool deleteOnUnsubscribe;
        
            static bool defaultReloadResourcesOnModify;
        
        private:
        
            ResourcePool *fallbackPool;
            String name;
			int ticksSinceCheck;
            std::vector <Resource*> resources;
        
    };

	/**
	* Manages loading and unloading of resources from directories and archives. Should only be accessed via the CoreServices singleton. 
	*/ 
	class _PolyExport ResourceManager : public EventDispatcher {
		public:
			ResourceManager();
			~ResourceManager();
			

			/**
			* Loads resources from a directory.
			* @param dirPath Path to directory to load resources from.
			* @param recursive If true, will recurse into subdirectories.
			*/
			void addDirResource(const String& dirPath, bool recursive=true);
		
			void parseTexturesIntoPool(ResourcePool *pool, const String& dirPath, bool recursive, const String& basePath);
			void parseMaterialsIntoPool(ResourcePool *pool, const String& dirPath, bool recursive);
			void parseShadersIntoPool(ResourcePool *pool, const String& dirPath, bool recursive);
			void parseProgramsIntoPool(ResourcePool *pool, const String& dirPath, bool recursive);
			void parseCubemapsIntoPool(ResourcePool *pool, const String& dirPath, bool recursive);
            void parseOtherIntoPool(ResourcePool *pool, const String& dirPath, bool recursive);
		
            ResourcePool *getGlobalPool();
        
            ResourcePool *getResourcePoolByName(const String &name);
		      
            void addResourcePool(ResourcePool *pool);
            void removeResourcePool(ResourcePool *pool);
        
			std::vector<Resource*> getResources(int resourceType);
        
			void removeResource(Resource *resource);
        
            void subscribeToResourcePool(ResourcePool *pool);
            void unsubscibeFromResourcePool(ResourcePool *pool);
        
			void Update(int elapsed);
			void handleEvent(Event *event);
		
		private:
		
            ResourcePool *globalPool;
            std::vector <ResourcePool*> pools;
	};
}
