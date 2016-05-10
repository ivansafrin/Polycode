function AudioStreamingSource() {
}
Duktape.fin(AudioStreamingSource.prototype, function (x) {
	if (x === AudioStreamingSource.prototype) {
		return;
	}
	Polycode.AudioStreamingSource__delete(x.__ptr)
})

AudioStreamingSource.prototype.getNumChannels = function() {
	return Polycode.AudioStreamingSource_getNumChannels(this.__ptr)
}

AudioStreamingSource.prototype.getFrequency = function() {
	return Polycode.AudioStreamingSource_getFrequency(this.__ptr)
}
