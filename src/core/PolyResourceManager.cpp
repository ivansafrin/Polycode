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
#include "polycode/core/PolyLogger.h"
#include "polycode/core/PolyMaterial.h"
#include "polycode/core/PolyShader.h"
#include "polycode/core/PolyTexture.h"
#include "polycode/core/PolyRenderer.h"
#include "polycode/core/PolyFont.h"
#include "polycode/core/PolyMesh.h"
#include "polycode/core/PolyScript.h"
#include "polycode/core/PolyCore.h"
#ifndef NO_LUA
	#include "polycode/bindings/lua/PolycodeLua.h"
#endif
#include "polycode/bindings/javascript/PolycodeJS.h"
#include "tinyxml.h"

using std::vector;
using namespace Polycode;

bool ResourcePool::defaultReloadResourcesOnModify = false;

ResourcePool::ResourcePool() : fallbackPool(NULL), resourceSubscribers(0), ticksSinceCheck(0), deleteOnUnsubscribe(false), dispatchChangeEvents(false) {
	
}

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
}

String ResourcePool::getName() {
	return name;
}

void ResourcePool::setName(const String &name) {
	this->name = name;
}

void ResourcePool::removeResource(std::shared_ptr<Resource> resource) {
	for(int i=0;i<resources.size();i++) {
		if(resources[i] == resource) {
			resources.erase(resources.begin()+i);
			return;
		}
	}
}

bool ResourcePool::hasResource(std::shared_ptr<Resource> resource) {
	for(int i=0; i < resources.size(); i++) {
		if(resources[i] == resource) {
			return true;
		}
	}
	return false;
}

