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

#import "PolycodeView.h"


@implementation PolycodeView

@synthesize viewReady;
@synthesize mouseX;
@synthesize mouseY;

- (id)initWithFrame:(NSRect)frameRect pixelFormat:(NSOpenGLPixelFormat *)format 
{
	self = [super initWithFrame:frameRect pixelFormat:format];
	if(self) {
		glSizeX = 0;
		glSizeY = 0;		
		viewReady = NO;
		currentCursor = NULL;
		contextLock = [[NSLock alloc] init];
	}
	return self;
}

- (void) awakeFromNib {
	contextLock = [[NSLock alloc] init];
	
	[[self window] setAcceptsMouseMovedEvents:YES];
	[[self window] makeFirstResponder:self];	

	[[NSNotificationCenter defaultCenter] addObserver:self  selector:@selector(windowResized:) name:NSWindowDidResizeNotification object:[self window]];
	
	[self setAutoresizesSubviews: YES];
}

-(void) viewDidMoveToWindow
{
	[super viewDidMoveToWindow];
	
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(windowDidResignMain:) name:NSWindowDidResignKeyNotification object:[self window]];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(windowDidResignMain:) name:NSWindowDidResignMainNotification object:[self window]];


	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(windowDidBecomeMain:) name:NSWindowDidBecomeKeyNotification object:[self window]];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(windowDidBecomeMain:) name:NSWindowDidBecomeMainNotification object:[self window]];

	
	viewReady = YES;
}

- (void)windowDidResignMain:(NSNotification *)notification
{	
	if(core == NULL)
		return;	
	
	core->lockMutex(core->eventMutex);	
	CocoaEvent newEvent;
	newEvent.eventGroup = CocoaEvent::FOCUS_EVENT;
	newEvent.eventCode = Core::EVENT_LOST_FOCUS;	
	core->cocoaEvents.push_back(newEvent);	
	core->unlockMutex(core->eventMutex);		
}

- (void)windowDidBecomeMain:(NSNotification *)notification
{	
	if(core == NULL)
		return;
	
	core->lockMutex(core->eventMutex);	
	CocoaEvent newEvent;
	newEvent.eventGroup = CocoaEvent::FOCUS_EVENT;
	newEvent.eventCode = Core::EVENT_GAINED_FOCUS;	
	core->cocoaEvents.push_back(newEvent);	
	core->unlockMutex(core->eventMutex);		
}


