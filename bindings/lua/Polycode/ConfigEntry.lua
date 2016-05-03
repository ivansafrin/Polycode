class "ConfigEntry"



function ConfigEntry:__getvar(name)
	if name == "key" then
		return Polycore.ConfigEntry_get_key(self.__ptr)
	elseif name == "configNamespace" then
		return Polycore.ConfigEntry_get_configNamespace(self.__ptr)
	elseif name == "numVal" then
		return Polycore.ConfigEntry_get_numVal(self.__ptr)
	elseif name == "stringVal" then
		return Polycore.ConfigEntry_get_stringVal(self.__ptr)
	elseif name == "isString" then
		return Polycore.ConfigEntry_get_isString(self.__ptr)
	end
end


function ConfigEntry:__setvar(name,value)
	if name == "key" then
		Polycore.ConfigEntry_set_key(self.__ptr, value)
		return true
	elseif name == "configNamespace" then
		Polycore.ConfigEntry_set_configNamespace(self.__ptr, value)
		return true
	elseif name == "numVal" then
		Polycore.ConfigEntry_set_numVal(self.__ptr, value)
		return true
	elseif name == "stringVal" then
		Polycore.ConfigEntry_set_stringVal(self.__ptr, value)
		return true
	elseif name == "isString" then
		Polycore.ConfigEntry_set_isString(self.__ptr, value)
		return true
	end
	return false
end


function ConfigEntry:__delete()
	if self then Polycore.delete_ConfigEntry(self.__ptr) end
end
