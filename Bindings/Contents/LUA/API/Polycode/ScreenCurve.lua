require "Polycode/ScreenShape"

class "ScreenCurve" (ScreenShape)

function ScreenCurve:ScreenCurve(curve, numVertices)
	if self.__ptr == nil then
		self.__ptr = Polycore.ScreenCurve(curve, numVertices)
	end
end

