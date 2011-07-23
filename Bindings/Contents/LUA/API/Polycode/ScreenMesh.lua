require "Polycode/ScreenEntity"

class "ScreenMesh" (ScreenEntity)







function ScreenMesh:ScreenMesh(...)
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1]:class() == "ScreenEntity" then
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
		self.__ptr = Polycore.ScreenMesh(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function ScreenMesh:Render()
	local retVal =  Polycore.ScreenMesh_Render(self.__ptr)
end

function ScreenMesh:getMesh()
	local retVal =  Polycore.ScreenMesh_getMesh(self.__ptr)
	if retVal == nil then return nil end
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
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Texture("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function ScreenMesh:loadTexture(fileName)
	local retVal = Polycore.ScreenMesh_loadTexture(self.__ptr, fileName.__ptr)
end

function ScreenMesh:setTexture(texture)
	local retVal = Polycore.ScreenMesh_setTexture(self.__ptr, texture.__ptr)
end



function ScreenMesh:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_ScreenMesh(self.__ptr)
end
