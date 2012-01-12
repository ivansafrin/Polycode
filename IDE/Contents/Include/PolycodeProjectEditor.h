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

#include "PolycodeGlobals.h"
#include "PolycodeUI.h"
#include "PolycodeEditor.h"
#include <Polycode.h>

using namespace Polycode;

class PolycodeProjectEditor : public PolycodeEditor {
	public:
	PolycodeProjectEditor();
	virtual ~PolycodeProjectEditor();
	
	bool openFile(String filePath);
	void Resize(int x, int y);
	void saveFile();
	
	protected:
	
	Object configFile;	
	
	std::vector<UICheckBox*> moduleCheckboxes;
	
	UIWindow *mainSettingsWindow;
	UIWindow *moduleSettingsWindow;
		
	UICheckBox *vSyncCheckBox;
	UITextInput *defaultWidthInput;
	UITextInput *defaultHeightInput;	
	UITextInput *framerateInput;	
	UIComboBox *aaLevelComboBox;
	UIComboBox *afLevelComboBox;	
	UITextInput *entryPointInput;	
	UIColorBox *bgColorBox;
	
};

class PolycodeProjectEditorFactory : public PolycodeEditorFactory {
	public:
		PolycodeProjectEditorFactory() : PolycodeEditorFactory() { extensions.push_back("polyproject"); }
		PolycodeEditor *createEditor() { return new PolycodeProjectEditor(); }
};
