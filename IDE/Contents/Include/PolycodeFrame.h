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

#include "PolycodeUI.h"
#include "Polycode.h"
#include "PolycodeProjectBrowser.h"
#include "PolycodeEditor.h"
#include "NewProjectWindow.h"
#include "ExampleBrowserWindow.h"
#include "NewFileWindow.h"
#include "ToolWindows.h"

using namespace Polycode;

class PolycodeFrame : public ScreenEntity {
public:
	
	PolycodeFrame();
	~PolycodeFrame();
	
	void Resize(int x, int y);
	
	void showModal(UIWindow *modalChild);
	void hideModal();
	
	void handleEvent(Event *event);
	
	void addEditor(PolycodeEditor *editor);
	void showEditor(PolycodeEditor *editor);
	
	PolycodeProjectBrowser *getProjectBrowser();
	
	NewProjectWindow *newProjectWindow;	
	ExampleBrowserWindow *exampleBrowserWindow;
	NewFileWindow *newFileWindow;
	
	TextInputPopup *textInputPopup;
	
	ScreenEntity *welcomeEntity;	
	PolycodeProjectBrowser *projectBrowser;
		
	UIImageButton *playButton;
			
private:
	
	int frameSizeX;
	int frameSizeY;
	
	ScreenShape *topBarBg;
	ScreenImage *logo;	
	ScreenImage *resizer;	

	
	ScreenImage *welcomeImage;	
	
	ScreenEntity *editorHolder;
	
	PolycodeEditor *currentEditor;
	vector<PolycodeEditor*> editors;
	
	ScreenShape *modalBlocker;
	UIWindow *modalChild;		
	
	UIButton *newProjectButton;
	UIButton *examplesButton;
	
};