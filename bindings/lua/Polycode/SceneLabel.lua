require "Polycode/ScenePrimitive"

class "SceneLabel" (ScenePrimitive)



function SceneLabel:__getvar(name)
	if name == "positionAtBaseline" then
		return Polycore.SceneLabel_get_positionAtBaseline(self.__ptr)
	end
	if ScenePrimitive["__getvar"] ~= nil then
		return ScenePrimitive.__getvar(self, name)
	end
end


function SceneLabel:__setvar(name,value)
	if name == "positionAtBaseline" then
		Polycore.SceneLabel_set_positionAtBaseline(self.__ptr, value)
		return true
	end
	if ScenePrimitive["__setvar"] ~= nil then
		return ScenePrimitive.__setvar(self, name, value)
	else
		return false
	end
end


function SceneLabel:SceneLabel(...)
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
		self.__ptr = Polycore.SceneLabel(unpack(arg))
	end
end

function SceneLabel:getText()
	local retVal =  Polycore.SceneLabel_getText(self.__ptr)
	return retVal
end

function SceneLabel:setLabelActualHeight(actualHeight)
	local retVal = Polycore.SceneLabel_setLabelActualHeight(self.__ptr, actualHeight)
end

function SceneLabel:getLabelActualHeight()
	local retVal =  Polycore.SceneLabel_getLabelActualHeight(self.__ptr)
	return retVal
end

function SceneLabel:Render(buffer)
	local retVal = Polycore.SceneLabel_Render(self.__ptr, buffer.__ptr)
end

function SceneLabel:getTextWidthForString(text)
	local retVal = Polycore.SceneLabel_getTextWidthForString(self.__ptr, text)
	return retVal
end

function SceneLabel:setText(newText)
	local retVal = Polycore.SceneLabel_setText(self.__ptr, newText)
end

function SceneLabel:Clone(deepClone, ignoreEditorOnly)
	local retVal = Polycore.SceneLabel_Clone(self.__ptr, deepClone, ignoreEditorOnly)
	if retVal == nil then return nil end
	local __c = _G["Entity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneLabel:applyClone(clone, deepClone, ignoreEditorOnly)
	local retVal = Polycore.SceneLabel_applyClone(self.__ptr, clone.__ptr, deepClone, ignoreEditorOnly)
end

function SceneLabel:updateFromLabel()
	local retVal =  Polycore.SceneLabel_updateFromLabel(self.__ptr)
end

function SceneLabel:getLabel()
	local retVal =  Polycore.SceneLabel_getLabel(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Label"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneLabel:__delete()
	if self then Polycore.delete_SceneLabel(self.__ptr) end
end
