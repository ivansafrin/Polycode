require "Polycode/EventDispatcher"

class "Entity" (EventDispatcher)


function Entity:__getvar(name)
	if name == "ownsChildren" then
		return Polycode.Entity_get_ownsChildren(self.__ptr)
	elseif name == "billboardMode" then
		return Polycode.Entity_get_billboardMode(self.__ptr)
	elseif name == "color" then
		local retVal = Polycode.Entity_get_color(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Color"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "enabled" then
		return Polycode.Entity_get_enabled(self.__ptr)
	elseif name == "visible" then
		return Polycode.Entity_get_visible(self.__ptr)
	elseif name == "depthWrite" then
		return Polycode.Entity_get_depthWrite(self.__ptr)
	elseif name == "depthTest" then
		return Polycode.Entity_get_depthTest(self.__ptr)
	elseif name == "colorAffectsChildren" then
		return Polycode.Entity_get_colorAffectsChildren(self.__ptr)
	elseif name == "visibilityAffectsChildren" then
		return Polycode.Entity_get_visibilityAffectsChildren(self.__ptr)
	elseif name == "ignoreParentMatrix" then
		return Polycode.Entity_get_ignoreParentMatrix(self.__ptr)
	elseif name == "enableScissor" then
		return Polycode.Entity_get_enableScissor(self.__ptr)
	elseif name == "scissorBox" then
		local retVal = Polycode.Entity_get_scissorBox(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Rectangle"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "editorOnly" then
		return Polycode.Entity_get_editorOnly(self.__ptr)
	elseif name == "id" then
		return Polycode.Entity_get_id(self.__ptr)
	elseif name == "collisionShapeType" then
		local retVal = Polycode.Entity_get_collisionShapeType(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["char"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "processInputEvents" then
		return Polycode.Entity_get_processInputEvents(self.__ptr)
	elseif name == "blockMouseInput" then
		return Polycode.Entity_get_blockMouseInput(self.__ptr)
	elseif name == "snapToPixels" then
		return Polycode.Entity_get_snapToPixels(self.__ptr)
	elseif name == "mouseOver" then
		return Polycode.Entity_get_mouseOver(self.__ptr)
	elseif name == "rendererVis" then
		return Polycode.Entity_get_rendererVis(self.__ptr)
	elseif name == "layerID" then
		local retVal = Polycode.Entity_get_layerID(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["char"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "castShadows" then
		return Polycode.Entity_get_castShadows(self.__ptr)
	end
	if EventDispatcher["__getvar"] ~= nil then
		return EventDispatcher.__getvar(self, name)
	end
end

function Entity:__setvar(name,value)
	if name == "ownsChildren" then
		Polycode.Entity_set_ownsChildren(self.__ptr, value)
		return true
	elseif name == "billboardMode" then
		Polycode.Entity_set_billboardMode(self.__ptr, value)
		return true
	elseif name == "color" then
		Polycode.Entity_set_color(self.__ptr, value.__ptr)
		return true
	elseif name == "enabled" then
		Polycode.Entity_set_enabled(self.__ptr, value)
		return true
	elseif name == "visible" then
		Polycode.Entity_set_visible(self.__ptr, value)
		return true
	elseif name == "depthWrite" then
		Polycode.Entity_set_depthWrite(self.__ptr, value)
		return true
	elseif name == "depthTest" then
		Polycode.Entity_set_depthTest(self.__ptr, value)
		return true
	elseif name == "colorAffectsChildren" then
		Polycode.Entity_set_colorAffectsChildren(self.__ptr, value)
		return true
	elseif name == "visibilityAffectsChildren" then
		Polycode.Entity_set_visibilityAffectsChildren(self.__ptr, value)
		return true
	elseif name == "ignoreParentMatrix" then
		Polycode.Entity_set_ignoreParentMatrix(self.__ptr, value)
		return true
	elseif name == "enableScissor" then
		Polycode.Entity_set_enableScissor(self.__ptr, value)
		return true
	elseif name == "scissorBox" then
		Polycode.Entity_set_scissorBox(self.__ptr, value.__ptr)
		return true
	elseif name == "editorOnly" then
		Polycode.Entity_set_editorOnly(self.__ptr, value)
		return true
	elseif name == "id" then
		Polycode.Entity_set_id(self.__ptr, value)
		return true
	elseif name == "collisionShapeType" then
		Polycode.Entity_set_collisionShapeType(self.__ptr, value.__ptr)
		return true
	elseif name == "processInputEvents" then
		Polycode.Entity_set_processInputEvents(self.__ptr, value)
		return true
	elseif name == "blockMouseInput" then
		Polycode.Entity_set_blockMouseInput(self.__ptr, value)
		return true
	elseif name == "snapToPixels" then
		Polycode.Entity_set_snapToPixels(self.__ptr, value)
		return true
	elseif name == "mouseOver" then
		Polycode.Entity_set_mouseOver(self.__ptr, value)
		return true
	elseif name == "rendererVis" then
		Polycode.Entity_set_rendererVis(self.__ptr, value)
		return true
	elseif name == "layerID" then
		Polycode.Entity_set_layerID(self.__ptr, value.__ptr)
		return true
	elseif name == "castShadows" then
		Polycode.Entity_set_castShadows(self.__ptr, value)
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
		self.__ptr = Polycode.Entity(unpack(arg))
	end
end

function Entity:initEntity()
	local retVal =  Polycode.Entity_initEntity(self.__ptr)
end

function Entity:Update(elapsed)
	local retVal = Polycode.Entity_Update(self.__ptr, elapsed)
end

function Entity:fixedUpdate()
	local retVal =  Polycode.Entity_fixedUpdate(self.__ptr)
end

function Entity:dirtyMatrix(val)
	local retVal = Polycode.Entity_dirtyMatrix(self.__ptr, val)
end

function Entity:rebuildTransformMatrix()
	local retVal =  Polycode.Entity_rebuildTransformMatrix(self.__ptr)
end

function Entity:updateEntityMatrix()
	local retVal =  Polycode.Entity_updateEntityMatrix(self.__ptr)
end

function Entity:getTransformMatrix()
	local retVal =  Polycode.Entity_getTransformMatrix(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:getConcatenatedMatrix()
	local retVal =  Polycode.Entity_getConcatenatedMatrix(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:getAnchorAdjustedMatrix()
	local retVal =  Polycode.Entity_getAnchorAdjustedMatrix(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:getConcatenatedRollMatrix()
	local retVal =  Polycode.Entity_getConcatenatedRollMatrix(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:setTransformByMatrixPure(matrix)
	local retVal = Polycode.Entity_setTransformByMatrixPure(self.__ptr, matrix.__ptr)
end

function Entity:getLookAtMatrix(loc, upVector)
	local retVal = Polycode.Entity_getLookAtMatrix(self.__ptr, loc.__ptr, upVector.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:getNumChildren()
	local retVal =  Polycode.Entity_getNumChildren(self.__ptr)
	return retVal
end

function Entity:setOwnsChildrenRecursive(val)
	local retVal = Polycode.Entity_setOwnsChildrenRecursive(self.__ptr, val)
end

function Entity:getPosition()
	local retVal =  Polycode.Entity_getPosition(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:getPosition2D()
	local retVal =  Polycode.Entity_getPosition2D(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector2"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:getCombinedPosition()
	local retVal =  Polycode.Entity_getCombinedPosition(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:setPosition(x, y, z)
	local retVal = Polycode.Entity_setPosition(self.__ptr, x, y, z)
end

function Entity:setPositionX(x)
	local retVal = Polycode.Entity_setPositionX(self.__ptr, x)
end

function Entity:setPositionY(y)
	local retVal = Polycode.Entity_setPositionY(self.__ptr, y)
end

function Entity:Translate(x, y, z)
	local retVal = Polycode.Entity_Translate(self.__ptr, x, y, z)
end

function Entity:setPositionZ(z)
	local retVal = Polycode.Entity_setPositionZ(self.__ptr, z)
end

function Entity:setScaleX(x)
	local retVal = Polycode.Entity_setScaleX(self.__ptr, x)
end

function Entity:setScaleY(y)
	local retVal = Polycode.Entity_setScaleY(self.__ptr, y)
end

function Entity:setScaleZ(z)
	local retVal = Polycode.Entity_setScaleZ(self.__ptr, z)
end

function Entity:Scale(x, y, z)
	local retVal = Polycode.Entity_Scale(self.__ptr, x, y, z)
end

function Entity:setScale(x, y, z)
	local retVal = Polycode.Entity_setScale(self.__ptr, x, y, z)
end

function Entity:getCompoundScale()
	local retVal =  Polycode.Entity_getCompoundScale(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:getScale()
	local retVal =  Polycode.Entity_getScale(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:getRotationEuler()
	local retVal =  Polycode.Entity_getRotationEuler(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:getCombinedPitch()
	local retVal =  Polycode.Entity_getCombinedPitch(self.__ptr)
	return retVal
end

function Entity:getCombinedYaw()
	local retVal =  Polycode.Entity_getCombinedYaw(self.__ptr)
	return retVal
end

function Entity:getCombinedRoll()
	local retVal =  Polycode.Entity_getCombinedRoll(self.__ptr)
	return retVal
end

function Entity:rebuildRotation()
	local retVal =  Polycode.Entity_rebuildRotation(self.__ptr)
end

function Entity:setRotationEuler(rotation)
	local retVal = Polycode.Entity_setRotationEuler(self.__ptr, rotation.__ptr)
end

function Entity:setPitch(pitch)
	local retVal = Polycode.Entity_setPitch(self.__ptr, pitch)
end

function Entity:setYaw(yaw)
	local retVal = Polycode.Entity_setYaw(self.__ptr, yaw)
end

function Entity:setRoll(roll)
	local retVal = Polycode.Entity_setRoll(self.__ptr, roll)
end

function Entity:Roll(roll)
	local retVal = Polycode.Entity_Roll(self.__ptr, roll)
end

function Entity:Yaw(yaw)
	local retVal = Polycode.Entity_Yaw(self.__ptr, yaw)
end

function Entity:Pitch(pitch)
	local retVal = Polycode.Entity_Pitch(self.__ptr, pitch)
end

function Entity:getPitch()
	local retVal =  Polycode.Entity_getPitch(self.__ptr)
	return retVal
end

function Entity:getYaw()
	local retVal =  Polycode.Entity_getYaw(self.__ptr)
	return retVal
end

function Entity:getRoll()
	local retVal =  Polycode.Entity_getRoll(self.__ptr)
	return retVal
end

function Entity:getWidth()
	local retVal =  Polycode.Entity_getWidth(self.__ptr)
	return retVal
end

function Entity:getHeight()
	local retVal =  Polycode.Entity_getHeight(self.__ptr)
	return retVal
end

function Entity:getDepth()
	local retVal =  Polycode.Entity_getDepth(self.__ptr)
	return retVal
end

function Entity:setWidth(width)
	local retVal = Polycode.Entity_setWidth(self.__ptr, width)
end

function Entity:setHeight(height)
	local retVal = Polycode.Entity_setHeight(self.__ptr, height)
end

function Entity:setDepth(depth)
	local retVal = Polycode.Entity_setDepth(self.__ptr, depth)
end

function Entity:setRotationQuat(w, x, y, z)
	local retVal = Polycode.Entity_setRotationQuat(self.__ptr, w, x, y, z)
end

function Entity:setRotationByQuaternion(quaternion)
	local retVal = Polycode.Entity_setRotationByQuaternion(self.__ptr, quaternion.__ptr)
end

function Entity:getRotationQuat()
	local retVal =  Polycode.Entity_getRotationQuat(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Quaternion"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:getConcatenatedQuat()
	local retVal =  Polycode.Entity_getConcatenatedQuat(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Quaternion"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:lookAt(loc, upVector)
	local retVal = Polycode.Entity_lookAt(self.__ptr, loc.__ptr, upVector.__ptr)
end

function Entity:getCombinedColor()
	local retVal =  Polycode.Entity_getCombinedColor(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Color"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:setColor(r, g, b, a)
	local retVal = Polycode.Entity_setColor(self.__ptr, r, g, b, a)
end

function Entity:setColorInt(r, g, b, a)
	local retVal = Polycode.Entity_setColorInt(self.__ptr, r, g, b, a)
end

function Entity:setAnchorPoint(anchorPoint)
	local retVal = Polycode.Entity_setAnchorPoint(self.__ptr, anchorPoint.__ptr)
end

function Entity:getAnchorPoint()
	local retVal =  Polycode.Entity_getAnchorPoint(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:onMouseDown(ray, mouseButton, timestamp)
	local retVal = Polycode.Entity_onMouseDown(self.__ptr, ray.__ptr, mouseButton, timestamp)
	if retVal == nil then return nil end
	local __c = _G["MouseEventResult"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:onMouseUp(ray, mouseButton, timestamp)
	local retVal = Polycode.Entity_onMouseUp(self.__ptr, ray.__ptr, mouseButton, timestamp)
	if retVal == nil then return nil end
	local __c = _G["MouseEventResult"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:onMouseMove(ray, timestamp)
	local retVal = Polycode.Entity_onMouseMove(self.__ptr, ray.__ptr, timestamp)
	if retVal == nil then return nil end
	local __c = _G["MouseEventResult"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:onMouseWheelUp(ray, timestamp)
	local retVal = Polycode.Entity_onMouseWheelUp(self.__ptr, ray.__ptr, timestamp)
	if retVal == nil then return nil end
	local __c = _G["MouseEventResult"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:onMouseWheelDown(ray, timestamp)
	local retVal = Polycode.Entity_onMouseWheelDown(self.__ptr, ray.__ptr, timestamp)
	if retVal == nil then return nil end
	local __c = _G["MouseEventResult"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:setDepthOnly(val)
	local retVal = Polycode.Entity_setDepthOnly(self.__ptr, val)
end

function Entity:getDepthOnly()
	local retVal =  Polycode.Entity_getDepthOnly(self.__ptr)
	return retVal
end

function Entity:setBlendingMode(newBlendingMode)
	local retVal = Polycode.Entity_setBlendingMode(self.__ptr, newBlendingMode)
end

function Entity:getBlendingMode()
	local retVal =  Polycode.Entity_getBlendingMode(self.__ptr)
	return retVal
end

function Entity:getEntityProp(propName)
	local retVal = Polycode.Entity_getEntityProp(self.__ptr, propName)
	return retVal
end

function Entity:setEntityProp(propName, propValue)
	local retVal = Polycode.Entity_setEntityProp(self.__ptr, propName, propValue)
end

function Entity:setInverseY(val)
	local retVal = Polycode.Entity_setInverseY(self.__ptr, val)
end

function Entity:getInverseY()
	local retVal =  Polycode.Entity_getInverseY(self.__ptr)
	return retVal
end

function Entity:doUpdates(elapsed)
	local retVal = Polycode.Entity_doUpdates(self.__ptr, elapsed)
end

function Entity:doFixedUpdates()
	local retVal =  Polycode.Entity_doFixedUpdates(self.__ptr)
end

function Entity:buildPositionMatrix()
	local retVal =  Polycode.Entity_buildPositionMatrix(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:customHitDetection(ray)
	local retVal = Polycode.Entity_customHitDetection(self.__ptr, ray.__ptr)
	return retVal
end

function Entity:getNumTags()
	local retVal =  Polycode.Entity_getNumTags(self.__ptr)
	return retVal
end

function Entity:getTagAtIndex(index)
	local retVal = Polycode.Entity_getTagAtIndex(self.__ptr, index)
	return retVal
end

function Entity:hasTag(tag)
	local retVal = Polycode.Entity_hasTag(self.__ptr, tag)
	return retVal
end

function Entity:clearTags()
	local retVal =  Polycode.Entity_clearTags(self.__ptr)
end

function Entity:addTag(tag)
	local retVal = Polycode.Entity_addTag(self.__ptr, tag)
end

function Entity:getScreenPosition(projectionMatrix, cameraMatrix, viewport)
	local retVal = Polycode.Entity_getScreenPosition(self.__ptr, projectionMatrix.__ptr, cameraMatrix.__ptr, viewport.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector2"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:recalculateAABBAllChildren()
	local retVal =  Polycode.Entity_recalculateAABBAllChildren(self.__ptr)
end

function Entity:recalculateAABB()
	local retVal =  Polycode.Entity_recalculateAABB(self.__ptr)
end

function Entity:getWorldAABB()
	local retVal =  Polycode.Entity_getWorldAABB(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["AABB"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:getLocalBoundingBox()
	local retVal =  Polycode.Entity_getLocalBoundingBox(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Entity:setLocalBoundingBox(box)
	local retVal = Polycode.Entity_setLocalBoundingBox(self.__ptr, box.__ptr)
end

function Entity:setLocalBoundingBoxX(x)
	local retVal = Polycode.Entity_setLocalBoundingBoxX(self.__ptr, x)
end

function Entity:setLocalBoundingBoxY(y)
	local retVal = Polycode.Entity_setLocalBoundingBoxY(self.__ptr, y)
end

function Entity:setLocalBoundingBoxZ(z)
	local retVal = Polycode.Entity_setLocalBoundingBoxZ(self.__ptr, z)
end

function Entity:attachScript(script)
	local retVal = Polycode.Entity_attachScript(self.__ptr, script.__ptr)
end

function Entity:getNumScripts()
	local retVal =  Polycode.Entity_getNumScripts(self.__ptr)
	return retVal
end

function Entity:__delete()
	if self then Polycode.delete_Entity(self.__ptr) end
end
