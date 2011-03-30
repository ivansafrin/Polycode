class "Entity"

function Entity:Entity()
	if self.__ptr == nil then
		self.__ptr = Polycore.Entity()
	end
end

function Entity:Render()
	return Polycore.Entity_Render(self.__ptr)
end

function Entity:Update()
	return Polycore.Entity_Update(self.__ptr)
end

function Entity:transformAndRender()
	return Polycore.Entity_transformAndRender(self.__ptr)
end

function Entity:setMatrix(matrix)
	return Polycore.Entity_setMatrix(self.__ptr, matrix.__ptr)
end

function Entity:rebuildTransformMatrix()
	return Polycore.Entity_rebuildTransformMatrix(self.__ptr)
end

function Entity:addEntity(newChild)
	return Polycore.Entity_addEntity(self.__ptr, newChild.__ptr)
end

function Entity:addChild(newChild)
	return Polycore.Entity_addChild(self.__ptr, newChild.__ptr)
end

function Entity:removeChild(entityToRemove)
	return Polycore.Entity_removeChild(self.__ptr, entityToRemove.__ptr)
end

function Entity:updateEntityMatrix()
	return Polycore.Entity_updateEntityMatrix(self.__ptr)
end

function Entity:renderChildren()
	return Polycore.Entity_renderChildren(self.__ptr)
end

function Entity:getPosition()
	return Polycore.Entity_getPosition(self.__ptr)
end

function Entity:setPosition(x, y, z)
	return Polycore.Entity_setPosition(self.__ptr, x, y, z)
end

function Entity:setPositionX(x)
	return Polycore.Entity_setPositionX(self.__ptr, x)
end

function Entity:setPositionY(y)
	return Polycore.Entity_setPositionY(self.__ptr, y)
end

function Entity:setPositionZ(z)
	return Polycore.Entity_setPositionZ(self.__ptr, z)
end

function Entity:setScaleX(x)
	return Polycore.Entity_setScaleX(self.__ptr, x)
end

function Entity:setScaleY(y)
	return Polycore.Entity_setScaleY(self.__ptr, y)
end

function Entity:setScaleZ(z)
	return Polycore.Entity_setScaleZ(self.__ptr, z)
end

function Entity:Translate(x, y, z)
	return Polycore.Entity_Translate(self.__ptr, x, y, z)
end

function Entity:Scale(x, y, z)
	return Polycore.Entity_Scale(self.__ptr, x, y, z)
end

function Entity:setScale(x, y, z)
	return Polycore.Entity_setScale(self.__ptr, x, y, z)
end

function Entity:getScale()
	return Polycore.Entity_getScale(self.__ptr)
end

function Entity:getCombinedPosition()
	return Polycore.Entity_getCombinedPosition(self.__ptr)
end

function Entity:getCombinedPitch()
	return Polycore.Entity_getCombinedPitch(self.__ptr)
end

function Entity:getCombinedYaw()
	return Polycore.Entity_getCombinedYaw(self.__ptr)
end

function Entity:getCombinedRoll()
	return Polycore.Entity_getCombinedRoll(self.__ptr)
end

function Entity:setParentEntity(entity)
	return Polycore.Entity_setParentEntity(self.__ptr, entity.__ptr)
end

function Entity:getParentEntity()
	return Polycore.Entity_getParentEntity(self.__ptr)
end

function Entity:rebuildRotation()
	return Polycore.Entity_rebuildRotation(self.__ptr)
end

function Entity:dirtyMatrix(val)
	return Polycore.Entity_dirtyMatrix(self.__ptr, val)
end

function Entity:setPitch(pitch)
	return Polycore.Entity_setPitch(self.__ptr, pitch)
end

function Entity:setYaw(yaw)
	return Polycore.Entity_setYaw(self.__ptr, yaw)
end

function Entity:setRoll(roll)
	return Polycore.Entity_setRoll(self.__ptr, roll)
end

function Entity:Roll(roll)
	return Polycore.Entity_Roll(self.__ptr, roll)
end

