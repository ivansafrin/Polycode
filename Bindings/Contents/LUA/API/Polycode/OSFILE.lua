class "OSFILE"



TYPE_FILE = 0
TYPE_ARCHIVE_FILE = 1
function OSFILE:__index__(name)
	if name == "fileType" then
		return Polycore.OSFILE_get_fileType(self.__ptr)
	end
end


function OSFILE:__set_callback(name,value)
	if name == "fileType" then
		Polycore.OSFILE_set_fileType(self.__ptr, value)
		return true
	end
	return false
end


function OSFILE:OSFILE(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.OSFILE(unpack(arg))
	end
end

function OSFILE:debugDump()
	local retVal =  Polycore.OSFILE_debugDump(self.__ptr)
end

