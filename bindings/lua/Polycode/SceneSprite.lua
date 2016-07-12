require "Polycode/SceneMesh"

class "SceneSprite" (SceneMesh)


function SceneSprite:SceneSprite(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "SceneMesh" then
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
		self.__ptr = Polycode.SceneSprite(unpack(arg))
	end
end

function SceneSprite:getCurrentSprite()
	local retVal =  Polycode.SceneSprite_getCurrentSprite(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["shared_ptr<Sprite>"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneSprite:setSpriteByName(spriteName)
	local retVal = Polycode.SceneSprite_setSpriteByName(self.__ptr, spriteName)
end

function SceneSprite:setCurrentFrame(frameIndex)
	local retVal = Polycode.SceneSprite_setCurrentFrame(self.__ptr, frameIndex)
end

function SceneSprite:getCurrentFrame()
	local retVal =  Polycode.SceneSprite_getCurrentFrame(self.__ptr)
	return retVal
end

function SceneSprite:Update()
	local retVal =  Polycode.SceneSprite_Update(self.__ptr)
end

function SceneSprite:getSpriteBoundingBox()
	local retVal =  Polycode.SceneSprite_getSpriteBoundingBox(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneSprite:setPaused(val)
	local retVal = Polycode.SceneSprite_setPaused(self.__ptr, val)
end

function SceneSprite:isPaused()
	local retVal =  Polycode.SceneSprite_isPaused(self.__ptr)
	return retVal
end

function SceneSprite:setSprite(spriteEntry)
	local retVal = Polycode.SceneSprite_setSprite(self.__ptr, spriteEntry.__ptr)
end

function SceneSprite:setSpriteStateByName(name, startingFrame, playOnce)
	local retVal = Polycode.SceneSprite_setSpriteStateByName(self.__ptr, name, startingFrame, playOnce)
end

function SceneSprite:getStartOnRandomFrame()
	local retVal =  Polycode.SceneSprite_getStartOnRandomFrame(self.__ptr)
	return retVal
end

function SceneSprite:setStartOnRandomFrame(val)
	local retVal = Polycode.SceneSprite_setStartOnRandomFrame(self.__ptr, val)
end

function SceneSprite:__delete()
	if self then Polycode.delete_SceneSprite(self.__ptr) end
end
