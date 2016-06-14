class "LightShadowInfoBinding"


function LightShadowInfoBinding:__delete()
	if self then Polycode.delete_LightShadowInfoBinding(self.__ptr) end
end
