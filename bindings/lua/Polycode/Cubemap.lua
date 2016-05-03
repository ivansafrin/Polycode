require "Polycode/Resource"

class "Cubemap" (Resource)



Cubemap.CUBEMAP_XPOS = 0
Cubemap.CUBEMAP_XNEG = 1
Cubemap.CUBEMAP_YPOS = 2
Cubemap.CUBEMAP_YNEG = 3
Cubemap.CUBEMAP_ZPOS = 4
Cubemap.CUBEMAP_ZNEG = 5




function Cubemap:Cubemap(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "Resource" then
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
		self.__ptr = Polycore.Cubemap(unpack(arg))
	end
end

function Cubemap:getTexture(index)
	local retVal = Polycore.Cubemap_getTexture(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["Texture"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Cubemap:setTexture(texture, index)
	local retVal = Polycore.Cubemap_setTexture(self.__ptr, texture.__ptr, index)
end

function Cubemap:recreateFromTextures()
	local retVal =  Polycore.Cubemap_recreateFromTextures(self.__ptr)
end

function Cubemap:__delete()
	if self then Polycore.delete_Cubemap(self.__ptr) end
end
