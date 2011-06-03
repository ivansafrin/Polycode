class "OSBasics"







function OSBasics:open(filename, opts)
	local retVal = Polycore.OSBasics_open(filename, opts)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = OSFILE("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function OSBasics:close(file)
	local retVal = Polycore.OSBasics_close(file.__ptr)
	return retVal
end

function OSBasics:read(ptr, size, count, stream)
	local retVal = Polycore.OSBasics_read(ptr.__ptr, size.__ptr, count.__ptr, stream.__ptr)
	return retVal
end

function OSBasics:write(ptr, size, count, stream)
	local retVal = Polycore.OSBasics_write(ptr.__ptr, size.__ptr, count.__ptr, stream.__ptr)
	return retVal
end

function OSBasics:seek(stream, offset, origin)
	local retVal = Polycore.OSBasics_seek(stream.__ptr, offset.__ptr, origin)
	return retVal
end

function OSBasics:tell(stream)
	local retVal = Polycore.OSBasics_tell(stream.__ptr)
	return retVal
end

function OSBasics:isFolder(pathString)
	local retVal = Polycore.OSBasics_isFolder(pathString)
	return retVal
end

function OSBasics:createFolder(pathString)
	local retVal = Polycore.OSBasics_createFolder(pathString)
end

function OSBasics:removeItem(pathString)
	local retVal = Polycore.OSBasics_removeItem(pathString)
end



function OSBasics:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_OSBasics(self.__ptr)
end
