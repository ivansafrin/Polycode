require "Polycode/Resource"

class "Sprite" (Resource)







function Sprite:Sprite(...)
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
		self.__ptr = Polycore.Sprite(unpack(arg))
	end
end

function Sprite:getName()
	local retVal =  Polycore.Sprite_getName(self.__ptr)
	return retVal
end

function Sprite:setName(name)
	local retVal = Polycore.Sprite_setName(self.__ptr, name)
end

function Sprite:addSpriteState(state)
	local retVal = Polycore.Sprite_addSpriteState(self.__ptr, state.__ptr)
end

function Sprite:removeSpriteState(state)
	local retVal = Polycore.Sprite_removeSpriteState(self.__ptr, state.__ptr)
end

function Sprite:getNumStates()
	local retVal =  Polycore.Sprite_getNumStates(self.__ptr)
	return retVal
end

function Sprite:getState(index)
	local retVal = Polycore.Sprite_getState(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["SpriteState"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Sprite:getStateByName(name)
	local retVal = Polycore.Sprite_getStateByName(self.__ptr, name)
	if retVal == nil then return nil end
	local __c = _G["SpriteState"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Sprite:setParentSpritSet(spriteSet)
	local retVal = Polycore.Sprite_setParentSpritSet(self.__ptr, spriteSet.__ptr)
end

function Sprite:getParentSpriteSet()
	local retVal =  Polycore.Sprite_getParentSpriteSet(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["SpriteSet"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Sprite:__delete()
	if self then Polycore.delete_Sprite(self.__ptr) end
end
