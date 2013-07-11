
-- makes a sound when a collision impact stronger than 5 happens

screen = PhysicsScreen(10, 60)
shape = ScreenShape(ScreenShape.SHAPE_RECT, 600,30)
shape:setColor(0.0,0.0,0.0,1.0)
shape:setPosition(640/2, 400)
screen:addPhysicsChild(shape, PhysicsScreenEntity.ENTITY_RECT, true)

for i=0,50 do
        shape = ScreenShape(ScreenShape.SHAPE_RECT, 20,5)
        shape:setRotation(random(360))
        shape:setPosition(random(640), random(300))
        screen:addPhysicsChild(shape, PhysicsScreenEntity.ENTITY_RECT, false)
end

collisionSound = Sound("Resources/collision.wav")

function onSolveCollision(t, event)
	physicsEvent = safe_cast(event, PhysicsScreenEvent)
	if physicsEvent.impactStrength > 5 then
			collisionSound:Play()
		end
end

screen:addEventListener(test, onSolveCollision, PhysicsScreenEvent.EVENT_SOLVE_SHAPE_COLLISION)