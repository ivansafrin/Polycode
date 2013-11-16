/*
Copyright (C) 2011 by Ivan Safrin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#import "MyDocument.h"

@implementation MyDocument

@synthesize mainView;
@synthesize consoleWindow;
@synthesize consoleTextView;

- (id)init
{
    self = [super init];
    if (self) {
			playerRunning = true;
			showingConsole = NO;
			needsToClose = false;
    }
    return self;
}

- (NSString *)windowNibName
{
    return @"MyDocument";
}

- (void)windowControllerDidLoadNib:(NSWindowController *) aController
{
    [super windowControllerDidLoadNib:aController];
	
	player =  new CocoaPolycodePlayer(mainView, [docFileName cStringUsingEncoding:NSASCIIStringEncoding], false, true);
	playerProxy = new PolycodeProxy();
	playerProxy->playerDocument = self;
	
	player->addEventListener(playerProxy, PolycodeDebugEvent::EVENT_RESIZE);
	player->addEventListener(playerProxy, PolycodeDebugEvent::EVENT_PRINT);		
	player->addEventListener(playerProxy, PolycodeDebugEvent::EVENT_ERROR);			
	player->addEventListener(playerProxy, PolycodeDebugEvent::EVENT_CLOSE);				
	player->windowData = self;
	
	player->runPlayer();
	
	timer = [NSTimer timerWithTimeInterval:(1.0f/90.0f) target:self selector:@selector(animationTimer:) userInfo:nil repeats:YES];
	[[NSRunLoop currentRunLoop] addTimer:timer forMode:NSDefaultRunLoopMode];
	[[NSRunLoop currentRunLoop] addTimer:timer forMode:NSEventTrackingRunLoopMode]; // ensure timer fires during resize		
}

- (void) destroyPlayer {
	if(playerRunning) {
		printf("DESTROYING PLAYER");
		playerRunning = false;
		[timer invalidate];
		delete player;
		delete playerProxy;	
		player = NULL;
		playerProxy = NULL;		
	}	
}	

- (void) needToClosePlayer {
	needsToClose = true;
}

- (IBAction) showConsoleWindow: (id) sender 
{
	if(!showingConsole) {
		[consoleWindow makeKeyAndOrderFront:nil];
	} else{
		[consoleWindow close];
	}
	showingConsole = !showingConsole;  
}

- (void) handleDebugError: (NSString*) error onLine:(int) lineNumber
{
 
NSTextStorage *textStorage = [consoleTextView textStorage];

	[consoleTextView setInsertionPointColor: [NSColor whiteColor]];
[textStorage beginEditing];

NSMutableString *fullText = [[NSMutableString alloc] initWithString: error];
NSMutableAttributedString *str = [[NSMutableAttributedString alloc ]initWithString: fullText];
[fullText release];

[str addAttribute:NSForegroundColorAttributeName value:[NSColor redColor] range:NSMakeRange(0,[str length])];
[str addAttribute:NSFontAttributeName value:[NSFont fontWithName:@"Menlo" size: 10] range:NSMakeRange(0,[str length])];

[textStorage appendAttributedString:str];
[textStorage endEditing];
[str release];

	if(!player->useDebugger) {
		showingConsole = NO;
		[self showConsoleWindow:self];
	}

}

- (void) printToConsole: (NSString*) message 
{
 
NSTextStorage *textStorage = [consoleTextView textStorage];

	[consoleTextView setInsertionPointColor: [NSColor whiteColor]];
[textStorage beginEditing];
NSMutableAttributedString *str = [[NSMutableAttributedString alloc ]initWithString: message];
[str addAttribute:NSForegroundColorAttributeName value:[NSColor whiteColor] range:NSMakeRange(0,[str length])];
[str addAttribute:NSFontAttributeName value:[NSFont fontWithName:@"Menlo" size: 10] range:NSMakeRange(0,[str length])];

[textStorage appendAttributedString:str];
[textStorage endEditing];
[str release];
}

- (void)animationTimer:(NSTimer *)timer
{

	if(player) {
		if(!player->Update() || needsToClose) {
			[self close];
		}
	}
}



- (void)close
{
	[self destroyPlayer];
	[super close];
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
