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

	Core *core = CoreServices::getInstance()->getCore();
	
	core->addEventListener(this, Core::EVENT_COPY);
	core->addEventListener(this, Core::EVENT_PASTE);
}

void PolycodeEditor::setHasChanges(bool newVal) {
	if(_hasChanges != newVal) {
		_hasChanges = newVal;	
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}
}

void PolycodeEditor::handleEvent(Event *event) {
	if(event->getDispatcher() == CoreServices::getInstance()->getCore()) {
		switch(event->getEventCode()) {
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
		}
	}
}

void PolycodeEditor::Resize(int x, int y) {
	editorSize = Vector2(x,y);
	Vector2 pos = getScreenPosition();
	scissorBox.setRect(pos.x,pos.y, x, y);	
}

PolycodeEditor::~PolycodeEditor() {
	
}


