class "TimeInfo"


function TimeInfo:__getvar(name)
	if name == "seconds" then
		return Polycode.TimeInfo_get_seconds(self.__ptr)
	elseif name == "minutes" then
		return Polycode.TimeInfo_get_minutes(self.__ptr)
	elseif name == "hours" then
		return Polycode.TimeInfo_get_hours(self.__ptr)
	elseif name == "month" then
		return Polycode.TimeInfo_get_month(self.__ptr)
	elseif name == "monthDay" then
		return Polycode.TimeInfo_get_monthDay(self.__ptr)
	elseif name == "weekDay" then
		return Polycode.TimeInfo_get_weekDay(self.__ptr)
	elseif name == "year" then
		return Polycode.TimeInfo_get_year(self.__ptr)
	elseif name == "yearDay" then
		return Polycode.TimeInfo_get_yearDay(self.__ptr)
	end
end

function TimeInfo:__setvar(name,value)
	if name == "seconds" then
		Polycode.TimeInfo_set_seconds(self.__ptr, value)
		return true
	elseif name == "minutes" then
		Polycode.TimeInfo_set_minutes(self.__ptr, value)
		return true
	elseif name == "hours" then
		Polycode.TimeInfo_set_hours(self.__ptr, value)
		return true
	elseif name == "month" then
		Polycode.TimeInfo_set_month(self.__ptr, value)
		return true
	elseif name == "monthDay" then
		Polycode.TimeInfo_set_monthDay(self.__ptr, value)
		return true
	elseif name == "weekDay" then
		Polycode.TimeInfo_set_weekDay(self.__ptr, value)
		return true
	elseif name == "year" then
		Polycode.TimeInfo_set_year(self.__ptr, value)
		return true
	elseif name == "yearDay" then
		Polycode.TimeInfo_set_yearDay(self.__ptr, value)
		return true
	end
	return false
end
function TimeInfo:TimeInfo(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.TimeInfo(unpack(arg))
	end
end

function TimeInfo:__delete()
	if self then Polycode.delete_TimeInfo(self.__ptr) end
end
