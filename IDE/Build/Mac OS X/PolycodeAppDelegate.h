//
//  PolycodeAppDelegate.h
//  Polycode
//
//  Created by Ivan Safrin on 11/28/10.
//  Copyright 2010 Local Projects. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "PolySubstanceView.h"

#include "PolycodeIDEApp.h"

@interface PolycodeAppDelegate : NSObject <NSApplicationDelegate> {
    NSWindow *window;	
	PolycodeIDEApp *app;
	SubstanceView *substanceView;
	
	NSTimer* timer;
}

@property (assign) IBOutlet SubstanceView *substanceView;
@property (assign) IBOutlet NSWindow *window;

// Menu accessors

-(void) newProject: (id) sender;
-(void) openProject: (id) sender;
-(void) saveFile: (id) sender;

@end
