require "Polycode/ScreenShape"

class "ScreenLabel" (ScreenShape)







function ScreenLabel:ScreenLabel(...)
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
		self.__ptr = Polycore.ScreenLabel(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function ScreenLabel:addDropShadow(color, size, offsetX, offsetY)
	local retVal = Polycore.ScreenLabel_addDropShadow(self.__ptr, color.__ptr, size, offsetX, offsetY)
end

function ScreenLabel:setText(newText)
	local retVal = Polycore.ScreenLabel_setText(self.__ptr, newText)
end

function ScreenLabel:getText()
	local retVal =  Polycore.ScreenLabel_getText(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = String("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function ScreenLabel:getLabel()
	local retVal =  Polycore.ScreenLabel_getLabel(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Label("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end



function ScreenLabel:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_ScreenLabel(self.__ptr)
end
