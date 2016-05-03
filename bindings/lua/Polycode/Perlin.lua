class "Perlin"







function Perlin:Perlin(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.Perlin(unpack(arg))
	end
end

function Perlin:Get2DTiledX(x, y, t)
	local retVal = Polycore.Perlin_Get2DTiledX(self.__ptr, x, y, t)
	return retVal
end

function Perlin:Get(x, y)
	local retVal = Polycore.Perlin_Get(self.__ptr, x, y)
	return retVal
end

function Perlin:Get2D(x, y)
	local retVal = Polycore.Perlin_Get2D(self.__ptr, x, y)
	return retVal
end

function Perlin:Get3D(x, y, z)
	local retVal = Polycore.Perlin_Get3D(self.__ptr, x, y, z)
	return retVal
end

function Perlin:__delete()
	if self then Polycore.delete_Perlin(self.__ptr) end
end
