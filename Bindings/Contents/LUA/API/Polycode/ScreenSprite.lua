require "Polycode/ScreenShape"

class "ScreenSprite" (ScreenShape)







function ScreenSprite:ScreenSprite(...)
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1]:class() == "ScreenShape" then
			self.__ptr = arg[1].__ptr
			return
		end
	end
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.ScreenSprite(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function ScreenSprite:addAnimation(name, frames, speed)
	local retVal = Polycore.ScreenSprite_addAnimation(self.__ptr, name.__ptr, frames.__ptr, speed)
end

function ScreenSprite:playAnimation(name, startFrame, once)
	local retVal = Polycore.ScreenSprite_playAnimation(self.__ptr, name.__ptr, startFrame, once)
end

function ScreenSprite:Update()
	local retVal =  Polycore.ScreenSprite_Update(self.__ptr)
end



function ScreenSprite:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_ScreenSprite(self.__ptr)
end
