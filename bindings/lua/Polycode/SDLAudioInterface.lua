require "Polycode/Polycode::AudioInterface"

class "SDLAudioInterface" (Polycode::AudioInterface)


function SDLAudioInterface:SDLAudioInterface(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "Polycode::AudioInterface" then
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
		self.__ptr = Polycode.SDLAudioInterface(unpack(arg))
	end
end

function SDLAudioInterface:sdlCallback(userData, _stream, _length)
	local retVal = Polycode.SDLAudioInterface_sdlCallback(self.__ptr, userData.__ptr, _stream.__ptr, _length)
end

function SDLAudioInterface:__delete()
	if self then Polycode.delete_SDLAudioInterface(self.__ptr) end
end
