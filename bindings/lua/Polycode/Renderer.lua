class "Renderer"

Renderer.BLEND_MODE_NONE = 0
Renderer.BLEND_MODE_NORMAL = 1
Renderer.BLEND_MODE_LIGHTEN = 2
Renderer.BLEND_MODE_COLOR = 3
Renderer.BLEND_MODE_PREMULTIPLIED = 4
Renderer.BLEND_MODE_MULTIPLY = 5
Renderer.BLEND_MODE_MATERIAL = 6
Renderer.DEPTH_FUNCTION_GREATER = 0
Renderer.DEPTH_FUNCTION_LEQUAL = 1

function Renderer:setBackingResolutionScale(xScale, yScale)
	local retVal = Polycode.Renderer_setBackingResolutionScale(self.__ptr, xScale, yScale)
end

function Renderer:getBackingResolutionScaleX()
	local retVal =  Polycode.Renderer_getBackingResolutionScaleX(self.__ptr)
	return retVal
end

function Renderer:getBackingResolutionScaleY()
	local retVal =  Polycode.Renderer_getBackingResolutionScaleY(self.__ptr)
	return retVal
end

function Renderer:setAnisotropyAmount(amount)
	local retVal = Polycode.Renderer_setAnisotropyAmount(self.__ptr, amount)
end

function Renderer:getAnisotropyAmount()
	local retVal =  Polycode.Renderer_getAnisotropyAmount(self.__ptr)
	return retVal
end

function Renderer:unProject(position, modelMatrix, projectionMatrix, viewport)
	local retVal = Polycode.Renderer_unProject(self.__ptr, position.__ptr, modelMatrix.__ptr, projectionMatrix.__ptr, viewport.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Renderer:project(position, modelMatrix, projectionMatrix, viewport)
	local retVal = Polycode.Renderer_project(self.__ptr, position.__ptr, modelMatrix.__ptr, projectionMatrix.__ptr, viewport.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Renderer:__delete()
	if self then Polycode.delete_Renderer(self.__ptr) end
end
