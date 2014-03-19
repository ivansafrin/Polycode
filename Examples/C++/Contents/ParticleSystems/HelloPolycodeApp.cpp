#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) {

	core = new POLYCODE_CORE(view, 640,480,false,true,0,0,90, 0, true);

	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);
	
	Scene *scene = new Scene(Scene::SCENE_2D);
	SceneParticleEmitter *emitter = new SceneParticleEmitter(100,2.0,0.5);
	
    emitter->setParticleRotationSpeed(Vector3(0.0, 0.0, 100.0));
    
	emitter->useScaleCurve = true;
	emitter->scaleCurve.clearControlPoints();
	emitter->scaleCurve.addControlPoint2d(0, 0.3);
	emitter->scaleCurve.addControlPoint2d(0.5, 1);
	emitter->scaleCurve.addControlPoint2d(1, 0);
	
	emitter->useColorCurves = true;
	emitter->colorCurveR.clearControlPoints();	
	emitter->colorCurveG.clearControlPoints();	
	emitter->colorCurveB.clearControlPoints();	
	emitter->colorCurveA.clearControlPoints();	
				
	emitter->colorCurveR.addControlPoint2d(0, 0.3);
	emitter->colorCurveR.addControlPoint2d(0.1, 1);	
	emitter->colorCurveR.addControlPoint2d(0.4, 1);		
	emitter->colorCurveR.addControlPoint2d(0.5, 0);	
	emitter->colorCurveR.addControlPoint2d(1, 0);
	
	emitter->colorCurveG.addControlPoint2d(0, 0.3);
	emitter->colorCurveG.addControlPoint2d(0.1, 0.6);	
	emitter->colorCurveG.addControlPoint2d(0.4, 0.6);		
	emitter->colorCurveG.addControlPoint2d(0.5, 0);		
	emitter->colorCurveG.addControlPoint2d(1, 0.0);
	
	emitter->colorCurveB.addControlPoint2d(0, 1);
	emitter->colorCurveB.addControlPoint2d(0.1, 0);	
	emitter->colorCurveB.addControlPoint2d(1, 0);
	
	emitter->colorCurveA.addControlPoint2d(0, 0);
	emitter->colorCurveA.addControlPoint2d(0.05, 1);
	emitter->colorCurveA.addControlPoint2d(0.6, 1);
	emitter->colorCurveA.addControlPoint2d(1, 0);
    
    emitter->setPosition(0.0, -0.4, 0.0);
    
    emitter->setMaterialByName("UnlitAdditive");
    
    Texture *tex = CoreServices::getInstance()->getMaterialManager()->createTextureFromFile("Resources/particle.png");
    emitter->getLocalShaderOptions()->addTexture("diffuse", tex);

	scene->addChild(emitter);
}

HelloPolycodeApp::~HelloPolycodeApp() {
}

bool HelloPolycodeApp::Update() {
    return core->updateAndRender();
}

