class "TweenManager"

function TweenManager:TweenManager()
	if self.__ptr == nil then
		self.__ptr = Polycore.TweenManager()
	end
end

function TweenManager:addTween(tween)
	return Polycore.TweenManager_addTween(self.__ptr, tween.__ptr)
end

function TweenManager:Update()
	return Polycore.TweenManager_Update(self.__ptr)
end

