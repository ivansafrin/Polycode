class "String"



String.ENCODING_UTF8 = 0
function String:__getvar(name)
	if name == "contents" then
		local retVal = Polycore.String_get_contents(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["string"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "w_contents" then
		local retVal = Polycore.String_get_w_contents(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["wstring"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end


function String:__setvar(name,value)
	if name == "contents" then
		Polycore.String_set_contents(self.__ptr, value.__ptr)
		return true
	elseif name == "w_contents" then
		Polycore.String_set_w_contents(self.__ptr, value.__ptr)
		return true
	end
	return false
end


function String:String(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.String(unpack(arg))
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

function String:substr(pos, n)
	local retVal = Polycore.String_substr(self.__ptr, pos.__ptr, n.__ptr)
	return retVal
end

function String:rfind(str, pos)
	local retVal = Polycore.String_rfind(self.__ptr, str, pos.__ptr)
	return retVal
end

function String:find(str, pos)
	local retVal = Polycore.String_find(self.__ptr, str, pos.__ptr)
	return retVal
end

function String:find_last_of(str, pos)
	local retVal = Polycore.String_find_last_of(self.__ptr, str, pos.__ptr)
	return retVal
end

function String:find_first_of(str, pos)
	local retVal = Polycore.String_find_first_of(self.__ptr, str, pos.__ptr)
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

function String:split(delim)
	local retVal = Polycore.String_split(self.__ptr, delim)
	if retVal == nil then return nil end
	local __c = _G["std::vector<String>"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function String:replace(what, withWhat)
	local retVal = Polycore.String_replace(self.__ptr, what, withWhat)
	return retVal
end

function String.NumberToString(value, precision)
	local retVal = Polycore.String_NumberToString(value, precision)
	return retVal
end

function String:toNumber()
	local retVal =  Polycore.String_toNumber(self.__ptr)
	return retVal
end

function String:toInteger()
	local retVal =  Polycore.String_toInteger(self.__ptr)
	return retVal
end

function String.IntToString(value)
	local retVal = Polycore.String_IntToString(value)
	return retVal
end

function String:c_str()
	local retVal =  Polycore.String_c_str(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["char"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function String:getDataWithEncoding(encoding)
	local retVal = Polycore.String_getDataWithEncoding(self.__ptr, encoding)
	if retVal == nil then return nil end
	local __c = _G["char"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function String:getWDataWithEncoding(encoding)
	local retVal = Polycore.String_getWDataWithEncoding(self.__ptr, encoding)
	if retVal == nil then return nil end
	local __c = _G["wchar_t"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function String:append(c)
	local retVal = Polycore.String_append(self.__ptr, c.__ptr)
end

function String:getDataSizeWithEncoding(encoding)
	local retVal = Polycore.String_getDataSizeWithEncoding(self.__ptr, encoding)
	return retVal
end

function String:setDataWithEncoding(data, encoding)
	local retVal = Polycore.String_setDataWithEncoding(self.__ptr, data.__ptr, encoding)
end

function String:isNumber()
	local retVal =  Polycore.String_isNumber(self.__ptr)
	return retVal
end

function String:__delete()
	if self then Polycore.delete_String(self.__ptr) end
end
