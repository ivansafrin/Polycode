function MaterialManager() {
}

MaterialManager.prototype.Update = function(elapsed) {
	Polycode.MaterialManager_Update(this.__ptr, elapsed)
}

MaterialManager.prototype.createTexture = function(width,height,imageData,clamp,createMipmaps,type) {
	Polycode.MaterialManager_createTexture(this.__ptr, width,height,imageData,clamp,createMipmaps,type)
}

MaterialManager.prototype.createNewTexture = function(width,height,clamp,createMipmaps,type) {
	Polycode.MaterialManager_createNewTexture(this.__ptr, width,height,clamp,createMipmaps,type)
}

MaterialManager.prototype.createTextureFromImage = function(image,clamp,createMipmaps) {
	Polycode.MaterialManager_createTextureFromImage(this.__ptr, image,clamp,createMipmaps)
}

MaterialManager.prototype.createTextureFromFile = function(fileName,clamp,createMipmaps,resourcePool) {
	Polycode.MaterialManager_createTextureFromFile(this.__ptr, fileName,clamp,createMipmaps,resourcePool)
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
	Polycode.MaterialManager_getTextureByResourcePath(this.__ptr, resourcePath)
}

MaterialManager.prototype.createProgramFromFile = function(programPath) {
	Polycode.MaterialManager_createProgramFromFile(this.__ptr, programPath)
}

MaterialManager.prototype.loadMaterialLibraryIntoPool = function(pool,materialFile) {
	Polycode.MaterialManager_loadMaterialLibraryIntoPool(this.__ptr, pool,materialFile)
}

MaterialManager.prototype.cubemapFromXMLNode = function(node) {
	Polycode.MaterialManager_cubemapFromXMLNode(this.__ptr, node)
}

MaterialManager.prototype.materialFromXMLNode = function(resourcePool,node) {
	Polycode.MaterialManager_materialFromXMLNode(this.__ptr, resourcePool,node)
}

MaterialManager.prototype.createMaterial = function(resourcePool,materialName,shaderName) {
	Polycode.MaterialManager_createMaterial(this.__ptr, resourcePool,materialName,shaderName)
}

MaterialManager.prototype.setShaderFromXMLNode = function(resourcePool,node) {
	Polycode.MaterialManager_setShaderFromXMLNode(this.__ptr, resourcePool,node)
}

MaterialManager.prototype.createShaderFromXMLNode = function(resourcePool,node) {
	Polycode.MaterialManager_createShaderFromXMLNode(this.__ptr, resourcePool,node)
}

MaterialManager.prototype.createShader = function(resourcePool,shaderType,name,vpName,fpName,screenShader) {
	Polycode.MaterialManager_createShader(this.__ptr, resourcePool,shaderType,name,vpName,fpName,screenShader)
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
	Polycode.MaterialManager_getTextureFilteringMode(this.__ptr)
}

MaterialManager.prototype.addMaterial = function(material) {
	Polycode.MaterialManager_addMaterial(this.__ptr, material)
}

MaterialManager.prototype.addShader = function(shader) {
	Polycode.MaterialManager_addShader(this.__ptr, shader)
}

MaterialManager.prototype.getNumShaders = function() {
	Polycode.MaterialManager_getNumShaders(this.__ptr)
}

MaterialManager.prototype.getShaderByIndex = function(index) {
	Polycode.MaterialManager_getShaderByIndex(this.__ptr, index)
}
