require "Polycode/Resource"

class "Cubemap" (Resource)

function Cubemap:Cubemap(t0, t1, t2, t3, t4, t5)
	if self.__ptr == nil then
		self.__ptr = Polycore.Cubemap(t0, t1, t2, t3, t4, t5)
	end
end

