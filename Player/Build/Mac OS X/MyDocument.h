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
				//				[playerDocument handleDebugError: [NSString stringWithCString:debugEvent->errorString.c_str()] onLine: debugEvent->lineNumber];
				break;
			case PolycodeDebugEvent::EVENT_PRINT:
				//				[playerDocument printToConsole: [NSString stringWithCString:debugEvent->errorString.c_str()]];				
				break;
			case PolycodeDebugEvent::EVENT_RESIZE:
//				printf("RERERERERESIZE\n");
//				[playerDocument resizeDocument: debugEvent->xRes withYRes: debugEvent->yRes];
				break;				
		}
	}
	
	id playerDocument;	
};

@interface MyDocument : NSDocument
{
	PolycodeView *mainView;
	NSString *docFileName;	
	NSTimer* timer;
	CocoaPolycodePlayer *player;
	PolycodeProxy *playerProxy;
}

@property (assign) IBOutlet PolycodeView *mainView;

@end
