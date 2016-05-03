require "Polycode/Entity"

class "SceneMesh" (Entity)



function SceneMesh:__getvar(name)
	if name == "lineWidth" then
		return Polycore.SceneMesh_get_lineWidth(self.__ptr)
	elseif name == "lineSmooth" then
		return Polycore.SceneMesh_get_lineSmooth(self.__ptr)
	elseif name == "pointSmooth" then
		return Polycore.SceneMesh_get_pointSmooth(self.__ptr)
	elseif name == "ownsMesh" then
		return Polycore.SceneMesh_get_ownsMesh(self.__ptr)
	elseif name == "ownsSkeleton" then
		return Polycore.SceneMesh_get_ownsSkeleton(self.__ptr)
	elseif name == "useGeometryHitDetection" then
		return Polycore.SceneMesh_get_useGeometryHitDetection(self.__ptr)
	elseif name == "alphaTest" then
		return Polycore.SceneMesh_get_alphaTest(self.__ptr)
	elseif name == "backfaceCulled" then
		return Polycore.SceneMesh_get_backfaceCulled(self.__ptr)
	elseif name == "sendBoneMatricesToMaterial" then
		return Polycore.SceneMesh_get_sendBoneMatricesToMaterial(self.__ptr)
	end
	if Entity["__getvar"] ~= nil then
		return Entity.__getvar(self, name)
	end
end


function SceneMesh:__setvar(name,value)
	if name == "lineWidth" then
		Polycore.SceneMesh_set_lineWidth(self.__ptr, value)
		return true
	elseif name == "lineSmooth" then
		Polycore.SceneMesh_set_lineSmooth(self.__ptr, value)
		return true
	elseif name == "pointSmooth" then
		Polycore.SceneMesh_set_pointSmooth(self.__ptr, value)
		return true
	elseif name == "ownsMesh" then
		Polycore.SceneMesh_set_ownsMesh(self.__ptr, value)
		return true
	elseif name == "ownsSkeleton" then
		Polycore.SceneMesh_set_ownsSkeleton(self.__ptr, value)
		return true
	elseif name == "useGeometryHitDetection" then
		Polycore.SceneMesh_set_useGeometryHitDetection(self.__ptr, value)
		return true
	elseif name == "alphaTest" then
		Polycore.SceneMesh_set_alphaTest(self.__ptr, value)
		return true
	elseif name == "backfaceCulled" then
		Polycore.SceneMesh_set_backfaceCulled(self.__ptr, value)
		return true
	elseif name == "sendBoneMatricesToMaterial" then
		Polycore.SceneMesh_set_sendBoneMatricesToMaterial(self.__ptr, value)
		return true
	end
	if Entity["__setvar"] ~= nil then
		return Entity.__setvar(self, name, value)
	else
		return false
	end
end


function SceneMesh:SceneMesh(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "Entity" then
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
		self.__ptr = Polycore.SceneMesh(unpack(arg))
	end
end

function SceneMesh.SceneMeshFromMesh(mesh)
	local retVal = Polycore.SceneMesh_SceneMeshFromMesh(mesh.__ptr)
	if retVal == nil then return nil end
	local __c = _G["SceneMesh"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneMesh.SceneMeshWithType(meshType)
	local retVal = Polycore.SceneMesh_SceneMeshWithType(meshType)
	if retVal == nil then return nil end
	local __c = _G["SceneMesh"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneMesh:Render(buffer)
	local retVal = Polycore.SceneMesh_Render(self.__ptr, buffer.__ptr)
end

function SceneMesh:getShaderPass(index)
	local retVal = Polycore.SceneMesh_getShaderPass(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["ShaderPass"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneMesh:getNumShaderPasses()
	local retVal =  Polycore.SceneMesh_getNumShaderPasses(self.__ptr)
	return retVal
end

function SceneMesh:addShaderPass(pass)
	local retVal = Polycore.SceneMesh_addShaderPass(self.__ptr, pass.__ptr)
end

function SceneMesh:removeShaderPass(shaderIndex)
	local retVal = Polycore.SceneMesh_removeShaderPass(self.__ptr, shaderIndex)
end

function SceneMesh:getMesh()
	local retVal =  Polycore.SceneMesh_getMesh(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Mesh"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneMesh:getMaterial()
	local retVal =  Polycore.SceneMesh_getMaterial(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Material"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneMesh:loadSkeleton(fileName)
	local retVal = Polycore.SceneMesh_loadSkeleton(self.__ptr, fileName)
	if retVal == nil then return nil end
	local __c = _G["Skeleton"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneMesh:clearMaterial()
	local retVal =  Polycore.SceneMesh_clearMaterial(self.__ptr)
end

function SceneMesh:setMaterial(material)
	local retVal = Polycore.SceneMesh_setMaterial(self.__ptr, material.__ptr)
end

function SceneMesh:rebuildAttributes()
	local retVal =  Polycore.SceneMesh_rebuildAttributes(self.__ptr)
end

function SceneMesh:setMaterialByName(materialName, resourcePool)
	local retVal = Polycore.SceneMesh_setMaterialByName(self.__ptr, materialName, resourcePool.__ptr)
end

function SceneMesh:setMesh(mesh)
	local retVal = Polycore.SceneMesh_setMesh(self.__ptr, mesh.__ptr)
end

function SceneMesh:setSkeleton(skeleton)
	local retVal = Polycore.SceneMesh_setSkeleton(self.__ptr, skeleton.__ptr)
end

function SceneMesh:getSkeleton()
	local retVal =  Polycore.SceneMesh_getSkeleton(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Skeleton"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneMesh:applySkeletonLocally()
	local retVal =  Polycore.SceneMesh_applySkeletonLocally(self.__ptr)
end

function SceneMesh:setLineWidth(newWidth)
	local retVal = Polycore.SceneMesh_setLineWidth(self.__ptr, newWidth)
end

function SceneMesh:getFilename()
	local retVal =  Polycore.SceneMesh_getFilename(self.__ptr)
	return retVal
end

function SceneMesh:setFilename(fileName)
	local retVal = Polycore.SceneMesh_setFilename(self.__ptr, fileName)
end

function SceneMesh:loadFromFile(fileName)
	local retVal = Polycore.SceneMesh_loadFromFile(self.__ptr, fileName)
end

function SceneMesh:customHitDetection(ray)
	local retVal = Polycore.SceneMesh_customHitDetection(self.__ptr, ray.__ptr)
	return retVal
end

function SceneMesh:setForceMaterial(forceMaterial)
	local retVal = Polycore.SceneMesh_setForceMaterial(self.__ptr, forceMaterial)
end

function SceneMesh:getForceMaterial()
	local retVal =  Polycore.SceneMesh_getForceMaterial(self.__ptr)
	return retVal
end

function SceneMesh:Clone(deepClone, ignoreEditorOnly)
	local retVal = Polycore.SceneMesh_Clone(self.__ptr, deepClone, ignoreEditorOnly)
	if retVal == nil then return nil end
	local __c = _G["Entity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneMesh:applyClone(clone, deepClone, ignoreEditorOnly)
	local retVal = Polycore.SceneMesh_applyClone(self.__ptr, clone.__ptr, deepClone, ignoreEditorOnly)
end

function SceneMesh:__delete()
	if self then Polycore.delete_SceneMesh(self.__ptr) end
end
