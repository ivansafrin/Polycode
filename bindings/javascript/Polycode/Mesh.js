function Mesh() {
	Object.defineProperties(this, {
		'indexedMesh': { enumerable: true, configurable: true, get: Mesh.prototype.__get_indexedMesh, set: Mesh.prototype.__set_indexedMesh}
	})
}
Mesh.prototype.__get_indexedMesh = function() {
	return Polycode.Mesh__get_indexedMesh(this.__ptr)
}

Mesh.prototype.__set_indexedMesh = function(val) {
	Polycode.Mesh__set_indexedMesh(this.__ptr, val)
}


Mesh.prototype.loadMesh = function(fileName) {
	Polycode.Mesh_loadMesh(this.__ptr, fileName)
}

Mesh.prototype.clearMesh = function() {
	Polycode.Mesh_clearMesh(this.__ptr)
}

Mesh.prototype.saveToFile = function(fileName,writeNormals,writeTangents,writeColors,writeBoneWeights,writeUVs,writeSecondaryUVs) {
	Polycode.Mesh_saveToFile(this.__ptr, fileName,writeNormals,writeTangents,writeColors,writeBoneWeights,writeUVs,writeSecondaryUVs)
}

Mesh.prototype.loadFromFile = function(inFile) {
	Polycode.Mesh_loadFromFile(this.__ptr, inFile)
}

Mesh.prototype.getVertexCount = function() {
	return Polycode.Mesh_getVertexCount(this.__ptr)
}

Mesh.prototype.createPlane = function(w,h,tilingValue) {
	Polycode.Mesh_createPlane(this.__ptr, w,h,tilingValue)
}

Mesh.prototype.createVPlane = function(w,h,tilingValue) {
	Polycode.Mesh_createVPlane(this.__ptr, w,h,tilingValue)
}

Mesh.prototype.createCircle = function(w,h,numSegments,tilingValue) {
	Polycode.Mesh_createCircle(this.__ptr, w,h,numSegments,tilingValue)
}

Mesh.prototype.createLineCircle = function(w,h,numSegments,tilingValue) {
	Polycode.Mesh_createLineCircle(this.__ptr, w,h,numSegments,tilingValue)
}

Mesh.prototype.createTorus = function(radius,tubeRadius,segmentsW,segmentsH,tilingValue) {
	Polycode.Mesh_createTorus(this.__ptr, radius,tubeRadius,segmentsW,segmentsH,tilingValue)
}

Mesh.prototype.createBox = function(w,d,h,tilingValue) {
	Polycode.Mesh_createBox(this.__ptr, w,d,h,tilingValue)
}

Mesh.prototype.createSphere = function(radius,numRings,numSegments,tilingValue) {
	Polycode.Mesh_createSphere(this.__ptr, radius,numRings,numSegments,tilingValue)
}

Mesh.prototype.createIcosphere = function(radius,subdivisions) {
	Polycode.Mesh_createIcosphere(this.__ptr, radius,subdivisions)
}

Mesh.prototype.createOctosphere = function(radius,subdivisions) {
	Polycode.Mesh_createOctosphere(this.__ptr, radius,subdivisions)
}

Mesh.prototype.createCylinder = function(height,radius,numSegments,capped,tilingValue) {
	Polycode.Mesh_createCylinder(this.__ptr, height,radius,numSegments,capped,tilingValue)
}

Mesh.prototype.createCone = function(height,radius,numSegments,tilingValue) {
	Polycode.Mesh_createCone(this.__ptr, height,radius,numSegments,tilingValue)
}

Mesh.prototype.recenterMesh = function() {
	var retVal = new Vector3()
	retVal.__ptr = Polycode.Mesh_recenterMesh(this.__ptr)
	return retVal
}

Mesh.prototype.setVertexAtOffset = function(offset,x,y,z) {
	Polycode.Mesh_setVertexAtOffset(this.__ptr, offset,x,y,z)
}

Mesh.prototype.addVertexWithUVAndNormal = function(x,y,z,u,v,nx,ny,nz) {
	Polycode.Mesh_addVertexWithUVAndNormal(this.__ptr, x,y,z,u,v,nx,ny,nz)
}

Mesh.prototype.addTexCoord = function(u,v) {
	Polycode.Mesh_addTexCoord(this.__ptr, u,v)
}

Mesh.prototype.addTexCoord2 = function(u,v) {
	Polycode.Mesh_addTexCoord2(this.__ptr, u,v)
}

Mesh.prototype.addTangent = function(x,y,z) {
	Polycode.Mesh_addTangent(this.__ptr, x,y,z)
}

