require "Polycode/Resource"

class "Mesh" (Resource)

Mesh.TRISTRIP_MESH = 0
Mesh.TRI_MESH = 1
Mesh.TRIFAN_MESH = 2
Mesh.LINE_MESH = 4
Mesh.POINT_MESH = 5
Mesh.LINE_STRIP_MESH = 6
Mesh.LINE_LOOP_MESH = 7

function Mesh:__getvar(name)
	if name == "indexedMesh" then
		return Polycode.Mesh_get_indexedMesh(self.__ptr)
	end
	if Resource["__getvar"] ~= nil then
		return Resource.__getvar(self, name)
	end
end

function Mesh:__setvar(name,value)
	if name == "indexedMesh" then
		Polycode.Mesh_set_indexedMesh(self.__ptr, value)
		return true
	end
	if Resource["__setvar"] ~= nil then
		return Resource.__setvar(self, name, value)
	else
		return false
	end
end
function Mesh:Mesh(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "Resource" then
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
		self.__ptr = Polycode.Mesh(unpack(arg))
	end
end

function Mesh:MeshFromFileName(fileName)
	local retVal = Polycode.Mesh_MeshFromFileName(self.__ptr, fileName)
	if retVal == nil then return nil end
	local __c = _G["Mesh"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Mesh:loadMesh(fileName)
	local retVal = Polycode.Mesh_loadMesh(self.__ptr, fileName)
end

function Mesh:clearMesh()
	local retVal =  Polycode.Mesh_clearMesh(self.__ptr)
end

function Mesh:saveToFile(fileName, writeNormals, writeTangents, writeColors, writeBoneWeights, writeUVs, writeSecondaryUVs)
	local retVal = Polycode.Mesh_saveToFile(self.__ptr, fileName, writeNormals, writeTangents, writeColors, writeBoneWeights, writeUVs, writeSecondaryUVs)
end

function Mesh:loadFromFile(inFile)
	local retVal = Polycode.Mesh_loadFromFile(self.__ptr, inFile.__ptr)
end

function Mesh:getVertexCount()
	local retVal =  Polycode.Mesh_getVertexCount(self.__ptr)
	return retVal
end

function Mesh:createPlane(w, h, tilingValue)
	local retVal = Polycode.Mesh_createPlane(self.__ptr, w, h, tilingValue)
end

function Mesh:createVPlane(w, h, tilingValue)
	local retVal = Polycode.Mesh_createVPlane(self.__ptr, w, h, tilingValue)
end

function Mesh:createCircle(w, h, numSegments, tilingValue)
	local retVal = Polycode.Mesh_createCircle(self.__ptr, w, h, numSegments, tilingValue)
end

function Mesh:createLineCircle(w, h, numSegments, tilingValue)
	local retVal = Polycode.Mesh_createLineCircle(self.__ptr, w, h, numSegments, tilingValue)
end

function Mesh:createTorus(radius, tubeRadius, segmentsW, segmentsH, tilingValue)
	local retVal = Polycode.Mesh_createTorus(self.__ptr, radius, tubeRadius, segmentsW, segmentsH, tilingValue)
end

function Mesh:createBox(w, d, h, tilingValue)
	local retVal = Polycode.Mesh_createBox(self.__ptr, w, d, h, tilingValue)
end

function Mesh:createSphere(radius, numRings, numSegments, tilingValue)
	local retVal = Polycode.Mesh_createSphere(self.__ptr, radius, numRings, numSegments, tilingValue)
end

function Mesh:createIcosphere(radius, subdivisions)
	local retVal = Polycode.Mesh_createIcosphere(self.__ptr, radius, subdivisions)
end

function Mesh:createOctosphere(radius, subdivisions)
	local retVal = Polycode.Mesh_createOctosphere(self.__ptr, radius, subdivisions)
end

function Mesh:createCylinder(height, radius, numSegments, capped, tilingValue)
	local retVal = Polycode.Mesh_createCylinder(self.__ptr, height, radius, numSegments, capped, tilingValue)
end

function Mesh:createCone(height, radius, numSegments, tilingValue)
	local retVal = Polycode.Mesh_createCone(self.__ptr, height, radius, numSegments, tilingValue)
end

function Mesh:recenterMesh()
	local retVal =  Polycode.Mesh_recenterMesh(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Mesh:setVertexAtOffset(offset, x, y, z)
	local retVal = Polycode.Mesh_setVertexAtOffset(self.__ptr, offset, x, y, z)
end

function Mesh:addVertexWithUVAndNormal(x, y, z, u, v, nx, ny, nz)
	local retVal = Polycode.Mesh_addVertexWithUVAndNormal(self.__ptr, x, y, z, u, v, nx, ny, nz)
end

function Mesh:addTexCoord(u, v)
	local retVal = Polycode.Mesh_addTexCoord(self.__ptr, u, v)
end

function Mesh:addTexCoord2(u, v)
	local retVal = Polycode.Mesh_addTexCoord2(self.__ptr, u, v)
end

function Mesh:addTangent(x, y, z)
	local retVal = Polycode.Mesh_addTangent(self.__ptr, x, y, z)
end

function Mesh:addVertexWithUV(x, y, z, u, v)
	local retVal = Polycode.Mesh_addVertexWithUV(self.__ptr, x, y, z, u, v)
end

function Mesh:addVertex(x, y, z)
	local retVal = Polycode.Mesh_addVertex(self.__ptr, x, y, z)
end

function Mesh:addNormal(nx, ny, nz)
	local retVal = Polycode.Mesh_addNormal(self.__ptr, nx, ny, nz)
end

function Mesh:addBoneAssignments(b1Weight, b1Index, b2Weight, b2Index, b3Weight, b3Index, b4Weight, b4Index)
	local retVal = Polycode.Mesh_addBoneAssignments(self.__ptr, b1Weight, b1Index, b2Weight, b2Index, b3Weight, b3Index, b4Weight, b4Index)
end

function Mesh:addColor(r, g, b, a)
	local retVal = Polycode.Mesh_addColor(self.__ptr, r, g, b, a)
end

function Mesh:getVertexPosition(vertexOffset)
	local retVal = Polycode.Mesh_getVertexPosition(self.__ptr, vertexOffset)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Mesh:getVertexPositionAtIndex(index)
	local retVal = Polycode.Mesh_getVertexPositionAtIndex(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Mesh:getVertexTexCoord(vertexOffset)
	local retVal = Polycode.Mesh_getVertexTexCoord(self.__ptr, vertexOffset)
	if retVal == nil then return nil end
	local __c = _G["Vector2"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Mesh:getVertexTexCoordAtIndex(index)
	local retVal = Polycode.Mesh_getVertexTexCoordAtIndex(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["Vector2"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Mesh:Copy()
	local retVal =  Polycode.Mesh_Copy(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Mesh"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Mesh:getRadius()
	local retVal =  Polycode.Mesh_getRadius(self.__ptr)
	return retVal
end

function Mesh:calculateNormals()
	local retVal =  Polycode.Mesh_calculateNormals(self.__ptr)
end

function Mesh:calculateTangents()
	local retVal =  Polycode.Mesh_calculateTangents(self.__ptr)
end

function Mesh:getMeshType()
	local retVal =  Polycode.Mesh_getMeshType(self.__ptr)
	return retVal
end

function Mesh:setMeshType(newType)
	local retVal = Polycode.Mesh_setMeshType(self.__ptr, newType)
end

function Mesh:getIndexGroupSize()
	local retVal =  Polycode.Mesh_getIndexGroupSize(self.__ptr)
	return retVal
end

function Mesh:calculateBBox()
	local retVal =  Polycode.Mesh_calculateBBox(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Mesh:hasVertexBuffer()
	local retVal =  Polycode.Mesh_hasVertexBuffer(self.__ptr)
	return retVal
end

function Mesh:addIndexedFace(i1, i2)
	local retVal = Polycode.Mesh_addIndexedFace(self.__ptr, i1, i2)
end

function Mesh:addIndex(index)
	local retVal = Polycode.Mesh_addIndex(self.__ptr, index)
end

function Mesh:removeVertexRange(beginRemoveVertex, vertexRemovalCount)
	local retVal = Polycode.Mesh_removeVertexRange(self.__ptr, beginRemoveVertex, vertexRemovalCount)
end

function Mesh:removeFace(faceIndex)
	local retVal = Polycode.Mesh_removeFace(self.__ptr, faceIndex)
end

function Mesh:removeUnusedVertices()
	local retVal =  Polycode.Mesh_removeUnusedVertices(self.__ptr)
	return retVal
end

function Mesh:getIndexCount()
	local retVal =  Polycode.Mesh_getIndexCount(self.__ptr)
	return retVal
end

function Mesh:subdivideToRadius(radius, subdivisions)
	local retVal = Polycode.Mesh_subdivideToRadius(self.__ptr, radius, subdivisions)
end

function Mesh:calculateFaceTangent(v1, v2, v3, texCoord1, texCoord2, texCoord3)
	local retVal = Polycode.Mesh_calculateFaceTangent(self.__ptr, v1.__ptr, v2.__ptr, v3.__ptr, texCoord1.__ptr, texCoord2.__ptr, texCoord3.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Mesh:saveAsOBJ(fileName)
	local retVal = Polycode.Mesh_saveAsOBJ(self.__ptr, fileName)
end

function Mesh:normalizeBoneWeights()
	local retVal =  Polycode.Mesh_normalizeBoneWeights(self.__ptr)
end

function Mesh:__delete()
	if self then Polycode.delete_Mesh(self.__ptr) end
end
