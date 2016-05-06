function SoundManager() {
}

SoundManager.prototype.setListenerPosition = function(position) {
	Polycode.SoundManager_setListenerPosition(this.__ptr, position)
}

SoundManager.prototype.setListenerOrientation = function(orientation,upVector) {
	Polycode.SoundManager_setListenerOrientation(this.__ptr, orientation,upVector)
}

SoundManager.prototype.recordSound = function(rate,sampleSize) {
	Polycode.SoundManager_recordSound(this.__ptr, rate,sampleSize)
}

SoundManager.prototype.stopRecording = function(generateFloatBuffer) {
	Polycode.SoundManager_stopRecording(this.__ptr, generateFloatBuffer)
}

SoundManager.prototype.setAudioInterface = function(audioInterface) {
	Polycode.SoundManager_setAudioInterface(this.__ptr, audioInterface)
}

SoundManager.prototype.Update = function() {
	Polycode.SoundManager_Update(this.__ptr)
}

SoundManager.prototype.setGlobalVolume = function(globalVolume) {
	Polycode.SoundManager_setGlobalVolume(this.__ptr, globalVolume)
}

SoundManager.prototype.registerSound = function(sound) {
	Polycode.SoundManager_registerSound(this.__ptr, sound)
}

SoundManager.prototype.unregisterSound = function(sound) {
	Polycode.SoundManager_unregisterSound(this.__ptr, sound)
}
