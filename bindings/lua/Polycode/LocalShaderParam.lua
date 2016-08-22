class "LocalShaderParam"


function LocalShaderParam:__getvar(name)
	if name == "name" then
		return Polycode.LocalShaderParam_get_name(self.__ptr)
	elseif name == "type" then
		return Polycode.LocalShaderParam_get_type(self.__ptr)
	elseif name == "ownsPointer" then
		return Polycode.LocalShaderParam_get_ownsPointer(self.__ptr)
	elseif name == "arraySize" then
		return Polycode.LocalShaderParam_get_arraySize(self.__ptr)
	end
end

function LocalShaderParam:__setvar(name,value)
	if name == "name" then
		Polycode.LocalShaderParam_set_name(self.__ptr, value)
		return true
	elseif name == "type" then
		Polycode.LocalShaderParam_set_type(self.__ptr, value)
		return true
	elseif name == "ownsPointer" then
		Polycode.LocalShaderParam_set_ownsPointer(self.__ptr, value)
		return true
	elseif name == "arraySize" then
		Polycode.LocalShaderParam_set_arraySize(self.__ptr, value)
		return true
	end
	return false
end
function LocalShaderParam:LocalShaderParam(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.LocalShaderParam(unpack(arg))
	end
end

function LocalShaderParam:Copy()
	local retVal =  Polycode.LocalShaderParam_Copy(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["shared_ptr<LocalShaderParam>"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function LocalShaderParam:getNumber()
	local retVal =  Polycode.LocalShaderParam_getNumber(self.__ptr)
	return retVal
end

function LocalShaderParam:getVector2()
	local retVal =  Polycode.LocalShaderParam_getVector2(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector2"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function LocalShaderParam:getVector3()
	local retVal =  Polycode.LocalShaderParam_getVector3(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function LocalShaderParam:getMatrix4()
	local retVal =  Polycode.LocalShaderParam_getMatrix4(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function LocalShaderParam:getColor()
	local retVal =  Polycode.LocalShaderParam_getColor(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Color"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function LocalShaderParam:setNumber(x)
	local retVal = Polycode.LocalShaderParam_setNumber(self.__ptr, x)
end

function LocalShaderParam:setVector2(x)
	local retVal = Polycode.LocalShaderParam_setVector2(self.__ptr, x.__ptr)
end

function LocalShaderParam:setVector3(x)
	local retVal = Polycode.LocalShaderParam_setVector3(self.__ptr, x.__ptr)
end

function LocalShaderParam:setMatrix4(x)
	local retVal = Polycode.LocalShaderParam_setMatrix4(self.__ptr, x.__ptr)
end

function LocalShaderParam:setMatrix4Array(x)
	local retVal = Polycode.LocalShaderParam_setMatrix4Array(self.__ptr, x.__ptr)
end

function LocalShaderParam:setColor(x)
	local retVal = Polycode.LocalShaderParam_setColor(self.__ptr, x.__ptr)
end

function LocalShaderParam:setTexture(texture)
	local retVal = Polycode.LocalShaderParam_setTexture(self.__ptr, texture.__ptr)
end

function LocalShaderParam:getTexture()
	local retVal =  Polycode.LocalShaderParam_getTexture(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["shared_ptr<Texture>"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function LocalShaderParam:setCubemap(cubemap)
	local retVal = Polycode.LocalShaderParam_setCubemap(self.__ptr, cubemap.__ptr)
end

function LocalShaderParam:getCubemap()
	local retVal =  Polycode.LocalShaderParam_getCubemap(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["shared_ptr<Cubemap>"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function LocalShaderParam:__delete()
	if self then Polycode.delete_LocalShaderParam(self.__ptr) end
end
