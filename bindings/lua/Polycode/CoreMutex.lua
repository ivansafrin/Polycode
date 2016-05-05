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
function CoreMutex:lock()
	local retVal =  Polycode.CoreMutex_lock(self.__ptr)
end

function CoreMutex:unlock()
	local retVal =  Polycode.CoreMutex_unlock(self.__ptr)
end

function CoreMutex:__delete()
	if self then Polycode.delete_CoreMutex(self.__ptr) end
end
