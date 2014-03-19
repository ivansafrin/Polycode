
scene = PhysicsScene2D(0.1, 50)

ceiling = ScenePrimitive(ScenePrimitive.TYPE_VPLANE, 2.0, 0.1)
ceiling:setColor(0.0, 0.0, 0.0, 1.0)
ceiling:setPosition(0, 0.5)
scene:addPhysicsChild(ceiling, PhysicsScene2DEntity.ENTITY_RECT, true)
	
--Revolute Joint	
shape = ScenePrimitive(ScenePrimitive.TYPE_VPLANE, 0.03, 0.2)
shape:setAnchorPoint(Vector3(0.0, 1.0, 0.0))
shape:setPosition(-0.3, 0.48)
scene:addPhysicsChild(shape, PhysicsScene2DEntity.ENTITY_RECT, false)
scene:createRevoluteJoint(shape, ceiling, 0.0, 0.01)
scene:applyImpulse(shape, 10, 0)
	
--Distance Joint	
shape = ScenePrimitive(ScenePrimitive.TYPE_VPLANE, 0.1, 0.02)
shape:setPosition(0.0, 0.2)
scene:addPhysicsChild(shape, PhysicsScene2DEntity.ENTITY_RECT, false)
scene:createDistanceJoint(shape, ceiling, false)
scene:applyImpulse(shape, 2, 0)
	
line = SceneLine(shape, ceiling)
line:setColor(1.0, 0.0, 0.0, 1.0)
scene:addChild(line)

--Prismatic Joint	
shape = ScenePrimitive(ScenePrimitive.TYPE_VPLANE, 0.05, 0.1)
shape:setPosition(0.3, 0.3)
scene:addPhysicsChild(shape, PhysicsScene2DEntity.ENTITY_RECT, false)
scene:createPrismaticJoint(ceiling, shape, Vector2(0,1), 0,0, false, -0.3, 0, true)

lineAnchor = Entity()
lineAnchor:setPosition(0.3,0.5)
line = SceneLine(shape, lineAnchor)
line:setColor(0.0, 1.0, 0.0, 1.0)
scene:addChild(line)