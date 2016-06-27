require('Polycode/Polycode::AudioInterface')

function SDLAudioInterface() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.SDLAudioInterface()
	}
}

SDLAudioInterface.prototype = Object.create(Polycode::AudioInterface.prototype);

Duktape.fin(SDLAudioInterface.prototype, function (x) {
	if (x === SDLAudioInterface.prototype) {
		return;
	}
	Polycode.SDLAudioInterface__delete(x.__ptr)
})

SDLAudioInterface.prototype.sdlCallback = function(userData,_stream,_length) {
	Polycode.SDLAudioInterface_sdlCallback(userData.__ptr, _stream.__ptr, _length)
}
