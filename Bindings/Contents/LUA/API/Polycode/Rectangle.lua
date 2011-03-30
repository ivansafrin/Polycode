class "Rectangle"

function Rectangle:Rectangle()
	if self.__ptr == nil then
		self.__ptr = Polycore.Rectangle()
	end
end

function Rectangle:setRect(x, y, w, h)
	return Polycore.Rectangle_setRect(self.__ptr, x, y, w, h)
end

