require "Polycode/Resource"

class "ShaderProgram" (Resource)



ShaderProgram.TYPE_VERT = 0
ShaderProgram.TYPE_FRAG = 1
function ShaderProgram:__getvar(name)
	if name == "type" then
		return Polycore.ShaderProgram_get_type(self.__ptr)
	end
	if Resource["__getvar"] ~= nil then
		return Resource.__getvar(self, name)
	end
end


function ShaderProgram:__setvar(name,value)
	if name == "type" then
		Polycore.ShaderProgram_set_type(self.__ptr, value)
		return true
	end
	if Resource["__setvar"] ~= nil then
		return Resource.__setvar(self, name, value)
	else
		return false
	end
end


function ShaderProgram:ShaderProgram(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "Resource" then
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
		self.__ptr = Polycore.ShaderProgram(unpack(arg))
	end
end

function ShaderProgram:reloadProgram()
	local retVal =  Polycore.ShaderProgram_reloadProgram(self.__ptr)
end

function ShaderProgram:reloadResource()
	local retVal =  Polycore.ShaderProgram_reloadResource(self.__ptr)
end

function ShaderProgram:__delete()
	if self then Polycore.delete_ShaderProgram(self.__ptr) end
end
