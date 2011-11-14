require "Polycode/Image"

class "Label" (Image)



ANTIALIAS_FULL = 0
ANTIALIAS_NONE = 1




function Label:Label(...)
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1]:class() == "Image" then
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
		self.__ptr = Polycore.Label(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function Label:setText(text)
	local retVal = Polycore.Label_setText(self.__ptr, text)
end

function Label:getText()
	local retVal =  Polycore.Label_getText(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = String("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Label:getTextWidth(font, text, size)
	local retVal = Polycore.Label_getTextWidth(self.__ptr, font.__ptr, text, size)
	return retVal
end

function Label:getTextHeight(font, text, size)
	local retVal = Polycore.Label_getTextHeight(self.__ptr, font.__ptr, text, size)
	return retVal
end

function Label:getFont()
	local retVal =  Polycore.Label_getFont(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Font("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end



function Label:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_Label(self.__ptr)
end
