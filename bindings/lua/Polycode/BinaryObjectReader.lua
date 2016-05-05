class "BinaryObjectReader"


function BinaryObjectReader:__getvar(name)
	if name == "success" then
		return Polycode.BinaryObjectReader_get_success(self.__ptr)
	end
end

function BinaryObjectReader:__setvar(name,value)
	if name == "success" then
		Polycode.BinaryObjectReader_set_success(self.__ptr, value)
		return true
	end
	return false
end
function BinaryObjectReader:BinaryObjectReader(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.BinaryObjectReader(unpack(arg))
	end
end

function BinaryObjectReader:__delete()
	if self then Polycode.delete_BinaryObjectReader(self.__ptr) end
end
