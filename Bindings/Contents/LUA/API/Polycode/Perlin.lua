class "Perlin"







function Perlin:Perlin(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.Perlin(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function Perlin:Get(x, y)
	local retVal = Polycore.Perlin_Get(self.__ptr, x, y)
	return retVal
end

