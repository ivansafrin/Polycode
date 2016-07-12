require "Polycode/EventDispatcher"

class "CoreServices" (EventDispatcher)


function CoreServices:createInstance()
	local retVal =  Polycode.CoreServices_createInstance(self.__ptr)
end

function CoreServices:Update(elapsed)
	local retVal = Polycode.CoreServices_Update(self.__ptr, elapsed)
end

function CoreServices:fixedUpdate()
	local retVal =  Polycode.CoreServices_fixedUpdate(self.__ptr)
end

function CoreServices:__delete()
	if self then Polycode.delete_CoreServices(self.__ptr) end
end
