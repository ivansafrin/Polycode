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

#include "EntityEditorTreeView.h"

EntityEditorTreeView::EntityEditorTreeView() : UIElement() {

    treeContainer = new UITreeContainer("folder.png", "Root", 10, 10);
    addChild(treeContainer);
    treeContainer->getRootNode()->addEventListener(this, UITreeEvent::SELECTED_EVENT);
    treeContainer->setPosition(0, 30);
    treeContainer->getRootNode()->toggleCollapsed();
    
	headerBg = new UIRect(10,10);
	addChild(headerBg);
	headerBg->setAnchorPoint(-1.0, -1.0, 0.0);
	headerBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));
	
	UILabel *label = new UILabel("TREE VIEW", 18, "section", Label::ANTIALIAS_FULL);
	label->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderFontColor"));
	
	addChild(label);
	label->setPosition(10, 3);
    
    selectedEntity = NULL;
    dontSendSelectionEvent = false;
}

void EntityEditorTreeView::setRootEntity(Entity *entity) {
    rootEntity = entity;
    treeContainer->getRootNode()->setUserData((void*) entity);
    refreshTree();
}

void EntityEditorTreeView::syncNodeToEntity(UITree *node, Entity *entity) {
    // remove non existing and set proper ids,
	
	std::vector<UITree*> nodesToRemove;
    
	for(int i=0; i < node->getNumTreeChildren(); i++) {
		UITree *child = node->getTreeChild(i);
		
		bool hasChild = false;
		for(int j=0; j < entity->getNumChildren(); j++) {
			if(!entity->getChildAtIndex(j)->editorOnly) {
                if(((Entity*)child->getUserData()) == entity->getChildAtIndex(j)) {
                    hasChild = true;
                    
                    String entityName = entity->getChildAtIndex(j)->id;
                    if(entityName == "") {
                        entityName = "<unnamed entity>";
                    }
                    
                    if(child->getLabelText() != entityName) {
                        child->setLabelText(entityName);
                    }
                    
                    if(entity->getChildAtIndex(j) == selectedEntity) {
                        dontSendSelectionEvent = true;
                        child->setSelected();
                    }
                    
                }
			}
		}
        
		if(!hasChild) {
			nodesToRemove.push_back(child);
		}
	}
	
	for(int i=0; i < nodesToRemove.size(); i++) {
		node->removeTreeChild(nodesToRemove[i]);
	}
	
	std::vector<Entity*> entitiesToAdd;
	
	for(int j=0; j < entity->getNumChildren(); j++) {
		if(!entity->getChildAtIndex(j)->editorOnly) {
            bool hasEntity = false;
            for(int i=0; i < node->getNumTreeChildren(); i++) {
                UITree *child = node->getTreeChild(i);
                if(((Entity*)child->getUserData()) == entity->getChildAtIndex(j)) {
                    hasEntity = true;
                }
            }
            
            if(!hasEntity) {
                entitiesToAdd.push_back(entity->getChildAtIndex(j));
            }
		}
	}
	
	for(int i=0; i < entitiesToAdd.size(); i++) {
        
		String entityName = entitiesToAdd[i]->id;
        if(entityName == "") {
            entityName = "<unnamed entity>";
        }
        
		UITree *newNode = node->addTreeChild("file.png", entityName);
		newNode->setUserData((void*)entitiesToAdd[i]);
		
		if(entitiesToAdd[i] == selectedEntity) {
			dontSendSelectionEvent = true;
			newNode->setSelected();
		}
	}
	
	for(int i=0; i < node->getNumTreeChildren(); i++) {
		UITree *child = node->getTreeChild(i);
		syncNodeToEntity(child, ((Entity*)child->getUserData()));
	}
}

Entity *EntityEditorTreeView::getSelectedEntity() {
    return selectedEntity;
}

void EntityEditorTreeView::setSelectedEntity(Entity *entity) {
    selectedEntity = entity;
    refreshTree();
}

void EntityEditorTreeView::handleEvent(Event *event) {
	
	if(event->getDispatcher() == treeContainer->getRootNode()) {
		if(event->getEventCode() == UITreeEvent::SELECTED_EVENT){
			if(!dontSendSelectionEvent) {
                if(treeContainer->getRootNode()->getSelectedNode() != treeContainer->getRootNode()) {
                    selectedEntity = (Entity*)treeContainer->getRootNode()->getSelectedNode()->getUserData();
                    dispatchEvent(new Event(), Event::CHANGE_EVENT);
                }
			}
			dontSendSelectionEvent = false;
		}
	}
	ScreenEntity::handleEvent(event);
}


void EntityEditorTreeView::refreshTree() {
    syncNodeToEntity(treeContainer->getRootNode(), rootEntity);
}

EntityEditorTreeView::~EntityEditorTreeView() {
    
}

void EntityEditorTreeView::Resize(Number width, Number height) {
    treeContainer->Resize(width, height-30);
    headerBg->Resize(width, 30);
}