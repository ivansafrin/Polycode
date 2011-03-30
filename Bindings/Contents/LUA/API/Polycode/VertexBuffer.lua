class "VertexBuffer"

function VertexBuffer:VertexBuffer()
	if self.__ptr == nil then
		self.__ptr = Polycore.VertexBuffer()
	end
end

function VertexBuffer:getVertexCount()
	return Polycore.VertexBuffer_getVertexCount(self.__ptr)
end

