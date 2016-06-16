function SoundManager() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.SoundManager()
	}
}

Duktape.fin(SoundManager.prototype, function (x) {
	if (x === SoundManager.prototype) {
		return;
	}
	Polycode.SoundManager__delete(x.__ptr)
})

SoundManager.prototype.setListenerPosition = function(position) {
	Polycode.SoundManager_setListenerPosition(this.__ptr, position)
}

SoundManager.prototype.setListenerOrientation = function(orientation) {
	Polycode.SoundManager_setListenerOrientation(this.__ptr, orientation)
}

SoundManager.prototype.recordSound = function(rate,sampleSize) {
	return Polycode.SoundManager_recordSound(this.__ptr, rate, sampleSize)
}

SoundManager.prototype.stopRecording = function(generateFloatBuffer) {
	var retVal = new Sound()
	retVal.__ptr = Polycode.SoundManager_stopRecording(this.__ptr, generateFloatBuffer)
	return retVal
}

SoundManager.prototype.setAudioInterface = function(audioInterface) {
	Polycode.SoundManager_setAudioInterface(this.__ptr, audioInterface.__ptr)
}

SoundManager.prototype.Update = function() {
	Polycode.SoundManager_Update(this.__ptr)
}

SoundManager.prototype.setGlobalVolume = function(globalVolume) {
	Polycode.SoundManager_setGlobalVolume(this.__ptr, globalVolume)
}

SoundManager.prototype.registerSound = function(sound) {
	Polycode.SoundManager_registerSound(this.__ptr, sound.__ptr)
}

SoundManager.prototype.unregisterSound = function(sound) {
	Polycode.SoundManager_unregisterSound(this.__ptr, sound.__ptr)
}
