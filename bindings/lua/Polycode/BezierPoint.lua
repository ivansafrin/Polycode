class "BezierPoint"


function BezierPoint:__getvar(name)
	if name == "p1" then
		local retVal = Polycode.BezierPoint_get_p1(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "p2" then
		local retVal = Polycode.BezierPoint_get_p2(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "p3" then
		local retVal = Polycode.BezierPoint_get_p3(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end

function BezierPoint:__setvar(name,value)
	if name == "p1" then
		Polycode.BezierPoint_set_p1(self.__ptr, value.__ptr)
		return true
	elseif name == "p2" then
		Polycode.BezierPoint_set_p2(self.__ptr, value.__ptr)
		return true
	elseif name == "p3" then
		Polycode.BezierPoint_set_p3(self.__ptr, value.__ptr)
		return true
	end
	return false
end
function BezierPoint:BezierPoint(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.BezierPoint(unpack(arg))
	end
end

function BezierPoint:__delete()
	if self then Polycode.delete_BezierPoint(self.__ptr) end
end
