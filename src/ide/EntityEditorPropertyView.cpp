/*
 Copyright (C) 2013 by Ivan Safrin
 
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
 
#include "EntityEditorPropertyView.h"


EntityEditorPropertyView::EntityEditorPropertyView() : UIElement() {
    
    targetEntity = NULL;
    
    entityProps = new PropList();
    addChild(entityProps);
    
    transformSheet = new TransformSheet();
    entityProps->addPropSheet(transformSheet);
    transformSheet->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);
    
    materialSheet = new MaterialPropSheet();
    entityProps->addPropSheet(materialSheet);
    materialSheet->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);
    materialSheet->addEventListener(this, Event::CHANGE_EVENT);
    
    shaderTexturesSheet = new ShaderTexturesSheet();
    entityProps->addPropSheet(shaderTexturesSheet);
    shaderTexturesSheet->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);

    shaderOptionsSheet = new ShaderOptionsSheet();
    entityProps->addPropSheet(shaderOptionsSheet);
    shaderOptionsSheet->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);
    
    labelSheet = new SceneLabelSheet();
    entityProps->addPropSheet(labelSheet);
    labelSheet->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);
    
    curveSheet = new SceneCurveSheet();
    entityProps->addPropSheet(curveSheet);
    curveSheet->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);
    
    lightSheet = new SceneLightSheet();
    entityProps->addPropSheet(lightSheet);
    lightSheet->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);

    particleSheet = new ParticleEmitterSheet();
    entityProps->addPropSheet(particleSheet);
    particleSheet->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);

    spriteSheet = new SceneSpriteSheet();
    entityProps->addPropSheet(spriteSheet);
    spriteSheet->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);

    primitiveSheet = new ScenePrimitiveSheet();
    entityProps->addPropSheet(primitiveSheet);
    primitiveSheet->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);

    sceneMeshSheet = new SceneMeshSheet();
    entityProps->addPropSheet(sceneMeshSheet);
    sceneMeshSheet->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);
    
    soundSheet = new SoundSheet();
    entityProps->addPropSheet(soundSheet);
    soundSheet->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);

    cameraSheet = new CameraSheet();
    entityProps->addPropSheet(cameraSheet);
    cameraSheet->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);
    
    entitySheet = new EntitySheet();
    entityProps->addPropSheet(entitySheet);
    entitySheet->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);
    
    propSheet = new EntityPropSheet();
    entityProps->addPropSheet(propSheet);
    propSheet->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);
    
}

PropList *EntityEditorPropertyView::getEntityProps() {
    return entityProps;
}

void EntityEditorPropertyView::setEntityInstance(SceneEntityInstance *instance) {
    materialSheet->setEntityInstance(instance);
    entitySheet->setEntityInstance(instance);
    spriteSheet->setEntityInstance(instance);
}

void EntityEditorPropertyView::Resize(Number width, Number height) {
    entityProps->Resize(width, height);
    UIElement::Resize(width, height);
}

void EntityEditorPropertyView::handleEvent(Event *event) {
    if(event->getEventCode() == PropEvent::EVENT_PROP_CHANGE) {
        
        PropEvent *propEvent = (PropEvent*) event;
        
        PropEvent *newPropEvent = new PropEvent(propEvent->prop, propEvent->sheet, propEvent->beforeData, propEvent->afterData);
        dispatchEvent(newPropEvent, PropEvent::EVENT_PROP_CHANGE);
    } else {
        if(event->getDispatcher() == materialSheet) {
            if(targetEntity) {
                updateShaderOptions();
            }
        }
    }
}

void EntityEditorPropertyView::updateShaderOptions() {
    SceneMesh *sceneMesh = dynamic_cast<SceneMesh*>(targetEntity);
    SceneLabel *sceneLabel = dynamic_cast<SceneLabel*>(targetEntity);
    SceneSprite *sceneSprite = dynamic_cast<SceneSprite*>(targetEntity);
    
    shaderTexturesSheet->enabled = false;
    shaderOptionsSheet->enabled = false;
    
    if(sceneMesh) {
        if(sceneMesh->getMaterial() && sceneMesh->getLocalShaderOptions()) {
            
            // can't edit the textures manually on a scene label or sprite
            if(!sceneLabel && !sceneSprite) {
            shaderTexturesSheet->setShader(sceneMesh->getMaterial()->getShader(0), sceneMesh->getMaterial(), sceneMesh->getLocalShaderOptions());
                shaderTexturesSheet->enabled = true;
            }
            
            shaderOptionsSheet->setShader(sceneMesh->getMaterial()->getShader(0), sceneMesh->getMaterial(), sceneMesh->getLocalShaderOptions());
        }
    }
}

void EntityEditorPropertyView::setEntity(Entity *entity, bool rootEntityMode) {
    
    targetEntity = entity;
    
    SceneLight *sceneLight = dynamic_cast<SceneLight*>(entity);
    lightSheet->setSceneLight(sceneLight);
    
    SceneMesh *sceneMesh = dynamic_cast<SceneMesh*>(entity);
    materialSheet->setSceneMesh(sceneMesh);
    updateShaderOptions();

    SceneLabel *sceneLabel = dynamic_cast<SceneLabel*>(entity);
    labelSheet->setSceneLabel(sceneLabel);

    SceneCurve *sceneCurve = dynamic_cast<SceneCurve*>(entity);
    curveSheet->setCurve(sceneCurve);
    
    SceneSprite *sceneSprite = dynamic_cast<SceneSprite*>(entity);
    spriteSheet->setSprite(sceneSprite);

    ScenePrimitive *scenePrimitive = dynamic_cast<ScenePrimitive*>(entity);
    
    if(!sceneLabel && !sceneSprite) {
        primitiveSheet->setScenePrimitive(scenePrimitive);
    } else {
        primitiveSheet->setScenePrimitive(NULL);
    }
    
    sceneMeshSheet->setSceneMesh(sceneMesh);
    
    SceneSound *sound = dynamic_cast<SceneSound*>(entity);
    soundSheet->setSound(sound);

    Camera *camera = dynamic_cast<Camera*>(entity);
    cameraSheet->setCamera(camera);

    SceneParticleEmitter *emitter = dynamic_cast<SceneParticleEmitter*>(entity);
    particleSheet->setParticleEmitter(emitter);

    entitySheet->setEntity(entity);
    propSheet->setEntity(entity);
    
    if(!rootEntityMode) {
        transformSheet->setEntity(entity);
    } else {
        transformSheet->setEntity(NULL);
    }
    
    Resize(getWidth(), getHeight());
}

EntityEditorPropertyView::~EntityEditorPropertyView() {
    entityProps->setOwnsChildrenRecursive(true);
    delete entityProps;
}
