
-- Mouse input example
-- Set the image position to mouse position when the mouse is moved
-- and change the image color when mouse is left or right clicked

scene = Scene(Scene.SCENE_2D)
scene:getActiveCamera():setOrthoSize(640,480)

image = SceneImage("Resources/polycode_logo.png")
scene:addChild(image)

function onMouseMove(x,y)
	local ray =scene:projectRayFromCameraAndViewportCoordinate(scene:getActiveCamera(), Vector2(x,y))
	image:setPosition(ray.origin.x, ray.origin.y)

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

