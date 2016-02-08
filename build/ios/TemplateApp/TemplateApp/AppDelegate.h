

#import <UIKit/UIKit.h>
#import "polycode/view/ios/PolycodeView.h"
#include "PolycodeTemplateApp.h"

@interface AppDelegate : UIResponder <UIApplicationDelegate> {
    @private
    UIWindow *window;
    PolycodeView *mainView;
    PolycodeTemplateApp *app;
    NSTimer *timer;
}

@property (strong, nonatomic) UIWindow *window;
@property (strong, nonatomic) PolycodeView *mainView;


@end

