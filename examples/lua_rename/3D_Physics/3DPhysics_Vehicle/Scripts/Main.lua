scene = PhysicsScene(0, Vector3(200, 200, 200))

ground = ScenePrimitive(ScenePrimitive.TYPE_PLANE, 30, 30)
ground:loadTexture("Resources/green_texture.png")
scene:addPhysicsChild(ground, 0, 0)

-- Some obstacles
local box = ScenePrimitive(ScenePrimitive.TYPE_BOX, 4,4,6)
box:setPitch(25)
box:setPosition(7, -1, 0)
box:setColor(0.5, 0.5, 1,1)
box:loadTexture("Resources/green_texture.png")
scene:addPhysicsChild(box, 0, 0)

box = ScenePrimitive(ScenePrimitive.TYPE_BOX, 4, 4, 6)
box:setPitch(25)
box:setPosition(-7, -1, 0)
box:setColor(0.5,0.5,1,1)
box:loadTexture("Resources/green_texture.png")
scene:addPhysicsChild(box, 0, 0)

box = ScenePrimitive(ScenePrimitive.TYPE_BOX, 20,2,5)
box:setPosition(0,1, -4.3)
box:setColor(0.5,0.5,1,1)
box:loadTexture("Resources/green_texture.png")
scene:addPhysicsChild(box, 0, 0)

for i = 1, 10 do
	box = ScenePrimitive(ScenePrimitive.TYPE_BOX, 0.7,0.7,0.7)
	box:loadTexture("Resources/pink_texture.png")
	box:Roll(-45 + math.random() % 90)
	box:Pitch(-45 + (math.random() % 90))
	box:setPosition(-3 + (math.random() % 6), 2 + i*0.5, -5 + math.random() % 3)
	scene:addPhysicsChild(box, 0, 1)
end

-- The vehicle
vehicle = ScenePrimitive(ScenePrimitive.TYPE_BOX, 1, 0.5, 2)
vehicle:loadTexture("Resources/pink_texture.png")
vehicle:setColor(1, 1, 0, 1)
vehicle:setPosition(6,1,5)
vehicleController = scene:addVehicleChild(vehicle, 5, 1)

local wheel = ScenePrimitive(ScenePrimitive.TYPE_SPHERE, 0.3, 10, 10)
wheel:loadTexture("Resources/pink_texture.png")
wheel:setColor(0, 1, 0, 1)
vehicleController:addWheel(wheel, Vector3(0.6, 0, -0.5), Vector3(0, -1, 0), Vector3(-1,0,0), 0.2, 0.3, true)
scene:addEntity(wheel)

wheel = ScenePrimitive(ScenePrimitive.TYPE_SPHERE, 0.3, 10, 10)
wheel:loadTexture("Resources/pink_texture.png")
wheel:setColor(0, 1, 0, 1)
vehicleController:addWheel(wheel, Vector3(-0.6,0,-0.5), Vector3(0,-1,0), Vector3(-1,0,0), 0.2, 0.3, true)
scene:addEntity(wheel)

wheel = ScenePrimitive(ScenePrimitive.TYPE_SPHERE, 0.3, 10, 10)
wheel:loadTexture("Resources/pink_texture.png")
wheel:setColor(0, 1, 0, 1)
vehicleController:addWheel(wheel, Vector3(0.6,0,0.5), Vector3(0,-1,0), Vector3(-1,0,0), 0.2, 0.3, false)
scene:addEntity(wheel)

wheel = ScenePrimitive(ScenePrimitive.TYPE_SPHERE, 0.3, 10, 10)
wheel:loadTexture("Resources/pink_texture.png")
wheel:setColor(0, 1, 0, 1)
vehicleController:addWheel(wheel, Vector3(-0.6,0,0.5), Vector3(0,-1,0), Vector3(-1,0,0), 0.2, 0.3, false)
scene:addEntity(wheel)

local steeringValue = 0
local engineForce = 0
local breaking = false

local testBox = ScenePrimitive(ScenePrimitive.TYPE_BOX, 4, 4, 4)
testBox:loadTexture("Resources/pink_texture.png")
testBox:setColor(0.3, 0.5, 1, 0.4)
testBox:setPosition(-5, 2, 7)
scene:addCollisionChild(testBox, 0)


scene:getDefaultCamera():setPosition(16, 16, 16)
scene:getDefaultCamera():lookAt(Vector3(0, 0, 0), Vector3(0, 1, 0))

function onKeyDown(keyCode)
	if keyCode == KEY_r then
		vehicleController:warpVehicle(Vector3(6,1,5))
	elseif keyCode == KEY_UP then
		engineForce = -15
	elseif keyCode == KEY_DOWN then
		engineForce = 15
	elseif keyCode == KEY_LEFT then
		steeringValue = 0.5
	elseif keyCode == KEY_RIGHT then
		steeringValue = -0.5
	elseif keyCode == KEY_SPACE then
		breaking = true
	end
end

function onKeyUp(keyCode)
	if keyCode == KEY_DOWN or keyCode == KEY_UP then
		engineForce = 0	
	elseif keyCode == KEY_RIGHT or keyCode == KEY_LEFT then
		steeringValue = 0
	elseif keyCode == KEY_SPACE then
		breaking = false
	end
end

function Update(elapsed)
	
	if breaking then
		vehicleController:setBrake(20, 2)
		vehicleController:setBrake(20, 3)
		vehicleController:applyEngineForce(0, 2)
		vehicleController:applyEngineForce(0, 3)
	else
		vehicleController:setBrake(0, 2)
		vehicleController:setBrake(0, 3)
		vehicleController:applyEngineForce(engineForce, 2)
		vehicleController:applyEngineForce(engineForce, 3)
	end
	
	vehicleController:setSteeringValue(steeringValue, 0)
	vehicleController:setSteeringValue(steeringValue, 1)
	
	local res = scene:testCollision(vehicle, testBox)
	if res.collided then
		testBox:setColor(1,1,0,0.5)
	else
		testBox:setColor(0,1,1,0.5)
	end
end