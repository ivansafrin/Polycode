class "ObjectEntry"



FLOAT_ENTRY = 0
INT_ENTRY = 1
BOOL_ENTRY = 2
ARRAY_ENTRY = 3
STRING_ENTRY = 4
CONTAINER_ENTRY = 5
function ObjectEntry:__index__(name)
	if name == "type" then
		return Polycore.ObjectEntry_get_type(self.__ptr)
	elseif name == "name" then
		return Polycore.ObjectEntry_get_name(self.__ptr)
	elseif name == "NumberVal" then
		return Polycore.ObjectEntry_get_NumberVal(self.__ptr)
	elseif name == "intVal" then
		return Polycore.ObjectEntry_get_intVal(self.__ptr)
	elseif name == "stringVal" then
		return Polycore.ObjectEntry_get_stringVal(self.__ptr)
	elseif name == "boolVal" then
		return Polycore.ObjectEntry_get_boolVal(self.__ptr)
	elseif name == "length" then
		return Polycore.ObjectEntry_get_length(self.__ptr)
	end
end


function ObjectEntry:__set_callback(name,value)
	if name == "type" then
		Polycore.ObjectEntry_set_type(self.__ptr, value)
		return true
	elseif name == "name" then
		Polycore.ObjectEntry_set_name(self.__ptr, value)
		return true
	elseif name == "NumberVal" then
		Polycore.ObjectEntry_set_NumberVal(self.__ptr, value)
		return true
	elseif name == "intVal" then
		Polycore.ObjectEntry_set_intVal(self.__ptr, value)
		return true
	elseif name == "stringVal" then
		Polycore.ObjectEntry_set_stringVal(self.__ptr, value)
		return true
	elseif name == "boolVal" then
		Polycore.ObjectEntry_set_boolVal(self.__ptr, value)
		return true
	elseif name == "length" then
		Polycore.ObjectEntry_set_length(self.__ptr, value)
		return true
	end
	return false
end


function ObjectEntry:ObjectEntry(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.ObjectEntry(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function ObjectEntry:addChild(name)
	local retVal = Polycore.ObjectEntry_addChild(self.__ptr, name)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = ObjectEntry("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end



function ObjectEntry:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_ObjectEntry(self.__ptr)
end
