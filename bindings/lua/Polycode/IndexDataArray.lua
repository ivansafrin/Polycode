require "Polycode/RenderDataArray"

class "IndexDataArray" (RenderDataArray)


function IndexDataArray:IndexDataArray(...)
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
		self.__ptr = Polycode.IndexDataArray(unpack(arg))
	end
end

function IndexDataArray:getArrayData()
	local retVal =  Polycode.IndexDataArray_getArrayData(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["void"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function IndexDataArray:getDataSize()
	local retVal =  Polycode.IndexDataArray_getDataSize(self.__ptr)
	return retVal
end

function IndexDataArray:__delete()
	if self then Polycode.delete_IndexDataArray(self.__ptr) end
end
