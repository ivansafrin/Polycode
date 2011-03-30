class "TimerManager"

function TimerManager:TimerManager()
	if self.__ptr == nil then
		self.__ptr = Polycore.TimerManager()
	end
end

function TimerManager:removeTimer(timer)
	return Polycore.TimerManager_removeTimer(self.__ptr, timer.__ptr)
end

function TimerManager:addTimer(timer)
	return Polycore.TimerManager_addTimer(self.__ptr, timer.__ptr)
end

function TimerManager:Update()
	return Polycore.TimerManager_Update(self.__ptr)
end

