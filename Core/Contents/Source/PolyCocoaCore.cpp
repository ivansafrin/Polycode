/*
 *  PolyCocoaCore.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 2/16/10.
 *  Copyright 2010 Ivan Safrin. All rights reserved.
 *
 */


#include "PolyCocoaCore.h"
#include <iostream>

using namespace Polycode;

long getThreadID() {
	return (long)pthread_self();
}

CocoaCore::CocoaCore(PolycodeView *view, int xRes, int yRes, bool fullScreen,int aaLevel, int frameRate) : Core(xRes, yRes, fullScreen,aaLevel, frameRate) {	
	eventMutex = createMutex();
	
//	NSLog(@"BUNDLE: %@", [[NSBundle mainBundle] bundlePath]);
	chdir([[[NSBundle mainBundle] bundlePath] UTF8String]);
	
	NSOpenGLPixelFormatAttribute attrs[32];
	
	int atindx = 0;
	attrs[atindx++] = NSOpenGLPFADoubleBuffer;
	
	attrs[atindx++] = NSOpenGLPFADepthSize;
	attrs[atindx++] = 32;
	
	if(aaLevel > 0) {
		attrs[atindx++] = NSOpenGLPFASampleBuffers;	
		attrs[atindx++] = 1;	
	
		attrs[atindx++] = NSOpenGLPFASamples;	
		attrs[atindx++] = aaLevel;	
	
		attrs[atindx++] = NSOpenGLPFAMultisample;	
	}
	
	attrs[atindx++] = NSOpenGLPFANoRecovery;		

	if(fullScreen) {
		
//		attrs[atindx++] = NSOpenGLPFAFullScreen;		
//		attrs[atindx++] = NSOpenGLPFAScreenMask;	
//		attrs[atindx++] = CGDisplayIDToOpenGLDisplayMask(kCGDirectMainDisplay);
		
	}
	
	attrs[atindx++] = NSOpenGLPFAAccelerated;			
	
	
	attrs[atindx++] = nil;				
/*	
	NSOpenGLPixelFormatAttribute attrs[] =
	{
			NSOpenGLPFADoubleBuffer,	
		NSOpenGLPFADepthSize, 16,
//		NSOpenGLPFAFullScreen,
//		NSOpenGLPFAScreenMask,
//		CGDisplayIDToOpenGLDisplayMask(kCGDirectMainDisplay),
		NSOpenGLPFASampleBuffers, 1,
		NSOpenGLPFASamples,  aaLevel,
		NSOpenGLPFANoRecovery,	
//		NSOpenGLPFAWindow,
		NSOpenGLPFAMultisample,
//		NSOpenGLPFAAccelerated,
//		NSOpenGLPFAAccumSize, 0,
		nil
	};	
*/

//	[view lockContext];
	
	[view setCore:this];	
	NSOpenGLPixelFormat *format = [[NSOpenGLPixelFormat alloc] initWithAttributes:attrs];
	
	if(!format) {
		NSLog(@"Error creating pixel format!\n");
	}
	
	context = [[NSOpenGLContext alloc] initWithFormat: format shareContext:nil];

	if (context == nil) {
        NSLog(@"Failed to create open gl context");
	}	
	
	if(false) {

//		[view enterFullScreenMode:[NSScreen mainScreen] withOptions:0];
//		[view removeFromSuperview];
//		[[view window] orderOut:nil];
		
//		CGDisplayCapture (kCGDirectMainDisplay ) ;			
//		CGDisplaySwitchToMode (kCGDirectMainDisplay, CGDisplayBestModeForParameters (kCGDirectMainDisplay, 32, xRes, yRes, NULL) );				
		
		
//		[context makeCurrentContext];		
//		[context setFullScreen];
//		[context flushBuffer];	
//		CGDisplayCapture (kCGDirectMainDisplay ) ;		


		
//		[context clearDrawable];
  //      [context release];		
	} else {
		[view clearGLContext];
		[view setOpenGLContext:context];	
		[context setView: view];					
	}
	
	if(fullScreen) {
	//	[view enterFullScreenMode:[NSScreen mainScreen] withOptions:0];	
	}
	
	
	glView = view;
	
	initTime = mach_absolute_time();					
	
//	while(![view isContextReady]) {
		
//	}
	
	renderer = new OpenGLRenderer();
	services->setRenderer(renderer);	
	//[view unlockContext];			
	setVideoMode(xRes,yRes,fullScreen,aaLevel);		


}

void CocoaCore::copyStringToClipboard(String str) {
	NSPasteboard *pb = [NSPasteboard generalPasteboard];
    NSArray *types = [NSArray arrayWithObjects:NSStringPboardType, nil];
    [pb declareTypes:types owner:glView];
	
	//NSString *nsstr = [NSString stringWithCharacters: (unichar*) str.c_str() length: str.length()];
	
	char* data = (char*)str.data();
	unsigned size = str.size() * sizeof(wchar_t);
	
	NSString* nsstr = [[[NSString alloc] initWithBytes:data length:size encoding:NSUTF32LittleEndianStringEncoding] autorelease];
    [pb setString: nsstr forType:NSStringPboardType];	
}

