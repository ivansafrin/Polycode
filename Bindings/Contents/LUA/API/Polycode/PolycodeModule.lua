class "PolycodeModule"

function PolycodeModule:PolycodeModule()
	if self.__ptr == nil then
		self.__ptr = Polycore.PolycodeModule()
	end
end

function PolycodeModule:getType()
	return Polycore.PolycodeModule_getType(self.__ptr)
end

