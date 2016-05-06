function Entity() {
}

Entity.prototype.initEntity = function() {
	Polycode.Entity_initEntity(this.__ptr)
}

Entity.prototype.Render = function(buffer) {
	Polycode.Entity_Render(this.__ptr, buffer)
}

Entity.prototype.Update = function() {
	Polycode.Entity_Update(this.__ptr)
}

Entity.prototype.fixedUpdate = function() {
	Polycode.Entity_fixedUpdate(this.__ptr)
}

Entity.prototype.transformAndRender = function(drawBuffer,parentScissorBox) {
	Polycode.Entity_transformAndRender(this.__ptr, drawBuffer,parentScissorBox)
}

Entity.prototype.renderChildren = function(buffer,parentScissorBox) {
	Polycode.Entity_renderChildren(this.__ptr, buffer,parentScissorBox)
}

Entity.prototype.Clone = function(deepClone,ignoreEditorOnly) {
	Polycode.Entity_Clone(this.__ptr, deepClone,ignoreEditorOnly)
}

Entity.prototype.applyClone = function(clone,deepClone,ignoreEditorOnly) {
	Polycode.Entity_applyClone(this.__ptr, clone,deepClone,ignoreEditorOnly)
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
	Polycode.Entity_getTransformMatrix(this.__ptr)
}

Entity.prototype.getConcatenatedMatrix = function() {
	Polycode.Entity_getConcatenatedMatrix(this.__ptr)
}

Entity.prototype.getConcatenatedMatrixRelativeTo = function(relativeEntity) {
	Polycode.Entity_getConcatenatedMatrixRelativeTo(this.__ptr, relativeEntity)
}

Entity.prototype.getAnchorAdjustedMatrix = function() {
	Polycode.Entity_getAnchorAdjustedMatrix(this.__ptr)
}

Entity.prototype.getConcatenatedRollMatrix = function() {
	Polycode.Entity_getConcatenatedRollMatrix(this.__ptr)
}

Entity.prototype.setTransformByMatrixPure = function(matrix) {
	Polycode.Entity_setTransformByMatrixPure(this.__ptr, matrix)
}

Entity.prototype.getLookAtMatrix = function(loc,upVector) {
	Polycode.Entity_getLookAtMatrix(this.__ptr, loc,upVector)
}

Entity.prototype.addChild = function(newChild) {
	Polycode.Entity_addChild(this.__ptr, newChild)
}

Entity.prototype.removeChild = function(entityToRemove) {
	Polycode.Entity_removeChild(this.__ptr, entityToRemove)
}

Entity.prototype.moveChildUp = function(child) {
	Polycode.Entity_moveChildUp(this.__ptr, child)
}

Entity.prototype.moveChildDown = function(child) {
	Polycode.Entity_moveChildDown(this.__ptr, child)
}

Entity.prototype.moveChildTop = function(child) {
	Polycode.Entity_moveChildTop(this.__ptr, child)
}

Entity.prototype.moveChildBottom = function(child) {
	Polycode.Entity_moveChildBottom(this.__ptr, child)
}

Entity.prototype.setParentEntity = function(entity) {
	Polycode.Entity_setParentEntity(this.__ptr, entity)
}

Entity.prototype.getParentEntity = function() {
	Polycode.Entity_getParentEntity(this.__ptr)
}

Entity.prototype.getNumChildren = function() {
	Polycode.Entity_getNumChildren(this.__ptr)
}

Entity.prototype.getChildAtIndex = function(index) {
	Polycode.Entity_getChildAtIndex(this.__ptr, index)
}

Entity.prototype.setOwnsChildrenRecursive = function(val) {
	Polycode.Entity_setOwnsChildrenRecursive(this.__ptr, val)
}

Entity.prototype.getPosition = function() {
	Polycode.Entity_getPosition(this.__ptr)
}

Entity.prototype.getPosition2D = function() {
	Polycode.Entity_getPosition2D(this.__ptr)
}

Entity.prototype.getCombinedPosition = function() {
	Polycode.Entity_getCombinedPosition(this.__ptr)
}

Entity.prototype.setPosition = function(x,y,z) {
	Polycode.Entity_setPosition(this.__ptr, x,y,z)
}

Entity.prototype.setPositionX = function(x) {
	Polycode.Entity_setPositionX(this.__ptr, x)
}

