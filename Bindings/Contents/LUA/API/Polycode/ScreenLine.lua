require "Polycode/ScreenEntity"

class "ScreenLine" (ScreenEntity)







function ScreenLine:ScreenLine(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.ScreenLine(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function ScreenLine:Update()
	local retVal =  Polycore.ScreenLine_Update(self.__ptr)
end

function ScreenLine:Render()
	local retVal =  Polycore.ScreenLine_Render(self.__ptr)
end

function ScreenLine:setLineWidth(width)
	local retVal = Polycore.ScreenLine_setLineWidth(self.__ptr, width)
end

