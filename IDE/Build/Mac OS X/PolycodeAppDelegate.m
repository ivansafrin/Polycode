//
//  PolycodeAppDelegate.m
//  Polycode
//
//  Created by Ivan Safrin on 11/28/10.
//  Copyright 2010 Local Projects. All rights reserved.
//PolycodeIDEApp

#import "PolycodeAppDelegate.h"

@implementation PolycodeAppDelegate

@synthesize window;
@synthesize substanceView;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
	// Insert code here to initialize your application 
	
	app = new PolycodeIDEApp(substanceView);
	
	timer = [NSTimer timerWithTimeInterval:(1.0f/90.0f) target:self selector:@selector(animationTimer:) userInfo:nil repeats:YES];
	[[NSRunLoop currentRunLoop] addTimer:timer forMode:NSDefaultRunLoopMode];
	[[NSRunLoop currentRunLoop] addTimer:timer forMode:NSEventTrackingRunLoopMode]; // ensure timer fires during resize	
}

- (void)animationTimer:(NSTimer *)timer
{
	if(!app->Update()) {
		[[NSApplication sharedApplication] stop:self];
	}
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
	delete app;
}

-(void) newProject: (id) sender {
	app->newProject();
}

-(void) openProject: (id) sender {
	app->openProject();
}

@end
