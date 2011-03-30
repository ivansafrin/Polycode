require "Polycode/SceneEntity"

class "SceneLine" (SceneEntity)

function SceneLine:SceneLine(ent1, ent2)
	if self.__ptr == nil then
		self.__ptr = Polycore.SceneLine(ent1, ent2)
	end
end

function SceneLine:Render()
	return Polycore.SceneLine_Render(self.__ptr)
end

