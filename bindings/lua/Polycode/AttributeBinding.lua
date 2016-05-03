class "AttributeBinding"



function AttributeBinding:__getvar(name)
	if name == "name" then
		return Polycore.AttributeBinding_get_name(self.__ptr)
	elseif name == "vertexData" then
		local retVal = Polycore.AttributeBinding_get_vertexData(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["VertexDataArray"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "attribute" then
		local retVal = Polycore.AttributeBinding_get_attribute(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["ProgramAttribute"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "enabled" then
		return Polycore.AttributeBinding_get_enabled(self.__ptr)
	end
end


function AttributeBinding:__setvar(name,value)
	if name == "name" then
		Polycore.AttributeBinding_set_name(self.__ptr, value)
		return true
	elseif name == "enabled" then
		Polycore.AttributeBinding_set_enabled(self.__ptr, value)
		return true
	end
	return false
end


function AttributeBinding:AttributeBinding(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.AttributeBinding(unpack(arg))
	end
end

function AttributeBinding:__delete()
	if self then Polycore.delete_AttributeBinding(self.__ptr) end
end
