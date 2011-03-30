require "Polycode/EventDispatcher"

class "Screen" (EventDispatcher)

function Screen:Screen()
	if self.__ptr == nil then
		self.__ptr = Polycore.Screen()
	end
end

function Screen:addChild(newEntity)
	return Polycore.Screen_addChild(self.__ptr, newEntity.__ptr)
end

function Screen:removeChild(entityToRemove)
	return Polycore.Screen_removeChild(self.__ptr, entityToRemove.__ptr)
end

function Screen:setScreenOffset(x, y)
	return Polycore.Screen_setScreenOffset(self.__ptr, x, y)
end

function Screen:getScreenOffset()
	return Polycore.Screen_getScreenOffset(self.__ptr)
end

function Screen:Shutdown()
	return Polycore.Screen_Shutdown(self.__ptr)
end

function Screen:Update()
	return Polycore.Screen_Update(self.__ptr)
end

function Screen:getEntityAt(x, y)
	return Polycore.Screen_getEntityAt(self.__ptr, x, y)
end

function Screen:Render()
	return Polycore.Screen_Render(self.__ptr)
end

function Screen:setRenderer(r_enderer)
	return Polycore.Screen_setRenderer(self.__ptr, r_enderer.__ptr)
end

function Screen:setNormalizedCoordinates(newVal, yCoordinateSize)
	return Polycore.Screen_setNormalizedCoordinates(self.__ptr, newVal, yCoordinateSize)
end

function Screen:setScreenShader(shaderName)
	return Polycore.Screen_setScreenShader(self.__ptr, shaderName)
end

function Screen:handleEvent(event)
	return Polycore.Screen_handleEvent(self.__ptr, event.__ptr)
end

function Screen:getHighestZIndex()
	return Polycore.Screen_getHighestZIndex(self.__ptr)
end

function Screen:sortChildren()
	return Polycore.Screen_sortChildren(self.__ptr)
end

function Screen:cmpZindex(left, right)
	return Polycore.Screen_cmpZindex(self.__ptr, left.__ptr, right.__ptr)
end

function Screen:handleInputEvent(inputEvent)
	return Polycore.Screen_handleInputEvent(self.__ptr, inputEvent.__ptr)
end

function Screen:hasFilterShader()
	return Polycore.Screen_hasFilterShader(self.__ptr)
end

function Screen:drawFilter()
	return Polycore.Screen_drawFilter(self.__ptr)
end

function Screen:usesNormalizedCoordinates()
	return Polycore.Screen_usesNormalizedCoordinates(self.__ptr)
end

function Screen:getYCoordinateSize()
	return Polycore.Screen_getYCoordinateSize(self.__ptr)
end

function Screen:getRootEntity()
	return Polycore.Screen_getRootEntity(self.__ptr)
end

