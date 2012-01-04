/*
 *  PolycodeIDEApp.h
 *  Polycode
 *
 *  Created by Ivan Safrin on 11/29/10.
 *  Copyright 2010 Local Projects. All rights reserved.
 *
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
#include "PolycodeFontEditor.h"
#include "PolycodeTextEditor.h"

using namespace Polycode;

class PolycodeIDEApp : public EventDispatcher {
public:
	PolycodeIDEApp(PolycodeView *view);
	~PolycodeIDEApp();
	
	void handleEvent(Event *event);	
	bool Update();
	
	void saveConfigFile();
	void loadConfigFile();
	
	// menu commands
	void newProject();
	void newFile();	
	void openProject();
	void closeProject();	
	void saveFile();
	
	const static int EVENT_SHOW_MENU = 1;
	
protected:	
	PolycodeFrame *frame;
	CocoaCore *core;
	
	PolycodeEditorManager *editorManager;
	PolycodeProjectManager *projectManager;
	
};
