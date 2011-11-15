Services.ResourceManager:addDirResource("Resources", false)

scene = Scene()
ground = ScenePrimitive(TYPE_PLANE, 5,5)
ground:setMaterialByName("GroundMaterial")
scene:addEntity(ground)

box =  ScenePrimitive(TYPE_TORUS, 0.8,0.3,30,20)
box:setMaterialByName("CubeMaterial")
box:setPosition(0.0, 0.5, 0.0)
scene:addEntity(box)

light = SceneLight(AREA_LIGHT, scene, 6)
light:setPosition(1,2,1)
scene:addLight(light)

scene:getDefaultCamera():setPosition(7,7,7)
scene:getDefaultCamera():lookAt(Vector3(0,0,0), Vector3(0,1,0))