- (void) initKeymap {	 
	
	keymap[0x00] = KEY_a;
	keymap[0x01] = KEY_s;
	keymap[0x02] = KEY_d;
	keymap[0x03] = KEY_f;
	keymap[0x05] = KEY_g;
	keymap[0x04] = KEY_h;
	keymap[0x06] = KEY_z;
	keymap[0x07] = KEY_x;
	keymap[0x08] = KEY_c;
	keymap[0x09] = KEY_v;
	keymap[0x0B] = KEY_b;
	keymap[0x0C] = KEY_q;
	keymap[0x0D] = KEY_w;
	keymap[0x0E] = KEY_e;
	keymap[0x0F] = KEY_r;
	keymap[0x10] = KEY_y;
	keymap[0x11] = KEY_t;
	keymap[0x12] = KEY_1;
	keymap[0x13] = KEY_2;
	keymap[0x14] = KEY_3;
	keymap[0x15] = KEY_4;
	keymap[0x16] = KEY_6;
	keymap[0x17] = KEY_5;
	keymap[0x18] = KEY_EQUALS;
	keymap[0x19] = KEY_9;
	keymap[0x1A] = KEY_7;
	keymap[0x1B] = KEY_MINUS;
	keymap[0x1C] = KEY_8;
	keymap[0x1D] = KEY_0;
	keymap[0x1E] = KEY_RIGHTBRACKET;
	keymap[0x1F] = KEY_o;
	keymap[0x20] = KEY_u;
	keymap[0x21] = KEY_LEFTBRACKET;
	keymap[0x22] = KEY_i;
	keymap[0x23] = KEY_p;
	keymap[0x25] = KEY_l;
	keymap[0x26] = KEY_j;
	keymap[0x27] = KEY_QUOTE;
	keymap[0x28] = KEY_k;
	keymap[0x29] = KEY_SEMICOLON;
	keymap[0x2A] = KEY_BACKSLASH;
	keymap[0x2B] = KEY_COMMA;
	keymap[0x2C] = KEY_SLASH;
	keymap[0x2D] = KEY_n;
	keymap[0x2E] = KEY_m;
	keymap[0x2F] = KEY_PERIOD;
	//	keymap[0x32] = KEY_GRAVE;
	keymap[0x41] = KEY_KP_PERIOD;
	keymap[0x43] = KEY_KP_MULTIPLY;
	keymap[0x45] = KEY_KP_PLUS;
	//	keymap[0x47] = KEY_KeypadClear;
	keymap[0x4B] = KEY_KP_DIVIDE;
	keymap[0x4C] = KEY_KP_ENTER;
	keymap[0x4E] = KEY_KP_MINUS;
	keymap[0x51] = KEY_KP_EQUALS;
	keymap[0x52] = KEY_KP0;
	keymap[0x53] = KEY_KP1;
	keymap[0x54] = KEY_KP2;
	keymap[0x55] = KEY_KP3;
	keymap[0x56] = KEY_KP4;
	keymap[0x57] = KEY_KP5;
	keymap[0x58] = KEY_KP6;
	keymap[0x59] = KEY_KP7;
	keymap[0x5B] = KEY_KP8;
	keymap[0x5C] = KEY_KP9;
	keymap[0x24] = KEY_RETURN;
	keymap[0x30] = KEY_TAB;
	keymap[0x31] = KEY_SPACE;
	keymap[0x33] = KEY_BACKSPACE;
	keymap[0x35] = KEY_ESCAPE;
	keymap[0x37] = KEY_LSUPER;
	keymap[0x36] = KEY_RSUPER;
	keymap[0x38] = KEY_LSHIFT;
	keymap[0x39] = KEY_CAPSLOCK;
	keymap[0x3A] = KEY_LALT;
	keymap[0x3D] = KEY_RALT;	
	keymap[0x3B] = KEY_LCTRL;
	keymap[0x3C] = KEY_RSHIFT;
	keymap[0x3E] = KEY_RCTRL;
	keymap[0x3F] = KEY_COMPOSE;
	//	keymap[0x40] = KEY_F17;
	//	keymap[0x48] = KEY_VolumeUp;
	//	keymap[0x49] = KEY_VolumeDown;
	//	keymap[0x4A] = KEY_Mute;
	//	keymap[0x4F] = KEY_F18;
	//	keymap[0x50] = KEY_F19;
	//	keymap[0x5A] = KEY_F20;
	keymap[0x60] = KEY_F5;
	keymap[0x61] = KEY_F6;
	keymap[0x62] = KEY_F7;
	keymap[0x63] = KEY_F3;
	keymap[0x64] = KEY_F8;
	keymap[0x65] = KEY_F9;
	keymap[0x67] = KEY_F11;
	keymap[0x69] = KEY_F13;
	//	keymap[0x6A] = KEY_F16;
	keymap[0x6B] = KEY_F14;
	keymap[0x6D] = KEY_F10;
	keymap[0x6F] = KEY_F12;
	keymap[0x71] = KEY_F15;
	keymap[0x72] = KEY_HELP;
	keymap[0x73] = KEY_HOME;
	keymap[0x74] = KEY_PAGEUP;
	keymap[0x75] = KEY_DELETE;
	keymap[0x76] = KEY_F4;
	keymap[0x77] = KEY_END;
	keymap[0x78] = KEY_F2;
	keymap[0x79] = KEY_PAGEDOWN;
	keymap[0x7A] = KEY_F1;
	keymap[0x7B] = KEY_LEFT;
	keymap[0x7C] = KEY_RIGHT;
	keymap[0x7D] = KEY_DOWN;
	keymap[0x7E] = KEY_UP;
	//	keymap[0x0A] = KEY_ISO_Section;
	//	keymap[0x5D] = KEY_JIS_Yen;
	//	keymap[0x5E] = KEY_JIS_Underscore;
	//	keymap[0x5F] = KEY_JIS_KeypadComma;
	//	keymap[0x66] = KEY_JIS_Eisu;
	//	keymap[0x68] = KEY_JIS_Kana;	
}

-(void) setCurrentCursor: (NSCursor*) newCursor
{
	currentCursor = newCursor;
}

- (void)resetCursorRects
{
	if(currentCursor)
		[self addCursorRect:[self bounds] cursor:currentCursor];
}

- (void) setCore: (CocoaCore*) newCore {
	[self initKeymap];	
	core = newCore;
}

- (BOOL) lockFocusIfCanDraw {
	[contextLock lock];
	BOOL retVal = [super lockFocusIfCanDraw];
	[contextLock unlock];
	return retVal;
}

