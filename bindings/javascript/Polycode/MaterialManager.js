function MaterialManager() {
	Object.defineProperties(this, {
		'premultiplyAlphaOnLoad': { enumerable: true, configurable: true, get: MaterialManager.prototype.__get_premultiplyAlphaOnLoad, set: MaterialManager.prototype.__set_premultiplyAlphaOnLoad},
		'clampDefault': { enumerable: true, configurable: true, get: MaterialManager.prototype.__get_clampDefault, set: MaterialManager.prototype.__set_clampDefault},
		'mipmapsDefault': { enumerable: true, configurable: true, get: MaterialManager.prototype.__get_mipmapsDefault, set: MaterialManager.prototype.__set_mipmapsDefault},
		'keepTextureData': { enumerable: true, configurable: true, get: MaterialManager.prototype.__get_keepTextureData, set: MaterialManager.prototype.__set_keepTextureData}
	})
}
MaterialManager.prototype.__get_premultiplyAlphaOnLoad = function() {
	return Polycode.MaterialManager__get_premultiplyAlphaOnLoad(this.__ptr)
}

MaterialManager.prototype.__set_premultiplyAlphaOnLoad = function(val) {
	Polycode.MaterialManager__set_premultiplyAlphaOnLoad(this.__ptr, val)
}

MaterialManager.prototype.__get_clampDefault = function() {
	return Polycode.MaterialManager__get_clampDefault(this.__ptr)
}

MaterialManager.prototype.__set_clampDefault = function(val) {
	Polycode.MaterialManager__set_clampDefault(this.__ptr, val)
}

MaterialManager.prototype.__get_mipmapsDefault = function() {
	return Polycode.MaterialManager__get_mipmapsDefault(this.__ptr)
}

MaterialManager.prototype.__set_mipmapsDefault = function(val) {
	Polycode.MaterialManager__set_mipmapsDefault(this.__ptr, val)
}

MaterialManager.prototype.__get_keepTextureData = function() {
	return Polycode.MaterialManager__get_keepTextureData(this.__ptr)
}

MaterialManager.prototype.__set_keepTextureData = function(val) {
	Polycode.MaterialManager__set_keepTextureData(this.__ptr, val)
}


MaterialManager.prototype.Update = function(elapsed) {
	Polycode.MaterialManager_Update(this.__ptr, elapsed)
}

MaterialManager.prototype.createTexture = function(width,height,imageData,clamp,createMipmaps,type) {
	var retVal = new Texture()
	retVal.__ptr = Polycode.MaterialManager_createTexture(this.__ptr, width,height,imageData,clamp,createMipmaps,type)
	return retVal
}

MaterialManager.prototype.createNewTexture = function(width,height,clamp,createMipmaps,type) {
	var retVal = new Texture()
	retVal.__ptr = Polycode.MaterialManager_createNewTexture(this.__ptr, width,height,clamp,createMipmaps,type)
	return retVal
}

MaterialManager.prototype.createTextureFromImage = function(image,clamp,createMipmaps) {
	var retVal = new Texture()
	retVal.__ptr = Polycode.MaterialManager_createTextureFromImage(this.__ptr, image,clamp,createMipmaps)
	return retVal
}

MaterialManager.prototype.createTextureFromFile = function(fileName,clamp,createMipmaps,resourcePool) {
	var retVal = new Texture()
	retVal.__ptr = Polycode.MaterialManager_createTextureFromFile(this.__ptr, fileName,clamp,createMipmaps,resourcePool)
	return retVal
}

MaterialManager.prototype.deleteTexture = function(texture) {
	Polycode.MaterialManager_deleteTexture(this.__ptr, texture)
}

MaterialManager.prototype.reloadTextures = function() {
	Polycode.MaterialManager_reloadTextures(this.__ptr)
}

MaterialManager.prototype.reloadProgramsAndTextures = function() {
	Polycode.MaterialManager_reloadProgramsAndTextures(this.__ptr)
}

MaterialManager.prototype.reloadPrograms = function() {
	Polycode.MaterialManager_reloadPrograms(this.__ptr)
}

