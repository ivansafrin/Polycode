require "Polycode/ResourcePool"

class "SpriteSet" (ResourcePool)







function SpriteSet:SpriteSet(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "ResourcePool" then
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
		self.__ptr = Polycore.SpriteSet(unpack(arg))
	end
end

function SpriteSet:setTexture(texture)
	local retVal = Polycore.SpriteSet_setTexture(self.__ptr, texture.__ptr)
end

function SpriteSet:getTexture()
	local retVal =  Polycore.SpriteSet_getTexture(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Texture"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SpriteSet:loadTexture(imageFileName)
	local retVal = Polycore.SpriteSet_loadTexture(self.__ptr, imageFileName)
	if retVal == nil then return nil end
	local __c = _G["Texture"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SpriteSet:addSpriteEntry(newEntry)
	local retVal = Polycore.SpriteSet_addSpriteEntry(self.__ptr, newEntry.__ptr)
end

function SpriteSet:getNumSpriteEntries()
	local retVal =  Polycore.SpriteSet_getNumSpriteEntries(self.__ptr)
	return retVal
end

function SpriteSet:getSpriteEntry(index)
	local retVal = Polycore.SpriteSet_getSpriteEntry(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["Sprite"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SpriteSet:removeSprite(sprite)
	local retVal = Polycore.SpriteSet_removeSprite(self.__ptr, sprite.__ptr)
end

function SpriteSet:loadSpriteSet(fileName)
	local retVal = Polycore.SpriteSet_loadSpriteSet(self.__ptr, fileName)
end

function SpriteSet:addSpriteFrame(frame, assignID)
	local retVal = Polycore.SpriteSet_addSpriteFrame(self.__ptr, frame.__ptr, assignID)
end

function SpriteSet:getNumFrames()
	local retVal =  Polycore.SpriteSet_getNumFrames(self.__ptr)
	return retVal
end

function SpriteSet:getSpriteFrame(index)
	local retVal = Polycore.SpriteSet_getSpriteFrame(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["SpriteFrame"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SpriteSet:getSpriteFrameByID(frameID)
	local retVal = Polycore.SpriteSet_getSpriteFrameByID(self.__ptr, frameID)
	if retVal == nil then return nil end
	local __c = _G["SpriteFrame"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SpriteSet:removeFrameByID(frameID)
	local retVal = Polycore.SpriteSet_removeFrameByID(self.__ptr, frameID)
end

function SpriteSet:setSpriteFrame(frame)
	local retVal = Polycore.SpriteSet_setSpriteFrame(self.__ptr, frame.__ptr)
end

function SpriteSet:clearFrames()
	local retVal =  Polycore.SpriteSet_clearFrames(self.__ptr)
end

function SpriteSet:createGridFrames(xCount, yCount, defaultAnchor)
	local retVal = Polycore.SpriteSet_createGridFrames(self.__ptr, xCount, yCount, defaultAnchor.__ptr)
end

function SpriteSet:createFramesFromIslands(minDistance, defaultAnchor)
	local retVal = Polycore.SpriteSet_createFramesFromIslands(self.__ptr, minDistance, defaultAnchor.__ptr)
end

function SpriteSet:getSpriteByName(spriteName)
	local retVal = Polycore.SpriteSet_getSpriteByName(self.__ptr, spriteName)
	if retVal == nil then return nil end
	local __c = _G["Sprite"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SpriteSet:__delete()
	if self then Polycore.delete_SpriteSet(self.__ptr) end
end
