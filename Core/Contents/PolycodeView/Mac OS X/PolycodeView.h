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


#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#include <OpenGL/gl.h>
#include <OpenGL/OpenGL.h>

#include "PolyString.h"
#include "Polycode.h"
#include "PolyCocoaCore.h"

using namespace Polycode;

@interface PolycodeView : NSOpenGLView {
	PolyKEY keymap[512];
	char mouseMap[128];
		
	CocoaCore *core;
	
	NSLock *contextLock;	
	
	NSCursor *currentCursor;
	bool contextReady;
	
	int mouseX;
	int mouseY;
	
	int glSizeX;
	int glSizeY;	
    
    BOOL viewReady;
	
}

@property BOOL viewReady;
@property int mouseX;
@property int mouseY;

- (void) setCurrentCursor: (NSCursor*) newCursor;

- (id)initWithFrame:(NSRect)frameRect pixelFormat:(NSOpenGLPixelFormat *)format;

- (void) lockContext;
- (void) unlockContext;

- (BOOL) isContextReady;

- (void) setCore: (CocoaCore*) newCore;
- (void) initKeymap;

@end
