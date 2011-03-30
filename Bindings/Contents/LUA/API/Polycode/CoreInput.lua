require "Polycode/EventDispatcher"

class "CoreInput" (EventDispatcher)

function CoreInput:CoreInput()
	if self.__ptr == nil then
		self.__ptr = Polycore.CoreInput()
	end
end

function CoreInput:mouseWheelUp(ticks)
	return Polycore.CoreInput_mouseWheelUp(self.__ptr, ticks)
end

function CoreInput:mouseWheelDown(ticks)
	return Polycore.CoreInput_mouseWheelDown(self.__ptr, ticks)
end

function CoreInput:getMouseButtonState(mouseButton)
	return Polycore.CoreInput_getMouseButtonState(self.__ptr, mouseButton)
end

function CoreInput:setMouseButtonState(mouseButton, state, ticks)
	return Polycore.CoreInput_setMouseButtonState(self.__ptr, mouseButton, state, ticks)
end

function CoreInput:setMousePosition(x, y, ticks)
	return Polycore.CoreInput_setMousePosition(self.__ptr, x, y, ticks)
end

function CoreInput:getMousePosition()
	return Polycore.CoreInput_getMousePosition(self.__ptr)
end

function CoreInput:setKeyState(keyCode, code, newState, ticks)
	return Polycore.CoreInput_setKeyState(self.__ptr, keyCode.__ptr, code.__ptr, newState, ticks)
end

function CoreInput:getKeyState(keyCode)
	return Polycore.CoreInput_getKeyState(self.__ptr, keyCode.__ptr)
end

function CoreInput:getMouseDelta()
	return Polycore.CoreInput_getMouseDelta(self.__ptr)
end

function CoreInput:setDeltaPosition(x, y)
	return Polycore.CoreInput_setDeltaPosition(self.__ptr, x, y)
end

function CoreInput:createEvent(event)
	return Polycore.CoreInput_createEvent(self.__ptr, event.__ptr)
end

