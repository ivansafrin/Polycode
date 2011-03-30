class "GenericScene"

function GenericScene:GenericScene()
	if self.__ptr == nil then
		self.__ptr = Polycore.GenericScene()
	end
end

function GenericScene:Render()
	return Polycore.GenericScene_Render(self.__ptr)
end

function GenericScene:RenderDepthOnly(targetCamera)
	return Polycore.GenericScene_RenderDepthOnly(self.__ptr, targetCamera.__ptr)
end

function GenericScene:addGrid(gridTexture)
	return Polycore.GenericScene_addGrid(self.__ptr, gridTexture)
end

function GenericScene:readString(inFile)
	return Polycore.GenericScene_readString(self.__ptr, inFile.__ptr)
end

function GenericScene:loadScene(fileName)
	return Polycore.GenericScene_loadScene(self.__ptr, fileName)
end

function GenericScene:generateLightmaps(lightMapRes, lightMapQuality, numRadPasses)
	return Polycore.GenericScene_generateLightmaps(self.__ptr, lightMapRes, lightMapQuality, numRadPasses)
end

function GenericScene:addLight(light)
	return Polycore.GenericScene_addLight(self.__ptr, light.__ptr)
end

function GenericScene:getNearestLight(pos)
	return Polycore.GenericScene_getNearestLight(self.__ptr, pos.__ptr)
end

function GenericScene:writeEntityMatrix(entity, outFile)
	return Polycore.GenericScene_writeEntityMatrix(self.__ptr, entity.__ptr, outFile.__ptr)
end

function GenericScene:writeString(str, outFile)
	return Polycore.GenericScene_writeString(self.__ptr, str, outFile.__ptr)
end

function GenericScene:saveScene(fileName)
	return Polycore.GenericScene_saveScene(self.__ptr, fileName)
end

function GenericScene:getNumStaticGeometry()
	return Polycore.GenericScene_getNumStaticGeometry(self.__ptr)
end

function GenericScene:getStaticGeometry(index)
	return Polycore.GenericScene_getStaticGeometry(self.__ptr, index)
end

function GenericScene:loadCollisionChild(entity, autoCollide, type)
	return Polycore.GenericScene_loadCollisionChild(self.__ptr, entity.__ptr, autoCollide, type)
end

function GenericScene:getNumLights()
	return Polycore.GenericScene_getNumLights(self.__ptr)
end

function GenericScene:getLight(index)
	return Polycore.GenericScene_getLight(self.__ptr, index)
end

function GenericScene:getCustomEntityByType(type)
	return Polycore.GenericScene_getCustomEntityByType(self.__ptr, type)
end

