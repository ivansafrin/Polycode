//
//  MyDocument.m
//  Polycode Player
//
//  Created by Ivan Safrin on 12/13/10.
//  Copyright 2010 Local Projects. All rights reserved.
//

#import "MyDocument.h"

@implementation MyDocument

@synthesize substanceView;


- (id)init
{
    self = [super init];
    if (self) {
    
        // Add your subclass-specific initialization here.
        // If an error occurs here, send a [self release] message and return nil.
    
    }
    return self;
}

- (NSString *)windowNibName
{
    // Override returning the nib file name of the document
    // If you need to use a subclass of NSWindowController or if your document supports multiple NSWindowControllers, you should remove this method and override -makeWindowControllers instead.
    return @"MyDocument";
}

- (void)windowControllerDidLoadNib:(NSWindowController *) aController
{
    [super windowControllerDidLoadNib:aController];
    // Add any code here that needs to be executed once the windowController has loaded the document's window.		

	player =  new CocoaPolycodePlayer(substanceView, [docFileName cStringUsingEncoding:NSASCIIStringEncoding], false);
	playerProxy = new PolycodeProxy();
	playerProxy->playerDocument = self;
	player->addEventListener(playerProxy, PolycodeDebugEvent::EVENT_RESIZE);
	player->windowData = self;
	
	player->runPlayer();

	
	timer = [NSTimer timerWithTimeInterval:(1.0f/90.0f) target:self selector:@selector(animationTimer:) userInfo:nil repeats:YES];
	[[NSRunLoop currentRunLoop] addTimer:timer forMode:NSDefaultRunLoopMode];
	[[NSRunLoop currentRunLoop] addTimer:timer forMode:NSEventTrackingRunLoopMode]; // ensure timer fires during resize		
}

- (void)animationTimer:(NSTimer *)timer
{

	if(!player->Update()) {
		[self close];
	}
}

- (NSData *)dataOfType:(NSString *)typeName error:(NSError **)outError
{
    // Insert code here to write your document to data of the specified type. If the given outError != NULL, ensure that you set *outError when returning nil.

    // You can also choose to override -fileWrapperOfType:error:, -writeToURL:ofType:error:, or -writeToURL:ofType:forSaveOperation:originalContentsURL:error: instead.

    // For applications targeted for Panther or earlier systems, you should use the deprecated API -dataRepresentationOfType:. In this case you can also choose to override -fileWrapperRepresentationOfType: or -writeToFile:ofType: instead.

    if ( outError != NULL ) {
		*outError = [NSError errorWithDomain:NSOSStatusErrorDomain code:unimpErr userInfo:NULL];
	}
	return nil;
}

- (BOOL)readFromURL:(NSURL *)absoluteURL ofType:(NSString *)typeName error:(NSError **)outError
{	
	NSLog(@"Reading from %@\n", docFileName);
	docFileName = [[NSString stringWithString:[absoluteURL path]] retain];
	
	return YES;
}

@end
