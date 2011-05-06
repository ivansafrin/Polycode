require "Polycode/Scene"

class "GenericScene" (Scene)



ENTITY_MESH = 0
ENTITY_LIGHT = 1
ENTITY_CAMERA = 2
ENTITY_ENTITY = 3
ENTITY_COLLMESH = 4




function GenericScene:GenericScene(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.GenericScene(unpack(arg))
	end
end

function GenericScene:Render()
	local retVal =  Polycore.GenericScene_Render(self.__ptr)
end

function GenericScene:RenderDepthOnly(targetCamera)
	local retVal = Polycore.GenericScene_RenderDepthOnly(self.__ptr, targetCamera.__ptr)
end

function GenericScene:addGrid(gridTexture)
	local retVal = Polycore.GenericScene_addGrid(self.__ptr, gridTexture)
end

function GenericScene:readString(inFile)
	local retVal = Polycore.GenericScene_readString(inFile.__ptr)
	return retVal
end

function GenericScene:loadScene(fileName)
	local retVal = Polycore.GenericScene_loadScene(self.__ptr, fileName)
end

function GenericScene:generateLightmaps(lightMapRes, lightMapQuality, numRadPasses)
	local retVal = Polycore.GenericScene_generateLightmaps(self.__ptr, lightMapRes, lightMapQuality, numRadPasses)
end

function GenericScene:addLight(light)
	local retVal = Polycore.GenericScene_addLight(self.__ptr, light.__ptr)
end

function GenericScene:getNearestLight(pos)
	local retVal = Polycore.GenericScene_getNearestLight(self.__ptr, pos.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = SceneLight("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function GenericScene:writeEntityMatrix(entity, outFile)
	local retVal = Polycore.GenericScene_writeEntityMatrix(self.__ptr, entity.__ptr, outFile.__ptr)
end

function GenericScene:writeString(str, outFile)
	local retVal = Polycore.GenericScene_writeString(self.__ptr, str, outFile.__ptr)
end

function GenericScene:saveScene(fileName)
	local retVal = Polycore.GenericScene_saveScene(self.__ptr, fileName)
end

function GenericScene:getNumStaticGeometry()
	local retVal =  Polycore.GenericScene_getNumStaticGeometry(self.__ptr)
	return retVal
end

function GenericScene:getStaticGeometry(index)
	local retVal = Polycore.GenericScene_getStaticGeometry(self.__ptr, index)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = SceneMesh("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function GenericScene:loadCollisionChild(entity, autoCollide, type)
	local retVal = Polycore.GenericScene_loadCollisionChild(self.__ptr, entity.__ptr, autoCollide, type)
end

function GenericScene:getNumLights()
	local retVal =  Polycore.GenericScene_getNumLights(self.__ptr)
	return retVal
end

function GenericScene:getLight(index)
	local retVal = Polycore.GenericScene_getLight(self.__ptr, index)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = SceneLight("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function GenericScene:getCustomEntityByType(type)
	local retVal = Polycore.GenericScene_getCustomEntityByType(self.__ptr, type)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = SceneEntity("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

