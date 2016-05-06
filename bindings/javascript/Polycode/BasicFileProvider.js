function BasicFileProvider() {
}

BasicFileProvider.prototype.openFile = function(fileName,opts) {
	Polycode.BasicFileProvider_openFile(this.__ptr, fileName,opts)
}

BasicFileProvider.prototype.closeFile = function(file) {
	Polycode.BasicFileProvider_closeFile(this.__ptr, file)
}

BasicFileProvider.prototype.addSource = function(source) {
	Polycode.BasicFileProvider_addSource(this.__ptr, source)
}

BasicFileProvider.prototype.removeSource = function(source) {
	Polycode.BasicFileProvider_removeSource(this.__ptr, source)
}
