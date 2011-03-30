require "Polycode/Entity"

class "ScreenEntity" (Entity)

function ScreenEntity:ScreenEntity()
	if self.__ptr == nil then
		self.__ptr = Polycore.ScreenEntity()
	end
end

function ScreenEntity:setPosition(x, y)
	return Polycore.ScreenEntity_setPosition(self.__ptr, x, y)
end

function ScreenEntity:setScale(x, y)
	return Polycore.ScreenEntity_setScale(self.__ptr, x, y)
end

function ScreenEntity:setRotation(roatation)
	return Polycore.ScreenEntity_setRotation(self.__ptr, roatation)
end

function ScreenEntity:getRotation()
	return Polycore.ScreenEntity_getRotation(self.__ptr)
end

function ScreenEntity:_onMouseDown(x, y, mouseButton, timestamp)
	return Polycore.ScreenEntity__onMouseDown(self.__ptr, x, y, mouseButton, timestamp)
end

function ScreenEntity:_onMouseUp(x, y, mouseButton, timestamp)
	return Polycore.ScreenEntity__onMouseUp(self.__ptr, x, y, mouseButton, timestamp)
end

function ScreenEntity:_onMouseMove(x, y, timestamp)
	return Polycore.ScreenEntity__onMouseMove(self.__ptr, x, y, timestamp)
end

function ScreenEntity:_onMouseWheelUp(x, y, timestamp)
	return Polycore.ScreenEntity__onMouseWheelUp(self.__ptr, x, y, timestamp)
end

function ScreenEntity:_onMouseWheelDown(x, y, timestamp)
	return Polycore.ScreenEntity__onMouseWheelDown(self.__ptr, x, y, timestamp)
end

function ScreenEntity:onMouseDown(x, y)
	return Polycore.ScreenEntity_onMouseDown(self.__ptr, x, y)
end

function ScreenEntity:onMouseUp(x, y)
	return Polycore.ScreenEntity_onMouseUp(self.__ptr, x, y)
end

function ScreenEntity:onMouseMove(x, y)
	return Polycore.ScreenEntity_onMouseMove(self.__ptr, x, y)
end

function ScreenEntity:onMouseWheelUp(x, y)
	return Polycore.ScreenEntity_onMouseWheelUp(self.__ptr, x, y)
end

function ScreenEntity:onMouseWheelDown(x, y)
	return Polycore.ScreenEntity_onMouseWheelDown(self.__ptr, x, y)
end

function ScreenEntity:_onKeyDown(key, charCode)
	return Polycore.ScreenEntity__onKeyDown(self.__ptr, key.__ptr, charCode.__ptr)
end

function ScreenEntity:_onKeyUp(key, charCode)
	return Polycore.ScreenEntity__onKeyUp(self.__ptr, key.__ptr, charCode.__ptr)
end

function ScreenEntity:onKeyDown(key, charCode)
	return Polycore.ScreenEntity_onKeyDown(self.__ptr, key.__ptr, charCode.__ptr)
end

function ScreenEntity:onKeyUp(key, charCode)
	return Polycore.ScreenEntity_onKeyUp(self.__ptr, key.__ptr, charCode.__ptr)
end

function ScreenEntity:hitTest(x, y)
	return Polycore.ScreenEntity_hitTest(self.__ptr, x, y)
end

function ScreenEntity:buildPositionMatrix()
	return Polycore.ScreenEntity_buildPositionMatrix(self.__ptr)
end

function ScreenEntity:adjustMatrixForChildren()
	return Polycore.ScreenEntity_adjustMatrixForChildren(self.__ptr)
end

function ScreenEntity:getWidth()
	return Polycore.ScreenEntity_getWidth(self.__ptr)
end

function ScreenEntity:getHeight()
	return Polycore.ScreenEntity_getHeight(self.__ptr)
end

function ScreenEntity:setWidth(w)
	return Polycore.ScreenEntity_setWidth(self.__ptr, w)
end

function ScreenEntity:setHeight(h)
	return Polycore.ScreenEntity_setHeight(self.__ptr, h)
end

function ScreenEntity:onGainFocus()
	return Polycore.ScreenEntity_onGainFocus(self.__ptr)
end

function ScreenEntity:onLoseFocus()
	return Polycore.ScreenEntity_onLoseFocus(self.__ptr)
end

function ScreenEntity:startDrag(xOffset, yOffset)
	return Polycore.ScreenEntity_startDrag(self.__ptr, xOffset, yOffset)
end

function ScreenEntity:stopDrag()
	return Polycore.ScreenEntity_stopDrag(self.__ptr)
end

function ScreenEntity:setBlendingMode(newBl_endingMode)
	return Polycore.ScreenEntity_setBlendingMode(self.__ptr, newBl_endingMode)
end

function ScreenEntity:setPositionMode(newPositionMode)
	return Polycore.ScreenEntity_setPositionMode(self.__ptr, newPositionMode)
end

function ScreenEntity:setDragLimits(rect)
	return Polycore.ScreenEntity_setDragLimits(self.__ptr, rect.__ptr)
end

function ScreenEntity:clearDragLimits()
	return Polycore.ScreenEntity_clearDragLimits(self.__ptr)
end

function ScreenEntity:focusChild(child)
	return Polycore.ScreenEntity_focusChild(self.__ptr, child.__ptr)
end

function ScreenEntity:focusNextChild()
	return Polycore.ScreenEntity_focusNextChild(self.__ptr)
end

function ScreenEntity:getPosition2D()
	return Polycore.ScreenEntity_getPosition2D(self.__ptr)
end

function ScreenEntity:isFocusable()
	return Polycore.ScreenEntity_isFocusable(self.__ptr)
end

