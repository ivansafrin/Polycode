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
    
    shaderTexturesSheet = new ShaderTexturesSheet();
    entityProps->addPropSheet(shaderTexturesSheet);
    shaderTexturesSheet->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);

    shaderOptionsSheet = new ShaderOptionsSheet();
    entityProps->addPropSheet(shaderOptionsSheet);
    shaderOptionsSheet->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);
    
    labelSheet = new SceneLabelSheet();
    entityProps->addPropSheet(labelSheet);
    labelSheet->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);
    
    
    lightSheet = new SceneLightSheet();
    entityProps->addPropSheet(lightSheet);
    lightSheet->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);

    particleSheet = new ParticleEmitterSheet();
    entityProps->addPropSheet(particleSheet);
    particleSheet->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);
    
    
    primitiveSheet = new ScenePrimitiveSheet();
    entityProps->addPropSheet(primitiveSheet);
    primitiveSheet->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);
    
    entitySheet = new EntitySheet();
    entityProps->addPropSheet(entitySheet);
    entitySheet->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);
    
}

void EntityEditorPropertyView::Resize(Number width, Number height) {
    entityProps->Resize(width, height);
    UIElement::Resize(width, height);
}

void EntityEditorPropertyView::handleEvent(Event *event) {
    if(event->getDispatcher() == materialSheet) {
        if(targetEntity) {
            updateShaderOptions();
        }
    }
}

void EntityEditorPropertyView::updateShaderOptions() {
    SceneMesh *sceneMesh = dynamic_cast<SceneMesh*>(targetEntity);
    SceneLabel *sceneLabel = dynamic_cast<SceneLabel*>(targetEntity);
    
    shaderTexturesSheet->enabled = false;
    shaderOptionsSheet->enabled = false;
    
    if(sceneMesh) {
        if(sceneMesh->getMaterial() && sceneMesh->getLocalShaderOptions()) {
            
            // can't edit the textures manually on a scene label
            if(!sceneLabel) {
            shaderTexturesSheet->setShader(sceneMesh->getMaterial()->getShader(0), sceneMesh->getMaterial(), sceneMesh->getLocalShaderOptions());
            }
            
            shaderOptionsSheet->setShader(sceneMesh->getMaterial()->getShader(0), sceneMesh->getMaterial(), sceneMesh->getLocalShaderOptions());
        }
    }
}

void EntityEditorPropertyView::setEntity(Entity *entity) {
    
    targetEntity = entity;
    
    SceneLight *sceneLight = dynamic_cast<SceneLight*>(entity);
    lightSheet->setSceneLight(sceneLight);
    
    SceneMesh *sceneMesh = dynamic_cast<SceneMesh*>(entity);
    materialSheet->setSceneMesh(sceneMesh);
    updateShaderOptions();

    SceneLabel *sceneLabel = dynamic_cast<SceneLabel*>(entity);
    labelSheet->setSceneLabel(sceneLabel);

    ScenePrimitive *scenePrimitive = dynamic_cast<ScenePrimitive*>(entity);
    
    if(!sceneLabel) {
        primitiveSheet->setScenePrimitive(scenePrimitive);
    } else {
        primitiveSheet->setScenePrimitive(NULL);
    }
    

    SceneParticleEmitter *emitter = dynamic_cast<SceneParticleEmitter*>(entity);
    particleSheet->setParticleEmitter(emitter);

    entitySheet->setEntity(entity);
    transformSheet->setEntity(entity);
        
    Resize(getWidth(), getHeight());
}

EntityEditorPropertyView::~EntityEditorPropertyView() {
}
