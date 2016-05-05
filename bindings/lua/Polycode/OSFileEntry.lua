class "OSFileEntry"

OSFileEntry.TYPE_FILE = 0
OSFileEntry.TYPE_FOLDER = 1

function OSFileEntry:__getvar(name)
	if name == "name" then
		return Polycode.OSFileEntry_get_name(self.__ptr)
	elseif name == "extension" then
		return Polycode.OSFileEntry_get_extension(self.__ptr)
	elseif name == "nameWithoutExtension" then
		return Polycode.OSFileEntry_get_nameWithoutExtension(self.__ptr)
	elseif name == "basePath" then
		return Polycode.OSFileEntry_get_basePath(self.__ptr)
	elseif name == "fullPath" then
		return Polycode.OSFileEntry_get_fullPath(self.__ptr)
	elseif name == "type" then
		return Polycode.OSFileEntry_get_type(self.__ptr)
	end
end

function OSFileEntry:__setvar(name,value)
	if name == "name" then
		Polycode.OSFileEntry_set_name(self.__ptr, value)
		return true
	elseif name == "extension" then
		Polycode.OSFileEntry_set_extension(self.__ptr, value)
		return true
	elseif name == "nameWithoutExtension" then
		Polycode.OSFileEntry_set_nameWithoutExtension(self.__ptr, value)
		return true
	elseif name == "basePath" then
		Polycode.OSFileEntry_set_basePath(self.__ptr, value)
		return true
	elseif name == "fullPath" then
		Polycode.OSFileEntry_set_fullPath(self.__ptr, value)
		return true
	elseif name == "type" then
		Polycode.OSFileEntry_set_type(self.__ptr, value)
		return true
	end
	return false
end
function OSFileEntry:OSFileEntry(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.OSFileEntry(unpack(arg))
	end
end

function OSFileEntry:init(path, name, type)
	local retVal = Polycode.OSFileEntry_init(self.__ptr, path, name, type)
end

function OSFileEntry:__delete()
	if self then Polycode.delete_OSFileEntry(self.__ptr) end
end
