class "PolycodeViewBase"







function PolycodeViewBase:PolycodeViewBase(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.PolycodeViewBase(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end



function PolycodeViewBase:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_PolycodeViewBase(self.__ptr)
end