Entity.prototype.setPositionY = function(y) {
	Polycode.Entity_setPositionY(this.__ptr, y)
}

Entity.prototype.Translate = function(x,y,z) {
	Polycode.Entity_Translate(this.__ptr, x,y,z)
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
	Polycode.Entity_Scale(this.__ptr, x,y,z)
}

Entity.prototype.setScale = function(x,y,z) {
	Polycode.Entity_setScale(this.__ptr, x,y,z)
}

Entity.prototype.getCompoundScale = function() {
	Polycode.Entity_getCompoundScale(this.__ptr)
}

Entity.prototype.getScale = function() {
	Polycode.Entity_getScale(this.__ptr)
}

Entity.prototype.getRotationEuler = function() {
	Polycode.Entity_getRotationEuler(this.__ptr)
}

Entity.prototype.getCombinedPitch = function() {
	Polycode.Entity_getCombinedPitch(this.__ptr)
}

Entity.prototype.getCombinedYaw = function() {
	Polycode.Entity_getCombinedYaw(this.__ptr)
}

Entity.prototype.getCombinedRoll = function() {
	Polycode.Entity_getCombinedRoll(this.__ptr)
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
	Polycode.Entity_getPitch(this.__ptr)
}

Entity.prototype.getYaw = function() {
	Polycode.Entity_getYaw(this.__ptr)
}

Entity.prototype.getRoll = function() {
	Polycode.Entity_getRoll(this.__ptr)
}

Entity.prototype.getWidth = function() {
	Polycode.Entity_getWidth(this.__ptr)
}

Entity.prototype.getHeight = function() {
	Polycode.Entity_getHeight(this.__ptr)
}

Entity.prototype.getDepth = function() {
	Polycode.Entity_getDepth(this.__ptr)
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
	Polycode.Entity_setRotationQuat(this.__ptr, w,x,y,z)
}

Entity.prototype.setRotationByQuaternion = function(quaternion) {
	Polycode.Entity_setRotationByQuaternion(this.__ptr, quaternion)
}

Entity.prototype.getRotationQuat = function() {
	Polycode.Entity_getRotationQuat(this.__ptr)
}

Entity.prototype.getConcatenatedQuat = function() {
	Polycode.Entity_getConcatenatedQuat(this.__ptr)
}

Entity.prototype.lookAt = function(loc,upVector) {
	Polycode.Entity_lookAt(this.__ptr, loc,upVector)
}

Entity.prototype.lookAtEntity = function(entity,upVector) {
	Polycode.Entity_lookAtEntity(this.__ptr, entity,upVector)
}

Entity.prototype.getCombinedColor = function() {
	Polycode.Entity_getCombinedColor(this.__ptr)
}

Entity.prototype.setColor = function(r,g,b,a) {
	Polycode.Entity_setColor(this.__ptr, r,g,b,a)
}

Entity.prototype.setColorInt = function(r,g,b,a) {
	Polycode.Entity_setColorInt(this.__ptr, r,g,b,a)
}

Entity.prototype.setAnchorPoint = function(anchorPoint) {
	Polycode.Entity_setAnchorPoint(this.__ptr, anchorPoint)
}

Entity.prototype.getAnchorPoint = function() {
	Polycode.Entity_getAnchorPoint(this.__ptr)
}

Entity.prototype.onMouseDown = function(ray,mouseButton,timestamp) {
	Polycode.Entity_onMouseDown(this.__ptr, ray,mouseButton,timestamp)
}

Entity.prototype.onMouseUp = function(ray,mouseButton,timestamp) {
	Polycode.Entity_onMouseUp(this.__ptr, ray,mouseButton,timestamp)
}

Entity.prototype.onMouseMove = function(ray,timestamp) {
	Polycode.Entity_onMouseMove(this.__ptr, ray,timestamp)
}

Entity.prototype.onMouseWheelUp = function(ray,timestamp) {
	Polycode.Entity_onMouseWheelUp(this.__ptr, ray,timestamp)
}

Entity.prototype.onMouseWheelDown = function(ray,timestamp) {
	Polycode.Entity_onMouseWheelDown(this.__ptr, ray,timestamp)
}

Entity.prototype.setDepthOnly = function(val) {
	Polycode.Entity_setDepthOnly(this.__ptr, val)
}

