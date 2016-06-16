function SceneManager() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.SceneManager()
	}
}

Duktape.fin(SceneManager.prototype, function (x) {
	if (x === SceneManager.prototype) {
		return;
	}
	Polycode.SceneManager__delete(x.__ptr)
})

SceneManager.prototype.addScene = function(newScene) {
	Polycode.SceneManager_addScene(this.__ptr, newScene.__ptr)
}

SceneManager.prototype.removeScene = function(scene) {
	Polycode.SceneManager_removeScene(this.__ptr, scene.__ptr)
}

SceneManager.prototype.Update = function() {
	Polycode.SceneManager_Update(this.__ptr)
}

SceneManager.prototype.fixedUpdate = function() {
	Polycode.SceneManager_fixedUpdate(this.__ptr)
}

SceneManager.prototype.Render = function(viewport) {
	Polycode.SceneManager_Render(this.__ptr, viewport)
}

SceneManager.prototype.renderVirtual = function() {
	Polycode.SceneManager_renderVirtual(this.__ptr)
}

SceneManager.prototype.registerRenderTexture = function(renderTexture) {
	Polycode.SceneManager_registerRenderTexture(this.__ptr, renderTexture.__ptr)
}

SceneManager.prototype.unregisterRenderTexture = function(renderTexture) {
	Polycode.SceneManager_unregisterRenderTexture(this.__ptr, renderTexture.__ptr)
}

SceneManager.prototype.setRenderer = function(renderer) {
	Polycode.SceneManager_setRenderer(this.__ptr, renderer.__ptr)
}
