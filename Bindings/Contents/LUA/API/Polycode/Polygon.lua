class "Polygon"

function Polygon:Polygon()
	if self.__ptr == nil then
		self.__ptr = Polycore.Polygon()
	end
end

function Polygon:getVertexCount()
	return Polycore.Polygon_getVertexCount(self.__ptr)
end

function Polygon:getVertex(index)
	return Polycore.Polygon_getVertex(self.__ptr, index)
end

function Polygon:addVertex(x, y, z)
	return Polycore.Polygon_addVertex(self.__ptr, x, y, z)
end

function Polygon:removeVertex(index)
	return Polycore.Polygon_removeVertex(self.__ptr, index)
end

function Polygon:addTexCoord(u, v)
	return Polycore.Polygon_addTexCoord(self.__ptr, u, v)
end

function Polygon:addTexCoord2(u, v)
	return Polycore.Polygon_addTexCoord2(self.__ptr, u, v)
end

function Polygon:getTexCoord(index)
	return Polycore.Polygon_getTexCoord(self.__ptr, index)
end

function Polygon:getTexCoord2(index)
	return Polycore.Polygon_getTexCoord2(self.__ptr, index)
end

function Polygon:calculateNormal()
	return Polycore.Polygon_calculateNormal(self.__ptr)
end

function Polygon:getFaceNormal()
	return Polycore.Polygon_getFaceNormal(self.__ptr)
end

function Polygon:getBounds2D()
	return Polycore.Polygon_getBounds2D(self.__ptr)
end

function Polygon:setNormal(normal)
	return Polycore.Polygon_setNormal(self.__ptr, normal.__ptr)
end

function Polygon:flipUVY()
	return Polycore.Polygon_flipUVY(self.__ptr)
end

function Polygon:setUseFaceUV(val)
	return Polycore.Polygon_setUseFaceUV(self.__ptr, val)
end

function Polygon:usesFaceUV()
	return Polycore.Polygon_usesFaceUV(self.__ptr)
end

