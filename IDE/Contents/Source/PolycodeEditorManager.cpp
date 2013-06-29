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
 
#include "PolycodeEditorManager.h"


PolycodeEditorManager::PolycodeEditorManager()  : EventDispatcher() {
	currentEditor = NULL;
}

PolycodeEditorManager::~PolycodeEditorManager() {

}

PolycodeEditorFactory *PolycodeEditorManager::getEditorFactoryForExtension(String extension) {
	for(int i=0;i < editorFactories.size(); i++) {
		PolycodeEditorFactory *factory = editorFactories[i];
		if(factory->canHandleExtension(extension)) {
			return factory;
		}
	}
	return NULL;
}

PolycodeEditor *PolycodeEditorManager::createEditorForExtension(String extension) {
	for(int i=0;i < editorFactories.size(); i++) {
		PolycodeEditorFactory *factory = editorFactories[i];
		if(factory->canHandleExtension(extension)) {
			PolycodeEditor *editor = factory->createEditor();
			openEditors.push_back(editor);
			editor->addEventListener(this, Event::CHANGE_EVENT);
			return editor;
		}
	}
	return NULL;
}

void PolycodeEditorManager::destroyEditor(PolycodeEditor* editor) {
	for(int i=0; i < openEditors.size();i++) {
		if(openEditors[i] == editor) {
			openEditors.erase(openEditors.begin()+i);
			delete editor;
			dispatchEvent(new Event(), Event::CHANGE_EVENT);
			return;
		}
	}
}

bool PolycodeEditorManager::hasUnsavedFiles() {
	for(int i=0; i < openEditors.size();i++) {
		PolycodeEditor *editor = openEditors[i];
		if(editor->hasChanges())
			return true;
	}
	return false;
}

void PolycodeEditorManager::saveAll() {
	for(int i=0; i < openEditors.size();i++) {
		PolycodeEditor *editor = openEditors[i];
		editor->saveFile();
	}
}

void PolycodeEditorManager::saveFilesForProject(PolycodeProject *project) {
	for(int i=0; i < openEditors.size(); i++) {
		if(openEditors[i]->hasChanges() && openEditors[i]->parentProject == project)
			openEditors[i]->saveFile();
	}
}

bool PolycodeEditorManager::hasUnsavedFilesForProject(PolycodeProject *project) {
	for(int i=0; i < openEditors.size();i++) {
		PolycodeEditor *editor = openEditors[i];
		if(editor->hasChanges() && editor->parentProject == project)
			return true;
	}
	return false;
}

void PolycodeEditorManager::handleEvent(Event *event) {
	dispatchEvent(new Event(), Event::CHANGE_EVENT);
}

void PolycodeEditorManager::setCurrentEditor(PolycodeEditor *editor, bool sendChangeEvent) {
	currentEditor = editor;
	if(sendChangeEvent){
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}
}


PolycodeEditor *PolycodeEditorManager::getEditorForPath(String path) {
	for(int i=0; i < openEditors.size();i++) {
		PolycodeEditor *editor = openEditors[i];
		if(editor->getFilePath() == path)
			return editor;
	}
	return NULL;
}

void PolycodeEditorManager::registerEditorFactory(PolycodeEditorFactory *editorFactory) {
	editorFactories.push_back(editorFactory);
}
