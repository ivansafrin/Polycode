require('Polycode/EventDispatcher')

function Entity() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.Entity()
	}
	Object.defineProperties(this, {
		'ownsChildren': { enumerable: true, configurable: true, get: Entity.prototype.__get_ownsChildren, set: Entity.prototype.__set_ownsChildren},
		'billboardMode': { enumerable: true, configurable: true, get: Entity.prototype.__get_billboardMode, set: Entity.prototype.__set_billboardMode},
		'color': { enumerable: true, configurable: true, get: Entity.prototype.__get_color, set: Entity.prototype.__set_color},
		'enabled': { enumerable: true, configurable: true, get: Entity.prototype.__get_enabled, set: Entity.prototype.__set_enabled},
		'visible': { enumerable: true, configurable: true, get: Entity.prototype.__get_visible, set: Entity.prototype.__set_visible},
		'depthWrite': { enumerable: true, configurable: true, get: Entity.prototype.__get_depthWrite, set: Entity.prototype.__set_depthWrite},
		'depthTest': { enumerable: true, configurable: true, get: Entity.prototype.__get_depthTest, set: Entity.prototype.__set_depthTest},
		'colorAffectsChildren': { enumerable: true, configurable: true, get: Entity.prototype.__get_colorAffectsChildren, set: Entity.prototype.__set_colorAffectsChildren},
		'visibilityAffectsChildren': { enumerable: true, configurable: true, get: Entity.prototype.__get_visibilityAffectsChildren, set: Entity.prototype.__set_visibilityAffectsChildren},
		'ignoreParentMatrix': { enumerable: true, configurable: true, get: Entity.prototype.__get_ignoreParentMatrix, set: Entity.prototype.__set_ignoreParentMatrix},
		'enableScissor': { enumerable: true, configurable: true, get: Entity.prototype.__get_enableScissor, set: Entity.prototype.__set_enableScissor},
		'scissorBox': { enumerable: true, configurable: true, get: Entity.prototype.__get_scissorBox, set: Entity.prototype.__set_scissorBox},
		'editorOnly': { enumerable: true, configurable: true, get: Entity.prototype.__get_editorOnly, set: Entity.prototype.__set_editorOnly},
		'id': { enumerable: true, configurable: true, get: Entity.prototype.__get_id, set: Entity.prototype.__set_id},
		'collisionShapeType': { enumerable: true, configurable: true, get: Entity.prototype.__get_collisionShapeType, set: Entity.prototype.__set_collisionShapeType},
		'processInputEvents': { enumerable: true, configurable: true, get: Entity.prototype.__get_processInputEvents, set: Entity.prototype.__set_processInputEvents},
		'blockMouseInput': { enumerable: true, configurable: true, get: Entity.prototype.__get_blockMouseInput, set: Entity.prototype.__set_blockMouseInput},
		'snapToPixels': { enumerable: true, configurable: true, get: Entity.prototype.__get_snapToPixels, set: Entity.prototype.__set_snapToPixels},
		'mouseOver': { enumerable: true, configurable: true, get: Entity.prototype.__get_mouseOver, set: Entity.prototype.__set_mouseOver},
		'rendererVis': { enumerable: true, configurable: true, get: Entity.prototype.__get_rendererVis, set: Entity.prototype.__set_rendererVis},
		'layerID': { enumerable: true, configurable: true, get: Entity.prototype.__get_layerID, set: Entity.prototype.__set_layerID}
	})
}


Entity.prototype = Object.create(EventDispatcher.prototype)

Entity.prototype.__get_ownsChildren = function() {
	return Polycode.Entity__get_ownsChildren(this.__ptr)
}

Entity.prototype.__set_ownsChildren = function(val) {
	Polycode.Entity__set_ownsChildren(this.__ptr, val)
}

Entity.prototype.__get_billboardMode = function() {
	return Polycode.Entity__get_billboardMode(this.__ptr)
}

Entity.prototype.__set_billboardMode = function(val) {
	Polycode.Entity__set_billboardMode(this.__ptr, val)
}

