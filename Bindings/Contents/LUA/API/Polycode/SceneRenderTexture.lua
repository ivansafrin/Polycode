class "SceneRenderTexture"

function SceneRenderTexture:SceneRenderTexture(targetScene, targetCamera, r_enderWidth, r_enderHeight)
	if self.__ptr == nil then
		self.__ptr = Polycore.SceneRenderTexture(targetScene, targetCamera, r_enderWidth, r_enderHeight)
	end
end

function SceneRenderTexture:drawScreen()
	return Polycore.SceneRenderTexture_drawScreen(self.__ptr)
end

function SceneRenderTexture:getTargetTexture()
	return Polycore.SceneRenderTexture_getTargetTexture(self.__ptr)
end

function SceneRenderTexture:getTargetScene()
	return Polycore.SceneRenderTexture_getTargetScene(self.__ptr)
end

function SceneRenderTexture:getTargetCamera()
	return Polycore.SceneRenderTexture_getTargetCamera(self.__ptr)
end

