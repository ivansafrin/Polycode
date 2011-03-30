require "Polycode/SceneEntity"

class "SceneMesh" (SceneEntity)

function SceneMesh:SceneMesh(fileName)
	if self.__ptr == nil then
		self.__ptr = Polycore.SceneMesh(fileName)
	end
end

function SceneMesh:Render()
	return Polycore.SceneMesh_Render(self.__ptr)
end

function SceneMesh:getLocalShaderOptions()
	return Polycore.SceneMesh_getLocalShaderOptions(self.__ptr)
end

function SceneMesh:getMesh()
	return Polycore.SceneMesh_getMesh(self.__ptr)
end

function SceneMesh:getTexture()
	return Polycore.SceneMesh_getTexture(self.__ptr)
end

function SceneMesh:getMaterial()
	return Polycore.SceneMesh_getMaterial(self.__ptr)
end

function SceneMesh:loadTexture(fileName, clamp)
	return Polycore.SceneMesh_loadTexture(self.__ptr, fileName, clamp)
end

function SceneMesh:loadSkeleton(fileName)
	return Polycore.SceneMesh_loadSkeleton(self.__ptr, fileName)
end

function SceneMesh:setTexture(texture)
	return Polycore.SceneMesh_setTexture(self.__ptr, texture.__ptr)
end

function SceneMesh:setMaterial(material)
	return Polycore.SceneMesh_setMaterial(self.__ptr, material.__ptr)
end

function SceneMesh:setMesh(mesh)
	return Polycore.SceneMesh_setMesh(self.__ptr, mesh.__ptr)
end

function SceneMesh:setSkeleton(skeleton)
	return Polycore.SceneMesh_setSkeleton(self.__ptr, skeleton.__ptr)
end

function SceneMesh:getSkeleton()
	return Polycore.SceneMesh_getSkeleton(self.__ptr)
end

function SceneMesh:renderMeshLocally()
	return Polycore.SceneMesh_renderMeshLocally(self.__ptr)
end

function SceneMesh:cacheToVertexBuffer(cache)
	return Polycore.SceneMesh_cacheToVertexBuffer(self.__ptr, cache)
end

