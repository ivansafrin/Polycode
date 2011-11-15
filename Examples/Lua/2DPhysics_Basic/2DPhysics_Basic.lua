screen = PhysicsScreen(10, 60)
shape = ScreenShape(SHAPE_RECT, 600,30)
shape:setColor(0.0,0.0,0.0,1.0)
shape:setPosition(640/2, 400)
screen:addPhysicsChild(shape, ENTITY_RECT, true)

for i=0,200 do
        shape = ScreenShape(SHAPE_RECT, 20,5)
        shape:setRotation(random(360))
        shape:setPosition(random(640), random(300))
        screen:addPhysicsChild(shape, ENTITY_RECT, false);
end
