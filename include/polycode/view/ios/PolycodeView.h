
#import <UIKit/UIKit.h>
#import <CoreMotion/CoreMotion.h>
#include "polycode/core/PolyIOSCore.h"

using namespace Polycode;

@interface PolycodeView : UIView

@property (nonatomic) Polycode::Core *core;
@property (nonatomic) BOOL needsUpdate;
@property (strong, nonatomic) CMMotionManager *motionManager;

- (void) drawView:(id)sender;
- (void) setCore: (Polycode::Core*) newCore;

@end
