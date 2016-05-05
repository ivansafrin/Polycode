class "Rectangle"


function Rectangle:__getvar(name)
	if name == "x" then
		return Polycode.Rectangle_get_x(self.__ptr)
	elseif name == "y" then
		return Polycode.Rectangle_get_y(self.__ptr)
	elseif name == "w" then
		return Polycode.Rectangle_get_w(self.__ptr)
	elseif name == "h" then
		return Polycode.Rectangle_get_h(self.__ptr)
	end
end

function Rectangle:__setvar(name,value)
	if name == "x" then
		Polycode.Rectangle_set_x(self.__ptr, value)
		return true
	elseif name == "y" then
		Polycode.Rectangle_set_y(self.__ptr, value)
		return true
	elseif name == "w" then
		Polycode.Rectangle_set_w(self.__ptr, value)
		return true
	elseif name == "h" then
		Polycode.Rectangle_set_h(self.__ptr, value)
		return true
	end
	return false
end
function Rectangle:Rectangle(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.Rectangle(unpack(arg))
	end
end

function Rectangle:setRect(x, y, w, h)
	local retVal = Polycode.Rectangle_setRect(self.__ptr, x, y, w, h)
end

function Rectangle:Clipped(rect)
	local retVal = Polycode.Rectangle_Clipped(self.__ptr, rect.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Rectangle"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Rectangle:minX()
	local retVal =  Polycode.Rectangle_minX(self.__ptr)
	return retVal
end

function Rectangle:maxX()
	local retVal =  Polycode.Rectangle_maxX(self.__ptr)
	return retVal
end

function Rectangle:minY()
	local retVal =  Polycode.Rectangle_minY(self.__ptr)
	return retVal
end

function Rectangle:maxY()
	local retVal =  Polycode.Rectangle_maxY(self.__ptr)
	return retVal
end

function Rectangle:__delete()
	if self then Polycode.delete_Rectangle(self.__ptr) end
end
