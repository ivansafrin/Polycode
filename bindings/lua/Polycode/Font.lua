require "Polycode/Resource"

class "Font" (Resource)



function Font:__getvar(name)
	if name == "loaded" then
		return Polycore.Font_get_loaded(self.__ptr)
	end
	if Resource["__getvar"] ~= nil then
		return Resource.__getvar(self, name)
	end
end


function Font:__setvar(name,value)
	if name == "loaded" then
		Polycore.Font_set_loaded(self.__ptr, value)
		return true
	end
	if Resource["__setvar"] ~= nil then
		return Resource.__setvar(self, name, value)
	else
		return false
	end
end


function Font:Font(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "Resource" then
			self.__ptr = arg[1].__ptr
			return
		end
	end
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.Font(unpack(arg))
	end
end

function Font:getFace()
	local retVal =  Polycore.Font_getFace(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["FT_Face"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Font:isValid()
	local retVal =  Polycore.Font_isValid(self.__ptr)
	return retVal
end

function Font:setFontName(fontName)
	local retVal = Polycore.Font_setFontName(self.__ptr, fontName)
end

function Font:getFontName()
	local retVal =  Polycore.Font_getFontName(self.__ptr)
	return retVal
end

function Font:getFontPath()
	local retVal =  Polycore.Font_getFontPath(self.__ptr)
	return retVal
end

function Font:__delete()
	if self then Polycore.delete_Font(self.__ptr) end
end
