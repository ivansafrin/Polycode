class "Mesh"

function Mesh:Mesh(fileName)
	if self.__ptr == nil then
		self.__ptr = Polycore.Mesh(fileName)
	end
end

function Mesh:addPolygon(newPolygon)
	return Polycore.Mesh_addPolygon(self.__ptr, newPolygon.__ptr)
end

function Mesh:loadMesh(fileName)
	return Polycore.Mesh_loadMesh(self.__ptr, fileName)
end

function Mesh:loadFromFile(inFile)
	return Polycore.Mesh_loadFromFile(self.__ptr, inFile.__ptr)
end

function Mesh:saveToFile(outFile)
	return Polycore.Mesh_saveToFile(self.__ptr, outFile.__ptr)
end

function Mesh:getPolygonCount()
	return Polycore.Mesh_getPolygonCount(self.__ptr)
end

function Mesh:getPolygon(index)
	return Polycore.Mesh_getPolygon(self.__ptr, index)
end

function Mesh:createPlane(w, h)
	return Polycore.Mesh_createPlane(self.__ptr, w, h)
end

function Mesh:createBox(w, d, h)
	return Polycore.Mesh_createBox(self.__ptr, w, d, h)
end

function Mesh:createSphere(radius, numRings, numSegments)
	return Polycore.Mesh_createSphere(self.__ptr, radius, numRings, numSegments)
end

function Mesh:addVertex(vertex)
	return Polycore.Mesh_addVertex(self.__ptr, vertex.__ptr)
end

function Mesh:getVertex(index)
	return Polycore.Mesh_getVertex(self.__ptr, index)
end

function Mesh:getNumVertices()
	return Polycore.Mesh_getNumVertices(self.__ptr)
end

function Mesh:recenterMesh()
	return Polycore.Mesh_recenterMesh(self.__ptr)
end

function Mesh:useVertexNormals(val)
	return Polycore.Mesh_useVertexNormals(self.__ptr, val)
end

function Mesh:getVertexIndex(vertex)
	return Polycore.Mesh_getVertexIndex(self.__ptr, vertex.__ptr)
end

function Mesh:setVertexBuffer(buffer)
	return Polycore.Mesh_setVertexBuffer(self.__ptr, buffer.__ptr)
end

function Mesh:getVertexBuffer()
	return Polycore.Mesh_getVertexBuffer(self.__ptr)
end

function Mesh:usesFaceUV()
	return Polycore.Mesh_usesFaceUV(self.__ptr)
end

function Mesh:getRadius()
	return Polycore.Mesh_getRadius(self.__ptr)
end

function Mesh:calculateNormals()
	return Polycore.Mesh_calculateNormals(self.__ptr)
end

function Mesh:getMeshType()
	return Polycore.Mesh_getMeshType(self.__ptr)
end

function Mesh:setMeshType(newType)
	return Polycore.Mesh_setMeshType(self.__ptr, newType)
end

function Mesh:calculateBBox()
	return Polycore.Mesh_calculateBBox(self.__ptr)
end

function Mesh:hasVertexBuffer()
	return Polycore.Mesh_hasVertexBuffer(self.__ptr)
end

