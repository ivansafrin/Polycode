
-- Simple sound loading and playing example

sound = Sound("Resources/test.wav")

function onMouseDown(x,y)
	sound:Play()
end
