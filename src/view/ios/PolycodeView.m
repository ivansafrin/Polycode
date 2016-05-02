
#import "polycode/view/ios/PolycodeView.h"
#import "polycode/core/PolyInputEvent.h"
#import "polycode/core/PolyIOSCore.h"

@interface PolycodeView ()
{
    BOOL _needsUpdate;
    Polycode::Core *_core;
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
    
    self.motionManager = [[CMMotionManager alloc] init];
//    self.motionManager.accelerometerUpdateInterval = .2;
//    self.motionManager.gyroUpdateInterval = .2;
    
    [self.motionManager startDeviceMotionUpdatesUsingReferenceFrame:CMAttitudeReferenceFrameXArbitraryCorrectedZVertical
                                                            toQueue: [NSOperationQueue currentQueue]
                                                        withHandler: ^(CMDeviceMotion *motion, NSError *error) {
                                                            [self handleDeviceMotion: motion];
     }];
    

    [self.motionManager startAccelerometerUpdatesToQueue:[NSOperationQueue currentQueue]
          withHandler:^(CMAccelerometerData  *accelerometerData, NSError *error) {
              [self outputAccelertionData:accelerometerData.acceleration];
              if(error){
                  NSLog(@"%@", error);
              }
          }];
    
    
    [self.motionManager startGyroUpdatesToQueue:[NSOperationQueue currentQueue]
                                    withHandler:^(CMGyroData *gyroData, NSError *error) {
                                        [self outputRotationData:gyroData.rotationRate];
    }];
    
    return self;
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    _core->eventMutex->lock();
    for (UITouch *aTouch in touches) {
        IOSEvent newEvent;
        newEvent.eventCode = InputEvent::EVENT_TOUCHES_BEGAN;
        newEvent.eventGroup = IOSEvent::INPUT_EVENT;
//        newEvent.touches = touchInfos;
//        newEvent.touch = touchInfos[index];
        ((IOSCore*)_core)->iosEvents.push_back(newEvent);
    }
    _core->eventMutex->unlock();
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
    
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
    
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
    
}

-(void)handleDeviceMotion:(CMDeviceMotion*) motion
{
    
    UIDeviceOrientation orientation = [[UIDevice currentDevice] orientation];
    
    Quaternion q;
    q.set(motion.attitude.quaternion.w, motion.attitude.quaternion.x, motion.attitude.quaternion.y, motion.attitude.quaternion.z);
    
    Quaternion rQ;
    rQ.fromAxes(-90.0, 00.0, 0.0);
    
    if(orientation == UIDeviceOrientationLandscapeRight) {
        
    } else {

    }

    
    _core->deviceAttitude = rQ * q;
}

-(void)outputAccelertionData:(CMAcceleration)acceleration
{
    ((IOSCore*)_core)->_setAcceleration(Vector3(acceleration.x, acceleration.y, acceleration.z));
}

- (void) setCore: (Polycode::Core*) newCore {
    _core = newCore;
}
-(void)outputRotationData:(CMRotationRate)rotation
{
    ((IOSCore*)_core)->_setGyroRotation(Vector3(rotation.x, rotation.y, rotation.z));
}

- (BOOL) needsUpdate
{
    return _needsUpdate;
}

- (void) drawView:(id)sender {
    _needsUpdate = YES;

}

@end
