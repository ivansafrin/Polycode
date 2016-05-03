class "OpenGLGraphicsInterface"



function OpenGLGraphicsInterface:__getvar(name)
	if name == "lineSmooth" then
		return Polycore.OpenGLGraphicsInterface_get_lineSmooth(self.__ptr)
	end
end


function OpenGLGraphicsInterface:__setvar(name,value)
	if name == "lineSmooth" then
		Polycore.OpenGLGraphicsInterface_set_lineSmooth(self.__ptr, value)
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
		self.__ptr = Polycore.OpenGLGraphicsInterface(unpack(arg))
	end
end

function OpenGLGraphicsInterface:createTexture(texture)
	local retVal = Polycore.OpenGLGraphicsInterface_createTexture(self.__ptr, texture.__ptr)
end

function OpenGLGraphicsInterface:destroyTexture(texture)
	local retVal = Polycore.OpenGLGraphicsInterface_destroyTexture(self.__ptr, texture.__ptr)
end

function OpenGLGraphicsInterface:setViewport(x, y, width, height)
	local retVal = Polycore.OpenGLGraphicsInterface_setViewport(self.__ptr, x, y, width, height)
end

function OpenGLGraphicsInterface:clearBuffers(clearColor, colorBuffer, depthBuffer, stencilBuffer)
	local retVal = Polycore.OpenGLGraphicsInterface_clearBuffers(self.__ptr, clearColor.__ptr, colorBuffer, depthBuffer, stencilBuffer)
end

function OpenGLGraphicsInterface:setParamInShader(shader, param, localParam)
	local retVal = Polycore.OpenGLGraphicsInterface_setParamInShader(self.__ptr, shader.__ptr, param.__ptr, localParam.__ptr)
end

function OpenGLGraphicsInterface:setAttributeInShader(shader, attribute, attributeBinding)
	local retVal = Polycore.OpenGLGraphicsInterface_setAttributeInShader(self.__ptr, shader.__ptr, attribute.__ptr, attributeBinding.__ptr)
end

function OpenGLGraphicsInterface:disableAttribute(shader, attribute)
	local retVal = Polycore.OpenGLGraphicsInterface_disableAttribute(self.__ptr, shader.__ptr, attribute.__ptr)
end

function OpenGLGraphicsInterface:useShader(shader)
	local retVal = Polycore.OpenGLGraphicsInterface_useShader(self.__ptr, shader.__ptr)
end

function OpenGLGraphicsInterface:createProgram(program)
	local retVal = Polycore.OpenGLGraphicsInterface_createProgram(self.__ptr, program.__ptr)
end

function OpenGLGraphicsInterface:destroyProgram(program)
	local retVal = Polycore.OpenGLGraphicsInterface_destroyProgram(self.__ptr, program.__ptr)
end

function OpenGLGraphicsInterface:createVBOForVertexArray(array)
	local retVal = Polycore.OpenGLGraphicsInterface_createVBOForVertexArray(self.__ptr, array.__ptr)
end

function OpenGLGraphicsInterface:createMesh(mesh)
	local retVal = Polycore.OpenGLGraphicsInterface_createMesh(self.__ptr, mesh.__ptr)
end

function OpenGLGraphicsInterface:destroyMesh(mesh)
	local retVal = Polycore.OpenGLGraphicsInterface_destroyMesh(self.__ptr, mesh.__ptr)
end

function OpenGLGraphicsInterface:createShader(shader)
	local retVal = Polycore.OpenGLGraphicsInterface_createShader(self.__ptr, shader.__ptr)
end

function OpenGLGraphicsInterface:destroyShader(shader)
	local retVal = Polycore.OpenGLGraphicsInterface_destroyShader(self.__ptr, shader.__ptr)
end

function OpenGLGraphicsInterface:beginDrawCall()
	local retVal =  Polycore.OpenGLGraphicsInterface_beginDrawCall(self.__ptr)
end

function OpenGLGraphicsInterface:endDrawCall()
	local retVal =  Polycore.OpenGLGraphicsInterface_endDrawCall(self.__ptr)
end

function OpenGLGraphicsInterface:setBlendingMode(bl_endingMode)
	local retVal = Polycore.OpenGLGraphicsInterface_setBlendingMode(self.__ptr, bl_endingMode)
end

function OpenGLGraphicsInterface:createRenderBuffer(r_enderBuffer)
	local retVal = Polycore.OpenGLGraphicsInterface_createRenderBuffer(self.__ptr, r_enderBuffer.__ptr)
end

function OpenGLGraphicsInterface:destroyRenderBuffer(r_enderBuffer)
	local retVal = Polycore.OpenGLGraphicsInterface_destroyRenderBuffer(self.__ptr, r_enderBuffer.__ptr)
end

function OpenGLGraphicsInterface:bindRenderBuffer(r_enderBuffer)
	local retVal = Polycore.OpenGLGraphicsInterface_bindRenderBuffer(self.__ptr, r_enderBuffer.__ptr)
end

function OpenGLGraphicsInterface:createVertexBuffer(dataArray)
	local retVal = Polycore.OpenGLGraphicsInterface_createVertexBuffer(self.__ptr, dataArray.__ptr)
end

function OpenGLGraphicsInterface:createIndexBuffer(dataArray)
	local retVal = Polycore.OpenGLGraphicsInterface_createIndexBuffer(self.__ptr, dataArray.__ptr)
end

function OpenGLGraphicsInterface:destroyBuffer(array)
	local retVal = Polycore.OpenGLGraphicsInterface_destroyBuffer(self.__ptr, array.__ptr)
end

function OpenGLGraphicsInterface:drawIndices(type, indexArray)
	local retVal = Polycore.OpenGLGraphicsInterface_drawIndices(self.__ptr, type, indexArray.__ptr)
end

function OpenGLGraphicsInterface:drawArrays(type, vertexCount)
	local retVal = Polycore.OpenGLGraphicsInterface_drawArrays(self.__ptr, type, vertexCount)
end

function OpenGLGraphicsInterface:enableDepthTest(val)
	local retVal = Polycore.OpenGLGraphicsInterface_enableDepthTest(self.__ptr, val)
end

function OpenGLGraphicsInterface:enableDepthWrite(val)
	local retVal = Polycore.OpenGLGraphicsInterface_enableDepthWrite(self.__ptr, val)
end

function OpenGLGraphicsInterface:enableBackfaceCulling(val)
	local retVal = Polycore.OpenGLGraphicsInterface_enableBackfaceCulling(self.__ptr, val)
end

function OpenGLGraphicsInterface:setLineSize(lineSize)
	local retVal = Polycore.OpenGLGraphicsInterface_setLineSize(self.__ptr, lineSize)
end

function OpenGLGraphicsInterface:setWireframeMode(val)
	local retVal = Polycore.OpenGLGraphicsInterface_setWireframeMode(self.__ptr, val)
end

function OpenGLGraphicsInterface:enableScissor(val)
	local retVal = Polycore.OpenGLGraphicsInterface_enableScissor(self.__ptr, val)
end

function OpenGLGraphicsInterface:setScissorBox(box)
	local retVal = Polycore.OpenGLGraphicsInterface_setScissorBox(self.__ptr, box.__ptr)
end

function OpenGLGraphicsInterface:__delete()
	if self then Polycore.delete_OpenGLGraphicsInterface(self.__ptr) end
end
