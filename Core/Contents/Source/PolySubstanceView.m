//
//  SubstanceView.m
//  Substance
//
//  Created by Ivan Safrin on 2/21/10.
//  Copyright 2010 Ivan Safrin. All rights reserved.
//

#import "PolySubstanceView.h"


@implementation SubstanceView

@synthesize viewReady;

- (id)initWithFrame:(NSRect)frameRect pixelFormat:(NSOpenGLPixelFormat *)format 
{
	self = [super initWithFrame:frameRect pixelFormat:format];
	if(self) {
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
	viewReady = YES;
	NSLog(@"VIEW READY!");	
}


- (void) initKeymap {	 
	
	for(int i=0; i < 512; i++) {
		modifierMap[i] = 0;	
	}
	
	keymap[0x00] = TAUK_a;
	keymap[0x01] = TAUK_s;
	keymap[0x02] = TAUK_d;
	keymap[0x03] = TAUK_f;
	keymap[0x04] = TAUK_g;
	keymap[0x05] = TAUK_h;
	keymap[0x06] = TAUK_z;
	keymap[0x07] = TAUK_x;
	keymap[0x08] = TAUK_c;
	keymap[0x09] = TAUK_v;
	keymap[0x0B] = TAUK_b;
	keymap[0x0C] = TAUK_q;
	keymap[0x0D] = TAUK_w;
	keymap[0x0E] = TAUK_e;
	keymap[0x0F] = TAUK_r;
	keymap[0x10] = TAUK_y;
	keymap[0x11] = TAUK_t;
	keymap[0x12] = TAUK_1;
	keymap[0x13] = TAUK_2;
	keymap[0x14] = TAUK_3;
	keymap[0x15] = TAUK_4;
	keymap[0x16] = TAUK_6;
	keymap[0x17] = TAUK_5;
	keymap[0x18] = TAUK_EQUALS;
	keymap[0x19] = TAUK_9;
	keymap[0x1A] = TAUK_7;
	keymap[0x1B] = TAUK_MINUS;
	keymap[0x1C] = TAUK_8;
	keymap[0x1D] = TAUK_0;
	keymap[0x1E] = TAUK_RIGHTBRACKET;
	keymap[0x1F] = TAUK_o;
	keymap[0x20] = TAUK_u;
	keymap[0x21] = TAUK_LEFTBRACKET;
	keymap[0x22] = TAUK_i;
	keymap[0x23] = TAUK_p;
	keymap[0x25] = TAUK_l;
	keymap[0x26] = TAUK_j;
	keymap[0x27] = TAUK_QUOTE;
	keymap[0x28] = TAUK_k;
	keymap[0x29] = TAUK_SEMICOLON;
	keymap[0x2A] = TAUK_BACKSLASH;
	keymap[0x2B] = TAUK_COMMA;
	keymap[0x2C] = TAUK_SLASH;
	keymap[0x2D] = TAUK_n;
	keymap[0x2E] = TAUK_m;
	keymap[0x2F] = TAUK_PERIOD;
	//	keymap[0x32] = TAUK_GRAVE;
	keymap[0x41] = TAUK_KP_PERIOD;
	keymap[0x43] = TAUK_KP_MULTIPLY;
	keymap[0x45] = TAUK_KP_PLUS;
	//	keymap[0x47] = TAUK_KeypadClear;
	keymap[0x4B] = TAUK_KP_DIVIDE;
	keymap[0x4C] = TAUK_KP_ENTER;
	keymap[0x4E] = TAUK_KP_MINUS;
	keymap[0x51] = TAUK_KP_EQUALS;
	keymap[0x52] = TAUK_KP0;
	keymap[0x53] = TAUK_KP1;
	keymap[0x54] = TAUK_KP2;
	keymap[0x55] = TAUK_KP3;
	keymap[0x56] = TAUK_KP4;
	keymap[0x57] = TAUK_KP5;
	keymap[0x58] = TAUK_KP6;
	keymap[0x59] = TAUK_KP7;
	keymap[0x5B] = TAUK_KP8;
	keymap[0x5C] = TAUK_KP9;
	keymap[0x24] = TAUK_RETURN;
	keymap[0x30] = TAUK_TAB;
	keymap[0x31] = TAUK_SPACE;
	keymap[0x33] = TAUK_BACKSPACE;
	keymap[0x35] = TAUK_ESCAPE;
	keymap[0x37] = TAUK_LSUPER;
	keymap[0x36] = TAUK_RSUPER;
	keymap[0x38] = TAUK_LSHIFT;
	keymap[0x39] = TAUK_CAPSLOCK;
	keymap[0x3A] = TAUK_LALT;
	keymap[0x3D] = TAUK_RALT;	
	keymap[0x3B] = TAUK_LCTRL;
	keymap[0x3C] = TAUK_RSHIFT;
	keymap[0x3E] = TAUK_RCTRL;
	keymap[0x3F] = TAUK_COMPOSE;
	//	keymap[0x40] = TAUK_F17;
	//	keymap[0x48] = TAUK_VolumeUp;
	//	keymap[0x49] = TAUK_VolumeDown;
	//	keymap[0x4A] = TAUK_Mute;
	//	keymap[0x4F] = TAUK_F18;
	//	keymap[0x50] = TAUK_F19;
	//	keymap[0x5A] = TAUK_F20;
	keymap[0x60] = TAUK_F5;
	keymap[0x61] = TAUK_F6;
	keymap[0x62] = TAUK_F7;
	keymap[0x63] = TAUK_F3;
	keymap[0x64] = TAUK_F8;
	keymap[0x65] = TAUK_F9;
	keymap[0x67] = TAUK_F11;
	keymap[0x69] = TAUK_F13;
	//	keymap[0x6A] = TAUK_F16;
	keymap[0x6B] = TAUK_F14;
	keymap[0x6D] = TAUK_F10;
	keymap[0x6F] = TAUK_F12;
	keymap[0x71] = TAUK_F15;
	keymap[0x72] = TAUK_HELP;
	keymap[0x73] = TAUK_HOME;
	keymap[0x74] = TAUK_PAGEUP;
	keymap[0x75] = TAUK_DELETE;
	keymap[0x76] = TAUK_F4;
	keymap[0x77] = TAUK_END;
	keymap[0x78] = TAUK_F2;
	keymap[0x79] = TAUK_PAGEDOWN;
	keymap[0x7A] = TAUK_F1;
	keymap[0x7B] = TAUK_LEFT;
	keymap[0x7C] = TAUK_RIGHT;
	keymap[0x7D] = TAUK_DOWN;
	keymap[0x7E] = TAUK_UP;
	//	keymap[0x0A] = TAUK_ISO_Section;
	//	keymap[0x5D] = TAUK_JIS_Yen;
	//	keymap[0x5E] = TAUK_JIS_Underscore;
	//	keymap[0x5F] = TAUK_JIS_KeypadComma;
	//	keymap[0x66] = TAUK_JIS_Eisu;
	//	keymap[0x68] = TAUK_JIS_Kana;	
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
	
}

-(void) windowResized: (NSNotification *) notification {
	NSSize size = [self frame].size;
	if(core == NULL)
			return;	
	core->resizeTo(size.width, size.height);
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
	core->cocoaEvents.push_back(newEvent);	
	core->unlockMutex(core->eventMutex);	
}

- (void)flagsChanged:(NSEvent *)theEvent
{
	if(core == NULL)
		return;
	
//	NSLog(@"KEY: %x\n", [theEvent keyCode]);
	
	core->lockMutex(core->eventMutex);	
	CocoaEvent newEvent;	
	newEvent.eventGroup = CocoaEvent::INPUT_EVENT;
	newEvent.keyCode = keymap[[theEvent keyCode]];	
	
	if(modifierMap[[theEvent keyCode]] == 0) {
		modifierMap[[theEvent keyCode]] = 1;
		newEvent.eventCode = InputEvent::EVENT_KEYDOWN;		
	} else {
		modifierMap[[theEvent keyCode]] = 0;
		newEvent.eventCode = InputEvent::EVENT_KEYUP;				
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
	unsigned int numChars = [chars length];
	
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
	NSPoint mouseLoc = [self convertPoint:[theEvent locationInWindow] fromView:self];	
	CocoaEvent newEvent;
	newEvent.eventGroup = CocoaEvent::INPUT_EVENT;
	newEvent.eventCode = InputEvent::EVENT_KEYUP;
	newEvent.keyCode = keymap[[theEvent keyCode]];
	
	NSString *chars = [theEvent characters];
	unsigned int numChars = [chars length];
	
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
	core->cocoaEvents.push_back(newEvent);	
	core->unlockMutex(core->eventMutex);
}


@end
