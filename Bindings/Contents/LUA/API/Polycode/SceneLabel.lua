require "Polycode/SceneEntity"

class "SceneLabel" (SceneEntity)

function SceneLabel:SceneLabel(fontName, text, size, scale, amode)
	if self.__ptr == nil then
		self.__ptr = Polycore.SceneLabel(fontName, text, size, scale, amode)
	end
end

function SceneLabel:testMouseCollision(x, y)
	return Polycore.SceneLabel_testMouseCollision(self.__ptr, x, y)
end

function SceneLabel:setText(newText)
	return Polycore.SceneLabel_setText(self.__ptr, newText)
end

function SceneLabel:getLabel()
	return Polycore.SceneLabel_getLabel(self.__ptr)
end

function SceneLabel:Render()
	return Polycore.SceneLabel_Render(self.__ptr)
end