String CocoaCore::getClipboardString() {
	
}

void CocoaCore::setVideoMode(int xRes, int yRes, bool fullScreen, int aaLevel) {
	this->xRes = xRes;
	this->yRes = yRes;
	this->fullScreen = fullScreen;
	this->aaLevel = aaLevel;
	
	renderer->Resize(xRes, yRes);
//	CoreServices::getInstance()->getMaterialManager()->reloadProgramsAndTextures();	
	dispatchEvent(new Event(), EVENT_CORE_RESIZE);	

	
//	NSRect visibleFrame = [[NSScreen mainScreen] visibleFrame];	
//	NSRect frame = NSMakeRect([[glView window] frame].origin.x, [[glView window] frame].origin.y, xRes, yRes);
	
//	frame.origin.x = (visibleFrame.size.width - frame.size.width) * 0.5;
//	frame.origin.y = (visibleFrame.size.height - frame.size.height) * (9.0/10.0);
	
//	[[glView window] setFrame: frame display: YES animate: NO];
//	if(!fullScreen) {
		[[glView window] setContentSize: NSMakeSize(xRes, yRes)];
//	} else {
//		CGDisplaySwitchToMode (kCGDirectMainDisplay, CGDisplayBestModeForParameters (kCGDirectMainDisplay, 32, xRes, yRes, NULL) );						
//	}
	if(fullScreen) {	
		CGDisplaySwitchToMode (kCGDirectMainDisplay, CGDisplayBestModeForParameters (kCGDirectMainDisplay, 32, xRes, yRes, NULL) );						
		[glView enterFullScreenMode:[NSScreen mainScreen] withOptions:[NSDictionary dictionaryWithObjectsAndKeys:
																	   nil]];
		
	}
		
	/*
	if(aaLevel > 0) {
		glEnable( GL_MULTISAMPLE_ARB );	
	} else {
		glDisable( GL_MULTISAMPLE_ARB );			
	}
	*/
}

void CocoaCore::resizeTo(int xRes, int yRes) {
	this->xRes = xRes;
	this->yRes = yRes;
	renderer->Resize(xRes, yRes);	
	dispatchEvent(new Event(), EVENT_CORE_RESIZE);	
}

vector<Polycode::Rectangle> CocoaCore::getVideoModes() {
	vector<Polycode::Rectangle> retVector;
	return retVector;
}

CocoaCore::~CocoaCore() {
	
	if(fullScreen) {
		[glView exitFullScreenModeWithOptions:nil];
		
	}
	
	[glView clearGLContext];	
	[context release];
}

void *ManagedThreadFunc(void *data) {
	Threaded *target = static_cast<Threaded*>(data);
	target->runThread();
	return NULL;
}

void CocoaCore::createThread(Threaded *target) {
	pthread_t thread;
	pthread_create( &thread, NULL, ManagedThreadFunc, (void*)target);
}

void CocoaCore::lockMutex(CoreMutex *mutex) {
	PosixMutex *m = (PosixMutex*) mutex;
	pthread_mutex_lock(&m->pMutex);	
}

void CocoaCore::unlockMutex(CoreMutex *mutex) {
	PosixMutex *m = (PosixMutex*) mutex;
	pthread_mutex_unlock(&m->pMutex);
}

CoreMutex *CocoaCore::createMutex() {
	PosixMutex *mutex = new PosixMutex();	
	pthread_mutex_init(&mutex->pMutex, NULL);
	return mutex;
}

unsigned int CocoaCore::getTicks() {
	uint64_t time = mach_absolute_time();	
	double conversion = 0.0;
	
	mach_timebase_info_data_t info;
	mach_timebase_info( &info );
	conversion = 1e-9 * (double) info.numer / (double) info.denom;	
	
	return (((double)(time - initTime)) * conversion) * 1000.0f;
}

void CocoaCore::enableMouse(bool newval) {
	
	if(newval) 
		CGDisplayShowCursor(kCGDirectMainDisplay);			
	else
		CGDisplayHideCursor(kCGDirectMainDisplay);	
	Core::enableMouse(newval);
}

void CocoaCore::setCursor(int cursorType) {
	
	NSCursor *newCursor;
	
	switch(cursorType) {
		case CURSOR_TEXT:
			newCursor = [NSCursor IBeamCursor];			
		break;			
		case CURSOR_POINTER:
			newCursor = [NSCursor pointingHandCursor];						
		break;			
		case CURSOR_CROSSHAIR:
			newCursor = [NSCursor crosshairCursor];
		break;			
		case CURSOR_RESIZE_LEFT_RIGHT:
			newCursor = [NSCursor resizeLeftRightCursor];
		break;			
		case CURSOR_RESIZE_UP_DOWN:
			newCursor = [NSCursor resizeUpDownCursor];			
		break;
		default:
			newCursor = [NSCursor arrowCursor];			
		break;
	}
	[glView setCurrentCursor:newCursor];
	[glView resetCursorRects];	
	[[glView window] invalidateCursorRectsForView: glView];
}

