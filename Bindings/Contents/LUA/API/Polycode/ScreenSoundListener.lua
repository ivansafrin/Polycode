require "Polycode/ScreenEntity"

class "ScreenSoundListener" (ScreenEntity)







function ScreenSoundListener:ScreenSoundListener(...)
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1]:class() == "ScreenEntity" then
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
		self.__ptr = Polycore.ScreenSoundListener(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function ScreenSoundListener:Update()
	local retVal =  Polycore.ScreenSoundListener_Update(self.__ptr)
end



function ScreenSoundListener:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_ScreenSoundListener(self.__ptr)
end
