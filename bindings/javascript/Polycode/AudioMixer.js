function AudioMixer() {
}

AudioMixer.prototype.mixIntoBuffer = function(buffer,numSamples) {
	Polycode.AudioMixer_mixIntoBuffer(this.__ptr, buffer,numSamples)
}
