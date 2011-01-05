/*
 *  PolycodeIDEApp.h
 *  Polycode
 *
 *  Created by Ivan Safrin on 11/29/10.
 *  Copyright 2010 Local Projects. All rights reserved.
 *
 */

#import "PolySubstanceView.h"

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

extern "C" {	
#include <stdio.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
	
using namespace Polycode;

class PolycodeIDEApp : public EventHandler {
public:
	PolycodeIDEApp(SubstanceView *view);
	~PolycodeIDEApp();
	
	void handleEvent(Event *event);	
	bool Update();
	
	void saveConfigFile();
	void loadConfigFile();
	
	// menu commands
	void newProject();
	void newFile();	
	void openProject();
	void saveFile();
	
protected:	
	PolycodeFrame *frame;
	CocoaCore *core;
	
	PolycodeEditorManager *editorManager;
	PolycodeProjectManager *projectManager;
	
};
}
