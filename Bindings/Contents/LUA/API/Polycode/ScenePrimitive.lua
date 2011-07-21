require "Polycode/SceneMesh"

class "ScenePrimitive" (SceneMesh)



TYPE_BOX = 0
TYPE_PLANE = 1
TYPE_SPHERE = 2
TYPE_CYLINDER = 3
TYPE_CONE = 4
TYPE_VPLANE = 5
TYPE_TORUS = 6




function ScenePrimitive:ScenePrimitive(...)
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1]:class() == "SceneMesh" then
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
		self.__ptr = Polycore.ScenePrimitive(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end



function ScenePrimitive:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_ScenePrimitive(self.__ptr)
end