Entity.prototype.getDepthOnly = function() {
	Polycode.Entity_getDepthOnly(this.__ptr)
}

Entity.prototype.setUserData = function(userData) {
	Polycode.Entity_setUserData(this.__ptr, userData)
}

Entity.prototype.getUserData = function() {
	Polycode.Entity_getUserData(this.__ptr)
}

Entity.prototype.setBlendingMode = function(newBlendingMode) {
	Polycode.Entity_setBlendingMode(this.__ptr, newBlendingMode)
}

Entity.prototype.getBlendingMode = function() {
	Polycode.Entity_getBlendingMode(this.__ptr)
}

Entity.prototype.getEntityById = function(id,recursive) {
	Polycode.Entity_getEntityById(this.__ptr, id,recursive)
}

Entity.prototype.getEntitiesByTag = function(tag,recursive) {
	Polycode.Entity_getEntitiesByTag(this.__ptr, tag,recursive)
}

Entity.prototype.getEntitiesByLayerID = function(layerID,recursive) {
	Polycode.Entity_getEntitiesByLayerID(this.__ptr, layerID,recursive)
}

Entity.prototype.getEntityProp = function(propName) {
	Polycode.Entity_getEntityProp(this.__ptr, propName)
}

Entity.prototype.setEntityProp = function(propName,propValue) {
	Polycode.Entity_setEntityProp(this.__ptr, propName,propValue)
}

Entity.prototype.setInverseY = function(val) {
	Polycode.Entity_setInverseY(this.__ptr, val)
}

Entity.prototype.getInverseY = function() {
	Polycode.Entity_getInverseY(this.__ptr)
}

Entity.prototype.doUpdates = function() {
	Polycode.Entity_doUpdates(this.__ptr)
}

Entity.prototype.doFixedUpdates = function() {
	Polycode.Entity_doFixedUpdates(this.__ptr)
}

Entity.prototype.buildPositionMatrix = function() {
	Polycode.Entity_buildPositionMatrix(this.__ptr)
}

Entity.prototype.setRenderer = function(renderer) {
	Polycode.Entity_setRenderer(this.__ptr, renderer)
}

Entity.prototype.customHitDetection = function(ray) {
	Polycode.Entity_customHitDetection(this.__ptr, ray)
}

Entity.prototype.getNumTags = function() {
	Polycode.Entity_getNumTags(this.__ptr)
}

Entity.prototype.getTagAtIndex = function(index) {
	Polycode.Entity_getTagAtIndex(this.__ptr, index)
}

Entity.prototype.hasTag = function(tag) {
	Polycode.Entity_hasTag(this.__ptr, tag)
}

Entity.prototype.clearTags = function() {
	Polycode.Entity_clearTags(this.__ptr)
}

Entity.prototype.addTag = function(tag) {
	Polycode.Entity_addTag(this.__ptr, tag)
}

Entity.prototype.getScreenPosition = function(projectionMatrix,cameraMatrix,viewport) {
	Polycode.Entity_getScreenPosition(this.__ptr, projectionMatrix,cameraMatrix,viewport)
}

Entity.prototype.recalculateAABBAllChildren = function() {
	Polycode.Entity_recalculateAABBAllChildren(this.__ptr)
}

Entity.prototype.recalculateAABB = function() {
	Polycode.Entity_recalculateAABB(this.__ptr)
}

Entity.prototype.getWorldAABB = function() {
	Polycode.Entity_getWorldAABB(this.__ptr)
}

Entity.prototype.getLocalBoundingBox = function() {
	Polycode.Entity_getLocalBoundingBox(this.__ptr)
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

Entity.prototype.setContainerScene = function(scene) {
	Polycode.Entity_setContainerScene(this.__ptr, scene)
}

Entity.prototype.getContainerScene = function() {
	Polycode.Entity_getContainerScene(this.__ptr)
}

Entity.prototype.attachScript = function(script) {
	Polycode.Entity_attachScript(this.__ptr, script)
}

Entity.prototype.detachScript = function(script) {
	Polycode.Entity_detachScript(this.__ptr, script)
}

Entity.prototype.getNumScripts = function() {
	Polycode.Entity_getNumScripts(this.__ptr)
}

Entity.prototype.getScriptAtIndex = function(index) {
	Polycode.Entity_getScriptAtIndex(this.__ptr, index)
}
