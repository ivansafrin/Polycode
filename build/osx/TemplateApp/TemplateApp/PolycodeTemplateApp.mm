//
// Polycode template. Write your code here.
// 

#include "PolycodeTemplateApp.h"


PolycodeTemplateApp::PolycodeTemplateApp(PolycodeView *view) {
    core = new CocoaCore(view, 1280/2,720/2,false,false, 0,0,60, 0, true);
    
    core->addFileSource("archive", "lua_Polycode.pak");
    core->addFileSource("archive", "js_Polycode.pak");
    
    core->addFileSource("archive", "default.pak");
    ResourcePool *globalPool = Services()->getResourceManager()->getGlobalPool();
    globalPool->loadResourcesFromFolder("default", true);

    core->addFileSource("archive", "hdr.pak");
    globalPool->loadResourcesFromFolder("hdr", true);
    
	//std::shared_ptr<Script>rotateScript = std::static_pointer_cast<Script>(globalPool->loadResource("rotate.js"));
    
	// Write your code here!
    
    scene = new Scene(Scene::SCENE_2D);
    scene->useClearColor = true;
    scene->clearColor.setColor(0.2, 0.2, 0.2, 1.0);
    
   // scene->setOverrideMaterial((Material*)globalPool->getResource(Resource::RESOURCE_MATERIAL, "Unlit"));
    
    for(int i=0; i  < 2000; i++) {
        
        MeshGeometry geom;
        geom.createVPlane(0.5, 0.5);
        SceneMesh *test = new SceneMesh();
        test->setMaterialByName("Unlit");
        test->getMesh()->addSubmesh(geom);
        
        //test->attachScript(rotateScript);
        /*
         ScriptInstance *scriptInstance = test->attachScript(rotateScript);
         scriptInstance->setPropNumber("speed", 1.0);
         */
        test->getShaderPass(0).shaderBinding->loadTextureForParam("diffuse", "main_icon.png");
        test->setPosition(RANDOM_NUMBER * 0.5, RANDOM_NUMBER * 0.4);
        test->setBlendingMode(Renderer::BLEND_MODE_NONE);
        test->setScale(0.3, 0.3);
        scene->addChild(test);
        tests.push_back(test);
    }
    Camera *camera = scene->getDefaultCamera();

    fpsLabel = new SceneLabel("FPS:", 32, "mono", Label::ANTIALIAS_FULL, 0.1);
    scene->addChild(fpsLabel);
    fpsLabel->setPositionY(-0.4);
    
    Services()->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
}

void PolycodeTemplateApp::handleEvent(Event *event) {
    InputEvent *inputEvent = (InputEvent*) event;
}

PolycodeTemplateApp::~PolycodeTemplateApp() {
    
}

bool PolycodeTemplateApp::Update() {
    Number elapsed = core->getElapsed();
    
    for(int i=0; i < tests.size(); i++) {
        tests[i]->Roll(elapsed * 30.0);
    }
	
    if(tests.size() > 0) {
        SceneMesh *removing = tests[0];
        tests.erase(tests.begin());
        scene->removeEntity(removing);
        delete removing;
        
        MeshGeometry geom;
        geom.createVPlane(0.5, 0.5);
        SceneMesh *test = new SceneMesh();
        test->setMaterialByName("Unlit");
        test->getMesh()->addSubmesh(geom);
        test->getShaderPass(0).shaderBinding->loadTextureForParam("diffuse", "main_icon.png");
        test->setPosition(RANDOM_NUMBER * 0.5, RANDOM_NUMBER * 0.4);
        test->setBlendingMode(Renderer::BLEND_MODE_NONE);
        test->setScale(0.1, 0.1);
        scene->addChild(test);
        tests.push_back(test);
    }
	 
    ++numFrames;
    counter += elapsed;
    if(counter >= 1.0) {
        counter = 0.0;
        fpsLabel->setText("FPS:"+String::IntToString(numFrames)+" FRAME MS:"+String::IntToString(Services()->getRenderer()->getRenderThread()->getFrameInfo().timeTaken));
        numFrames = 0;
    }
	 
    return core->updateAndRender();
}