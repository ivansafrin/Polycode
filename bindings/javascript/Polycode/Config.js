function Config() {
}

Config.prototype.loadConfig = function(configNamespace,fileName) {
	Polycode.Config_loadConfig(this.__ptr, configNamespace,fileName)
}

Config.prototype.saveConfig = function(configNamespace,fileName) {
	Polycode.Config_saveConfig(this.__ptr, configNamespace,fileName)
}

Config.prototype.getEntry = function(configNamespace,key) {
	Polycode.Config_getEntry(this.__ptr, configNamespace,key)
}

Config.prototype.setStringValue = function(configNamespace,key,value) {
	Polycode.Config_setStringValue(this.__ptr, configNamespace,key,value)
}

Config.prototype.setNumericValue = function(configNamespace,key,value) {
	Polycode.Config_setNumericValue(this.__ptr, configNamespace,key,value)
}

Config.prototype.getNumericValue = function(configNamespace,key) {
	Polycode.Config_getNumericValue(this.__ptr, configNamespace,key)
}

Config.prototype.getStringValue = function(configNamespace,key) {
	Polycode.Config_getStringValue(this.__ptr, configNamespace,key)
}

Config.prototype.setBoolValue = function(configNamespace,key,value) {
	Polycode.Config_setBoolValue(this.__ptr, configNamespace,key,value)
}

Config.prototype.getBoolValue = function(configNamespace,key) {
	Polycode.Config_getBoolValue(this.__ptr, configNamespace,key)
}
