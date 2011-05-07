class "TimerManager"







function TimerManager:TimerManager(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.TimerManager(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function TimerManager:removeTimer(timer)
	local retVal = Polycore.TimerManager_removeTimer(self.__ptr, timer.__ptr)
end

function TimerManager:addTimer(timer)
	local retVal = Polycore.TimerManager_addTimer(self.__ptr, timer.__ptr)
end

function TimerManager:Update()
	local retVal =  Polycore.TimerManager_Update(self.__ptr)
end

