require "Polycode/ScreenEntity"

class "ScreenLine" (ScreenEntity)

function ScreenLine:ScreenLine(start, _end)
	if self.__ptr == nil then
		self.__ptr = Polycore.ScreenLine(start, _end)
	end
end

function ScreenLine:Update()
	return Polycore.ScreenLine_Update(self.__ptr)
end

function ScreenLine:Render()
	return Polycore.ScreenLine_Render(self.__ptr)
end

function ScreenLine:setLineWidth(width)
	return Polycore.ScreenLine_setLineWidth(self.__ptr, width)
end

