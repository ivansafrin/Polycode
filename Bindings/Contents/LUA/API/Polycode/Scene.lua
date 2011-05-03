require "Polycode/EventDispatcher"

class "Scene" (EventDispatcher)



ENTITY_MESH = 0
ENTITY_LIGHT = 1
ENTITY_CAMERA = 2
ENTITY_ENTITY = 3
ENTITY_COLLMESH = 4




function Scene:Scene(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.Scene(unpack(arg))
	end
end

function Scene:addEntity(entity)
	local retVal = Polycore.Scene_addEntity(self.__ptr, entity.__ptr)
end

function Scene:removeEntity(entity)
	local retVal = Polycore.Scene_removeEntity(self.__ptr, entity.__ptr)
end

function Scene:getDefaultCamera()
	local retVal =  Polycore.Scene_getDefaultCamera(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Camera("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Scene:enableLighting(enable)
	local retVal = Polycore.Scene_enableLighting(self.__ptr, enable)
end

function Scene:enableFog(enable)
	local retVal = Polycore.Scene_enableFog(self.__ptr, enable)
end

function Scene:setFogProperties(fogMode, color, density, startDepth, _endDepth)
	local retVal = Polycore.Scene_setFogProperties(self.__ptr, fogMode, color.__ptr, density, startDepth, _endDepth)
end

function Scene:Update()
	local retVal =  Polycore.Scene_Update(self.__ptr)
end

function Scene:setVirtual(val)
	local retVal = Polycore.Scene_setVirtual(self.__ptr, val)
end

function Scene:isVirtual()
	local retVal =  Polycore.Scene_isVirtual(self.__ptr)
	return retVal
end

function Scene:isEnabled()
	local retVal =  Polycore.Scene_isEnabled(self.__ptr)
	return retVal
end

function Scene:setEnabled(enabled)
	local retVal = Polycore.Scene_setEnabled(self.__ptr, enabled)
end

function Scene:getNumEntities()
	local retVal =  Polycore.Scene_getNumEntities(self.__ptr)
	return retVal
end

function Scene:getEntity(index)
	local retVal = Polycore.Scene_getEntity(self.__ptr, index)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = SceneEntity("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Scene:getEntityAtCursor(x, y)
	local retVal = Polycore.Scene_getEntityAtCursor(self.__ptr, x, y)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = SceneEntity("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Scene:Render()
	local retVal =  Polycore.Scene_Render(self.__ptr)
end

function Scene:RenderDepthOnly(targetCamera)
	local retVal = Polycore.Scene_RenderDepthOnly(self.__ptr, targetCamera.__ptr)
end

function Scene:readString(inFile)
	local retVal = Polycore.Scene_readString(inFile.__ptr)
	return retVal
end

function Scene:loadScene(fileName)
	local retVal = Polycore.Scene_loadScene(self.__ptr, fileName)
end

function Scene:generateLightmaps(lightMapRes, lightMapQuality, numRadPasses)
	local retVal = Polycore.Scene_generateLightmaps(self.__ptr, lightMapRes, lightMapQuality, numRadPasses)
end

function Scene:addLight(light)
	local retVal = Polycore.Scene_addLight(self.__ptr, light.__ptr)
end

function Scene:getNearestLight(pos)
	local retVal = Polycore.Scene_getNearestLight(self.__ptr, pos.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = SceneLight("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Scene:writeEntityMatrix(entity, outFile)
	local retVal = Polycore.Scene_writeEntityMatrix(self.__ptr, entity.__ptr, outFile.__ptr)
end

function Scene:writeString(str, outFile)
	local retVal = Polycore.Scene_writeString(self.__ptr, str, outFile.__ptr)
end

function Scene:saveScene(fileName)
	local retVal = Polycore.Scene_saveScene(self.__ptr, fileName)
end

function Scene:getNumStaticGeometry()
	local retVal =  Polycore.Scene_getNumStaticGeometry(self.__ptr)
	return retVal
end

function Scene:getStaticGeometry(index)
	local retVal = Polycore.Scene_getStaticGeometry(self.__ptr, index)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = SceneMesh("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Scene:loadCollisionChild(entity, autoCollide, type)
	local retVal = Polycore.Scene_loadCollisionChild(self.__ptr, entity.__ptr, autoCollide, type)
end

function Scene:getNumLights()
	local retVal =  Polycore.Scene_getNumLights(self.__ptr)
	return retVal
end

function Scene:getLight(index)
	local retVal = Polycore.Scene_getLight(self.__ptr, index)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = SceneLight("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Scene:getCustomEntityByType(type)
	local retVal = Polycore.Scene_getCustomEntityByType(self.__ptr, type)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = SceneEntity("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

