class "RenderFrame"


function RenderFrame:__delete()
	if self then Polycode.delete_RenderFrame(self.__ptr) end
end
