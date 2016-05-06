function OSFileEntry() {
}

OSFileEntry.prototype.init = function(path,name,type) {
	Polycode.OSFileEntry_init(this.__ptr, path,name,type)
}
