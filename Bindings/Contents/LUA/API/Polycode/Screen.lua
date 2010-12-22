
class "Screen"

function Screen:Screen()
	self.__ptr = Polycore.Screen()
end

function addChild(child)
	Polycore.Screen_addChild(self.__ptr, child.__ptr)
end