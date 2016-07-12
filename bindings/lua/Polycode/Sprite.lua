require "Polycode/Resource"

class "Sprite" (Resource)


function Sprite:Sprite(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "Resource" then
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
		self.__ptr = Polycode.Sprite(unpack(arg))
	end
end

function Sprite:getName()
	local retVal =  Polycode.Sprite_getName(self.__ptr)
	return retVal
end

function Sprite:setName(name)
	local retVal = Polycode.Sprite_setName(self.__ptr, name)
end

function Sprite:getNumStates()
	local retVal =  Polycode.Sprite_getNumStates(self.__ptr)
	return retVal
end

function Sprite:__delete()
	if self then Polycode.delete_Sprite(self.__ptr) end
end
