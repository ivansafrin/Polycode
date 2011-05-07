class "Entity"



function Entity:__index__(name)
	if name == "custEntityType" then
		return Polycore.Entity_get_custEntityType(self.__ptr)
	elseif name == "billboardMode" then
		return Polycore.Entity_get_billboardMode(self.__ptr)
	elseif name == "billboardRoll" then
		return Polycore.Entity_get_billboardRoll(self.__ptr)
	elseif name == "alphaTest" then
		return Polycore.Entity_get_alphaTest(self.__ptr)
	elseif name == "backfaceCulled" then
		return Polycore.Entity_get_backfaceCulled(self.__ptr)
	elseif name == "renderWireframe" then
		return Polycore.Entity_get_renderWireframe(self.__ptr)
	elseif name == "enabled" then
		return Polycore.Entity_get_enabled(self.__ptr)
	elseif name == "visible" then
		return Polycore.Entity_get_visible(self.__ptr)
	elseif name == "depthWrite" then
		return Polycore.Entity_get_depthWrite(self.__ptr)
	elseif name == "depthTest" then
		return Polycore.Entity_get_depthTest(self.__ptr)
	elseif name == "blendingMode" then
		return Polycore.Entity_get_blendingMode(self.__ptr)
	elseif name == "colorAffectsChildren" then
		return Polycore.Entity_get_colorAffectsChildren(self.__ptr)
	elseif name == "depthOnly" then
		return Polycore.Entity_get_depthOnly(self.__ptr)
	elseif name == "ignoreParentMatrix" then
		return Polycore.Entity_get_ignoreParentMatrix(self.__ptr)
	elseif name == "isMask" then
		return Polycore.Entity_get_isMask(self.__ptr)
	end
end


function Entity:__set_callback(name,value)
	if name == "custEntityType" then
		Polycore.Entity_set_custEntityType(self.__ptr, value)
		return true
	elseif name == "billboardMode" then
		Polycore.Entity_set_billboardMode(self.__ptr, value)
		return true
	elseif name == "billboardRoll" then
		Polycore.Entity_set_billboardRoll(self.__ptr, value)
		return true
	elseif name == "alphaTest" then
		Polycore.Entity_set_alphaTest(self.__ptr, value)
		return true
	elseif name == "backfaceCulled" then
		Polycore.Entity_set_backfaceCulled(self.__ptr, value)
		return true
	elseif name == "renderWireframe" then
		Polycore.Entity_set_renderWireframe(self.__ptr, value)
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
	elseif name == "blendingMode" then
		Polycore.Entity_set_blendingMode(self.__ptr, value)
		return true
	elseif name == "colorAffectsChildren" then
		Polycore.Entity_set_colorAffectsChildren(self.__ptr, value)
		return true
	elseif name == "depthOnly" then
		Polycore.Entity_set_depthOnly(self.__ptr, value)
		return true
	elseif name == "ignoreParentMatrix" then
		Polycore.Entity_set_ignoreParentMatrix(self.__ptr, value)
		return true
	elseif name == "isMask" then
		Polycore.Entity_set_isMask(self.__ptr, value)
		return true
	end
	return false
end


