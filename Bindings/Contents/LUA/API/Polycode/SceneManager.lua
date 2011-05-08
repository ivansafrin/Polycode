class "SceneManager"







function SceneManager:SceneManager(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.SceneManager(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function SceneManager:addScene(newScene)
	local retVal = Polycore.SceneManager_addScene(self.__ptr, newScene.__ptr)
end

function SceneManager:Update()
	local retVal =  Polycore.SceneManager_Update(self.__ptr)
end

function SceneManager:UpdateVirtual()
	local retVal =  Polycore.SceneManager_UpdateVirtual(self.__ptr)
end

function SceneManager:removeScene(scene)
	local retVal = Polycore.SceneManager_removeScene(self.__ptr, scene.__ptr)
end

function SceneManager:registerRenderTexture(r_enderTexture)
	local retVal = Polycore.SceneManager_registerRenderTexture(self.__ptr, r_enderTexture.__ptr)
end



function SceneManager:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_SceneManager(self.__ptr)
end
