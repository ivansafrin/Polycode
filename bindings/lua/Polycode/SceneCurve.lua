require "Polycode/SceneMesh"

class "SceneCurve" (SceneMesh)


function SceneCurve:__getvar(name)
	if name == "renderCurve" then
		return Polycode.SceneCurve_get_renderCurve(self.__ptr)
	elseif name == "curveResolution" then
		return Polycode.SceneCurve_get_curveResolution(self.__ptr)
	end
	if SceneMesh["__getvar"] ~= nil then
		return SceneMesh.__getvar(self, name)
	end
end

function SceneCurve:__setvar(name,value)
	if name == "renderCurve" then
		Polycode.SceneCurve_set_renderCurve(self.__ptr, value)
		return true
	elseif name == "curveResolution" then
		Polycode.SceneCurve_set_curveResolution(self.__ptr, value)
		return true
	end
	if SceneMesh["__setvar"] ~= nil then
		return SceneMesh.__setvar(self, name, value)
	else
		return false
	end
end
function SceneCurve:SceneCurve(...)
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
		self.__ptr = Polycode.SceneCurve(unpack(arg))
	end
end

function SceneCurve:getWorldPointAt(t)
	local retVal = Polycode.SceneCurve_getWorldPointAt(self.__ptr, t)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneCurve:__delete()
	if self then Polycode.delete_SceneCurve(self.__ptr) end
end
