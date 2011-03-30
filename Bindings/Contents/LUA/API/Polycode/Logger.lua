class "Logger"

function Logger:Logger()
	if self.__ptr == nil then
		self.__ptr = Polycore.Logger()
	end
end

function Logger:log(format)
	return Polycore.Logger_log(self.__ptr, format.__ptr)
end

function Logger:logw(str)
	return Polycore.Logger_logw(self.__ptr, str.__ptr)
end

