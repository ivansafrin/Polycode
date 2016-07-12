class "ProgramParam"

ProgramParam.PARAM_UNKNOWN = 0
ProgramParam.PARAM_NUMBER = 1
ProgramParam.PARAM_VECTOR2 = 2
ProgramParam.PARAM_VECTOR3 = 3
ProgramParam.PARAM_COLOR = 4
ProgramParam.PARAM_MATRIX = 5
ProgramParam.PARAM_TEXTURE = 6
ProgramParam.PARAM_CUBEMAP = 7

function ProgramParam:__getvar(name)
	if name == "name" then
		return Polycode.ProgramParam_get_name(self.__ptr)
	elseif name == "type" then
		return Polycode.ProgramParam_get_type(self.__ptr)
	end
end

function ProgramParam:__setvar(name,value)
	if name == "name" then
		Polycode.ProgramParam_set_name(self.__ptr, value)
		return true
	elseif name == "type" then
		Polycode.ProgramParam_set_type(self.__ptr, value)
		return true
	end
	return false
end
function ProgramParam:ProgramParam(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.ProgramParam(unpack(arg))
	end
end

function ProgramParam:__delete()
	if self then Polycode.delete_ProgramParam(self.__ptr) end
end
