class "EntityProp"


function EntityProp:__getvar(name)
	if name == "propName" then
		return Polycode.EntityProp_get_propName(self.__ptr)
	elseif name == "propValue" then
		return Polycode.EntityProp_get_propValue(self.__ptr)
	end
end

function EntityProp:__setvar(name,value)
	if name == "propName" then
		Polycode.EntityProp_set_propName(self.__ptr, value)
		return true
	elseif name == "propValue" then
		Polycode.EntityProp_set_propValue(self.__ptr, value)
		return true
	end
	return false
end
function EntityProp:__delete()
	if self then Polycode.delete_EntityProp(self.__ptr) end
end
