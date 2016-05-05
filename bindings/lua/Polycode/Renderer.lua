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

function Renderer:createCubemap(t0, t1, t2, t3, t4, t5)
	local retVal = Polycode.Renderer_createCubemap(self.__ptr, t0.__ptr, t1.__ptr, t2.__ptr, t3.__ptr, t4.__ptr, t5.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Cubemap"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Renderer:createTexture(width, height, textureData, clamp, createMipmaps, type, filteringMode, anisotropy, framebufferTexture)
	local retVal = Polycode.Renderer_createTexture(self.__ptr, width, height, textureData.__ptr, clamp, createMipmaps, type, filteringMode, anisotropy, framebufferTexture)
	if retVal == nil then return nil end
	local __c = _G["Texture"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Renderer:createRenderBuffer(width, height, attachDepthBuffer, floatingPoint)
	local retVal = Polycode.Renderer_createRenderBuffer(self.__ptr, width, height, attachDepthBuffer, floatingPoint)
	if retVal == nil then return nil end
	local __c = _G["RenderBuffer"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Renderer:destroyRenderBuffer(buffer)
	local retVal = Polycode.Renderer_destroyRenderBuffer(self.__ptr, buffer.__ptr)
end

function Renderer:destroyTexture(texture)
	local retVal = Polycode.Renderer_destroyTexture(self.__ptr, texture.__ptr)
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

function Renderer:createProgram(fileName)
	local retVal = Polycode.Renderer_createProgram(self.__ptr, fileName)
	if retVal == nil then return nil end
	local __c = _G["ShaderProgram"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Renderer:createShader(vertexProgram, fragmentProgram)
	local retVal = Polycode.Renderer_createShader(self.__ptr, vertexProgram.__ptr, fragmentProgram.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Shader"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Renderer:createVertexBuffers(mesh)
	local retVal = Polycode.Renderer_createVertexBuffers(self.__ptr, mesh.__ptr)
end

function Renderer:enqueueFrameJob(jobType, data)
	local retVal = Polycode.Renderer_enqueueFrameJob(self.__ptr, jobType, data.__ptr)
end

function Renderer:destroyProgram(program)
	local retVal = Polycode.Renderer_destroyProgram(self.__ptr, program.__ptr)
end

function Renderer:destroyShader(shader)
	local retVal = Polycode.Renderer_destroyShader(self.__ptr, shader.__ptr)
end

function Renderer:destroyBuffer(array)
	local retVal = Polycode.Renderer_destroyBuffer(self.__ptr, array.__ptr)
end

function Renderer:destroyShaderBinding(binding)
	local retVal = Polycode.Renderer_destroyShaderBinding(self.__ptr, binding.__ptr)
end

function Renderer:destroyShaderParam(param)
	local retVal = Polycode.Renderer_destroyShaderParam(self.__ptr, param.__ptr)
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

function Renderer:createMesh(fileName)
	local retVal = Polycode.Renderer_createMesh(self.__ptr, fileName)
	if retVal == nil then return nil end
	local __c = _G["Mesh"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Renderer:destroyMesh(mesh)
	local retVal = Polycode.Renderer_destroyMesh(self.__ptr, mesh.__ptr)
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
