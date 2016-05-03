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
		self.__ptr = Polycore.SceneSound(unpack(arg))
	end
end

function SceneSound:Update()
	local retVal =  Polycore.SceneSound_Update(self.__ptr)
end

function SceneSound:Clone(deepClone, ignoreEditorOnly)
	local retVal = Polycore.SceneSound_Clone(self.__ptr, deepClone, ignoreEditorOnly)
	if retVal == nil then return nil end
	local __c = _G["Entity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneSound:applyClone(clone, deepClone, ignoreEditorOnly)
	local retVal = Polycore.SceneSound_applyClone(self.__ptr, clone.__ptr, deepClone, ignoreEditorOnly)
end

function SceneSound:isDirectionalSound()
	local retVal =  Polycore.SceneSound_isDirectionalSound(self.__ptr)
	return retVal
end

function SceneSound:setDirectionalSound(val)
	local retVal = Polycore.SceneSound_setDirectionalSound(self.__ptr, val)
end

function SceneSound:getSound()
	local retVal =  Polycore.SceneSound_getSound(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Sound"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneSound:setLoopOnLoad(val)
	local retVal = Polycore.SceneSound_setLoopOnLoad(self.__ptr, val)
end

function SceneSound:getLoopOnLoad()
	local retVal =  Polycore.SceneSound_getLoopOnLoad(self.__ptr)
	return retVal
end

function SceneSound:__delete()
	if self then Polycore.delete_SceneSound(self.__ptr) end
end
