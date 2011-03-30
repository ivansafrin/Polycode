class "OSFILE"

function OSFILE:OSFILE()
	if self.__ptr == nil then
		self.__ptr = Polycore.OSFILE()
	end
end

function OSFILE:debugDump()
	return Polycore.OSFILE_debugDump(self.__ptr)
end

