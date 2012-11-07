//
//  StandalonePlayerAppDelegate.m
//  StandalonePlayer
//
//  Created by Ivan Safrin on 5/25/11.
//  Copyright 2011 Tomatogon. All rights reserved.
//

#import "StandalonePlayerAppDelegate.h"

@implementation StandalonePlayerAppDelegate

@synthesize window;
@synthesize mainView;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	chdir([[[[NSBundle mainBundle] bundlePath] stringByAppendingString:@"/Contents/Resources"] UTF8String]);

	player =  new CocoaPolycodePlayer(mainView, "main.polyapp", false, false);
	player->windowData = self;	
	player->runPlayer();

	timer = [NSTimer timerWithTimeInterval:(1.0f/90.0f) target:self selector:@selector(animationTimer:) userInfo:nil repeats:YES];
	[[NSRunLoop currentRunLoop] addTimer:timer forMode:NSDefaultRunLoopMode];
	[[NSRunLoop currentRunLoop] addTimer:timer forMode:NSEventTrackingRunLoopMode]; // ensure timer fires during resize

}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication
{
	return YES;
}

- (void)animationTimer:(NSTimer *)timer
{

	if(!player->Update()) {
		[window close];
	}
}

@end
