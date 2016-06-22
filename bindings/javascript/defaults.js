_core__services__instance = Polycode.CoreServices_getInstance()

Services = {}

Services.Core = new Core("__skip_ptr__")
Services.Core.__ptr = Polycode.CoreServices_getCore(Polycode.CoreServices_getInstance())

Services.Input = Services.Core.getInput()

Services.Renderer = new Renderer("__skip_ptr__")
Services.Renderer.__ptr = Polycode.CoreServices_getRenderer(Polycode.CoreServices_getInstance())

Services.Config = new Config("__skip_ptr__")
Services.Config.__ptr = Polycode.CoreServices_getConfig(Polycode.CoreServices_getInstance())

Services.SceneManager = new SceneManager("__skip_ptr__")
Services.SceneManager.__ptr = Polycode.CoreServices_getSceneManager(Polycode.CoreServices_getInstance())

Services.ResourceManager = new ResourceManager("__skip_ptr__")
Services.ResourceManager.__ptr = Polycode.CoreServices_getResourceManager(Polycode.CoreServices_getInstance())

Services.SoundManager = new SoundManager("__skip_ptr__")
Services.SoundManager.__ptr = Polycode.CoreServices_getSoundManager(Polycode.CoreServices_getInstance())