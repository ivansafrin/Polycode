class "Perlin"

function Perlin:Perlin(octaves, freq, amp, seed)
	if self.__ptr == nil then
		self.__ptr = Polycore.Perlin(octaves, freq, amp, seed)
	end
end

function Perlin:Get(x, y)
	return Polycore.Perlin_Get(self.__ptr, x, y)
end

