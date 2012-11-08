
-- Mouse input example
-- Set the image position to mouse position when the mouse is moved
-- and change the image color when mouse is left or right clicked

screen = Screen()
image = ScreenImage("Resources/polycode_logo.png")
image:setPositionMode(ScreenEntity.POSITION_CENTER)
screen:addChild(image)

function onMouseMove(x,y)
	image.position.x = x
	image.position.y = y
end

function onMouseDown(button, x,y)
	if button == 0 then
		image:setColor(1.0, 0.0, 0.0, 1.0)
	else
		image:setColor(0.0, 1.0, 0.0, 1.0)
	end
end

function onMouseUp(button, x,y)
	image:setColor(1.0, 1.0, 1.0, 1.0)
end

