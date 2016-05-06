function Camera() {
}

Camera.prototype.buildFrustumPlanes = function() {
	Polycode.Camera_buildFrustumPlanes(this.__ptr)
}

Camera.prototype.isSphereInFrustum = function(pos,fRadius) {
	Polycode.Camera_isSphereInFrustum(this.__ptr, pos,fRadius)
}

Camera.prototype.isAABBInFrustum = function(aabb) {
	Polycode.Camera_isAABBInFrustum(this.__ptr, aabb)
}

Camera.prototype.setOrthoMode = function(mode) {
	Polycode.Camera_setOrthoMode(this.__ptr, mode)
}

Camera.prototype.setOrthoSize = function(orthoSizeX,orthoSizeY) {
	Polycode.Camera_setOrthoSize(this.__ptr, orthoSizeX,orthoSizeY)
}

Camera.prototype.setFrustumMode = function(left,right,bottom,top,front,back) {
	Polycode.Camera_setFrustumMode(this.__ptr, left,right,bottom,top,front,back)
}

Camera.prototype.getOrthoMode = function() {
	Polycode.Camera_getOrthoMode(this.__ptr)
}

Camera.prototype.getOrthoSizeX = function() {
	Polycode.Camera_getOrthoSizeX(this.__ptr)
}

Camera.prototype.getOrthoSizeY = function() {
	Polycode.Camera_getOrthoSizeY(this.__ptr)
}

Camera.prototype.setFOV = function(fov) {
	Polycode.Camera_setFOV(this.__ptr, fov)
}

Camera.prototype.getFOV = function() {
	Polycode.Camera_getFOV(this.__ptr)
}

Camera.prototype.setClippingPlanes = function(nearClipPlane,farClipPlane) {
	Polycode.Camera_setClippingPlanes(this.__ptr, nearClipPlane,farClipPlane)
}

Camera.prototype.getNearClippingPlane = function() {
	Polycode.Camera_getNearClippingPlane(this.__ptr)
}

Camera.prototype.getFarClippingPlane = function() {
	Polycode.Camera_getFarClippingPlane(this.__ptr)
}

Camera.prototype.setParentScene = function(parentScene) {
	Polycode.Camera_setParentScene(this.__ptr, parentScene)
}

Camera.prototype.getParentScene = function() {
	Polycode.Camera_getParentScene(this.__ptr)
}

Camera.prototype.createProjectionMatrix = function() {
	Polycode.Camera_createProjectionMatrix(this.__ptr)
}

Camera.prototype.hasFilterShader = function() {
	Polycode.Camera_hasFilterShader(this.__ptr)
}

Camera.prototype.drawFilter = function(targetBuffer) {
	Polycode.Camera_drawFilter(this.__ptr, targetBuffer)
}

Camera.prototype.setPostFilter = function(material) {
	Polycode.Camera_setPostFilter(this.__ptr, material)
}

Camera.prototype.setPostFilterByName = function(shaderName) {
	Polycode.Camera_setPostFilterByName(this.__ptr, shaderName)
}

Camera.prototype.removePostFilter = function() {
	Polycode.Camera_removePostFilter(this.__ptr)
}

Camera.prototype.getScreenShaderMaterial = function() {
	Polycode.Camera_getScreenShaderMaterial(this.__ptr)
}

Camera.prototype.Clone = function(deepClone,ignoreEditorOnly) {
	Polycode.Camera_Clone(this.__ptr, deepClone,ignoreEditorOnly)
}

Camera.prototype.applyClone = function(clone,deepClone,ignoreEditorOnly) {
	Polycode.Camera_applyClone(this.__ptr, clone,deepClone,ignoreEditorOnly)
}

Camera.prototype.getProjectionMatrix = function() {
	Polycode.Camera_getProjectionMatrix(this.__ptr)
}

Camera.prototype.setCustomProjectionMatrix = function(matrix) {
	Polycode.Camera_setCustomProjectionMatrix(this.__ptr, matrix)
}

Camera.prototype.getViewport = function() {
	Polycode.Camera_getViewport(this.__ptr)
}

Camera.prototype.setViewport = function(viewport) {
	Polycode.Camera_setViewport(this.__ptr, viewport)
}

Camera.prototype.setOrthoSizeMode = function(orthoSizeMode) {
	Polycode.Camera_setOrthoSizeMode(this.__ptr, orthoSizeMode)
}

Camera.prototype.getOrthoSizeMode = function() {
	Polycode.Camera_getOrthoSizeMode(this.__ptr)
}

Camera.prototype.setProjectionMode = function(mode) {
	Polycode.Camera_setProjectionMode(this.__ptr, mode)
}

Camera.prototype.getProjectionMode = function() {
	Polycode.Camera_getProjectionMode(this.__ptr)
}

Camera.prototype.projectRayFrom2DCoordinate = function(coordinate,viewport) {
	Polycode.Camera_projectRayFrom2DCoordinate(this.__ptr, coordinate,viewport)
}

Camera.prototype.renderFullScreenQuad = function(drawBuffer,shaderPass) {
	Polycode.Camera_renderFullScreenQuad(this.__ptr, drawBuffer,shaderPass)
}

Camera.prototype.getShaderPass = function(index) {
	Polycode.Camera_getShaderPass(this.__ptr, index)
}

Camera.prototype.getNumShaderPasses = function() {
	Polycode.Camera_getNumShaderPasses(this.__ptr)
}
