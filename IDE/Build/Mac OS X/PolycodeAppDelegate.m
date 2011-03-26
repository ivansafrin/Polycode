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
@synthesize projectMenu;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
	// Insert code here to initialize your application 
	
	mustShowProjectMenu = NO;
	
	eventHandler = new PolycodeAppEventHandler();
	eventHandler->appDelegate = self;
	
	app = new PolycodeIDEApp(substanceView);
	app->addEventListener(eventHandler, PolycodeIDEApp::EVENT_SHOW_MENU);
	
	timer = [NSTimer timerWithTimeInterval:(1.0f/90.0f) target:self selector:@selector(animationTimer:) userInfo:nil repeats:YES];
	[[NSRunLoop currentRunLoop] addTimer:timer forMode:NSDefaultRunLoopMode];
	[[NSRunLoop currentRunLoop] addTimer:timer forMode:NSEventTrackingRunLoopMode]; // ensure timer fires during resize	
}

- (void)animationTimer:(NSTimer *)timer
{
	if(!app->Update()) {
		[[NSApplication sharedApplication] stop:self];
	}
	
	if(mustShowProjectMenu) {
		NSPoint menuOrigin = NSMakePoint(substanceView.mouseX, substanceView.mouseY);
		
		NSEvent *event =  [NSEvent mouseEventWithType:NSLeftMouseDown
											 location:menuOrigin
										modifierFlags:NSLeftMouseDownMask // 0x100
											timestamp:nil
										 windowNumber:[window windowNumber]
											  context:[window graphicsContext]
										  eventNumber:0
										   clickCount:1
											 pressure:1];	
		
		[NSMenu popUpContextMenu:projectMenu withEvent:event forView:substanceView];
		
		mustShowProjectMenu = NO;
	}
}

- (void) showProjectMenu {
	
	mustShowProjectMenu = YES;	
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
	delete app;
}

-(void) newProject: (id) sender {
	app->newProject();
}

-(void) newFile: (id) sender {
	app->newFile();
}

-(void) openProject: (id) sender {
	app->openProject();
}

-(void) closeProject: (id) sender {
	app->closeProject();
}

-(void) saveFile: (id) sender {
	app->saveFile();
}

@end
