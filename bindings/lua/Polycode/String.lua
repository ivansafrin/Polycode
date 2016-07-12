class "String"

String.ENCODING_UTF8 = 0

function String:__getvar(name)
	if name == "contents" then
		local retVal = Polycode.String_get_contents(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["string"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "w_contents" then
		local retVal = Polycode.String_get_w_contents(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["wstring"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end

function String:__setvar(name,value)
	if name == "contents" then
		Polycode.String_set_contents(self.__ptr, value.__ptr)
		return true
	elseif name == "w_contents" then
		Polycode.String_set_w_contents(self.__ptr, value.__ptr)
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
		self.__ptr = Polycode.String(unpack(arg))
	end
end

function String:size()
	local retVal =  Polycode.String_size(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["size_t"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function String:length()
	local retVal =  Polycode.String_length(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["size_t"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function String:substr(pos, n)
	local retVal = Polycode.String_substr(self.__ptr, pos.__ptr, n.__ptr)
	return retVal
end

function String:rfind(str, pos)
	local retVal = Polycode.String_rfind(self.__ptr, str, pos.__ptr)
	if retVal == nil then return nil end
	local __c = _G["size_t"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function String:find(str, pos)
	local retVal = Polycode.String_find(self.__ptr, str, pos.__ptr)
	if retVal == nil then return nil end
	local __c = _G["size_t"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function String:find_last_of(str, pos)
	local retVal = Polycode.String_find_last_of(self.__ptr, str, pos.__ptr)
	if retVal == nil then return nil end
	local __c = _G["size_t"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function String:find_first_of(str, pos)
	local retVal = Polycode.String_find_first_of(self.__ptr, str, pos.__ptr)
	if retVal == nil then return nil end
	local __c = _G["size_t"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function String:find_first_not_of(str, pos)
	local retVal = Polycode.String_find_first_not_of(self.__ptr, str, pos.__ptr)
	if retVal == nil then return nil end
	local __c = _G["size_t"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function String:toLowerCase()
	local retVal =  Polycode.String_toLowerCase(self.__ptr)
	return retVal
end

function String:toUpperCase()
	local retVal =  Polycode.String_toUpperCase(self.__ptr)
	return retVal
end

function String:split(delim)
	local retVal = Polycode.String_split(self.__ptr, delim)
	if retVal == nil then return nil end
	for i=1,count(retVal) do
		local __c  = _G["String"]("__skip_ptr__")
		__c.__ptr = retVal[i]
		retVal[i] = __c
	end
	return retVal
end

function String:replace(what, withWhat)
	local retVal = Polycode.String_replace(self.__ptr, what, withWhat)
	return retVal
end

function String:NumberToString(value, precision)
	local retVal = Polycode.String_NumberToString(self.__ptr, value, precision)
	return retVal
end

function String:toNumber()
	local retVal =  Polycode.String_toNumber(self.__ptr)
	return retVal
end

function String:toInteger()
	local retVal =  Polycode.String_toInteger(self.__ptr)
	return retVal
end

function String:IntToString(value)
	local retVal = Polycode.String_IntToString(self.__ptr, value)
	return retVal
end

function String:append(c)
	local retVal = Polycode.String_append(self.__ptr, c.__ptr)
end

function String:getDataSizeWithEncoding(encoding)
	local retVal = Polycode.String_getDataSizeWithEncoding(self.__ptr, encoding)
	if retVal == nil then return nil end
	local __c = _G["size_t"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function String:isNumber()
	local retVal =  Polycode.String_isNumber(self.__ptr)
	return retVal
end

function String:isInteger()
	local retVal =  Polycode.String_isInteger(self.__ptr)
	return retVal
end

function String:__delete()
	if self then Polycode.delete_String(self.__ptr) end
end
