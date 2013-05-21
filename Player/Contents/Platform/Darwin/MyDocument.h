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

#import <Cocoa/Cocoa.h>
#import "PolycodeView.h"
#include "PolycodeCocoaPlayer.h"

class PolycodeProxy;

@interface MyDocument : NSDocument
{
	PolycodeView *mainView;
	NSString *docFileName;
	NSTimer* timer;
	CocoaPolycodePlayer *player;
	PolycodeProxy *playerProxy;
	NSWindow *consoleWindow;
	NSTextView *consoleTextView;
	bool showingConsole;
	bool playerRunning;
	bool needsToClose;

}

- (void) printToConsole: (NSString*) message;
- (void) handleDebugError: (NSString*) error onLine:(int) lineNumber;
- (IBAction) showConsoleWindow: (id) sender;

- (void) destroyPlayer;
- (void) needToClosePlayer;

@property (assign) IBOutlet PolycodeView *mainView;
@property (assign) IBOutlet NSWindow *consoleWindow;
@property (assign) IBOutlet NSTextView *consoleTextView;

@end

class PolycodeProxy : public EventHandler {
public:
	PolycodeProxy(){ playerDocument = nil; }
	~PolycodeProxy(){}	
	
	void handleEvent(Event *event) {
		if(!playerDocument)
			return;		
		
		PolycodeDebugEvent *debugEvent = (PolycodeDebugEvent*)event;		
		switch(event->getEventCode()) {
			case PolycodeDebugEvent::EVENT_ERROR:
			{
				String fullError = "Error in file: "+debugEvent->fileName+" on line "+String::IntToString(debugEvent->lineNumber)+"\n"+debugEvent->errorString+"\n\n Backtrace:\n\n";
			
				for(int i=0; i < debugEvent->backTrace.size(); i++) {
					fullError += "In file "+debugEvent->backTrace[i].fileName + " on line " + String::IntToString(debugEvent->backTrace[i].lineNumber)+"\n";
				}
			
				[playerDocument handleDebugError: [NSString stringWithCString:fullError.c_str() encoding:NSUTF8StringEncoding] onLine: debugEvent->lineNumber];
			}
				break;
			case PolycodeDebugEvent::EVENT_PRINT:
				[playerDocument printToConsole: [NSString stringWithCString:debugEvent->errorString.c_str() encoding:NSUTF8StringEncoding]];
				break;
			case PolycodeDebugEvent::EVENT_CLOSE:
				[playerDocument needToClosePlayer];
			break;				
			case PolycodeDebugEvent::EVENT_RESIZE:
//				printf("RERERERERESIZE\n");
//				[playerDocument resizeDocument: debugEvent->xRes withYRes: debugEvent->yRes];
				break;				
		}
	}
	
	MyDocument* playerDocument;
};
