class "Rectangle"



function Rectangle:__getvar(name)
	if name == "x" then
		return Polycore.Rectangle_get_x(self.__ptr)
	elseif name == "y" then
		return Polycore.Rectangle_get_y(self.__ptr)
	elseif name == "w" then
		return Polycore.Rectangle_get_w(self.__ptr)
	elseif name == "h" then
		return Polycore.Rectangle_get_h(self.__ptr)
	end
end


function Rectangle:__setvar(name,value)
	if name == "x" then
		Polycore.Rectangle_set_x(self.__ptr, value)
		return true
	elseif name == "y" then
		Polycore.Rectangle_set_y(self.__ptr, value)
		return true
	elseif name == "w" then
		Polycore.Rectangle_set_w(self.__ptr, value)
		return true
	elseif name == "h" then
		Polycore.Rectangle_set_h(self.__ptr, value)
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
		self.__ptr = Polycore.Rectangle(unpack(arg))
	end
end

function Rectangle:setRect(x, y, w, h)
	local retVal = Polycore.Rectangle_setRect(self.__ptr, x, y, w, h)
end

function Rectangle:Clipped(rect)
	local retVal = Polycore.Rectangle_Clipped(self.__ptr, rect.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Rectangle"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Rectangle:minX()
	local retVal =  Polycore.Rectangle_minX(self.__ptr)
	return retVal
end

function Rectangle:maxX()
	local retVal =  Polycore.Rectangle_maxX(self.__ptr)
	return retVal
end

function Rectangle:minY()
	local retVal =  Polycore.Rectangle_minY(self.__ptr)
	return retVal
end

function Rectangle:maxY()
	local retVal =  Polycore.Rectangle_maxY(self.__ptr)
	return retVal
end

function Rectangle:__delete()
	if self then Polycore.delete_Rectangle(self.__ptr) end
end
