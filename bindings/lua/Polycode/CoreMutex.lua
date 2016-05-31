class "CoreMutex"


function CoreMutex:__getvar(name)
	if name == "mutexID" then
		return Polycode.CoreMutex_get_mutexID(self.__ptr)
	end
end

function CoreMutex:__setvar(name,value)
	if name == "mutexID" then
		Polycode.CoreMutex_set_mutexID(self.__ptr, value)
		return true
	end
	return false
end
function CoreMutex:CoreMutex(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.CoreMutex(unpack(arg))
	end
end

function CoreMutex:lock()
	local retVal =  Polycode.CoreMutex_lock(self.__ptr)
end

function CoreMutex:unlock()
	local retVal =  Polycode.CoreMutex_unlock(self.__ptr)
end

function CoreMutex:__delete()
	if self then Polycode.delete_CoreMutex(self.__ptr) end
end
