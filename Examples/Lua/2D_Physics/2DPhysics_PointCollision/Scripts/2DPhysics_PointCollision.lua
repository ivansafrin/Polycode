scene = PhysicsScene2D(0.01, 50)
lastEntity = nil

for i=0,50 do
	shape = ScenePrimitive(ScenePrimitive.TYPE_VPLANE, 0.1,0.02)
	shape:setRoll(random(360))
	shape:setPosition(-0.5 + random(), -0.5 + random())
	scene:addCollisionChild(shape, PhysicsScene2DEntity.ENTITY_RECT)
end

function onMouseMove(x,y)
	if lastEntity ~= nil then lastEntity:setColor(1.0,1.0,1.0,1.0) end

	ray = scene:projectRayFromCameraAndViewportCoordinate(scene:getActiveCamera(), Vector2(x,y))

	local entity = scene:getEntityAtPosition(ray.origin.x, ray.origin.y)
	if entity ~= nil then
		entity:setColor(1.0, 0.0, 0.0, 1.0)
		lastEntity = entity
	end
end