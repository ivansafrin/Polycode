
-- Simple 2D Physics example

screen = PhysicsScreen(10, 60)

-- add a static floor shape
shape = ScreenShape(ScreenShape.SHAPE_RECT, 600,30)
shape:setColor(0.0,0.0,0.0,1.0)
shape.position.x = 640/2
shape.position.y = 400
screen:addPhysicsChild(shape, PhysicsScreenEntity.ENTITY_RECT, true)

-- add 200 falling blocks
for i=0,200 do
        shape = ScreenShape(ScreenShape.SHAPE_RECT, 20,5)
        shape:setRotation(random(360))
        shape.position.x = random(640)
		shape.position.y = random(300)
        screen:addPhysicsChild(shape, PhysicsScreenEntity.ENTITY_RECT, false);
end
