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

#include "PolyMaterialManager.h"
#include "PolyCoreServices.h"
#include "PolyCubemap.h"
#include "PolyMaterial.h"
#include "PolyRenderer.h"
#include "PolyResourceManager.h"
#include "PolyTexture.h"

#include "tinyxml.h"

using namespace Polycode;
using std::vector;

MaterialManager::MaterialManager() {
	premultiplyAlphaOnLoad = false;
	clampDefault = false;
	mipmapsDefault = true;
    keepTextureData = true;
}

MaterialManager::~MaterialManager() {
	
}

void MaterialManager::Update(int elapsed) {

}

Texture *MaterialManager::getTextureByResourcePath(const String& resourcePath) const {
	for(int i=0;i < textures.size(); i++) {
		if(textures[i]->getResourcePath() == resourcePath)
			return textures[i];
	}
	return NULL;
}

void MaterialManager::deleteTexture(Texture *texture) {
	for(int i=0;i < textures.size(); i++) {
		if(textures[i] == texture) {
			textures.erase(textures.begin()+i);
			CoreServices::getInstance()->getRenderer()->destroyTexture(texture);
			return;
		}
	}
}

void MaterialManager::reloadPrograms() {

	vector<Resource *> shaders = CoreServices::getInstance()->getResourceManager()->getResources(Resource::RESOURCE_SHADER);
	for(int s = 0; s < shaders.size(); s++) {
		Shader *shader = (Shader *)shaders[s];
		shader->reload();
	}
}

void MaterialManager::loadMaterialLibraryIntoPool(ResourcePool *pool, const String &materialFile) {
    printf("LOADING [%s] into pool [%s]\n", materialFile.c_str(), pool->getName().c_str());
    std::vector<Shader*> shaders =loadShadersFromFile(pool, materialFile);

    for(int s=0; s < shaders.size(); s++) {
        pool->addResource(shaders[s]);
        addShader(shaders[s]);
    }
    
    std::vector<Cubemap*> cubemaps = loadCubemapsFromFile(materialFile);
    for(int c=0; c < cubemaps.size(); c++) {
        pool->addResource(cubemaps[c]);
    }
    
    std::vector<Material*> materials = loadMaterialsFromFile(pool, materialFile);
    
    for(int m=0; m < materials.size(); m++) {
        materials[m]->setResourceName(materials[m]->getName());
        pool->addResource(materials[m]);
        addMaterial(materials[m]);
    }
}

ShaderProgram *MaterialManager::createProgramFromFile(String programPath) {
    ShaderProgram *program = Services()->getRenderer()->createProgram(programPath);
    return program;
}

#define DEFAULT_TEXTURE "default/default.png"

Texture *MaterialManager::createTextureFromFile(const String& fileName, bool clamp, bool createMipmaps, ResourcePool *resourcePool) {
	if(fileName.size() == 0) {
		Logger::log("empty texture filename, using default texture.\n");
		return getTextureByResourcePath(DEFAULT_TEXTURE);
	}
    
    if(!resourcePool) {
        resourcePool = CoreServices::getInstance()->getResourceManager()->getGlobalPool();
    }

	Texture *newTexture;
	newTexture = getTextureByResourcePath(fileName);
	if(newTexture) {
		return newTexture;
	}
	
	Image *image = new Image(fileName);
	if(image->isLoaded()) {
		if(premultiplyAlphaOnLoad) {
			image->premultiplyAlpha();
		}
		newTexture = createTexture(image->getWidth(), image->getHeight(), image->getPixels(), clamp, createMipmaps, image->getType());
		newTexture->setResourcePath(fileName);
        resourcePool->addResource(newTexture);
	} else {
		Logger::log("Error loading image (\"%s\"), using default texture.\n", fileName.c_str());		
		newTexture = getTextureByResourcePath(DEFAULT_TEXTURE);
	}
		
	delete image;
	return newTexture;
}

Texture *MaterialManager::createNewTexture(int width, int height, bool clamp, bool createMipmaps, int type) {
	Image *newImage = new Image(width, height, type);
	newImage->fill(Color(1,1,1,1));
	Texture *retTexture = createTextureFromImage(newImage, clamp, createMipmaps);
	delete newImage;
	return retTexture;
	
}

