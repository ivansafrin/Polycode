require "Polycode/Vector3"

class "Vertex" (Vector3)

function Vertex:Vertex()
	if self.__ptr == nil then
		self.__ptr = Polycore.Vertex()
	end
end

function Vertex:addBoneAssignment(boneID, boneWeight)
	return Polycore.Vertex_addBoneAssignment(self.__ptr, boneID, boneWeight)
end

function Vertex:getNumBoneAssignments()
	return Polycore.Vertex_getNumBoneAssignments(self.__ptr)
end

function Vertex:getBoneAssignment(index)
	return Polycore.Vertex_getBoneAssignment(self.__ptr, index)
end

function Vertex:normalizeWeights()
	return Polycore.Vertex_normalizeWeights(self.__ptr)
end

function Vertex:getTexCoord()
	return Polycore.Vertex_getTexCoord(self.__ptr)
end

function Vertex:setTexCoord(u, v)
	return Polycore.Vertex_setTexCoord(self.__ptr, u, v)
end

function Vertex:setNormal(x, y, z)
	return Polycore.Vertex_setNormal(self.__ptr, x, y, z)
end

