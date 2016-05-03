require "Polycode/EventDispatcher"

class "Entity" (EventDispatcher)



function Entity:__getvar(name)
	if name == "ownsChildren" then
		return Polycore.Entity_get_ownsChildren(self.__ptr)
	elseif name == "billboardMode" then
		return Polycore.Entity_get_billboardMode(self.__ptr)
	elseif name == "color" then
		local retVal = Polycore.Entity_get_color(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Color"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "enabled" then
		return Polycore.Entity_get_enabled(self.__ptr)
	elseif name == "visible" then
		return Polycore.Entity_get_visible(self.__ptr)
	elseif name == "depthWrite" then
		return Polycore.Entity_get_depthWrite(self.__ptr)
	elseif name == "depthTest" then
		return Polycore.Entity_get_depthTest(self.__ptr)
	elseif name == "colorAffectsChildren" then
		return Polycore.Entity_get_colorAffectsChildren(self.__ptr)
	elseif name == "visibilityAffectsChildren" then
		return Polycore.Entity_get_visibilityAffectsChildren(self.__ptr)
	elseif name == "ignoreParentMatrix" then
		return Polycore.Entity_get_ignoreParentMatrix(self.__ptr)
	elseif name == "enableScissor" then
		return Polycore.Entity_get_enableScissor(self.__ptr)
	elseif name == "scissorBox" then
		local retVal = Polycore.Entity_get_scissorBox(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Rectangle"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "editorOnly" then
		return Polycore.Entity_get_editorOnly(self.__ptr)
	elseif name == "id" then
		return Polycore.Entity_get_id(self.__ptr)
	elseif name == "collisionShapeType" then
		local retVal = Polycore.Entity_get_collisionShapeType(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["char"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "processInputEvents" then
		return Polycore.Entity_get_processInputEvents(self.__ptr)
	elseif name == "blockMouseInput" then
		return Polycore.Entity_get_blockMouseInput(self.__ptr)
	elseif name == "snapToPixels" then
		return Polycore.Entity_get_snapToPixels(self.__ptr)
	elseif name == "mouseOver" then
		return Polycore.Entity_get_mouseOver(self.__ptr)
	elseif name == "rendererVis" then
		return Polycore.Entity_get_rendererVis(self.__ptr)
	elseif name == "layerID" then
		local retVal = Polycore.Entity_get_layerID(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["char"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
	if EventDispatcher["__getvar"] ~= nil then
		return EventDispatcher.__getvar(self, name)
	end
end


function Entity:__setvar(name,value)
	if name == "ownsChildren" then
		Polycore.Entity_set_ownsChildren(self.__ptr, value)
		return true
	elseif name == "billboardMode" then
		Polycore.Entity_set_billboardMode(self.__ptr, value)
		return true
	elseif name == "color" then
		Polycore.Entity_set_color(self.__ptr, value.__ptr)
		return true
	elseif name == "enabled" then
		Polycore.Entity_set_enabled(self.__ptr, value)
		return true
	elseif name == "visible" then
		Polycore.Entity_set_visible(self.__ptr, value)
		return true
	elseif name == "depthWrite" then
		Polycore.Entity_set_depthWrite(self.__ptr, value)
		return true
	elseif name == "depthTest" then
		Polycore.Entity_set_depthTest(self.__ptr, value)
		return true
	elseif name == "colorAffectsChildren" then
		Polycore.Entity_set_colorAffectsChildren(self.__ptr, value)
		return true
	elseif name == "visibilityAffectsChildren" then
		Polycore.Entity_set_visibilityAffectsChildren(self.__ptr, value)
		return true
	elseif name == "ignoreParentMatrix" then
		Polycore.Entity_set_ignoreParentMatrix(self.__ptr, value)
		return true
	elseif name == "enableScissor" then
		Polycore.Entity_set_enableScissor(self.__ptr, value)
		return true
	elseif name == "scissorBox" then
		Polycore.Entity_set_scissorBox(self.__ptr, value.__ptr)
		return true
	elseif name == "editorOnly" then
		Polycore.Entity_set_editorOnly(self.__ptr, value)
		return true
	elseif name == "id" then
		Polycore.Entity_set_id(self.__ptr, value)
		return true
	elseif name == "collisionShapeType" then
		Polycore.Entity_set_collisionShapeType(self.__ptr, value.__ptr)
		return true
	elseif name == "processInputEvents" then
		Polycore.Entity_set_processInputEvents(self.__ptr, value)
		return true
	elseif name == "blockMouseInput" then
		Polycore.Entity_set_blockMouseInput(self.__ptr, value)
		return true
	elseif name == "snapToPixels" then
		Polycore.Entity_set_snapToPixels(self.__ptr, value)
		return true
	elseif name == "mouseOver" then
		Polycore.Entity_set_mouseOver(self.__ptr, value)
		return true
	elseif name == "rendererVis" then
		Polycore.Entity_set_rendererVis(self.__ptr, value)
		return true
	elseif name == "layerID" then
		Polycore.Entity_set_layerID(self.__ptr, value.__ptr)
		return true
	end
	if EventDispatcher["__setvar"] ~= nil then
		return EventDispatcher.__setvar(self, name, value)
	else
		return false
	end
end


function Entity:Entity(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "EventDispatcher" then
			self.__ptr = arg[1].__ptr
			return
		end
	end
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.Entity(unpack(arg))
	end
end

function Entity:initEntity()
	local retVal =  Polycore.Entity_initEntity(self.__ptr)
end

function Entity:Render(buffer)
	local retVal = Polycore.Entity_Render(self.__ptr, buffer.__ptr)
end

function Entity:Update()
	local retVal =  Polycore.Entity_Update(self.__ptr)
end

function Entity:fixedUpdate()
	local retVal =  Polycore.Entity_fixedUpdate(self.__ptr)
end

function Entity:transformAndRender(drawBuffer, parentScissorBox)
	local retVal = Polycore.Entity_transformAndRender(self.__ptr, drawBuffer.__ptr, parentScissorBox.__ptr)
end

function Entity:renderChildren(buffer, parentScissorBox)
	local retVal = Polycore.Entity_renderChildren(self.__ptr, buffer.__ptr, parentScissorBox.__ptr)
end

function Entity:Clone(deepClone, ignoreEditorOnly)
	local retVal = Polycore.Entity_Clone(self.__ptr, deepClone, ignoreEditorOnly)
	if retVal == nil then return nil end
	local __c = _G["Entity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:applyClone(clone, deepClone, ignoreEditorOnly)
	local retVal = Polycore.Entity_applyClone(self.__ptr, clone.__ptr, deepClone, ignoreEditorOnly)
end

function Entity:dirtyMatrix(val)
	local retVal = Polycore.Entity_dirtyMatrix(self.__ptr, val)
end

function Entity:rebuildTransformMatrix()
	local retVal =  Polycore.Entity_rebuildTransformMatrix(self.__ptr)
end

function Entity:updateEntityMatrix()
	local retVal =  Polycore.Entity_updateEntityMatrix(self.__ptr)
end

function Entity:getTransformMatrix()
	local retVal =  Polycore.Entity_getTransformMatrix(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:getConcatenatedMatrix()
	local retVal =  Polycore.Entity_getConcatenatedMatrix(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:getConcatenatedMatrixRelativeTo(relativeEntity)
	local retVal = Polycore.Entity_getConcatenatedMatrixRelativeTo(self.__ptr, relativeEntity.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:getAnchorAdjustedMatrix()
	local retVal =  Polycore.Entity_getAnchorAdjustedMatrix(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:getConcatenatedRollMatrix()
	local retVal =  Polycore.Entity_getConcatenatedRollMatrix(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:setTransformByMatrixPure(matrix)
	local retVal = Polycore.Entity_setTransformByMatrixPure(self.__ptr, matrix.__ptr)
end

function Entity:getLookAtMatrix(loc, upVector)
	local retVal = Polycore.Entity_getLookAtMatrix(self.__ptr, loc.__ptr, upVector.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:addChild(newChild)
	local retVal = Polycore.Entity_addChild(self.__ptr, newChild.__ptr)
end

function Entity:removeChild(entityToRemove)
	local retVal = Polycore.Entity_removeChild(self.__ptr, entityToRemove.__ptr)
end

function Entity:moveChildUp(child)
	local retVal = Polycore.Entity_moveChildUp(self.__ptr, child.__ptr)
end

function Entity:moveChildDown(child)
	local retVal = Polycore.Entity_moveChildDown(self.__ptr, child.__ptr)
end

function Entity:moveChildTop(child)
	local retVal = Polycore.Entity_moveChildTop(self.__ptr, child.__ptr)
end

function Entity:moveChildBottom(child)
	local retVal = Polycore.Entity_moveChildBottom(self.__ptr, child.__ptr)
end

function Entity:setParentEntity(entity)
	local retVal = Polycore.Entity_setParentEntity(self.__ptr, entity.__ptr)
end

function Entity:getParentEntity()
	local retVal =  Polycore.Entity_getParentEntity(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Entity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:getNumChildren()
	local retVal =  Polycore.Entity_getNumChildren(self.__ptr)
	return retVal
end

function Entity:getChildAtIndex(index)
	local retVal = Polycore.Entity_getChildAtIndex(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["Entity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:setOwnsChildrenRecursive(val)
	local retVal = Polycore.Entity_setOwnsChildrenRecursive(self.__ptr, val)
end

function Entity:getPosition()
	local retVal =  Polycore.Entity_getPosition(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:getPosition2D()
	local retVal =  Polycore.Entity_getPosition2D(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector2"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:getCombinedPosition()
	local retVal =  Polycore.Entity_getCombinedPosition(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:setPosition(x, y, z)
	local retVal = Polycore.Entity_setPosition(self.__ptr, x, y, z)
end

function Entity:setPositionX(x)
	local retVal = Polycore.Entity_setPositionX(self.__ptr, x)
end

function Entity:setPositionY(y)
	local retVal = Polycore.Entity_setPositionY(self.__ptr, y)
end

function Entity:Translate(x, y, z)
	local retVal = Polycore.Entity_Translate(self.__ptr, x, y, z)
end

function Entity:setPositionZ(z)
	local retVal = Polycore.Entity_setPositionZ(self.__ptr, z)
end

function Entity:setScaleX(x)
	local retVal = Polycore.Entity_setScaleX(self.__ptr, x)
end

function Entity:setScaleY(y)
	local retVal = Polycore.Entity_setScaleY(self.__ptr, y)
end

function Entity:setScaleZ(z)
	local retVal = Polycore.Entity_setScaleZ(self.__ptr, z)
end

function Entity:Scale(x, y, z)
	local retVal = Polycore.Entity_Scale(self.__ptr, x, y, z)
end

function Entity:setScale(x, y, z)
	local retVal = Polycore.Entity_setScale(self.__ptr, x, y, z)
end

function Entity:getCompoundScale()
	local retVal =  Polycore.Entity_getCompoundScale(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:getScale()
	local retVal =  Polycore.Entity_getScale(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:getRotationEuler()
	local retVal =  Polycore.Entity_getRotationEuler(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:getCombinedPitch()
	local retVal =  Polycore.Entity_getCombinedPitch(self.__ptr)
	return retVal
end

function Entity:getCombinedYaw()
	local retVal =  Polycore.Entity_getCombinedYaw(self.__ptr)
	return retVal
end

function Entity:getCombinedRoll()
	local retVal =  Polycore.Entity_getCombinedRoll(self.__ptr)
	return retVal
end

function Entity:rebuildRotation()
	local retVal =  Polycore.Entity_rebuildRotation(self.__ptr)
end

function Entity:setRotationEuler(rotation)
	local retVal = Polycore.Entity_setRotationEuler(self.__ptr, rotation.__ptr)
end

function Entity:setPitch(pitch)
	local retVal = Polycore.Entity_setPitch(self.__ptr, pitch)
end

function Entity:setYaw(yaw)
	local retVal = Polycore.Entity_setYaw(self.__ptr, yaw)
end

function Entity:setRoll(roll)
	local retVal = Polycore.Entity_setRoll(self.__ptr, roll)
end

function Entity:Roll(roll)
	local retVal = Polycore.Entity_Roll(self.__ptr, roll)
end

function Entity:Yaw(yaw)
	local retVal = Polycore.Entity_Yaw(self.__ptr, yaw)
end

function Entity:Pitch(pitch)
	local retVal = Polycore.Entity_Pitch(self.__ptr, pitch)
end

function Entity:getPitch()
	local retVal =  Polycore.Entity_getPitch(self.__ptr)
	return retVal
end

function Entity:getYaw()
	local retVal =  Polycore.Entity_getYaw(self.__ptr)
	return retVal
end

function Entity:getRoll()
	local retVal =  Polycore.Entity_getRoll(self.__ptr)
	return retVal
end

function Entity:getWidth()
	local retVal =  Polycore.Entity_getWidth(self.__ptr)
	return retVal
end

function Entity:getHeight()
	local retVal =  Polycore.Entity_getHeight(self.__ptr)
	return retVal
end

function Entity:getDepth()
	local retVal =  Polycore.Entity_getDepth(self.__ptr)
	return retVal
end

function Entity:setWidth(width)
	local retVal = Polycore.Entity_setWidth(self.__ptr, width)
end

function Entity:setHeight(height)
	local retVal = Polycore.Entity_setHeight(self.__ptr, height)
end

function Entity:setDepth(depth)
	local retVal = Polycore.Entity_setDepth(self.__ptr, depth)
end

function Entity:setRotationQuat(w, x, y, z)
	local retVal = Polycore.Entity_setRotationQuat(self.__ptr, w, x, y, z)
end

function Entity:setRotationByQuaternion(quaternion)
	local retVal = Polycore.Entity_setRotationByQuaternion(self.__ptr, quaternion.__ptr)
end

function Entity:getRotationQuat()
	local retVal =  Polycore.Entity_getRotationQuat(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Quaternion"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:getConcatenatedQuat()
	local retVal =  Polycore.Entity_getConcatenatedQuat(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Quaternion"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:lookAt(loc, upVector)
	local retVal = Polycore.Entity_lookAt(self.__ptr, loc.__ptr, upVector.__ptr)
end

function Entity:lookAtEntity(entity, upVector)
	local retVal = Polycore.Entity_lookAtEntity(self.__ptr, entity.__ptr, upVector.__ptr)
end

function Entity:getCombinedColor()
	local retVal =  Polycore.Entity_getCombinedColor(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Color"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:setColor(r, g, b, a)
	local retVal = Polycore.Entity_setColor(self.__ptr, r, g, b, a)
end

function Entity:setColorInt(r, g, b, a)
	local retVal = Polycore.Entity_setColorInt(self.__ptr, r, g, b, a)
end

function Entity:setAnchorPoint(anchorPoint)
	local retVal = Polycore.Entity_setAnchorPoint(self.__ptr, anchorPoint.__ptr)
end

function Entity:getAnchorPoint()
	local retVal =  Polycore.Entity_getAnchorPoint(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:onMouseDown(ray, mouseButton, timestamp)
	local retVal = Polycore.Entity_onMouseDown(self.__ptr, ray.__ptr, mouseButton, timestamp)
	if retVal == nil then return nil end
	local __c = _G["MouseEventResult"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:onMouseUp(ray, mouseButton, timestamp)
	local retVal = Polycore.Entity_onMouseUp(self.__ptr, ray.__ptr, mouseButton, timestamp)
	if retVal == nil then return nil end
	local __c = _G["MouseEventResult"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:onMouseMove(ray, timestamp)
	local retVal = Polycore.Entity_onMouseMove(self.__ptr, ray.__ptr, timestamp)
	if retVal == nil then return nil end
	local __c = _G["MouseEventResult"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:onMouseWheelUp(ray, timestamp)
	local retVal = Polycore.Entity_onMouseWheelUp(self.__ptr, ray.__ptr, timestamp)
	if retVal == nil then return nil end
	local __c = _G["MouseEventResult"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:onMouseWheelDown(ray, timestamp)
	local retVal = Polycore.Entity_onMouseWheelDown(self.__ptr, ray.__ptr, timestamp)
	if retVal == nil then return nil end
	local __c = _G["MouseEventResult"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:setDepthOnly(val)
	local retVal = Polycore.Entity_setDepthOnly(self.__ptr, val)
end

function Entity:getDepthOnly()
	local retVal =  Polycore.Entity_getDepthOnly(self.__ptr)
	return retVal
end

function Entity:setUserData(userData)
	local retVal = Polycore.Entity_setUserData(self.__ptr, userData.__ptr)
end

function Entity:getUserData()
	local retVal =  Polycore.Entity_getUserData(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["void"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:setBlendingMode(newBl_endingMode)
	local retVal = Polycore.Entity_setBlendingMode(self.__ptr, newBl_endingMode)
end

function Entity:getBlendingMode()
	local retVal =  Polycore.Entity_getBlendingMode(self.__ptr)
	return retVal
end

function Entity:getEntityById(id, recursive)
	local retVal = Polycore.Entity_getEntityById(self.__ptr, id, recursive)
	if retVal == nil then return nil end
	local __c = _G["Entity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:getEntitiesByTag(tag, recursive)
	local retVal = Polycore.Entity_getEntitiesByTag(self.__ptr, tag, recursive)
	if retVal == nil then return nil end
	for i=1,count(retVal) do
		local __c  = _G["Entity"]("__skip_ptr__")
		__c.__ptr = retVal[i]
		retVal[i] = __c
	end
	return retVal
end

function Entity:getEntitiesByLayerID(layerID, recursive)
	local retVal = Polycore.Entity_getEntitiesByLayerID(self.__ptr, layerID.__ptr, recursive)
	if retVal == nil then return nil end
	for i=1,count(retVal) do
		local __c  = _G["Entity"]("__skip_ptr__")
		__c.__ptr = retVal[i]
		retVal[i] = __c
	end
	return retVal
end

function Entity:getEntityProp(propName)
	local retVal = Polycore.Entity_getEntityProp(self.__ptr, propName)
	return retVal
end

function Entity:setEntityProp(propName, propValue)
	local retVal = Polycore.Entity_setEntityProp(self.__ptr, propName, propValue)
end

function Entity:setInverseY(val)
	local retVal = Polycore.Entity_setInverseY(self.__ptr, val)
end

function Entity:getInverseY()
	local retVal =  Polycore.Entity_getInverseY(self.__ptr)
	return retVal
end

function Entity:doUpdates()
	local retVal =  Polycore.Entity_doUpdates(self.__ptr)
end

function Entity:doFixedUpdates()
	local retVal =  Polycore.Entity_doFixedUpdates(self.__ptr)
end

function Entity:buildPositionMatrix()
	local retVal =  Polycore.Entity_buildPositionMatrix(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:setRenderer(r_enderer)
	local retVal = Polycore.Entity_setRenderer(self.__ptr, r_enderer.__ptr)
end

function Entity:customHitDetection(ray)
	local retVal = Polycore.Entity_customHitDetection(self.__ptr, ray.__ptr)
	return retVal
end

function Entity:getNumTags()
	local retVal =  Polycore.Entity_getNumTags(self.__ptr)
	return retVal
end

function Entity:getTagAtIndex(index)
	local retVal = Polycore.Entity_getTagAtIndex(self.__ptr, index)
	return retVal
end

function Entity:hasTag(tag)
	local retVal = Polycore.Entity_hasTag(self.__ptr, tag)
	return retVal
end

function Entity:clearTags()
	local retVal =  Polycore.Entity_clearTags(self.__ptr)
end

function Entity:addTag(tag)
	local retVal = Polycore.Entity_addTag(self.__ptr, tag)
end

function Entity:getScreenPosition(projectionMatrix, cameraMatrix, viewport)
	local retVal = Polycore.Entity_getScreenPosition(self.__ptr, projectionMatrix.__ptr, cameraMatrix.__ptr, viewport.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector2"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:recalculateAABBAllChildren()
	local retVal =  Polycore.Entity_recalculateAABBAllChildren(self.__ptr)
end

function Entity:recalculateAABB()
	local retVal =  Polycore.Entity_recalculateAABB(self.__ptr)
end

function Entity:getWorldAABB()
	local retVal =  Polycore.Entity_getWorldAABB(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["AABB"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:getLocalBoundingBox()
	local retVal =  Polycore.Entity_getLocalBoundingBox(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:setLocalBoundingBox(box)
	local retVal = Polycore.Entity_setLocalBoundingBox(self.__ptr, box.__ptr)
end

function Entity:setLocalBoundingBoxX(x)
	local retVal = Polycore.Entity_setLocalBoundingBoxX(self.__ptr, x)
end

function Entity:setLocalBoundingBoxY(y)
	local retVal = Polycore.Entity_setLocalBoundingBoxY(self.__ptr, y)
end

function Entity:setLocalBoundingBoxZ(z)
	local retVal = Polycore.Entity_setLocalBoundingBoxZ(self.__ptr, z)
end

function Entity:setContainerScene(scene)
	local retVal = Polycore.Entity_setContainerScene(self.__ptr, scene.__ptr)
end

function Entity:getContainerScene()
	local retVal =  Polycore.Entity_getContainerScene(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Scene"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:attachScript(script)
	local retVal = Polycore.Entity_attachScript(self.__ptr, script.__ptr)
end

function Entity:detachScript(script)
	local retVal = Polycore.Entity_detachScript(self.__ptr, script.__ptr)
end

function Entity:getNumScripts()
	local retVal =  Polycore.Entity_getNumScripts(self.__ptr)
	return retVal
end

function Entity:getScriptAtIndex(index)
	local retVal = Polycore.Entity_getScriptAtIndex(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["ScriptInstance"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:__delete()
	if self then Polycore.delete_Entity(self.__ptr) end
end
