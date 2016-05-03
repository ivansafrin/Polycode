require "Polycode/Resource"

class "SceneEntityInstanceResourceEntry" (Resource)







function SceneEntityInstanceResourceEntry:SceneEntityInstanceResourceEntry(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "Resource" then
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
		self.__ptr = Polycore.SceneEntityInstanceResourceEntry(unpack(arg))
	end
end

function SceneEntityInstanceResourceEntry:getInstance()
	local retVal =  Polycore.SceneEntityInstanceResourceEntry_getInstance(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["SceneEntityInstance"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneEntityInstanceResourceEntry:reloadResource()
	local retVal =  Polycore.SceneEntityInstanceResourceEntry_reloadResource(self.__ptr)
end

function SceneEntityInstanceResourceEntry:__delete()
	if self then Polycore.delete_SceneEntityInstanceResourceEntry(self.__ptr) end
end
