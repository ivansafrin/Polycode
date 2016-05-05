class "OpenGLGraphicsInterface"


function OpenGLGraphicsInterface:__getvar(name)
	if name == "lineSmooth" then
		return Polycode.OpenGLGraphicsInterface_get_lineSmooth(self.__ptr)
	end
end

function OpenGLGraphicsInterface:__setvar(name,value)
	if name == "lineSmooth" then
		Polycode.OpenGLGraphicsInterface_set_lineSmooth(self.__ptr, value)
		return true
	end
	return false
end
function OpenGLGraphicsInterface:OpenGLGraphicsInterface(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.OpenGLGraphicsInterface(unpack(arg))
	end
end

function OpenGLGraphicsInterface:createTexture(texture)
	local retVal = Polycode.OpenGLGraphicsInterface_createTexture(self.__ptr, texture.__ptr)
end

function OpenGLGraphicsInterface:destroyTexture(texture)
	local retVal = Polycode.OpenGLGraphicsInterface_destroyTexture(self.__ptr, texture.__ptr)
end

function OpenGLGraphicsInterface:setViewport(x, y, width, height)
	local retVal = Polycode.OpenGLGraphicsInterface_setViewport(self.__ptr, x, y, width, height)
end

function OpenGLGraphicsInterface:clearBuffers(clearColor, colorBuffer, depthBuffer, stencilBuffer)
	local retVal = Polycode.OpenGLGraphicsInterface_clearBuffers(self.__ptr, clearColor.__ptr, colorBuffer, depthBuffer, stencilBuffer)
end

function OpenGLGraphicsInterface:setParamInShader(shader, param, localParam)
	local retVal = Polycode.OpenGLGraphicsInterface_setParamInShader(self.__ptr, shader.__ptr, param.__ptr, localParam.__ptr)
end

function OpenGLGraphicsInterface:setAttributeInShader(shader, attribute, attributeBinding)
	local retVal = Polycode.OpenGLGraphicsInterface_setAttributeInShader(self.__ptr, shader.__ptr, attribute.__ptr, attributeBinding.__ptr)
end

function OpenGLGraphicsInterface:disableAttribute(shader, attribute)
	local retVal = Polycode.OpenGLGraphicsInterface_disableAttribute(self.__ptr, shader.__ptr, attribute.__ptr)
end

function OpenGLGraphicsInterface:useShader(shader)
	local retVal = Polycode.OpenGLGraphicsInterface_useShader(self.__ptr, shader.__ptr)
end

function OpenGLGraphicsInterface:createProgram(program)
	local retVal = Polycode.OpenGLGraphicsInterface_createProgram(self.__ptr, program.__ptr)
end

function OpenGLGraphicsInterface:destroyProgram(program)
	local retVal = Polycode.OpenGLGraphicsInterface_destroyProgram(self.__ptr, program.__ptr)
end

function OpenGLGraphicsInterface:createVBOForVertexArray(array)
	local retVal = Polycode.OpenGLGraphicsInterface_createVBOForVertexArray(self.__ptr, array.__ptr)
end

function OpenGLGraphicsInterface:createMesh(mesh)
	local retVal = Polycode.OpenGLGraphicsInterface_createMesh(self.__ptr, mesh.__ptr)
end

function OpenGLGraphicsInterface:destroyMesh(mesh)
	local retVal = Polycode.OpenGLGraphicsInterface_destroyMesh(self.__ptr, mesh.__ptr)
end

function OpenGLGraphicsInterface:createShader(shader)
	local retVal = Polycode.OpenGLGraphicsInterface_createShader(self.__ptr, shader.__ptr)
end

function OpenGLGraphicsInterface:destroyShader(shader)
	local retVal = Polycode.OpenGLGraphicsInterface_destroyShader(self.__ptr, shader.__ptr)
end

function OpenGLGraphicsInterface:beginDrawCall()
	local retVal =  Polycode.OpenGLGraphicsInterface_beginDrawCall(self.__ptr)
end

function OpenGLGraphicsInterface:endDrawCall()
	local retVal =  Polycode.OpenGLGraphicsInterface_endDrawCall(self.__ptr)
end

function OpenGLGraphicsInterface:setBlendingMode(blendingMode)
	local retVal = Polycode.OpenGLGraphicsInterface_setBlendingMode(self.__ptr, blendingMode)
end

function OpenGLGraphicsInterface:createRenderBuffer(renderBuffer)
	local retVal = Polycode.OpenGLGraphicsInterface_createRenderBuffer(self.__ptr, renderBuffer.__ptr)
end

function OpenGLGraphicsInterface:destroyRenderBuffer(renderBuffer)
	local retVal = Polycode.OpenGLGraphicsInterface_destroyRenderBuffer(self.__ptr, renderBuffer.__ptr)
end

function OpenGLGraphicsInterface:bindRenderBuffer(renderBuffer)
	local retVal = Polycode.OpenGLGraphicsInterface_bindRenderBuffer(self.__ptr, renderBuffer.__ptr)
end

function OpenGLGraphicsInterface:createVertexBuffer(dataArray)
	local retVal = Polycode.OpenGLGraphicsInterface_createVertexBuffer(self.__ptr, dataArray.__ptr)
end

function OpenGLGraphicsInterface:createIndexBuffer(dataArray)
	local retVal = Polycode.OpenGLGraphicsInterface_createIndexBuffer(self.__ptr, dataArray.__ptr)
end

function OpenGLGraphicsInterface:destroyBuffer(array)
	local retVal = Polycode.OpenGLGraphicsInterface_destroyBuffer(self.__ptr, array.__ptr)
end

function OpenGLGraphicsInterface:drawIndices(type, indexArray)
	local retVal = Polycode.OpenGLGraphicsInterface_drawIndices(self.__ptr, type, indexArray.__ptr)
end

function OpenGLGraphicsInterface:drawArrays(type, vertexCount)
	local retVal = Polycode.OpenGLGraphicsInterface_drawArrays(self.__ptr, type, vertexCount)
end

function OpenGLGraphicsInterface:enableDepthTest(val)
	local retVal = Polycode.OpenGLGraphicsInterface_enableDepthTest(self.__ptr, val)
end

function OpenGLGraphicsInterface:enableDepthWrite(val)
	local retVal = Polycode.OpenGLGraphicsInterface_enableDepthWrite(self.__ptr, val)
end

function OpenGLGraphicsInterface:enableBackfaceCulling(val)
	local retVal = Polycode.OpenGLGraphicsInterface_enableBackfaceCulling(self.__ptr, val)
end

function OpenGLGraphicsInterface:setLineSize(lineSize)
	local retVal = Polycode.OpenGLGraphicsInterface_setLineSize(self.__ptr, lineSize)
end

function OpenGLGraphicsInterface:setWireframeMode(val)
	local retVal = Polycode.OpenGLGraphicsInterface_setWireframeMode(self.__ptr, val)
end

function OpenGLGraphicsInterface:enableScissor(val)
	local retVal = Polycode.OpenGLGraphicsInterface_enableScissor(self.__ptr, val)
end

function OpenGLGraphicsInterface:setScissorBox(box)
	local retVal = Polycode.OpenGLGraphicsInterface_setScissorBox(self.__ptr, box.__ptr)
end

function OpenGLGraphicsInterface:__delete()
	if self then Polycode.delete_OpenGLGraphicsInterface(self.__ptr) end
end
