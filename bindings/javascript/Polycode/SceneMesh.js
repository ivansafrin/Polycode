function SceneMesh() {
	Object.defineProperties(this, {
		'lineWidth': { enumerable: true, configurable: true, get: SceneMesh.prototype.__get_lineWidth, set: SceneMesh.prototype.__set_lineWidth},
		'lineSmooth': { enumerable: true, configurable: true, get: SceneMesh.prototype.__get_lineSmooth, set: SceneMesh.prototype.__set_lineSmooth},
		'pointSmooth': { enumerable: true, configurable: true, get: SceneMesh.prototype.__get_pointSmooth, set: SceneMesh.prototype.__set_pointSmooth},
		'useGeometryHitDetection': { enumerable: true, configurable: true, get: SceneMesh.prototype.__get_useGeometryHitDetection, set: SceneMesh.prototype.__set_useGeometryHitDetection},
		'alphaTest': { enumerable: true, configurable: true, get: SceneMesh.prototype.__get_alphaTest, set: SceneMesh.prototype.__set_alphaTest},
		'backfaceCulled': { enumerable: true, configurable: true, get: SceneMesh.prototype.__get_backfaceCulled, set: SceneMesh.prototype.__set_backfaceCulled},
		'sendBoneMatricesToMaterial': { enumerable: true, configurable: true, get: SceneMesh.prototype.__get_sendBoneMatricesToMaterial, set: SceneMesh.prototype.__set_sendBoneMatricesToMaterial}
	})
}
SceneMesh.prototype.__get_lineWidth = function() {
	return Polycode.SceneMesh__get_lineWidth(this.__ptr)
}

SceneMesh.prototype.__set_lineWidth = function(val) {
	Polycode.SceneMesh__set_lineWidth(this.__ptr, val)
}

SceneMesh.prototype.__get_lineSmooth = function() {
	return Polycode.SceneMesh__get_lineSmooth(this.__ptr)
}

SceneMesh.prototype.__set_lineSmooth = function(val) {
	Polycode.SceneMesh__set_lineSmooth(this.__ptr, val)
}

SceneMesh.prototype.__get_pointSmooth = function() {
	return Polycode.SceneMesh__get_pointSmooth(this.__ptr)
}

SceneMesh.prototype.__set_pointSmooth = function(val) {
	Polycode.SceneMesh__set_pointSmooth(this.__ptr, val)
}

SceneMesh.prototype.__get_useGeometryHitDetection = function() {
	return Polycode.SceneMesh__get_useGeometryHitDetection(this.__ptr)
}

SceneMesh.prototype.__set_useGeometryHitDetection = function(val) {
	Polycode.SceneMesh__set_useGeometryHitDetection(this.__ptr, val)
}

SceneMesh.prototype.__get_alphaTest = function() {
	return Polycode.SceneMesh__get_alphaTest(this.__ptr)
}

SceneMesh.prototype.__set_alphaTest = function(val) {
	Polycode.SceneMesh__set_alphaTest(this.__ptr, val)
}

SceneMesh.prototype.__get_backfaceCulled = function() {
	return Polycode.SceneMesh__get_backfaceCulled(this.__ptr)
}

SceneMesh.prototype.__set_backfaceCulled = function(val) {
	Polycode.SceneMesh__set_backfaceCulled(this.__ptr, val)
}

SceneMesh.prototype.__get_sendBoneMatricesToMaterial = function() {
	return Polycode.SceneMesh__get_sendBoneMatricesToMaterial(this.__ptr)
}

SceneMesh.prototype.__set_sendBoneMatricesToMaterial = function(val) {
	Polycode.SceneMesh__set_sendBoneMatricesToMaterial(this.__ptr, val)
}


SceneMesh.prototype.Render = function(buffer) {
	Polycode.SceneMesh_Render(this.__ptr, buffer)
}

SceneMesh.prototype.getShaderPass = function(index) {
	var retVal = new ShaderPass()
	retVal.__ptr = Polycode.SceneMesh_getShaderPass(this.__ptr, index)
	return retVal
}

SceneMesh.prototype.getNumShaderPasses = function() {
	return Polycode.SceneMesh_getNumShaderPasses(this.__ptr)
}

SceneMesh.prototype.addShaderPass = function(pass) {
	Polycode.SceneMesh_addShaderPass(this.__ptr, pass)
}

SceneMesh.prototype.removeShaderPass = function(shaderIndex) {
	Polycode.SceneMesh_removeShaderPass(this.__ptr, shaderIndex)
}

SceneMesh.prototype.getMesh = function() {
	var retVal = new shared_ptr<Mesh>()
	retVal.__ptr = Polycode.SceneMesh_getMesh(this.__ptr)
	return retVal
}

SceneMesh.prototype.getMaterial = function() {
	var retVal = new shared_ptr<Material>()
	retVal.__ptr = Polycode.SceneMesh_getMaterial(this.__ptr)
	return retVal
}

SceneMesh.prototype.loadSkeleton = function(fileName) {
	var retVal = new shared_ptr<Skeleton>()
	retVal.__ptr = Polycode.SceneMesh_loadSkeleton(this.__ptr, fileName)
	return retVal
}

SceneMesh.prototype.clearMaterial = function() {
	Polycode.SceneMesh_clearMaterial(this.__ptr)
}

SceneMesh.prototype.setMaterial = function(material) {
	Polycode.SceneMesh_setMaterial(this.__ptr, material)
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
	var retVal = new shared_ptr<Skeleton>()
	retVal.__ptr = Polycode.SceneMesh_getSkeleton(this.__ptr)
	return retVal
}

SceneMesh.prototype.applySkeletonLocally = function() {
	Polycode.SceneMesh_applySkeletonLocally(this.__ptr)
}

SceneMesh.prototype.setLineWidth = function(newWidth) {
	Polycode.SceneMesh_setLineWidth(this.__ptr, newWidth)
}

SceneMesh.prototype.getFilename = function() {
	return Polycode.SceneMesh_getFilename(this.__ptr)
}

SceneMesh.prototype.setFilename = function(fileName) {
	Polycode.SceneMesh_setFilename(this.__ptr, fileName)
}

SceneMesh.prototype.loadFromFile = function(fileName) {
	Polycode.SceneMesh_loadFromFile(this.__ptr, fileName)
}

SceneMesh.prototype.customHitDetection = function(ray) {
	return Polycode.SceneMesh_customHitDetection(this.__ptr, ray)
}

SceneMesh.prototype.setForceMaterial = function(forceMaterial) {
	Polycode.SceneMesh_setForceMaterial(this.__ptr, forceMaterial)
}

SceneMesh.prototype.getForceMaterial = function() {
	return Polycode.SceneMesh_getForceMaterial(this.__ptr)
}

SceneMesh.prototype.Clone = function(deepClone,ignoreEditorOnly) {
	var retVal = new Entity()
	retVal.__ptr = Polycode.SceneMesh_Clone(this.__ptr, deepClone,ignoreEditorOnly)
	return retVal
}

SceneMesh.prototype.applyClone = function(clone,deepClone,ignoreEditorOnly) {
	Polycode.SceneMesh_applyClone(this.__ptr, clone,deepClone,ignoreEditorOnly)
}
