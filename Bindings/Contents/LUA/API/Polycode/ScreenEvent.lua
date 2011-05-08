require "Polycode/Event"

class "ScreenEvent" (Event)



ENTITY_MOVE_TOP = 0
ENTITY_MOVE_BOTTOM = 1
ENTITY_MOVE_UP = 2
ENTITY_MOVE_DOWN = 3




function ScreenEvent:ScreenEvent(...)
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
		self.__ptr = Polycore.ScreenEvent(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end



function ScreenEvent:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_ScreenEvent(self.__ptr)
end
