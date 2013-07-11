screen = PhysicsScreen(0.5, 60)
lastEntity = nil

for i=0,50 do
	shape = ScreenShape(ScreenShape.SHAPE_RECT, 30,15)
	shape:setRotation(random(360))
	shape:setPosition(random(640), random(480))
	screen:addCollisionChild(shape, PhysicsScreenEntity.ENTITY_RECT)
end

function onMouseMove(x,y)
	if lastEntity ~= nil then lastEntity:setColor(1.0,1.0,1.0,1.0) end
	local entity = screen:getEntityAtPosition(x,y)
	if entity ~= nil then
		entity:setColor(1.0, 0.0, 0.0, 1.0)
		lastEntity = entity
	end
end