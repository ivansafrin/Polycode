class "SceneManager"







function SceneManager:SceneManager(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.SceneManager(unpack(arg))
	end
end

function SceneManager:addScene(newScene)
	local retVal = Polycore.SceneManager_addScene(self.__ptr, newScene.__ptr)
end

function SceneManager:removeScene(scene)
	local retVal = Polycore.SceneManager_removeScene(self.__ptr, scene.__ptr)
end

function SceneManager:Update()
	local retVal =  Polycore.SceneManager_Update(self.__ptr)
end

function SceneManager:fixedUpdate()
	local retVal =  Polycore.SceneManager_fixedUpdate(self.__ptr)
end

function SceneManager:Render(viewport)
	local retVal = Polycore.SceneManager_Render(self.__ptr, viewport.__ptr)
end

function SceneManager:renderVirtual()
	local retVal =  Polycore.SceneManager_renderVirtual(self.__ptr)
end

function SceneManager:registerRenderTexture(r_enderTexture)
	local retVal = Polycore.SceneManager_registerRenderTexture(self.__ptr, r_enderTexture.__ptr)
end

function SceneManager:unregisterRenderTexture(r_enderTexture)
	local retVal = Polycore.SceneManager_unregisterRenderTexture(self.__ptr, r_enderTexture.__ptr)
end

function SceneManager:setRenderer(r_enderer)
	local retVal = Polycore.SceneManager_setRenderer(self.__ptr, r_enderer.__ptr)
end

function SceneManager:__delete()
	if self then Polycore.delete_SceneManager(self.__ptr) end
end
