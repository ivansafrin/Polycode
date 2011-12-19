require "Polycode/EventDispatcher"

class "CoreInput" (EventDispatcher)



MOUSE_BUTTON1 = 0
MOUSE_BUTTON2 = 1
MOUSE_BUTTON3 = 2




function CoreInput:CoreInput(...)
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1]:class() == "EventDispatcher" then
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
		self.__ptr = Polycore.CoreInput(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function CoreInput:getMousePosition()
	local retVal =  Polycore.CoreInput_getMousePosition(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Vector2("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function CoreInput:getKeyState(keyCode)
	local retVal = Polycore.CoreInput_getKeyState(self.__ptr, keyCode.__ptr)
	return retVal
end

function CoreInput:getMouseDelta()
	local retVal =  Polycore.CoreInput_getMouseDelta(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Vector2("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function CoreInput:getMouseButtonState(mouseButton)
	local retVal = Polycore.CoreInput_getMouseButtonState(self.__ptr, mouseButton)
	return retVal
end

function CoreInput:getNumJoysticks()
	local retVal =  Polycore.CoreInput_getNumJoysticks(self.__ptr)
	return retVal
end

function CoreInput:getJoystickInfoByIndex(index)
	local retVal = Polycore.CoreInput_getJoystickInfoByIndex(self.__ptr, index)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = JoystickInfo("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function CoreInput:getJoystickInfoByID(deviceID)
	local retVal = Polycore.CoreInput_getJoystickInfoByID(self.__ptr, deviceID)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = JoystickInfo("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function CoreInput:addJoystick(deviceID)
	local retVal = Polycore.CoreInput_addJoystick(self.__ptr, deviceID)
end

function CoreInput:removeJoystick(deviceID)
	local retVal = Polycore.CoreInput_removeJoystick(self.__ptr, deviceID)
end

function CoreInput:joystickAxisMoved(axisID, value, deviceID)
	local retVal = Polycore.CoreInput_joystickAxisMoved(self.__ptr, axisID, value, deviceID)
end

function CoreInput:joystickButtonDown(buttonID, deviceID)
	local retVal = Polycore.CoreInput_joystickButtonDown(self.__ptr, buttonID, deviceID)
end

function CoreInput:joystickButtonUp(buttonID, deviceID)
	local retVal = Polycore.CoreInput_joystickButtonUp(self.__ptr, buttonID, deviceID)
end

function CoreInput:mouseWheelUp(ticks)
	local retVal = Polycore.CoreInput_mouseWheelUp(self.__ptr, ticks)
end

function CoreInput:mouseWheelDown(ticks)
	local retVal = Polycore.CoreInput_mouseWheelDown(self.__ptr, ticks)
end

function CoreInput:setMouseButtonState(mouseButton, state, ticks)
	local retVal = Polycore.CoreInput_setMouseButtonState(self.__ptr, mouseButton, state, ticks)
end

function CoreInput:setMousePosition(x, y, ticks)
	local retVal = Polycore.CoreInput_setMousePosition(self.__ptr, x, y, ticks)
end

function CoreInput:setKeyState(keyCode, code, newState, ticks)
	local retVal = Polycore.CoreInput_setKeyState(self.__ptr, keyCode.__ptr, code.__ptr, newState, ticks)
end

function CoreInput:setDeltaPosition(x, y)
	local retVal = Polycore.CoreInput_setDeltaPosition(self.__ptr, x, y)
end

function CoreInput:createEvent(event)
	local retVal = Polycore.CoreInput_createEvent(event.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = InputEvent("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end



function CoreInput:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_CoreInput(self.__ptr)
end
