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

#include "polycode/core/PolyResourceManager.h"
#include "polycode/core/PolyCoreServices.h"
#include "polycode/core/PolyCubemap.h"
#include "polycode/core/PolyMaterialManager.h"
#include "polycode/core/PolyLogger.h"
#include "polycode/core/PolyMaterial.h"
#include "polycode/core/PolyShader.h"
#include "polycode/core/PolyTexture.h"
#include "polycode/core/PolyRenderer.h"
#include "polycode/core/PolyFont.h"
#include "polycode/core/PolyMesh.h"
#include "polycode/core/PolyScript.h"
#include "polycode/core/PolyLuaApi.h"
#include "tinyxml.h"

using std::vector;
using namespace Polycode;

bool ResourcePool::defaultReloadResourcesOnModify = false;

ResourcePool::ResourcePool(const String &name, ResourcePool *fallbackPool) {
    
    this->name = name;
    this->fallbackPool = fallbackPool;
	dispatchChangeEvents = false;
	reloadResourcesOnModify = ResourcePool::defaultReloadResourcesOnModify;
	ticksSinceCheck = 0;
    resourceSubscribers = 0;
    deleteOnUnsubscribe = false;
}

ResourcePool::~ResourcePool() {
    
    CoreServices::getInstance()->getResourceManager()->removeResourcePool(this);
    
    for(int i=0; i < resources.size(); i++)	{
        if(resources[i]->getResourceType() == Resource::RESOURCE_MATERIAL) {
            delete resources[i];
        }
    }
    
    for(int i=0; i < resources.size(); i++)	{
        if(resources[i]->getResourceType() == Resource::RESOURCE_SHADER) {
            delete resources[i];
        }
    }
    
    for(int i=0; i < resources.size(); i++)	{
        if(resources[i]->getResourceType() == Resource::RESOURCE_PROGRAM) {
            delete resources[i];
        }
    }
    
    resources.clear();
}

String ResourcePool::getName() {
    return name;
}

void ResourcePool::setName(const String &name) {
    this->name = name;
}

void ResourcePool::removeResource(Resource *resource) {
	for(int i=0;i<resources.size();i++) {
		if(resources[i] == resource) {
			resources.erase(resources.begin()+i);
			return;
		}
	}
}

bool ResourcePool::hasResource(Resource *resource) {
	for(int i=0; i < resources.size(); i++) {
		if(resources[i] == resource) {
			return true;
		}
	}
	return false;
}

void ResourcePool::addResource(Resource *resource) {
    resource->addEventListener(this, Event::RESOURCE_CHANGE_EVENT);
    resources.push_back(resource);
    
    // NOCMAKE_TODO: fix this!!
    resource->resourceFileTime = 0; //OSBasics::getFileTime(resource->getResourcePath());
    if(dispatchChangeEvents) {
        dispatchEvent(new Event(), Event::CHANGE_EVENT);
    }
}

void ResourcePool::setFallbackPool(ResourcePool *pool) {
    fallbackPool = pool;
}

bool ResourceLoader::canHandleExtension(const String &extension) {
    for(int i=0; i < extensions.size(); i++) {
        if(extensions[i] == extension) {
            return true;
        }
    }
    return false;
}

TextureResourceLoader::TextureResourceLoader() {
    extensions.push_back("png");
    extensions.push_back("hdr");
    extensions.push_back("jpg");
    extensions.push_back("tga");
    extensions.push_back("psd");
}

Resource *TextureResourceLoader::loadResource(const String &path,  ResourcePool *targetPool) {
    MaterialManager *materialManager = Services()->getMaterialManager();
    Texture *texture = materialManager->createTextureFromFile(path, materialManager->clampDefault, materialManager->mipmapsDefault);
    return texture;
}

