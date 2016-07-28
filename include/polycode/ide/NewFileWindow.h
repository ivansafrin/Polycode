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

#include "polycode/ide/PolycodeGlobals.h"
#include "polycode/modules/ui/PolycodeUI.h"
#include "Polycode.h"
#include "polycode/ide/PolycodeProjectBrowser.h"

using namespace Polycode;

class FileTemplateUserData	{
public:
	String templatePath;
	int type;
};

class NewFileWindow : public UIWindow {
	public:
		NewFileWindow(Core *core, ResourcePool *pool);
		~NewFileWindow();
	
		void resetForm();
		void parseTemplatesIntoTree(UITree *tree, OSFileEntry folder);

		String getTemplatePath();
		String getFileName();
		
		void handleEvent(Event *event);
	
	protected:
	
		UITextInput *fileNameInput;
	
		UIButton *cancelButton;
		UIButton *okButton;
		
		String templatePath;
			
		UITreeContainer *templateContainer; 
		UITree *defaultTemplateTree;
};