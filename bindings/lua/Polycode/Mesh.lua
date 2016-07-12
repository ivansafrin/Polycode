require "Polycode/Resource"

class "Mesh" (Resource)


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

function Mesh:loadMesh(fileName)
	local retVal = Polycode.Mesh_loadMesh(self.__ptr, fileName)
end

function Mesh:saveToFile(fileName, writeNormals, writeTangents, writeColors, writeBoneWeights, writeUVs, writeSecondaryUVs)
	local retVal = Polycode.Mesh_saveToFile(self.__ptr, fileName, writeNormals, writeTangents, writeColors, writeBoneWeights, writeUVs, writeSecondaryUVs)
end

function Mesh:addSubmesh(newSubmesh)
	local retVal = Polycode.Mesh_addSubmesh(self.__ptr, newSubmesh.__ptr)
end

function Mesh:removeSubmeshAtIndex(index)
	local retVal = Polycode.Mesh_removeSubmeshAtIndex(self.__ptr, index)
end

function Mesh:getNumSubmeshes()
	local retVal =  Polycode.Mesh_getNumSubmeshes(self.__ptr)
	return retVal
end

function Mesh:getSubmeshAtIndex(index)
	local retVal = Polycode.Mesh_getSubmeshAtIndex(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["MeshGeometry"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Mesh:getSubmeshPointer(index)
	local retVal = Polycode.Mesh_getSubmeshPointer(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["shared_ptr<MeshGeometry>"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Mesh:clearMesh()
	local retVal =  Polycode.Mesh_clearMesh(self.__ptr)
end

function Mesh:calculateBBox()
	local retVal =  Polycode.Mesh_calculateBBox(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Mesh:getRadius()
	local retVal =  Polycode.Mesh_getRadius(self.__ptr)
	return retVal
end

function Mesh:__delete()
	if self then Polycode.delete_Mesh(self.__ptr) end
end
