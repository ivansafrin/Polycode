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

using namespace Polycode;

MaterialManager::MaterialManager() {
	
}

MaterialManager::~MaterialManager() {
	
}

void MaterialManager::Update(int elapsed) {
	for(int i=0;i < textures.size(); i++) {
		textures[i]->updateScroll(elapsed);
	}
}

Texture *MaterialManager::getTextureByResourcePath(String resourcePath) {
	for(int i=0;i < textures.size(); i++) {
		if(textures[i]->getResourcePath() == resourcePath)
			return textures[i];
	}
	return NULL;
}

//SceneRenderTexture *MaterialManager::createRenderTexture(Scene *targetScene, Camera *targetCamera, int renderWidth,int renderHeight) {
//	Texture *baseTexture = createTexture(renderWidth, renderHeight, NULL);
//	textures.push_back(baseTexture);
//	SceneRenderTexture *renderTexture = new SceneRenderTexture(baseTexture, targetScene, targetCamera, renderWidth, renderHeight);
//	return renderTexture;
//}

void MaterialManager::deleteTexture(Texture *texture) {
	for(int i=0;i < textures.size(); i++) {
		if(textures[i] == texture) {
			textures.erase(textures.begin()+i);
			delete texture;
			return;
		}
	}
}

void MaterialManager::reloadPrograms() {
	for(int m=0; m < shaderModules.size(); m++) {
		PolycodeShaderModule *shaderModule = shaderModules[m];
		shaderModule->reloadPrograms();
	}
}

void MaterialManager::addShaderModule(PolycodeShaderModule *module) {
	shaderModules.push_back(module);
}

Texture *MaterialManager::createTextureFromFile(String fileName, bool clamp) {
	Texture *newTexture;
	newTexture = getTextureByResourcePath(fileName);
	if(newTexture) {
		return newTexture;
	}
	
	Image *image = new Image(fileName);
	if(image->isLoaded()) {
		newTexture = createTexture(image->getWidth(), image->getHeight(), image->getPixels(), clamp);
	} else {
		char *data = (char*)malloc(4);
		newTexture = createTexture(1, 1, data, true);
		free(data);
	}
		
	delete image;

	vector<String> bits = fileName.split("/");
	
	newTexture->setResourcePath(bits[bits.size()-1]);
	return newTexture;
}

Texture *MaterialManager::createFramebufferTexture(int width, int height, int type) {
	Texture *newTexture = CoreServices::getInstance()->getRenderer()->createFramebufferTexture(width, height);
	return newTexture;
}

Texture *MaterialManager::createNewTexture(int width, int height, bool clamp, int type) {
	Image *newImage = new Image(width, height, type);
	newImage->fill(1,1,1,1);
	Texture *retTexture = createTextureFromImage(newImage, clamp);
	delete newImage;
	return retTexture;
	
}

Texture *MaterialManager::createTexture(int width, int height, char *imageData, bool clamp, int type) {
	Texture *newTexture = CoreServices::getInstance()->getRenderer()->createTexture(width, height, imageData,clamp, type);
	textures.push_back(newTexture);
	return newTexture;
}

Texture *MaterialManager::createTextureFromImage(Image *image, bool clamp) {
	Texture *newTexture;
	newTexture = createTexture(image->getWidth(), image->getHeight(), image->getPixels(),clamp, image->getType());
	return newTexture; 
}

void MaterialManager::reloadProgramsAndTextures() {
	reloadTextures();
	reloadPrograms();
}

void MaterialManager::reloadTextures() {
	for(int i=0; i < textures.size(); i++) {
		Texture *texture = textures[i];
		texture->recreateFromImageData();
	}
}

void MaterialManager::loadMaterialsFromFile(String fileName) {
	
}

Shader *MaterialManager::createShaderFromXMLNode(TiXmlNode *node) {
	Shader *retShader = NULL;
	
	
	if(node->ToElement()->Attribute("type")) {
		String shaderType = node->ToElement()->Attribute("type");
//		Logger::log("Attempting to create %s shader\n", shaderType.c_str());
		
		for(int m=0; m < shaderModules.size(); m++) {
			PolycodeShaderModule *shaderModule = shaderModules[m];
			if(shaderModule->getShaderType() == shaderType) {
				retShader = shaderModule->createShader(node);
			}
		}		
	}
	
	return retShader;
}

