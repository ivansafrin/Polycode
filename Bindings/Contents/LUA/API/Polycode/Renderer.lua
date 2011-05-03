class "Renderer"



RENDER_MODE_NORMAL = 0
RENDER_MODE_WIREFRAME = 1
BLEND_MODE_NORMAL = 0
BLEND_MODE_LIGHTEN = 1
BLEND_MODE_COLOR = 2
FOG_LINEAR = 0
FOG_EXP = 1
FOG_EXP2 = 2
DEPTH_FUNCTION_GREATER = 0
DEPTH_FUNCTION_LEQUAL = 1
TEX_FILTERING_NEAREST = 0
TEX_FILTERING_LINEAR = 1
function Renderer:__index__(name)
	if name == "exposureLevel" then
		return Polycore.Renderer_get_exposureLevel(self.__ptr)
	end
end


function Renderer:__set_callback(name,value)
	if name == "exposureLevel" then
		Polycore.Renderer_set_exposureLevel(self.__ptr, value)
		return true
	end
	return false
end


function Renderer:Resize(xRes, yRes)
	local retVal = Polycore.Renderer_Resize(self.__ptr, xRes, yRes)
end

function Renderer:BeginRender()
	local retVal =  Polycore.Renderer_BeginRender(self.__ptr)
end

function Renderer:EndRender()
	local retVal =  Polycore.Renderer_EndRender(self.__ptr)
end

