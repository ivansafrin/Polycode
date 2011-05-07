require "Polycode/Entity"

class "ScreenEntity" (Entity)



POSITION_TOPLEFT = 0
POSITION_CENTER = 1
function ScreenEntity:__index__(name)
	if name == "hasFocus" then
		return Polycore.ScreenEntity_get_hasFocus(self.__ptr)
	elseif name == "blockMouseInput" then
		return Polycore.ScreenEntity_get_blockMouseInput(self.__ptr)
	elseif name == "zindex" then
		return Polycore.ScreenEntity_get_zindex(self.__ptr)
	elseif name == "snapToPixels" then
		return Polycore.ScreenEntity_get_snapToPixels(self.__ptr)
	end
end


function ScreenEntity:__set_callback(name,value)
	if name == "hasFocus" then
		Polycore.ScreenEntity_set_hasFocus(self.__ptr, value)
		return true
	elseif name == "blockMouseInput" then
		Polycore.ScreenEntity_set_blockMouseInput(self.__ptr, value)
		return true
	elseif name == "zindex" then
		Polycore.ScreenEntity_set_zindex(self.__ptr, value)
		return true
	elseif name == "snapToPixels" then
		Polycore.ScreenEntity_set_snapToPixels(self.__ptr, value)
		return true
	end
	return false
end


function ScreenEntity:ScreenEntity(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.ScreenEntity(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function ScreenEntity:setPosition(x, y)
	local retVal = Polycore.ScreenEntity_setPosition(self.__ptr, x, y)
end

function ScreenEntity:setScale(x, y)
	local retVal = Polycore.ScreenEntity_setScale(self.__ptr, x, y)
end

function ScreenEntity:setRotation(roatation)
	local retVal = Polycore.ScreenEntity_setRotation(self.__ptr, roatation)
end

function ScreenEntity:getRotation()
	local retVal =  Polycore.ScreenEntity_getRotation(self.__ptr)
	return retVal
end

function ScreenEntity:_onMouseDown(x, y, mouseButton, timestamp)
	local retVal = Polycore.ScreenEntity__onMouseDown(self.__ptr, x, y, mouseButton, timestamp)
	return retVal
end

function ScreenEntity:_onMouseUp(x, y, mouseButton, timestamp)
	local retVal = Polycore.ScreenEntity__onMouseUp(self.__ptr, x, y, mouseButton, timestamp)
	return retVal
end

function ScreenEntity:_onMouseMove(x, y, timestamp)
	local retVal = Polycore.ScreenEntity__onMouseMove(self.__ptr, x, y, timestamp)
end

function ScreenEntity:_onMouseWheelUp(x, y, timestamp)
	local retVal = Polycore.ScreenEntity__onMouseWheelUp(self.__ptr, x, y, timestamp)
end

function ScreenEntity:_onMouseWheelDown(x, y, timestamp)
	local retVal = Polycore.ScreenEntity__onMouseWheelDown(self.__ptr, x, y, timestamp)
end

function ScreenEntity:onMouseDown(x, y)
	local retVal = Polycore.ScreenEntity_onMouseDown(self.__ptr, x, y)
end

function ScreenEntity:onMouseUp(x, y)
	local retVal = Polycore.ScreenEntity_onMouseUp(self.__ptr, x, y)
end

function ScreenEntity:onMouseMove(x, y)
	local retVal = Polycore.ScreenEntity_onMouseMove(self.__ptr, x, y)
end

function ScreenEntity:onMouseWheelUp(x, y)
	local retVal = Polycore.ScreenEntity_onMouseWheelUp(self.__ptr, x, y)
end

function ScreenEntity:onMouseWheelDown(x, y)
	local retVal = Polycore.ScreenEntity_onMouseWheelDown(self.__ptr, x, y)
end

function ScreenEntity:_onKeyDown(key, charCode)
	local retVal = Polycore.ScreenEntity__onKeyDown(self.__ptr, key.__ptr, charCode.__ptr)
end

function ScreenEntity:_onKeyUp(key, charCode)
	local retVal = Polycore.ScreenEntity__onKeyUp(self.__ptr, key.__ptr, charCode.__ptr)
end

function ScreenEntity:onKeyDown(key, charCode)
	local retVal = Polycore.ScreenEntity_onKeyDown(self.__ptr, key.__ptr, charCode.__ptr)
end

function ScreenEntity:onKeyUp(key, charCode)
	local retVal = Polycore.ScreenEntity_onKeyUp(self.__ptr, key.__ptr, charCode.__ptr)
end

function ScreenEntity:hitTest(x, y)
	local retVal = Polycore.ScreenEntity_hitTest(self.__ptr, x, y)
	return retVal
end

function ScreenEntity:buildPositionMatrix()
	local retVal =  Polycore.ScreenEntity_buildPositionMatrix(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Matrix4("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function ScreenEntity:adjustMatrixForChildren()
	local retVal =  Polycore.ScreenEntity_adjustMatrixForChildren(self.__ptr)
end

function ScreenEntity:getWidth()
	local retVal =  Polycore.ScreenEntity_getWidth(self.__ptr)
	return retVal
end

function ScreenEntity:getHeight()
	local retVal =  Polycore.ScreenEntity_getHeight(self.__ptr)
	return retVal
end

function ScreenEntity:setWidth(w)
	local retVal = Polycore.ScreenEntity_setWidth(self.__ptr, w)
end

function ScreenEntity:setHeight(h)
	local retVal = Polycore.ScreenEntity_setHeight(self.__ptr, h)
end

function ScreenEntity:onGainFocus()
	local retVal =  Polycore.ScreenEntity_onGainFocus(self.__ptr)
end

function ScreenEntity:onLoseFocus()
	local retVal =  Polycore.ScreenEntity_onLoseFocus(self.__ptr)
end

function ScreenEntity:startDrag(xOffset, yOffset)
	local retVal = Polycore.ScreenEntity_startDrag(self.__ptr, xOffset, yOffset)
end

function ScreenEntity:stopDrag()
	local retVal =  Polycore.ScreenEntity_stopDrag(self.__ptr)
end

function ScreenEntity:setBlendingMode(newBl_endingMode)
	local retVal = Polycore.ScreenEntity_setBlendingMode(self.__ptr, newBl_endingMode)
end

function ScreenEntity:setPositionMode(newPositionMode)
	local retVal = Polycore.ScreenEntity_setPositionMode(self.__ptr, newPositionMode)
end

function ScreenEntity:setDragLimits(rect)
	local retVal = Polycore.ScreenEntity_setDragLimits(self.__ptr, rect.__ptr)
end

function ScreenEntity:clearDragLimits()
	local retVal =  Polycore.ScreenEntity_clearDragLimits(self.__ptr)
end

function ScreenEntity:focusChild(child)
	local retVal = Polycore.ScreenEntity_focusChild(self.__ptr, child.__ptr)
end

function ScreenEntity:focusNextChild()
	local retVal =  Polycore.ScreenEntity_focusNextChild(self.__ptr)
end

function ScreenEntity:getPosition2D()
	local retVal =  Polycore.ScreenEntity_getPosition2D(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Vector2("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function ScreenEntity:isFocusable()
	local retVal =  Polycore.ScreenEntity_isFocusable(self.__ptr)
	return retVal
end

