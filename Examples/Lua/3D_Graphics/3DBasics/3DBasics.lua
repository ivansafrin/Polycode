scene = Scene()
ground = ScenePrimitive(TYPE_PLANE, 5,5)
ground:loadTexture("green_texture.png")
scene:addEntity(ground)

box =  ScenePrimitive(TYPE_BOX, 1,1,1)
box:loadTexture("pink_texture.png")
box:setPosition(0.0, 0.5, 0.0)
scene:addEntity(box)

scene:getDefaultCamera():setPosition(7,7,7)
scene:getDefaultCamera():lookAt(Vector3(0,0,0), Vector3(0,1,0))

