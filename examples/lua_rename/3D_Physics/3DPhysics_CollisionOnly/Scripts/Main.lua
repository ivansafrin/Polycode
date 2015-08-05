scene =  CollisionScene(Vector3(2000, 2000, 2000), false, false)

ground = ScenePrimitive(ScenePrimitive.TYPE_PLANE, 10, 10)
ground:loadTexture("Resources/green_texture.png")
scene:addEntity(ground)

box = ScenePrimitive(ScenePrimitive.TYPE_BOX, 0.5, 0.5, 0.5)
box:loadTexture("Resources/pink_texture.png")
box:setPosition(0, 1, 0)
scene:addCollisionChild(box, CollisionEntity.SHAPE_BOX)

bigBox = ScenePrimitive(ScenePrimitive.TYPE_BOX, 2, 2, 2)
bigBox:loadTexture("Resources/pink_texture.png")
bigBox:setColor(0, 1, 1, 0.5)
bigBox:setPosition(0, 1, 0)
scene:addCollisionChild(bigBox, CollisionEntity.SHAPE_BOX)


scene:getDefaultCamera():setPosition(7, 7, 7)
scene:getDefaultCamera():lookAt(Vector3(0, 0, 0), Vector3(0, 1, 0))

local swingValue = 0

function Update(elapsed)
	swingValue = swingValue + elapsed
	box:setPosition(math.sin(swingValue) * 5, 1, 0)	
	
	if scene:testCollision(box, bigBox).collided then
		bigBox:setColor(1, 1, 0, 0.5)		
	else
		bigBox:setColor(0, 1, 1, 0.5)	
	end
end