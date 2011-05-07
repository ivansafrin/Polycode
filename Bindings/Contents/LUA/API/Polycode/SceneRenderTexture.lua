class "SceneRenderTexture"







function SceneRenderTexture:SceneRenderTexture(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.SceneRenderTexture(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function SceneRenderTexture:drawScreen()
	local retVal =  Polycore.SceneRenderTexture_drawScreen(self.__ptr)
end

function SceneRenderTexture:getTargetTexture()
	local retVal =  Polycore.SceneRenderTexture_getTargetTexture(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Texture("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function SceneRenderTexture:getTargetScene()
	local retVal =  Polycore.SceneRenderTexture_getTargetScene(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Scene("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function SceneRenderTexture:getTargetCamera()
	local retVal =  Polycore.SceneRenderTexture_getTargetCamera(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Camera("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

