function __is_kind_of(c,T)
	local __baseclass = getmetatable(c)
	while __baseclass do
		if __baseclass.__classname == T.__classname then
			return true
		end
		__baseclass = __baseclass.__baseclass
	end
	return false
end

function __is_class(c, T)
	return (c.__classname == T.__classname)
end

function __are_tables_same_c_class(a,b)
	return __are_same_c_class(a.__ptr,b.__ptr)
end

function class(name)
	local cls = {}
	cls.__classname = name
	
	cls.__eq = __are_tables_same_c_class

	cls.__tostring = function(c)
		return "Class of type "..c.__classname
	end

	cls.__newindex = function(t,k,v)
		retVal = false
		if t["__setvar"] ~= nil then
			retVal = t["__setvar"](t,k,v)
		end
		if retVal == false then
			rawset(t,k,v)
		end
	end

	cls.isKindOfClass = __is_kind_of
	cls.isClass = __is_class

	cls.__index = function(t,k)
		local prototype = rawget(t,"__prototype")
		if prototype ~= nil then
			ret = rawget(prototype,k)
			if ret ~= nil then return ret end
		end

		if k ~= "__index" and k ~= "__getvar" then
			if t["__getvar"] ~= nil then
				local ret = t["__getvar"](t,k)
				if ret ~= nil then return ret end
			end
			return rawget(t,k)
		end
	end

	_G[name] = setmetatable(cls, {
		 __call = function (c, ...)
		local instance = setmetatable({}, cls)
		instance.__prototype = cls
		if cls[name] then
			cls[name](instance, ...)
		end	
		return instance
	end})
	
	return function(superclass)
		if type(superclass) == 'table' then
			cls[superclass.__classname] = {}
			setmetatable(cls[superclass.__classname], superclass)
			for i,v in pairs(superclass) do
				if cls[i] == nil then
					cls[i] = v
				else
					cls[superclass.__classname][i] = v
				end
			end
			cls.__baseclass = superclass
		end
		
	end
end
