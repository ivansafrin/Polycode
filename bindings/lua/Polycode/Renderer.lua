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
	local retVal = Polycore.Renderer_setGraphicsInterface(self.__ptr, core.__ptr, graphicsInterface.__ptr)
end

function Renderer:getRenderThread()
	local retVal =  Polycore.Renderer_getRenderThread(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["RenderThread"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Renderer:createCubemap(t0, t1, t2, t3, t4, t5)
	local retVal = Polycore.Renderer_createCubemap(self.__ptr, t0.__ptr, t1.__ptr, t2.__ptr, t3.__ptr, t4.__ptr, t5.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Cubemap"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Renderer:createTexture(width, height, textureData, clamp, createMipmaps, type, filteringMode, anisotropy, framebufferTexture)
	local retVal = Polycore.Renderer_createTexture(self.__ptr, width, height, textureData.__ptr, clamp, createMipmaps, type, filteringMode, anisotropy, framebufferTexture)
	if retVal == nil then return nil end
	local __c = _G["Texture"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Renderer:createRenderBuffer(width, height, attachDepthBuffer, floatingPoint)
	local retVal = Polycore.Renderer_createRenderBuffer(self.__ptr, width, height, attachDepthBuffer, floatingPoint)
	if retVal == nil then return nil end
	local __c = _G["RenderBuffer"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Renderer:destroyRenderBuffer(buffer)
	local retVal = Polycore.Renderer_destroyRenderBuffer(self.__ptr, buffer.__ptr)
end

function Renderer:destroyTexture(texture)
	local retVal = Polycore.Renderer_destroyTexture(self.__ptr, texture.__ptr)
end

function Renderer:processDrawBuffer(buffer)
	local retVal = Polycore.Renderer_processDrawBuffer(self.__ptr, buffer.__ptr)
end

function Renderer:setBackingResolutionScale(xScale, yScale)
	local retVal = Polycore.Renderer_setBackingResolutionScale(self.__ptr, xScale, yScale)
end

function Renderer:getBackingResolutionScaleX()
	local retVal =  Polycore.Renderer_getBackingResolutionScaleX(self.__ptr)
	return retVal
end

function Renderer:getBackingResolutionScaleY()
	local retVal =  Polycore.Renderer_getBackingResolutionScaleY(self.__ptr)
	return retVal
end

function Renderer:createProgram(fileName)
	local retVal = Polycore.Renderer_createProgram(self.__ptr, fileName)
	if retVal == nil then return nil end
	local __c = _G["ShaderProgram"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Renderer:createShader(vertexProgram, fragmentProgram)
	local retVal = Polycore.Renderer_createShader(self.__ptr, vertexProgram.__ptr, fragmentProgram.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Shader"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Renderer:createVertexBuffers(mesh)
	local retVal = Polycore.Renderer_createVertexBuffers(self.__ptr, mesh.__ptr)
end

function Renderer:enqueueFrameJob(jobType, data)
	local retVal = Polycore.Renderer_enqueueFrameJob(self.__ptr, jobType, data.__ptr)
end

function Renderer:destroyProgram(program)
	local retVal = Polycore.Renderer_destroyProgram(self.__ptr, program.__ptr)
end

function Renderer:destroyShader(shader)
	local retVal = Polycore.Renderer_destroyShader(self.__ptr, shader.__ptr)
end

function Renderer:destroyBuffer(array)
	local retVal = Polycore.Renderer_destroyBuffer(self.__ptr, array.__ptr)
end

function Renderer:destroyShaderBinding(binding)
	local retVal = Polycore.Renderer_destroyShaderBinding(self.__ptr, binding.__ptr)
end

function Renderer:destroyShaderParam(param)
	local retVal = Polycore.Renderer_destroyShaderParam(self.__ptr, param.__ptr)
end

function Renderer:setTextureParam(param, texture)
	local retVal = Polycore.Renderer_setTextureParam(self.__ptr, param.__ptr, texture.__ptr)
end

function Renderer:setAnisotropyAmount(amount)
	local retVal = Polycore.Renderer_setAnisotropyAmount(self.__ptr, amount)
end

function Renderer:getAnisotropyAmount()
	local retVal =  Polycore.Renderer_getAnisotropyAmount(self.__ptr)
	return retVal
end

function Renderer:createMesh(fileName)
	local retVal = Polycore.Renderer_createMesh(self.__ptr, fileName)
	if retVal == nil then return nil end
	local __c = _G["Mesh"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Renderer:destroyMesh(mesh)
	local retVal = Polycore.Renderer_destroyMesh(self.__ptr, mesh.__ptr)
end

function Renderer.unProject(position, modelMatrix, projectionMatrix, viewport)
	local retVal = Polycore.Renderer_unProject(position.__ptr, modelMatrix.__ptr, projectionMatrix.__ptr, viewport.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Renderer.project(position, modelMatrix, projectionMatrix, viewport)
	local retVal = Polycore.Renderer_project(position.__ptr, modelMatrix.__ptr, projectionMatrix.__ptr, viewport.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Renderer:beginFrame()
	local retVal =  Polycore.Renderer_beginFrame(self.__ptr)
end

function Renderer:endFrame()
	local retVal =  Polycore.Renderer_endFrame(self.__ptr)
end

function Renderer:__delete()
	if self then Polycore.delete_Renderer(self.__ptr) end
end
