function AudioMixer() {
	Object.defineProperties(this, {
		'globalVolume': { enumerable: true, configurable: true, get: AudioMixer.prototype.__get_globalVolume, set: AudioMixer.prototype.__set_globalVolume},
		'mixerMutex': { enumerable: true, configurable: true, get: AudioMixer.prototype.__get_mixerMutex, set: AudioMixer.prototype.__set_mixerMutex}
	})
}
AudioMixer.prototype.__get_globalVolume = function() {
	return Polycode.AudioMixer__get_globalVolume(this.__ptr)
}

AudioMixer.prototype.__set_globalVolume = function(val) {
	Polycode.AudioMixer__set_globalVolume(this.__ptr, val)
}

AudioMixer.prototype.__get_mixerMutex = function() {
	var retVal = new CoreMutex()
	retVal.__ptr = 	Polycode.AudioMixer__get_mixerMutex(this.__ptr)
	return retVal
}

AudioMixer.prototype.__set_mixerMutex = function(val) {
	Polycode.AudioMixer__set_mixerMutex(this.__ptr, val.__ptr)
}


AudioMixer.prototype.mixIntoBuffer = function(buffer,numSamples) {
	Polycode.AudioMixer_mixIntoBuffer(this.__ptr, buffer,numSamples)
}