void ResourcePool::loadResourcesFromFolderWithLoader(const String &folder, bool recursive, ResourceLoader *loader, const String &containingFolder) {
    vector<OSFileEntry> resourceDir;
    
    resourceDir = Services()->getCore()->parseFolder(folder, false);
    
    for(int i=0; i < resourceDir.size(); i++) {
        if(resourceDir[i].type == OSFileEntry::TYPE_FILE) {
            Resource *newResource = NULL;
            if(loader->canHandleExtension(resourceDir[i].extension)) {
                newResource = loader->loadResource(resourceDir[i].fullPath, this);
            }
            if(newResource) {
                if(newResource->getResourceName() == "") {
                    newResource->setResourceName(resourceDir[i].name);
                }
                newResource->setResourcePath(resourceDir[i].fullPath);
                addResource(newResource);
            }
        } else {
            if(recursive) {
                loadResourcesFromFolderWithLoader(folder+"/"+resourceDir[i].name, true, loader, containingFolder);
            }
        }
    }
}

Resource *ResourcePool::loadResource(const String &path) {
    
    Resource *newResource = getResourceByPath(path);
    if(newResource) {
        return newResource;
    }
    
    OSFileEntry entry(path, OSFileEntry::TYPE_FILE);
    for(int r = 0; r < Services()->getResourceManager()->getNumResourceLoaders(); r++) {
        ResourceLoader *loader = Services()->getResourceManager()->getResourceLoaderAtIndex(r);
        if(loader->canHandleExtension(entry.extension)) {
            newResource = loader->loadResource(entry.fullPath, this);
            if(newResource) {
                newResource->setResourceName(entry.name);
                newResource->setResourcePath(entry.fullPath);
                addResource(newResource);
                break;
            }
        }
    }
    return newResource;
}

Resource *ResourcePool::loadResourceWithName(const String &path, const String &name) {
    
    Resource *newResource = getResourceByPath(path);
    if(newResource) {
        return newResource;
    }
    
    OSFileEntry entry(path, OSFileEntry::TYPE_FILE);
    for(int r = 0; r < Services()->getResourceManager()->getNumResourceLoaders(); r++) {
        ResourceLoader *loader = Services()->getResourceManager()->getResourceLoaderAtIndex(r);
        if(loader->canHandleExtension(entry.extension)) {
            newResource = loader->loadResource(entry.fullPath, this);
            if(newResource) {
                newResource->setResourceName(name);
                newResource->setResourcePath(entry.fullPath);
                addResource(newResource);
                break;
            }
        }
    }
    return newResource;
}

void ResourcePool::loadResourcesFromFolder(const String &folder, bool recursive) {
    for(int r = 0; r < Services()->getResourceManager()->getNumResourceLoaders(); r++) {
        ResourceLoader *loader = Services()->getResourceManager()->getResourceLoaderAtIndex(r);
        loadResourcesFromFolderWithLoader(folder, recursive, loader, "");
    }
}


Resource *ResourcePool::getResourceByPath(const String& resourcePath) const {
	for(int i =0; i < resources.size(); i++) {
		if(resources[i]->getResourcePath() == resourcePath) {
			return resources[i];
		}
	}
    
    if(fallbackPool) {
        return fallbackPool->getResourceByPath(resourcePath);
    } else {
        return NULL;
    }
}

std::vector<Resource*> ResourcePool::getResources(int resourceType) {
	std::vector<Resource*> result;
	for(int i =0; i < resources.size(); i++) {
		if(resources[i]->getResourceType() == resourceType) {
			result.push_back(resources[i]);
		}
	}
    
	return result;
}

Resource *ResourcePool::getResource(int resourceType, const String& resourceName) const {
	for(int i =0; i < resources.size(); i++) {
		if(resources[i]->getResourceName() == resourceName && resources[i]->getResourceType() == resourceType) {
			return resources[i];
		}
	}
	
	if(resourceType == Resource::RESOURCE_TEXTURE && resourceName != "default/default.png") {
		Logger::log("Texture [%s] not found in pool [%s], using default\n", resourceName.c_str(), name.c_str());
		return getResource(Resource::RESOURCE_TEXTURE, "default/default.png");
	}
    
    if(fallbackPool) {
        return fallbackPool->getResource(resourceType, resourceName);
    } else {
        Logger::log("Could not find resource [%s] in pool [%s]\n", resourceName.c_str(), name.c_str());
        
        return NULL;
    }
}

