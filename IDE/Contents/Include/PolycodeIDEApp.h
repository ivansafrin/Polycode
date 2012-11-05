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
 
#import "PolycodeView.h"

#include "PolycodeGlobals.h"
#include "PolycodeProjectManager.h"
#include "PolycodeEditorManager.h"
#include "Polycode.h"
#include "PolyCocoaCore.h"
#include "PolycodeUI.h"
#include "PolycodeFrame.h"

#include "PolycodeImageEditor.h"
#include "PolycodeMaterialEditor.h"
#include "PolycodeScreenEditor.h"
#include "PolycodeFontEditor.h"
#include "PolycodeTextEditor.h"
#include "PolycodeProjectEditor.h"

#include "PolycodeToolLauncher.h"

#include "PolycodeRemoteDebugger.h"

using namespace Polycode;

class PolycodeIDEApp : public EventDispatcher {
public:
	PolycodeIDEApp(PolycodeView *view);
	~PolycodeIDEApp();
	
	void handleEvent(Event *event);	
	bool Update();
	
	void saveConfigFile();
	void loadConfigFile();
	
	void openFileInProject(PolycodeProject *project, String filePath);
	
	void openFile(OSFileEntry file);
	
	void stopProject();
	
	// menu commands
	void renameFile();
	void removeFile();
	void browseExamples();
	void newProject();
	void newFile();	
	void newGroup();
	void openProject();
	void closeProject();	
	void saveFile();
	void findText();
	
	void refreshProject();
	
	void runProject();
	
	const static int EVENT_SHOW_MENU = 1;
	
	CocoaCore *core;	
protected:	
	PolycodeFrame *frame;
	
	PolycodeEditorManager *editorManager;
	PolycodeProjectManager *projectManager;
	
	PolycodeRemoteDebugger *debugger;
	
};
