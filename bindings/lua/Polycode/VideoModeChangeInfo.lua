class "VideoModeChangeInfo"


function VideoModeChangeInfo:__getvar(name)
	if name == "xRes" then
		return Polycode.VideoModeChangeInfo_get_xRes(self.__ptr)
	elseif name == "yRes" then
		return Polycode.VideoModeChangeInfo_get_yRes(self.__ptr)
	elseif name == "fullScreen" then
		return Polycode.VideoModeChangeInfo_get_fullScreen(self.__ptr)
	elseif name == "vSync" then
		return Polycode.VideoModeChangeInfo_get_vSync(self.__ptr)
	elseif name == "aaLevel" then
		return Polycode.VideoModeChangeInfo_get_aaLevel(self.__ptr)
	elseif name == "anisotropyLevel" then
		return Polycode.VideoModeChangeInfo_get_anisotropyLevel(self.__ptr)
	elseif name == "retinaSupport" then
		return Polycode.VideoModeChangeInfo_get_retinaSupport(self.__ptr)
	end
end

function VideoModeChangeInfo:__setvar(name,value)
	if name == "xRes" then
		Polycode.VideoModeChangeInfo_set_xRes(self.__ptr, value)
		return true
	elseif name == "yRes" then
		Polycode.VideoModeChangeInfo_set_yRes(self.__ptr, value)
		return true
	elseif name == "fullScreen" then
		Polycode.VideoModeChangeInfo_set_fullScreen(self.__ptr, value)
		return true
	elseif name == "vSync" then
		Polycode.VideoModeChangeInfo_set_vSync(self.__ptr, value)
		return true
	elseif name == "aaLevel" then
		Polycode.VideoModeChangeInfo_set_aaLevel(self.__ptr, value)
		return true
	elseif name == "anisotropyLevel" then
		Polycode.VideoModeChangeInfo_set_anisotropyLevel(self.__ptr, value)
		return true
	elseif name == "retinaSupport" then
		Polycode.VideoModeChangeInfo_set_retinaSupport(self.__ptr, value)
		return true
	end
	return false
end
function VideoModeChangeInfo:__delete()
	if self then Polycode.delete_VideoModeChangeInfo(self.__ptr) end
end
