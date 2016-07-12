function MeshGeometry() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.MeshGeometry()
	}
	Object.defineProperties(this, {
		'meshType': { enumerable: true, configurable: true, get: MeshGeometry.prototype.__get_meshType, set: MeshGeometry.prototype.__set_meshType},
		'dataChanged': { enumerable: true, configurable: true, get: MeshGeometry.prototype.__get_dataChanged, set: MeshGeometry.prototype.__set_dataChanged},
		'indexedMesh': { enumerable: true, configurable: true, get: MeshGeometry.prototype.__get_indexedMesh, set: MeshGeometry.prototype.__set_indexedMesh}
	})
}

MeshGeometry.TRISTRIP_MESH = 0
MeshGeometry.TRI_MESH = 1
MeshGeometry.TRIFAN_MESH = 2
MeshGeometry.LINE_MESH = 4
MeshGeometry.POINT_MESH = 5
MeshGeometry.LINE_STRIP_MESH = 6
MeshGeometry.LINE_LOOP_MESH = 7

MeshGeometry.prototype.__get_meshType = function() {
	return Polycode.MeshGeometry__get_meshType(this.__ptr)
}

MeshGeometry.prototype.__set_meshType = function(val) {
	Polycode.MeshGeometry__set_meshType(this.__ptr, val)
}

MeshGeometry.prototype.__get_dataChanged = function() {
	return Polycode.MeshGeometry__get_dataChanged(this.__ptr)
}

MeshGeometry.prototype.__set_dataChanged = function(val) {
	Polycode.MeshGeometry__set_dataChanged(this.__ptr, val)
}

MeshGeometry.prototype.__get_indexedMesh = function() {
	return Polycode.MeshGeometry__get_indexedMesh(this.__ptr)
}

MeshGeometry.prototype.__set_indexedMesh = function(val) {
	Polycode.MeshGeometry__set_indexedMesh(this.__ptr, val)
}

Duktape.fin(MeshGeometry.prototype, function (x) {
	if (x === MeshGeometry.prototype) {
		return;
	}
	Polycode.MeshGeometry__delete(x.__ptr)
})

MeshGeometry.prototype.clearMesh = function() {
	Polycode.MeshGeometry_clearMesh(this.__ptr)
}

MeshGeometry.prototype.getVertexCount = function() {
	return Polycode.MeshGeometry_getVertexCount(this.__ptr)
}

MeshGeometry.prototype.createPlane = function(w,h,tilingValue) {
	Polycode.MeshGeometry_createPlane(this.__ptr, w, h, tilingValue)
}

MeshGeometry.prototype.createVPlane = function(w,h,tilingValue) {
	Polycode.MeshGeometry_createVPlane(this.__ptr, w, h, tilingValue)
}

MeshGeometry.prototype.createCircle = function(w,h,numSegments,tilingValue) {
	Polycode.MeshGeometry_createCircle(this.__ptr, w, h, numSegments, tilingValue)
}

MeshGeometry.prototype.createLineCircle = function(w,h,numSegments,tilingValue) {
	Polycode.MeshGeometry_createLineCircle(this.__ptr, w, h, numSegments, tilingValue)
}

MeshGeometry.prototype.createTorus = function(radius,tubeRadius,segmentsW,segmentsH,tilingValue) {
	Polycode.MeshGeometry_createTorus(this.__ptr, radius, tubeRadius, segmentsW, segmentsH, tilingValue)
}

MeshGeometry.prototype.createBox = function(w,d,h,tilingValue) {
	Polycode.MeshGeometry_createBox(this.__ptr, w, d, h, tilingValue)
}

MeshGeometry.prototype.createSphere = function(radius,numRings,numSegments,tilingValue) {
	Polycode.MeshGeometry_createSphere(this.__ptr, radius, numRings, numSegments, tilingValue)
}

MeshGeometry.prototype.createIcosphere = function(radius,subdivisions) {
	Polycode.MeshGeometry_createIcosphere(this.__ptr, radius, subdivisions)
}

MeshGeometry.prototype.createOctosphere = function(radius,subdivisions) {
	Polycode.MeshGeometry_createOctosphere(this.__ptr, radius, subdivisions)
}

MeshGeometry.prototype.createCylinder = function(height,radius,numSegments,capped,tilingValue) {
	Polycode.MeshGeometry_createCylinder(this.__ptr, height, radius, numSegments, capped, tilingValue)
}

MeshGeometry.prototype.createCone = function(height,radius,numSegments,tilingValue) {
	Polycode.MeshGeometry_createCone(this.__ptr, height, radius, numSegments, tilingValue)
}

MeshGeometry.prototype.recenterMesh = function() {
	var retVal = new Vector3("__skip_ptr__")
	retVal.__ptr = Polycode.MeshGeometry_recenterMesh(this.__ptr)
	return retVal
}

MeshGeometry.prototype.setVertexAtOffset = function(offset,x,y,z) {
	Polycode.MeshGeometry_setVertexAtOffset(this.__ptr, offset, x, y, z)
}

MeshGeometry.prototype.addVertexWithUVAndNormal = function(x,y,z,u,v,nx,ny,nz) {
	Polycode.MeshGeometry_addVertexWithUVAndNormal(this.__ptr, x, y, z, u, v, nx, ny, nz)
}

MeshGeometry.prototype.addTexCoord = function(u,v) {
	Polycode.MeshGeometry_addTexCoord(this.__ptr, u, v)
}