void ResourcePool::checkForChangedFiles() {
	for(int i=0; i < resources.size(); i++) {
		if(resources[i]->reloadOnFileModify == true) {
            
            // NOCMAKE_TODO: fix this!
            time_t newFileTime = 0; //OSBasics::getFileTime(resources[i]->getResourcePath());
            //			printf("%s\n%lld %lld\n", resources[i]->getResourcePath().c_str(), newFileTime, resources[i]->resourceFileTime);
			if((newFileTime != resources[i]->resourceFileTime) && newFileTime != 0) {
				resources[i]->reloadResource();
				resources[i]->resourceFileTime = newFileTime;
			}
		}
	}
}

ResourceManager::ResourceManager() : EventDispatcher() {
    globalPool = new ResourcePool("Global", NULL);
    
    resourceLoaders.push_back(new TextureResourceLoader());
    resourceLoaders.push_back(new ProgramResourceLoader());
    resourceLoaders.push_back(new MaterialResourceLoader());
    resourceLoaders.push_back(new FontResourceLoader());
    resourceLoaders.push_back(new MeshResourceLoader());
    resourceLoaders.push_back(new ScriptResourceLoader());
}

ResourceManager::~ResourceManager() {
    for(int i=0; i < resourceLoaders.size(); i++)	{
        delete resourceLoaders[i];
    }
    
    for(int i=0; i < pools.size(); i++)	{
        delete pools[i];
    }
    pools.clear();
}

void ResourcePool::Update(int elapsed) {
	if(!reloadResourcesOnModify)
		return;
    
	ticksSinceCheck += elapsed;
	if(ticksSinceCheck > RESOURCE_CHECK_INTERVAL) {
		ticksSinceCheck = 0;
		checkForChangedFiles();
	}
}

void ResourceManager::addResourceLoader(ResourceLoader *loader) {
    resourceLoaders.push_back(loader);
}

ResourceLoader *ResourceManager::getResourceLoaderForExtension(const String &extension) {
    for(int i=0; i < resourceLoaders.size(); i++) {
        if(resourceLoaders[i]->canHandleExtension(extension)) {
            return resourceLoaders[i];
        }
    }
    return NULL;
}

void ResourceManager::removeResourceLoader(ResourceLoader *loader) {
    for(int i=0; i < resourceLoaders.size(); i++) {
        if(resourceLoaders[i] == loader) {
            delete resourceLoaders[i];
            resourceLoaders.erase(resourceLoaders.begin() + i);
            return;
        }
    }
}

unsigned int ResourceManager::getNumResourceLoaders() {
    return resourceLoaders.size();
}

ResourceLoader *ResourceManager::getResourceLoaderAtIndex(unsigned int index) {
    if(index <= resourceLoaders.size()) {
        return resourceLoaders[index];
    } else {
        return NULL;
    }
}


MaterialResourceLoader::MaterialResourceLoader() {
    extensions.push_back("mat");
}

Resource *MaterialResourceLoader::loadResource(const String &path, ResourcePool *targetPool) {
    Services()->getMaterialManager()->loadMaterialLibraryIntoPool(targetPool, path);
    return NULL;
}

ProgramResourceLoader::ProgramResourceLoader() {
    extensions.push_back("frag");
    extensions.push_back("vert");
}

Resource *ProgramResourceLoader::loadResource(const String &path, ResourcePool *targetPool) {
    ShaderProgram *newProgram = Services()->getMaterialManager()->createProgramFromFile(path);
    return newProgram;
}

