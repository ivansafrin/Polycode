//
// Polycode template. Write your code here.
// 

#include "PolycodeTemplateApp.h"


PolycodeTemplateApp::PolycodeTemplateApp(PolycodeView *view) {
	core = new POLYCODE_CORE(view, 1280 / 2, 720 / 2, false, false, 0, 0, 60, 0, true);

	core->addFileSource("archive", "default.pak");
	ResourcePool *globalPool = core->getResourceManager()->getGlobalPool();
	globalPool->loadResourcesFromFolder("default", true);

	core->addFileSource("archive", "hdr.pak");
	globalPool->loadResourcesFromFolder("hdr", true);

	scene = new Scene(core, Scene::SCENE_2D);
	scene->useClearColor = true;

	label = new SceneLabel(globalPool->getMaterial("Unlit"), "Hello World", 32, globalPool->getFont("mono"), Label::ANTIALIAS_FULL, 0.1);
	scene->addChild(label);
	/*
	core->addFileSource("archive", "lua_Polycode.pak");
	core->addFileSource("archive", "js_Polycode.pak");
	std::shared_ptr<Script>mainScript = std::static_pointer_cast<Script>(globalPool->loadResource("main.js"));
	*/
}

void PolycodeTemplateApp::handleEvent(Event *event) {
	InputEvent *inputEvent = (InputEvent*)event;
}

PolycodeTemplateApp::~PolycodeTemplateApp() {
	delete core;
}

bool PolycodeTemplateApp::Update() {
	bool res = core->Update();

	label->Roll(core->getElapsed() * 40.0);

	RenderFrame *frame = new RenderFrame(core->getViewport());
	scene->Render(frame, NULL, NULL, NULL, false);
	core->getRenderer()->submitRenderFrame(frame);

	return res;
}