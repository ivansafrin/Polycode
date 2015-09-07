scene = Scene(Scene.SCENE_2D)
scene:getActiveCamera():setOrthoSize(640, 480)
    
spriteSet = SpriteSet("Resources/sprite_set.sprites", Services.ResourceManager:getGlobalPool())
sceneSprite = SceneSprite(spriteSet)
sceneSprite:setScale(4, 4)
scene:addEntity(sceneSprite)
    
sceneSprite:setSpriteByName("Explosion")
sceneSprite:setSpriteStateByName("default", 0, false)