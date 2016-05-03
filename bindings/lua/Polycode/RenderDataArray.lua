class "RenderDataArray"



RenderDataArray.VERTEX_DATA_ARRAY = 0
RenderDataArray.COLOR_DATA_ARRAY = 1
RenderDataArray.NORMAL_DATA_ARRAY = 2
RenderDataArray.TEXCOORD_DATA_ARRAY = 3
RenderDataArray.TANGENT_DATA_ARRAY = 4
RenderDataArray.BONE_WEIGHT_DATA_ARRAY = 5
RenderDataArray.BONE_INDEX_DATA_ARRAY = 6
RenderDataArray.INDEX_DATA_ARRAY = 7
RenderDataArray.TEXCOORD2_DATA_ARRAY = 8
function RenderDataArray:__getvar(name)
	if name == "type" then
		return Polycore.RenderDataArray_get_type(self.__ptr)
	elseif name == "customArrayName" then
		return Polycore.RenderDataArray_get_customArrayName(self.__ptr)
	elseif name == "hasVBO" then
		return Polycore.RenderDataArray_get_hasVBO(self.__ptr)
	elseif name == "platformData" then
		local retVal = Polycore.RenderDataArray_get_platformData(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["void"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end


function RenderDataArray:__setvar(name,value)
	if name == "type" then
		Polycore.RenderDataArray_set_type(self.__ptr, value)
		return true
	elseif name == "customArrayName" then
		Polycore.RenderDataArray_set_customArrayName(self.__ptr, value)
		return true
	elseif name == "hasVBO" then
		Polycore.RenderDataArray_set_hasVBO(self.__ptr, value)
		return true
	end
	return false
end


function RenderDataArray:RenderDataArray(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.RenderDataArray(unpack(arg))
	end
end

function RenderDataArray:getArrayData()
	local retVal =  Polycore.RenderDataArray_getArrayData(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["void"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function RenderDataArray:getDataSize()
	local retVal =  Polycore.RenderDataArray_getDataSize(self.__ptr)
	return retVal
end

function RenderDataArray:__delete()
	if self then Polycore.delete_RenderDataArray(self.__ptr) end
end
