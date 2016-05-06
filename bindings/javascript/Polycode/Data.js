function Data() {
}

Data.prototype.loadFromFile = function(fileName) {
	Polycode.Data_loadFromFile(this.__ptr, fileName)
}

Data.prototype.getAsString = function(encoding) {
	Polycode.Data_getAsString(this.__ptr, encoding)
}

Data.prototype.setFromString = function(str,encoding) {
	Polycode.Data_setFromString(this.__ptr, str,encoding)
}

Data.prototype.saveToFile = function(fileName) {
	Polycode.Data_saveToFile(this.__ptr, fileName)
}

Data.prototype.getData = function() {
	Polycode.Data_getData(this.__ptr)
}
