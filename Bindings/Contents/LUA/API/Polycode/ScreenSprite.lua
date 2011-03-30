require "Polycode/ScreenShape"

class "ScreenSprite" (ScreenShape)

function ScreenSprite:ScreenSprite(fileName, spriteWidth, spriteHeight)
	if self.__ptr == nil then
		self.__ptr = Polycore.ScreenSprite(fileName, spriteWidth, spriteHeight)
	end
end

function ScreenSprite:addAnimation(name, frames, speed)
	return Polycore.ScreenSprite_addAnimation(self.__ptr, name, frames, speed)
end

function ScreenSprite:playAnimation(name, startFrame, once)
	return Polycore.ScreenSprite_playAnimation(self.__ptr, name, startFrame, once)
end

function ScreenSprite:Update()
	return Polycore.ScreenSprite_Update(self.__ptr)
end

