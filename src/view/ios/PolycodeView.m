
#import "polycode/view/ios/PolycodeView.h"

@interface PolycodeView ()
{
    BOOL _needsUpdate;
}
@end

@implementation PolycodeView

// Must return the CAEAGLLayer class so that CA allocates an EAGLLayer backing for this view
+ (Class) layerClass
{
    return [CAEAGLLayer class];
}

- (instancetype) initWithCoder:(NSCoder*)coder
{
    if ((self = [super initWithCoder:coder]))
    {
        _needsUpdate = NO;
        CADisplayLink *displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(drawView:)];
        [displayLink addToRunLoop:[NSRunLoop mainRunLoop] forMode:NSDefaultRunLoopMode];
    }
    
    return self;
}

- (BOOL) needsUpdate
{
    return _needsUpdate;
}

- (void) drawView:(id)sender {
    _needsUpdate = YES;

}

@end
