//
//  PolycodeAppDelegate.h
//  Polycode
//
//  Created by Ivan Safrin on 11/28/10.
//  Copyright 2010 Local Projects. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "PolycodeView.h"

#include "Polycode.h"
#include "PolycodeIDEApp.h"

using namespace Polycode;

class PolycodeAppEventHandler : public EventHandler {
	
public:
	PolycodeAppEventHandler() {}
	~PolycodeAppEventHandler() {}
	
	void handleEvent(Event *evt) {
		switch(evt->getEventCode()) {
			case PolycodeIDEApp::EVENT_SHOW_MENU:
				[appDelegate showProjectMenu];
			break;
		}
	}
	
	id appDelegate;
};

@interface PolycodeAppDelegate : NSObject <NSApplicationDelegate> {
    NSWindow *window;	
	PolycodeIDEApp *app;
	PolycodeView *polycodeView;
	PolycodeAppEventHandler *eventHandler;
	NSTimer* timer;
	
	NSMenu *projectMenu;
	
	BOOL mustShowProjectMenu;
}

@property (assign) IBOutlet PolycodeView *polycodeView;
@property (assign) IBOutlet NSWindow *window;
@property (assign) IBOutlet NSMenu *projectMenu;

- (void) showProjectMenu;

// Menu accessors

-(void) newProject: (id) sender;
-(void) closeProject: (id) sender;
-(void) newFile: (id) sender;
-(void) openProject: (id) sender;
-(void) saveFile: (id) sender;

@end
