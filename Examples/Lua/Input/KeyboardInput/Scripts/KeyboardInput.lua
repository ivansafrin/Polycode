
-- Keyboard input example.
-- Rotate the Polycode logo with left and right keys

scene = Scene(Scene.SCENE_2D)
scene:getDefaultCamera():setOrthoSize(640, 480)

image = SceneImage("Resources/polycode_logo.png")
scene:addChild(image)
rotationSpeed = 0

function onKeyDown(key)
	if key == KEY_LEFT then
		rotationSpeed = 200
	elseif key == KEY_RIGHT then
		rotationSpeed = -200
	end
end

function onKeyUp(key)
	if key == KEY_LEFT or key == KEY_RIGHT then
		rotationSpeed = 0
	end
end

function Update(elapsed)
        image:Roll(elapsed * rotationSpeed)
end
