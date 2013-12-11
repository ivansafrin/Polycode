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

#include "PolySceneEntityInstance.h"
#include "PolyLogger.h"
#include "PolyCoreServices.h"
#include "PolyResourceManager.h"
#include "PolyMaterial.h"
#include "PolySceneLight.h"
#include "PolySceneMesh.h"

using namespace Polycode;

SceneEntityInstanceResourceEntry::SceneEntityInstanceResourceEntry(SceneEntityInstance *instance)  : Resource(Resource::RESOURCE_SCREEN_ENTITY_INSTANCE) {
	this->instance = instance;
}

SceneEntityInstanceResourceEntry::~SceneEntityInstanceResourceEntry() {

}

SceneEntityInstance *SceneEntityInstanceResourceEntry::getInstance() {
	return instance;
}

void SceneEntityInstanceResourceEntry::reloadResource() {
	instance->reloadEntityInstance();
	Resource::reloadResource();
}

SceneEntityInstance *SceneEntityInstance::BlankSceneEntityInstance() {
	return new SceneEntityInstance();
}

SceneEntityInstance::SceneEntityInstance(Scene *parentScene, const String& fileName) : Entity() {
    this->parentScene = parentScene;
	resourceEntry = new SceneEntityInstanceResourceEntry(this);		
	loadFromFile(fileName);
	resourceEntry->setResourceName(fileName);
	resourceEntry->setResourcePath(fileName);
	cloneUsingReload = false;
	ownsChildren = true;	
}

SceneEntityInstance::SceneEntityInstance() : Entity() {
	cloneUsingReload = true;
	ownsChildren = true;
	resourceEntry = new SceneEntityInstanceResourceEntry(this);
}

SceneEntityInstance::~SceneEntityInstance() {	
	CoreServices::getInstance()->getResourceManager()->removeResource(resourceEntry);
	delete resourceEntry;
}

void SceneEntityInstance::reloadEntityInstance() {
	loadFromFile(fileName);
}

SceneEntityInstanceResourceEntry *SceneEntityInstance::getResourceEntry() {
	return resourceEntry;
}

Entity *SceneEntityInstance::Clone(bool deepClone, bool ignoreEditorOnly) const {
	SceneEntityInstance *newEntity;
	if(cloneUsingReload) {
		newEntity = new SceneEntityInstance(parentScene, fileName);
	} else {
		newEntity = new SceneEntityInstance();
	}
	applyClone(newEntity, deepClone, ignoreEditorOnly);
	return newEntity;
}

void SceneEntityInstance::applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly) const {
	if(cloneUsingReload) {
		Entity::applyClone(clone, false, ignoreEditorOnly);
	} else {
		Entity::applyClone(clone, deepClone, ignoreEditorOnly);
		SceneEntityInstance *_clone = (SceneEntityInstance*) clone;
		_clone->fileName = fileName;
	}
}

