
-- Keyboard input example.
-- Rotate the Polycode logo with left and right keys

screen = Screen()

image = ScreenImage("Resources/polycode_logo.png")
image:setPositionMode(ScreenEntity.POSITION_CENTER)
image:setPosition(640/2,480/2)
screen:addChild(image)
rotationSpeed = 0

function onKeyDown(key)
	if key == KEY_LEFT then
		rotationSpeed = -200
	elseif key == KEY_RIGHT then
		rotationSpeed = 200
	end
end

function onKeyUp(key)
	if key == KEY_LEFT or key == KEY_RIGHT then
		rotationSpeed = 0
	end
end

function Update(elapsed)
        image.rotation.roll = image.rotation.roll + (elapsed * rotationSpeed)
end