Texture *MaterialManager::createTexture(int width, int height, char *imageData, bool clamp, bool createMipmaps, int type) {
	Texture *newTexture = CoreServices::getInstance()->getRenderer()->createTexture(width, height, imageData,clamp, createMipmaps, type);
	textures.push_back(newTexture);
    if(!keepTextureData) {
        free(newTexture->textureData);
        newTexture->textureData = NULL;
    }
	return newTexture;
}

Texture *MaterialManager::createTextureFromImage(Image *image, bool clamp, bool createMipmaps) {
	Texture *newTexture;
	newTexture = createTexture(image->getWidth(), image->getHeight(), image->getPixels(),clamp, createMipmaps, image->getType());
    if(!keepTextureData) {
        free(newTexture->textureData);
        newTexture->textureData = NULL;
    }
	return newTexture; 
}

void MaterialManager::reloadProgramsAndTextures() {
	reloadTextures();
	reloadPrograms();
}

void MaterialManager::reloadTextures() {
	for(int i=0; i < textures.size(); i++) {
		Texture *texture = textures[i];
        //RENDERER_TODO
//		texture->recreateFromImageData();
	}
}

unsigned int MaterialManager::getNumShaders() {
	return shaders.size();
}

Shader *MaterialManager::getShaderByIndex(unsigned int index) {
	if(index < shaders.size())
		return shaders[index];
	else
		return NULL;
}

Shader *MaterialManager::createShader(ResourcePool *resourcePool, String shaderType, String name, String vpName, String fpName, bool screenShader) {
	Shader *retShader = NULL;
    
    ShaderProgram *vertexProgram = (ShaderProgram*)resourcePool->getResourceByPath(vpName);
    ShaderProgram *fragmentProgram = (ShaderProgram*)resourcePool->getResourceByPath(fpName);
    
    if(vertexProgram != NULL && fragmentProgram != NULL) {
        retShader = Services()->getRenderer()->createShader(vertexProgram, fragmentProgram);
        retShader->setName(name);
        shaders.push_back(retShader);
    }
	
	if(retShader) {
		retShader->screenShader = screenShader;
		retShader->numPointLights = 0;
		retShader->numSpotLights = 0;
        retShader->setResourceName(name);        
	}
    
	return retShader;
}

