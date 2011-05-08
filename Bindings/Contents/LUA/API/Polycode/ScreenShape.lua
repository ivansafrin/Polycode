require "Polycode/ScreenMesh"

class "ScreenShape" (ScreenMesh)



SHAPE_RECT = 1
SHAPE_CIRCLE = 2
SHAPE_CUSTOM = 4
function ScreenShape:__index__(name)
	if name == "strokeEnabled" then
		return Polycore.ScreenShape_get_strokeEnabled(self.__ptr)
	elseif name == "lineSmooth" then
		return Polycore.ScreenShape_get_lineSmooth(self.__ptr)
	end
end


function ScreenShape:__set_callback(name,value)
	if name == "strokeEnabled" then
		Polycore.ScreenShape_set_strokeEnabled(self.__ptr, value)
		return true
	elseif name == "lineSmooth" then
		Polycore.ScreenShape_set_lineSmooth(self.__ptr, value)
		return true
	end
	return false
end


function ScreenShape:ScreenShape(...)
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1]:class() == "ScreenMesh" then
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
		self.__ptr = Polycore.ScreenShape(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function ScreenShape:Render()
	local retVal =  Polycore.ScreenShape_Render(self.__ptr)
end

function ScreenShape:setStrokeColor(r, g, b, a)
	local retVal = Polycore.ScreenShape_setStrokeColor(self.__ptr, r, g, b, a)
end

function ScreenShape:setStrokeWidth(width)
	local retVal = Polycore.ScreenShape_setStrokeWidth(self.__ptr, width)
end

function ScreenShape:setGradient(r1, g1, b1, a1, r2, g2, b2, a2)
	local retVal = Polycore.ScreenShape_setGradient(self.__ptr, r1, g1, b1, a1, r2, g2, b2, a2)
end

function ScreenShape:clearGradient()
	local retVal =  Polycore.ScreenShape_clearGradient(self.__ptr)
end

function ScreenShape:setShapeSize(newWidth, newHeight)
	local retVal = Polycore.ScreenShape_setShapeSize(self.__ptr, newWidth, newHeight)
end

function ScreenShape:addShapePoint(x, y)
	local retVal = Polycore.ScreenShape_addShapePoint(self.__ptr, x, y)
end



function ScreenShape:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_ScreenShape(self.__ptr)
end