ScriptResourceLoader::ScriptResourceLoader() {
    luaState =  lua_open();
    luaL_openlibs(luaState);
    luaopen_debug(luaState);
    luaopen_Polycode(luaState);
    
    // init duktape
    
    duktapeContext = duk_create_heap_default();
    
    extensions.push_back("lua");
    extensions.push_back("js");
    
    
}

ScriptResourceLoader::~ScriptResourceLoader() {
    lua_close(luaState);
    duk_destroy_heap(duktapeContext);
}

Resource *ScriptResourceLoader::loadResource(const String &path, ResourcePool *targetPool) {
    OSFileEntry entry(path, OSFileEntry::TYPE_FILE);
    Script *newScript = NULL;
    if(entry.extension == "lua") {
        newScript = new LuaScript(luaState, path);
    } else if(entry.extension == "js") {
        newScript = new JSScript(duktapeContext, path);
    }
    return newScript;
}

FontResourceLoader::FontResourceLoader() {
    
    FT_Init_FreeType(&FTLibrary);
    FT_Library_SetLcdFilter(FTLibrary, FT_LCD_FILTER_LIGHT);
    
    extensions.push_back("ttf");
    extensions.push_back("otf");
}

FontResourceLoader::~FontResourceLoader() {
    FT_Done_FreeType(FTLibrary);
}

MeshResourceLoader::MeshResourceLoader() {
    extensions.push_back("mesh");
}

Resource *MeshResourceLoader::loadResource(const String &path, ResourcePool *targetPool) {
    Mesh *mesh = Services()->getRenderer()->createMesh(path);
    return mesh;
}


Resource *FontResourceLoader::loadResource(const String &path, ResourcePool *targetPool) {
    OSFileEntry entry = OSFileEntry(path, OSFileEntry::TYPE_FILE);
    Font *font = new Font(path, FTLibrary);
    font->setResourceName(entry.nameWithoutExtension);
    return font;
}

void ResourceManager::handleEvent(Event *event) {
	if(event->getEventCode() == Event::RESOURCE_CHANGE_EVENT) {
		dispatchEvent(new Event(), Event::CHANGE_EVENT);	
	}
}

ResourcePool *ResourceManager::getGlobalPool() {
    return globalPool;
}

void ResourceManager::Update(int elapsed) {
    globalPool->Update(elapsed);
    for(int i=0; i < pools.size(); i++) {
        pools[i]->Update(elapsed);
    }
}

void ResourceManager::removeResource(Resource *resource) {
    globalPool->removeResource(resource);
    for(int i=0; i < pools.size(); i++) {
        pools[i]->removeResource(resource);
    }
}

void ResourceManager::addResourcePool(ResourcePool *pool) {
    pools.push_back(pool);
}

ResourcePool *ResourceManager::getResourcePoolByName(const String &name) {
    printf("request resource pool [%s]\n", name.c_str());
    for(int i=0; i < pools.size(); i++) {
        if(pools[i]->getName() == name) {
            return pools[i];
        }
    }
    printf("resource pool not found!\n");
    return NULL;
}

void ResourceManager::removeResourcePool(ResourcePool *pool) {
    for(int i=0; i < pools.size(); i++) {
        if(pools[i] == pool) {
            pools.erase(pools.begin()+i);
            return;
        }
    }
}

void ResourceManager::subscribeToResourcePool(ResourcePool *pool) {
    pool->resourceSubscribers++;
}

void ResourceManager::unsubscibeFromResourcePool(ResourcePool *pool) {
    pool->resourceSubscribers--;
    if(pool->deleteOnUnsubscribe && pool->resourceSubscribers < 1) {
        delete pool;
    }
}

std::vector<Resource*> ResourceManager::getResources(int resourceType) {
	std::vector<Resource*> result;

    std::vector<Resource*> subresult = globalPool->getResources(resourceType);
    result.insert(result.end(), subresult.begin(), subresult.end());
    
	for(int i =0; i < pools.size(); i++) {
        subresult = pools[i]->getResources(resourceType);
        result.insert(result.end(), subresult.begin(), subresult.end());
	}
    
	return result;
}
