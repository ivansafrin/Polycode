require "Polycode/EventDispatcher"

class "Screen" (EventDispatcher)



function Screen:__index__(name)
	if name == "enabled" then
		return Polycore.Screen_get_enabled(self.__ptr)
	end
end


function Screen:__set_callback(name,value)
	if name == "enabled" then
		Polycore.Screen_set_enabled(self.__ptr, value)
		return true
	end
	return false
end


function Screen:Screen(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.Screen(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function Screen:addChild(newEntity)
	local retVal = Polycore.Screen_addChild(self.__ptr, newEntity.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = ScreenEntity("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Screen:removeChild(entityToRemove)
	local retVal = Polycore.Screen_removeChild(self.__ptr, entityToRemove.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = ScreenEntity("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Screen:setScreenOffset(x, y)
	local retVal = Polycore.Screen_setScreenOffset(self.__ptr, x, y)
end

function Screen:getScreenOffset()
	local retVal =  Polycore.Screen_getScreenOffset(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Vector2("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Screen:Shutdown()
	local retVal =  Polycore.Screen_Shutdown(self.__ptr)
end

function Screen:Update()
	local retVal =  Polycore.Screen_Update(self.__ptr)
end

function Screen:getEntityAt(x, y)
	local retVal = Polycore.Screen_getEntityAt(self.__ptr, x, y)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = ScreenEntity("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Screen:Render()
	local retVal =  Polycore.Screen_Render(self.__ptr)
end

function Screen:setRenderer(r_enderer)
	local retVal = Polycore.Screen_setRenderer(self.__ptr, r_enderer.__ptr)
end

function Screen:setNormalizedCoordinates(newVal, yCoordinateSize)
	local retVal = Polycore.Screen_setNormalizedCoordinates(self.__ptr, newVal, yCoordinateSize)
end

function Screen:setScreenShader(shaderName)
	local retVal = Polycore.Screen_setScreenShader(self.__ptr, shaderName)
end

function Screen:getHighestZIndex()
	local retVal =  Polycore.Screen_getHighestZIndex(self.__ptr)
	return retVal
end

function Screen:sortChildren()
	local retVal =  Polycore.Screen_sortChildren(self.__ptr)
end

function Screen:cmpZindex(left, right)
	local retVal = Polycore.Screen_cmpZindex(left.__ptr, right.__ptr)
	return retVal
end

function Screen:handleInputEvent(inputEvent)
	local retVal = Polycore.Screen_handleInputEvent(self.__ptr, inputEvent.__ptr)
end

function Screen:hasFilterShader()
	local retVal =  Polycore.Screen_hasFilterShader(self.__ptr)
	return retVal
end

function Screen:drawFilter()
	local retVal =  Polycore.Screen_drawFilter(self.__ptr)
end

function Screen:usesNormalizedCoordinates()
	local retVal =  Polycore.Screen_usesNormalizedCoordinates(self.__ptr)
	return retVal
end

function Screen:getYCoordinateSize()
	local retVal =  Polycore.Screen_getYCoordinateSize(self.__ptr)
	return retVal
end

function Screen:getRootEntity()
	local retVal =  Polycore.Screen_getRootEntity(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = ScreenEntity("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

