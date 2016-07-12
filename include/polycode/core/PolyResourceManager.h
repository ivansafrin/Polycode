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
#include "tinyxml.h"
#define generic GenericFreetypeLibrary
#include "ft2build.h"
#include FT_FREETYPE_H
#include FT_LCD_FILTER_H

extern "C" {
#ifndef NO_LUA
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
#endif	 
	#include "duktape.h"
}

#include <memory>

#define RESOURCE_CHECK_INTERVAL 2000

namespace Polycode {

	class Resource;
	class String;
	class ResourceLoader;
	class Shader;
	class Cubemap;
	class Material;
    class Font;
	
	class _PolyExport ResourcePool : public EventDispatcher {
		public:
			ResourcePool();
			ResourcePool(const String &name, ResourcePool *fallbackPool);
			~ResourcePool();
		
			void setFallbackPool(ResourcePool *pool);
		
			void addResource(std::shared_ptr<Resource> resource);
			void removeResource(std::shared_ptr<Resource> resource);
			bool hasResource(std::shared_ptr<Resource> resource);
		
			void loadResourcesFromFolder(const String &folder, bool recursive);
			void loadResourcesFromMaterialFile(const String &path);
		
			std::shared_ptr<Resource> loadResource(const String &path);
			std::shared_ptr<Resource> loadResourceWithName(const String &path, const String &name);
			std::shared_ptr<Resource> getResource(int resourceType, const String& resourceName) const;
			String getName();
			void setName(const String &name);
		
            std::shared_ptr<Font> loadFont(const String &name, const String &path);
        
			std::shared_ptr<Resource> getResourceByPath(const String& resourcePath) const;
			void Update(int elapsed);
		
			std::vector<std::shared_ptr<Resource> > getResources(int resourceType);
		
			void checkForChangedFiles();
		
			bool reloadResourcesOnModify;
			bool dispatchChangeEvents;
		
			int resourceSubscribers;
			bool deleteOnUnsubscribe;
		
			static bool defaultReloadResourcesOnModify;
		
		private:
		
			void loadResourcesFromFolderWithLoader(const String &folder, bool recursive, ResourceLoader *loader, const String &containingFolder);
		
			void loadShadersFromFile(const String &fileName);
			std::shared_ptr<Shader> createShaderFromXMLNode(TiXmlNode *node);
			std::shared_ptr<Cubemap> cubemapFromXMLNode(TiXmlNode *node);
			void loadCubemapsFromFile(const String &fileName);
			void loadMaterialsFromFile(const String &fileName);
			std::shared_ptr<Material> materialFromXMLNode(TiXmlNode *node);

			ResourcePool *fallbackPool;
			String name;
			int ticksSinceCheck;
			std::vector <std::shared_ptr<Resource> > resources;
		
	};
	
	class _PolyExport ResourceLoader {
		public:
			virtual ~ResourceLoader() {}
			bool canHandleExtension(const String &extension);
			virtual std::shared_ptr<Resource> loadResource(const String &path, ResourcePool *targetPool) = 0;
			std::vector<String> extensions;
	};
	
	class _PolyExport TextureResourceLoader : public ResourceLoader {
		public:
			TextureResourceLoader();
			std::shared_ptr<Resource> loadResource(const String &path, ResourcePool *targetPool);
	};
	
	class _PolyExport ProgramResourceLoader : public ResourceLoader {
	public:
		ProgramResourceLoader();
		std::shared_ptr<Resource> loadResource(const String &path, ResourcePool *targetPool);
	};

	class _PolyExport MaterialResourceLoader : public ResourceLoader {
	public:
			MaterialResourceLoader();
			std::shared_ptr<Resource> loadResource(const String &path, ResourcePool *targetPool);
	};
	
	class _PolyExport FontResourceLoader : public ResourceLoader {
	public:
		FontResourceLoader();
		~FontResourceLoader();
		std::shared_ptr<Resource> loadResource(const String &path, ResourcePool *targetPool);
	private:
		FT_Library FTLibrary;
	};
	
	class DebugBackTraceEntry {
	public:
		String fileName;
		unsigned int lineNumber;
	};
	
	class _PolyExport ScriptResourceLoader : public ResourceLoader {
	public:
		ScriptResourceLoader();
		~ScriptResourceLoader();
		std::shared_ptr<Resource> loadResource(const String &path, ResourcePool *targetPool);
	private:
		
		void initJavascript();
		duk_context *duktapeContext;
		
#ifndef NO_LUA
		void initLua();
		lua_State *luaState;
#endif
	};
	
	class _PolyExport MeshResourceLoader : public ResourceLoader {
	public:
		MeshResourceLoader();
		std::shared_ptr<Resource> loadResource(const String &path, ResourcePool *targetPool);
	};
	
	/**
	* Manages loading and unloading of resources from directories and archives. Should only be accessed via the CoreServices singleton.
	*/ 
	class _PolyExport ResourceManager : public EventDispatcher {
		public:
			ResourceManager();
			~ResourceManager();
		
			ResourcePool *getGlobalPool();
			ResourcePool *getResourcePoolByName(const String &name);
			  
			void addResourceLoader(ResourceLoader *loader);
			ResourceLoader *getResourceLoaderForExtension(const String &extension);
			void removeResourceLoader(ResourceLoader *loader);

			unsigned int getNumResourceLoaders();
			ResourceLoader *getResourceLoaderAtIndex(unsigned int index);
		
			void addResourcePool(ResourcePool *pool);
			void removeResourcePool(ResourcePool *pool);
		
			std::vector<std::shared_ptr<Resource> > getResources(int resourceType);
		
			void removeResource(std::shared_ptr<Resource> resource);
		
			void subscribeToResourcePool(ResourcePool *pool);
			void unsubscibeFromResourcePool(ResourcePool *pool);
		
			void Update(int elapsed);
			void handleEvent(Event *event);
		
		private:
		
			std::vector<ResourceLoader*> resourceLoaders;
			ResourcePool *globalPool;
			std::vector <ResourcePool*> pools;
	};
}
