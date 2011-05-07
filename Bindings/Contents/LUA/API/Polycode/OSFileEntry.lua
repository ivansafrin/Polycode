class "OSFileEntry"



TYPE_FILE = 0
TYPE_FOLDER = 1
function OSFileEntry:__index__(name)
	if name == "name" then
		return Polycore.OSFileEntry_get_name(self.__ptr)
	elseif name == "extension" then
		return Polycore.OSFileEntry_get_extension(self.__ptr)
	elseif name == "nameWithoutExtension" then
		return Polycore.OSFileEntry_get_nameWithoutExtension(self.__ptr)
	elseif name == "basePath" then
		return Polycore.OSFileEntry_get_basePath(self.__ptr)
	elseif name == "fullPath" then
		return Polycore.OSFileEntry_get_fullPath(self.__ptr)
	elseif name == "type" then
		return Polycore.OSFileEntry_get_type(self.__ptr)
	end
end


function OSFileEntry:__set_callback(name,value)
	if name == "name" then
		Polycore.OSFileEntry_set_name(self.__ptr, value)
		return true
	elseif name == "extension" then
		Polycore.OSFileEntry_set_extension(self.__ptr, value)
		return true
	elseif name == "nameWithoutExtension" then
		Polycore.OSFileEntry_set_nameWithoutExtension(self.__ptr, value)
		return true
	elseif name == "basePath" then
		Polycore.OSFileEntry_set_basePath(self.__ptr, value)
		return true
	elseif name == "fullPath" then
		Polycore.OSFileEntry_set_fullPath(self.__ptr, value)
		return true
	elseif name == "type" then
		Polycore.OSFileEntry_set_type(self.__ptr, value)
		return true
	end
	return false
end


function OSFileEntry:OSFileEntry(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.OSFileEntry(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