function Renderer:createCubemap(t0, t1, t2, t3, t4, t5)
	local retVal = Polycore.Renderer_createCubemap(self.__ptr, t0.__ptr, t1.__ptr, t2.__ptr, t3.__ptr, t4.__ptr, t5.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Cubemap("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Renderer:createTexture(width, height, textureData, clamp, type)
	local retVal = Polycore.Renderer_createTexture(self.__ptr, width, height, textureData.__ptr, clamp, type)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Texture("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Renderer:createRenderTextures(colorBuffer, depthBuffer, width, height)
	local retVal = Polycore.Renderer_createRenderTextures(self.__ptr, colorBuffer.__ptr, depthBuffer.__ptr, width, height)
end

function Renderer:createFramebufferTexture(width, height)
	local retVal = Polycore.Renderer_createFramebufferTexture(self.__ptr, width, height)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Texture("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Renderer:bindFrameBufferTexture(texture)
	local retVal = Polycore.Renderer_bindFrameBufferTexture(self.__ptr, texture.__ptr)
end

function Renderer:unbindFramebuffers()
	local retVal =  Polycore.Renderer_unbindFramebuffers(self.__ptr)
end

function Renderer:renderToTexture(targetTexture)
	local retVal = Polycore.Renderer_renderToTexture(self.__ptr, targetTexture.__ptr)
end

function Renderer:renderZBufferToTexture(targetTexture)
	local retVal = Polycore.Renderer_renderZBufferToTexture(self.__ptr, targetTexture.__ptr)
end

function Renderer:setViewportSize(w, h, fov)
	local retVal = Polycore.Renderer_setViewportSize(self.__ptr, w, h, fov)
end

function Renderer:loadIdentity()
	local retVal =  Polycore.Renderer_loadIdentity(self.__ptr)
end

function Renderer:setOrthoMode(xSize, ySize)
	local retVal = Polycore.Renderer_setOrthoMode(self.__ptr, xSize, ySize)
end

function Renderer:_setOrthoMode()
	local retVal =  Polycore.Renderer__setOrthoMode(self.__ptr)
end

function Renderer:setPerspectiveMode()
	local retVal =  Polycore.Renderer_setPerspectiveMode(self.__ptr)
end

function Renderer:setTexture(texture)
	local retVal = Polycore.Renderer_setTexture(self.__ptr, texture.__ptr)
end

function Renderer:enableBackfaceCulling(val)
	local retVal = Polycore.Renderer_enableBackfaceCulling(self.__ptr, val)
end

function Renderer:setClearColor(r, g, b)
	local retVal = Polycore.Renderer_setClearColor(self.__ptr, r, g, b)
end

function Renderer:setAmbientColor(r, g, b)
	local retVal = Polycore.Renderer_setAmbientColor(self.__ptr, r, g, b)
end

function Renderer:clearScreen()
	local retVal =  Polycore.Renderer_clearScreen(self.__ptr)
end

function Renderer:translate2D(x, y)
	local retVal = Polycore.Renderer_translate2D(self.__ptr, x, y)
end

function Renderer:rotate2D(angle)
	local retVal = Polycore.Renderer_rotate2D(self.__ptr, angle)
end

function Renderer:scale2D(scale)
	local retVal = Polycore.Renderer_scale2D(self.__ptr, scale.__ptr)
end

function Renderer:setFOV(fov)
	local retVal = Polycore.Renderer_setFOV(self.__ptr, fov)
end

function Renderer:setVertexColor(r, g, b, a)
	local retVal = Polycore.Renderer_setVertexColor(self.__ptr, r, g, b, a)
end

function Renderer:pushDataArrayForMesh(mesh, arrayType)
	local retVal = Polycore.Renderer_pushDataArrayForMesh(self.__ptr, mesh.__ptr, arrayType)
end

function Renderer:pushRenderDataArray(array)
	local retVal = Polycore.Renderer_pushRenderDataArray(self.__ptr, array.__ptr)
end

function Renderer:createRenderDataArrayForMesh(mesh, arrayType)
	local retVal = Polycore.Renderer_createRenderDataArrayForMesh(self.__ptr, mesh.__ptr, arrayType)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = RenderDataArray("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Renderer:createRenderDataArray(arrayType)
	local retVal = Polycore.Renderer_createRenderDataArray(self.__ptr, arrayType)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = RenderDataArray("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Renderer:setRenderArrayData(array, arrayData)
	local retVal = Polycore.Renderer_setRenderArrayData(self.__ptr, array.__ptr, arrayData.__ptr)
end

function Renderer:drawArrays(drawType)
	local retVal = Polycore.Renderer_drawArrays(self.__ptr, drawType)
end

function Renderer:translate3D(position)
	local retVal = Polycore.Renderer_translate3D(self.__ptr, position.__ptr)
end

function Renderer:scale3D(scale)
	local retVal = Polycore.Renderer_scale3D(self.__ptr, scale.__ptr)
end

function Renderer:pushMatrix()
	local retVal =  Polycore.Renderer_pushMatrix(self.__ptr)
end

function Renderer:popMatrix()
	local retVal =  Polycore.Renderer_popMatrix(self.__ptr)
end

function Renderer:setLineSmooth(val)
	local retVal = Polycore.Renderer_setLineSmooth(self.__ptr, val)
end

function Renderer:setLineSize(lineSize)
	local retVal = Polycore.Renderer_setLineSize(self.__ptr, lineSize)
end

function Renderer:enableLighting(enable)
	local retVal = Polycore.Renderer_enableLighting(self.__ptr, enable)
end

function Renderer:enableFog(enable)
	local retVal = Polycore.Renderer_enableFog(self.__ptr, enable)
end

function Renderer:setFogProperties(fogMode, color, density, startDepth, _endDepth)
	local retVal = Polycore.Renderer_setFogProperties(self.__ptr, fogMode, color.__ptr, density, startDepth, _endDepth)
end

function Renderer:multModelviewMatrix(m)
	local retVal = Polycore.Renderer_multModelviewMatrix(self.__ptr, m.__ptr)
end

function Renderer:setModelviewMatrix(m)
	local retVal = Polycore.Renderer_setModelviewMatrix(self.__ptr, m.__ptr)
end

function Renderer:setBlendingMode(bl_endingMode)
	local retVal = Polycore.Renderer_setBlendingMode(self.__ptr, bl_endingMode)
end

function Renderer:applyMaterial(material, localOptions, shaderIndex)
	local retVal = Polycore.Renderer_applyMaterial(self.__ptr, material.__ptr, localOptions.__ptr, shaderIndex)
end

function Renderer:clearShader()
	local retVal =  Polycore.Renderer_clearShader(self.__ptr)
end

function Renderer:setDepthFunction(depthFunction)
	local retVal = Polycore.Renderer_setDepthFunction(self.__ptr, depthFunction)
end

function Renderer:createVertexBufferForMesh(mesh)
	local retVal = Polycore.Renderer_createVertexBufferForMesh(self.__ptr, mesh.__ptr)
end

function Renderer:drawVertexBuffer(buffer)
	local retVal = Polycore.Renderer_drawVertexBuffer(self.__ptr, buffer.__ptr)
end

function Renderer:setRenderMode(newR_enderMode)
	local retVal = Polycore.Renderer_setRenderMode(self.__ptr, newR_enderMode)
end

function Renderer:getRenderMode()
	local retVal =  Polycore.Renderer_getRenderMode(self.__ptr)
	return retVal
end

function Renderer:enableDepthTest(val)
	local retVal = Polycore.Renderer_enableDepthTest(self.__ptr, val)
end

function Renderer:enableDepthWrite(val)
	local retVal = Polycore.Renderer_enableDepthWrite(self.__ptr, val)
end

function Renderer:billboardMatrix()
	local retVal =  Polycore.Renderer_billboardMatrix(self.__ptr)
end

function Renderer:billboardMatrixWithScale(scale)
	local retVal = Polycore.Renderer_billboardMatrixWithScale(self.__ptr, scale.__ptr)
end

function Renderer:setTextureFilteringMode(mode)
	local retVal = Polycore.Renderer_setTextureFilteringMode(self.__ptr, mode)
end

function Renderer:enableAlphaTest(val)
	local retVal = Polycore.Renderer_enableAlphaTest(self.__ptr, val)
end

function Renderer:clearBuffer(colorBuffer, depthBuffer)
	local retVal = Polycore.Renderer_clearBuffer(self.__ptr, colorBuffer, depthBuffer)
end

function Renderer:drawToColorBuffer(val)
	local retVal = Polycore.Renderer_drawToColorBuffer(self.__ptr, val)
end

function Renderer:getCameraMatrix()
	local retVal =  Polycore.Renderer_getCameraMatrix(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Matrix4("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Renderer:setCameraMatrix(matrix)
	local retVal = Polycore.Renderer_setCameraMatrix(self.__ptr, matrix.__ptr)
end

function Renderer:setCameraPosition(pos)
	local retVal = Polycore.Renderer_setCameraPosition(self.__ptr, pos.__ptr)
end

function Renderer:drawScreenQuad(qx, qy)
	local retVal = Polycore.Renderer_drawScreenQuad(self.__ptr, qx, qy)
end

function Renderer:getXRes()
	local retVal =  Polycore.Renderer_getXRes(self.__ptr)
	return retVal
end

function Renderer:getYRes()
	local retVal =  Polycore.Renderer_getYRes(self.__ptr)
	return retVal
end

function Renderer:clearLights()
	local retVal =  Polycore.Renderer_clearLights(self.__ptr)
end

function Renderer:addLight(position, direction, type, color, distance, intensity, textureMatrix)
	local retVal = Polycore.Renderer_addLight(self.__ptr, position.__ptr, direction.__ptr, type, color.__ptr, distance, intensity, textureMatrix.__ptr)
end

function Renderer:setExposureLevel(level)
	local retVal = Polycore.Renderer_setExposureLevel(self.__ptr, level)
end

function Renderer:rayTriangleIntersect(ray_origin, ray_direction, vert0, vert1, vert2, hitPoint)
	local retVal = Polycore.Renderer_rayTriangleIntersect(self.__ptr, ray_origin.__ptr, ray_direction.__ptr, vert0.__ptr, vert1.__ptr, vert2.__ptr, hitPoint.__ptr)
	return retVal
end

function Renderer:enableShaders(flag)
	local retVal = Polycore.Renderer_enableShaders(self.__ptr, flag)
end

function Renderer:addShaderModule(module)
	local retVal = Polycore.Renderer_addShaderModule(self.__ptr, module.__ptr)
end

function Renderer:test2DCoordinate(x, y, poly, matrix, billboardMode)
	local retVal = Polycore.Renderer_test2DCoordinate(self.__ptr, x, y, poly.__ptr, matrix.__ptr, billboardMode)
	return retVal
end

function Renderer:getProjectionMatrix()
	local retVal =  Polycore.Renderer_getProjectionMatrix(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Matrix4("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Renderer:getModelviewMatrix()
	local retVal =  Polycore.Renderer_getModelviewMatrix(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Matrix4("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Renderer:addShadowMap(texture)
	local retVal = Polycore.Renderer_addShadowMap(self.__ptr, texture.__ptr)
end

function Renderer:Unproject(x, y)
	local retVal = Polycore.Renderer_Unproject(self.__ptr, x, y)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Vector3("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Renderer:getNumAreaLights()
	local retVal =  Polycore.Renderer_getNumAreaLights(self.__ptr)
	return retVal
end

function Renderer:getNumSpotLights()
	local retVal =  Polycore.Renderer_getNumSpotLights(self.__ptr)
	return retVal
end

function Renderer:getNumLights()
	local retVal =  Polycore.Renderer_getNumLights(self.__ptr)
	return retVal
end

