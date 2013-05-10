
screen = PhysicsScreen(10, 60)

checkShape = ScreenShape(ScreenShape.SHAPE_RECT, 90,10)
screen:addCollisionChild(checkShape, PhysicsScreenEntity.ENTITY_RECT)

for i=0,50 do
        shape = ScreenShape(ScreenShape.SHAPE_RECT, 30,15)
        shape:setRotation(random(360))
        shape:setPosition(random(640), random(480))
        screen:addCollisionChild(shape, PhysicsScreenEntity.ENTITY_RECT)
end

function onNewCollision(t, event)
	physicsEvent = safe_cast(event, PhysicsScreenEvent)
	if physicsEvent.entity1 == checkShape then
		physicsEvent:getFirstEntity():setColor(1.0, 0.0, 0.0, 1.0)
		physicsEvent:getSecondEntity():setColor(1.0, 0.0, 0.0, 1.0)
	end
end

function onEndCollision(t, event)
	physicsEvent = safe_cast(event, PhysicsScreenEvent)
	physicsEvent:getFirstEntity():setColor(1.0, 1.0, 1.0, 1.0)
	physicsEvent:getSecondEntity():setColor(1.0, 1.0, 1.0, 1.0)
end

screen:addEventListener(nil, onNewCollision, PhysicsScreenEvent.EVENT_NEW_SHAPE_COLLISION)
screen:addEventListener(nil, onEndCollision, PhysicsScreenEvent.EVENT_END_SHAPE_COLLISION)

function onMouseMove(x,y)
	checkShape:setPosition(x,y)
end

function Update(e)
	checkShape:setRotation(checkShape:getRotation() + (e*100))
end
