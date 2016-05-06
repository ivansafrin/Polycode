function SceneParticleEmitter() {
}

SceneParticleEmitter.prototype.setParticleCount = function(newParticleCount) {
	Polycode.SceneParticleEmitter_setParticleCount(this.__ptr, newParticleCount)
}

SceneParticleEmitter.prototype.getParticleCount = function() {
	Polycode.SceneParticleEmitter_getParticleCount(this.__ptr)
}

SceneParticleEmitter.prototype.setParticleLifetime = function(lifetime) {
	Polycode.SceneParticleEmitter_setParticleLifetime(this.__ptr, lifetime)
}

SceneParticleEmitter.prototype.getParticleLifetime = function() {
	Polycode.SceneParticleEmitter_getParticleLifetime(this.__ptr)
}

SceneParticleEmitter.prototype.setDirectionDeviation = function(newDeviation) {
	Polycode.SceneParticleEmitter_setDirectionDeviation(this.__ptr, newDeviation)
}

SceneParticleEmitter.prototype.getDirectionDeviation = function() {
	Polycode.SceneParticleEmitter_getDirectionDeviation(this.__ptr)
}

SceneParticleEmitter.prototype.setEmitterSize = function(newSize) {
	Polycode.SceneParticleEmitter_setEmitterSize(this.__ptr, newSize)
}

SceneParticleEmitter.prototype.getEmitterSize = function() {
	Polycode.SceneParticleEmitter_getEmitterSize(this.__ptr)
}

SceneParticleEmitter.prototype.setGravity = function(newGravity) {
	Polycode.SceneParticleEmitter_setGravity(this.__ptr, newGravity)
}

SceneParticleEmitter.prototype.getGravity = function() {
	Polycode.SceneParticleEmitter_getGravity(this.__ptr)
}

SceneParticleEmitter.prototype.fixedUpdate = function() {
	Polycode.SceneParticleEmitter_fixedUpdate(this.__ptr)
}

SceneParticleEmitter.prototype.Render = function(buffer) {
	Polycode.SceneParticleEmitter_Render(this.__ptr, buffer)
}

SceneParticleEmitter.prototype.updateParticles = function() {
	Polycode.SceneParticleEmitter_updateParticles(this.__ptr)
}

SceneParticleEmitter.prototype.rebuildParticles = function(buffer) {
	Polycode.SceneParticleEmitter_rebuildParticles(this.__ptr, buffer)
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
	Polycode.SceneParticleEmitter_getParticlesInWorldSpace(this.__ptr)
}

SceneParticleEmitter.prototype.setPerlinEnabled = function(val) {
	Polycode.SceneParticleEmitter_setPerlinEnabled(this.__ptr, val)
}

SceneParticleEmitter.prototype.getPerlinEnabled = function() {
	Polycode.SceneParticleEmitter_getPerlinEnabled(this.__ptr)
}

SceneParticleEmitter.prototype.getParticleSpeed = function() {
	Polycode.SceneParticleEmitter_getParticleSpeed(this.__ptr)
}

SceneParticleEmitter.prototype.setParticleSpeed = function(speed) {
	Polycode.SceneParticleEmitter_setParticleSpeed(this.__ptr, speed)
}

SceneParticleEmitter.prototype.setPerlinValue = function(perlinValue) {
	Polycode.SceneParticleEmitter_setPerlinValue(this.__ptr, perlinValue)
}

SceneParticleEmitter.prototype.getPerlinValue = function() {
	Polycode.SceneParticleEmitter_getPerlinValue(this.__ptr)
}

SceneParticleEmitter.prototype.setParticleType = function(particleType) {
	Polycode.SceneParticleEmitter_setParticleType(this.__ptr, particleType)
}

SceneParticleEmitter.prototype.getParticleType = function() {
	Polycode.SceneParticleEmitter_getParticleType(this.__ptr)
}

SceneParticleEmitter.prototype.setParticleSize = function(particleSize) {
	Polycode.SceneParticleEmitter_setParticleSize(this.__ptr, particleSize)
}

SceneParticleEmitter.prototype.getParticleSize = function() {
	Polycode.SceneParticleEmitter_getParticleSize(this.__ptr)
}

SceneParticleEmitter.prototype.setParticleRotationSpeed = function(rotationSpeed) {
	Polycode.SceneParticleEmitter_setParticleRotationSpeed(this.__ptr, rotationSpeed)
}

SceneParticleEmitter.prototype.getParticleRotationSpeed = function() {
	Polycode.SceneParticleEmitter_getParticleRotationSpeed(this.__ptr)
}

SceneParticleEmitter.prototype.setParticleDirection = function(direction) {
	Polycode.SceneParticleEmitter_setParticleDirection(this.__ptr, direction)
}

SceneParticleEmitter.prototype.getParticleDirection = function() {
	Polycode.SceneParticleEmitter_getParticleDirection(this.__ptr)
}

SceneParticleEmitter.prototype.setLoopParticles = function(val) {
	Polycode.SceneParticleEmitter_setLoopParticles(this.__ptr, val)
}

SceneParticleEmitter.prototype.getLoopParticles = function() {
	Polycode.SceneParticleEmitter_getLoopParticles(this.__ptr)
}

SceneParticleEmitter.prototype.addSourceMesh = function(mesh) {
	Polycode.SceneParticleEmitter_addSourceMesh(this.__ptr, mesh)
}

SceneParticleEmitter.prototype.getNumSourceMeshes = function() {
	Polycode.SceneParticleEmitter_getNumSourceMeshes(this.__ptr)
}

SceneParticleEmitter.prototype.getSourcesMeshAtIndex = function(index) {
	Polycode.SceneParticleEmitter_getSourcesMeshAtIndex(this.__ptr, index)
}

SceneParticleEmitter.prototype.removeSourceMeshAtIndex = function(index) {
	Polycode.SceneParticleEmitter_removeSourceMeshAtIndex(this.__ptr, index)
}

SceneParticleEmitter.prototype.positionParticle = function(index) {
	Polycode.SceneParticleEmitter_positionParticle(this.__ptr, index)
}

SceneParticleEmitter.prototype.Clone = function(deepClone,ignoreEditorOnly) {
	Polycode.SceneParticleEmitter_Clone(this.__ptr, deepClone,ignoreEditorOnly)
}

SceneParticleEmitter.prototype.applyClone = function(clone,deepClone,ignoreEditorOnly) {
	Polycode.SceneParticleEmitter_applyClone(this.__ptr, clone,deepClone,ignoreEditorOnly)
}