- (void) update {
	[contextLock lock];
	[super update];
	[contextLock unlock];	
}

- (void) lockContext {
	[contextLock lock];	
}

- (void) unlockContext {
	[contextLock unlock];	
}

- (void)prepareOpenGL {
	contextReady = YES;
}

- (BOOL) isContextReady {
	return contextReady;
}

- (void)setOpenGLContext:(NSOpenGLContext *)context {
	contextReady = NO;
	[super setOpenGLContext:context];
}

- (BOOL)acceptsFirstResponder
{
	return YES;
}

// ---------------------------------

- (BOOL)becomeFirstResponder
{
	return  YES;
}

// ---------------------------------

- (BOOL)resignFirstResponder
{
	return YES;
}

- (BOOL)acceptsFirstMouse:(NSEvent *)theEvent
{
	return YES;
}

- (BOOL)mouseDownCanMoveWindow
{
	return NO;
}

- (void) drawRect:(NSRect)rect {
	if(glSizeX != (int)[self frame].size.width || glSizeY != (int)[self frame].size.height) {
		glSizeX = (int)[self frame].size.width;
		glSizeY = (int)[self frame].size.height;		
		
		if(core != NULL) {
			core->resizeTo(glSizeX, glSizeY);
		}
		
	}
}

-(void) windowResized: (NSNotification *) notification {
}

-(void) dealloc {
	[[NSNotificationCenter defaultCenter] removeObserver:self];
	[super dealloc];
	 
}	

- (void) resizeWithOldSuperviewSize: (NSSize) oldSize {	
	[super resizeWithOldSuperviewSize: oldSize];
//	if(core == NULL)
//		return;	
//	core->setVideoMode(oldSize.width, oldSize.height, core->isFullscreen(), core->getAALevel());	
}

// INPUT

- (void) otherMouseDown:(NSEvent *) event
{
	if(core == NULL)
		return;
	
	core->lockMutex(core->eventMutex);	
	NSPoint mouseLoc = [self convertPoint:[event locationInWindow] fromView:self];	
	CocoaEvent newEvent;
	newEvent.eventGroup = CocoaEvent::INPUT_EVENT;
	newEvent.eventCode = InputEvent::EVENT_MOUSEDOWN;
	newEvent.mouseButton = CoreInput::MOUSE_BUTTON3;
	newEvent.mouseX = mouseLoc.x;
	newEvent.mouseY = core->getYRes() - mouseLoc.y;
	core->cocoaEvents.push_back(newEvent);	
	core->unlockMutex(core->eventMutex);		
}

- (void) otherMouseUp:(NSEvent *) event
{
	if(core == NULL)
		return;
	
	core->lockMutex(core->eventMutex);	
	NSPoint mouseLoc = [self convertPoint:[event locationInWindow] fromView:self];	
	CocoaEvent newEvent;
	newEvent.eventGroup = CocoaEvent::INPUT_EVENT;
	newEvent.eventCode = InputEvent::EVENT_MOUSEUP;
	newEvent.mouseButton = CoreInput::MOUSE_BUTTON3;	
	newEvent.mouseX = mouseLoc.x;
	newEvent.mouseY = core->getYRes() - mouseLoc.y;
	core->cocoaEvents.push_back(newEvent);	
	core->unlockMutex(core->eventMutex);		
}


- (void) rightMouseDown:(NSEvent *) event
{
	if(core == NULL)
		return;
	
	core->lockMutex(core->eventMutex);	
	NSPoint mouseLoc = [self convertPoint:[event locationInWindow] fromView:self];	
	CocoaEvent newEvent;
	newEvent.eventGroup = CocoaEvent::INPUT_EVENT;
	newEvent.eventCode = InputEvent::EVENT_MOUSEDOWN;
	newEvent.mouseButton = CoreInput::MOUSE_BUTTON2;
	newEvent.mouseX = mouseLoc.x;
	newEvent.mouseY = core->getYRes() - mouseLoc.y;
	core->cocoaEvents.push_back(newEvent);	
	core->unlockMutex(core->eventMutex);		
}

