scene = PhysicsScene(0, Vector3(200, 200, 200))

ground = ScenePrimitive(ScenePrimitive.TYPE_PLANE, 10, 10)
ground:loadTexture("Resources/green_texture.png")

scene:addPhysicsChild(ground, 6, 0)

for i = 1, 1 do
	local box = ScenePrimitive(ScenePrimitive.TYPE_BOX, 0.8, 0.8, 0.8)
	box:loadTexture("Resources/pink_texture.png")
	box:Roll(-45 + math.random() % 90)
	box:Pitch(-45 + math.random() % 90)
	box:setPosition(-2 + math.random() % 4, i * 0.5, -2 + math.random() % 4)

	scene:addPhysicsChild(box, 0, 1)
end

player = ScenePrimitive(ScenePrimitive.TYPE_BOX, 0.5, 1, 0.5)
player:loadTexture("Resources/pink_texture.png")
player:setColor(1, 1, 0, 1)
player:setPosition(2, 1, 2)

playerController = scene:addCharacterChild(player, 10, 1, 0.5)
local walkSpeed = 0
local rotateSpeed = 0
local playerDirection = 0

testBox = ScenePrimitive(ScenePrimitive.TYPE_BOX, 2, 2, 2)
testBox:loadTexture("Resources/pink_texture.png")
testBox:setColor(0.3, 0.5, 1, 0.4)
testBox:setPosition(2,1,-2)

scene:addCollisionChild(testBox, 0)
	
hud = Scene(Scene.SCENE_2D_TOPLEFT)
onGroundLabel = SceneLabel("Arrow keys to control, spacebar to jump, press R to reset", 16)
onGroundLabel:setAnchorPoint(Vector3(-1, -1, 0))
onGroundLabel:setPosition(0,0)
hud:addChild(onGroundLabel)
onGroundLabel = SceneLabel("On Ground:", 16)
onGroundLabel:setAnchorPoint(Vector3(-1, -1, 0))
onGroundLabel:setPosition(0, 32)

hud:addChild(onGroundLabel)


scene:getDefaultCamera():setPosition(7, 7, 7)
scene:getDefaultCamera():lookAt(Vector3(0, 0, 0), Vector3(0, 1, 0))

function onKeyDown(keyCode)
	if keyCode == KEY_r then
		playerController:warpCharacter(Vector3(2, 1, 2))
	elseif keyCode == KEY_UP then
		walkSpeed = 0.05
	elseif keyCode == KEY_DOWN then
		walkSpeed = -0.05
	elseif keyCode == KEY_LEFT then
		rotateSpeed = 3
	elseif keyCode == KEY_RIGHT then
		rotateSpeed = -3
	elseif keyCode == KEY_SPACE then
		playerController:jump()
	end
end

function onKeyUp(keyCode)
	if keyCode == KEY_DOWN or keyCode == KEY_UP then
		walkSpeed = 0
	elseif keyCode == KEY_RIGHT or keyCode == KEY_LEFT then
		rotateSpeed = 0
	end
end

function Update(elapsed)
	playerDirection = playerDirection + rotateSpeed * elapsed
	
	player:setYaw(playerDirection * (180 / math.pi))
	playerController:setWalkDirection(Vector3(walkSpeed * math.cos(playerDirection), 0, walkSpeed * math.sin(-playerDirection)))
	
	if playerController:onGround() then
		onGroundLabel:setText("On Ground: YES")
	else
		onGroundLabel:setText("On Ground: NO")	
	end
	
	res = scene:testCollision(player, testBox)
	if res.collided then
		testBox:setColor(1, 1, 0, 0.5)		
	else
		testBox:setColor(0, 1, 1, 0.5)	
	end
end