require('Polycode/Entity')

function Camera() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.Camera()
	}
	Object.defineProperties(this, {
		'frustumCulling': { enumerable: true, configurable: true, get: Camera.prototype.__get_frustumCulling, set: Camera.prototype.__set_frustumCulling},
		'topLeftOrtho': { enumerable: true, configurable: true, get: Camera.prototype.__get_topLeftOrtho, set: Camera.prototype.__set_topLeftOrtho},
		'cameraShift': { enumerable: true, configurable: true, get: Camera.prototype.__get_cameraShift, set: Camera.prototype.__set_cameraShift}
	})
}

Camera.ORTHO_SIZE_MANUAL = 0
Camera.ORTHO_SIZE_LOCK_HEIGHT = 1
Camera.ORTHO_SIZE_LOCK_WIDTH = 2
Camera.ORTHO_SIZE_VIEWPORT = 3
Camera.PERSPECTIVE_FOV = 4
Camera.PERSPECTIVE_FRUSTUM = 5
Camera.MANUAL_MATRIX = 6

Camera.prototype = Object.create(Entity.prototype)

Camera.prototype.__get_frustumCulling = function() {
	return Polycode.Camera__get_frustumCulling(this.__ptr)
}

Camera.prototype.__set_frustumCulling = function(val) {
	Polycode.Camera__set_frustumCulling(this.__ptr, val)
}

Camera.prototype.__get_topLeftOrtho = function() {
	return Polycode.Camera__get_topLeftOrtho(this.__ptr)
}

Camera.prototype.__set_topLeftOrtho = function(val) {
	Polycode.Camera__set_topLeftOrtho(this.__ptr, val)
}

Camera.prototype.__get_cameraShift = function() {
	var retVal = new Vector2("__skip_ptr__")
	retVal.__ptr = 	Polycode.Camera__get_cameraShift(this.__ptr)
	return retVal
}

Camera.prototype.__set_cameraShift = function(val) {
	Polycode.Camera__set_cameraShift(this.__ptr, val.__ptr)
}


Camera.prototype.buildFrustumPlanes = function() {
	Polycode.Camera_buildFrustumPlanes(this.__ptr)
}

Camera.prototype.isSphereInFrustum = function(pos,fRadius) {
	return Polycode.Camera_isSphereInFrustum(this.__ptr, pos, fRadius)
}

Camera.prototype.isAABBInFrustum = function(aabb) {
	return Polycode.Camera_isAABBInFrustum(this.__ptr, aabb)
}

Camera.prototype.setOrthoMode = function(mode) {
	Polycode.Camera_setOrthoMode(this.__ptr, mode)
}

Camera.prototype.setOrthoSize = function(orthoSizeX,orthoSizeY) {
	Polycode.Camera_setOrthoSize(this.__ptr, orthoSizeX, orthoSizeY)
}

Camera.prototype.setFrustumMode = function(left,right,bottom,top,front,back) {
	Polycode.Camera_setFrustumMode(this.__ptr, left, right, bottom, top, front, back)
}

Camera.prototype.getOrthoMode = function() {
	return Polycode.Camera_getOrthoMode(this.__ptr)
}

Camera.prototype.getOrthoSizeX = function() {
	return Polycode.Camera_getOrthoSizeX(this.__ptr)
}

Camera.prototype.getOrthoSizeY = function() {
	return Polycode.Camera_getOrthoSizeY(this.__ptr)
}

Camera.prototype.setFOV = function(fov) {
	Polycode.Camera_setFOV(this.__ptr, fov)
}

Camera.prototype.getFOV = function() {
	return Polycode.Camera_getFOV(this.__ptr)
}

Camera.prototype.setClippingPlanes = function(nearClipPlane,farClipPlane) {
	Polycode.Camera_setClippingPlanes(this.__ptr, nearClipPlane, farClipPlane)
}

Camera.prototype.getNearClippingPlane = function() {
	return Polycode.Camera_getNearClippingPlane(this.__ptr)
}

Camera.prototype.getFarClippingPlane = function() {
	return Polycode.Camera_getFarClippingPlane(this.__ptr)
}

Camera.prototype.createProjectionMatrix = function() {
	var retVal = new Matrix4("__skip_ptr__")
	retVal.__ptr = Polycode.Camera_createProjectionMatrix(this.__ptr)
	return retVal
}

Camera.prototype.hasFilterShader = function() {
	return Polycode.Camera_hasFilterShader(this.__ptr)
}

Camera.prototype.setPostFilter = function(material) {
	Polycode.Camera_setPostFilter(this.__ptr, material)
}

Camera.prototype.removePostFilter = function() {
	Polycode.Camera_removePostFilter(this.__ptr)
}

Camera.prototype.getScreenShaderMaterial = function() {
	var retVal = new Material("__skip_ptr__")
	retVal.__ptr = Polycode.Camera_getScreenShaderMaterial(this.__ptr)
	return retVal
}

Camera.prototype.getProjectionMatrix = function() {
	var retVal = new Matrix4("__skip_ptr__")
	retVal.__ptr = Polycode.Camera_getProjectionMatrix(this.__ptr)
	return retVal
}

Camera.prototype.setCustomProjectionMatrix = function(matrix) {
	Polycode.Camera_setCustomProjectionMatrix(this.__ptr, matrix)
}

Camera.prototype.getViewport = function() {
	var retVal = new Rectangle("__skip_ptr__")
	retVal.__ptr = Polycode.Camera_getViewport(this.__ptr)
	return retVal
}

Camera.prototype.setViewport = function(viewport) {
	Polycode.Camera_setViewport(this.__ptr, viewport)
}

Camera.prototype.setOrthoSizeMode = function(orthoSizeMode) {
	Polycode.Camera_setOrthoSizeMode(this.__ptr, orthoSizeMode)
}

Camera.prototype.getOrthoSizeMode = function() {
	return Polycode.Camera_getOrthoSizeMode(this.__ptr)
}

Camera.prototype.setProjectionMode = function(mode) {
	Polycode.Camera_setProjectionMode(this.__ptr, mode)
}

Camera.prototype.getProjectionMode = function() {
	return Polycode.Camera_getProjectionMode(this.__ptr)
}

Camera.prototype.projectRayFrom2DCoordinate = function(coordinate,viewport) {
	var retVal = new Vector3("__skip_ptr__")
	retVal.__ptr = Polycode.Camera_projectRayFrom2DCoordinate(this.__ptr, coordinate, viewport)
	return retVal
}

Camera.prototype.getShaderPass = function(index) {
	var retVal = new ShaderPass("__skip_ptr__")
	retVal.__ptr = Polycode.Camera_getShaderPass(this.__ptr, index)
	return retVal
}

Camera.prototype.getNumShaderPasses = function() {
	return Polycode.Camera_getNumShaderPasses(this.__ptr)
}