- (void) rightMouseUp:(NSEvent *) event
{
	if(core == NULL)
		return;
	
	core->lockMutex(core->eventMutex);	
	NSPoint mouseLoc = [self convertPoint:[event locationInWindow] fromView:self];	
	CocoaEvent newEvent;
	newEvent.eventGroup = CocoaEvent::INPUT_EVENT;
	newEvent.eventCode = InputEvent::EVENT_MOUSEUP;
	newEvent.mouseButton = CoreInput::MOUSE_BUTTON2;	
	newEvent.mouseX = mouseLoc.x;
	newEvent.mouseY = core->getYRes() - mouseLoc.y;
	core->cocoaEvents.push_back(newEvent);	
	core->unlockMutex(core->eventMutex);		
}

- (void)scrollWheel:(NSEvent*) event {
	
	if(core == NULL || [event deltaY] == 0)
		return;
	
	core->lockMutex(core->eventMutex);	
	NSPoint mouseLoc = [self convertPoint:[event locationInWindow] fromView:self];	
	CocoaEvent newEvent;
	newEvent.eventGroup = CocoaEvent::INPUT_EVENT;
	
	if([event deltaY] > 0)
		newEvent.eventCode = InputEvent::EVENT_MOUSEWHEEL_UP;
	else
		newEvent.eventCode = InputEvent::EVENT_MOUSEWHEEL_DOWN;
	newEvent.mouseX = mouseLoc.x;
	newEvent.mouseY = core->getYRes() - mouseLoc.y;
	core->cocoaEvents.push_back(newEvent);	
	core->unlockMutex(core->eventMutex);	
	
}

- (void) mouseDown:(NSEvent *) event
{
	
	if(core == NULL)
		return;
	
	core->lockMutex(core->eventMutex);	
	NSPoint mouseLoc = [self convertPoint:[event locationInWindow] fromView:self];	
	CocoaEvent newEvent;
	newEvent.eventGroup = CocoaEvent::INPUT_EVENT;
	newEvent.eventCode = InputEvent::EVENT_MOUSEDOWN;
	newEvent.mouseButton = CoreInput::MOUSE_BUTTON1;
	newEvent.mouseX = mouseLoc.x;
	newEvent.mouseY = core->getYRes() - mouseLoc.y;
	
	mouseX = mouseLoc.x;
	mouseY = mouseLoc.y;
	
	
	core->cocoaEvents.push_back(newEvent);	
	core->unlockMutex(core->eventMutex);	
}

- (void) mouseUp:(NSEvent *) event
{
	if(core == NULL)
		return;
	
	core->lockMutex(core->eventMutex);	
	NSPoint mouseLoc = [self convertPoint:[event locationInWindow] fromView:self];	
	CocoaEvent newEvent;
	newEvent.eventGroup = CocoaEvent::INPUT_EVENT;
	newEvent.eventCode = InputEvent::EVENT_MOUSEUP;
	newEvent.mouseButton = CoreInput::MOUSE_BUTTON1;	
	newEvent.mouseX = mouseLoc.x;
	newEvent.mouseY = core->getYRes() - mouseLoc.y;
	
	mouseX = mouseLoc.x;
	mouseY = mouseLoc.y;
	
	
	core->cocoaEvents.push_back(newEvent);	
	core->unlockMutex(core->eventMutex);	
}

- (void)flagsChanged:(NSEvent *)theEvent
{
	if(core == NULL)
		return;
	
	if([theEvent keyCode] == 0) {
		return;
	}
	core->lockMutex(core->eventMutex);	
	CocoaEvent newEvent;	
	newEvent.eventGroup = CocoaEvent::INPUT_EVENT;
	newEvent.keyCode = keymap[[theEvent keyCode]];	
	
	switch(newEvent.keyCode) {
		case Polycode::KEY_LALT:
			if (([theEvent modifierFlags] & 0x80120) == 0x80120) {
				newEvent.eventCode = InputEvent::EVENT_KEYDOWN;
			} else {
				newEvent.eventCode = InputEvent::EVENT_KEYUP;			
			}
		break;
		case Polycode::KEY_RALT:
			if (([theEvent modifierFlags] & 0x80140) == 0x80140) {
				newEvent.eventCode = InputEvent::EVENT_KEYDOWN;
			} else {
				newEvent.eventCode = InputEvent::EVENT_KEYUP;			
			}
		break;
		case Polycode::KEY_LSHIFT:
			if (([theEvent modifierFlags] & 0x20102) == 0x20102) {
				newEvent.eventCode = InputEvent::EVENT_KEYDOWN;
			} else {
				newEvent.eventCode = InputEvent::EVENT_KEYUP;			
			}
		break;		
		case Polycode::KEY_RSHIFT:
			if (([theEvent modifierFlags] & 0x20104) == 0x20104) {
				newEvent.eventCode = InputEvent::EVENT_KEYDOWN;
			} else {
				newEvent.eventCode = InputEvent::EVENT_KEYUP;			
			}
		break;		
		case Polycode::KEY_LCTRL:
			if (([theEvent modifierFlags] & 0x40101) == 0x40101) {
				newEvent.eventCode = InputEvent::EVENT_KEYDOWN;
			} else {
				newEvent.eventCode = InputEvent::EVENT_KEYUP;			
			}
		break;		
		case Polycode::KEY_RCTRL:
			// no right control on my mac :)
		break;
		case Polycode::KEY_LSUPER:
			if (([theEvent modifierFlags] & 0x100108) == 0x100108) {
				newEvent.eventCode = InputEvent::EVENT_KEYDOWN;
			} else {
				newEvent.eventCode = InputEvent::EVENT_KEYUP;			
			}
		break;
		case Polycode::KEY_RSUPER:
			if (([theEvent modifierFlags] & 0x100110) == 0x100110) {
				newEvent.eventCode = InputEvent::EVENT_KEYDOWN;
			} else {
				newEvent.eventCode = InputEvent::EVENT_KEYUP;			
			}		
		break;
		default:
			// Don't care otherwise
			break;
	}
	newEvent.unicodeChar = 0;
	
	
	core->cocoaEvents.push_back(newEvent);	
	core->unlockMutex(core->eventMutex);	

}

