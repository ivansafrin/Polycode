require "Polycode/Resource"

class "GLSLProgram" (Resource)



TYPE_VERT = 0
TYPE_FRAG = 1
function GLSLProgram:__index__(name)
	if name == "type" then
		return Polycore.GLSLProgram_get_type(self.__ptr)
	end
end


function GLSLProgram:__set_callback(name,value)
	if name == "type" then
		Polycore.GLSLProgram_set_type(self.__ptr, value)
		return true
	end
	return false
end


function GLSLProgram:GLSLProgram(...)
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1]:class() == "Resource" then
			self.__ptr = arg[1].__ptr
			return
		end
	end
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.GLSLProgram(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function GLSLProgram:addParam(name, isAuto, autoID, paramType, defaultData)
	local retVal = Polycore.GLSLProgram_addParam(self.__ptr, name, isAuto, autoID, paramType, defaultData.__ptr)
end



function GLSLProgram:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_GLSLProgram(self.__ptr)
end
