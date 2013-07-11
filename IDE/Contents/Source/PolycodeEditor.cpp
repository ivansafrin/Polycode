/*
 Copyright (C) 2012 by Ivan Safrin
 
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

#include "PolycodeEditor.h"

extern PolycodeClipboard *globalClipboard;

PolycodeEditorFactory::PolycodeEditorFactory() {
	
}

PolycodeEditorFactory::~PolycodeEditorFactory() {
	
}

bool PolycodeEditorFactory::canHandleExtension(String extension) {
	for(int i=0; i < extensions.size(); i++) {
		if(extension == extensions[i])
		   return true;
	}
	return false;
}

void PolycodeEditor::setFilePath(String newPath) {
	filePath = newPath;
}

PolycodeEditor::PolycodeEditor(bool _isReadOnly) : ScreenEntity(), ClipboardProvider() {
	this->_isReadOnly = _isReadOnly;
	enableScissor = true;	
	processInputEvents = true;
	_hasChanges = false;
	
	currentUndoPosition = 0;
	
	Core *core = CoreServices::getInstance()->getCore();
	
	core->addEventListener(this, Core::EVENT_COPY);
	core->addEventListener(this, Core::EVENT_PASTE);
	core->addEventListener(this, Core::EVENT_UNDO);	
	core->addEventListener(this, Core::EVENT_REDO);	
}

void PolycodeEditor::setHasChanges(bool newVal) {
	if(_hasChanges != newVal) {
		_hasChanges = newVal;	
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}
}

void PolycodeEditor::handleEvent(Event *event) {
	if(event->getDispatcher() == CoreServices::getInstance()->getCore() && enabled) {
		switch(event->getEventCode()) {

			// Only copypaste of more complex IDE entities is handled here.
			// Pure text copy/paste is handled in:
			// Modules/Contents/UI/Source/PolyUITextInput.cpp
			case Core::EVENT_COPY:
			{
				void *data = NULL;
				String dataType = Copy(&data);
				if(data) {
					globalClipboard->setData(data, dataType, this);
				}
			}
			break;
			case Core::EVENT_PASTE:
			{
				if(globalClipboard->getData()) {
					Paste(globalClipboard->getData(), globalClipboard->getType());
				}
			}
			break;
			case Core::EVENT_UNDO:
			{
				if(editorActions.size() > 0) {
				doAction(editorActions[currentUndoPosition].actionName, editorActions[currentUndoPosition].beforeData);
				currentUndoPosition--;
				if(currentUndoPosition < 0) {
					currentUndoPosition = 0;
				}
				}				
			}
			break;
			case Core::EVENT_REDO:
			{
				if(editorActions.size() > 0) {			
				currentUndoPosition++;
				if(currentUndoPosition > editorActions.size()-1) {
					currentUndoPosition = editorActions.size()-1;
				} else {
					doAction(editorActions[currentUndoPosition].actionName, editorActions[currentUndoPosition].afterData);
				}
				}
			}
			break;			
		}
	}
}

void PolycodeEditor::didAction(String actionName, PolycodeEditorActionData *beforeData, PolycodeEditorActionData *afterData, bool setFileChanged) {

//	printf("DID ACTION: %s\n", actionName.c_str());
	
	if(setFileChanged) {
		setHasChanges(true);
	}
	
	// if the undo position is not at the end, remove the states after it
	if(currentUndoPosition < editorActions.size()-1 && editorActions.size() > 0) {
		for(int i=currentUndoPosition+1; i < editorActions.size(); i++) {
			editorActions[i].deleteData();		
		}
		editorActions.erase(editorActions.begin()+currentUndoPosition+1, editorActions.end());
	}

	PolycodeEditorAction newAction;
	newAction.actionName = actionName;
	newAction.beforeData = beforeData;
	newAction.afterData = afterData;	
	editorActions.push_back(newAction);
	
	if(editorActions.size() > MAX_EDITOR_UNDO_ACTIONS) {
		editorActions[0].deleteData();
		editorActions.erase(editorActions.begin());
	}
	
	currentUndoPosition = editorActions.size()-1;	
}

void PolycodeEditor::Resize(int x, int y) {
	editorSize = Vector2(x,y);
	Vector2 pos = getScreenPosition();
	scissorBox.setRect(pos.x,pos.y, x, y);	
}

PolycodeEditor::~PolycodeEditor() {
	Core *core = CoreServices::getInstance()->getCore();
	core->removeAllHandlersForListener(this);
}


