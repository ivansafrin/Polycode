
for k,v in pairs(math) do _G[k]=v end for k,v in pairs(table) do _G[k]=v end
_G["count"]=_G["getn"]

Polycore.__ptr_lookup = {}

Services = {}

Services.Core = Core("__skip_ptr__")
Services.Core.__ptr = Polycore.CoreServices_getCore(Polycore.CoreServices_getInstance())

Services.Renderer = Renderer("__skip_ptr__")
Services.Renderer.__ptr = Polycore.CoreServices_getRenderer(Polycore.CoreServices_getInstance())

Services.MaterialManager = MaterialManager("__skip_ptr__")
Services.MaterialManager.__ptr = Polycore.CoreServices_getMaterialManager(Polycore.CoreServices_getInstance())

Services.ScreenManager = ScreenManager("__skip_ptr__")
Services.ScreenManager.__ptr = Polycore.CoreServices_getScreenManager(Polycore.CoreServices_getInstance())

Services.SceneManager = SceneManager("__skip_ptr__")
Services.SceneManager.__ptr = Polycore.CoreServices_getSceneManager(Polycore.CoreServices_getInstance())

Services.TimerManager = TimerManager("__skip_ptr__")
Services.TimerManager.__ptr = Polycore.CoreServices_getTimerManager(Polycore.CoreServices_getInstance())

Services.TweenManager = TweenManager("__skip_ptr__")
Services.TweenManager.__ptr = Polycore.CoreServices_getTweenManager(Polycore.CoreServices_getInstance())

Services.ResourceManager = ResourceManager("__skip_ptr__")
Services.ResourceManager.__ptr = Polycore.CoreServices_getResourceManager(Polycore.CoreServices_getInstance())

Services.SoundManager = SoundManager("__skip_ptr__")
Services.SoundManager.__ptr = Polycore.CoreServices_getSoundManager(Polycore.CoreServices_getInstance())

Services.FontManager = FontManager("__skip_ptr__")
Services.FontManager.__ptr = Polycore.CoreServices_getFontManager(Polycore.CoreServices_getInstance())




function Update(e)
end

