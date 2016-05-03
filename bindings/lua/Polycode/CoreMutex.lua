class "CoreMutex"



function CoreMutex:__getvar(name)
	if name == "mutexID" then
		return Polycore.CoreMutex_get_mutexID(self.__ptr)
	end
end


function CoreMutex:__setvar(name,value)
	if name == "mutexID" then
		Polycore.CoreMutex_set_mutexID(self.__ptr, value)
		return true
	end
	return false
end


function CoreMutex:lock()
	local retVal =  Polycore.CoreMutex_lock(self.__ptr)
end

function CoreMutex:unlock()
	local retVal =  Polycore.CoreMutex_unlock(self.__ptr)
end

function CoreMutex:__delete()
	if self then Polycore.delete_CoreMutex(self.__ptr) end
end
