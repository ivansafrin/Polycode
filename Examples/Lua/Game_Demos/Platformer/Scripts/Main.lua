require "Scripts/Level"
require "Scripts/HUD"

level = Level("level1")

function onKeyDown(key)
	if key == KEY_z then 
		level.player:Jump()
	end
end

function Update(elapsed)
	level:Update(elapsed)
end