MeshGeometry.prototype.addTexCoord2 = function(u,v) {
	Polycode.MeshGeometry_addTexCoord2(this.__ptr, u, v)
}

MeshGeometry.prototype.addTangent = function(x,y,z) {
	Polycode.MeshGeometry_addTangent(this.__ptr, x, y, z)
}

MeshGeometry.prototype.addVertexWithUV = function(x,y,z,u,v) {
	Polycode.MeshGeometry_addVertexWithUV(this.__ptr, x, y, z, u, v)
}

MeshGeometry.prototype.addVertex = function(x,y,z) {
	Polycode.MeshGeometry_addVertex(this.__ptr, x, y, z)
}

MeshGeometry.prototype.addNormal = function(nx,ny,nz) {
	Polycode.MeshGeometry_addNormal(this.__ptr, nx, ny, nz)
}

MeshGeometry.prototype.addBoneAssignments = function(b1Weight,b1Index,b2Weight,b2Index,b3Weight,b3Index,b4Weight,b4Index) {
	Polycode.MeshGeometry_addBoneAssignments(this.__ptr, b1Weight, b1Index, b2Weight, b2Index, b3Weight, b3Index, b4Weight, b4Index)
}

MeshGeometry.prototype.addColor = function(r,g,b,a) {
	Polycode.MeshGeometry_addColor(this.__ptr, r, g, b, a)
}

MeshGeometry.prototype.getVertexPosition = function(vertexOffset) {
	var retVal = new Vector3("__skip_ptr__")
	retVal.__ptr = Polycode.MeshGeometry_getVertexPosition(this.__ptr, vertexOffset)
	return retVal
}

MeshGeometry.prototype.getVertexPositionAtIndex = function(index) {
	var retVal = new Vector3("__skip_ptr__")
	retVal.__ptr = Polycode.MeshGeometry_getVertexPositionAtIndex(this.__ptr, index)
	return retVal
}

MeshGeometry.prototype.getVertexTexCoord = function(vertexOffset) {
	var retVal = new Vector2("__skip_ptr__")
	retVal.__ptr = Polycode.MeshGeometry_getVertexTexCoord(this.__ptr, vertexOffset)
	return retVal
}

MeshGeometry.prototype.getVertexTexCoordAtIndex = function(index) {
	var retVal = new Vector2("__skip_ptr__")
	retVal.__ptr = Polycode.MeshGeometry_getVertexTexCoordAtIndex(this.__ptr, index)
	return retVal
}

MeshGeometry.prototype.getRadius = function() {
	return Polycode.MeshGeometry_getRadius(this.__ptr)
}

MeshGeometry.prototype.calculateNormals = function() {
	Polycode.MeshGeometry_calculateNormals(this.__ptr)
}

MeshGeometry.prototype.calculateTangents = function() {
	Polycode.MeshGeometry_calculateTangents(this.__ptr)
}

MeshGeometry.prototype.getMeshType = function() {
	return Polycode.MeshGeometry_getMeshType(this.__ptr)
}

MeshGeometry.prototype.setMeshType = function(newType) {
	Polycode.MeshGeometry_setMeshType(this.__ptr, newType)
}

MeshGeometry.prototype.getIndexGroupSize = function() {
	return Polycode.MeshGeometry_getIndexGroupSize(this.__ptr)
}

MeshGeometry.prototype.calculateBBox = function() {
	var retVal = new Vector3("__skip_ptr__")
	retVal.__ptr = Polycode.MeshGeometry_calculateBBox(this.__ptr)
	return retVal
}

MeshGeometry.prototype.addIndexedFace = function(i1,i2) {
	Polycode.MeshGeometry_addIndexedFace(this.__ptr, i1, i2)
}

MeshGeometry.prototype.addIndex = function(index) {
	Polycode.MeshGeometry_addIndex(this.__ptr, index)
}

MeshGeometry.prototype.removeVertexRange = function(beginRemoveVertex,vertexRemovalCount) {
	Polycode.MeshGeometry_removeVertexRange(this.__ptr, beginRemoveVertex, vertexRemovalCount)
}

MeshGeometry.prototype.removeFace = function(faceIndex) {
	Polycode.MeshGeometry_removeFace(this.__ptr, faceIndex)
}

MeshGeometry.prototype.removeUnusedVertices = function() {
	return Polycode.MeshGeometry_removeUnusedVertices(this.__ptr)
}

MeshGeometry.prototype.getIndexCount = function() {
	return Polycode.MeshGeometry_getIndexCount(this.__ptr)
}

MeshGeometry.prototype.subdivideToRadius = function(radius,subdivisions) {
	Polycode.MeshGeometry_subdivideToRadius(this.__ptr, radius, subdivisions)
}

MeshGeometry.prototype.calculateFaceTangent = function(v1,v2,v3,texCoord1,texCoord2,texCoord3) {
	var retVal = new Vector3("__skip_ptr__")
	retVal.__ptr = Polycode.MeshGeometry_calculateFaceTangent(v1, v2, v3, texCoord1, texCoord2, texCoord3)
	return retVal
}

MeshGeometry.prototype.saveAsOBJ = function(fileName) {
	Polycode.MeshGeometry_saveAsOBJ(this.__ptr, fileName)
}

MeshGeometry.prototype.normalizeBoneWeights = function() {
	Polycode.MeshGeometry_normalizeBoneWeights(this.__ptr)
}
