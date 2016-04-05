//
// Polycode template. Write your code here.
// 

#include "PolycodeTemplateApp.h"


PolycodeTemplateApp::PolycodeTemplateApp(PolycodeView *view) {
	core = new POLYCODE_CORE(view, 1280 / 2, 720 / 2, false, false, 0, 0, 60, 0, true);

	core->addFileSource("archive", "default.pak");
	ResourcePool *globalPool = Services()->getResourceManager()->getGlobalPool();
	globalPool->loadResourcesFromFolder("default", true);

	core->addFileSource("archive", "hdr.pak");
	globalPool->loadResourcesFromFolder("hdr", true);


	// Write your code here!

	Scene *scene = new Scene(Scene::SCENE_2D);
	scene->useClearColor = true;
	scene->clearColor.setColor(0.2, 0.2, 0.2, 1.0);


	// scene->setOverrideMaterial((Material*)globalPool->getResource(Resource::RESOURCE_MATERIAL, "Unlit"));

	for (int i = 0; i < 3000; i++) {
		test = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 0.5, 0.5);
		test->setMaterialByName("Unlit");
		test->getShaderPass(0).shaderBinding->loadTextureForParam("diffuse", "main_icon.png");
		test->setPosition(RANDOM_NUMBER * 0.5, RANDOM_NUMBER * 0.4);
		test->setBlendingMode(Renderer::BLEND_MODE_NONE);
		test->setScale(0.3, 0.3);
		scene->addChild(test);
		tests.push_back(test);
	}
	Camera *camera = scene->getDefaultCamera();

	fpsLabel = new SceneLabel("FPS:", 32, "main", Label::ANTIALIAS_FULL, 0.1);
	scene->addChild(fpsLabel);
	fpsLabel->setPositionX(-0.6);
	
	scene->getDefaultCamera()->setPostFilterByName("HDRProcessBloom");

	camera->getShaderPass(0).shaderBinding->addParam(ProgramParam::PARAM_NUMBER, "brightThreshold")->setNumber(0.4);
	camera->getShaderPass(1).shaderBinding->addParam(ProgramParam::PARAM_NUMBER, "blurSize")->setNumber(0.003);
	camera->getShaderPass(2).shaderBinding->addParam(ProgramParam::PARAM_NUMBER, "blurSize")->setNumber(0.003);
	camera->getShaderPass(3).shaderBinding->addParam(ProgramParam::PARAM_NUMBER, "bloomFactor")->setNumber(1.5);
	camera->getShaderPass(3).shaderBinding->addParam(ProgramParam::PARAM_NUMBER, "exposure")->setNumber(0.7);
	

	//scene->getDefaultCamera()->setPostFilterByName("Blur");
	//camera->getShaderPass(0).shaderBinding->addParam(ProgramParam::PARAM_NUMBER, "blurSize")->setNumber(0.003);
	//camera->getShaderPass(1).shaderBinding->addParam(ProgramParam::PARAM_NUMBER, "blurSize")->setNumber(0.003);

	//    Sound *music = new Sound("BUGSHUFFLE.ogg");
	//  music->Play();

	Services()->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
}

void PolycodeTemplateApp::handleEvent(Event *event) {
	InputEvent *inputEvent = (InputEvent*)event;
}

PolycodeTemplateApp::~PolycodeTemplateApp() {

}

bool PolycodeTemplateApp::Update() {
	Number elapsed = core->getElapsed();

	for (int i = 0; i < tests.size(); i++) {
		tests[i]->Roll(elapsed * 45.0);
	}

	if (Services()->getRenderer()->getRenderThread()->getFrameInfo().timeTaken > 0) {
		fpsLabel->setText("FPS:" + String::IntToString(1000 / Services()->getRenderer()->getRenderThread()->getFrameInfo().timeTaken));
	}

	return core->updateAndRender();
}