
scene = PhysicsScene2D(0.1, 60)

checkShape = ScenePrimitive(ScenePrimitive.TYPE_VPLANE, 0.2,0.03)
scene:addCollisionChild(checkShape, PhysicsScene2DEntity.ENTITY_RECT)

for i=0,50 do
	shape = ScenePrimitive(ScenePrimitive.TYPE_VPLANE, 0.1,0.02)
	shape:setRoll(random(360))
	shape:setPosition(-0.5 + random(), -0.5 + random())
	scene:addCollisionChild(shape, PhysicsScene2DEntity.ENTITY_RECT)
end

function onNewCollision(t, event)
	physicsEvent = safe_cast(event, PhysicsScene2DEvent)
	if physicsEvent.entity1 == checkShape then
		physicsEvent:getFirstEntity():setColor(1.0, 0.0, 0.0, 1.0)
		physicsEvent:getSecondEntity():setColor(1.0, 0.0, 0.0, 1.0)
	end
end

function onEndCollision(t, event)
	physicsEvent = safe_cast(event, PhysicsScene2DEvent)
	physicsEvent:getFirstEntity():setColor(1.0, 1.0, 1.0, 1.0)
	physicsEvent:getSecondEntity():setColor(1.0, 1.0, 1.0, 1.0)
end

scene:addEventListener(nil, onNewCollision, PhysicsScene2DEvent.EVENT_NEW_SHAPE_COLLISION)
scene:addEventListener(nil, onEndCollision, PhysicsScene2DEvent.EVENT_END_SHAPE_COLLISION)

function onMouseMove(x,y)
	local ray = scene:projectRayFromCameraAndViewportCoordinate(scene:getActiveCamera(), Vector2(x,y))
    checkShape:setPosition(ray.origin.x, ray.origin.y)

end

function Update(e)
	checkShape:setRoll(checkShape:getRoll() + (e*100))
end
