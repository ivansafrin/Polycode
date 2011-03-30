class "FixedShader"

function FixedShader:FixedShader()
	if self.__ptr == nil then
		self.__ptr = Polycore.FixedShader()
	end
end

function FixedShader:createBinding()
	return Polycore.FixedShader_createBinding(self.__ptr)
end

