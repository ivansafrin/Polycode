class "GlyphData"



function GlyphData:__getvar(name)
	if name == "glyphs" then
		local retVal = Polycore.GlyphData_get_glyphs(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["FT_Glyph"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "positions" then
		local retVal = Polycore.GlyphData_get_positions(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["FT_Vector"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "num_glyphs" then
		local retVal = Polycore.GlyphData_get_num_glyphs(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["FT_UInt"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "trailingAdvance" then
		return Polycore.GlyphData_get_trailingAdvance(self.__ptr)
	end
end


function GlyphData:__setvar(name,value)
	if name == "num_glyphs" then
		Polycore.GlyphData_set_num_glyphs(self.__ptr, value.__ptr)
		return true
	elseif name == "trailingAdvance" then
		Polycore.GlyphData_set_trailingAdvance(self.__ptr, value)
		return true
	end
	return false
end


function GlyphData:GlyphData(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.GlyphData(unpack(arg))
	end
end

function GlyphData:clearData()
	local retVal =  Polycore.GlyphData_clearData(self.__ptr)
end

function GlyphData:__delete()
	if self then Polycore.delete_GlyphData(self.__ptr) end
end
