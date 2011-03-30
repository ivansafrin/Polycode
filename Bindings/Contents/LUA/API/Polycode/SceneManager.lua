class "SceneManager"

function SceneManager:SceneManager()
	if self.__ptr == nil then
		self.__ptr = Polycore.SceneManager()
	end
end

function SceneManager:addScene(newScene)
	return Polycore.SceneManager_addScene(self.__ptr, newScene.__ptr)
end

function SceneManager:Update()
	return Polycore.SceneManager_Update(self.__ptr)
end

function SceneManager:UpdateVirtual()
	return Polycore.SceneManager_UpdateVirtual(self.__ptr)
end

function SceneManager:removeScene(scene)
	return Polycore.SceneManager_removeScene(self.__ptr, scene.__ptr)
end

function SceneManager:registerRenderTexture(r_enderTexture)
	return Polycore.SceneManager_registerRenderTexture(self.__ptr, r_enderTexture.__ptr)
end

