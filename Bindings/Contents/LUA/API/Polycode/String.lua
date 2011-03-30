class "String"

function String:String()
	if self.__ptr == nil then
		self.__ptr = Polycore.String()
	end
end

function String:size()
	return Polycore.String_size(self.__ptr)
end

function String:length()
	return Polycore.String_length(self.__ptr)
end

function String:getSTLString()
	return Polycore.String_getSTLString(self.__ptr)
end

function String:getSTLWString()
	return Polycore.String_getSTLWString(self.__ptr)
end

function String:substr(pos, n)
	return Polycore.String_substr(self.__ptr, pos.__ptr, n.__ptr)
end

function String:rfind(str, pos)
	return Polycore.String_rfind(self.__ptr, str.__ptr, pos.__ptr)
end

function String:find(str, pos)
	return Polycore.String_find(self.__ptr, str.__ptr, pos.__ptr)
end

function String:toLowerCase()
	return Polycore.String_toLowerCase(self.__ptr)
end

function String:split(delims)
	return Polycore.String_split(self.__ptr, delims.__ptr)
end

function String:replace(what, withWhat)
	return Polycore.String_replace(self.__ptr, what.__ptr, withWhat.__ptr)
end

function String:NumberToString(value)
	return Polycore.String_NumberToString(self.__ptr, value)
end

function String:c_str()
	return Polycore.String_c_str(self.__ptr)
end

function String:wc_str()
	return Polycore.String_wc_str(self.__ptr)
end

function String:data()
	return Polycore.String_data(self.__ptr)
end

function String:getDataWithEncoding(encoding)
	return Polycore.String_getDataWithEncoding(self.__ptr, encoding)
end

function String:setDataWithEncoding(data, encoding)
	return Polycore.String_setDataWithEncoding(self.__ptr, data.__ptr, encoding)
end

function String:getDataSizeWithEncoding(encoding)
	return Polycore.String_getDataSizeWithEncoding(self.__ptr, encoding)
end

