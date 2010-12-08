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

using namespace Polycode;

class PolycodeIDEApp : public EventHandler {
public:
	PolycodeIDEApp(SubstanceView *view);
	~PolycodeIDEApp();
	
	void handleEvent(Event *event);	
	bool Update();
	
	// menu commands
	void newProject();
	void openProject();
	
protected:	
	PolycodeFrame *frame;
	CocoaCore *core;
	
	PolycodeEditorManager *editorManager;
	PolycodeProjectManager *projectManager;
	
};
