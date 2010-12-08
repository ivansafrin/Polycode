/*
 *  PolycodeFrame.h
 *  Polycode
 *
 *  Created by Ivan Safrin on 11/29/10.
 *  Copyright 2010 Local Projects. All rights reserved.
 *
 */

#include "PolycodeUI.h"
#include "Polycode.h"
#include "PolycodeProjectBrowser.h"
#include "PolycodeEditor.h"
#include "NewProjectWindow.h"

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
	
private:
	
	int frameSizeX;
	int frameSizeY;
	
	ScreenShape *topBarBg;
	ScreenImage *logo;	
	ScreenImage *resizer;	
	
	ScreenEntity *editorHolder;
	
	PolycodeEditor *currentEditor;
	vector<PolycodeEditor*> editors;
	
	ScreenShape *modalBlocker;
	UIWindow *modalChild;	
	
	PolycodeProjectBrowser *projectBrowser;
};