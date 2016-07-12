require "Polycode/Entity"

class "SceneSound" (Entity)


function SceneSound:SceneSound(...)
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
		self.__ptr = Polycode.SceneSound(unpack(arg))
	end
end

function SceneSound:Update()
	local retVal =  Polycode.SceneSound_Update(self.__ptr)
end

function SceneSound:isDirectionalSound()
	local retVal =  Polycode.SceneSound_isDirectionalSound(self.__ptr)
	return retVal
end

function SceneSound:setDirectionalSound(val)
	local retVal = Polycode.SceneSound_setDirectionalSound(self.__ptr, val)
end

function SceneSound:setLoopOnLoad(val)
	local retVal = Polycode.SceneSound_setLoopOnLoad(self.__ptr, val)
end

function SceneSound:getLoopOnLoad()
	local retVal =  Polycode.SceneSound_getLoopOnLoad(self.__ptr)
	return retVal
end

function SceneSound:__delete()
	if self then Polycode.delete_SceneSound(self.__ptr) end
end
