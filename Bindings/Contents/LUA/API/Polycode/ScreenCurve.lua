require "Polycode/ScreenShape"

class "ScreenCurve" (ScreenShape)







function ScreenCurve:ScreenCurve(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.ScreenCurve(unpack(arg))
	end
end