function Entity:Yaw(roll)
	return Polycore.Entity_Yaw(self.__ptr, roll)
end

function Entity:Pitch(roll)
	return Polycore.Entity_Pitch(self.__ptr, roll)
end

function Entity:getPitch()
	return Polycore.Entity_getPitch(self.__ptr)
end

function Entity:getYaw()
	return Polycore.Entity_getYaw(self.__ptr)
end

function Entity:getRoll()
	return Polycore.Entity_getRoll(self.__ptr)
end

function Entity:setRotationQuat(w, x, y, z)
	return Polycore.Entity_setRotationQuat(self.__ptr, w, x, y, z)
end

function Entity:getRotationQuat()
	return Polycore.Entity_getRotationQuat(self.__ptr)
end

function Entity:getTransformMatrix()
	return Polycore.Entity_getTransformMatrix(self.__ptr)
end

function Entity:getConcatenatedMatrix()
	return Polycore.Entity_getConcatenatedMatrix(self.__ptr)
end

function Entity:getConcatenatedRollMatrix()
	return Polycore.Entity_getConcatenatedRollMatrix(self.__ptr)
end

function Entity:setTransformByMatrix(matrix)
	return Polycore.Entity_setTransformByMatrix(self.__ptr, matrix.__ptr)
end

function Entity:setTransformByMatrixPure(matrix)
	return Polycore.Entity_setTransformByMatrixPure(self.__ptr, matrix.__ptr)
end

function Entity:setRenderer(r_enderer)
	return Polycore.Entity_setRenderer(self.__ptr, r_enderer.__ptr)
end

function Entity:getCombinedColor()
	return Polycore.Entity_getCombinedColor(self.__ptr)
end

function Entity:setColor(r, g, b, a)
	return Polycore.Entity_setColor(self.__ptr, r, g, b, a)
end

function Entity:setColorInt(r, g, b, a)
	return Polycore.Entity_setColorInt(self.__ptr, r, g, b, a)
end

function Entity:recalculateBBox()
	return Polycore.Entity_recalculateBBox(self.__ptr)
end

function Entity:getBBoxRadius()
	return Polycore.Entity_getBBoxRadius(self.__ptr)
end

function Entity:getCompoundBBoxRadius()
	return Polycore.Entity_getCompoundBBoxRadius(self.__ptr)
end

function Entity:setBBoxRadius(rad)
	return Polycore.Entity_setBBoxRadius(self.__ptr, rad)
end

function Entity:setBlendingMode(newBl_endingMode)
	return Polycore.Entity_setBlendingMode(self.__ptr, newBl_endingMode)
end

function Entity:getChildCenter()
	return Polycore.Entity_getChildCenter(self.__ptr)
end

function Entity:setDepthWrite(val)
	return Polycore.Entity_setDepthWrite(self.__ptr, val)
end

function Entity:doUpdates()
	return Polycore.Entity_doUpdates(self.__ptr)
end

function Entity:lookAt(loc, upVector)
	return Polycore.Entity_lookAt(self.__ptr, loc.__ptr, upVector.__ptr)
end

function Entity:lookAtEntity(entity, upVector)
	return Polycore.Entity_lookAtEntity(self.__ptr, entity.__ptr, upVector.__ptr)
end

function Entity:getLookAtMatrix(loc, upVector)
	return Polycore.Entity_getLookAtMatrix(self.__ptr, loc.__ptr, upVector.__ptr)
end

function Entity:buildPositionMatrix()
	return Polycore.Entity_buildPositionMatrix(self.__ptr)
end

function Entity:adjustMatrixForChildren()
	return Polycore.Entity_adjustMatrixForChildren(self.__ptr)
end

function Entity:setMask(mask)
	return Polycore.Entity_setMask(self.__ptr, mask.__ptr)
end

function Entity:clearMask()
	return Polycore.Entity_clearMask(self.__ptr)
end

function Entity:getCompoundScale()
	return Polycore.Entity_getCompoundScale(self.__ptr)
end

function Entity:getEntityProp(propName)
	return Polycore.Entity_getEntityProp(self.__ptr, propName)
end