Entity.prototype.__get_color = function() {
	var retVal = new Color("__skip_ptr__")
	retVal.__ptr = 	Polycode.Entity__get_color(this.__ptr)
	return retVal
}

Entity.prototype.__set_color = function(val) {
	Polycode.Entity__set_color(this.__ptr, val.__ptr)
}

Entity.prototype.__get_enabled = function() {
	return Polycode.Entity__get_enabled(this.__ptr)
}

Entity.prototype.__set_enabled = function(val) {
	Polycode.Entity__set_enabled(this.__ptr, val)
}

Entity.prototype.__get_visible = function() {
	return Polycode.Entity__get_visible(this.__ptr)
}

Entity.prototype.__set_visible = function(val) {
	Polycode.Entity__set_visible(this.__ptr, val)
}

Entity.prototype.__get_depthWrite = function() {
	return Polycode.Entity__get_depthWrite(this.__ptr)
}

Entity.prototype.__set_depthWrite = function(val) {
	Polycode.Entity__set_depthWrite(this.__ptr, val)
}

Entity.prototype.__get_depthTest = function() {
	return Polycode.Entity__get_depthTest(this.__ptr)
}

Entity.prototype.__set_depthTest = function(val) {
	Polycode.Entity__set_depthTest(this.__ptr, val)
}

Entity.prototype.__get_colorAffectsChildren = function() {
	return Polycode.Entity__get_colorAffectsChildren(this.__ptr)
}

Entity.prototype.__set_colorAffectsChildren = function(val) {
	Polycode.Entity__set_colorAffectsChildren(this.__ptr, val)
}

Entity.prototype.__get_visibilityAffectsChildren = function() {
	return Polycode.Entity__get_visibilityAffectsChildren(this.__ptr)
}

Entity.prototype.__set_visibilityAffectsChildren = function(val) {
	Polycode.Entity__set_visibilityAffectsChildren(this.__ptr, val)
}

Entity.prototype.__get_ignoreParentMatrix = function() {
	return Polycode.Entity__get_ignoreParentMatrix(this.__ptr)
}

Entity.prototype.__set_ignoreParentMatrix = function(val) {
	Polycode.Entity__set_ignoreParentMatrix(this.__ptr, val)
}

Entity.prototype.__get_enableScissor = function() {
	return Polycode.Entity__get_enableScissor(this.__ptr)
}

Entity.prototype.__set_enableScissor = function(val) {
	Polycode.Entity__set_enableScissor(this.__ptr, val)
}

Entity.prototype.__get_scissorBox = function() {
	var retVal = new Rectangle("__skip_ptr__")
	retVal.__ptr = 	Polycode.Entity__get_scissorBox(this.__ptr)
	return retVal
}

Entity.prototype.__set_scissorBox = function(val) {
	Polycode.Entity__set_scissorBox(this.__ptr, val.__ptr)
}

Entity.prototype.__get_editorOnly = function() {
	return Polycode.Entity__get_editorOnly(this.__ptr)
}

Entity.prototype.__set_editorOnly = function(val) {
	Polycode.Entity__set_editorOnly(this.__ptr, val)
}

Entity.prototype.__get_id = function() {
	return Polycode.Entity__get_id(this.__ptr)
}

Entity.prototype.__set_id = function(val) {
	Polycode.Entity__set_id(this.__ptr, val)
}

Entity.prototype.__get_collisionShapeType = function() {
	var retVal = new char("__skip_ptr__")
	retVal.__ptr = 	Polycode.Entity__get_collisionShapeType(this.__ptr)
	return retVal
}

Entity.prototype.__set_collisionShapeType = function(val) {
	Polycode.Entity__set_collisionShapeType(this.__ptr, val.__ptr)
}

Entity.prototype.__get_processInputEvents = function() {
	return Polycode.Entity__get_processInputEvents(this.__ptr)
}

Entity.prototype.__set_processInputEvents = function(val) {
	Polycode.Entity__set_processInputEvents(this.__ptr, val)
}

