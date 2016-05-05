class "GPUDrawOptions"


function GPUDrawOptions:__getvar(name)
	if name == "depthTest" then
		return Polycode.GPUDrawOptions_get_depthTest(self.__ptr)
	elseif name == "depthWrite" then
		return Polycode.GPUDrawOptions_get_depthWrite(self.__ptr)
	elseif name == "linePointSize" then
		return Polycode.GPUDrawOptions_get_linePointSize(self.__ptr)
	elseif name == "alphaTest" then
		return Polycode.GPUDrawOptions_get_alphaTest(self.__ptr)
	elseif name == "backfaceCull" then
		return Polycode.GPUDrawOptions_get_backfaceCull(self.__ptr)
	elseif name == "depthOnly" then
		return Polycode.GPUDrawOptions_get_depthOnly(self.__ptr)
	elseif name == "forceMaterial" then
		return Polycode.GPUDrawOptions_get_forceMaterial(self.__ptr)
	elseif name == "blendingMode" then
		return Polycode.GPUDrawOptions_get_blendingMode(self.__ptr)
	elseif name == "scissorBox" then
		local retVal = Polycode.GPUDrawOptions_get_scissorBox(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Rectangle"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "enableScissor" then
		return Polycode.GPUDrawOptions_get_enableScissor(self.__ptr)
	elseif name == "drawColor" then
		local retVal = Polycode.GPUDrawOptions_get_drawColor(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Color"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end

function GPUDrawOptions:__setvar(name,value)
	if name == "depthTest" then
		Polycode.GPUDrawOptions_set_depthTest(self.__ptr, value)
		return true
	elseif name == "depthWrite" then
		Polycode.GPUDrawOptions_set_depthWrite(self.__ptr, value)
		return true
	elseif name == "linePointSize" then
		Polycode.GPUDrawOptions_set_linePointSize(self.__ptr, value)
		return true
	elseif name == "alphaTest" then
		Polycode.GPUDrawOptions_set_alphaTest(self.__ptr, value)
		return true
	elseif name == "backfaceCull" then
		Polycode.GPUDrawOptions_set_backfaceCull(self.__ptr, value)
		return true
	elseif name == "depthOnly" then
		Polycode.GPUDrawOptions_set_depthOnly(self.__ptr, value)
		return true
	elseif name == "forceMaterial" then
		Polycode.GPUDrawOptions_set_forceMaterial(self.__ptr, value)
		return true
	elseif name == "blendingMode" then
		Polycode.GPUDrawOptions_set_blendingMode(self.__ptr, value)
		return true
	elseif name == "scissorBox" then
		Polycode.GPUDrawOptions_set_scissorBox(self.__ptr, value.__ptr)
		return true
	elseif name == "enableScissor" then
		Polycode.GPUDrawOptions_set_enableScissor(self.__ptr, value)
		return true
	elseif name == "drawColor" then
		Polycode.GPUDrawOptions_set_drawColor(self.__ptr, value.__ptr)
		return true
	end
	return false
end
function GPUDrawOptions:__delete()
	if self then Polycode.delete_GPUDrawOptions(self.__ptr) end
end
