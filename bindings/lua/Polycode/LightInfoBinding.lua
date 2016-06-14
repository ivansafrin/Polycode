class "LightInfoBinding"


function LightInfoBinding:__delete()
	if self then Polycode.delete_LightInfoBinding(self.__ptr) end
end
