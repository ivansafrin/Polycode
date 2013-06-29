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

#if defined(__APPLE__) && defined(__MACH__)
#import "PolycodeView.h"
#else
#include "PolycodeView.h"
#endif

#include "PolycodeGlobals.h"
#include "PolycodeProjectManager.h"
#include "PolycodeEditorManager.h"
#include "Polycode.h"
//#include "PolyCocoaCore.h"
#include "PolycodeUI.h"
#include "PolycodeFrame.h"

#include "PolycodeImageEditor.h"
#include "PolycodeMaterialEditor.h"
#include "PolycodeScreenEditor.h"
#include "PolycodeFontEditor.h"
#include "PolycodeTextEditor.h"
#include "PolycodeProjectEditor.h"
#include "PolycodeSpriteEditor.h"

#include "PolycodeToolLauncher.h"

#include "PolycodeRemoteDebugger.h"
#include "PolycodeClipboard.h"

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
	void doRemoveFile();
	void browseExamples();
	void newProject();
	void newFile();
	void showAbout();

	void openDocs();

	void addFiles();

	void newGroup();
	void openProject();
	void closeProject();
	void closeFile();
	void saveFile();
	void findText();
	void runProject();
	void doRunProject();
	void exportProject();
	void toggleConsole();
	void showSettings();

	void removeEditor(PolycodeEditor *editor);

	// system callbacks

	void openProject(String projectFile);

	void refreshProject();	

	bool quitApp();

	bool needsRedraw;
	bool lastConnected;

	const static int EVENT_SHOW_MENU = 1;

	Core *core;

	void saveFiles(std::vector<PolycodeEditor*> editors);
	void closeFiles(std::vector<PolycodeEditor*> editors, String saveMsg="");
	bool filesHaveChanges(std::vector<PolycodeEditor*> editors);

protected:

	bool quittingApp;
	bool runNextFrame;

	bool willRunProject;
	PolycodeFrame *frame;

	PolycodeEditorManager *editorManager;
	PolycodeProjectManager *projectManager;

	PolycodeRemoteDebugger *debugger;

	UIMenuBar *menuBar;

private:
	void doCloseProject();
	void doCloseFiles(std::vector<PolycodeEditor*> editors);

	// used in saving/closing files via popup dialog prompts
	std::vector<PolycodeEditor*> tempEditorStore;
};
