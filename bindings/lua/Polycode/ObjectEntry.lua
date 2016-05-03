class "ObjectEntry"



ObjectEntry.UNKNOWN_ENTRY = - 1
ObjectEntry.FLOAT_ENTRY = 0
ObjectEntry.INT_ENTRY = 1
ObjectEntry.BOOL_ENTRY = 2
ObjectEntry.ARRAY_ENTRY = 3
ObjectEntry.STRING_ENTRY = 4
ObjectEntry.CONTAINER_ENTRY = 5
function ObjectEntry:__getvar(name)
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


function ObjectEntry:__setvar(name,value)
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
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.ObjectEntry(unpack(arg))
	end
end

function ObjectEntry:readNumber(key, out)
	local retVal = Polycore.ObjectEntry_readNumber(self.__ptr, key, out.__ptr)
	return retVal
end

function ObjectEntry:readString(key, out)
	local retVal = Polycore.ObjectEntry_readString(self.__ptr, key, out.__ptr)
	return retVal
end

function ObjectEntry:readBool(key, out)
	local retVal = Polycore.ObjectEntry_readBool(self.__ptr, key, out.__ptr)
	return retVal
end

function ObjectEntry:addChild(name)
	local retVal = Polycore.ObjectEntry_addChild(self.__ptr, name)
	if retVal == nil then return nil end
	local __c = _G["ObjectEntry"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ObjectEntry:getTypedName()
	local retVal =  Polycore.ObjectEntry_getTypedName(self.__ptr)
	return retVal
end

function ObjectEntry:setTypedName(str)
	local retVal = Polycore.ObjectEntry_setTypedName(self.__ptr, str)
end

function ObjectEntry:Clear()
	local retVal =  Polycore.ObjectEntry_Clear(self.__ptr)
end

function ObjectEntry:__delete()
	if self then Polycore.delete_ObjectEntry(self.__ptr) end
end
