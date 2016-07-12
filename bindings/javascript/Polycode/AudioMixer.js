function AudioMixer() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.AudioMixer()
	}
	Object.defineProperties(this, {
		'globalVolume': { enumerable: true, configurable: true, get: AudioMixer.prototype.__get_globalVolume, set: AudioMixer.prototype.__set_globalVolume},
		'listenerPosition': { enumerable: true, configurable: true, get: AudioMixer.prototype.__get_listenerPosition, set: AudioMixer.prototype.__set_listenerPosition},
		'listenerOrientation': { enumerable: true, configurable: true, get: AudioMixer.prototype.__get_listenerOrientation, set: AudioMixer.prototype.__set_listenerOrientation}
	})
}


AudioMixer.prototype.__get_globalVolume = function() {
	return Polycode.AudioMixer__get_globalVolume(this.__ptr)
}

AudioMixer.prototype.__set_globalVolume = function(val) {
	Polycode.AudioMixer__set_globalVolume(this.__ptr, val)
}

AudioMixer.prototype.__get_listenerPosition = function() {
	var retVal = new Vector3("__skip_ptr__")
	retVal.__ptr = 	Polycode.AudioMixer__get_listenerPosition(this.__ptr)
	return retVal
}

AudioMixer.prototype.__set_listenerPosition = function(val) {
	Polycode.AudioMixer__set_listenerPosition(this.__ptr, val.__ptr)
}

AudioMixer.prototype.__get_listenerOrientation = function() {
	var retVal = new Quaternion("__skip_ptr__")
	retVal.__ptr = 	Polycode.AudioMixer__get_listenerOrientation(this.__ptr)
	return retVal
}

AudioMixer.prototype.__set_listenerOrientation = function(val) {
	Polycode.AudioMixer__set_listenerOrientation(this.__ptr, val.__ptr)
}

Duktape.fin(AudioMixer.prototype, function (x) {
	if (x === AudioMixer.prototype) {
		return;
	}
	Polycode.AudioMixer__delete(x.__ptr)
})