void CocoaCore::checkEvents() {
	lockMutex(eventMutex);
	CocoaEvent event;
	for(int i=0; i < cocoaEvents.size(); i++) {
		event = cocoaEvents[i];
		switch(event.eventGroup) {
			case CocoaEvent::INPUT_EVENT:
				switch(event.eventCode) {
					case InputEvent::EVENT_MOUSEMOVE:
						input->setDeltaPosition(lastMouseX - event.mouseX, lastMouseY - event.mouseY);										
						lastMouseX = event.mouseX;
						lastMouseY = event.mouseY;
						input->setMousePosition(event.mouseX, event.mouseY, getTicks());						
						break;
					case InputEvent::EVENT_MOUSEDOWN:
						input->setMouseButtonState(event.mouseButton, true, getTicks());						
						break;
					case InputEvent::EVENT_MOUSEWHEEL_UP:
						input->mouseWheelUp(getTicks());
					break;
					case InputEvent::EVENT_MOUSEWHEEL_DOWN:
						input->mouseWheelDown(getTicks());						
					break;						
					case InputEvent::EVENT_MOUSEUP:
						input->setMouseButtonState(event.mouseButton, false, getTicks());
						break;
					case InputEvent::EVENT_KEYDOWN:
						input->setKeyState(event.keyCode, event.unicodeChar, true, getTicks());
						break;
					case InputEvent::EVENT_KEYUP:
						input->setKeyState(event.keyCode, event.unicodeChar, false, getTicks());
						break;						
				}
				break;
		}
	}
	cocoaEvents.clear();	
	unlockMutex(eventMutex);		
}

void CocoaCore::createFolder(String folderPath) {
	[[NSFileManager defaultManager] createDirectoryAtPath:[NSString stringWithUTF8String: folderPath.c_str()] withIntermediateDirectories:YES attributes:nil error:nil];
}

void CocoaCore::copyDiskItem(String itemPath, String destItemPath) {
	[[NSFileManager defaultManager] copyItemAtPath: [NSString stringWithUTF8String: itemPath.c_str()] toPath: [NSString stringWithUTF8String: destItemPath.c_str()] error: nil];	
}

void CocoaCore::moveDiskItem(String itemPath, String destItemPath) {
	[[NSFileManager defaultManager] moveItemAtPath: [NSString stringWithUTF8String: itemPath.c_str()] toPath: [NSString stringWithUTF8String: destItemPath.c_str()] error: nil];		
}

void CocoaCore::removeDiskItem(String itemPath) {
	[[NSFileManager defaultManager] removeItemAtPath: [NSString stringWithUTF8String: itemPath.c_str()] error:nil];
}
	
String CocoaCore::openFolderPicker() {
	NSOpenPanel *attachmentPanel = [NSOpenPanel openPanel];	
	[attachmentPanel setCanChooseFiles:NO];
	[attachmentPanel setCanCreateDirectories: YES];
	[attachmentPanel setCanChooseDirectories:YES];
	
	if ( [attachmentPanel runModalForDirectory:nil file:nil] == NSOKButton )
	{
		// files and directories selected.
		NSArray* files = [attachmentPanel filenames];
		NSString* fileName = [files objectAtIndex:0];
		return [fileName UTF8String];
	} else {
		return [@"" UTF8String];
	}	
}

vector<string> CocoaCore::openFilePicker(vector<CoreFileExtension> extensions, bool allowMultiple) {
	
	vector<string> retVector;
	
	NSOpenPanel *attachmentPanel = [NSOpenPanel openPanel];	
	[attachmentPanel setCanChooseFiles:YES];
	[attachmentPanel setCanCreateDirectories: YES];
	[attachmentPanel setCanChooseDirectories:NO];
	[attachmentPanel setAllowsMultipleSelection: allowMultiple];
	
	NSMutableArray *types = [[NSMutableArray alloc] init];
	
	for(int i=0; i < extensions.size(); i++) {	
		CoreFileExtension extInfo = extensions[i];
		[types addObject: [NSString stringWithUTF8String: extInfo.extension.c_str()]];
	}
	
	if ( [attachmentPanel runModalForDirectory:nil file:nil types:types] == NSOKButton )
	{
		NSArray* files = [attachmentPanel filenames];
		NSString* fileName = [files objectAtIndex:0];
		retVector.push_back([fileName UTF8String]);
	} else {
		retVector.push_back("");
	}	
	
	return retVector;
}

bool CocoaCore::Update() {
	if(!running)
		return false;
		
	lockMutex(CoreServices::getRenderMutex());	
	checkEvents();
	renderer->BeginRender();
	updateCore();
	renderer->EndRender();
	[context flushBuffer];
	unlockMutex(CoreServices::getRenderMutex());	
	doSleep();	
	return running;
}