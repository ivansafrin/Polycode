
-- Simple 2D Physics example

scene = PhysicsScene2D(0.1, 60)

-- add a static floor shape
shape = ScenePrimitive(ScenePrimitive.TYPE_VPLANE, 1.0,0.05)
shape:setColor(0.0,0.0,0.1,1.0)
shape:setPosition(0, -0.3)
scene:addPhysicsChild(shape, PhysicsScene2DEntity.ENTITY_RECT, true)


-- add 200 falling blocks
for i=0,200 do
		shape = ScenePrimitive(ScenePrimitive.TYPE_VPLANE, 0.08,0.02)
		shape:setRoll(random(360))
        shape:setColor(random(), random(), random(), 1.0)
		shape:setPosition(-0.3 + (random()*0.6), random())
		scene:addPhysicsChild(shape, PhysicsScene2DEntity.ENTITY_RECT, false)
end
