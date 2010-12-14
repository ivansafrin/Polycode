//
//  MyDocument.h
//  Polycode Player
//
//  Created by Ivan Safrin on 12/13/10.
//  Copyright 2010 Local Projects. All rights reserved.
//


#import <Cocoa/Cocoa.h>
#import "PolySubstanceView.h"
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
	SubstanceView *substanceView;
	NSString *docFileName;	
	NSTimer* timer;
	CocoaPolycodePlayer *player;
	PolycodeProxy *playerProxy;
}

@property (assign) IBOutlet SubstanceView *substanceView;

@end
