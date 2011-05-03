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
function InputEvent:__index__(name)
	if name == "mouseButton" then
		return Polycore.InputEvent_get_mouseButton(self.__ptr)
	elseif name == "timestamp" then
		return Polycore.InputEvent_get_timestamp(self.__ptr)
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
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.InputEvent(unpack(arg))
	end
end

function InputEvent:keyCode()
	local retVal =  Polycore.InputEvent_keyCode(self.__ptr)
	return retVal
end