- (void)keyDown: (NSEvent*) theEvent
{
	if(core == NULL)
		return;
	
	core->lockMutex(core->eventMutex);	
	CocoaEvent newEvent;
	newEvent.eventGroup = CocoaEvent::INPUT_EVENT;
	newEvent.eventCode = InputEvent::EVENT_KEYDOWN;
	newEvent.keyCode = keymap[[theEvent keyCode]];	
	
	NSString *chars = [theEvent characters];
	NSUInteger numChars = [chars length];
	
//	NSLog(@"CHARS: %@", [chars characterAtIndex:0]);
	if(numChars > 0) {
		newEvent.unicodeChar = [chars characterAtIndex:0];
	} else {
		newEvent.unicodeChar = 0;
	}
	
	core->cocoaEvents.push_back(newEvent);	
	core->unlockMutex(core->eventMutex);	
	
}

- (void)keyUp: (NSEvent*) theEvent
{
	if(core == NULL)
		return;
	
	core->lockMutex(core->eventMutex);	
	CocoaEvent newEvent;
	newEvent.eventGroup = CocoaEvent::INPUT_EVENT;
	newEvent.eventCode = InputEvent::EVENT_KEYUP;
	newEvent.keyCode = keymap[[theEvent keyCode]];
	
	NSString *chars = [theEvent characters];
	NSUInteger numChars = [chars length];
	
	if(numChars > 0)
		newEvent.unicodeChar = [chars characterAtIndex:0];
	else
		newEvent.unicodeChar = 0;
	
	core->cocoaEvents.push_back(newEvent);	
	core->unlockMutex(core->eventMutex);		
}

- (void)mouseDragged:(NSEvent *)theEvent
{
	if(core == NULL)
		return;
	
	core->lockMutex(core->eventMutex);	
	NSPoint mouseLoc = [self convertPoint:[theEvent locationInWindow] fromView:self];	
	CocoaEvent newEvent;
	newEvent.eventGroup = CocoaEvent::INPUT_EVENT;
	newEvent.eventCode = InputEvent::EVENT_MOUSEMOVE;
	newEvent.mouseX = mouseLoc.x;
	newEvent.mouseY = core->getYRes() - mouseLoc.y;
	core->cocoaEvents.push_back(newEvent);	
	core->unlockMutex(core->eventMutex);
}


- (void)mouseMoved:(NSEvent *)theEvent
{
	if(core == NULL)
		return;
	
	core->lockMutex(core->eventMutex);	
	NSPoint mouseLoc = [self convertPoint:[theEvent locationInWindow] fromView:self];	
	CocoaEvent newEvent;
	newEvent.eventGroup = CocoaEvent::INPUT_EVENT;
	newEvent.eventCode = InputEvent::EVENT_MOUSEMOVE;
	newEvent.mouseX = mouseLoc.x;
	newEvent.mouseY = core->getYRes() - mouseLoc.y;
	
	mouseX = mouseLoc.x;
	mouseY = mouseLoc.y;
	
	core->cocoaEvents.push_back(newEvent);	
	core->unlockMutex(core->eventMutex);
}


@end
