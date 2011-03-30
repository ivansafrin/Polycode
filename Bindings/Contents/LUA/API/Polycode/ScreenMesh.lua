require "Polycode/ScreenEntity"

class "ScreenMesh" (ScreenEntity)

function ScreenMesh:ScreenMesh(fileName)
	if self.__ptr == nil then
		self.__ptr = Polycore.ScreenMesh(fileName)
	end
end

function ScreenMesh:Render()
	return Polycore.ScreenMesh_Render(self.__ptr)
end

function ScreenMesh:getMesh()
	return Polycore.ScreenMesh_getMesh(self.__ptr)
end

function ScreenMesh:getTexture()
	return Polycore.ScreenMesh_getTexture(self.__ptr)
end

function ScreenMesh:loadTexture(fileName)
	return Polycore.ScreenMesh_loadTexture(self.__ptr, fileName)
end

function ScreenMesh:setTexture(texture)
	return Polycore.ScreenMesh_setTexture(self.__ptr, texture.__ptr)
end

