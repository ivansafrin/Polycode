require "Polycode/RenderDataArray"

class "VertexDataArray" (RenderDataArray)



function VertexDataArray:__getvar(name)
	if name == "countPerVertex" then
		local retVal = Polycore.VertexDataArray_get_countPerVertex(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["char"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
	if RenderDataArray["__getvar"] ~= nil then
		return RenderDataArray.__getvar(self, name)
	end
end


function VertexDataArray:__setvar(name,value)
	if name == "countPerVertex" then
		Polycore.VertexDataArray_set_countPerVertex(self.__ptr, value.__ptr)
		return true
	end
	if RenderDataArray["__setvar"] ~= nil then
		return RenderDataArray.__setvar(self, name, value)
	else
		return false
	end
end


function VertexDataArray:VertexDataArray(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "RenderDataArray" then
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
		self.__ptr = Polycore.VertexDataArray(unpack(arg))
	end
end

function VertexDataArray:getCountPerVertex()
	local retVal =  Polycore.VertexDataArray_getCountPerVertex(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["unsignedchar"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function VertexDataArray:getArrayData()
	local retVal =  Polycore.VertexDataArray_getArrayData(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["void"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function VertexDataArray:getDataSize()
	local retVal =  Polycore.VertexDataArray_getDataSize(self.__ptr)
	return retVal
end

function VertexDataArray:__delete()
	if self then Polycore.delete_VertexDataArray(self.__ptr) end
end
