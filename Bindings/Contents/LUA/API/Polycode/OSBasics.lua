class "OSBasics"

function OSBasics:open(filename, opts)
	return Polycore.OSBasics_open(self.__ptr, filename, opts)
end

function OSBasics:close(file)
	return Polycore.OSBasics_close(self.__ptr, file.__ptr)
end

function OSBasics:read(ptr, size, count, stream)
	return Polycore.OSBasics_read(self.__ptr, ptr.__ptr, size.__ptr, count.__ptr, stream.__ptr)
end

function OSBasics:write(ptr, size, count, stream)
	return Polycore.OSBasics_write(self.__ptr, ptr.__ptr, size.__ptr, count.__ptr, stream.__ptr)
end

function OSBasics:seek(stream, offset, origin)
	return Polycore.OSBasics_seek(self.__ptr, stream.__ptr, offset.__ptr, origin)
end

function OSBasics:tell(stream)
	return Polycore.OSBasics_tell(self.__ptr, stream.__ptr)
end

function OSBasics:parsePhysFSFolder(pathString, showHidden)
	return Polycore.OSBasics_parsePhysFSFolder(self.__ptr, pathString, showHidden)
end

function OSBasics:parseFolder(pathString, showHidden)
	return Polycore.OSBasics_parseFolder(self.__ptr, pathString, showHidden)
end

function OSBasics:isFolder(pathString)
	return Polycore.OSBasics_isFolder(self.__ptr, pathString)
end

function OSBasics:createFolder(pathString)
	return Polycore.OSBasics_createFolder(self.__ptr, pathString)
end

function OSBasics:removeItem(pathString)
	return Polycore.OSBasics_removeItem(self.__ptr, pathString)
end

