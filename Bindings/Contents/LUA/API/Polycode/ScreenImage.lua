require "Polycode/ScreenShape"

class "ScreenImage" (ScreenShape)







function ScreenImage:ScreenImage(...)
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1]:class() == "ScreenShape" then
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
		self.__ptr = Polycore.ScreenImage(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function ScreenImage:setImageCoordinates(x, y, width, height)
	local retVal = Polycore.ScreenImage_setImageCoordinates(self.__ptr, x, y, width, height)
end

function ScreenImage:getImageWidth()
	local retVal =  Polycore.ScreenImage_getImageWidth(self.__ptr)
	return retVal
end

function ScreenImage:getImageHeight()
	local retVal =  Polycore.ScreenImage_getImageHeight(self.__ptr)
	return retVal
end



function ScreenImage:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_ScreenImage(self.__ptr)
end
