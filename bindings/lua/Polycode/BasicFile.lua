class "BasicFile"



function BasicFile:__getvar(name)
	if name == "file" then
		local retVal = Polycore.BasicFile_get_file(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["FILE"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end


function BasicFile:__setvar(name,value)
	return false
end


function BasicFile:read(ptr, size, count)
	local retVal = Polycore.BasicFile_read(self.__ptr, ptr.__ptr, size.__ptr, count.__ptr)
	return retVal
end

function BasicFile:write(ptr, size, count)
	local retVal = Polycore.BasicFile_write(self.__ptr, ptr.__ptr, size.__ptr, count.__ptr)
	return retVal
end

function BasicFile:seek(offset, origin)
	local retVal = Polycore.BasicFile_seek(self.__ptr, offset, origin)
	return retVal
end

function BasicFile:tell()
	local retVal =  Polycore.BasicFile_tell(self.__ptr)
	return retVal
end

function BasicFile:__delete()
	if self then Polycore.delete_BasicFile(self.__ptr) end
end
