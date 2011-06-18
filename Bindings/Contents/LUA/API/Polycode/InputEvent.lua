require "Polycode/Event"

class "InputEvent" (Event)



EVENT_MOUSEDOWN = 0
EVENT_MOUSEUP = 1
EVENT_MOUSEMOVE = 2
EVENT_MOUSEOVER = 3
EVENT_MOUSEOUT = 4
EVENT_DOUBLECLICK = 5
EVENT_MOUSEUP_OUTSIDE = 6
EVENT_MOUSEWHEEL_UP = 7
EVENT_MOUSEWHEEL_DOWN = 8
EVENT_KEYDOWN = 13
EVENT_KEYUP = 14
EVENT_JOYBUTTON_DOWN = 15
EVENT_JOYBUTTON_UP = 16
EVENT_JOYAXIS_MOVED = 17
EVENT_JOYDEVICE_ATTACHED = 18
EVENT_JOYDEVICE_DETACHED = 19
function InputEvent:__index__(name)
	if name == "mouseButton" then
		return Polycore.InputEvent_get_mouseButton(self.__ptr)
	elseif name == "mousePosition" then
		retVal = Polycore.InputEvent_get_mousePosition(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = Vector2("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "key" then
		retVal = Polycore.InputEvent_get_key(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = PolyKEY("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "charCode" then
		retVal = Polycore.InputEvent_get_charCode(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = wchar_t("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "timestamp" then
		return Polycore.InputEvent_get_timestamp(self.__ptr)
	elseif name == "joystickDeviceID" then
		retVal = Polycore.InputEvent_get_joystickDeviceID(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = unsigned int("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "joystickAxisValue" then
		retVal = Polycore.InputEvent_get_joystickAxisValue(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = float("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "joystickButton" then
		retVal = Polycore.InputEvent_get_joystickButton(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = unsigned int("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "joystickAxis" then
		retVal = Polycore.InputEvent_get_joystickAxis(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = unsigned int("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	end
end


function InputEvent:__set_callback(name,value)
	if name == "mouseButton" then
		Polycore.InputEvent_set_mouseButton(self.__ptr, value)
		return true
	elseif name == "timestamp" then
		Polycore.InputEvent_set_timestamp(self.__ptr, value)
		return true
	end
	return false
end


function InputEvent:InputEvent(...)
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1]:class() == "Event" then
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
		self.__ptr = Polycore.InputEvent(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function InputEvent:getMousePosition()
	local retVal =  Polycore.InputEvent_getMousePosition(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Vector2("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function InputEvent:getKey()
	local retVal =  Polycore.InputEvent_getKey(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = PolyKEY("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function InputEvent:getMouseButton()
	local retVal =  Polycore.InputEvent_getMouseButton(self.__ptr)
	return retVal
end

function InputEvent:keyCode()
	local retVal =  Polycore.InputEvent_keyCode(self.__ptr)
	return retVal
end



function InputEvent:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_InputEvent(self.__ptr)
end
