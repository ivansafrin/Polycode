class "Font"







function Font:Font(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.Font(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function Font:getFace()
	local retVal =  Polycore.Font_getFace(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = FT_Face("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Font:isValid()
	local retVal =  Polycore.Font_isValid(self.__ptr)
	return retVal
end

