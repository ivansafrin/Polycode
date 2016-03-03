//
//  ViewController.m
//  TemplateApp
//
//  Created by Ivan Safrin on 11/12/15.
//  Copyright © 2015 Polycode. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    app = new PolycodeTemplateApp(_mainView);
    timer = [NSTimer timerWithTimeInterval:(1.0f/60.0f)
                                    target:self
                                  selector:@selector(animationTimer:)
                                  userInfo:nil
                                   repeats:YES];
    [[NSRunLoop currentRunLoop] addTimer:timer forMode:NSDefaultRunLoopMode];
    [_mainView setNeedsDisplay];
}

- (void)animationTimer:(NSTimer *)timer
{
    if(!app->Update()) {
        //       [[NSApplication sharedApplication] stop:self];
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
