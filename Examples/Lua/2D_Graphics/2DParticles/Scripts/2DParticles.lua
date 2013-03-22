-- 2D Particle emitter example

screen = Screen()

emitter = ScreenParticleEmitter("Resources/particle.png", Particle.BILLBOARD_PARTICLE,
	ParticleEmitter.CONTINUOUS_EMITTER, 4, 200, Vector3(0.0,-50.0,0.0), Vector3(0.0,0.0,0.0),
	Vector3(20.5, 40.0, 0.0), Vector3(0.0,0.0,0.0))

emitter:getEmitter().useScaleCurves = true
emitter:getEmitter().scaleCurve:addControlPoint2d(0, 0.3)
emitter:getEmitter().scaleCurve:addControlPoint2d(0.5, 1)
emitter:getEmitter().scaleCurve:addControlPoint2d(1, 0)

emitter:getEmitter().useColorCurves = true
emitter:getEmitter().colorCurveR:addControlPoint2d(0, 0.3)
emitter:getEmitter().colorCurveR:addControlPoint2d(0.1, 1)
emitter:getEmitter().colorCurveR:addControlPoint2d(0.4, 1)
emitter:getEmitter().colorCurveR:addControlPoint2d(0.5, 0)
emitter:getEmitter().colorCurveR:addControlPoint2d(1, 0)

emitter:getEmitter().colorCurveG:addControlPoint2d(0, 0.3)
emitter:getEmitter().colorCurveG:addControlPoint2d(0.1, 0.6)
emitter:getEmitter().colorCurveG:addControlPoint2d(0.4, 0.6)
emitter:getEmitter().colorCurveG:addControlPoint2d(0.5, 0)
emitter:getEmitter().colorCurveG:addControlPoint2d(1, 0.0)

emitter:getEmitter().colorCurveB:addControlPoint2d(0, 1)
emitter:getEmitter().colorCurveB:addControlPoint2d(0.1, 0)
emitter:getEmitter().colorCurveB:addControlPoint2d(1, 0)

emitter:getEmitter().colorCurveA:addControlPoint2d(0, 0)
emitter:getEmitter().colorCurveA:addControlPoint2d(0.05, 1)
emitter:getEmitter().colorCurveA:addControlPoint2d(0.6, 1)
emitter:getEmitter().colorCurveA:addControlPoint2d(1, 0)

emitter:setPosition(640/2, 400)
screen:addChild(emitter)
