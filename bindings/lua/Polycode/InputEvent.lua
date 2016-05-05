require "Polycode/Event"

class "InputEvent" (Event)

InputEvent.EVENTBASE_INPUTEVENT = 0x400
InputEvent.EVENT_MOUSEDOWN = InputEvent.EVENTBASE_INPUTEVENT + 0
InputEvent.EVENT_MOUSEUP = InputEvent.EVENTBASE_INPUTEVENT + 1
InputEvent.EVENT_MOUSEMOVE = InputEvent.EVENTBASE_INPUTEVENT + 2
InputEvent.EVENT_MOUSEOVER = InputEvent.EVENTBASE_INPUTEVENT + 3
InputEvent.EVENT_MOUSEOUT = InputEvent.EVENTBASE_INPUTEVENT + 4
InputEvent.EVENT_DOUBLECLICK = InputEvent.EVENTBASE_INPUTEVENT + 5
InputEvent.EVENT_MOUSEUP_OUTSIDE = InputEvent.EVENTBASE_INPUTEVENT + 6
InputEvent.EVENT_MOUSEWHEEL_UP = InputEvent.EVENTBASE_INPUTEVENT + 7
InputEvent.EVENT_MOUSEWHEEL_DOWN = InputEvent.EVENTBASE_INPUTEVENT + 8
InputEvent.EVENT_KEYDOWN = InputEvent.EVENTBASE_INPUTEVENT + 13
InputEvent.EVENT_KEYUP = InputEvent.EVENTBASE_INPUTEVENT + 14
InputEvent.EVENT_JOYBUTTON_DOWN = InputEvent.EVENTBASE_INPUTEVENT + 15
InputEvent.EVENT_JOYBUTTON_UP = InputEvent.EVENTBASE_INPUTEVENT + 16
InputEvent.EVENT_JOYAXIS_MOVED = InputEvent.EVENTBASE_INPUTEVENT + 17
InputEvent.EVENT_JOYDEVICE_ATTACHED = InputEvent.EVENTBASE_INPUTEVENT + 18
InputEvent.EVENT_JOYDEVICE_DETACHED = InputEvent.EVENTBASE_INPUTEVENT + 19
InputEvent.EVENT_TOUCHES_BEGAN = InputEvent.EVENTBASE_INPUTEVENT + 20
InputEvent.EVENT_TOUCHES_MOVED = InputEvent.EVENTBASE_INPUTEVENT + 21
InputEvent.EVENT_TOUCHES_ENDED = InputEvent.EVENTBASE_INPUTEVENT + 22

function InputEvent:__getvar(name)
	if name == "mouseButton" then
		return Polycode.InputEvent_get_mouseButton(self.__ptr)
	elseif name == "mousePosition" then
		local retVal = Polycode.InputEvent_get_mousePosition(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Vector2"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "key" then
		return Polycode.InputEvent_get_key(self.__ptr)
	elseif name == "charCode" then
		local retVal = Polycode.InputEvent_get_charCode(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["wchar_t"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "timestamp" then
		return Polycode.InputEvent_get_timestamp(self.__ptr)
	elseif name == "touch" then
		local retVal = Polycode.InputEvent_get_touch(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["TouchInfo"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "touchType" then
		return Polycode.InputEvent_get_touchType(self.__ptr)
	elseif name == "joystickDeviceID" then
		return Polycode.InputEvent_get_joystickDeviceID(self.__ptr)
	elseif name == "joystickAxisValue" then
		return Polycode.InputEvent_get_joystickAxisValue(self.__ptr)
	elseif name == "joystickButton" then
		return Polycode.InputEvent_get_joystickButton(self.__ptr)
	elseif name == "joystickAxis" then
		return Polycode.InputEvent_get_joystickAxis(self.__ptr)
	elseif name == "joystickIndex" then
		return Polycode.InputEvent_get_joystickIndex(self.__ptr)
	elseif name == "hitDistance" then
		return Polycode.InputEvent_get_hitDistance(self.__ptr)
	end
	if Event["__getvar"] ~= nil then
		return Event.__getvar(self, name)
	end
end

function InputEvent:__setvar(name,value)
	if name == "mouseButton" then
		Polycode.InputEvent_set_mouseButton(self.__ptr, value)
		return true
	elseif name == "mousePosition" then
		Polycode.InputEvent_set_mousePosition(self.__ptr, value.__ptr)
		return true
	elseif name == "key" then
		Polycode.InputEvent_set_key(self.__ptr, value)
		return true
	elseif name == "charCode" then
		Polycode.InputEvent_set_charCode(self.__ptr, value.__ptr)
		return true
	elseif name == "timestamp" then
		Polycode.InputEvent_set_timestamp(self.__ptr, value)
		return true
	elseif name == "touch" then
		Polycode.InputEvent_set_touch(self.__ptr, value.__ptr)
		return true
	elseif name == "touchType" then
		Polycode.InputEvent_set_touchType(self.__ptr, value)
		return true
	elseif name == "joystickDeviceID" then
		Polycode.InputEvent_set_joystickDeviceID(self.__ptr, value)
		return true
	elseif name == "joystickAxisValue" then
		Polycode.InputEvent_set_joystickAxisValue(self.__ptr, value)
		return true
	elseif name == "joystickButton" then
		Polycode.InputEvent_set_joystickButton(self.__ptr, value)
		return true
	elseif name == "joystickAxis" then
		Polycode.InputEvent_set_joystickAxis(self.__ptr, value)
		return true
	elseif name == "joystickIndex" then
		Polycode.InputEvent_set_joystickIndex(self.__ptr, value)
		return true
	elseif name == "hitDistance" then
		Polycode.InputEvent_set_hitDistance(self.__ptr, value)
		return true
	end
	if Event["__setvar"] ~= nil then
		return Event.__setvar(self, name, value)
	else
		return false
	end
end
function InputEvent:InputEvent(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "Event" then
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
		self.__ptr = Polycode.InputEvent(unpack(arg))
	end
end

function InputEvent:getMousePosition()
	local retVal =  Polycode.InputEvent_getMousePosition(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector2"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function InputEvent:getKey()
	local retVal =  Polycode.InputEvent_getKey(self.__ptr)
	return retVal
end

function InputEvent:getMouseButton()
	local retVal =  Polycode.InputEvent_getMouseButton(self.__ptr)
	return retVal
end

function InputEvent:getCharCode()
	local retVal =  Polycode.InputEvent_getCharCode(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["wchar_t"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function InputEvent:keyCode()
	local retVal =  Polycode.InputEvent_keyCode(self.__ptr)
	return retVal
end

function InputEvent:__delete()
	if self then Polycode.delete_InputEvent(self.__ptr) end
end
