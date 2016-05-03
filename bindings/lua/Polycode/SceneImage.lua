require "Polycode/ScenePrimitive"

class "SceneImage" (ScenePrimitive)







function SceneImage:SceneImage(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "ScenePrimitive" then
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
		self.__ptr = Polycore.SceneImage(unpack(arg))
	end
end

function SceneImage.SceneImageWithImage(image)
	local retVal = Polycore.SceneImage_SceneImageWithImage(image.__ptr)
	if retVal == nil then return nil end
	local __c = _G["SceneImage"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneImage.SceneImageWithTexture(texture)
	local retVal = Polycore.SceneImage_SceneImageWithTexture(texture.__ptr)
	if retVal == nil then return nil end
	local __c = _G["SceneImage"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneImage:Clone(deepClone, ignoreEditorOnly)
	local retVal = Polycore.SceneImage_Clone(self.__ptr, deepClone, ignoreEditorOnly)
	if retVal == nil then return nil end
	local __c = _G["Entity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneImage:applyClone(clone, deepClone, ignoreEditorOnly)
	local retVal = Polycore.SceneImage_applyClone(self.__ptr, clone.__ptr, deepClone, ignoreEditorOnly)
end

function SceneImage:setImageCoordinates(x, y, width, height, realWidth, realHeight)
	local retVal = Polycore.SceneImage_setImageCoordinates(self.__ptr, x, y, width, height, realWidth, realHeight)
end

function SceneImage:getImageWidth()
	local retVal =  Polycore.SceneImage_getImageWidth(self.__ptr)
	return retVal
end

function SceneImage:getImageHeight()
	local retVal =  Polycore.SceneImage_getImageHeight(self.__ptr)
	return retVal
end

function SceneImage:__delete()
	if self then Polycore.delete_SceneImage(self.__ptr) end
end
