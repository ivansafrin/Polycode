class "Logger"







function Logger:Logger(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.Logger(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function Logger:log(format)
	local retVal = Polycore.Logger_log(format.__ptr)
end

function Logger:logw(str)
	local retVal = Polycore.Logger_logw(str.__ptr)
end

