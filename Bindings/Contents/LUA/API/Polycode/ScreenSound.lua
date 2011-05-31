require "Polycode/ScreenEntity"

class "ScreenSound" (ScreenEntity)







function ScreenSound:ScreenSound(...)
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
		self.__ptr = Polycore.ScreenSound(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function ScreenSound:Update()
	local retVal =  Polycore.ScreenSound_Update(self.__ptr)
end

function ScreenSound:getSound()
	local retVal =  Polycore.ScreenSound_getSound(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Sound("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end



function ScreenSound:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_ScreenSound(self.__ptr)
end
