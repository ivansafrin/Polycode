require "Polycode/Resource"

class "Shader" (Resource)



FIXED_SHADER = 0
MODULE_SHADER = 1
function Shader:__index__(name)
	if name == "numSpotLights" then
		return Polycore.Shader_get_numSpotLights(self.__ptr)
	elseif name == "numAreaLights" then
		return Polycore.Shader_get_numAreaLights(self.__ptr)
	end
end


function Shader:__set_callback(name,value)
	if name == "numSpotLights" then
		Polycore.Shader_set_numSpotLights(self.__ptr, value)
		return true
	elseif name == "numAreaLights" then
		Polycore.Shader_set_numAreaLights(self.__ptr, value)
		return true
	end
	return false
end


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
	if retVal == nil then return nil end
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
