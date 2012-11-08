-- 3D lighting and materials example

Services.ResourceManager:addDirResource("Resources", false)

scene = Scene()
ground = ScenePrimitive(ScenePrimitive.TYPE_PLANE, 5,5)
ground:setMaterialByName("GroundMaterial")
scene:addEntity(ground)
scene.ambientColor:setColor(0.2, 0.2, 0.2, 1.0)

box =  ScenePrimitive(ScenePrimitive.TYPE_TORUS, 0.8,0.3,30,20)
box:setMaterialByName("CubeMaterial")
box:setPosition(0.0, 0.5, 0.0)
scene:addEntity(box)

light = SceneLight(SceneLight.AREA_LIGHT, scene, 6)
scene:addLight(light)

scene:getDefaultCamera():setPosition(5,5,5)
scene:getDefaultCamera():lookAt(Vector3(0,0,0), Vector3(0,1,0))

lightPositionVal = 0

function Update(elapsed)
	lightPositionVal = lightPositionVal + elapsed
	light:setPosition(sin(lightPositionVal), 2.0, sin(lightPositionVal))
end