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