Entity.prototype.__get_blockMouseInput = function() {
	return Polycode.Entity__get_blockMouseInput(this.__ptr)
}

Entity.prototype.__set_blockMouseInput = function(val) {
	Polycode.Entity__set_blockMouseInput(this.__ptr, val)
}

Entity.prototype.__get_snapToPixels = function() {
	return Polycode.Entity__get_snapToPixels(this.__ptr)
}

Entity.prototype.__set_snapToPixels = function(val) {
	Polycode.Entity__set_snapToPixels(this.__ptr, val)
}

Entity.prototype.__get_mouseOver = function() {
	return Polycode.Entity__get_mouseOver(this.__ptr)
}

Entity.prototype.__set_mouseOver = function(val) {
	Polycode.Entity__set_mouseOver(this.__ptr, val)
}

Entity.prototype.__get_rendererVis = function() {
	return Polycode.Entity__get_rendererVis(this.__ptr)
}

Entity.prototype.__set_rendererVis = function(val) {
	Polycode.Entity__set_rendererVis(this.__ptr, val)
}

Entity.prototype.__get_layerID = function() {
	var retVal = new char("__skip_ptr__")
	retVal.__ptr = 	Polycode.Entity__get_layerID(this.__ptr)
	return retVal
}

Entity.prototype.__set_layerID = function(val) {
	Polycode.Entity__set_layerID(this.__ptr, val.__ptr)
}


Entity.prototype.initEntity = function() {
	Polycode.Entity_initEntity(this.__ptr)
}

Entity.prototype.Update = function() {
	Polycode.Entity_Update(this.__ptr)
}

Entity.prototype.fixedUpdate = function() {
	Polycode.Entity_fixedUpdate(this.__ptr)
}

Entity.prototype.dirtyMatrix = function(val) {
	Polycode.Entity_dirtyMatrix(this.__ptr, val)
}

Entity.prototype.rebuildTransformMatrix = function() {
	Polycode.Entity_rebuildTransformMatrix(this.__ptr)
}

Entity.prototype.updateEntityMatrix = function() {
	Polycode.Entity_updateEntityMatrix(this.__ptr)
}

Entity.prototype.getTransformMatrix = function() {
	var retVal = new Matrix4("__skip_ptr__")
	retVal.__ptr = Polycode.Entity_getTransformMatrix(this.__ptr)
	return retVal
}

Entity.prototype.getConcatenatedMatrix = function() {
	var retVal = new Matrix4("__skip_ptr__")
	retVal.__ptr = Polycode.Entity_getConcatenatedMatrix(this.__ptr)
	return retVal
}

Entity.prototype.getAnchorAdjustedMatrix = function() {
	var retVal = new Matrix4("__skip_ptr__")
	retVal.__ptr = Polycode.Entity_getAnchorAdjustedMatrix(this.__ptr)
	return retVal
}

Entity.prototype.getConcatenatedRollMatrix = function() {
	var retVal = new Matrix4("__skip_ptr__")
	retVal.__ptr = Polycode.Entity_getConcatenatedRollMatrix(this.__ptr)
	return retVal
}

Entity.prototype.setTransformByMatrixPure = function(matrix) {
	Polycode.Entity_setTransformByMatrixPure(this.__ptr, matrix)
}

Entity.prototype.getLookAtMatrix = function(loc,upVector) {
	var retVal = new Matrix4("__skip_ptr__")
	retVal.__ptr = Polycode.Entity_getLookAtMatrix(this.__ptr, loc, upVector)
	return retVal
}

Entity.prototype.getNumChildren = function() {
	return Polycode.Entity_getNumChildren(this.__ptr)
}

Entity.prototype.setOwnsChildrenRecursive = function(val) {
	Polycode.Entity_setOwnsChildrenRecursive(this.__ptr, val)
}

Entity.prototype.getPosition = function() {
	var retVal = new Vector3("__skip_ptr__")
	retVal.__ptr = Polycode.Entity_getPosition(this.__ptr)
	return retVal
}

