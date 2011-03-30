require "Polycode/ScreenMesh"

class "ScreenShape" (ScreenMesh)

function ScreenShape:ScreenShape(shapeType, option1, option2, option3, option4)
	if self.__ptr == nil then
		self.__ptr = Polycore.ScreenShape(shapeType, option1, option2, option3, option4)
	end
end

function ScreenShape:Render()
	return Polycore.ScreenShape_Render(self.__ptr)
end

function ScreenShape:setStrokeColor(r, g, b, a)
	return Polycore.ScreenShape_setStrokeColor(self.__ptr, r, g, b, a)
end

function ScreenShape:setStrokeWidth(width)
	return Polycore.ScreenShape_setStrokeWidth(self.__ptr, width)
end

function ScreenShape:setGradient(r1, g1, b1, a1, r2, g2, b2, a2)
	return Polycore.ScreenShape_setGradient(self.__ptr, r1, g1, b1, a1, r2, g2, b2, a2)
end

function ScreenShape:clearGradient()
	return Polycore.ScreenShape_clearGradient(self.__ptr)
end

function ScreenShape:setShapeSize(newWidth, newHeight)
	return Polycore.ScreenShape_setShapeSize(self.__ptr, newWidth, newHeight)
end

function ScreenShape:addShapePoint(x, y)
	return Polycore.ScreenShape_addShapePoint(self.__ptr, x, y)
end

