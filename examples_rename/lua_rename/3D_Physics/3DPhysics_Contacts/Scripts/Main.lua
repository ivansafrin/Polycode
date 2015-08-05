scene = PhysicsScene(0, Vector3(200, 200, 200))

ground = ScenePrimitive(ScenePrimitive.TYPE_PLANE, 10, 10)
ground:loadTexture("Resources/green_texture.png")

scene:addPhysicsChild(ground, 6, 0)

for i = 1, 100 do
	local box = ScenePrimitive(ScenePrimitive.TYPE_BOX, 0.5,0.5,0.5)
	box:loadTexture("Resources/pink_texture.png")
	box:Roll(-45 + math.random() % 90)
	box:Pitch(-45 + math.random() % 90)		
	box:setPosition(-2 + math.random() % 4, i*0.5, -2 + math.random() % 4)

	scene:addPhysicsChild(box, 0, 1)
end

scene:getDefaultCamera():setPosition(7, 7, 7)
scene:getDefaultCamera():lookAt(Vector3(0, 0, 0), Vector3(0, 1, 0))

collisionSound = Sound("Resources/hit.wav")

function onCollisionEvent(t, event)
	local physEvent = safe_cast(event, PhysicsSceneEvent)
	if physEvent.appliedImpulse > 2 then
			collisionSound:Play()
	end
end
scene:addEventListener(nil, onCollisionEvent, PhysicsSceneEvent.COLLISION_EVENT)