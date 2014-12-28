hud = Scene(Scene.SCENE_2D)

label = SceneLabel("Click on a shape to select it.", 16)
label:setPosition(-640/ 2 + 120, 480 / 2 - 10)

hud:addChild(label)

scene = CollisionScene(Vector3(2000, 2000, 2000), false, false)

local ground = ScenePrimitive(ScenePrimitive.TYPE_PLANE, 10, 10)
ground:loadTexture("Resources/green_texture.png")
scene:addEntity(ground)

local box = ScenePrimitive(ScenePrimitive.TYPE_BOX, 1, 1, 1)
box:loadTexture("Resources/pink_texture.png")
box:setPosition(0, 1, 0)
scene:addCollisionChild(box, CollisionEntity.SHAPE_MESH)

local cone = ScenePrimitive(ScenePrimitive.TYPE_CONE, 1, 1, 10)
cone:loadTexture("Resources/pink_texture.png")
cone:setPosition(1, 2, 2)
scene:addCollisionChild(cone, CollisionEntity.SHAPE_CONE)

local cylinder = ScenePrimitive(ScenePrimitive.TYPE_CYLINDER, 2, 0.5, 10)
cylinder:loadTexture("Resources/pink_texture.png")
cylinder:setPosition(2, 1, -1)
scene:addCollisionChild(cylinder, CollisionEntity.SHAPE_CYLINDER)


scene:getDefaultCamera():setPosition(7, 7, 7)
scene:getDefaultCamera():lookAt(Vector3(0, 0, 0), Vector3(0, 1, 0))

local lastEntity = nil

function onMouseDown(button, x, y)
	local ray = scene:projectRayFromCameraAndViewportCoordinate(scene:getActiveCamera(), Vector2(x,y))
	local res = scene:getFirstEntityInRay(ray.origin, Vector3(ray.direction.x * 100, ray.direction.y * 100, ray.direction.z * 100))

	if lastEntity then
		lastEntity:setColor(1, 1, 1, 1)
	end

	if res.entity then
		res.entity:setColor(1, 0, 0, 1)
		lastEntity = res.entity
		end
end