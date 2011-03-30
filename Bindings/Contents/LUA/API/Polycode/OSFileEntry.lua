class "OSFileEntry"

function OSFileEntry:OSFileEntry()
	if self.__ptr == nil then
		self.__ptr = Polycore.OSFileEntry()
	end
end

