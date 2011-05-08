require "Polycode/Resource"

class "Shader" (Resource)



FIXED_SHADER = 0
MODULE_SHADER = 1




function Shader:getType()
	local retVal =  Polycore.Shader_getType(self.__ptr)
	return retVal
end

function Shader:setName(name)
	local retVal = Polycore.Shader_setName(self.__ptr, name)
end

function Shader:getName()
	local retVal =  Polycore.Shader_getName(self.__ptr)
	return retVal
end

function Shader:createBinding()
	local retVal =  Polycore.Shader_createBinding(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = ShaderBinding("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end



function Shader:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_Shader(self.__ptr)
end
