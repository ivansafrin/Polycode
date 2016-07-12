require "Polycode/ScenePrimitive"

class "SceneLabel" (ScenePrimitive)


function SceneLabel:__getvar(name)
	if name == "positionAtBaseline" then
		return Polycode.SceneLabel_get_positionAtBaseline(self.__ptr)
	end
	if ScenePrimitive["__getvar"] ~= nil then
		return ScenePrimitive.__getvar(self, name)
	end
end

function SceneLabel:__setvar(name,value)
	if name == "positionAtBaseline" then
		Polycode.SceneLabel_set_positionAtBaseline(self.__ptr, value)
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
		self.__ptr = Polycode.SceneLabel(unpack(arg))
	end
end

function SceneLabel:getText()
	local retVal =  Polycode.SceneLabel_getText(self.__ptr)
	return retVal
end

function SceneLabel:setLabelActualHeight(actualHeight)
	local retVal = Polycode.SceneLabel_setLabelActualHeight(self.__ptr, actualHeight)
end

function SceneLabel:getLabelActualHeight()
	local retVal =  Polycode.SceneLabel_getLabelActualHeight(self.__ptr)
	return retVal
end

function SceneLabel:getTextWidthForString(text)
	local retVal = Polycode.SceneLabel_getTextWidthForString(self.__ptr, text)
	return retVal
end

function SceneLabel:setText(newText)
	local retVal = Polycode.SceneLabel_setText(self.__ptr, newText)
end

function SceneLabel:updateFromLabel()
	local retVal =  Polycode.SceneLabel_updateFromLabel(self.__ptr)
end

function SceneLabel:__delete()
	if self then Polycode.delete_SceneLabel(self.__ptr) end
end
