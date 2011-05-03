require "Polycode/SceneMesh"

class "ScenePrimitive" (SceneMesh)



TYPE_BOX = 0
TYPE_PLANE = 1
TYPE_SPHERE = 2




function ScenePrimitive:ScenePrimitive(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.ScenePrimitive(unpack(arg))
	end
end

