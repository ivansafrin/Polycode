class "RenderBuffer"


function RenderBuffer:RenderBuffer(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.RenderBuffer(unpack(arg))
	end
end

function RenderBuffer:getWidth()
	local retVal =  Polycode.RenderBuffer_getWidth(self.__ptr)
	return retVal
end

function RenderBuffer:getHeight()
	local retVal =  Polycode.RenderBuffer_getHeight(self.__ptr)
	return retVal
end

function RenderBuffer:__delete()
	if self then Polycode.delete_RenderBuffer(self.__ptr) end
end
