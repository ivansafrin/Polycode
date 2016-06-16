require('Polycode/SceneMesh')

function SceneParticleEmitter(particleCount,lifetime,speed) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.SceneParticleEmitter(particleCount,lifetime,speed)
	}
	Object.defineProperties(this, {
		'useScaleCurve': { enumerable: true, configurable: true, get: SceneParticleEmitter.prototype.__get_useScaleCurve, set: SceneParticleEmitter.prototype.__set_useScaleCurve},
		'scaleCurve': { enumerable: true, configurable: true, get: SceneParticleEmitter.prototype.__get_scaleCurve, set: SceneParticleEmitter.prototype.__set_scaleCurve},
		'useColorCurves': { enumerable: true, configurable: true, get: SceneParticleEmitter.prototype.__get_useColorCurves, set: SceneParticleEmitter.prototype.__set_useColorCurves},
		'colorCurveR': { enumerable: true, configurable: true, get: SceneParticleEmitter.prototype.__get_colorCurveR, set: SceneParticleEmitter.prototype.__set_colorCurveR},
		'colorCurveG': { enumerable: true, configurable: true, get: SceneParticleEmitter.prototype.__get_colorCurveG, set: SceneParticleEmitter.prototype.__set_colorCurveG},
		'colorCurveB': { enumerable: true, configurable: true, get: SceneParticleEmitter.prototype.__get_colorCurveB, set: SceneParticleEmitter.prototype.__set_colorCurveB},
		'colorCurveA': { enumerable: true, configurable: true, get: SceneParticleEmitter.prototype.__get_colorCurveA, set: SceneParticleEmitter.prototype.__set_colorCurveA},
		'colorDeviation': { enumerable: true, configurable: true, get: SceneParticleEmitter.prototype.__get_colorDeviation, set: SceneParticleEmitter.prototype.__set_colorDeviation}
	})
}

SceneParticleEmitter.prototype = Object.create(SceneMesh.prototype);

SceneParticleEmitter.prototype.__get_useScaleCurve = function() {
	return Polycode.SceneParticleEmitter__get_useScaleCurve(this.__ptr)
}

SceneParticleEmitter.prototype.__set_useScaleCurve = function(val) {
	Polycode.SceneParticleEmitter__set_useScaleCurve(this.__ptr, val)
}

SceneParticleEmitter.prototype.__get_scaleCurve = function() {
	var retVal = new BezierCurve()
	retVal.__ptr = 	Polycode.SceneParticleEmitter__get_scaleCurve(this.__ptr)
	return retVal
}

SceneParticleEmitter.prototype.__set_scaleCurve = function(val) {
	Polycode.SceneParticleEmitter__set_scaleCurve(this.__ptr, val.__ptr)
}

SceneParticleEmitter.prototype.__get_useColorCurves = function() {
	return Polycode.SceneParticleEmitter__get_useColorCurves(this.__ptr)
}

SceneParticleEmitter.prototype.__set_useColorCurves = function(val) {
	Polycode.SceneParticleEmitter__set_useColorCurves(this.__ptr, val)
}

SceneParticleEmitter.prototype.__get_colorCurveR = function() {
	var retVal = new BezierCurve()
	retVal.__ptr = 	Polycode.SceneParticleEmitter__get_colorCurveR(this.__ptr)
	return retVal
}

SceneParticleEmitter.prototype.__set_colorCurveR = function(val) {
	Polycode.SceneParticleEmitter__set_colorCurveR(this.__ptr, val.__ptr)
}

SceneParticleEmitter.prototype.__get_colorCurveG = function() {
	var retVal = new BezierCurve()
	retVal.__ptr = 	Polycode.SceneParticleEmitter__get_colorCurveG(this.__ptr)
	return retVal
}

SceneParticleEmitter.prototype.__set_colorCurveG = function(val) {
	Polycode.SceneParticleEmitter__set_colorCurveG(this.__ptr, val.__ptr)
}

SceneParticleEmitter.prototype.__get_colorCurveB = function() {
	var retVal = new BezierCurve()
	retVal.__ptr = 	Polycode.SceneParticleEmitter__get_colorCurveB(this.__ptr)
	return retVal
}

SceneParticleEmitter.prototype.__set_colorCurveB = function(val) {
	Polycode.SceneParticleEmitter__set_colorCurveB(this.__ptr, val.__ptr)
}

SceneParticleEmitter.prototype.__get_colorCurveA = function() {
	var retVal = new BezierCurve()
	retVal.__ptr = 	Polycode.SceneParticleEmitter__get_colorCurveA(this.__ptr)
	return retVal
}

