class "String"



ENCODING_UTF8 = 0
function String:__index__(name)
	if name == "contents" then
		retVal = Polycore.String_get_contents(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = string("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	end
end


function String:__set_callback(name,value)
	return false
end


function String:String(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.String(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function String:size()
	local retVal =  Polycore.String_size(self.__ptr)
	return retVal
end

function String:length()
	local retVal =  Polycore.String_length(self.__ptr)
	return retVal
end

function String:getSTLString()
	local retVal =  Polycore.String_getSTLString(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = string("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function String:substr(pos, n)
	local retVal = Polycore.String_substr(self.__ptr, pos.__ptr, n.__ptr)
	return retVal
end

function String:rfind(str, pos)
	local retVal = Polycore.String_rfind(self.__ptr, str.__ptr, pos.__ptr)
	return retVal
end

function String:find(str, pos)
	local retVal = Polycore.String_find(self.__ptr, str.__ptr, pos.__ptr)
	return retVal
end

function String:find_last_of(str, pos)
	local retVal = Polycore.String_find_last_of(self.__ptr, str.__ptr, pos.__ptr)
	return retVal
end

function String:toLowerCase()
	local retVal =  Polycore.String_toLowerCase(self.__ptr)
	return retVal
end

function String:toUpperCase()
	local retVal =  Polycore.String_toUpperCase(self.__ptr)
	return retVal
end

function String:replace(what, withWhat)
	local retVal = Polycore.String_replace(self.__ptr, what.__ptr, withWhat.__ptr)
	return retVal
end

function String:NumberToString(value)
	local retVal = Polycore.String_NumberToString(value)
	return retVal
end

function String:c_str()
	local retVal =  Polycore.String_c_str(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = char("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function String:getDataWithEncoding(encoding)
	local retVal = Polycore.String_getDataWithEncoding(self.__ptr, encoding)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = char("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function String:getDataSizeWithEncoding(encoding)
	local retVal = Polycore.String_getDataSizeWithEncoding(self.__ptr, encoding)
	return retVal
end

function String:setDataWithEncoding(data, encoding)
	local retVal = Polycore.String_setDataWithEncoding(self.__ptr, data.__ptr, encoding)
end



function String:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_String(self.__ptr)
end
