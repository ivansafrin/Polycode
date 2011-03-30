class "Vector2"

function Vector2:Vector2()
	if self.__ptr == nil then
		self.__ptr = Polycore.Vector2()
	end
end

