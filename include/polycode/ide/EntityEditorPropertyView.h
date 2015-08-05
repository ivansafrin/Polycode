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

#pragma once

#include "Polycode.h"
#include "PolycodeUI.h"
#include "PolycodeProps.h"

#include "OSBasics.h"

using namespace Polycode;


class EntityEditorPropertyView : public UIElement {
    public:
    
        EntityEditorPropertyView();
        ~EntityEditorPropertyView();
    
        void setEntityInstance(SceneEntityInstance *instance);
        void setEntity(Entity *entity, bool rootEntityMode = false);
        void handleEvent(Event *event);
        void updateShaderOptions();
    
        PropList *getEntityProps();
        void Resize(Number width, Number height);
    
    protected:
    
        Entity *targetEntity;
        PropList *entityProps;
    
        TransformSheet *transformSheet;    
        EntitySheet *entitySheet;
        MaterialPropSheet *materialSheet;
        ScenePrimitiveSheet *primitiveSheet;
        SceneLightSheet *lightSheet;
        ParticleEmitterSheet *particleSheet;
        SceneLabelSheet *labelSheet;
        SceneSpriteSheet *spriteSheet;
        SoundSheet *soundSheet;
        SceneCurveSheet *curveSheet;
        CameraSheet *cameraSheet;
        EntityPropSheet *propSheet;
        SceneMeshSheet *sceneMeshSheet;
    
        ShaderTexturesSheet *shaderTexturesSheet;
        ShaderOptionsSheet *shaderOptionsSheet;
};

