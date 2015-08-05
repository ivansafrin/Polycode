#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) : EventHandler() {
	core = new POLYCODE_CORE(view, 640,480,false,true,0,0,90, 0, true);

	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

	CoreServices::getInstance()->getRenderer()->setTextureFilteringMode(Renderer::TEX_FILTERING_NEAREST);
    
	Scene *scene = new Scene(Scene::SCENE_2D);
    scene->getActiveCamera()->setOrthoSize(640, 480);
    
	SpriteSet *sprite = new SpriteSet("Resources/sprite_set.sprites");
	SceneSprite *sceneSprite = new SceneSprite(sprite);
	sceneSprite->setSpriteByName("Explosion");
	sceneSprite->setSpriteStateByName("default", 0, false);
	sceneSprite->setScale(4, 4);
	scene->addEntity(sceneSprite);
}

HelloPolycodeApp::~HelloPolycodeApp() {
}

bool HelloPolycodeApp::Update() {
    return core->updateAndRender();
}
