/*
 Copyright (C) 2014 by Ivan Safrin
 
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

class EntityEditorTreeSheet : public PropSheet {
    public:
        EntityEditorTreeSheet();
        ~EntityEditorTreeSheet();
    
        void refreshTree();
        void syncNodeToEntity(UITree *node, Entity *entity);
        void handleEvent(Event *event);
        void setSelectedEntity(Entity *entity);
        Entity *getSelectedEntity();
        void Resize(Number width, Number height);
        void setRootEntity(Entity *entity);
    
    private:

        Entity *selectedEntity;
        bool dontSendSelectionEvent;
        UITreeContainer *treeContainer;
        Entity *rootEntity;
    
};

class EntityEditorTreeView : public UIElement {
    public:
        EntityEditorTreeView();

        void setEntityInstance(SceneEntityInstance *instance);
        EntityEditorTreeSheet *getTreeSheet();
        void Resize(Number width, Number height);
    
    private:
    
    
        PropList *entityProps;
        EntityEditorTreeSheet *treeSheet;
        LayerSheet *layerSheet;
    

};