class "OSFileEntry"



TYPE_FILE = 0
TYPE_FOLDER = 1
function OSFileEntry:__index__(name)
	if name == "name" then
		retVal = Polycore.OSFileEntry_get_name(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = Polycode::String("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "extension" then
		retVal = Polycore.OSFileEntry_get_extension(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = Polycode::String("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "nameWithoutExtension" then
		retVal = Polycore.OSFileEntry_get_nameWithoutExtension(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = Polycode::String("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "basePath" then
		retVal = Polycore.OSFileEntry_get_basePath(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = Polycode::String("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "fullPath" then
		retVal = Polycore.OSFileEntry_get_fullPath(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = Polycode::String("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "type" then
		return Polycore.OSFileEntry_get_type(self.__ptr)
	end
end


function OSFileEntry:__set_callback(name,value)
	if name == "type" then
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



function OSFileEntry:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_OSFileEntry(self.__ptr)
end
