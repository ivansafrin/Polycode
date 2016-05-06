function SceneLight() {
}

SceneLight.prototype.getIntensity = function() {
	Polycode.SceneLight_getIntensity(this.__ptr)
}

SceneLight.prototype.setIntensity = function(newIntensity) {
	Polycode.SceneLight_setIntensity(this.__ptr, newIntensity)
}

SceneLight.prototype.setAttenuation = function(constantAttenuation,linearAttenuation,quadraticAttenuation) {
	Polycode.SceneLight_setAttenuation(this.__ptr, constantAttenuation,linearAttenuation,quadraticAttenuation)
}

SceneLight.prototype.getConstantAttenuation = function() {
	Polycode.SceneLight_getConstantAttenuation(this.__ptr)
}

SceneLight.prototype.getLinearAttenuation = function() {
	Polycode.SceneLight_getLinearAttenuation(this.__ptr)
}

SceneLight.prototype.getQuadraticAttenuation = function() {
	Polycode.SceneLight_getQuadraticAttenuation(this.__ptr)
}

SceneLight.prototype.getType = function() {
	Polycode.SceneLight_getType(this.__ptr)
}

SceneLight.prototype.renderDepthMap = function(scene) {
	Polycode.SceneLight_renderDepthMap(this.__ptr, scene)
}

SceneLight.prototype.getZBufferTexture = function() {
	Polycode.SceneLight_getZBufferTexture(this.__ptr)
}

SceneLight.prototype.setSpecularLightColor = function(r,g,b,a) {
	Polycode.SceneLight_setSpecularLightColor(this.__ptr, r,g,b,a)
}

SceneLight.prototype.setDiffuseLightColor = function(r,g,b,a) {
	Polycode.SceneLight_setDiffuseLightColor(this.__ptr, r,g,b,a)
}

SceneLight.prototype.setLightColor = function(r,g,b,a) {
	Polycode.SceneLight_setLightColor(this.__ptr, r,g,b,a)
}

SceneLight.prototype.setSpotlightProperties = function(spotlightCutoff,spotlightExponent) {
	Polycode.SceneLight_setSpotlightProperties(this.__ptr, spotlightCutoff,spotlightExponent)
}

SceneLight.prototype.getSpotlightCutoff = function() {
	Polycode.SceneLight_getSpotlightCutoff(this.__ptr)
}

SceneLight.prototype.getSpotlightExponent = function() {
	Polycode.SceneLight_getSpotlightExponent(this.__ptr)
}

SceneLight.prototype.enableShadows = function(val,resolution) {
	Polycode.SceneLight_enableShadows(this.__ptr, val,resolution)
}

SceneLight.prototype.setShadowMapFOV = function(fov) {
	Polycode.SceneLight_setShadowMapFOV(this.__ptr, fov)
}

SceneLight.prototype.getShadowMapFOV = function() {
	Polycode.SceneLight_getShadowMapFOV(this.__ptr)
}

SceneLight.prototype.getShadowMapResolution = function() {
	Polycode.SceneLight_getShadowMapResolution(this.__ptr)
}

SceneLight.prototype.areShadowsEnabled = function() {
	Polycode.SceneLight_areShadowsEnabled(this.__ptr)
}

SceneLight.prototype.getLightType = function() {
	Polycode.SceneLight_getLightType(this.__ptr)
}

SceneLight.prototype.setLightImportance = function(newImportance) {
	Polycode.SceneLight_setLightImportance(this.__ptr, newImportance)
}

SceneLight.prototype.getLightImportance = function() {
	Polycode.SceneLight_getLightImportance(this.__ptr)
}

SceneLight.prototype.setLightType = function(lightType) {
	Polycode.SceneLight_setLightType(this.__ptr, lightType)
}

SceneLight.prototype.Clone = function(deepClone,ignoreEditorOnly) {
	Polycode.SceneLight_Clone(this.__ptr, deepClone,ignoreEditorOnly)
}

SceneLight.prototype.applyClone = function(clone,deepClone,ignoreEditorOnly) {
	Polycode.SceneLight_applyClone(this.__ptr, clone,deepClone,ignoreEditorOnly)
}

SceneLight.prototype.getParentScene = function() {
	Polycode.SceneLight_getParentScene(this.__ptr)
}

SceneLight.prototype.setParentScene = function(scene) {
	Polycode.SceneLight_setParentScene(this.__ptr, scene)
}

SceneLight.prototype.getSpotlightCamera = function() {
	Polycode.SceneLight_getSpotlightCamera(this.__ptr)
}

SceneLight.prototype.getLightInfo = function() {
	Polycode.SceneLight_getLightInfo(this.__ptr)
}
