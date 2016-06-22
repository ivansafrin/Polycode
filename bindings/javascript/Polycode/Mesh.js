require('Polycode/Resource')

function Mesh() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.Mesh()
	}
}

Mesh.prototype = Object.create(Resource.prototype);


Mesh.prototype.MeshFromFileName = function(fileName) {
	var retVal = new Mesh()
	retVal.__ptr = Polycode.Mesh_MeshFromFileName(fileName)
	return retVal
}

Mesh.prototype.Copy = function() {
	var retVal = new Mesh()
	retVal.__ptr = Polycode.Mesh_Copy(this.__ptr)
	return retVal
}

Mesh.prototype.loadMesh = function(fileName) {
	Polycode.Mesh_loadMesh(this.__ptr, fileName)
}

Mesh.prototype.saveToFile = function(fileName,writeNormals,writeTangents,writeColors,writeBoneWeights,writeUVs,writeSecondaryUVs) {
	Polycode.Mesh_saveToFile(this.__ptr, fileName, writeNormals, writeTangents, writeColors, writeBoneWeights, writeUVs, writeSecondaryUVs)
}

Mesh.prototype.loadFromFile = function(inFile) {
	Polycode.Mesh_loadFromFile(this.__ptr, inFile.__ptr)
}

Mesh.prototype.addSubmesh = function(newSubmesh) {
	Polycode.Mesh_addSubmesh(this.__ptr, newSubmesh)
}

Mesh.prototype.removeSubmeshAtIndex = function(index) {
	Polycode.Mesh_removeSubmeshAtIndex(this.__ptr, index)
}

Mesh.prototype.getNumSubmeshes = function() {
	return Polycode.Mesh_getNumSubmeshes(this.__ptr)
}

Mesh.prototype.getSubmeshAtIndex = function(index) {
	var retVal = new MeshGeometry()
	retVal.__ptr = Polycode.Mesh_getSubmeshAtIndex(this.__ptr, index)
	return retVal
}

Mesh.prototype.getSubmeshPointer = function(index) {
	var retVal = new MeshGeometry()
	retVal.__ptr = Polycode.Mesh_getSubmeshPointer(this.__ptr, index)
	return retVal
}

Mesh.prototype.clearMesh = function() {
	Polycode.Mesh_clearMesh(this.__ptr)
}

Mesh.prototype.calculateBBox = function() {
	var retVal = new Vector3()
	retVal.__ptr = Polycode.Mesh_calculateBBox(this.__ptr)
	return retVal
}

Mesh.prototype.getRadius = function() {
	return Polycode.Mesh_getRadius(this.__ptr)
}
