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

#include "PolyResourceManager.h"
#include "PolyCoreServices.h"
#include "PolyCubemap.h"
#include "PolyRenderer.h"
#include "PolyMaterialManager.h"
#include "PolyModule.h"
#include "PolyFontManager.h"
#include "PolyLogger.h"
#include "PolyMaterial.h"
#include "PolyShader.h"
#include "PolyTexture.h"
#include "OSBasics.h"

#include "physfs.h"
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
            resources[i] = NULL;
        }
    }
    
    for(int i=0; i < resources.size(); i++)	{
        if(resources[i]) {
            if(resources[i]->getResourceType() == Resource::RESOURCE_SHADER) {
                delete resources[i];
                resources[i] = NULL;
            }
        }
    }
    
    for(int i=0; i < resources.size(); i++)	{
        if(resources[i]) {
            if(resources[i]->getResourceType() == Resource::RESOURCE_PROGRAM) {
                delete resources[i];
                resources[i] = NULL;
            }
        }
    }
    
    for(int i=0; i < resources.size(); i++)	{
        if(resources[i]) {
            if(resources[i]->getResourceType() == Resource::RESOURCE_TEXTURE) {
                Services()->getRenderer()->destroyTexture((Texture*)resources[i]);
                resources[i] = NULL;
            }
        }
    }
    
    for(int i=0; i < resources.size(); i++)	{
        delete resources[i];
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
    resource->resourceFileTime = OSBasics::getFileTime(resource->getResourcePath());
    if(dispatchChangeEvents) {
        dispatchEvent(new Event(), Event::CHANGE_EVENT);
    }
}

void ResourcePool::setFallbackPool(ResourcePool *pool) {
    fallbackPool = pool;
}

void ResourceManager::addDirResource(const String& dirPath, bool recursive) {
	parseTexturesIntoPool(globalPool, dirPath, recursive, "");
	parseProgramsIntoPool(globalPool, dirPath, recursive);
	parseShadersIntoPool(globalPool, dirPath, recursive);
	parseCubemapsIntoPool(globalPool, dirPath, recursive);
	parseMaterialsIntoPool(globalPool, dirPath, recursive);
	parseOtherIntoPool(globalPool, dirPath, recursive);
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
        Logger::log("Could not find resource for path [%s] in pool [%s]\n", resourcePath.c_str(), name.c_str());
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
			time_t newFileTime = OSBasics::getFileTime(resources[i]->getResourcePath());
            //			printf("%s\n%lld %lld\n", resources[i]->getResourcePath().c_str(), newFileTime, resources[i]->resourceFileTime);
			if((newFileTime != resources[i]->resourceFileTime) && newFileTime != 0) {
				resources[i]->reloadResource();
				resources[i]->resourceFileTime = newFileTime;
			}
		}
	}
}

ResourceManager::ResourceManager() : EventDispatcher() {
	PHYSFS_init(NULL);
    globalPool = new ResourcePool("Global", NULL);
}