Entity.prototype.getPosition2D = function() {
	var retVal = new Vector2("__skip_ptr__")
	retVal.__ptr = Polycode.Entity_getPosition2D(this.__ptr)
	return retVal
}

Entity.prototype.getCombinedPosition = function() {
	var retVal = new Vector3("__skip_ptr__")
	retVal.__ptr = Polycode.Entity_getCombinedPosition(this.__ptr)
	return retVal
}

Entity.prototype.setPosition = function(x,y,z) {
	Polycode.Entity_setPosition(this.__ptr, x, y, z)
}

Entity.prototype.setPositionX = function(x) {
	Polycode.Entity_setPositionX(this.__ptr, x)
}

Entity.prototype.setPositionY = function(y) {
	Polycode.Entity_setPositionY(this.__ptr, y)
}

Entity.prototype.Translate = function(x,y,z) {
	Polycode.Entity_Translate(this.__ptr, x, y, z)
}

Entity.prototype.setPositionZ = function(z) {
	Polycode.Entity_setPositionZ(this.__ptr, z)
}

Entity.prototype.setScaleX = function(x) {
	Polycode.Entity_setScaleX(this.__ptr, x)
}

Entity.prototype.setScaleY = function(y) {
	Polycode.Entity_setScaleY(this.__ptr, y)
}

Entity.prototype.setScaleZ = function(z) {
	Polycode.Entity_setScaleZ(this.__ptr, z)
}

Entity.prototype.Scale = function(x,y,z) {
	Polycode.Entity_Scale(this.__ptr, x, y, z)
}

Entity.prototype.setScale = function(x,y,z) {
	Polycode.Entity_setScale(this.__ptr, x, y, z)
}

Entity.prototype.getCompoundScale = function() {
	var retVal = new Vector3("__skip_ptr__")
	retVal.__ptr = Polycode.Entity_getCompoundScale(this.__ptr)
	return retVal
}

Entity.prototype.getScale = function() {
	var retVal = new Vector3("__skip_ptr__")
	retVal.__ptr = Polycode.Entity_getScale(this.__ptr)
	return retVal
}

Entity.prototype.getRotationEuler = function() {
	var retVal = new Vector3("__skip_ptr__")
	retVal.__ptr = Polycode.Entity_getRotationEuler(this.__ptr)
	return retVal
}

Entity.prototype.getCombinedPitch = function() {
	return Polycode.Entity_getCombinedPitch(this.__ptr)
}

Entity.prototype.getCombinedYaw = function() {
	return Polycode.Entity_getCombinedYaw(this.__ptr)
}

Entity.prototype.getCombinedRoll = function() {
	return Polycode.Entity_getCombinedRoll(this.__ptr)
}

Entity.prototype.rebuildRotation = function() {
	Polycode.Entity_rebuildRotation(this.__ptr)
}

Entity.prototype.setRotationEuler = function(rotation) {
	Polycode.Entity_setRotationEuler(this.__ptr, rotation)
}

Entity.prototype.setPitch = function(pitch) {
	Polycode.Entity_setPitch(this.__ptr, pitch)
}

Entity.prototype.setYaw = function(yaw) {
	Polycode.Entity_setYaw(this.__ptr, yaw)
}

Entity.prototype.setRoll = function(roll) {
	Polycode.Entity_setRoll(this.__ptr, roll)
}

Entity.prototype.Roll = function(roll) {
	Polycode.Entity_Roll(this.__ptr, roll)
}

Entity.prototype.Yaw = function(yaw) {
	Polycode.Entity_Yaw(this.__ptr, yaw)
}

Entity.prototype.Pitch = function(pitch) {
	Polycode.Entity_Pitch(this.__ptr, pitch)
}

Entity.prototype.getPitch = function() {
	return Polycode.Entity_getPitch(this.__ptr)
}

Entity.prototype.getYaw = function() {
	return Polycode.Entity_getYaw(this.__ptr)
}

Entity.prototype.getRoll = function() {
	return Polycode.Entity_getRoll(this.__ptr)
}