Mesh.prototype.addVertexWithUV = function(x,y,z,u,v) {
	Polycode.Mesh_addVertexWithUV(this.__ptr, x,y,z,u,v)
}

Mesh.prototype.addVertex = function(x,y,z) {
	Polycode.Mesh_addVertex(this.__ptr, x,y,z)
}

Mesh.prototype.addNormal = function(nx,ny,nz) {
	Polycode.Mesh_addNormal(this.__ptr, nx,ny,nz)
}

Mesh.prototype.addBoneAssignments = function(b1Weight,b1Index,b2Weight,b2Index,b3Weight,b3Index,b4Weight,b4Index) {
	Polycode.Mesh_addBoneAssignments(this.__ptr, b1Weight,b1Index,b2Weight,b2Index,b3Weight,b3Index,b4Weight,b4Index)
}

Mesh.prototype.addColor = function(r,g,b,a) {
	Polycode.Mesh_addColor(this.__ptr, r,g,b,a)
}

Mesh.prototype.getVertexPosition = function(vertexOffset) {
	var retVal = new Vector3()
	retVal.__ptr = Polycode.Mesh_getVertexPosition(this.__ptr, vertexOffset)
	return retVal
}

Mesh.prototype.getVertexPositionAtIndex = function(index) {
	var retVal = new Vector3()
	retVal.__ptr = Polycode.Mesh_getVertexPositionAtIndex(this.__ptr, index)
	return retVal
}

Mesh.prototype.getVertexTexCoord = function(vertexOffset) {
	var retVal = new Vector2()
	retVal.__ptr = Polycode.Mesh_getVertexTexCoord(this.__ptr, vertexOffset)
	return retVal
}

Mesh.prototype.getVertexTexCoordAtIndex = function(index) {
	var retVal = new Vector2()
	retVal.__ptr = Polycode.Mesh_getVertexTexCoordAtIndex(this.__ptr, index)
	return retVal
}

Mesh.prototype.Copy = function() {
	var retVal = new Mesh()
	retVal.__ptr = Polycode.Mesh_Copy(this.__ptr)
	return retVal
}

Mesh.prototype.getRadius = function() {
	return Polycode.Mesh_getRadius(this.__ptr)
}

Mesh.prototype.calculateNormals = function() {
	Polycode.Mesh_calculateNormals(this.__ptr)
}

Mesh.prototype.calculateTangents = function() {
	Polycode.Mesh_calculateTangents(this.__ptr)
}

Mesh.prototype.getMeshType = function() {
	return Polycode.Mesh_getMeshType(this.__ptr)
}

Mesh.prototype.setMeshType = function(newType) {
	Polycode.Mesh_setMeshType(this.__ptr, newType)
}

Mesh.prototype.getIndexGroupSize = function() {
	return Polycode.Mesh_getIndexGroupSize(this.__ptr)
}

Mesh.prototype.calculateBBox = function() {
	var retVal = new Vector3()
	retVal.__ptr = Polycode.Mesh_calculateBBox(this.__ptr)
	return retVal
}

Mesh.prototype.hasVertexBuffer = function() {
	return Polycode.Mesh_hasVertexBuffer(this.__ptr)
}

Mesh.prototype.addIndexedFace = function(i1,i2) {
	Polycode.Mesh_addIndexedFace(this.__ptr, i1,i2)
}

Mesh.prototype.addIndex = function(index) {
	Polycode.Mesh_addIndex(this.__ptr, index)
}

Mesh.prototype.removeVertexRange = function(beginRemoveVertex,vertexRemovalCount) {
	Polycode.Mesh_removeVertexRange(this.__ptr, beginRemoveVertex,vertexRemovalCount)
}

Mesh.prototype.removeFace = function(faceIndex) {
	Polycode.Mesh_removeFace(this.__ptr, faceIndex)
}

Mesh.prototype.removeUnusedVertices = function() {
	return Polycode.Mesh_removeUnusedVertices(this.__ptr)
}

Mesh.prototype.getIndexCount = function() {
	return Polycode.Mesh_getIndexCount(this.__ptr)
}

Mesh.prototype.subdivideToRadius = function(radius,subdivisions) {
	Polycode.Mesh_subdivideToRadius(this.__ptr, radius,subdivisions)
}

Mesh.prototype.saveAsOBJ = function(fileName) {
	Polycode.Mesh_saveAsOBJ(this.__ptr, fileName)
}

Mesh.prototype.normalizeBoneWeights = function() {
	Polycode.Mesh_normalizeBoneWeights(this.__ptr)
}
