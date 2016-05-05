class "BasicFile"


function BasicFile:__getvar(name)
	if name == "file" then
		local retVal = Polycode.BasicFile_get_file(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["FILE"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end

function BasicFile:__setvar(name,value)
	if name == "file" then
		Polycode.BasicFile_set_file(self.__ptr, value.__ptr)
		return true
	end
	return false
end
function BasicFile:read(ptr, size, count)
	local retVal = Polycode.BasicFile_read(self.__ptr, ptr.__ptr, size.__ptr, count.__ptr)
	return retVal
end

function BasicFile:write(ptr, size, count)
	local retVal = Polycode.BasicFile_write(self.__ptr, ptr.__ptr, size.__ptr, count.__ptr)
	return retVal
end

function BasicFile:seek(offset, origin)
	local retVal = Polycode.BasicFile_seek(self.__ptr, offset, origin)
	return retVal
end

function BasicFile:tell()
	local retVal =  Polycode.BasicFile_tell(self.__ptr)
	return retVal
end

function BasicFile:__delete()
	if self then Polycode.delete_BasicFile(self.__ptr) end
end