void SceneEntityInstance::applySceneMesh(ObjectEntry *entry, SceneMesh *sceneMesh) {
	if(!entry) {
		return;
    }
    
    ObjectEntry *materialName =(*entry)["material"];
    if(materialName) {
        sceneMesh->setMaterialByName(materialName->stringVal);
        if(sceneMesh->getMaterial()) {
            ObjectEntry *optionsEntry =(*entry)["shader_options"];
            if(optionsEntry) {
                for(int i=0; i < optionsEntry->length; i++) {
                    ObjectEntry *shaderEntry =(*optionsEntry)[i];
                    if(shaderEntry) {
                        
                        // parse in texture bindings
                        ObjectEntry *texturesEntry =(*shaderEntry)["textures"];
                        if(texturesEntry) {
                            for(int j=0; j < texturesEntry->length; j++) {
                                ObjectEntry *textureEntry =(*texturesEntry)[j];
                                if(textureEntry) {
                                    ObjectEntry *nameEntry = (*textureEntry)["name"];
                                    if(nameEntry) {
                                        
                                        if(textureEntry->name == "cubemap") {
                                            Cubemap *cubemap = (Cubemap*)CoreServices::getInstance()->getResourceManager()->getResource(Resource::RESOURCE_CUBEMAP, textureEntry->stringVal);
                                            if(cubemap) {
                                                sceneMesh->getLocalShaderOptions()->addCubemap(nameEntry->stringVal, cubemap);
                                            }
                                        } else {
                                            sceneMesh->getLocalShaderOptions()->addTexture(nameEntry->stringVal, CoreServices::getInstance()->getMaterialManager()->createTextureFromFile(textureEntry->stringVal));
                                        }
                                    }
                                }
                            }
                        }
                        
                        ObjectEntry *paramsEntry =(*shaderEntry)["params"];
                        if(paramsEntry) {
                            for(int j=0; j < paramsEntry->length; j++) {
                                ObjectEntry *paramEntry =(*paramsEntry)[j];
                                if(paramEntry) {
                                    ObjectEntry *nameEntry = (*paramEntry)["name"];
                                    ObjectEntry *valueEntry = (*paramEntry)["value"];
                                    if(nameEntry && valueEntry) {
                                        Shader *materialShader = sceneMesh->getMaterial()->getShader(i);
                                        if(materialShader) {
                                            int type = materialShader->getExpectedParamType(nameEntry->stringVal);
                                            LocalShaderParam *param = sceneMesh->getLocalShaderOptions()->addParam(type, nameEntry->stringVal);
                                            if(param) {
                                                param->setParamValueFromString(type, valueEntry->stringVal);
                                            }
                                        }
                                    }
                                    
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
}

void SceneEntityInstance::parseObjectIntoCurve(ObjectEntry *entry, BezierCurve *curve) {
	curve->clearControlPoints();
	ObjectEntry *controlPoints =(*entry)["controlPoints"];
	if(controlPoints) {
		for(int i=0; i < controlPoints->length; i++) {		
			ObjectEntry *controlPoint = ((*controlPoints))[i];		
			if(controlPoint) {
				Vector2 vpt1;
				Vector2 vpt2;
				Vector2 vpt3;
												
				ObjectEntry *pt1 = ((*controlPoint))["pt1"];
				if(pt1) {
					vpt1.x = ((*pt1))["x"]->NumberVal;
					vpt1.y = ((*pt1))["y"]->NumberVal;					
				}

				ObjectEntry *pt2 = ((*controlPoint))["pt2"];
				if(pt2) {
					vpt2.x = ((*pt2))["x"]->NumberVal;
					vpt2.y = ((*pt2))["y"]->NumberVal;					
				}

				ObjectEntry *pt3 = ((*controlPoint))["pt3"];
				if(pt3) {
					vpt3.x = ((*pt3))["x"]->NumberVal;
					vpt3.y = ((*pt3))["y"]->NumberVal;					
				}

				curve->addControlPoint(vpt1.x, vpt1.y, 0.0, vpt2.x, vpt2.y, 0.0, vpt3.x, vpt3.y, 0.0);
			}
		}
	}
	
}

Entity *SceneEntityInstance::loadObjectEntryIntoEntity(ObjectEntry *entry, Entity *targetEntity) {

	Entity *entity = NULL;

	ObjectEntry *entityType = (*entry)["type"];
	if(entityType) {
			
        
        /*
         
         if(entityType->stringVal == "SceneEntityInstance") {
         ObjectEntry *screenInstanceEntry = (*entry)["SceneEntityInstance"];
         String filePath = (*screenInstanceEntry)["filePath"]->stringVal;
         SceneEntityInstance *instance = new SceneEntityInstance(filePath);
         entity = instance;
         }
         
         */

		if(entityType->stringVal == "SceneSprite") {
			ObjectEntry *spriteEntry = (*entry)["SceneSprite"];
			String filePath = (*spriteEntry)["filePath"]->stringVal;
			
			SceneSprite *sprite = new SceneSprite(filePath);
			
			String animName = (*spriteEntry)["anim"]->stringVal;
			sprite->playAnimation(animName, -1, false);
			entity = sprite;
            applySceneMesh((*entry)["SceneMesh"], sprite);
		} else if(entityType->stringVal == "SceneLight") {
            
			ObjectEntry *lightEntry = (*entry)["SceneLight"];
            if(lightEntry) {
                int lightType = (*lightEntry)["type"]->intVal;
                SceneLight *newLight  = new SceneLight(lightType, parentScene, 0);
                
                newLight->setIntensity((*lightEntry)["intensity"]->NumberVal);
                
                newLight->lightColor.setColor((*lightEntry)["cR"]->NumberVal, (*lightEntry)["cG"]->NumberVal, (*lightEntry)["cB"]->NumberVal, (*lightEntry)["cA"]->NumberVal);
                newLight->specularLightColor.setColor((*lightEntry)["scR"]->NumberVal, (*lightEntry)["scG"]->NumberVal, (*lightEntry)["scB"]->NumberVal, (*lightEntry)["scA"]->NumberVal);

                newLight->setAttenuation((*lightEntry)["cAtt"]->NumberVal, (*lightEntry)["lAtt"]->NumberVal, (*lightEntry)["qAtt"]->NumberVal);
                
                if(newLight->getType() == SceneLight::SPOT_LIGHT) {
                    newLight->setSpotlightProperties((*lightEntry)["spotCutoff"]->NumberVal, (*lightEntry)["spotExponent"]->NumberVal);
                    
                    if((*lightEntry)["shadows"]->boolVal) {
                        newLight->enableShadows(true, (*lightEntry)["shadowmapRes"]->intVal);
                        newLight->setShadowMapFOV((*lightEntry)["shadowmapFOV"]->NumberVal);
                    }
                }
                
                parentScene->addLight(newLight);
                entity = newLight;
            }
 
        } else if(entityType->stringVal == "ScenePrimitive") {
			ObjectEntry *scenePrimitiveEntry = (*entry)["ScenePrimitive"];
			int pType = (*scenePrimitiveEntry)["type"]->intVal;
			Number p1 = (*scenePrimitiveEntry)["p1"]->NumberVal;
			Number p2 = (*scenePrimitiveEntry)["p2"]->NumberVal;
			Number p3 = (*scenePrimitiveEntry)["p3"]->NumberVal;
			Number p4 = (*scenePrimitiveEntry)["p4"]->NumberVal;
			Number p5 = (*scenePrimitiveEntry)["p5"]->NumberVal;
            
			ScenePrimitive *primitive = new ScenePrimitive(pType, p1, p2, p3, p4, p5);
			entity = primitive;
            applySceneMesh((*entry)["SceneMesh"], primitive);
		} else if(entityType->stringVal == "SceneMesh") {
			ObjectEntry *meshEntry = (*entry)["SceneMesh"];
            if(meshEntry) {
                ObjectEntry *fileName = (*meshEntry)["file"];
                if(fileName) {
                    SceneMesh *newMesh = new SceneMesh(fileName->stringVal);
                    applySceneMesh(meshEntry, newMesh);
                    entity = newMesh;
                }
            }
        }
/*
		if(entityType->stringVal == "ScreenSound") {
			ObjectEntry *screenSoundEntry = (*entry)["ScreenSound"];
			
			String filePath = (*screenSoundEntry)["filePath"]->stringVal;
			Number refDistance = (*screenSoundEntry)["refDistance"]->NumberVal;
			Number maxDistance = (*screenSoundEntry)["maxDistance"]->NumberVal;
			Number volume = (*screenSoundEntry)["volume"]->NumberVal;
			Number pitch = (*screenSoundEntry)["pitch"]->NumberVal;
															
			ScreenSound *sound = new ScreenSound(filePath, refDistance, maxDistance);
			sound->getSound()->setVolume(volume);
			sound->getSound()->setPitch(pitch);	
			
			sound->setWidth(50);
			sound->setHeight(50);				
										
			entity = sound;
		}		


		if(entityType->stringVal == "ScreenLabel") {
			ObjectEntry *screenLabelEntry = (*entry)["ScreenLabel"];
			
			String text = (*screenLabelEntry)["text"]->stringVal;
			String font = (*screenLabelEntry)["font"]->stringVal;
			int size = (*screenLabelEntry)["size"]->intVal;
			int aaMode = (*screenLabelEntry)["aaMode"]->intVal;
												
			ScreenLabel *label = new ScreenLabel(text, size, font, aaMode);
			label->positionAtBaseline = false;
			
			ObjectEntry *screenShapeEntry = (*entry)["ScreenShape"];			
			applyScreenShape(screenShapeEntry, label);
			entity = label;
		}
			*/
	} 

	if(!entity) {
		if(targetEntity) {
			entity = targetEntity;
		} else {
			entity = new Entity();
		}
	}
	
	entity->ownsChildren = true;

	entry->readNumber("bbX", &entity->bBox.x);
	entry->readNumber("bbY", &entity->bBox.y);
	entry->readNumber("bbZ", &entity->bBox.z);

	entity->color.r = (*entry)["cR"]->NumberVal;
	entity->color.g = (*entry)["cG"]->NumberVal;
	entity->color.b = (*entry)["cB"]->NumberVal;
	entity->color.a = (*entry)["cA"]->NumberVal;


	if(!targetEntity) {	
		entity->blendingMode = (*entry)["blendMode"]->intVal;

        entity->setScale((*entry)["sX"]->NumberVal, (*entry)["sY"]->NumberVal, (*entry)["sZ"]->NumberVal);
        entity->setPosition((*entry)["pX"]->NumberVal, (*entry)["pY"]->NumberVal, (*entry)["pZ"]->NumberVal);
        entity->setRotationEuler(Vector3((*entry)["rX"]->NumberVal, (*entry)["rY"]->NumberVal, (*entry)["rZ"]->NumberVal));
	}
	
	if((*entry)["id"]->stringVal != "") {
		entity->id = (*entry)["id"]->stringVal;
	}
	
	String tagString = (*entry)["tags"]->stringVal; 
	
	if(tagString != "") {
		std::vector<String> tags = tagString.split(",");
		for(int i=0; i < tags.size(); i++) {
			entity->addTag(tags[i]);
		}
	}
	
	ObjectEntry *props = (*entry)["props"];
	if(props) {
		for(int i=0; i < props->length; i++) {		
			ObjectEntry *prop = ((*props))[i];		
			if(prop) {
				entity->setEntityProp((*prop)["name"]->stringVal, (*prop)["value"]->stringVal);
			}
		}
	}
														
	ObjectEntry *children = (*entry)["children"];
	
	if(children) {
		for(int i=0; i < children->length; i++) {
			ObjectEntry *childEntry = ((*children))[i];
			ScreenEntity *childEntity = loadObjectEntryIntoEntity(childEntry);
			entity->addChild(childEntity);				
		}
	}

	return entity;
}

String SceneEntityInstance::getFileName() const {
	return fileName;
}

void SceneEntityInstance::clearInstance() {
	for(int i=0; i < children.size(); i++) {
		removeChild(children[i]);
		children[i]->setOwnsChildrenRecursive(true);
		delete children[i];
	}
}

bool SceneEntityInstance::loadFromFile(const String& fileName) {

	clearInstance();
	
	resourceEntry->resourceFileTime = OSBasics::getFileTime(fileName);

	this->ownsChildren = true;
	this->fileName = fileName;
	Object loadObject;
	if(!loadObject.loadFromBinary(fileName)) {
        if(!loadObject.loadFromXML(fileName)) {
            Logger::log("Error loading entity instance.\n");
        }
	}	
	ObjectEntry *root = loadObject.root["root"];
	
	if(root) {
		loadObjectEntryIntoEntity(root, this);
	}
	
	return true;
}