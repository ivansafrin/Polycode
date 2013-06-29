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
 
#pragma once

#include "Polycode.h"
#include "OSBasics.h"
#include "PolycodeProject.h"
#include "PolycodeClipboard.h"

#define MAX_EDITOR_UNDO_ACTIONS	40

using namespace Polycode;

class PolycodeEditorActionData {
	public:
		PolycodeEditorActionData(){}
		virtual ~PolycodeEditorActionData() {}
};

class PolycodeEditorAction  {
	public:
		PolycodeEditorAction(){}
		~PolycodeEditorAction() {}

		void deleteData() {
			delete beforeData;
			delete afterData;
		}

		String actionName;
		PolycodeEditorActionData *beforeData;
		PolycodeEditorActionData *afterData;
};

class PolycodeEditor : public ScreenEntity, public ClipboardProvider { 
public:
	PolycodeEditor(bool _isReadOnly);
	virtual ~PolycodeEditor();

	virtual bool openFile(OSFileEntry filePath){ this->filePath = filePath.fullPath; return true;}
	virtual void Resize(int x, int y);

	virtual void handleEvent(Event *event);

	virtual void Activate() {};
	virtual void saveFile(){};

	void didAction(String actionName, PolycodeEditorActionData *beforeData, PolycodeEditorActionData *afterData, bool setFileChanged = true);
	virtual void doAction(String actionName, PolycodeEditorActionData *data) {}

	virtual String Copy(void **data) { return ""; }
	virtual void Paste(void *data, String clipboardType) {}

	virtual void handleDroppedFile(OSFileEntry file, Number x, Number y) {};

	void setFilePath(String newPath);
	String getFilePath() { return filePath; }

	bool isReadOnly() { return _isReadOnly; }

	String getEditorType() { return editorType; }

	bool hasChanges() { return _hasChanges;}

	void setHasChanges(bool newVal);

	PolycodeProject *parentProject;

protected:

	bool _hasChanges;

	String filePath;
	bool _isReadOnly;

	Vector2 editorSize;

	String editorType;

	std::vector<PolycodeEditorAction> editorActions;
	int currentUndoPosition;
};


class PolycodeEditorFactory {
public:
	PolycodeEditorFactory();
	virtual ~PolycodeEditorFactory();

	virtual PolycodeEditor *createEditor() = 0;

	bool canHandleExtension(String extension);

protected:
	std::vector<std::string> extensions;

};
