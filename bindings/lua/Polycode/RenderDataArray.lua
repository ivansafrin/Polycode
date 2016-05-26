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
RenderDataArray.CUSTOM_DATA_ARRAY1 = 9
RenderDataArray.CUSTOM_DATA_ARRAY2 = 10
RenderDataArray.CUSTOM_DATA_ARRAY3 = 11
RenderDataArray.CUSTOM_DATA_ARRAY4 = 12
RenderDataArray.UNKNOWN_DATA_ARRAY = 13

function RenderDataArray:__getvar(name)
	if name == "type" then
		return Polycode.RenderDataArray_get_type(self.__ptr)
	elseif name == "customArrayName" then
		return Polycode.RenderDataArray_get_customArrayName(self.__ptr)
	end
end

function RenderDataArray:__setvar(name,value)
	if name == "type" then
		Polycode.RenderDataArray_set_type(self.__ptr, value)
		return true
	elseif name == "customArrayName" then
		Polycode.RenderDataArray_set_customArrayName(self.__ptr, value)
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
		self.__ptr = Polycode.RenderDataArray(unpack(arg))
	end
end

function RenderDataArray:getArrayData()
	local retVal =  Polycode.RenderDataArray_getArrayData(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["void"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function RenderDataArray:getDataSize()
	local retVal =  Polycode.RenderDataArray_getDataSize(self.__ptr)
	return retVal
end

function RenderDataArray:__delete()
	if self then Polycode.delete_RenderDataArray(self.__ptr) end
end
