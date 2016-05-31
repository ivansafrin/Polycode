class "ProgramAttribute"


function ProgramAttribute:__getvar(name)
	if name == "size" then
		return Polycode.ProgramAttribute_get_size(self.__ptr)
	elseif name == "name" then
		return Polycode.ProgramAttribute_get_name(self.__ptr)
	elseif name == "arrayType" then
		return Polycode.ProgramAttribute_get_arrayType(self.__ptr)
	end
end

function ProgramAttribute:__setvar(name,value)
	if name == "size" then
		Polycode.ProgramAttribute_set_size(self.__ptr, value)
		return true
	elseif name == "name" then
		Polycode.ProgramAttribute_set_name(self.__ptr, value)
		return true
	elseif name == "arrayType" then
		Polycode.ProgramAttribute_set_arrayType(self.__ptr, value)
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
		self.__ptr = Polycode.ProgramAttribute(unpack(arg))
	end
end

function ProgramAttribute:__delete()
	if self then Polycode.delete_ProgramAttribute(self.__ptr) end
end
