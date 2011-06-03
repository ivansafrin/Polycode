require "Polycode/SceneEntity"

class "SceneMesh" (SceneEntity)



function SceneMesh:__index__(name)
	if name == "lightmapIndex" then
		retVal = Polycore.SceneMesh_get_lightmapIndex(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = unsigned int("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "showVertexNormals" then
		return Polycore.SceneMesh_get_showVertexNormals(self.__ptr)
	end
end


function SceneMesh:__set_callback(name,value)
	if name == "showVertexNormals" then
		Polycore.SceneMesh_set_showVertexNormals(self.__ptr, value)
		return true
	end
	return false
end


function SceneMesh:SceneMesh(...)
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1]:class() == "SceneEntity" then
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
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function SceneMesh:Render()
	local retVal =  Polycore.SceneMesh_Render(self.__ptr)
end

function SceneMesh:getLocalShaderOptions()
	local retVal =  Polycore.SceneMesh_getLocalShaderOptions(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = ShaderBinding("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function SceneMesh:getMesh()
	local retVal =  Polycore.SceneMesh_getMesh(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Mesh("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function SceneMesh:getTexture()
	local retVal =  Polycore.SceneMesh_getTexture(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Texture("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function SceneMesh:getMaterial()
	local retVal =  Polycore.SceneMesh_getMaterial(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Material("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function SceneMesh:loadTexture(fileName, clamp)
	local retVal = Polycore.SceneMesh_loadTexture(self.__ptr, fileName, clamp)
end

function SceneMesh:loadSkeleton(fileName)
	local retVal = Polycore.SceneMesh_loadSkeleton(self.__ptr, fileName)
end

function SceneMesh:setTexture(texture)
	local retVal = Polycore.SceneMesh_setTexture(self.__ptr, texture.__ptr)
end

function SceneMesh:setMaterial(material)
	local retVal = Polycore.SceneMesh_setMaterial(self.__ptr, material.__ptr)
end

function SceneMesh:setMaterialByName(materialName)
	local retVal = Polycore.SceneMesh_setMaterialByName(self.__ptr, materialName)
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
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Skeleton("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function SceneMesh:renderMeshLocally()
	local retVal =  Polycore.SceneMesh_renderMeshLocally(self.__ptr)
end

function SceneMesh:cacheToVertexBuffer(cache)
	local retVal = Polycore.SceneMesh_cacheToVertexBuffer(self.__ptr, cache)
end



function SceneMesh:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_SceneMesh(self.__ptr)
end
