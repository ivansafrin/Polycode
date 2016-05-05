require "Polycode/SceneMesh"

class "ScenePrimitive" (SceneMesh)

ScenePrimitive.TYPE_BOX = 0
ScenePrimitive.TYPE_PLANE = 1
ScenePrimitive.TYPE_VPLANE = 2
ScenePrimitive.TYPE_CYLINDER = 3
ScenePrimitive.TYPE_UNCAPPED_CYLINDER = 4
ScenePrimitive.TYPE_SPHERE = 5
ScenePrimitive.TYPE_TORUS = 6
ScenePrimitive.TYPE_CONE = 7
ScenePrimitive.TYPE_CIRCLE = 8
ScenePrimitive.TYPE_ICOSPHERE = 9
ScenePrimitive.TYPE_OCTOSPHERE = 10
ScenePrimitive.TYPE_LINE_CIRCLE = 11

function ScenePrimitive:ScenePrimitive(...)
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
		self.__ptr = Polycode.ScenePrimitive(unpack(arg))
	end
end

function ScenePrimitive:setPrimitiveOptions(type, v1, v2, v3, v4, v5)
	local retVal = Polycode.ScenePrimitive_setPrimitiveOptions(self.__ptr, type, v1, v2, v3, v4, v5)
end

function ScenePrimitive:recreatePrimitive()
	local retVal =  Polycode.ScenePrimitive_recreatePrimitive(self.__ptr)
end

function ScenePrimitive:getPrimitiveType()
	local retVal =  Polycode.ScenePrimitive_getPrimitiveType(self.__ptr)
	return retVal
end

function ScenePrimitive:getPrimitiveParameter1()
	local retVal =  Polycode.ScenePrimitive_getPrimitiveParameter1(self.__ptr)
	return retVal
end

function ScenePrimitive:getPrimitiveParameter2()
	local retVal =  Polycode.ScenePrimitive_getPrimitiveParameter2(self.__ptr)
	return retVal
end

function ScenePrimitive:getPrimitiveParameter3()
	local retVal =  Polycode.ScenePrimitive_getPrimitiveParameter3(self.__ptr)
	return retVal
end

function ScenePrimitive:getPrimitiveParameter4()
	local retVal =  Polycode.ScenePrimitive_getPrimitiveParameter4(self.__ptr)
	return retVal
end

function ScenePrimitive:getPrimitiveParameter5()
	local retVal =  Polycode.ScenePrimitive_getPrimitiveParameter5(self.__ptr)
	return retVal
end

function ScenePrimitive:Clone(deepClone, ignoreEditorOnly)
	local retVal = Polycode.ScenePrimitive_Clone(self.__ptr, deepClone, ignoreEditorOnly)
	if retVal == nil then return nil end
	local __c = _G["Entity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ScenePrimitive:applyClone(clone, deepClone, ignoreEditorOnly)
	local retVal = Polycode.ScenePrimitive_applyClone(self.__ptr, clone.__ptr, deepClone, ignoreEditorOnly)
end

function ScenePrimitive:__delete()
	if self then Polycode.delete_ScenePrimitive(self.__ptr) end
end