SceneParticleEmitter.prototype.__set_colorCurveA = function(val) {
	Polycode.SceneParticleEmitter__set_colorCurveA(this.__ptr, val.__ptr)
}

SceneParticleEmitter.prototype.__get_colorDeviation = function() {
	var retVal = new Color()
	retVal.__ptr = 	Polycode.SceneParticleEmitter__get_colorDeviation(this.__ptr)
	return retVal
}

SceneParticleEmitter.prototype.__set_colorDeviation = function(val) {
	Polycode.SceneParticleEmitter__set_colorDeviation(this.__ptr, val.__ptr)
}


SceneParticleEmitter.prototype.setParticleCount = function(newParticleCount) {
	Polycode.SceneParticleEmitter_setParticleCount(this.__ptr, newParticleCount)
}

SceneParticleEmitter.prototype.getParticleCount = function() {
	return Polycode.SceneParticleEmitter_getParticleCount(this.__ptr)
}

SceneParticleEmitter.prototype.setParticleLifetime = function(lifetime) {
	Polycode.SceneParticleEmitter_setParticleLifetime(this.__ptr, lifetime)
}

SceneParticleEmitter.prototype.getParticleLifetime = function() {
	return Polycode.SceneParticleEmitter_getParticleLifetime(this.__ptr)
}

SceneParticleEmitter.prototype.setDirectionDeviation = function(newDeviation) {
	Polycode.SceneParticleEmitter_setDirectionDeviation(this.__ptr, newDeviation)
}

SceneParticleEmitter.prototype.getDirectionDeviation = function() {
	var retVal = new Vector3()
	retVal.__ptr = Polycode.SceneParticleEmitter_getDirectionDeviation(this.__ptr)
	return retVal
}

SceneParticleEmitter.prototype.setEmitterSize = function(newSize) {
	Polycode.SceneParticleEmitter_setEmitterSize(this.__ptr, newSize)
}

SceneParticleEmitter.prototype.getEmitterSize = function() {
	var retVal = new Vector3()
	retVal.__ptr = Polycode.SceneParticleEmitter_getEmitterSize(this.__ptr)
	return retVal
}

SceneParticleEmitter.prototype.setGravity = function(newGravity) {
	Polycode.SceneParticleEmitter_setGravity(this.__ptr, newGravity)
}

SceneParticleEmitter.prototype.getGravity = function() {
	var retVal = new Vector3()
	retVal.__ptr = Polycode.SceneParticleEmitter_getGravity(this.__ptr)
	return retVal
}

SceneParticleEmitter.prototype.fixedUpdate = function() {
	Polycode.SceneParticleEmitter_fixedUpdate(this.__ptr)
}

SceneParticleEmitter.prototype.Render = function(buffer) {
	Polycode.SceneParticleEmitter_Render(this.__ptr, buffer.__ptr)
}

SceneParticleEmitter.prototype.updateParticles = function() {
	Polycode.SceneParticleEmitter_updateParticles(this.__ptr)
}

SceneParticleEmitter.prototype.rebuildParticles = function(buffer) {
	Polycode.SceneParticleEmitter_rebuildParticles(this.__ptr, buffer.__ptr)
}

SceneParticleEmitter.prototype.triggerParticles = function(allAtOnce) {
	Polycode.SceneParticleEmitter_triggerParticles(this.__ptr, allAtOnce)
}

SceneParticleEmitter.prototype.enableParticleSystem = function(val) {
	Polycode.SceneParticleEmitter_enableParticleSystem(this.__ptr, val)
}

SceneParticleEmitter.prototype.setUseFloorPlane = function(val) {
	Polycode.SceneParticleEmitter_setUseFloorPlane(this.__ptr, val)
}

SceneParticleEmitter.prototype.setFloorPlaneOffset = function(floorPlaneOffset) {
	Polycode.SceneParticleEmitter_setFloorPlaneOffset(this.__ptr, floorPlaneOffset)
}

SceneParticleEmitter.prototype.setFloorDamping = function(floorDamping) {
	Polycode.SceneParticleEmitter_setFloorDamping(this.__ptr, floorDamping)
}

SceneParticleEmitter.prototype.setParticlesInWorldSpace = function(val) {
	Polycode.SceneParticleEmitter_setParticlesInWorldSpace(this.__ptr, val)
}

SceneParticleEmitter.prototype.getParticlesInWorldSpace = function() {
	return Polycode.SceneParticleEmitter_getParticlesInWorldSpace(this.__ptr)
}

