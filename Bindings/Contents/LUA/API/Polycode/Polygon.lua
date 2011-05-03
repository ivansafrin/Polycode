class "Polygon"



function Polygon:__index__(name)
	if name == "useVertexNormals" then
		return Polycore.Polygon_get_useVertexNormals(self.__ptr)
	elseif name == "hasSecUVs" then
		return Polycore.Polygon_get_hasSecUVs(self.__ptr)
	end
end


function Polygon:__set_callback(name,value)
	if name == "useVertexNormals" then
		Polycore.Polygon_set_useVertexNormals(self.__ptr, value)
		return true
	elseif name == "hasSecUVs" then
		Polycore.Polygon_set_hasSecUVs(self.__ptr, value)
		return true
	end
	return false
end


function Polygon:Polygon(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.Polygon(unpack(arg))
	end
end

function Polygon:getVertexCount()
	local retVal =  Polycore.Polygon_getVertexCount(self.__ptr)
	return retVal
end

function Polygon:getVertex(index)
	local retVal = Polycore.Polygon_getVertex(self.__ptr, index)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Vertex("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Polygon:addVertex(x, y, z)
	local retVal = Polycore.Polygon_addVertex(self.__ptr, x, y, z)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Vertex("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Polygon:removeVertex(index)
	local retVal = Polycore.Polygon_removeVertex(self.__ptr, index)
end

function Polygon:addTexCoord(u, v)
	local retVal = Polycore.Polygon_addTexCoord(self.__ptr, u, v)
end

function Polygon:addTexCoord2(u, v)
	local retVal = Polycore.Polygon_addTexCoord2(self.__ptr, u, v)
end

function Polygon:getTexCoord(index)
	local retVal = Polycore.Polygon_getTexCoord(self.__ptr, index)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Vector2("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Polygon:getTexCoord2(index)
	local retVal = Polycore.Polygon_getTexCoord2(self.__ptr, index)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Vector2("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Polygon:calculateNormal()
	local retVal =  Polycore.Polygon_calculateNormal(self.__ptr)
end

function Polygon:getFaceNormal()
	local retVal =  Polycore.Polygon_getFaceNormal(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Vector3("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Polygon:getBounds2D()
	local retVal =  Polycore.Polygon_getBounds2D(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Rectangle("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Polygon:setNormal(normal)
	local retVal = Polycore.Polygon_setNormal(self.__ptr, normal.__ptr)
end

function Polygon:flipUVY()
	local retVal =  Polycore.Polygon_flipUVY(self.__ptr)
end

function Polygon:setUseFaceUV(val)
	local retVal = Polycore.Polygon_setUseFaceUV(self.__ptr, val)
end

function Polygon:usesFaceUV()
	local retVal =  Polycore.Polygon_usesFaceUV(self.__ptr)
	return retVal
end

