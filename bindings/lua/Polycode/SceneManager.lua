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
		self.__ptr = Polycode.SceneManager(unpack(arg))
	end
end

function SceneManager:Update()
	local retVal =  Polycode.SceneManager_Update(self.__ptr)
end

function SceneManager:fixedUpdate()
	local retVal =  Polycode.SceneManager_fixedUpdate(self.__ptr)
end

function SceneManager:Render(viewport)
	local retVal = Polycode.SceneManager_Render(self.__ptr, viewport.__ptr)
end

function SceneManager:renderVirtual()
	local retVal =  Polycode.SceneManager_renderVirtual(self.__ptr)
end

function SceneManager:__delete()
	if self then Polycode.delete_SceneManager(self.__ptr) end
end