MaterialManager.prototype.getTextureByResourcePath = function(resourcePath) {
	var retVal = new Texture()
	retVal.__ptr = Polycode.MaterialManager_getTextureByResourcePath(this.__ptr, resourcePath)
	return retVal
}

MaterialManager.prototype.createProgramFromFile = function(programPath) {
	var retVal = new ShaderProgram()
	retVal.__ptr = Polycode.MaterialManager_createProgramFromFile(this.__ptr, programPath)
	return retVal
}

MaterialManager.prototype.loadMaterialLibraryIntoPool = function(pool,materialFile) {
	Polycode.MaterialManager_loadMaterialLibraryIntoPool(this.__ptr, pool,materialFile)
}

MaterialManager.prototype.cubemapFromXMLNode = function(node) {
	var retVal = new Cubemap()
	retVal.__ptr = Polycode.MaterialManager_cubemapFromXMLNode(this.__ptr, node)
	return retVal
}

MaterialManager.prototype.materialFromXMLNode = function(resourcePool,node) {
	var retVal = new Material()
	retVal.__ptr = Polycode.MaterialManager_materialFromXMLNode(this.__ptr, resourcePool,node)
	return retVal
}

MaterialManager.prototype.createMaterial = function(resourcePool,materialName,shaderName) {
	var retVal = new Material()
	retVal.__ptr = Polycode.MaterialManager_createMaterial(this.__ptr, resourcePool,materialName,shaderName)
	return retVal
}

MaterialManager.prototype.setShaderFromXMLNode = function(resourcePool,node) {
	var retVal = new Shader()
	retVal.__ptr = Polycode.MaterialManager_setShaderFromXMLNode(this.__ptr, resourcePool,node)
	return retVal
}

MaterialManager.prototype.createShaderFromXMLNode = function(resourcePool,node) {
	var retVal = new Shader()
	retVal.__ptr = Polycode.MaterialManager_createShaderFromXMLNode(this.__ptr, resourcePool,node)
	return retVal
}

MaterialManager.prototype.createShader = function(resourcePool,shaderType,name,vpName,fpName,screenShader) {
	var retVal = new Shader()
	retVal.__ptr = Polycode.MaterialManager_createShader(this.__ptr, resourcePool,shaderType,name,vpName,fpName,screenShader)
	return retVal
}

MaterialManager.prototype.loadMaterialsFromFile = function(resourcePool,fileName) {
	Polycode.MaterialManager_loadMaterialsFromFile(this.__ptr, resourcePool,fileName)
}

MaterialManager.prototype.loadShadersFromFile = function(resourcePool,fileName) {
	Polycode.MaterialManager_loadShadersFromFile(this.__ptr, resourcePool,fileName)
}

MaterialManager.prototype.loadCubemapsFromFile = function(fileName) {
	Polycode.MaterialManager_loadCubemapsFromFile(this.__ptr, fileName)
}

MaterialManager.prototype.setAnisotropyAmount = function(anisotropy) {
	Polycode.MaterialManager_setAnisotropyAmount(this.__ptr, anisotropy)
}

MaterialManager.prototype.setTextureFilteringMode = function(textureFilteringMode) {
	Polycode.MaterialManager_setTextureFilteringMode(this.__ptr, textureFilteringMode)
}

MaterialManager.prototype.getTextureFilteringMode = function() {
	return Polycode.MaterialManager_getTextureFilteringMode(this.__ptr)
}

MaterialManager.prototype.addMaterial = function(material) {
	Polycode.MaterialManager_addMaterial(this.__ptr, material)
}

MaterialManager.prototype.addShader = function(shader) {
	Polycode.MaterialManager_addShader(this.__ptr, shader)
}

MaterialManager.prototype.getNumShaders = function() {
	return Polycode.MaterialManager_getNumShaders(this.__ptr)
}

MaterialManager.prototype.getShaderByIndex = function(index) {
	var retVal = new Shader()
	retVal.__ptr = Polycode.MaterialManager_getShaderByIndex(this.__ptr, index)
	return retVal
}
