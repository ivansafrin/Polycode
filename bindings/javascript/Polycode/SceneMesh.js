function SceneMesh() {
}

SceneMesh.prototype.Render = function(buffer) {
	Polycode.SceneMesh_Render(this.__ptr, buffer)
}

SceneMesh.prototype.getShaderPass = function(index) {
	Polycode.SceneMesh_getShaderPass(this.__ptr, index)
}

SceneMesh.prototype.getNumShaderPasses = function() {
	Polycode.SceneMesh_getNumShaderPasses(this.__ptr)
}

SceneMesh.prototype.addShaderPass = function(pass) {
	Polycode.SceneMesh_addShaderPass(this.__ptr, pass)
}

SceneMesh.prototype.removeShaderPass = function(shaderIndex) {
	Polycode.SceneMesh_removeShaderPass(this.__ptr, shaderIndex)
}

SceneMesh.prototype.getMesh = function() {
	Polycode.SceneMesh_getMesh(this.__ptr)
}

SceneMesh.prototype.getMaterial = function() {
	Polycode.SceneMesh_getMaterial(this.__ptr)
}

SceneMesh.prototype.loadSkeleton = function(fileName) {
	Polycode.SceneMesh_loadSkeleton(this.__ptr, fileName)
}

SceneMesh.prototype.clearMaterial = function() {
	Polycode.SceneMesh_clearMaterial(this.__ptr)
}

SceneMesh.prototype.setMaterial = function(material) {
	Polycode.SceneMesh_setMaterial(this.__ptr, material)
}

SceneMesh.prototype.rebuildAttributes = function() {
	Polycode.SceneMesh_rebuildAttributes(this.__ptr)
}

SceneMesh.prototype.setMaterialByName = function(materialName,resourcePool) {
	Polycode.SceneMesh_setMaterialByName(this.__ptr, materialName,resourcePool)
}

SceneMesh.prototype.setMesh = function(mesh) {
	Polycode.SceneMesh_setMesh(this.__ptr, mesh)
}

SceneMesh.prototype.setSkeleton = function(skeleton) {
	Polycode.SceneMesh_setSkeleton(this.__ptr, skeleton)
}

SceneMesh.prototype.getSkeleton = function() {
	Polycode.SceneMesh_getSkeleton(this.__ptr)
}

SceneMesh.prototype.applySkeletonLocally = function() {
	Polycode.SceneMesh_applySkeletonLocally(this.__ptr)
}

SceneMesh.prototype.setLineWidth = function(newWidth) {
	Polycode.SceneMesh_setLineWidth(this.__ptr, newWidth)
}

SceneMesh.prototype.getFilename = function() {
	Polycode.SceneMesh_getFilename(this.__ptr)
}

SceneMesh.prototype.setFilename = function(fileName) {
	Polycode.SceneMesh_setFilename(this.__ptr, fileName)
}

SceneMesh.prototype.loadFromFile = function(fileName) {
	Polycode.SceneMesh_loadFromFile(this.__ptr, fileName)
}

SceneMesh.prototype.customHitDetection = function(ray) {
	Polycode.SceneMesh_customHitDetection(this.__ptr, ray)
}

SceneMesh.prototype.setForceMaterial = function(forceMaterial) {
	Polycode.SceneMesh_setForceMaterial(this.__ptr, forceMaterial)
}

SceneMesh.prototype.getForceMaterial = function() {
	Polycode.SceneMesh_getForceMaterial(this.__ptr)
}

SceneMesh.prototype.Clone = function(deepClone,ignoreEditorOnly) {
	Polycode.SceneMesh_Clone(this.__ptr, deepClone,ignoreEditorOnly)
}

SceneMesh.prototype.applyClone = function(clone,deepClone,ignoreEditorOnly) {
	Polycode.SceneMesh_applyClone(this.__ptr, clone,deepClone,ignoreEditorOnly)
}
