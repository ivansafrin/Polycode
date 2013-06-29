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

ResourceManager::ResourceManager() {
	PHYSFS_init(NULL);
	ticksSinceCheck = 0;
	reloadResourcesOnModify = false;
}

ResourceManager::~ResourceManager() {
	printf("Shutting down resource manager...\n");
	PHYSFS_deinit();

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

void ResourceManager::parseShaders(const String& dirPath, bool recursive) {
	vector<OSFileEntry> resourceDir;
	resourceDir = OSBasics::parseFolder(dirPath, false);

	for(int i=0; i < resourceDir.size(); i++) {
		if(resourceDir[i].type == OSFileEntry::TYPE_FILE) {
			if(resourceDir[i].extension == "mat") {
				MaterialManager *materialManager = CoreServices::getInstance()->getMaterialManager();
				std::vector<Shader*> shaders = materialManager->loadShadersFromFile(resourceDir[i].fullPath);
				
				for(int s=0; s < shaders.size(); s++) {
					addResource(shaders[s]);
					materialManager->addShader(shaders[s]);
				}
			}
		} else if(recursive) {
			parseShaders(dirPath+"/"+resourceDir[i].name, true);
		}
	}
}

void ResourceManager::addShaderModule(PolycodeShaderModule *module) {
	shaderModules.push_back(module);
}

void ResourceManager::parsePrograms(const String& dirPath, bool recursive) {
	vector<OSFileEntry> resourceDir;
	resourceDir = OSBasics::parseFolder(dirPath, false);
	for(int i=0; i < resourceDir.size(); i++) {
		if(resourceDir[i].type == OSFileEntry::TYPE_FILE) {
			MaterialManager *materialManager = CoreServices::getInstance()->getMaterialManager();

			ShaderProgram *newProgram = materialManager->createProgramFromFile(resourceDir[i].fullPath);
			if(newProgram) {
				newProgram->setResourceName(resourceDir[i].name);
				newProgram->setResourcePath(resourceDir[i].fullPath);
				addResource(newProgram);
			}
		} else if(recursive) { 
			parsePrograms(dirPath+"/"+resourceDir[i].name, true);
		}
	}
}

void ResourceManager::parseMaterials(const String& dirPath, bool recursive) {
	vector<OSFileEntry> resourceDir;
	resourceDir = OSBasics::parseFolder(dirPath, false);

	for(int i=0; i < resourceDir.size(); i++) {
		if(resourceDir[i].type == OSFileEntry::TYPE_FILE) {
			if(resourceDir[i].extension == "mat") {
				MaterialManager *materialManager = CoreServices::getInstance()->getMaterialManager();
				std::vector<Material*> materials = materialManager->loadMaterialsFromFile(resourceDir[i].fullPath);

				for(int m=0; m < materials.size(); m++) {
					materials[m]->setResourceName(materials[m]->getName());
					addResource(materials[m]);
					materialManager->addMaterial(materials[m]);
				}
			}
		} else if(recursive) {
			parseMaterials(dirPath+"/"+resourceDir[i].name, true);
		}
	}
}

void ResourceManager::parseCubemaps(const String& dirPath, bool recursive) {
	vector<OSFileEntry> resourceDir;
	resourceDir = OSBasics::parseFolder(dirPath, false);
	
	for(int i=0; i < resourceDir.size(); i++) {
		if(resourceDir[i].type == OSFileEntry::TYPE_FILE) {
			if(resourceDir[i].extension == "mat") {

				MaterialManager *materialManager = CoreServices::getInstance()->getMaterialManager();
				std::vector<Cubemap*> cubemaps = materialManager->loadCubemapsFromFile(resourceDir[i].fullPath);
				for(int c=0; c < cubemaps.size(); c++) {
					addResource(cubemaps[c]);
				}
			}
		} else if(recursive) {
			parseCubemaps(dirPath+"/"+resourceDir[i].name, true);
		}
	}
}

bool ResourceManager::hasResource(Resource *resource) {
	for(int i=0; i < resources.size(); i++) {
		if(resources[i] == resource) {
			return true;
		}
	}
	return false;
}

void ResourceManager::addResource(Resource *resource) {
	resources.push_back(resource);
	resource->resourceFileTime = OSBasics::getFileTime(resource->getResourcePath());
}

void ResourceManager::removeResource(Resource *resource) {
	for(int i=0;i<resources.size();i++) {
		if(resources[i] == resource) {
			resources.erase(resources.begin()+i);
			return;
		}
	}
}


void ResourceManager::parseTextures(const String& dirPath, bool recursive, const String& basePath) {
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
					addResource(t);
				}
			}
		} else if(recursive) {
			if(basePath == "") {
				parseTextures(dirPath+"/"+resourceDir[i].name, true, resourceDir[i].name);
			} else {
				parseTextures(dirPath+"/"+resourceDir[i].name, true, basePath+"/"+resourceDir[i].name);
			}
		}
	}
}

void ResourceManager::parseOthers(const String& dirPath, bool recursive) {
	vector<OSFileEntry> resourceDir;
	resourceDir = OSBasics::parseFolder(dirPath, false);
	for(int i=0; i < resourceDir.size(); i++) {
		if(resourceDir[i].type == OSFileEntry::TYPE_FILE) {
			if(resourceDir[i].extension == "ttf") {
				Logger::log("Registering font: %s\n", resourceDir[i].nameWithoutExtension.c_str());
				CoreServices::getInstance()->getFontManager()->registerFont(resourceDir[i].nameWithoutExtension, resourceDir[i].fullPath);
			}
		} else if(recursive) {
			parseOthers(dirPath+"/"+resourceDir[i].name, true);
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


void ResourceManager::addDirResource(const String& dirPath, bool recursive) {
	parseTextures(dirPath, recursive, "");
	parsePrograms(dirPath, recursive);
	parseShaders(dirPath, recursive);
	parseCubemaps(dirPath, recursive);
	parseMaterials(dirPath, recursive);
	parseOthers(dirPath, recursive);
}

Resource *ResourceManager::getResourceByPath(const String& resourcePath) const {
	Logger::log("requested %s\n", resourcePath.c_str());
	for(int i =0; i < resources.size(); i++) {
		if(resources[i]->getResourcePath() == resourcePath) {
			return resources[i];
		}
	}
	Logger::log("return NULL\n");
	return NULL;
}

Resource *ResourceManager::getResource(int resourceType, const String& resourceName) const {
	Logger::log("requested %s\n", resourceName.c_str());
	for(int i =0; i < resources.size(); i++) {
		if(resources[i]->getResourceName() == resourceName && resources[i]->getResourceType() == resourceType) {
			return resources[i];
		}
	}

	if(resourceType == Resource::RESOURCE_TEXTURE && resourceName != "default/default.png") {
		Logger::log("Texture not found, using default\n");
		return getResource(Resource::RESOURCE_TEXTURE, "default/default.png");
	}
	Logger::log("return NULL\n");
	// need to add some sort of default resource for each type
	return NULL;
}

void ResourceManager::checkForChangedFiles() {
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

void ResourceManager::Update(int elapsed) {
	if(!reloadResourcesOnModify)
		return;

	ticksSinceCheck += elapsed;
	if(ticksSinceCheck > RESOURCE_CHECK_INTERVAL) {
		ticksSinceCheck = 0;
		checkForChangedFiles();
	}
}

std::vector<Resource*> ResourceManager::getResources(int resourceType) {
	std::vector<Resource*> result;
	for(int i =0; i < resources.size(); i++) {
		if(resources[i]->getResourceType() == resourceType) {
			result.push_back(resources[i]);
		}
	}
	return result;
}