Shader *MaterialManager::setShaderFromXMLNode(TiXmlNode *node) {
	Shader *retShader = NULL;
	if(node->ToElement()->Attribute("type")) {
		String shaderType = node->ToElement()->Attribute("type");
		if(shaderType == "fixed") {
			FixedShader *fShader =  new FixedShader();		
			retShader = fShader;
		}
	} else {
		retShader = (Shader*)CoreServices::getInstance()->getResourceManager()->getResource(Resource::RESOURCE_SHADER, node->ToElement()->Attribute("name"));
	}
	return retShader;
}


//			for (pChild = node->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {
//				if(strcmp(pChild->Value(), "textures") == 0) {
//					for (pChild2 = pChild->FirstChild(); pChild2 != 0; pChild2 = pChild2->NextSibling()) {
//						if(strcmp(pChild2->Value(), "texture") == 0)
//							fShader->setDiffuseTexture((Texture*)CoreServices::getInstance()->getResourceManager()->getResource(Resource::RESOURCE_TEXTURE, pChild2->ToElement()->GetText()));
//					}
//				}
//			}


Cubemap *MaterialManager::cubemapFromXMLNode(TiXmlNode *node) {
	Cubemap *newCubemap;
	
	String name = node->ToElement()->Attribute("name");
	String mapString = node->ToElement()->GetText();
	
	vector<String> maps = mapString.split(",");	
	if(maps.size() != 6) {
		Logger::log("Error: A cubemap must contain 6 images \n");
		return NULL;
	}
	
	newCubemap = CoreServices::getInstance()->getRenderer()->createCubemap(
							 (Texture*)CoreServices::getInstance()->getResourceManager()->getResource(Resource::RESOURCE_TEXTURE, maps[0]),
							 (Texture*)CoreServices::getInstance()->getResourceManager()->getResource(Resource::RESOURCE_TEXTURE, maps[1]),
							 (Texture*)CoreServices::getInstance()->getResourceManager()->getResource(Resource::RESOURCE_TEXTURE, maps[2]),
							 (Texture*)CoreServices::getInstance()->getResourceManager()->getResource(Resource::RESOURCE_TEXTURE, maps[3]),
							 (Texture*)CoreServices::getInstance()->getResourceManager()->getResource(Resource::RESOURCE_TEXTURE, maps[4]),
							 (Texture*)CoreServices::getInstance()->getResourceManager()->getResource(Resource::RESOURCE_TEXTURE, maps[5])
	);
	newCubemap->setResourceName(name);
	return newCubemap;
}

