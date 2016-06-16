function VideoModeChangeInfo() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.VideoModeChangeInfo()
	}
	Object.defineProperties(this, {
		'xRes': { enumerable: true, configurable: true, get: VideoModeChangeInfo.prototype.__get_xRes, set: VideoModeChangeInfo.prototype.__set_xRes},
		'yRes': { enumerable: true, configurable: true, get: VideoModeChangeInfo.prototype.__get_yRes, set: VideoModeChangeInfo.prototype.__set_yRes},
		'fullScreen': { enumerable: true, configurable: true, get: VideoModeChangeInfo.prototype.__get_fullScreen, set: VideoModeChangeInfo.prototype.__set_fullScreen},
		'vSync': { enumerable: true, configurable: true, get: VideoModeChangeInfo.prototype.__get_vSync, set: VideoModeChangeInfo.prototype.__set_vSync},
		'aaLevel': { enumerable: true, configurable: true, get: VideoModeChangeInfo.prototype.__get_aaLevel, set: VideoModeChangeInfo.prototype.__set_aaLevel},
		'anisotropyLevel': { enumerable: true, configurable: true, get: VideoModeChangeInfo.prototype.__get_anisotropyLevel, set: VideoModeChangeInfo.prototype.__set_anisotropyLevel},
		'retinaSupport': { enumerable: true, configurable: true, get: VideoModeChangeInfo.prototype.__get_retinaSupport, set: VideoModeChangeInfo.prototype.__set_retinaSupport}
	})
}

VideoModeChangeInfo.prototype.__get_xRes = function() {
	return Polycode.VideoModeChangeInfo__get_xRes(this.__ptr)
}

VideoModeChangeInfo.prototype.__set_xRes = function(val) {
	Polycode.VideoModeChangeInfo__set_xRes(this.__ptr, val)
}

VideoModeChangeInfo.prototype.__get_yRes = function() {
	return Polycode.VideoModeChangeInfo__get_yRes(this.__ptr)
}

VideoModeChangeInfo.prototype.__set_yRes = function(val) {
	Polycode.VideoModeChangeInfo__set_yRes(this.__ptr, val)
}

VideoModeChangeInfo.prototype.__get_fullScreen = function() {
	return Polycode.VideoModeChangeInfo__get_fullScreen(this.__ptr)
}

VideoModeChangeInfo.prototype.__set_fullScreen = function(val) {
	Polycode.VideoModeChangeInfo__set_fullScreen(this.__ptr, val)
}

VideoModeChangeInfo.prototype.__get_vSync = function() {
	return Polycode.VideoModeChangeInfo__get_vSync(this.__ptr)
}

VideoModeChangeInfo.prototype.__set_vSync = function(val) {
	Polycode.VideoModeChangeInfo__set_vSync(this.__ptr, val)
}

VideoModeChangeInfo.prototype.__get_aaLevel = function() {
	return Polycode.VideoModeChangeInfo__get_aaLevel(this.__ptr)
}

VideoModeChangeInfo.prototype.__set_aaLevel = function(val) {
	Polycode.VideoModeChangeInfo__set_aaLevel(this.__ptr, val)
}

VideoModeChangeInfo.prototype.__get_anisotropyLevel = function() {
	return Polycode.VideoModeChangeInfo__get_anisotropyLevel(this.__ptr)
}

VideoModeChangeInfo.prototype.__set_anisotropyLevel = function(val) {
	Polycode.VideoModeChangeInfo__set_anisotropyLevel(this.__ptr, val)
}

VideoModeChangeInfo.prototype.__get_retinaSupport = function() {
	return Polycode.VideoModeChangeInfo__get_retinaSupport(this.__ptr)
}

VideoModeChangeInfo.prototype.__set_retinaSupport = function(val) {
	Polycode.VideoModeChangeInfo__set_retinaSupport(this.__ptr, val)
}

Duktape.fin(VideoModeChangeInfo.prototype, function (x) {
	if (x === VideoModeChangeInfo.prototype) {
		return;
	}
	Polycode.VideoModeChangeInfo__delete(x.__ptr)
})
