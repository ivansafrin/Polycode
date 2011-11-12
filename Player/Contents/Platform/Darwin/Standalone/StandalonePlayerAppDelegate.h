//
//  StandalonePlayerAppDelegate.h
//  StandalonePlayer
//
//  Created by Ivan Safrin on 5/25/11.
//  Copyright 2011 Tomatogon. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "PolycodeView.h"
#include "PolycodeCocoaPlayer.h"

@interface StandalonePlayerAppDelegate : NSObject <NSApplicationDelegate> {
@private
	NSWindow *window;
	PolycodeView *mainView;
	CocoaPolycodePlayer *player;
	NSTimer *timer;
}

@property (assign) IBOutlet NSWindow *window;
@property (assign) IBOutlet PolycodeView *mainView;

@end