Entity.prototype.getWidth = function() {
	return Polycode.Entity_getWidth(this.__ptr)
}

Entity.prototype.getHeight = function() {
	return Polycode.Entity_getHeight(this.__ptr)
}

Entity.prototype.getDepth = function() {
	return Polycode.Entity_getDepth(this.__ptr)
}

Entity.prototype.setWidth = function(width) {
	Polycode.Entity_setWidth(this.__ptr, width)
}

Entity.prototype.setHeight = function(height) {
	Polycode.Entity_setHeight(this.__ptr, height)
}

Entity.prototype.setDepth = function(depth) {
	Polycode.Entity_setDepth(this.__ptr, depth)
}

Entity.prototype.setRotationQuat = function(w,x,y,z) {
	Polycode.Entity_setRotationQuat(this.__ptr, w, x, y, z)
}

Entity.prototype.setRotationByQuaternion = function(quaternion) {
	Polycode.Entity_setRotationByQuaternion(this.__ptr, quaternion)
}

Entity.prototype.getRotationQuat = function() {
	var retVal = new Quaternion("__skip_ptr__")
	retVal.__ptr = Polycode.Entity_getRotationQuat(this.__ptr)
	return retVal
}

Entity.prototype.getConcatenatedQuat = function() {
	var retVal = new Quaternion("__skip_ptr__")
	retVal.__ptr = Polycode.Entity_getConcatenatedQuat(this.__ptr)
	return retVal
}

Entity.prototype.lookAt = function(loc,upVector) {
	Polycode.Entity_lookAt(this.__ptr, loc, upVector)
}

Entity.prototype.getCombinedColor = function() {
	var retVal = new Color("__skip_ptr__")
	retVal.__ptr = Polycode.Entity_getCombinedColor(this.__ptr)
	return retVal
}

Entity.prototype.setColor = function(r,g,b,a) {
	Polycode.Entity_setColor(this.__ptr, r, g, b, a)
}

Entity.prototype.setColorInt = function(r,g,b,a) {
	Polycode.Entity_setColorInt(this.__ptr, r, g, b, a)
}

Entity.prototype.setAnchorPoint = function(anchorPoint) {
	Polycode.Entity_setAnchorPoint(this.__ptr, anchorPoint)
}

Entity.prototype.getAnchorPoint = function() {
	var retVal = new Vector3("__skip_ptr__")
	retVal.__ptr = Polycode.Entity_getAnchorPoint(this.__ptr)
	return retVal
}

Entity.prototype.onMouseDown = function(ray,mouseButton,timestamp) {
	var retVal = new MouseEventResult("__skip_ptr__")
	retVal.__ptr = Polycode.Entity_onMouseDown(this.__ptr, ray, mouseButton, timestamp)
	return retVal
}

Entity.prototype.onMouseUp = function(ray,mouseButton,timestamp) {
	var retVal = new MouseEventResult("__skip_ptr__")
	retVal.__ptr = Polycode.Entity_onMouseUp(this.__ptr, ray, mouseButton, timestamp)
	return retVal
}

Entity.prototype.onMouseMove = function(ray,timestamp) {
	var retVal = new MouseEventResult("__skip_ptr__")
	retVal.__ptr = Polycode.Entity_onMouseMove(this.__ptr, ray, timestamp)
	return retVal
}

Entity.prototype.onMouseWheelUp = function(ray,timestamp) {
	var retVal = new MouseEventResult("__skip_ptr__")
	retVal.__ptr = Polycode.Entity_onMouseWheelUp(this.__ptr, ray, timestamp)
	return retVal
}

Entity.prototype.onMouseWheelDown = function(ray,timestamp) {
	var retVal = new MouseEventResult("__skip_ptr__")
	retVal.__ptr = Polycode.Entity_onMouseWheelDown(this.__ptr, ray, timestamp)
	return retVal
}

Entity.prototype.setDepthOnly = function(val) {
	Polycode.Entity_setDepthOnly(this.__ptr, val)
}