Shader *MaterialManager::createShaderFromXMLNode(ResourcePool *resourcePool, TiXmlNode *node) {
	TiXmlElement *nodeElement = node->ToElement();
	if (!nodeElement) return NULL; // Skip comment nodes
	
	Shader *retShader = NULL;
    TiXmlNode* pChild;
    ShaderProgram *vp = NULL;
    ShaderProgram *fp = NULL;
    
    for (pChild = node->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {
        TiXmlElement *pChildElement = pChild->ToElement();
        if (!pChildElement) continue; // Skip comment nodes
        
        if(strcmp(pChild->Value(), "vp") == 0) {
            String vpFileName = String(pChildElement->Attribute("source"));
            vp = (ShaderProgram*)resourcePool->getResourceByPath(vpFileName);
            if(!vp) {
                vp = (ShaderProgram*)CoreServices::getInstance()->getMaterialManager()->createProgramFromFile(vpFileName);
                if(vp) {
                    vp->setResourcePath(vpFileName);
                    OSFileEntry entry = OSFileEntry(vpFileName, OSFileEntry::TYPE_FILE);
                    vp->setResourceName(entry.name);
                    resourcePool->addResource(vp);
                }
            }
        }
        if(strcmp(pChild->Value(), "fp") == 0) {
            String fpFileName = String(pChildElement->Attribute("source"));
            fp = (ShaderProgram*)resourcePool->getResourceByPath(fpFileName);
            if(!fp) {
                fp = (ShaderProgram*)CoreServices::getInstance()->getMaterialManager()->createProgramFromFile(fpFileName);
                if(fp) {
                    fp->setResourcePath(fpFileName);
                    OSFileEntry entry = OSFileEntry(fpFileName, OSFileEntry::TYPE_FILE);
                    fp->setResourceName(entry.name);
                    resourcePool->addResource(fp);				
                }
            }			
        }
        
    }
    if(vp != NULL && fp != NULL) {
        retShader = Services()->getRenderer()->createShader(vp, fp);
        retShader->setName(String(nodeElement->Attribute("name")));
        shaders.push_back(retShader);
    }
	
	if (!retShader)
		return NULL;

	int numPointLights = 0;
	int numSpotLights = 0;
		
	if(nodeElement->Attribute("numPointLights")) {
		numPointLights = atoi(nodeElement->Attribute("numPointLights"));
	}
	if(nodeElement->Attribute("numSpotLights")) {
		numSpotLights = atoi(nodeElement->Attribute("numSpotLights"));
	}
	
	retShader->screenShader = false;
	
	if(nodeElement->Attribute("screen")) {
		if(String(nodeElement->Attribute("screen")) == "true") {
			retShader->screenShader = true;
		}
	}
	
	if(retShader) {
		retShader->numPointLights = numPointLights;
		retShader->numSpotLights = numSpotLights;		
	}	
	
	return retShader;
}

Shader *MaterialManager::setShaderFromXMLNode(ResourcePool *resourcePool, TiXmlNode *node) {
	TiXmlElement *nodeElement = node->ToElement();
	if (!nodeElement) return NULL; // Skip comment nodes	
	return (Shader*)resourcePool->getResource(Resource::RESOURCE_SHADER, nodeElement->Attribute("name"));;
}

Cubemap *MaterialManager::cubemapFromXMLNode(TiXmlNode *node) {
	TiXmlElement *nodeElement = node->ToElement();
	if (!nodeElement) return NULL; // Skip comment nodes
	
	Cubemap *newCubemap = NULL;
	
	String name = nodeElement->Attribute("name");
	String xPos = nodeElement->Attribute("xPos");
	String xNeg = nodeElement->Attribute("xNeg");
	String yPos = nodeElement->Attribute("yPos");
	String yNeg = nodeElement->Attribute("yNeg");
	String zPos = nodeElement->Attribute("zPos");				
	String zNeg = nodeElement->Attribute("zNeg");
		
	newCubemap = CoreServices::getInstance()->getRenderer()->createCubemap(
		CoreServices::getInstance()->getMaterialManager()->createTextureFromFile(xPos),
		CoreServices::getInstance()->getMaterialManager()->createTextureFromFile(xNeg),
		CoreServices::getInstance()->getMaterialManager()->createTextureFromFile(yPos),
		CoreServices::getInstance()->getMaterialManager()->createTextureFromFile(yNeg),
		CoreServices::getInstance()->getMaterialManager()->createTextureFromFile(zPos),
		CoreServices::getInstance()->getMaterialManager()->createTextureFromFile(zNeg)
	);
	newCubemap->setResourceName(name);
	return newCubemap;
}

void MaterialManager::addMaterial(Material *material) {
	materials.push_back(material);
}

void MaterialManager::addShader(Shader *shader) {
	shaders.push_back(shader);
}

std::vector<Shader*> MaterialManager::loadShadersFromFile(ResourcePool *resourcePool, String fileName) {
	std::vector<Shader*> retVector;
	
	TiXmlDocument doc(fileName.c_str());
	doc.LoadFile();
	
	if(doc.Error()) {
		Logger::log("XML Error: %s\n", doc.ErrorDesc());
	} else {
		TiXmlElement *mElem = doc.RootElement()->FirstChildElement("shaders");
		if(mElem) {
			TiXmlNode* pChild;					
			for (pChild = mElem->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {	
				Shader *newShader = createShaderFromXMLNode(resourcePool, pChild);
				if(newShader != NULL) {
					Logger::log("Adding shader %s\n", newShader->getName().c_str());
					newShader->setResourceName(newShader->getName());
					retVector.push_back(newShader);
				}
			}
		}
	}
	return retVector;
}

std::vector<Cubemap*> MaterialManager::loadCubemapsFromFile(String fileName) {
	std::vector<Cubemap*> retVector;
	
	TiXmlDocument doc(fileName.c_str());
	doc.LoadFile();
	
	if(doc.Error()) {
		Logger::log("XML Error: %s\n", doc.ErrorDesc());
	} else {
		TiXmlElement *mElem = doc.RootElement()->FirstChildElement("cubemaps");
		if(mElem) {
			TiXmlNode* pChild;					
			for (pChild = mElem->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {
				Cubemap *newCubemap = cubemapFromXMLNode(pChild);
				if (newCubemap) {
					retVector.push_back(newCubemap);
				}
			}
		}
	}
	
	return retVector;
}

std::vector<Material*> MaterialManager::loadMaterialsFromFile(ResourcePool *resourcePool, const String &fileName) {
	std::vector<Material*> retVector;
	
	TiXmlDocument doc(fileName.c_str());
	doc.LoadFile();
	
	if(doc.Error()) {
		Logger::log("XML Error: %s\n", doc.ErrorDesc());
	} else {
		TiXmlElement *mElem = doc.RootElement()->FirstChildElement("materials");
		if(mElem) {
			TiXmlNode* pChild;					
			for (pChild = mElem->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {
				Material *newMat = materialFromXMLNode(resourcePool, pChild);
				if (newMat) {
					retVector.push_back(newMat);
				}
			}
		}
	}
	
	return retVector;
}

Material *MaterialManager::createMaterial(ResourcePool *resourcePool, String materialName, String shaderName) {
	Material *newMaterial = new Material(materialName);
	newMaterial->setResourceName(materialName);
	
	Shader *retShader = (Shader*)resourcePool->getResource(Resource::RESOURCE_SHADER, shaderName);
	
	if(retShader) {
		ShaderBinding *newShaderBinding = new ShaderBinding();
		newMaterial->addShader(retShader, newShaderBinding);
	}
	
	return newMaterial;
}

Material *MaterialManager::materialFromXMLNode(ResourcePool *resourcePool, TiXmlNode *node) {
	TiXmlElement *nodeElement = node->ToElement();
	if (!nodeElement) return NULL; // Skip comment nodes

	String mname = nodeElement->Attribute("name");
	TiXmlNode* pChild, *pChild2,*pChild3;
	Shader *materialShader;
	ShaderBinding *newShaderBinding;
	
	vector<Shader*> materialShaders;
	vector<ShaderBinding*> newShaderBindings;
	vector<ShaderRenderTarget*> renderTargets;

	Material *newMaterial = new Material(mname);
	
	newMaterial->setResourceName(mname);
	
	if(nodeElement->Attribute("screen")) {
		if(String(nodeElement->Attribute("screen")) == "true") {
			newMaterial->screenMaterial = true;
		}
	}
    
	if(nodeElement->Attribute("wireframe")) {
		newMaterial->wireframe = String(nodeElement->Attribute("wireframe")) == "true";
	}
	
	if(nodeElement->Attribute("blendingMode")) {
		newMaterial->blendingMode = atoi(nodeElement->Attribute("blendingMode"));
	}

	for (pChild3 = node->FirstChild(); pChild3 != 0; pChild3 = pChild3->NextSibling()) {
		TiXmlElement *pChild3Element = pChild3->ToElement();
		if (!pChild3Element) continue; // Skip comment nodes

		if(strcmp(pChild3->Value(), "rendertargets") == 0) {
			
			if(pChild3Element->Attribute("type")) {
				if(strcmp(pChild3Element->Attribute("type"), "rgba_fp16") == 0) {
					newMaterial->fp16RenderTargets = true;
				}			
			}
		
			for (pChild = pChild3->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {
				TiXmlElement *pChildElement = pChild->ToElement();
				if (!pChildElement) continue; // Skip comment nodes

				if(strcmp(pChild->Value(), "rendertarget") == 0) {
					ShaderRenderTarget *newTarget = new ShaderRenderTarget;
					newTarget->id = pChildElement->Attribute("id");
                    
                    // RENDERER_TODO
                    /*
					newTarget->width = CoreServices::getInstance()->getRenderer()->getXRes();
					newTarget->height = CoreServices::getInstance()->getRenderer()->getYRes();
                    */
                    
					newTarget->sizeMode = ShaderRenderTarget::SIZE_MODE_PIXELS;					
					if(pChildElement->Attribute("width") && pChildElement->Attribute("height")) {
						newTarget->width = atof(pChildElement->Attribute("width"));
						newTarget->height = atof(pChildElement->Attribute("height"));	
						if(pChildElement->Attribute("sizeMode")) {
							if(strcmp(pChildElement->Attribute("sizeMode"), "normalized") == 0) {
								newTarget->sizeMode = ShaderRenderTarget::SIZE_MODE_NORMALIZED;	
								if(newTarget->width > 1.0f)
									newTarget->width = 1.0f;
								if(newTarget->height > 1.0f)
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
		
		if(strcmp(pChild3->Value(), "shader") == 0) {
			materialShader = setShaderFromXMLNode(resourcePool, pChild3);
			if(materialShader) {
                newShaderBinding = new ShaderBinding();
				materialShaders.push_back(materialShader);
				newShaderBindings.push_back(newShaderBinding);
				for (pChild = pChild3->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {
					TiXmlElement *pChildElement = pChild->ToElement();
					if (!pChildElement) continue; // Skip comment nodes

					if(strcmp(pChild->Value(), "params") == 0) {
						for (pChild2 = pChild->FirstChild(); pChild2 != 0; pChild2 = pChild2->NextSibling()) {
							TiXmlElement *pChild2Element = pChild2->ToElement();
							if (!pChild2Element) continue; // Skip comment nodes

							if(strcmp(pChild2->Value(), "param") == 0){
								String pname =  pChild2Element->Attribute("name");

                                    // RENDERER_TODO
                                /*
								if(!CoreServices::getInstance()->getRenderer()->getDataPointerForName(pname)) {								
                                    String pvalue =  pChild2Element->Attribute("value");
                                    int type = materialShader->getExpectedParamType(pname);
                                    LocalShaderParam *param = newShaderBinding->addParam(type, pname);
                                    if(param) {
                                        param->setParamValueFromString(type, pvalue);
                                    }
								}
                                 */
							}						
						}
					}
					if(strcmp(pChild->Value(), "targettextures") == 0) {
						for (pChild2 = pChild->FirstChild(); pChild2 != 0; pChild2 = pChild2->NextSibling()) {
							TiXmlElement *pChild2Element = pChild2->ToElement();
							if (!pChild2Element) continue; // Skip comment nodes

							if(strcmp(pChild2->Value(), "targettexture") == 0){
							
								RenderTargetBinding* newBinding = new RenderTargetBinding;
								newBinding->id = pChild2Element->Attribute("id");
								
								newBinding->name = "";
								if(pChild2Element->Attribute("name")) {
									newBinding->name = pChild2Element->Attribute("name");
								}
								String mode = pChild2Element->Attribute("mode");
								if(strcmp(mode.c_str(), "in") == 0) {
									newBinding->mode = RenderTargetBinding::MODE_IN;			
								} else if(strcmp(mode.c_str(), "color") == 0) {
									newBinding->mode = RenderTargetBinding::MODE_COLOR;
								} else if(strcmp(mode.c_str(), "depth") == 0) {
									newBinding->mode = RenderTargetBinding::MODE_DEPTH;
								} else {
									newBinding->mode = RenderTargetBinding::MODE_OUT;								
								}
																
								newShaderBinding->addRenderTargetBinding(newBinding);
								
								for(int l=0; l < renderTargets.size(); l++) {
									if(renderTargets[l]->id == newBinding->id) {
										printf("Assigning texture to %s\n", newBinding->id.c_str());
										newBinding->texture = renderTargets[l]->texture;
									}
								}
								
								if(newBinding->mode == RenderTargetBinding::MODE_IN) {
									newShaderBinding->addTexture(newBinding->name, newBinding->texture);
								}
							}						
						}
					}					
					if(strcmp(pChild->Value(), "textures") == 0) {
						for (pChild2 = pChild->FirstChild(); pChild2 != 0; pChild2 = pChild2->NextSibling()) {
							TiXmlElement *pChild2Element = pChild2->ToElement();
							if (!pChild2Element) continue; // Skip comment nodes

							if(strcmp(pChild2->Value(), "texture") == 0){
								String tname = "";
								if(pChild2Element->Attribute("name")) {
									tname =  pChild2Element->Attribute("name");
								}
								Texture *texture = CoreServices::getInstance()->getMaterialManager()->createTextureFromFile(pChild2Element->GetText());
								newShaderBinding->addTexture(tname,texture);
//								newShaderBinding->addTexture(tname, (Texture*)CoreServices::getInstance()->getResourceManager()->getResource(Resource::RESOURCE_TEXTURE, pChild2Element->GetText()));
							}
							
							if(strcmp(pChild2->Value(), "cubemap") == 0){
								String tname = "";
								if(pChild2Element->Attribute("name")) {
									tname =  pChild2Element->Attribute("name");
								}
								newShaderBinding->addCubemap(tname, (Cubemap*)resourcePool->getResource(Resource::RESOURCE_CUBEMAP, pChild2Element->GetText()));
							}
							
						}
					}
				}
			}
		}
	}
	

	for(int i=0; i< materialShaders.size(); i++) {
		newMaterial->addShader(materialShaders[i],newShaderBindings[i]);
	}
	for(int i=0; i< renderTargets.size(); i++) {
		newMaterial->addShaderRenderTarget(renderTargets[i]);
	}
	
	return newMaterial;
}
