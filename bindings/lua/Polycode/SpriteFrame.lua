class "SpriteFrame"



function SpriteFrame:__getvar(name)
	if name == "coordinates" then
		local retVal = Polycore.SpriteFrame_get_coordinates(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Rectangle"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "anchorPoint" then
		local retVal = Polycore.SpriteFrame_get_anchorPoint(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Vector2"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "frameID" then
		return Polycore.SpriteFrame_get_frameID(self.__ptr)
	end
end


function SpriteFrame:__setvar(name,value)
	if name == "coordinates" then
		Polycore.SpriteFrame_set_coordinates(self.__ptr, value.__ptr)
		return true
	elseif name == "anchorPoint" then
		Polycore.SpriteFrame_set_anchorPoint(self.__ptr, value.__ptr)
		return true
	elseif name == "frameID" then
		Polycore.SpriteFrame_set_frameID(self.__ptr, value)
		return true
	end
	return false
end


function SpriteFrame:__delete()
	if self then Polycore.delete_SpriteFrame(self.__ptr) end
end
