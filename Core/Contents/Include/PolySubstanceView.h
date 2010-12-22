//
//  SubstanceView.h
//  Substance
//
//  Created by Ivan Safrin on 2/21/10.
//  Copyright 2010 Ivan Safrin. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#include <OpenGL/gl.h>
#include <OpenGL/OpenGL.h>

#include "PolyString.h"
#include "Polycode.h"
#include "PolyCocoaCore.h"

using namespace Polycode;

@interface SubstanceView : NSOpenGLView {
	TAUKey keymap[512];
	char mouseMap[128];
	
	char modifierMap[512];
	
	CocoaCore *core;
	
	NSLock *contextLock;	
	
	NSCursor *currentCursor;
	bool contextReady;
	
}

@property BOOL viewReady;

- (void) setCurrentCursor: (NSCursor*) newCursor;

- (id)initWithFrame:(NSRect)frameRect pixelFormat:(NSOpenGLPixelFormat *)format;

- (void) lockContext;
- (void) unlockContext;

- (BOOL) isContextReady;

- (void) setCore: (CocoaCore*) newCore;
- (void) initKeymap;

@end
