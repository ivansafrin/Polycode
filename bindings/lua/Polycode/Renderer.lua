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

function Renderer:setGraphicsInterface(core, graphicsInterface)
	local retVal = Polycode.Renderer_setGraphicsInterface(self.__ptr, core.__ptr, graphicsInterface.__ptr)
end

function Renderer:getRenderThread()
	local retVal =  Polycode.Renderer_getRenderThread(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["RenderThread"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Renderer:processDrawBuffer(buffer)
	local retVal = Polycode.Renderer_processDrawBuffer(self.__ptr, buffer.__ptr)
end

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

function Renderer:enqueueFrameJob(jobType, data)
	local retVal = Polycode.Renderer_enqueueFrameJob(self.__ptr, jobType, data.__ptr)
end

function Renderer:destroyRenderBufferPlatformData(platformData)
	local retVal = Polycode.Renderer_destroyRenderBufferPlatformData(self.__ptr, platformData.__ptr)
end

function Renderer:destroyTexturePlatformData(platformData)
	local retVal = Polycode.Renderer_destroyTexturePlatformData(self.__ptr, platformData.__ptr)
end

function Renderer:destroyProgramPlatformData(platformData)
	local retVal = Polycode.Renderer_destroyProgramPlatformData(self.__ptr, platformData.__ptr)
end

function Renderer:destroyShaderPlatformData(platformData)
	local retVal = Polycode.Renderer_destroyShaderPlatformData(self.__ptr, platformData.__ptr)
end

function Renderer:destroySubmeshPlatformData(platformData)
	local retVal = Polycode.Renderer_destroySubmeshPlatformData(self.__ptr, platformData.__ptr)
end

function Renderer:setTextureParam(param, texture)
	local retVal = Polycode.Renderer_setTextureParam(self.__ptr, param.__ptr, texture.__ptr)
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

function Renderer:beginFrame()
	local retVal =  Polycode.Renderer_beginFrame(self.__ptr)
end

function Renderer:endFrame()
	local retVal =  Polycode.Renderer_endFrame(self.__ptr)
end

function Renderer:__delete()
	if self then Polycode.delete_Renderer(self.__ptr) end
end
