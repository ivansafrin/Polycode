class "ObjectEntry"

function ObjectEntry:ObjectEntry()
	if self.__ptr == nil then
		self.__ptr = Polycore.ObjectEntry()
	end
end

function ObjectEntry:addChild(name)
	return Polycore.ObjectEntry_addChild(self.__ptr, name)
end

