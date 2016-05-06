function PhysFSFileProvider() {
}

PhysFSFileProvider.prototype.openFile = function(fileName,opts) {
	Polycode.PhysFSFileProvider_openFile(this.__ptr, fileName,opts)
}

PhysFSFileProvider.prototype.closeFile = function(file) {
	Polycode.PhysFSFileProvider_closeFile(this.__ptr, file)
}

PhysFSFileProvider.prototype.parseFolder = function(pathString,showHidden,targetVector) {
	Polycode.PhysFSFileProvider_parseFolder(this.__ptr, pathString,showHidden,targetVector)
}

PhysFSFileProvider.prototype.addSource = function(source) {
	Polycode.PhysFSFileProvider_addSource(this.__ptr, source)
}

PhysFSFileProvider.prototype.removeSource = function(source) {
	Polycode.PhysFSFileProvider_removeSource(this.__ptr, source)
}
