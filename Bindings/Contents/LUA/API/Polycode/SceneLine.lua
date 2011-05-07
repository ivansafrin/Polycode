require "Polycode/SceneEntity"

class "SceneLine" (SceneEntity)







function SceneLine:SceneLine(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.SceneLine(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function SceneLine:Render()
	local retVal =  Polycore.SceneLine_Render(self.__ptr)
end

