//
// Polycode template. Write your code here.
// 

#include "PolycodeTemplateApp.h"


PolycodeTemplateApp::PolycodeTemplateApp(PolycodeView *view) {
    core = new POLYCODE_CORE(view, 1280,720,false,false, 0,0,60);
    
    //core->addFileSource("archive", "default.pak");
    ResourcePool *globalPool = Services()->getResourceManager()->getGlobalPool();
    globalPool->loadResourcesFromFolder("default", true);
    
	SceneLabel::createMipmapsForLabels = false;

	MaterialManager *materialManager = Services()->getMaterialManager();

	// Write your code here!
    
    Scene *scene = new Scene(Scene::SCENE_2D);
    scene->useClearColor = true;
    
    ScenePrimitive *test = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 0.5, 0.5);
    test->setMaterialByName("Unlit");
    test->getLocalShaderOptions()->loadTextureForParam("diffuse", "main_icon.png");
    scene->addChild(test);

	SceneLabel *testLabel = new SceneLabel("O", 32, "sans", Label::ANTIALIAS_FULL, 0.2);
	scene->addChild(testLabel);
	

	test->getLocalShaderOptions()->setTextureForParam("diffuse", testLabel->getLocalShaderOptions()->getLocalParamByName("diffuse")->getTexture());
//	testLabel->getLocalShaderOptions()->setTextureForParam("diffuse", test->getLocalShaderOptions()->getLocalParamByName("diffuse")->getTexture());
    
}

PolycodeTemplateApp::~PolycodeTemplateApp() {
    
}

bool PolycodeTemplateApp::Update() {
    return core->updateAndRender();
}