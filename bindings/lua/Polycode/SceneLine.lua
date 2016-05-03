require "Polycode/SceneMesh"

class "SceneLine" (SceneMesh)







function SceneLine:SceneLine(...)
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
		self.__ptr = Polycore.SceneLine(unpack(arg))
	end
end

function SceneLine.SceneLineWithPositions(start, _end)
	local retVal = Polycore.SceneLine_SceneLineWithPositions(start.__ptr, _end.__ptr)
	if retVal == nil then return nil end
	local __c = _G["SceneLine"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneLine:setStart(start)
	local retVal = Polycore.SceneLine_setStart(self.__ptr, start.__ptr)
end

function SceneLine:setEnd(_end)
	local retVal = Polycore.SceneLine_setEnd(self.__ptr, _end.__ptr)
end

function SceneLine:Update()
	local retVal =  Polycore.SceneLine_Update(self.__ptr)
end

function SceneLine:__delete()
	if self then Polycore.delete_SceneLine(self.__ptr) end
end