void ResourcePool::addResource(std::shared_ptr<Resource> resource) {
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

std::shared_ptr<Resource> TextureResourceLoader::loadResource(const String &path,  ResourcePool *targetPool) {
	Image *image = new Image(path);
	std::shared_ptr<Texture> texture = std::make_shared<Texture>(image, Texture::clampDefault, Texture::mipmapsDefault);
	delete image;
	return texture;
}

std::shared_ptr<Shader> ResourcePool::createShaderFromXMLNode(TiXmlNode *node) {
	TiXmlElement *nodeElement = node->ToElement();
	if (!nodeElement) return nullptr; // Skip comment nodes

	TiXmlNode* pChild;
	std::shared_ptr<Shader> retShader;
	std::shared_ptr<ShaderProgram> vp;
	std::shared_ptr<ShaderProgram> fp;

	for (pChild = node->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {
		TiXmlElement *pChildElement = pChild->ToElement();
		if (!pChildElement) continue; // Skip comment nodes

		if (strcmp(pChild->Value(), "vp") == 0) {
			String vpFileName = String(pChildElement->Attribute("source"));
			vp = std::static_pointer_cast<ShaderProgram>(loadResource(vpFileName));
		}
		if (strcmp(pChild->Value(), "fp") == 0) {
			String fpFileName = String(pChildElement->Attribute("source"));
			fp = std::static_pointer_cast<ShaderProgram>(loadResource(fpFileName));
		}

	}
	if (vp != NULL && fp != NULL) {
		retShader = std::make_shared<Shader>(fp, vp);
		retShader->setName(String(nodeElement->Attribute("name")));
	}

	if (!retShader) {
		return NULL;
	}

	int numPointLights = 0;
	int numSpotLights = 0;

	if (nodeElement->Attribute("numPointLights")) {
		numPointLights = atoi(nodeElement->Attribute("numPointLights"));
	}
	if (nodeElement->Attribute("numSpotLights")) {
		numSpotLights = atoi(nodeElement->Attribute("numSpotLights"));
	}

	retShader->screenShader = false;

	if (nodeElement->Attribute("screen")) {
		if (String(nodeElement->Attribute("screen")) == "true") {
			retShader->screenShader = true;
		}
	}

	if (retShader) {
		retShader->numPointLights = numPointLights;
		retShader->numSpotLights = numSpotLights;
	}

	return retShader;
}


void ResourcePool::loadShadersFromFile(const String &fileName) {
	std::vector<Shader*> retVector;
	TiXmlDocument doc(fileName.c_str());
	doc.LoadFile();
	if (doc.Error()) {
		Logger::log("XML Error: %s\n", doc.ErrorDesc());
	}
	else {
		TiXmlElement *mElem = doc.RootElement()->FirstChildElement("shaders");
		if (mElem) {
			TiXmlNode* pChild;
			for (pChild = mElem->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {
				std::shared_ptr<Shader> newShader = createShaderFromXMLNode(pChild);
				if (newShader != NULL) {
					Logger::log("Adding shader %s\n", newShader->getName().c_str());
					newShader->setResourceName(newShader->getName());
					addResource(newShader);
				}
			}
		}
	}
}

std::shared_ptr<Cubemap> ResourcePool::cubemapFromXMLNode(TiXmlNode *node) {
	TiXmlElement *nodeElement = node->ToElement();
	if (!nodeElement) return NULL; // Skip comment nodes

	std::shared_ptr<Cubemap> newCubemap;

	String name = nodeElement->Attribute("name");
	String xPos = nodeElement->Attribute("xPos");
	String xNeg = nodeElement->Attribute("xNeg");
	String yPos = nodeElement->Attribute("yPos");
	String yNeg = nodeElement->Attribute("yNeg");
	String zPos = nodeElement->Attribute("zPos");
	String zNeg = nodeElement->Attribute("zNeg");

	newCubemap = std::make_shared<Cubemap>(
		std::static_pointer_cast<Texture>(loadResource(xPos)),
		std::static_pointer_cast<Texture>(loadResource(xNeg)),
		std::static_pointer_cast<Texture>(loadResource(yPos)),
		std::static_pointer_cast<Texture>(loadResource(yNeg)),
		std::static_pointer_cast<Texture>(loadResource(zPos)),
		std::static_pointer_cast<Texture>(loadResource(zNeg))
		);
	newCubemap->setResourceName(name);
	return newCubemap;
}

void ResourcePool::loadCubemapsFromFile(const String &fileName) {
	TiXmlDocument doc(fileName.c_str());
	doc.LoadFile();

	if (doc.Error()) {
		Logger::log("XML Error: %s\n", doc.ErrorDesc());
	}
	else {
		TiXmlElement *mElem = doc.RootElement()->FirstChildElement("cubemaps");
		if (mElem) {
			TiXmlNode* pChild;
			for (pChild = mElem->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {
				std::shared_ptr<Cubemap> newCubemap = cubemapFromXMLNode(pChild);
				if (newCubemap) {
					addResource(newCubemap);
				}
			}
		}
	}
}

std::shared_ptr<Material> ResourcePool::materialFromXMLNode(TiXmlNode *node) {
	TiXmlElement *nodeElement = node->ToElement();
	if (!nodeElement) return NULL; // Skip comment nodes

	String mname = nodeElement->Attribute("name");
	TiXmlNode* pChild, *pChild2, *pChild3;

	vector<ShaderPass> shaderPasses;
	vector<ShaderRenderTarget*> renderTargets;

	std::shared_ptr<Material> newMaterial = std::make_shared<Material>(mname);

	newMaterial->setResourceName(mname);

	if (nodeElement->Attribute("screen")) {
		if (String(nodeElement->Attribute("screen")) == "true") {
			newMaterial->screenMaterial = true;
		}
	}

	if (nodeElement->Attribute("blendingMode")) {
		newMaterial->blendingMode = atoi(nodeElement->Attribute("blendingMode"));
	}

	for (pChild3 = node->FirstChild(); pChild3 != 0; pChild3 = pChild3->NextSibling()) {
		TiXmlElement *pChild3Element = pChild3->ToElement();
		if (!pChild3Element) continue; // Skip comment nodes

		if (strcmp(pChild3->Value(), "rendertargets") == 0) {

			if (pChild3Element->Attribute("type")) {
				if (strcmp(pChild3Element->Attribute("type"), "rgba_fp16") == 0) {
					newMaterial->fp16RenderTargets = true;
				}
			}

			for (pChild = pChild3->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {
				TiXmlElement *pChildElement = pChild->ToElement();
				if (!pChildElement) continue; // Skip comment nodes

				if (strcmp(pChild->Value(), "rendertarget") == 0) {
					ShaderRenderTarget *newTarget = new ShaderRenderTarget;
					newTarget->id = pChildElement->Attribute("id");

					newTarget->width = CoreServices::getInstance()->getCore()->getXRes();
					newTarget->height = CoreServices::getInstance()->getCore()->getYRes();

					newTarget->sizeMode = ShaderRenderTarget::SIZE_MODE_PIXELS;
					if (pChildElement->Attribute("width") && pChildElement->Attribute("height")) {
						newTarget->width = atof(pChildElement->Attribute("width"));
						newTarget->height = atof(pChildElement->Attribute("height"));
						if (pChildElement->Attribute("sizeMode")) {
							if (strcmp(pChildElement->Attribute("sizeMode"), "normalized") == 0) {
								newTarget->sizeMode = ShaderRenderTarget::SIZE_MODE_NORMALIZED;
								if (newTarget->width > 1.0f)
									newTarget->width = 1.0f;
								if (newTarget->height > 1.0f)
									newTarget->height = 1.0f;
							}
						}
					}

					newTarget->normalizedWidth = -1;
					newTarget->normalizedHeight = -1;
					newMaterial->recreateRenderTarget(newTarget);
					renderTargets.push_back(newTarget);
				}
			}
		}
	}

	for (pChild3 = node->FirstChild(); pChild3 != 0; pChild3 = pChild3->NextSibling()) {
		TiXmlElement *pChild3Element = pChild3->ToElement();
		if (!pChild3Element) continue; // Skip comment nodes

		if (strcmp(pChild3->Value(), "shader") == 0) {
			ShaderPass shaderPass;

			TiXmlElement *snodeElement = pChild3->ToElement();
			if (snodeElement) {
				shaderPass.shader = std::static_pointer_cast<Shader>(getResource(Resource::RESOURCE_SHADER, snodeElement->Attribute("name")));
			}

			TiXmlElement *nodeElement = pChild3->ToElement();
			if (nodeElement->Attribute("wireframe")) {
				shaderPass.wireframe = String(nodeElement->Attribute("wireframe")) == "true";
			}

			if (shaderPass.shader) {
				shaderPass.shaderBinding = std::make_shared<ShaderBinding>();
				shaderPasses.push_back(shaderPass);
				for (pChild = pChild3->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {
					TiXmlElement *pChildElement = pChild->ToElement();
					if (!pChildElement) continue; // Skip comment nodes

					if (strcmp(pChild->Value(), "params") == 0) {
						for (pChild2 = pChild->FirstChild(); pChild2 != 0; pChild2 = pChild2->NextSibling()) {
							TiXmlElement *pChild2Element = pChild2->ToElement();
							if (!pChild2Element) continue; // Skip comment nodes

							if (strcmp(pChild2->Value(), "param") == 0) {
								String pname = pChild2Element->Attribute("name");

								String pvalue = pChild2Element->Attribute("value");
								int type = shaderPass.shader->getExpectedParamType(pname);
								std::shared_ptr<LocalShaderParam> param = shaderPass.shaderBinding->addParamFromData(pname, pvalue);
							}
						}
					}
					if (strcmp(pChild->Value(), "targettextures") == 0) {
						for (pChild2 = pChild->FirstChild(); pChild2 != 0; pChild2 = pChild2->NextSibling()) {
							TiXmlElement *pChild2Element = pChild2->ToElement();
							if (!pChild2Element) continue; // Skip comment nodes

							if (strcmp(pChild2->Value(), "targettexture") == 0) {

								RenderTargetBinding* newBinding = new RenderTargetBinding;
								newBinding->id = pChild2Element->Attribute("id");

								newBinding->name = "";
								if (pChild2Element->Attribute("name")) {
									newBinding->name = pChild2Element->Attribute("name");
								}
								String mode = pChild2Element->Attribute("mode");
								if (strcmp(mode.c_str(), "in") == 0) {
									newBinding->mode = RenderTargetBinding::MODE_IN;
								}
								else if (strcmp(mode.c_str(), "color") == 0) {
									newBinding->mode = RenderTargetBinding::MODE_COLOR;
								}
								else if (strcmp(mode.c_str(), "depth") == 0) {
									newBinding->mode = RenderTargetBinding::MODE_DEPTH;
								}
								else {
									newBinding->mode = RenderTargetBinding::MODE_OUT;
								}

								shaderPass.shaderBinding->addRenderTargetBinding(newBinding);

								for (int l = 0; l < renderTargets.size(); l++) {
									if (renderTargets[l]->id == newBinding->id) {
										printf("Assigning texture to %s\n", newBinding->id.c_str());
										newBinding->buffer = renderTargets[l]->buffer;
									}
								}
							}
						}
					}
					if (strcmp(pChild->Value(), "textures") == 0) {
						for (pChild2 = pChild->FirstChild(); pChild2 != 0; pChild2 = pChild2->NextSibling()) {
							TiXmlElement *pChild2Element = pChild2->ToElement();
							if (!pChild2Element) continue; // Skip comment nodes

							if (strcmp(pChild2->Value(), "texture") == 0) {
								String tname = "";
								if (pChild2Element->Attribute("name")) {
									tname = pChild2Element->Attribute("name");
								}
								std::shared_ptr<Texture> texture = std::static_pointer_cast<Texture>(loadResource(pChild2Element->GetText()));
								shaderPass.shaderBinding->setTextureForParam(tname, texture);
							}

							if (strcmp(pChild2->Value(), "cubemap") == 0) {
								String tname = "";
								if (pChild2Element->Attribute("name")) {
									tname = pChild2Element->Attribute("name");
								}
								// RENDERER_TODO
								//newShaderBinding->addCubemap(tname, (Cubemap*)resourcePool->getResource(Resource::RESOURCE_CUBEMAP, pChild2Element->GetText()));
							}
						}
					}
				}
			}
		}
	}


	for (int i = 0; i< shaderPasses.size(); i++) {
		newMaterial->addShaderPass(shaderPasses[i]);
	}

	return newMaterial;
}

void ResourcePool::loadMaterialsFromFile(const String &fileName) {
	std::vector<Material*> retVector;

	TiXmlDocument doc(fileName.c_str());
	doc.LoadFile();

	if (doc.Error()) {
		Logger::log("XML Error: %s\n", doc.ErrorDesc());
	}
	else {
		TiXmlElement *mElem = doc.RootElement()->FirstChildElement("materials");
		if (mElem) {
			TiXmlNode* pChild;
			for (pChild = mElem->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {
				std::shared_ptr<Material> newMaterial = materialFromXMLNode(pChild);
				if (newMaterial) {
					addResource(newMaterial);
				}
			}
		}
	}
}

void ResourcePool::loadResourcesFromMaterialFile(const String &path) {
	loadShadersFromFile(path);
	loadCubemapsFromFile(path);
	loadMaterialsFromFile(path);
}

void ResourcePool::loadResourcesFromFolderWithLoader(const String &folder, bool recursive, ResourceLoader *loader, const String &containingFolder) {
	vector<OSFileEntry> resourceDir;
	
	resourceDir = Services()->getCore()->parseFolder(folder, false);
	
	for(int i=0; i < resourceDir.size(); i++) {
		if(resourceDir[i].type == OSFileEntry::TYPE_FILE) {
			std::shared_ptr<Resource> newResource;
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

std::shared_ptr<Font> ResourcePool::loadFont(const String &name, const String &path) {
    return std::static_pointer_cast<Font>(loadResourceWithName(path, name));
}

std::shared_ptr<Resource> ResourcePool::loadResource(const String &path) {
	
	std::shared_ptr<Resource> newResource = getResourceByPath(path);
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

std::shared_ptr<Resource> ResourcePool::loadResourceWithName(const String &path, const String &name) {
	std::shared_ptr<Resource> newResource = getResourceByPath(path);
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


std::shared_ptr<Resource> ResourcePool::getResourceByPath(const String& resourcePath) const {
	for(int i =0; i < resources.size(); i++) {
		if(resources[i]->getResourcePath() == resourcePath) {
			return resources[i];
		}
	}
	
	if(fallbackPool) {
		return fallbackPool->getResourceByPath(resourcePath);
	} else {
		return nullptr;
	}
}

std::vector<std::shared_ptr<Resource> > ResourcePool::getResources(int resourceType) {
	std::vector<std::shared_ptr<Resource> > result;
	for(int i =0; i < resources.size(); i++) {
		if(resources[i]->getResourceType() == resourceType) {
			result.push_back(resources[i]);
		}
	}
	return result;
}

std::shared_ptr<Resource> ResourcePool::getResource(int resourceType, const String& resourceName) const {

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
	
	for(int i=0; i < pools.size(); i++) {
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

std::shared_ptr<Resource> MaterialResourceLoader::loadResource(const String &path, ResourcePool *targetPool) {
	targetPool->loadResourcesFromMaterialFile(path);
	return nullptr;
}

ProgramResourceLoader::ProgramResourceLoader() {
	extensions.push_back("frag");
	extensions.push_back("vert");
}

std::shared_ptr<Resource> ProgramResourceLoader::loadResource(const String &path, ResourcePool *targetPool) {
	std::shared_ptr<ShaderProgram> newProgram = std::make_shared<ShaderProgram>(path);
	OSFileEntry fileEntry(path, OSFileEntry::TYPE_FILE);
	if(fileEntry.extension == "vert") {
		newProgram->type = ShaderProgram::TYPE_VERT;
	} else {
		newProgram->type = ShaderProgram::TYPE_FRAG;
	}
	return newProgram;
}

#ifndef NO_LUA
static int customError(lua_State *L) {
	std::vector<DebugBackTraceEntry> backTrace;
	lua_Debug entry;
	int depth = 0;
	while (lua_getstack(L, depth, &entry)) {
		lua_getinfo(L, "Sln", &entry);
		
		std::vector<String> bits = String(entry.short_src).split("\"");
		if(bits.size() > 1) {
			String fileName = bits[1];
			if(fileName != "class.lua") {
				
				DebugBackTraceEntry trace;
				trace.lineNumber = entry.currentline;
				trace.fileName = fileName;
				backTrace.push_back(trace);
			}
		}
		depth++;
	}
	
	// horrible hack to determine the filenames of things
	bool stringThatIsTheMainFileSet = false;
	String stringThatIsTheMainFile;
	
	if(backTrace.size() == 0) {
		DebugBackTraceEntry trace;
		trace.lineNumber = 0;
		trace.fileName = "TODO: Figure out full pathHere";
		backTrace.push_back(trace);
		
	} else {
		stringThatIsTheMainFileSet = true;
		stringThatIsTheMainFile = backTrace[backTrace.size()-1].fileName;
		backTrace[backTrace.size()-1].fileName = "TODO: Figure out full pathHere";
	}
	
	if(stringThatIsTheMainFileSet) {
		for(int i=0; i < backTrace.size(); i++) {
			if(backTrace[i].fileName == stringThatIsTheMainFile) {
				backTrace[i].fileName = "TODO: Figure out full pathHere";
			}
		}
	}
	
	const char *msg = lua_tostring(L, -1);
	if (msg == NULL) msg = "(error with no message)";
	lua_pop(L, 1);
	printf("%s\n", msg);
	
	return 0;
}

int customLuaLoader(lua_State* pState)
{
	std::string module = lua_tostring(pState, 1);
	
	module += ".lua";
	
	std::string defaultPath = "default/";
	defaultPath.append(module);
	
	const char* fullPath = module.c_str();
	Logger::log("Loading custom class: %s\n", module.c_str());
	
	Polycode::CoreFile *inFile = Services()->getCore()->openFile(module, "r");
	
	if(!inFile) {
		inFile =  Services()->getCore()->openFile(defaultPath, "r");
	}
	
	if(inFile) {
		inFile->seek(0, SEEK_END);
		long progsize = inFile->tell();
		inFile->seek(0, SEEK_SET);
		char *buffer = (char*)malloc(progsize+1);
		memset(buffer, 0, progsize+1);
		inFile->read(buffer, progsize, 1);
		int status = luaL_loadbuffer(pState, (const char*)buffer, progsize, fullPath);
		if(status) {
			const char *msg;
			msg = lua_tostring(pState, -1);
			if (msg == NULL) msg = "(error with no message)";
			Logger::log("status=%d, (%s)\n", status, msg);
			lua_pop(pState, 1);
		}
		free(buffer);
		Services()->getCore()->closeFile(inFile);
	} else {
		std::string err = "\n\tError - Could could not find ";
		err += module;
		err += ".";			
		lua_pushstring(pState, err.c_str());			
	}
	return 1;
}

void ScriptResourceLoader::initLua() {
	luaState =	luaL_newstate();
	luaL_openlibs(luaState);
	luaopen_debug(luaState);
	luaopen_Polycode(luaState);
	
	/* install custom loader function */
	
	lua_getglobal(luaState, "package");
	lua_getfield(luaState, -1, "searchers");
	lua_remove(luaState, -2);
	
	int numLoaders = 0;
	lua_pushnil(luaState);
	while (lua_next(luaState, -2) != 0)
	{
		lua_pop(luaState, 1);
		numLoaders++;
	}
	
	lua_pushinteger(luaState, numLoaders + 1);
	lua_pushcfunction(luaState, customLuaLoader);
	lua_rawset(luaState, -3);
	lua_pop(luaState, 1);
	
	/* install custom error function */
	
	lua_register(luaState, "__customError", customError);
	lua_getglobal(luaState, "__customError");
	int errH = lua_gettop(luaState);
	
	/* require default lua files */
	
	lua_getglobal(luaState, "require");
	lua_pushstring(luaState, "class");
	lua_pcall(luaState, 1, 0, errH);

	lua_getglobal(luaState, "require");
	lua_pushstring(luaState, "Polycode");
	lua_pcall(luaState, 1, 0, errH);
	
	lua_getglobal(luaState, "require");
	lua_pushstring(luaState, "tweens");
	lua_pcall(luaState, 1, 0, errH);
	
	lua_getglobal(luaState, "require");
	lua_pushstring(luaState, "defaults");
	lua_pcall(luaState, 1, 0, errH);
}
#endif

void loadJSFile(duk_context *context, String fileName) {

	String defaultPath = "default/";
	defaultPath = defaultPath + fileName;
	
	const char* fullPath = fileName.c_str();
	Logger::log("Loading custom class: %s\n", fileName.c_str());
	Polycode::CoreFile *inFile = Services()->getCore()->openFile(fileName, "r");
	if(!inFile) {
		inFile =  Services()->getCore()->openFile(defaultPath, "r");
	}
	
	if(inFile) {
		inFile->seek(0, SEEK_END);
		long progsize = inFile->tell();
		inFile->seek(0, SEEK_SET);
		char *buffer = (char*)malloc(progsize+1);
		memset(buffer, 0, progsize+1);
		inFile->read(buffer, progsize, 1);
		
		if(duk_peval_string(context, (const char*)buffer) != 0) {
			Logger::log("JAVASCRIPT ERROR: [%s]\n", duk_safe_to_string(context, -1));
		}
		
		free(buffer);
		Services()->getCore()->closeFile(inFile);
	} else {
		Logger::log("Javascript module not found: %s", fileName.c_str());
	}
	
	
}

duk_ret_t customJSLoader(duk_context *context) {
	String module = duk_to_string(context, 0);
	module += ".js";
	loadJSFile(context, module);
	return 0;
}


void ScriptResourceLoader::initJavascript() {
	duktapeContext = duk_create_heap_default();
	
	jsopen_Polycode(duktapeContext);
	
	duk_push_c_function(duktapeContext, customJSLoader, 1);
	duk_put_global_string(duktapeContext, "require");

	loadJSFile(duktapeContext, "Polycode.js");
	loadJSFile(duktapeContext, "defaults.js");
}

ScriptResourceLoader::ScriptResourceLoader() {
#ifndef NO_LUA
	luaState = NULL;
	extensions.push_back("lua");
#endif
	duktapeContext = NULL;
	extensions.push_back("js");
}

ScriptResourceLoader::~ScriptResourceLoader() {
#ifndef NO_LUA
	if(luaState) {
		lua_close(luaState);
	}
#endif
	if(duktapeContext) {
		duk_destroy_heap(duktapeContext);
	}
}

std::shared_ptr<Resource> ScriptResourceLoader::loadResource(const String &path, ResourcePool *targetPool) {
	OSFileEntry entry(path, OSFileEntry::TYPE_FILE);
	std::shared_ptr<Script> newScript;

	if(entry.extension == "lua") {
#ifndef NO_LUA
		if(!luaState) {
			initLua();
		}
		newScript = std::make_shared<LuaScript>(luaState, path);
#endif
	} else if(entry.extension == "js") {
		if(!duktapeContext) {
			initJavascript();
		}
		newScript = std::make_shared<JSScript>(duktapeContext, path);
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

std::shared_ptr<Resource> MeshResourceLoader::loadResource(const String &path, ResourcePool *targetPool) {
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(path);
	return mesh;
}


std::shared_ptr<Resource> FontResourceLoader::loadResource(const String &path, ResourcePool *targetPool) {
	OSFileEntry entry = OSFileEntry(path, OSFileEntry::TYPE_FILE);
	std::shared_ptr<Font> font = std::make_shared<Font>(path, FTLibrary);
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

void ResourceManager::removeResource(std::shared_ptr<Resource> resource) {
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

std::vector<std::shared_ptr<Resource> > ResourceManager::getResources(int resourceType) {
	std::vector<std::shared_ptr<Resource> > result;

	std::vector<std::shared_ptr<Resource> > subresult = globalPool->getResources(resourceType);
	result.insert(result.end(), subresult.begin(), subresult.end());
	
	for(int i =0; i < pools.size(); i++) {
		subresult = pools[i]->getResources(resourceType);
		result.insert(result.end(), subresult.begin(), subresult.end());
	}
	
	return result;
}
