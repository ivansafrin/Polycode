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
}

ResourceManager::~ResourceManager() {
		printf("Shutting down resource manager...\n");
		PHYSFS_deinit();
		for(int i=0; i < resources.size(); i++)	{
			delete resources[i];
		}
		resources.clear();
}

void ResourceManager::parseShaders(const String& dirPath, bool recursive) {
	vector<OSFileEntry> resourceDir;
	resourceDir = OSBasics::parseFolder(dirPath, false);
	
	for(int i=0; i < resourceDir.size(); i++) {	
		if(resourceDir[i].type == OSFileEntry::TYPE_FILE) {
			if(resourceDir[i].extension == "mat") {
				Logger::log("Adding shaders from %s\n", resourceDir[i].nameWithoutExtension.c_str());
				TiXmlDocument doc(resourceDir[i].fullPath.c_str());
				doc.LoadFile();
				if(doc.Error()) {
					Logger::log("XML Error: %s\n", doc.ErrorDesc());
				} else {
					TiXmlElement *mElem = doc.RootElement()->FirstChildElement("shaders");
					
					if(mElem) {
						TiXmlNode* pChild;					
						for (pChild = mElem->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {						
							Shader *newShader = CoreServices::getInstance()->getMaterialManager()->createShaderFromXMLNode(pChild);
							if(newShader != NULL) {
								Logger::log("Adding shader %s\n", newShader->getName().c_str());
								newShader->setResourceName(newShader->getName());
								resources.push_back(newShader);
								 CoreServices::getInstance()->getMaterialManager()->registerShader(newShader);
							}
						}
					}
				}
			}
		} else {
			if(recursive)
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
			for(int m=0; m < shaderModules.size(); m++) {
				PolycodeShaderModule *shaderModule = shaderModules[m];
				if(shaderModule->acceptsExtension(resourceDir[i].extension)) {
					Resource *newProgram = shaderModule->createProgramFromFile(resourceDir[i].extension, resourceDir[i].fullPath);
					if(newProgram) {
						newProgram->setResourceName(resourceDir[i].name);
						newProgram->setResourcePath(resourceDir[i].fullPath);				
						resources.push_back(newProgram);					
					}
				}
			}
		} else {
			if(recursive)
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
					resources.push_back(materials[m]);
					materialManager->addMaterial(materials[m]);
				}
			}
		} else {
			if(recursive)
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
				Logger::log("Adding cubemaps from %s\n", resourceDir[i].nameWithoutExtension.c_str());
				TiXmlDocument doc(resourceDir[i].fullPath.c_str());
				doc.LoadFile();
				if(doc.Error()) {
					Logger::log("XML Error: %s\n", doc.ErrorDesc());
				} else {
					TiXmlElement *mElem = doc.RootElement()->FirstChildElement("cubemaps");
					
					if(mElem) {
						TiXmlNode* pChild;					
						for (pChild = mElem->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {
							Cubemap *newMat = CoreServices::getInstance()->getMaterialManager()->cubemapFromXMLNode(pChild);
							//						newMat->setResourceName(newMat->getName());
							if(newMat)
								resources.push_back(newMat);
						}
					}
				}
			}
		} else {
			if(recursive)
				parseCubemaps(dirPath+"/"+resourceDir[i].name, true);
		}
	}	
}

void ResourceManager::addResource(Resource *resource) {
	resources.push_back(resource);
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
					} else {
						t->setResourceName(basePath+"/"+resourceDir[i].name);
					}
					resources.push_back(t);
				}
			}
		} else {
			if(recursive) {
				if(basePath == "") {			
					parseTextures(dirPath+"/"+resourceDir[i].name, true, resourceDir[i].name);
				} else {
					parseTextures(dirPath+"/"+resourceDir[i].name, true, basePath+"/"+resourceDir[i].name);
				}
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
		} else {
			if(recursive)
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

Resource *ResourceManager::getResource(int resourceType, const String& resourceName) const {
	Logger::log("requested %s\n", resourceName.c_str());
	for(int i =0; i < resources.size(); i++) {
//		Logger::log("is it %s?\n", resources[i]->getResourceName().c_str());		
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

// Would it make more sense to pass back, like, something like an ObjectEntry here? Lua hates vectors.
vector<Resource *> ResourceManager::getResources(int resourceType) {
	vector<Resource *> result;
	Logger::log("requested all of type %d\n", resourceType);
	for(int i =0; i < resources.size(); i++) {
		//		Logger::log("is it %s?\n", resources[i]->getResourceName().c_str());		
		if(resources[i]->getResourceType() == resourceType) {
			result.push_back(resources[i]);
		}
	}
	return result;
}
