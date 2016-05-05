class "GPUDrawCall"


function GPUDrawCall:__getvar(name)
	if name == "mesh" then
		local retVal = Polycode.GPUDrawCall_get_mesh(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Mesh"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "options" then
		local retVal = Polycode.GPUDrawCall_get_options(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["GPUDrawOptions"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "modelMatrix" then
		local retVal = Polycode.GPUDrawCall_get_modelMatrix(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Matrix4"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "material" then
		local retVal = Polycode.GPUDrawCall_get_material(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Material"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end

function GPUDrawCall:__setvar(name,value)
	if name == "mesh" then
		Polycode.GPUDrawCall_set_mesh(self.__ptr, value.__ptr)
		return true
	elseif name == "options" then
		Polycode.GPUDrawCall_set_options(self.__ptr, value.__ptr)
		return true
	elseif name == "modelMatrix" then
		Polycode.GPUDrawCall_set_modelMatrix(self.__ptr, value.__ptr)
		return true
	elseif name == "material" then
		Polycode.GPUDrawCall_set_material(self.__ptr, value.__ptr)
		return true
	end
	return false
end
function GPUDrawCall:__delete()
	if self then Polycode.delete_GPUDrawCall(self.__ptr) end
end
