/*
 Copyright (C) 2015 by Ivan Safrin
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDEhD "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#import <Cocoa/Cocoa.h>
#import "PolycodeView.h"

#include "Polycode.h"
#include "polycode/ide/PolycodeIDEApp.h"

using namespace Polycode;

@class PolycodeAppDelegate;

class PolycodeAppEventHandler : public EventHandler {
    
public:
    PolycodeAppEventHandler() {}
    ~PolycodeAppEventHandler() {}
    
    void handleEvent(Event *evt);
    
    PolycodeAppDelegate* appDelegate;
};

@interface PolycodeAppDelegate : NSObject <NSApplicationDelegate> {
    NSWindow *window;
    PolycodeIDEApp *app;
    PolycodeView *polycodeView;
    PolycodeAppEventHandler *eventHandler;
    NSTimer* timer;
    
    NSMenu *projectMenu;
    
    String fileToOpen;
    BOOL mustShowProjectMenu;
}

@property (assign) IBOutlet PolycodeView *polycodeView;
@property (assign) IBOutlet NSWindow *window;
@property (assign) IBOutlet NSMenu *projectMenu;


- (void) showProjectMenu;

// Menu accessors

-(IBAction) toggleConsole: (id) sender;
-(IBAction) refreshProject: (id) sender;
-(IBAction) renameFile: (id) sender;
-(IBAction) removeFile: (id) sender;
-(IBAction) newGroup: (id) sender;
-(IBAction) browseExamples: (id) sender;
-(IBAction) runProject: (id) sender;
-(IBAction) exportProject: (id) sender;
-(IBAction) newProject: (id) sender;
-(IBAction) closeProject: (id) sender;
-(IBAction) closeFile: (id) sender;
-(IBAction) newFile: (id) sender;
-(IBAction) openProject: (id) sender;
-(IBAction) saveFile: (id) sender;
-(IBAction) findText: (id) sender;
-(IBAction) openDocs: (id) sender;
-(IBAction) showAbout: (id) sender;
-(IBAction) showSettings: (id) sender;

-(IBAction) createNewTab: (id) sender;
-(IBAction) showNextTab: (id) sender;
-(IBAction) showPreviousTab: (id) sender;
-(IBAction) closeTab: (id) sender;
@end