ResourceManager::~ResourceManager() {
    printf("Shutting down resource manager...\n");
    PHYSFS_deinit();

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

void ResourceManager::parseShadersIntoPool(ResourcePool *pool, const String& dirPath, bool recursive) {
	vector<OSFileEntry> resourceDir;
	resourceDir = OSBasics::parseFolder(dirPath, false);
	
	for(int i=0; i < resourceDir.size(); i++) {	
		if(resourceDir[i].type == OSFileEntry::TYPE_FILE) {
			if(resourceDir[i].extension == "mat") {
				MaterialManager *materialManager = CoreServices::getInstance()->getMaterialManager();
				std::vector<Shader*> shaders = materialManager->loadShadersFromFile(pool, resourceDir[i].fullPath);
				
				for(int s=0; s < shaders.size(); s++) {
					pool->addResource(shaders[s]);
				}
			}
		} else {
			if(recursive)
				parseShadersIntoPool(pool, dirPath+"/"+resourceDir[i].name, true);
		}
	}
}

void ResourceManager::parseOtherIntoPool(ResourcePool *pool, const String& dirPath, bool recursive) {
    vector<OSFileEntry> resourceDir;
    resourceDir = OSBasics::parseFolder(dirPath, false);
    for(int i=0; i < resourceDir.size(); i++) {
        if(resourceDir[i].type == OSFileEntry::TYPE_FILE) {
            if(resourceDir[i].extension == "ttf") {
                Logger::log("Registering font: %s\n", resourceDir[i].nameWithoutExtension.c_str());
                CoreServices::getInstance()->getFontManager()->registerFont(resourceDir[i].nameWithoutExtension, resourceDir[i].fullPath);
            }
        } else {
            if(recursive)
                parseOtherIntoPool(pool, dirPath+"/"+resourceDir[i].name, true);
        }
    }
}

void ResourceManager::parseProgramsIntoPool(ResourcePool *pool, const String& dirPath, bool recursive) {
	vector<OSFileEntry> resourceDir;
	resourceDir = OSBasics::parseFolder(dirPath, false);
	for(int i=0; i < resourceDir.size(); i++) {	
		if(resourceDir[i].type == OSFileEntry::TYPE_FILE) {
			MaterialManager *materialManager = CoreServices::getInstance()->getMaterialManager();
			
			ShaderProgram *newProgram = materialManager->createProgramFromFile(resourceDir[i].fullPath);
			if(newProgram) {
				newProgram->setResourceName(resourceDir[i].name);
				newProgram->setResourcePath(resourceDir[i].fullPath);
				pool->addResource(newProgram);
			}			
		} else {
			if(recursive)
				parseProgramsIntoPool(pool, dirPath+"/"+resourceDir[i].name, true);
		}
	}	
}

void ResourceManager::parseMaterialsIntoPool(ResourcePool *pool, const String& dirPath, bool recursive) {
	vector<OSFileEntry> resourceDir;
	resourceDir = OSBasics::parseFolder(dirPath, false);
	
	for(int i=0; i < resourceDir.size(); i++) {	
		if(resourceDir[i].type == OSFileEntry::TYPE_FILE) {
			if(resourceDir[i].extension == "mat") {				
				MaterialManager *materialManager = CoreServices::getInstance()->getMaterialManager();			
				std::vector<Material*> materials = materialManager->loadMaterialsFromFile(pool, resourceDir[i].fullPath);

				for(int m=0; m < materials.size(); m++) {
					materials[m]->setResourceName(materials[m]->getName());
					pool->addResource(materials[m]);
				}
			}
		} else {
			if(recursive)
				parseMaterialsIntoPool(pool, dirPath+"/"+resourceDir[i].name, true);
		}
	}
}

void ResourceManager::parseCubemapsIntoPool(ResourcePool *pool, const String& dirPath, bool recursive) {
	vector<OSFileEntry> resourceDir;
	resourceDir = OSBasics::parseFolder(dirPath, false);
	
	for(int i=0; i < resourceDir.size(); i++) {	
		if(resourceDir[i].type == OSFileEntry::TYPE_FILE) {
			if(resourceDir[i].extension == "mat") {
			
				MaterialManager *materialManager = CoreServices::getInstance()->getMaterialManager();			
				std::vector<Cubemap*> cubemaps = materialManager->loadCubemapsFromFile(resourceDir[i].fullPath);			
				for(int c=0; c < cubemaps.size(); c++) {
					pool->addResource(cubemaps[c]);
				}			
			}
		} else {
			if(recursive)
				parseCubemapsIntoPool(pool, dirPath+"/"+resourceDir[i].name, true);
		}
	}	
}

void ResourceManager::handleEvent(Event *event) {
	if(event->getEventCode() == Event::RESOURCE_CHANGE_EVENT) {
		dispatchEvent(new Event(), Event::CHANGE_EVENT);	
	}
}

ResourcePool *ResourceManager::getGlobalPool() {
    return globalPool;
}

void ResourceManager::parseTexturesIntoPool(ResourcePool *pool, const String& dirPath, bool recursive, const String& basePath) {
	MaterialManager *materialManager = CoreServices::getInstance()->getMaterialManager();
	vector<OSFileEntry> resourceDir;
	resourceDir = OSBasics::parseFolder(dirPath, false);
	for(int i=0; i < resourceDir.size(); i++) {	
		if(resourceDir[i].type == OSFileEntry::TYPE_FILE) {
			if(resourceDir[i].extension == "png") {
				Logger::log("Adding texture %s\n", resourceDir[i].nameWithoutExtension.c_str());
				Texture *t = materialManager->createTextureFromFile(resourceDir[i].fullPath, materialManager->clampDefault, materialManager->mipmapsDefault);
				if(t) {
					if(basePath == "") {
						t->setResourceName(resourceDir[i].name);
						t->setResourcePath(resourceDir[i].fullPath);
					} else {
						t->setResourceName(basePath+"/"+resourceDir[i].name);
						t->setResourcePath(resourceDir[i].fullPath);						
					}
					pool->addResource(t);
				}
			}
		} else {
			if(recursive) {
				if(basePath == "") {			
					parseTexturesIntoPool(pool, dirPath+"/"+resourceDir[i].name, true, resourceDir[i].name);
				} else {
					parseTexturesIntoPool(pool, dirPath+"/"+resourceDir[i].name, true, basePath+"/"+resourceDir[i].name);
				}
			}
		}
	}
}

void ResourceManager::addArchive(const String& path) {
	if(PHYSFS_addToSearchPath(path.c_str(), 1) == 0) {	
		Logger::log("Error adding archive to resource manager... %s\n", PHYSFS_getLastError());
	} else {
		Logger::log("Added archive: %s\n", path.c_str());
	}
}

void ResourceManager::removeArchive(const String& path) {
	PHYSFS_removeFromSearchPath(path.c_str());
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