Material *MaterialManager::materialFromXMLNode(TiXmlNode *node) {
	String mname = node->ToElement()->Attribute("name");
	TiXmlNode* pChild, *pChild2,*pChild3;
	Shader *materialShader;
	ShaderBinding *newShaderBinding;
	
	vector<Shader*> materialShaders;
	vector<ShaderBinding*> newShaderBindings;
	vector<ShaderRenderTarget*> renderTargets;	

	for (pChild3 = node->FirstChild(); pChild3 != 0; pChild3 = pChild3->NextSibling()) {
		if(strcmp(pChild3->Value(), "rendertargets") == 0) {
			for (pChild = pChild3->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {
				if(strcmp(pChild->Value(), "rendertarget") == 0) {
					ShaderRenderTarget *newTarget = new ShaderRenderTarget;
					newTarget->id = pChild->ToElement()->Attribute("id");
					newTarget->width = CoreServices::getInstance()->getRenderer()->getXRes();
					newTarget->height = CoreServices::getInstance()->getRenderer()->getYRes();
					newTarget->sizeMode = ShaderRenderTarget::SIZE_MODE_PIXELS;					
					if(pChild->ToElement()->Attribute("width") && pChild->ToElement()->Attribute("height")) {
						newTarget->width = atof(pChild->ToElement()->Attribute("width"));
						newTarget->height = atof(pChild->ToElement()->Attribute("height"));
						if(pChild->ToElement()->Attribute("sizeMode")) {
							if(strcmp(pChild->ToElement()->Attribute("sizeMode"), "normalized") == 0) {
								if(newTarget->width > 1.0f)
									newTarget->width = 1.0f;
								if(newTarget->height > 1.0f)
									newTarget->height = 1.0f;
									
								newTarget->width = ((Number)CoreServices::getInstance()->getRenderer()->getXRes()) * newTarget->width;
								newTarget->height = ((Number)CoreServices::getInstance()->getRenderer()->getYRes()) * newTarget->height;
							}						
						}
					}						
//					Texture *newTexture = CoreServices::getInstance()->getMaterialManager()->createNewTexture(newTarget->width, newTarget->height, true);
					Texture *newTexture, *temp;
					CoreServices::getInstance()->getRenderer()->createRenderTextures(&newTexture, &temp, (int)newTarget->width, (int)newTarget->height);
					newTexture->setResourceName(newTarget->id);
					//CoreServices::getInstance()->getResourceManager()->addResource(newTexture);
					newTarget->texture = newTexture;
					renderTargets.push_back(newTarget);

				}
			}
		}	
	}
	
	for (pChild3 = node->FirstChild(); pChild3 != 0; pChild3 = pChild3->NextSibling()) {
		if(strcmp(pChild3->Value(), "shader") == 0) {
			materialShader = setShaderFromXMLNode(pChild3);
			if(materialShader) {
				newShaderBinding = materialShader->createBinding();
				materialShaders.push_back(materialShader);
				newShaderBindings.push_back(newShaderBinding);
				for (pChild = pChild3->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {
					if(strcmp(pChild->Value(), "params") == 0) {
						for (pChild2 = pChild->FirstChild(); pChild2 != 0; pChild2 = pChild2->NextSibling()) {
							if(strcmp(pChild2->Value(), "param") == 0){
								String pname =  pChild2->ToElement()->Attribute("name");
								String ptype =  pChild2->ToElement()->Attribute("type");
								String pvalue =  pChild2->ToElement()->Attribute("value");
								newShaderBinding->addParam(ptype, pname, pvalue);
							}						
						}
					}
					if(strcmp(pChild->Value(), "targettextures") == 0) {
						for (pChild2 = pChild->FirstChild(); pChild2 != 0; pChild2 = pChild2->NextSibling()) {
							if(strcmp(pChild2->Value(), "targettexture") == 0){
							
								RenderTargetBinding* newBinding = new RenderTargetBinding;
								newBinding->id = pChild2->ToElement()->Attribute("id");
								
								newBinding->name = "";
								if(pChild2->ToElement()->Attribute("name")) {
									newBinding->name = pChild2->ToElement()->Attribute("name");
								}
								String mode = pChild2->ToElement()->Attribute("mode");
								if(strcmp(mode.c_str(), "in") == 0) {
									newBinding->mode = RenderTargetBinding::MODE_IN;
								} else {
									newBinding->mode = RenderTargetBinding::MODE_OUT;								
								}
																
								newShaderBinding->addRenderTargetBinding(newBinding);
								//Texture *texture =  (Texture*)CoreServices::getInstance()->getResourceManager()->getResource(Resource::RESOURCE_TEXTURE, newBinding->id);
//								newBinding->texture = texture;
								
								for(int l=0; l < renderTargets.size(); l++) {
									if(renderTargets[l]->id == newBinding->id) {
										newBinding->texture = renderTargets[l]->texture;
										newBinding->width = renderTargets[l]->width;
										newBinding->height = renderTargets[l]->height;
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
							if(strcmp(pChild2->Value(), "texture") == 0){
								String tname = "";
								if(pChild2->ToElement()->Attribute("name")) {
									tname =  pChild2->ToElement()->Attribute("name");
								}
								newShaderBinding->addTexture(tname, (Texture*)CoreServices::getInstance()->getResourceManager()->getResource(Resource::RESOURCE_TEXTURE, pChild2->ToElement()->GetText()));
							}
							
							if(strcmp(pChild2->Value(), "cubemap") == 0){
								String tname = "";
								if(pChild2->ToElement()->Attribute("name")) {
									tname =  pChild2->ToElement()->Attribute("name");
								}
								newShaderBinding->addCubemap(tname, (Cubemap*)CoreServices::getInstance()->getResourceManager()->getResource(Resource::RESOURCE_CUBEMAP, pChild2->ToElement()->GetText()));
							}
							
						}
					}
				}
			}
		}
	}
	
	Material *newMaterial = new Material(mname);
	for(int i=0; i< materialShaders.size(); i++) {
		newMaterial->addShader(materialShaders[i],newShaderBindings[i]);
	}
	for(int i=0; i< renderTargets.size(); i++) {
		newMaterial->addShaderRenderTarget(renderTargets[i]);
	}
	
	return newMaterial;
}