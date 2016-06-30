require('Polycode/Entity')

function SceneLight(type,parentScene,intensity,constantAttenuation,linearAttenuation,quadraticAttenuation) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.SceneLight(type,parentScene,intensity,constantAttenuation,linearAttenuation,quadraticAttenuation)
	}
}

SceneLight.POINT_LIGHT = 0
SceneLight.SPOT_LIGHT = 1

SceneLight.prototype = Object.create(Entity.prototype)


SceneLight.prototype.getIntensity = function() {
	return Polycode.SceneLight_getIntensity(this.__ptr)
}

SceneLight.prototype.setIntensity = function(newIntensity) {
	Polycode.SceneLight_setIntensity(this.__ptr, newIntensity)
}

SceneLight.prototype.setAttenuation = function(constantAttenuation,linearAttenuation,quadraticAttenuation) {
	Polycode.SceneLight_setAttenuation(this.__ptr, constantAttenuation, linearAttenuation, quadraticAttenuation)
}

SceneLight.prototype.getConstantAttenuation = function() {
	return Polycode.SceneLight_getConstantAttenuation(this.__ptr)
}

SceneLight.prototype.getLinearAttenuation = function() {
	return Polycode.SceneLight_getLinearAttenuation(this.__ptr)
}

SceneLight.prototype.getQuadraticAttenuation = function() {
	return Polycode.SceneLight_getQuadraticAttenuation(this.__ptr)
}

SceneLight.prototype.getType = function() {
	return Polycode.SceneLight_getType(this.__ptr)
}

SceneLight.prototype.renderDepthMap = function(scene) {
	Polycode.SceneLight_renderDepthMap(this.__ptr, scene.__ptr)
}

SceneLight.prototype.getZBufferTexture = function() {
	var retVal = new Texture()
	retVal.__ptr = Polycode.SceneLight_getZBufferTexture(this.__ptr)
	return retVal
}

SceneLight.prototype.setSpecularLightColor = function(r,g,b,a) {
	Polycode.SceneLight_setSpecularLightColor(this.__ptr, r, g, b, a)
}

SceneLight.prototype.setDiffuseLightColor = function(r,g,b,a) {
	Polycode.SceneLight_setDiffuseLightColor(this.__ptr, r, g, b, a)
}

SceneLight.prototype.setLightColor = function(r,g,b,a) {
	Polycode.SceneLight_setLightColor(this.__ptr, r, g, b, a)
}

SceneLight.prototype.setSpotlightProperties = function(spotlightCutoff,spotlightExponent) {
	Polycode.SceneLight_setSpotlightProperties(this.__ptr, spotlightCutoff, spotlightExponent)
}

SceneLight.prototype.getSpotlightCutoff = function() {
	return Polycode.SceneLight_getSpotlightCutoff(this.__ptr)
}

SceneLight.prototype.getSpotlightExponent = function() {
	return Polycode.SceneLight_getSpotlightExponent(this.__ptr)
}

SceneLight.prototype.enableShadows = function(val,resolution) {
	Polycode.SceneLight_enableShadows(this.__ptr, val, resolution)
}

SceneLight.prototype.setShadowMapFOV = function(fov) {
	Polycode.SceneLight_setShadowMapFOV(this.__ptr, fov)
}

SceneLight.prototype.getShadowMapFOV = function() {
	return Polycode.SceneLight_getShadowMapFOV(this.__ptr)
}

SceneLight.prototype.getShadowMapResolution = function() {
	return Polycode.SceneLight_getShadowMapResolution(this.__ptr)
}

SceneLight.prototype.areShadowsEnabled = function() {
	return Polycode.SceneLight_areShadowsEnabled(this.__ptr)
}

SceneLight.prototype.getLightType = function() {
	return Polycode.SceneLight_getLightType(this.__ptr)
}

SceneLight.prototype.setLightImportance = function(newImportance) {
	Polycode.SceneLight_setLightImportance(this.__ptr, newImportance)
}

SceneLight.prototype.getLightImportance = function() {
	return Polycode.SceneLight_getLightImportance(this.__ptr)
}

SceneLight.prototype.setLightType = function(lightType) {
	Polycode.SceneLight_setLightType(this.__ptr, lightType)
}

SceneLight.prototype.Clone = function(deepClone,ignoreEditorOnly) {
	var retVal = new Entity()
	retVal.__ptr = Polycode.SceneLight_Clone(this.__ptr, deepClone, ignoreEditorOnly)
	return retVal
}

SceneLight.prototype.applyClone = function(clone,deepClone,ignoreEditorOnly) {
	Polycode.SceneLight_applyClone(this.__ptr, clone.__ptr, deepClone, ignoreEditorOnly)
}

SceneLight.prototype.getParentScene = function() {
	var retVal = new Scene()
	retVal.__ptr = Polycode.SceneLight_getParentScene(this.__ptr)
	return retVal
}

SceneLight.prototype.setParentScene = function(scene) {
	Polycode.SceneLight_setParentScene(this.__ptr, scene.__ptr)
}

SceneLight.prototype.getSpotlightCamera = function() {
	var retVal = new Camera()
	retVal.__ptr = Polycode.SceneLight_getSpotlightCamera(this.__ptr)
	return retVal
}

SceneLight.prototype.getLightInfo = function() {
	var retVal = new LightInfo()
	retVal.__ptr = Polycode.SceneLight_getLightInfo(this.__ptr)
	return retVal
}
