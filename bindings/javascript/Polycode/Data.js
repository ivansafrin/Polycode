function Data() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.Data()
	}
}


Duktape.fin(Data.prototype, function (x) {
	if (x === Data.prototype) {
		return;
	}
	Polycode.Data__delete(x.__ptr)
})

Data.prototype.getAsString = function(encoding) {
	return Polycode.Data_getAsString(this.__ptr, encoding)
}

Data.prototype.setFromString = function(str,encoding) {
	Polycode.Data_setFromString(this.__ptr, str, encoding)
}
