require "Polycode/ScreenEntity"

class "ScreenMesh" (ScreenEntity)







function ScreenMesh:ScreenMesh(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.ScreenMesh(unpack(arg))
	end
end

function ScreenMesh:Render()
	local retVal =  Polycore.ScreenMesh_Render(self.__ptr)
end

function ScreenMesh:getMesh()
	local retVal =  Polycore.ScreenMesh_getMesh(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Mesh("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function ScreenMesh:getTexture()
	local retVal =  Polycore.ScreenMesh_getTexture(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Texture("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function ScreenMesh:loadTexture(fileName)
	local retVal = Polycore.ScreenMesh_loadTexture(self.__ptr, fileName)
end

function ScreenMesh:setTexture(texture)
	local retVal = Polycore.ScreenMesh_setTexture(self.__ptr, texture.__ptr)
end