Entity.prototype.getDepthOnly = function() {
	return Polycode.Entity_getDepthOnly(this.__ptr)
}

Entity.prototype.setBlendingMode = function(newBlendingMode) {
	Polycode.Entity_setBlendingMode(this.__ptr, newBlendingMode)
}

Entity.prototype.getBlendingMode = function() {
	return Polycode.Entity_getBlendingMode(this.__ptr)
}

Entity.prototype.getEntityProp = function(propName) {
	return Polycode.Entity_getEntityProp(this.__ptr, propName)
}

Entity.prototype.setEntityProp = function(propName,propValue) {
	Polycode.Entity_setEntityProp(this.__ptr, propName, propValue)
}

Entity.prototype.setInverseY = function(val) {
	Polycode.Entity_setInverseY(this.__ptr, val)
}

Entity.prototype.getInverseY = function() {
	return Polycode.Entity_getInverseY(this.__ptr)
}

Entity.prototype.doUpdates = function() {
	Polycode.Entity_doUpdates(this.__ptr)
}

Entity.prototype.doFixedUpdates = function() {
	Polycode.Entity_doFixedUpdates(this.__ptr)
}

Entity.prototype.buildPositionMatrix = function() {
	var retVal = new Matrix4("__skip_ptr__")
	retVal.__ptr = Polycode.Entity_buildPositionMatrix(this.__ptr)
	return retVal
}

Entity.prototype.customHitDetection = function(ray) {
	return Polycode.Entity_customHitDetection(this.__ptr, ray)
}

Entity.prototype.getNumTags = function() {
	return Polycode.Entity_getNumTags(this.__ptr)
}

Entity.prototype.getTagAtIndex = function(index) {
	return Polycode.Entity_getTagAtIndex(this.__ptr, index)
}

Entity.prototype.hasTag = function(tag) {
	return Polycode.Entity_hasTag(this.__ptr, tag)
}

Entity.prototype.clearTags = function() {
	Polycode.Entity_clearTags(this.__ptr)
}

Entity.prototype.addTag = function(tag) {
	Polycode.Entity_addTag(this.__ptr, tag)
}

Entity.prototype.getScreenPosition = function(projectionMatrix,cameraMatrix,viewport) {
	var retVal = new Vector2("__skip_ptr__")
	retVal.__ptr = Polycode.Entity_getScreenPosition(this.__ptr, projectionMatrix, cameraMatrix, viewport)
	return retVal
}

Entity.prototype.recalculateAABBAllChildren = function() {
	Polycode.Entity_recalculateAABBAllChildren(this.__ptr)
}

Entity.prototype.recalculateAABB = function() {
	Polycode.Entity_recalculateAABB(this.__ptr)
}

Entity.prototype.getWorldAABB = function() {
	var retVal = new AABB("__skip_ptr__")
	retVal.__ptr = Polycode.Entity_getWorldAABB(this.__ptr)
	return retVal
}

Entity.prototype.getLocalBoundingBox = function() {
	var retVal = new Vector3("__skip_ptr__")
	retVal.__ptr = Polycode.Entity_getLocalBoundingBox(this.__ptr)
	return retVal
}

Entity.prototype.setLocalBoundingBox = function(box) {
	Polycode.Entity_setLocalBoundingBox(this.__ptr, box)
}

Entity.prototype.setLocalBoundingBoxX = function(x) {
	Polycode.Entity_setLocalBoundingBoxX(this.__ptr, x)
}

Entity.prototype.setLocalBoundingBoxY = function(y) {
	Polycode.Entity_setLocalBoundingBoxY(this.__ptr, y)
}

Entity.prototype.setLocalBoundingBoxZ = function(z) {
	Polycode.Entity_setLocalBoundingBoxZ(this.__ptr, z)
}

Entity.prototype.attachScript = function(script) {
	Polycode.Entity_attachScript(this.__ptr, script)
}

Entity.prototype.getNumScripts = function() {
	return Polycode.Entity_getNumScripts(this.__ptr)
}
