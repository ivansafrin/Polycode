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
function BinaryObjectReader:__delete()
	if self then Polycode.delete_BinaryObjectReader(self.__ptr) end
end
