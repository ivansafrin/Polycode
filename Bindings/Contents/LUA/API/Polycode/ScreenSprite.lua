require "Polycode/ScreenShape"

class "ScreenSprite" (ScreenShape)







function ScreenSprite:ScreenSprite(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.ScreenSprite(unpack(arg))
	end
end

function ScreenSprite:addAnimation(name, frames, speed)
	local retVal = Polycore.ScreenSprite_addAnimation(self.__ptr, name, frames, speed)
end

function ScreenSprite:playAnimation(name, startFrame, once)
	local retVal = Polycore.ScreenSprite_playAnimation(self.__ptr, name, startFrame, once)
end

function ScreenSprite:Update()
	local retVal =  Polycore.ScreenSprite_Update(self.__ptr)
end

