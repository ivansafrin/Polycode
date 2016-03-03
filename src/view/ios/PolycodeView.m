
#import "PolycodeView.h"

@interface PolycodeView ()
{

}
@end

@implementation PolycodeView

// Must return the CAEAGLLayer class so that CA allocates an EAGLLayer backing for this view
+ (Class) layerClass
{
    return [CAEAGLLayer class];
}

@end
