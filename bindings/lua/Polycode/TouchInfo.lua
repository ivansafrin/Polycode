class "TouchInfo"



TouchInfo.TYPEBASE = 0x500
TouchInfo.TYPE_TOUCH = TouchInfo.TYPEBASE + 0
TouchInfo.TYPE_PEN = TouchInfo.TYPEBASE + 1
function TouchInfo:__getvar(name)
	if name == "id" then
		return Polycore.TouchInfo_get_id(self.__ptr)
	elseif name == "position" then
		local retVal = Polycore.TouchInfo_get_position(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Vector2"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "type" then
		return Polycore.TouchInfo_get_type(self.__ptr)
	end
end


function TouchInfo:__setvar(name,value)
	if name == "id" then
		Polycore.TouchInfo_set_id(self.__ptr, value)
		return true
	elseif name == "position" then
		Polycore.TouchInfo_set_position(self.__ptr, value.__ptr)
		return true
	elseif name == "type" then
		Polycore.TouchInfo_set_type(self.__ptr, value)
		return true
	end
	return false
end


function TouchInfo:TouchInfo(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.TouchInfo(unpack(arg))
	end
end

function TouchInfo:__delete()
	if self then Polycore.delete_TouchInfo(self.__ptr) end
end
