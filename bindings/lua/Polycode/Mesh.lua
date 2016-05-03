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
		return Polycore.Mesh_get_indexedMesh(self.__ptr)
	elseif name == "vertexPositionArray" then
		local retVal = Polycore.Mesh_get_vertexPositionArray(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["VertexDataArray"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "vertexColorArray" then
		local retVal = Polycore.Mesh_get_vertexColorArray(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["VertexDataArray"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "vertexNormalArray" then
		local retVal = Polycore.Mesh_get_vertexNormalArray(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["VertexDataArray"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "vertexTexCoordArray" then
		local retVal = Polycore.Mesh_get_vertexTexCoordArray(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["VertexDataArray"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "vertexTexCoord2Array" then
		local retVal = Polycore.Mesh_get_vertexTexCoord2Array(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["VertexDataArray"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "vertexTangentArray" then
		local retVal = Polycore.Mesh_get_vertexTangentArray(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["VertexDataArray"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "vertexBoneWeightArray" then
		local retVal = Polycore.Mesh_get_vertexBoneWeightArray(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["VertexDataArray"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "vertexBoneIndexArray" then
		local retVal = Polycore.Mesh_get_vertexBoneIndexArray(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["VertexDataArray"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "indexArray" then
		local retVal = Polycore.Mesh_get_indexArray(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["IndexDataArray"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
	if Resource["__getvar"] ~= nil then
		return Resource.__getvar(self, name)
	end
end


function Mesh:__setvar(name,value)
	if name == "indexedMesh" then
		Polycore.Mesh_set_indexedMesh(self.__ptr, value)
		return true
	elseif name == "vertexPositionArray" then
		Polycore.Mesh_set_vertexPositionArray(self.__ptr, value.__ptr)
		return true
	elseif name == "vertexColorArray" then
		Polycore.Mesh_set_vertexColorArray(self.__ptr, value.__ptr)
		return true
	elseif name == "vertexNormalArray" then
		Polycore.Mesh_set_vertexNormalArray(self.__ptr, value.__ptr)
		return true
	elseif name == "vertexTexCoordArray" then
		Polycore.Mesh_set_vertexTexCoordArray(self.__ptr, value.__ptr)
		return true
	elseif name == "vertexTexCoord2Array" then
		Polycore.Mesh_set_vertexTexCoord2Array(self.__ptr, value.__ptr)
		return true
	elseif name == "vertexTangentArray" then
		Polycore.Mesh_set_vertexTangentArray(self.__ptr, value.__ptr)
		return true
	elseif name == "vertexBoneWeightArray" then
		Polycore.Mesh_set_vertexBoneWeightArray(self.__ptr, value.__ptr)
		return true
	elseif name == "vertexBoneIndexArray" then
		Polycore.Mesh_set_vertexBoneIndexArray(self.__ptr, value.__ptr)
		return true
	elseif name == "indexArray" then
		Polycore.Mesh_set_indexArray(self.__ptr, value.__ptr)
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
		self.__ptr = Polycore.Mesh(unpack(arg))
	end
end

function Mesh.MeshFromFileName(fileName)
	local retVal = Polycore.Mesh_MeshFromFileName(fileName)
	if retVal == nil then return nil end
	local __c = _G["Mesh"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Mesh:loadMesh(fileName)
	local retVal = Polycore.Mesh_loadMesh(self.__ptr, fileName)
end

function Mesh:clearMesh()
	local retVal =  Polycore.Mesh_clearMesh(self.__ptr)
end

function Mesh:saveToFile(fileName, writeNormals, writeTangents, writeColors, writeBoneWeights, writeUVs, writeSecondaryUVs)
	local retVal = Polycore.Mesh_saveToFile(self.__ptr, fileName, writeNormals, writeTangents, writeColors, writeBoneWeights, writeUVs, writeSecondaryUVs)
end

function Mesh:loadFromFile(inFile)
	local retVal = Polycore.Mesh_loadFromFile(self.__ptr, inFile.__ptr)
end

function Mesh:getVertexCount()
	local retVal =  Polycore.Mesh_getVertexCount(self.__ptr)
	return retVal
end

function Mesh:createPlane(w, h, tilingValue)
	local retVal = Polycore.Mesh_createPlane(self.__ptr, w, h, tilingValue)
end

function Mesh:createVPlane(w, h, tilingValue)
	local retVal = Polycore.Mesh_createVPlane(self.__ptr, w, h, tilingValue)
end

function Mesh:createCircle(w, h, numSegments, tilingValue)
	local retVal = Polycore.Mesh_createCircle(self.__ptr, w, h, numSegments, tilingValue)
end

function Mesh:createLineCircle(w, h, numSegments, tilingValue)
	local retVal = Polycore.Mesh_createLineCircle(self.__ptr, w, h, numSegments, tilingValue)
end

function Mesh:createTorus(radius, tubeRadius, segmentsW, segmentsH, tilingValue)
	local retVal = Polycore.Mesh_createTorus(self.__ptr, radius, tubeRadius, segmentsW, segmentsH, tilingValue)
end

function Mesh:createBox(w, d, h, tilingValue)
	local retVal = Polycore.Mesh_createBox(self.__ptr, w, d, h, tilingValue)
end

function Mesh:createSphere(radius, numRings, numSegments, tilingValue)
	local retVal = Polycore.Mesh_createSphere(self.__ptr, radius, numRings, numSegments, tilingValue)
end

function Mesh:createIcosphere(radius, subdivisions)
	local retVal = Polycore.Mesh_createIcosphere(self.__ptr, radius, subdivisions)
end

function Mesh:createOctosphere(radius, subdivisions)
	local retVal = Polycore.Mesh_createOctosphere(self.__ptr, radius, subdivisions)
end

function Mesh:createCylinder(height, radius, numSegments, capped, tilingValue)
	local retVal = Polycore.Mesh_createCylinder(self.__ptr, height, radius, numSegments, capped, tilingValue)
end

function Mesh:createCone(height, radius, numSegments, tilingValue)
	local retVal = Polycore.Mesh_createCone(self.__ptr, height, radius, numSegments, tilingValue)
end

function Mesh:recenterMesh()
	local retVal =  Polycore.Mesh_recenterMesh(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Mesh:setVertexAtOffset(offset, x, y, z)
	local retVal = Polycore.Mesh_setVertexAtOffset(self.__ptr, offset, x, y, z)
end

function Mesh:addVertexWithUVAndNormal(x, y, z, u, v, nx, ny, nz)
	local retVal = Polycore.Mesh_addVertexWithUVAndNormal(self.__ptr, x, y, z, u, v, nx, ny, nz)
end

function Mesh:addTexCoord(u, v)
	local retVal = Polycore.Mesh_addTexCoord(self.__ptr, u, v)
end

function Mesh:addTexCoord2(u, v)
	local retVal = Polycore.Mesh_addTexCoord2(self.__ptr, u, v)
end

function Mesh:addTangent(x, y, z)
	local retVal = Polycore.Mesh_addTangent(self.__ptr, x, y, z)
end

function Mesh:addVertexWithUV(x, y, z, u, v)
	local retVal = Polycore.Mesh_addVertexWithUV(self.__ptr, x, y, z, u, v)
end

function Mesh:addVertex(x, y, z)
	local retVal = Polycore.Mesh_addVertex(self.__ptr, x, y, z)
end

function Mesh:addNormal(nx, ny, nz)
	local retVal = Polycore.Mesh_addNormal(self.__ptr, nx, ny, nz)
end

function Mesh:addBoneAssignments(b1Weight, b1Index, b2Weight, b2Index, b3Weight, b3Index, b4Weight, b4Index)
	local retVal = Polycore.Mesh_addBoneAssignments(self.__ptr, b1Weight, b1Index, b2Weight, b2Index, b3Weight, b3Index, b4Weight, b4Index)
end

function Mesh:addColor(r, g, b, a)
	local retVal = Polycore.Mesh_addColor(self.__ptr, r, g, b, a)
end

function Mesh:getVertexPosition(vertexOffset)
	local retVal = Polycore.Mesh_getVertexPosition(self.__ptr, vertexOffset)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Mesh:getVertexPositionAtIndex(index)
	local retVal = Polycore.Mesh_getVertexPositionAtIndex(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Mesh:getVertexTexCoord(vertexOffset)
	local retVal = Polycore.Mesh_getVertexTexCoord(self.__ptr, vertexOffset)
	if retVal == nil then return nil end
	local __c = _G["Vector2"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Mesh:getVertexTexCoordAtIndex(index)
	local retVal = Polycore.Mesh_getVertexTexCoordAtIndex(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["Vector2"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Mesh:Copy()
	local retVal =  Polycore.Mesh_Copy(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Mesh"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Mesh:getRadius()
	local retVal =  Polycore.Mesh_getRadius(self.__ptr)
	return retVal
end

function Mesh:calculateNormals()
	local retVal =  Polycore.Mesh_calculateNormals(self.__ptr)
end

function Mesh:calculateTangents()
	local retVal =  Polycore.Mesh_calculateTangents(self.__ptr)
end

function Mesh:getMeshType()
	local retVal =  Polycore.Mesh_getMeshType(self.__ptr)
	return retVal
end

function Mesh:setMeshType(newType)
	local retVal = Polycore.Mesh_setMeshType(self.__ptr, newType)
end

function Mesh:getIndexGroupSize()
	local retVal =  Polycore.Mesh_getIndexGroupSize(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["unsignedint"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Mesh:calculateBBox()
	local retVal =  Polycore.Mesh_calculateBBox(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Mesh:hasVertexBuffer()
	local retVal =  Polycore.Mesh_hasVertexBuffer(self.__ptr)
	return retVal
end

function Mesh:addIndexedFace(i1, i2)
	local retVal = Polycore.Mesh_addIndexedFace(self.__ptr, i1, i2)
end

function Mesh:addIndex(index)
	local retVal = Polycore.Mesh_addIndex(self.__ptr, index)
end

function Mesh:removeVertexRange(beginRemoveVertex, vertexRemovalCount)
	local retVal = Polycore.Mesh_removeVertexRange(self.__ptr, beginRemoveVertex, vertexRemovalCount)
end

function Mesh:removeFace(faceIndex)
	local retVal = Polycore.Mesh_removeFace(self.__ptr, faceIndex)
end

function Mesh:removeUnusedVertices()
	local retVal =  Polycore.Mesh_removeUnusedVertices(self.__ptr)
	return retVal
end

function Mesh:getIndexCount()
	local retVal =  Polycore.Mesh_getIndexCount(self.__ptr)
	return retVal
end

function Mesh:subdivideToRadius(radius, subdivisions)
	local retVal = Polycore.Mesh_subdivideToRadius(self.__ptr, radius, subdivisions)
end

function Mesh.calculateFaceTangent(v1, v2, v3, texCoord1, texCoord2, texCoord3)
	local retVal = Polycore.Mesh_calculateFaceTangent(v1.__ptr, v2.__ptr, v3.__ptr, texCoord1.__ptr, texCoord2.__ptr, texCoord3.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Mesh:saveAsOBJ(fileName)
	local retVal = Polycore.Mesh_saveAsOBJ(self.__ptr, fileName)
end

function Mesh:normalizeBoneWeights()
	local retVal =  Polycore.Mesh_normalizeBoneWeights(self.__ptr)
end

function Mesh:__delete()
	if self then Polycore.delete_Mesh(self.__ptr) end
end
