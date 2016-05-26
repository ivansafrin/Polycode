class "MeshGeometry"

MeshGeometry.TRISTRIP_MESH = 0
MeshGeometry.TRI_MESH = 1
MeshGeometry.TRIFAN_MESH = 2
MeshGeometry.LINE_MESH = 4
MeshGeometry.POINT_MESH = 5
MeshGeometry.LINE_STRIP_MESH = 6
MeshGeometry.LINE_LOOP_MESH = 7

function MeshGeometry:__getvar(name)
	if name == "meshType" then
		return Polycode.MeshGeometry_get_meshType(self.__ptr)
	elseif name == "dataChanged" then
		return Polycode.MeshGeometry_get_dataChanged(self.__ptr)
	elseif name == "indexedMesh" then
		return Polycode.MeshGeometry_get_indexedMesh(self.__ptr)
	end
end

function MeshGeometry:__setvar(name,value)
	if name == "meshType" then
		Polycode.MeshGeometry_set_meshType(self.__ptr, value)
		return true
	elseif name == "dataChanged" then
		Polycode.MeshGeometry_set_dataChanged(self.__ptr, value)
		return true
	elseif name == "indexedMesh" then
		Polycode.MeshGeometry_set_indexedMesh(self.__ptr, value)
		return true
	end
	return false
