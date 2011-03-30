require "Polycode/Event"

class "ScreenEvent" (Event)

function ScreenEvent:ScreenEvent()
	if self.__ptr == nil then
		self.__ptr = Polycore.ScreenEvent()
	end
end

