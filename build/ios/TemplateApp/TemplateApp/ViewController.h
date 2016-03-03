//
//  ViewController.h
//  TemplateApp
//
//  Created by Ivan Safrin on 11/12/15.
//  Copyright © 2015 Polycode. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "polycode/view/ios/PolycodeView.h"
#include "PolycodeTemplateApp.h"
#import <GLKit/GLKit.h>

@interface ViewController : UIViewController {
@private
    PolycodeView *_mainView;
    PolycodeTemplateApp *app;
    NSTimer *timer;
}

@property (strong, nonatomic) IBOutlet PolycodeView *mainView;

@end

