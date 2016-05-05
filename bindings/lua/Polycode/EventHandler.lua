class "EventHandler"


function EventHandler:EventHandler(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.EventHandler(self)
	end
end

function EventHandler:__delete()
	if self then Polycode.delete_EventHandler(self.__ptr) end
end
