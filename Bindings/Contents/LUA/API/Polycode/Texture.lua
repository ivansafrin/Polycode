require "Polycode/Resource"

class "Texture" (Resource)



function Texture:__index__(name)
	if name == "scrollSpeedX" then
		return Polycore.Texture_get_scrollSpeedX(self.__ptr)
	elseif name == "scrollSpeedY" then
		return Polycore.Texture_get_scrollSpeedY(self.__ptr)
	elseif name == "clamp" then
		return Polycore.Texture_get_clamp(self.__ptr)
	end
end


function Texture:__set_callback(name,value)
	if name == "scrollSpeedX" then
		Polycore.Texture_set_scrollSpeedX(self.__ptr, value)
		return true
	elseif name == "scrollSpeedY" then
		Polycore.Texture_set_scrollSpeedY(self.__ptr, value)
		return true
	elseif name == "clamp" then
		Polycore.Texture_set_clamp(self.__ptr, value)
		return true
	end
	return false
end


function Texture:setTextureData(data)
	local retVal = Polycore.Texture_setTextureData(self.__ptr, data.__ptr)
end

function Texture:recreateFromImageData()
	local retVal =  Polycore.Texture_recreateFromImageData(self.__ptr)
end

function Texture:getScrollOffsetX()
	local retVal =  Polycore.Texture_getScrollOffsetX(self.__ptr)
	return retVal
end

function Texture:getScrollOffsetY()
	local retVal =  Polycore.Texture_getScrollOffsetY(self.__ptr)
	return retVal
end

function Texture:setImageData(data)
	local retVal = Polycore.Texture_setImageData(self.__ptr, data.__ptr)
end

function Texture:updateScroll(elapsed)
	local retVal = Polycore.Texture_updateScroll(self.__ptr, elapsed)
end

function Texture:setResourcePath(newPath)
	local retVal = Polycore.Texture_setResourcePath(self.__ptr, newPath)
end

function Texture:getResourcePath()
	local retVal =  Polycore.Texture_getResourcePath(self.__ptr)
	return retVal
end

function Texture:getTextureData()
	local retVal =  Polycore.Texture_getTextureData(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = char("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Texture:getWidth()
	local retVal =  Polycore.Texture_getWidth(self.__ptr)
	return retVal
end

function Texture:getHeight()
	local retVal =  Polycore.Texture_getHeight(self.__ptr)
	return retVal
end



function Texture:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_Texture(self.__ptr)
end