end
function MeshGeometry:MeshGeometry(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.MeshGeometry(unpack(arg))
	end
end

function MeshGeometry:clearMesh()
	local retVal =  Polycode.MeshGeometry_clearMesh(self.__ptr)
end

function MeshGeometry:getVertexCount()
	local retVal =  Polycode.MeshGeometry_getVertexCount(self.__ptr)
	return retVal
end

function MeshGeometry:createPlane(w, h, tilingValue)
	local retVal = Polycode.MeshGeometry_createPlane(self.__ptr, w, h, tilingValue)
end

function MeshGeometry:createVPlane(w, h, tilingValue)
	local retVal = Polycode.MeshGeometry_createVPlane(self.__ptr, w, h, tilingValue)
end

function MeshGeometry:createCircle(w, h, numSegments, tilingValue)
	local retVal = Polycode.MeshGeometry_createCircle(self.__ptr, w, h, numSegments, tilingValue)
end

function MeshGeometry:createLineCircle(w, h, numSegments, tilingValue)
	local retVal = Polycode.MeshGeometry_createLineCircle(self.__ptr, w, h, numSegments, tilingValue)
end

function MeshGeometry:createTorus(radius, tubeRadius, segmentsW, segmentsH, tilingValue)
	local retVal = Polycode.MeshGeometry_createTorus(self.__ptr, radius, tubeRadius, segmentsW, segmentsH, tilingValue)
end

function MeshGeometry:createBox(w, d, h, tilingValue)
	local retVal = Polycode.MeshGeometry_createBox(self.__ptr, w, d, h, tilingValue)
end

function MeshGeometry:createSphere(radius, numRings, numSegments, tilingValue)
	local retVal = Polycode.MeshGeometry_createSphere(self.__ptr, radius, numRings, numSegments, tilingValue)
end

function MeshGeometry:createIcosphere(radius, subdivisions)
	local retVal = Polycode.MeshGeometry_createIcosphere(self.__ptr, radius, subdivisions)
end

function MeshGeometry:createOctosphere(radius, subdivisions)
	local retVal = Polycode.MeshGeometry_createOctosphere(self.__ptr, radius, subdivisions)
end

function MeshGeometry:createCylinder(height, radius, numSegments, capped, tilingValue)
	local retVal = Polycode.MeshGeometry_createCylinder(self.__ptr, height, radius, numSegments, capped, tilingValue)
end

function MeshGeometry:createCone(height, radius, numSegments, tilingValue)
	local retVal = Polycode.MeshGeometry_createCone(self.__ptr, height, radius, numSegments, tilingValue)
end

function MeshGeometry:recenterMesh()
	local retVal =  Polycode.MeshGeometry_recenterMesh(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function MeshGeometry:setVertexAtOffset(offset, x, y, z)
	local retVal = Polycode.MeshGeometry_setVertexAtOffset(self.__ptr, offset, x, y, z)
end

function MeshGeometry:addVertexWithUVAndNormal(x, y, z, u, v, nx, ny, nz)
	local retVal = Polycode.MeshGeometry_addVertexWithUVAndNormal(self.__ptr, x, y, z, u, v, nx, ny, nz)
end

function MeshGeometry:addTexCoord(u, v)
	local retVal = Polycode.MeshGeometry_addTexCoord(self.__ptr, u, v)
end

function MeshGeometry:addTexCoord2(u, v)
	local retVal = Polycode.MeshGeometry_addTexCoord2(self.__ptr, u, v)
end

function MeshGeometry:addTangent(x, y, z)
	local retVal = Polycode.MeshGeometry_addTangent(self.__ptr, x, y, z)
end

function MeshGeometry:addVertexWithUV(x, y, z, u, v)
	local retVal = Polycode.MeshGeometry_addVertexWithUV(self.__ptr, x, y, z, u, v)
end

function MeshGeometry:addVertex(x, y, z)
	local retVal = Polycode.MeshGeometry_addVertex(self.__ptr, x, y, z)
end

function MeshGeometry:addNormal(nx, ny, nz)
	local retVal = Polycode.MeshGeometry_addNormal(self.__ptr, nx, ny, nz)
end

function MeshGeometry:addBoneAssignments(b1Weight, b1Index, b2Weight, b2Index, b3Weight, b3Index, b4Weight, b4Index)
	local retVal = Polycode.MeshGeometry_addBoneAssignments(self.__ptr, b1Weight, b1Index, b2Weight, b2Index, b3Weight, b3Index, b4Weight, b4Index)
end

function MeshGeometry:addColor(r, g, b, a)
	local retVal = Polycode.MeshGeometry_addColor(self.__ptr, r, g, b, a)
end

function MeshGeometry:getVertexPosition(vertexOffset)
	local retVal = Polycode.MeshGeometry_getVertexPosition(self.__ptr, vertexOffset)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function MeshGeometry:getVertexPositionAtIndex(index)
	local retVal = Polycode.MeshGeometry_getVertexPositionAtIndex(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function MeshGeometry:getVertexTexCoord(vertexOffset)
	local retVal = Polycode.MeshGeometry_getVertexTexCoord(self.__ptr, vertexOffset)
	if retVal == nil then return nil end
	local __c = _G["Vector2"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function MeshGeometry:getVertexTexCoordAtIndex(index)
	local retVal = Polycode.MeshGeometry_getVertexTexCoordAtIndex(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["Vector2"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function MeshGeometry:Copy()
	local retVal =  Polycode.MeshGeometry_Copy(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["MeshGeometry"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function MeshGeometry:getRadius()
	local retVal =  Polycode.MeshGeometry_getRadius(self.__ptr)
	return retVal
end

function MeshGeometry:calculateNormals()
	local retVal =  Polycode.MeshGeometry_calculateNormals(self.__ptr)
end

function MeshGeometry:calculateTangents()
	local retVal =  Polycode.MeshGeometry_calculateTangents(self.__ptr)
end

function MeshGeometry:getMeshType()
	local retVal =  Polycode.MeshGeometry_getMeshType(self.__ptr)
	return retVal
end

function MeshGeometry:setMeshType(newType)
	local retVal = Polycode.MeshGeometry_setMeshType(self.__ptr, newType)
end

function MeshGeometry:getIndexGroupSize()
	local retVal =  Polycode.MeshGeometry_getIndexGroupSize(self.__ptr)
	return retVal
end

function MeshGeometry:calculateBBox()
	local retVal =  Polycode.MeshGeometry_calculateBBox(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function MeshGeometry:addIndexedFace(i1, i2)
	local retVal = Polycode.MeshGeometry_addIndexedFace(self.__ptr, i1, i2)
end

function MeshGeometry:addIndex(index)
	local retVal = Polycode.MeshGeometry_addIndex(self.__ptr, index)
end

function MeshGeometry:removeVertexRange(beginRemoveVertex, vertexRemovalCount)
	local retVal = Polycode.MeshGeometry_removeVertexRange(self.__ptr, beginRemoveVertex, vertexRemovalCount)
end

function MeshGeometry:removeFace(faceIndex)
	local retVal = Polycode.MeshGeometry_removeFace(self.__ptr, faceIndex)
end

function MeshGeometry:removeUnusedVertices()
	local retVal =  Polycode.MeshGeometry_removeUnusedVertices(self.__ptr)
	return retVal
end

function MeshGeometry:getIndexCount()
	local retVal =  Polycode.MeshGeometry_getIndexCount(self.__ptr)
	return retVal
end

function MeshGeometry:subdivideToRadius(radius, subdivisions)
	local retVal = Polycode.MeshGeometry_subdivideToRadius(self.__ptr, radius, subdivisions)
end

function MeshGeometry:calculateFaceTangent(v1, v2, v3, texCoord1, texCoord2, texCoord3)
	local retVal = Polycode.MeshGeometry_calculateFaceTangent(self.__ptr, v1.__ptr, v2.__ptr, v3.__ptr, texCoord1.__ptr, texCoord2.__ptr, texCoord3.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function MeshGeometry:saveAsOBJ(fileName)
	local retVal = Polycode.MeshGeometry_saveAsOBJ(self.__ptr, fileName)
end

function MeshGeometry:normalizeBoneWeights()
	local retVal =  Polycode.MeshGeometry_normalizeBoneWeights(self.__ptr)
end

function MeshGeometry:__delete()
	if self then Polycode.delete_MeshGeometry(self.__ptr) end
end
