class "PhysFSFile"


function PhysFSFile:__getvar(name)
	if name == "physFSFile" then
		local retVal = Polycode.PhysFSFile_get_physFSFile(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["PHYSFS_File"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end

function PhysFSFile:__setvar(name,value)
	if name == "physFSFile" then
		Polycode.PhysFSFile_set_physFSFile(self.__ptr, value.__ptr)
		return true
	end
	return false
end
function PhysFSFile:read(ptr, size, count)
	local retVal = Polycode.PhysFSFile_read(self.__ptr, ptr.__ptr, size.__ptr, count.__ptr)
	return retVal
end

function PhysFSFile:write(ptr, size, count)
	local retVal = Polycode.PhysFSFile_write(self.__ptr, ptr.__ptr, size.__ptr, count.__ptr)
	return retVal
end

function PhysFSFile:seek(offset, origin)
	local retVal = Polycode.PhysFSFile_seek(self.__ptr, offset, origin)
	return retVal
end

function PhysFSFile:tell()
	local retVal =  Polycode.PhysFSFile_tell(self.__ptr)
	return retVal
end

function PhysFSFile:__delete()
	if self then Polycode.delete_PhysFSFile(self.__ptr) end
end
