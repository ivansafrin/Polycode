class "ProgramAttribute"



function ProgramAttribute:__getvar(name)
	if name == "size" then
		return Polycore.ProgramAttribute_get_size(self.__ptr)
	elseif name == "name" then
		return Polycore.ProgramAttribute_get_name(self.__ptr)
	elseif name == "platformData" then
		local retVal = Polycore.ProgramAttribute_get_platformData(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["void"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end


function ProgramAttribute:__setvar(name,value)
	if name == "size" then
		Polycore.ProgramAttribute_set_size(self.__ptr, value)
		return true
	elseif name == "name" then
		Polycore.ProgramAttribute_set_name(self.__ptr, value)
		return true
	end
	return false
end


function ProgramAttribute:ProgramAttribute(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.ProgramAttribute(unpack(arg))
	end
end

function ProgramAttribute:__delete()
	if self then Polycore.delete_ProgramAttribute(self.__ptr) end
end
