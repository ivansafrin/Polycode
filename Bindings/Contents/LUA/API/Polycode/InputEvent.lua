require "Polycode/Event"

class "InputEvent" (Event)

function InputEvent:InputEvent(mousePosition, timestamp)
	if self.__ptr == nil then
		self.__ptr = Polycore.InputEvent(mousePosition, timestamp)
	end
end

function InputEvent:keyCode()
	return Polycore.InputEvent_keyCode(self.__ptr)
end

