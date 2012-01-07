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
@synthesize polycodeView;
@synthesize projectMenu;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
	// Insert code here to initialize your application 
	
	mustShowProjectMenu = NO;
	
	eventHandler = new PolycodeAppEventHandler();
	eventHandler->appDelegate = self;
	
	app = new PolycodeIDEApp(polycodeView);
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
		NSPoint menuOrigin = NSMakePoint(polycodeView.mouseX, polycodeView.mouseY);
		
		NSEvent *event =  [NSEvent mouseEventWithType:NSLeftMouseDown
											 location:menuOrigin
										modifierFlags:NSLeftMouseDownMask // 0x100
											timestamp:nil
										 windowNumber:[window windowNumber]
											  context:[window graphicsContext]
										  eventNumber:0
										   clickCount:1
											 pressure:1];	
		
		[NSMenu popUpContextMenu:projectMenu withEvent:event forView:polycodeView];
		
		mustShowProjectMenu = NO;
	}
}

- (void) showProjectMenu {
	
	mustShowProjectMenu = YES;	
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
	NSLog(@"STOPPING\n");
	app->saveConfigFile();
	app->core->Shutdown();
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication
{
	return YES;
}

-(IBAction) removeFile: (id) sender {
	app->removeFile();
}

-(IBAction) newGroup: (id) sender {
	app->newGroup();
}

-(IBAction) browseExamples: (id) sender {
	app->browseExamples();
}

-(IBAction) runProject: (id) sender {
	app->runProject();
}

-(IBAction) newProject: (id) sender {
	app->newProject();
}

-(IBAction) newFile: (id) sender {
	app->newFile();
}

-(IBAction) openProject: (id) sender {
	app->openProject();
}

-(IBAction) closeProject: (id) sender {
	app->closeProject();
}

-(IBAction) saveFile: (id) sender {
	app->saveFile();
}

@end
