class "VertexBuffer"



function VertexBuffer:__index__(name)
	if name == "verticesPerFace" then
		return Polycore.VertexBuffer_get_verticesPerFace(self.__ptr)
	elseif name == "meshType" then
		return Polycore.VertexBuffer_get_meshType(self.__ptr)
	end
end


function VertexBuffer:__set_callback(name,value)
	if name == "verticesPerFace" then
		Polycore.VertexBuffer_set_verticesPerFace(self.__ptr, value)
		return true
	elseif name == "meshType" then
		Polycore.VertexBuffer_set_meshType(self.__ptr, value)
		return true
	end
	return false
end


function VertexBuffer:VertexBuffer(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.VertexBuffer(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function VertexBuffer:getVertexCount()
	local retVal =  Polycore.VertexBuffer_getVertexCount(self.__ptr)
	return retVal
end



function VertexBuffer:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_VertexBuffer(self.__ptr)
end
