require "Polycode/EventDispatcher"

class "Scene" (EventDispatcher)

Scene.SCENE_3D = 0
Scene.SCENE_2D = 1
Scene.SCENE_2D_TOPLEFT = 2

function Scene:__getvar(name)
	if name == "clearColor" then
		local retVal = Polycode.Scene_get_clearColor(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Color"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "useClearColor" then
		return Polycode.Scene_get_useClearColor(self.__ptr)
	elseif name == "useClearDepth" then
		return Polycode.Scene_get_useClearDepth(self.__ptr)
	elseif name == "ambientColor" then
		local retVal = Polycode.Scene_get_ambientColor(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Color"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "fogColor" then
		local retVal = Polycode.Scene_get_fogColor(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Color"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "enabled" then
		return Polycode.Scene_get_enabled(self.__ptr)
	elseif name == "ownsChildren" then
		return Polycode.Scene_get_ownsChildren(self.__ptr)
	elseif name == "rootEntity" then
		local retVal = Polycode.Scene_get_rootEntity(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Entity"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "sceneMouseRect" then
		local retVal = Polycode.Scene_get_sceneMouseRect(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Rectangle"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "remapMouse" then
		return Polycode.Scene_get_remapMouse(self.__ptr)
	elseif name == "constrainPickingToViewport" then
		return Polycode.Scene_get_constrainPickingToViewport(self.__ptr)
	end
	if EventDispatcher["__getvar"] ~= nil then
		return EventDispatcher.__getvar(self, name)
	end
end

function Scene:__setvar(name,value)
	if name == "clearColor" then
		Polycode.Scene_set_clearColor(self.__ptr, value.__ptr)
		return true
	elseif name == "useClearColor" then
		Polycode.Scene_set_useClearColor(self.__ptr, value)
		return true
	elseif name == "useClearDepth" then
		Polycode.Scene_set_useClearDepth(self.__ptr, value)
		return true
	elseif name == "ambientColor" then
		Polycode.Scene_set_ambientColor(self.__ptr, value.__ptr)
		return true
	elseif name == "fogColor" then
		Polycode.Scene_set_fogColor(self.__ptr, value.__ptr)
		return true
	elseif name == "enabled" then
		Polycode.Scene_set_enabled(self.__ptr, value)
		return true
	elseif name == "ownsChildren" then
		Polycode.Scene_set_ownsChildren(self.__ptr, value)
		return true
	elseif name == "rootEntity" then
		Polycode.Scene_set_rootEntity(self.__ptr, value.__ptr)
		return true
	elseif name == "sceneMouseRect" then
		Polycode.Scene_set_sceneMouseRect(self.__ptr, value.__ptr)
		return true
	elseif name == "remapMouse" then
		Polycode.Scene_set_remapMouse(self.__ptr, value)
		return true
	elseif name == "constrainPickingToViewport" then
		Polycode.Scene_set_constrainPickingToViewport(self.__ptr, value)
		return true
	end
	if EventDispatcher["__setvar"] ~= nil then
		return EventDispatcher.__setvar(self, name, value)
	else
		return false
	end
end
function Scene:Scene(...)
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
		self.__ptr = Polycode.Scene(unpack(arg))
	end
end

function Scene:enableFog(enable)
	local retVal = Polycode.Scene_enableFog(self.__ptr, enable)
end

function Scene:setFogProperties(fogMode, color, density, startDepth, endDepth)
	local retVal = Polycode.Scene_setFogProperties(self.__ptr, fogMode, color.__ptr, density, startDepth, endDepth)
end

function Scene:setSceneType(newType)
	local retVal = Polycode.Scene_setSceneType(self.__ptr, newType)
end

function Scene:fixedUpdate()
	local retVal =  Polycode.Scene_fixedUpdate(self.__ptr)
end

function Scene:Update()
	local retVal =  Polycode.Scene_Update(self.__ptr)
end

function Scene:isEnabled()
	local retVal =  Polycode.Scene_isEnabled(self.__ptr)
	return retVal
end

function Scene:setEnabled(enabled)
	local retVal = Polycode.Scene_setEnabled(self.__ptr, enabled)
end

function Scene:setOverrideMaterial(material)
	local retVal = Polycode.Scene_setOverrideMaterial(self.__ptr, material.__ptr)
end

function Scene:getNumLights()
	local retVal =  Polycode.Scene_getNumLights(self.__ptr)
	return retVal
end

function Scene:doVisibilityChecking(val)
	local retVal = Polycode.Scene_doVisibilityChecking(self.__ptr, val)
end

function Scene:doesVisibilityChecking()
	local retVal =  Polycode.Scene_doesVisibilityChecking(self.__ptr)
	return retVal
end

function Scene:__delete()
	if self then Polycode.delete_Scene(self.__ptr) end
end
