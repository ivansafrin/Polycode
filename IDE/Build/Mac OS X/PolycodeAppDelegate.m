//
//  PolycodeAppDelegate.m
//  Polycode
//
//  Created by Ivan Safrin on 11/28/10.
//  Copyright 2010 Local Projects. All rights reserved.
//PolycodeIDEApp

#import "PolycodeAppDelegate.h"

void PolycodeAppEventHandler::handleEvent(Event *evt) {
	switch(evt->getEventCode()) {
		case PolycodeIDEApp::EVENT_SHOW_MENU:
			[appDelegate showProjectMenu];
			break;
	}
}

@implementation PolycodeAppDelegate

@synthesize window;
@synthesize polycodeView;
@synthesize projectMenu;

- (id) init {
	app = NULL;
	return [super init];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
	// Insert code here to initialize your application 
	
	mustShowProjectMenu = NO;
	
	eventHandler = new PolycodeAppEventHandler();
	eventHandler->appDelegate = self;
    
    [[window windowController] setShouldCascadeWindows:NO];
    [window setFrameAutosaveName:[window representedFilename]];
	
	app = new PolycodeIDEApp(polycodeView);
	app->addEventListener(eventHandler, PolycodeIDEApp::EVENT_SHOW_MENU);
	
	if(fileToOpen != "") {
		app->openProject(fileToOpen);
	}
	
	timer = [NSTimer timerWithTimeInterval:(1.0f/90.0f) target:self selector:@selector(animationTimer:) userInfo:nil repeats:YES];
	[[NSRunLoop currentRunLoop] addTimer:timer forMode:NSDefaultRunLoopMode];
	[[NSRunLoop currentRunLoop] addTimer:timer forMode:NSEventTrackingRunLoopMode]; // ensure timer fires during resize	
}

- (void)animationTimer:(NSTimer *)timer
{
	if(!app->Update()) {
		[[NSApplication sharedApplication] terminate:self];
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
}

- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)theApplication
{
	app->saveConfigFile();
	bool retVal = app->quitApp();
	if(retVal) {
		app->core->Shutdown();
		printf("STOPPING\n");
	}
	return retVal;
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication
{
	return YES;
}

- (BOOL)application:(NSApplication *)theApplication openFile:(NSString *)filename
{
	// this gets called before applicationDidFinishLaunching if 
	// user double-clicks the file to open the app
	
	if(app) {
		app->openProject([filename cStringUsingEncoding:NSUTF8StringEncoding]);
	} else {
		fileToOpen = [filename cStringUsingEncoding:NSUTF8StringEncoding];
	}
	return YES;
}

-(IBAction) refreshProject: (id) sender {
	app->refreshProject();
}	

-(IBAction) renameFile: (id) sender {
	app->renameFile();
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

-(IBAction) exportProject: (id) sender {
	app->exportProject();
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

-(IBAction) closeFile: (id) sender {
	app->closeFile();
}

-(IBAction) saveFile: (id) sender {
	app->saveFile();
}

-(IBAction) findText: (id) sender {
	app->findText();
}

-(IBAction) openDocs: (id) sender {
	app->openDocs();
}

-(IBAction) showAbout: (id) sender {
	app->showAbout();
}

-(IBAction) toggleConsole: (id) sender {
	app->toggleConsole();
}

-(IBAction) showSettings: (id) sender {
	app->showSettings();
}

-(IBAction) createNewTab: (id) sender {
	app->createNewTab();
}

-(IBAction) showNextTab: (id) sender {
	app->showNextTab();
}

-(IBAction) showPreviousTab: (id) sender {
	app->showPreviousTab();
}

-(IBAction) closeTab: (id) sender {
	app->closeTab();
}


@end
