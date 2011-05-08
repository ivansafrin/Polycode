require "Polycode/Resource"

class "Cubemap" (Resource)







function Cubemap:Cubemap(...)
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1]:class() == "Resource" then
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
		self.__ptr = Polycore.Cubemap(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end



function Cubemap:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_Cubemap(self.__ptr)
end