function Entity:Entity(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.Entity(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function Entity:Render()
	local retVal =  Polycore.Entity_Render(self.__ptr)
end

function Entity:Update()
	local retVal =  Polycore.Entity_Update(self.__ptr)
end

function Entity:transformAndRender()
	local retVal =  Polycore.Entity_transformAndRender(self.__ptr)
end

function Entity:renderChildren()
	local retVal =  Polycore.Entity_renderChildren(self.__ptr)
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
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Matrix4("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Entity:getConcatenatedMatrix()
	local retVal =  Polycore.Entity_getConcatenatedMatrix(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Matrix4("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Entity:getConcatenatedRollMatrix()
	local retVal =  Polycore.Entity_getConcatenatedRollMatrix(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Matrix4("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Entity:setTransformByMatrix(matrix)
	local retVal = Polycore.Entity_setTransformByMatrix(self.__ptr, matrix.__ptr)
end

function Entity:setTransformByMatrixPure(matrix)
	local retVal = Polycore.Entity_setTransformByMatrixPure(self.__ptr, matrix.__ptr)
end

function Entity:getLookAtMatrix(loc, upVector)
	local retVal = Polycore.Entity_getLookAtMatrix(self.__ptr, loc.__ptr, upVector.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Matrix4("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Entity:addEntity(newChild)
	local retVal = Polycore.Entity_addEntity(self.__ptr, newChild.__ptr)
end

function Entity:addChild(newChild)
	local retVal = Polycore.Entity_addChild(self.__ptr, newChild.__ptr)
end

function Entity:removeChild(entityToRemove)
	local retVal = Polycore.Entity_removeChild(self.__ptr, entityToRemove.__ptr)
end

function Entity:setParentEntity(entity)
	local retVal = Polycore.Entity_setParentEntity(self.__ptr, entity.__ptr)
end

function Entity:getParentEntity()
	local retVal =  Polycore.Entity_getParentEntity(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Entity("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Entity:getPosition()
	local retVal =  Polycore.Entity_getPosition(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Vector3("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Entity:getCombinedPosition()
	local retVal =  Polycore.Entity_getCombinedPosition(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Vector3("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
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
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Vector3("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Entity:getScale()
	local retVal =  Polycore.Entity_getScale(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Vector3("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
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

function Entity:setRotationQuat(w, x, y, z)
	local retVal = Polycore.Entity_setRotationQuat(self.__ptr, w, x, y, z)
end

function Entity:getRotationQuat()
	local retVal =  Polycore.Entity_getRotationQuat(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Quaternion("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Entity:lookAt(loc, upVector)
	local retVal = Polycore.Entity_lookAt(self.__ptr, loc.__ptr, upVector.__ptr)
end

function Entity:lookAtEntity(entity, upVector)
	local retVal = Polycore.Entity_lookAtEntity(self.__ptr, entity.__ptr, upVector.__ptr)
end

function Entity:getCombinedColor()
	local retVal =  Polycore.Entity_getCombinedColor(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Color("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Entity:setColor(r, g, b, a)
	local retVal = Polycore.Entity_setColor(self.__ptr, r, g, b, a)
end

function Entity:setColorInt(r, g, b, a)
	local retVal = Polycore.Entity_setColorInt(self.__ptr, r, g, b, a)
end

function Entity:recalculateBBox()
	local retVal =  Polycore.Entity_recalculateBBox(self.__ptr)
end

function Entity:getBBoxRadius()
	local retVal =  Polycore.Entity_getBBoxRadius(self.__ptr)
	return retVal
end

function Entity:getCompoundBBoxRadius()
	local retVal =  Polycore.Entity_getCompoundBBoxRadius(self.__ptr)
	return retVal
end

function Entity:setBBoxRadius(rad)
	local retVal = Polycore.Entity_setBBoxRadius(self.__ptr, rad)
end

function Entity:setMask(mask)
	local retVal = Polycore.Entity_setMask(self.__ptr, mask.__ptr)
end

function Entity:clearMask()
	local retVal =  Polycore.Entity_clearMask(self.__ptr)
end

function Entity:setBlendingMode(newBl_endingMode)
	local retVal = Polycore.Entity_setBlendingMode(self.__ptr, newBl_endingMode)
end

function Entity:getChildCenter()
	local retVal =  Polycore.Entity_getChildCenter(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Vector3("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Entity:getEntityProp(propName)
	local retVal = Polycore.Entity_getEntityProp(self.__ptr, propName)
	return retVal
end

function Entity:doUpdates()
	local retVal =  Polycore.Entity_doUpdates(self.__ptr)
end

function Entity:buildPositionMatrix()
	local retVal =  Polycore.Entity_buildPositionMatrix(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Matrix4("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Entity:adjustMatrixForChildren()
	local retVal =  Polycore.Entity_adjustMatrixForChildren(self.__ptr)
end

function Entity:setRenderer(r_enderer)
	local retVal = Polycore.Entity_setRenderer(self.__ptr, r_enderer.__ptr)
end