SceneParticleEmitter.prototype.setPerlinEnabled = function(val) {
	Polycode.SceneParticleEmitter_setPerlinEnabled(this.__ptr, val)
}

SceneParticleEmitter.prototype.getPerlinEnabled = function() {
	return Polycode.SceneParticleEmitter_getPerlinEnabled(this.__ptr)
}

SceneParticleEmitter.prototype.getParticleSpeed = function() {
	return Polycode.SceneParticleEmitter_getParticleSpeed(this.__ptr)
}

SceneParticleEmitter.prototype.setParticleSpeed = function(speed) {
	Polycode.SceneParticleEmitter_setParticleSpeed(this.__ptr, speed)
}

SceneParticleEmitter.prototype.setPerlinValue = function(perlinValue) {
	Polycode.SceneParticleEmitter_setPerlinValue(this.__ptr, perlinValue)
}

SceneParticleEmitter.prototype.getPerlinValue = function() {
	var retVal = new Vector3()
	retVal.__ptr = Polycode.SceneParticleEmitter_getPerlinValue(this.__ptr)
	return retVal
}

SceneParticleEmitter.prototype.setParticleType = function(particleType) {
	Polycode.SceneParticleEmitter_setParticleType(this.__ptr, particleType)
}

SceneParticleEmitter.prototype.getParticleType = function() {
	return Polycode.SceneParticleEmitter_getParticleType(this.__ptr)
}

SceneParticleEmitter.prototype.setParticleSize = function(particleSize) {
	Polycode.SceneParticleEmitter_setParticleSize(this.__ptr, particleSize)
}

SceneParticleEmitter.prototype.getParticleSize = function() {
	return Polycode.SceneParticleEmitter_getParticleSize(this.__ptr)
}

SceneParticleEmitter.prototype.setParticleRotationSpeed = function(rotationSpeed) {
	Polycode.SceneParticleEmitter_setParticleRotationSpeed(this.__ptr, rotationSpeed)
}

SceneParticleEmitter.prototype.getParticleRotationSpeed = function() {
	var retVal = new Vector3()
	retVal.__ptr = Polycode.SceneParticleEmitter_getParticleRotationSpeed(this.__ptr)
	return retVal
}

SceneParticleEmitter.prototype.setParticleDirection = function(direction) {
	Polycode.SceneParticleEmitter_setParticleDirection(this.__ptr, direction)
}

SceneParticleEmitter.prototype.getParticleDirection = function() {
	var retVal = new Vector3()
	retVal.__ptr = Polycode.SceneParticleEmitter_getParticleDirection(this.__ptr)
	return retVal
}

SceneParticleEmitter.prototype.setLoopParticles = function(val) {
	Polycode.SceneParticleEmitter_setLoopParticles(this.__ptr, val)
}

SceneParticleEmitter.prototype.getLoopParticles = function() {
	return Polycode.SceneParticleEmitter_getLoopParticles(this.__ptr)
}

SceneParticleEmitter.prototype.addSourceMesh = function(mesh) {
	Polycode.SceneParticleEmitter_addSourceMesh(this.__ptr, mesh.__ptr)
}

SceneParticleEmitter.prototype.getNumSourceMeshes = function() {
	return Polycode.SceneParticleEmitter_getNumSourceMeshes(this.__ptr)
}

SceneParticleEmitter.prototype.getSourcesMeshAtIndex = function(index) {
	var retVal = new Mesh()
	retVal.__ptr = Polycode.SceneParticleEmitter_getSourcesMeshAtIndex(this.__ptr, index)
	return retVal
}

SceneParticleEmitter.prototype.removeSourceMeshAtIndex = function(index) {
	Polycode.SceneParticleEmitter_removeSourceMeshAtIndex(this.__ptr, index)
}

SceneParticleEmitter.prototype.positionParticle = function(index) {
	Polycode.SceneParticleEmitter_positionParticle(this.__ptr, index)
}

SceneParticleEmitter.prototype.Clone = function(deepClone,ignoreEditorOnly) {
	var retVal = new Entity()
	retVal.__ptr = Polycode.SceneParticleEmitter_Clone(this.__ptr, deepClone, ignoreEditorOnly)
	return retVal
}

SceneParticleEmitter.prototype.applyClone = function(clone,deepClone,ignoreEditorOnly) {
	Polycode.SceneParticleEmitter_applyClone(this.__ptr, clone.__ptr, deepClone, ignoreEditorOnly)
}
