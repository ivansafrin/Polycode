/*
 *  PolyParticleEmitter.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 7/18/08.
 *  Copyright 2008 Ivan Safrin. All rights reserved.
 *
 */

#include "PolyParticleEmitter.h"

using namespace Polycode;

SceneParticleEmitter::SceneParticleEmitter(String imageFile, Mesh *particleMesh, SceneMesh *emitter, Scene *particleParentScene, int particleType, int emitterType, Number lifespan, unsigned int numParticles, Vector3 direction, Vector3 gravity, Vector3 deviation)
: ParticleEmitter(imageFile, particleMesh, particleType, emitterType, lifespan, numParticles,  direction, gravity, deviation),
SceneEntity()
{
	isScreenEmitter = false;
	emitterMesh = emitter;	
	this->particleParentScene = particleParentScene;	
	createParticles();	
}

SceneParticleEmitter::~SceneParticleEmitter() {
	
}

void SceneParticleEmitter::addParticleBody(Entity *particleBody) {
	particleParentScene->addEntity((SceneEntity*)particleBody);	
}

Matrix4 SceneParticleEmitter::getBaseMatrix() {
	return getConcatenatedMatrix();	
}

void SceneParticleEmitter::Update() {
	updateEmitter();
}


ScreenParticleEmitter::ScreenParticleEmitter(String imageFile, Mesh *particleMesh, ScreenMesh *emitter, Screen *particleParentScreen, int particleType, int emitterType, Number lifespan, unsigned int numParticles, Vector3 direction, Vector3 gravity, Vector3 deviation) 
: ParticleEmitter(imageFile, particleMesh, particleType, emitterType, lifespan, numParticles,  direction, gravity, deviation),
ScreenEntity()
{
	isScreenEmitter = true;
	emitterMesh = emitter;	
	this->particleParentScreen = particleParentScreen;	
	createParticles();
}

ScreenParticleEmitter::~ScreenParticleEmitter(){ 
	
}

void ScreenParticleEmitter::Update() {
	updateEmitter();
}

void ScreenParticleEmitter::addParticleBody(Entity *particleBody) {
	particleParentScreen->addChild((ScreenEntity*)particleBody);
}

Matrix4 ScreenParticleEmitter::getBaseMatrix() {
	return getConcatenatedMatrix();
}

ParticleEmitter::ParticleEmitter(String imageFile, Mesh *particleMesh, int particleType, int emitterType, Number lifespan, unsigned int numParticles,  Vector3 direction, Vector3 gravity, Vector3 deviation)  {
	
	isScreenEmitter = false;
	dirVector = direction;
	gravVector = gravity;
	this->emitterType = emitterType;
	this->emitSpeed = emitSpeed;
	this->deviation = deviation;
	pMesh = particleMesh;
	rotationFollowsPath = false;
	rotationSpeed = 0.0f;
	startingColor.setColor(1.0f,1.0f,1.0f,1.0f);
	endingColor.setColor(1.0f,1.0f,1.0f,1.0f);	
	perlinEnabled = false;
	startingScaleMod = 1.0f;
	endingScaleMod = 1.0f;
	emitterRadius = 0.0f;
	perlinModSize = 0.002;
	brightnessDeviation = 0.0f;
	particleSpeedMod = 1.0f;
	emitRotationVector.set(0.0f, 0.0f, 0.0f);
	emitRotationDeviance.set(360.0f, 360.0f, 360.0f);
	isEmitterEnabled = true;
	allAtOnce = false;
	
	this->particleType = particleType;
	
	this->numParticles = numParticles;

	this->lifespan = lifespan;
	timer = new Timer(true, 1);	
	motionPerlin = new Perlin(3,5,1.0,rand());
	
	textureFile = imageFile;
}

void ParticleEmitter::createParticles() {
	
//	if(isScreenEmitter)
		particleTexture = CoreServices::getInstance()->getMaterialManager()->createTextureFromFile(textureFile);	
//	else
//		particleMaterial = (Material*)CoreServices::getInstance()->getResourceManager()->getResource(Resource::RESOURCE_MATERIAL, textureFile);	
	
	
	Particle *particle;	
	for(int i=0; i < numParticles; i++) {
		particle = new Particle(particleType, isScreenEmitter, particleMaterial, particleTexture, pMesh);
		particle->velVector = dirVector;
		particle->dirVector = dirVector;
		particle->deviation = deviation;
		particle->lifespan = lifespan;
		particles.push_back(particle);
		addParticleBody(particle->particleBody);					
		resetParticle(particle);
		particle->life = lifespan * ((Number)rand()/RAND_MAX);		
	}
	updateEmitter();	
}

void ParticleEmitter::setEmitterRadius(Number rad) {
	emitterRadius = rad;
}

void ParticleEmitter::setEndingColor(Color c) {
	endingColor = c;
}

void ParticleEmitter::setStartingColor(Color c) {
	startingColor = c;
}

void ParticleEmitter::setRotationSpeed(Number speed) {
	rotationSpeed = speed;
}

void ParticleEmitter::setStartingScaleModifier(Number mod) {
	startingScaleMod = mod;
}

void ParticleEmitter::setEndingScaleModifier(Number mod) {
	endingScaleMod = mod;
}

void ParticleEmitter::setParticleBlendingMode(int mode) {
	for(int i=0;i < particles.size(); i++) {
		particles[i]->particleBody->setBlendingMode(mode);
	}
}

void ParticleEmitter::setAlphaTest(bool val) {
	for(int i=0;i < particles.size(); i++) {
		particles[i]->particleBody->alphaTest = val;
	}		
}

void ParticleEmitter::setDepthWrite(bool val) {
	for(int i=0;i < particles.size(); i++) {
		particles[i]->particleBody->depthWrite = val;
	}	
}

void ParticleEmitter::setDepthTest(bool val) {
	for(int i=0;i < particles.size(); i++) {
		particles[i]->particleBody->depthTest= val;
	}	
}


void ParticleEmitter::setBillboardMode(bool mode) {
	for(int i=0;i < particles.size(); i++) {
		particles[i]->particleBody->billboardMode = mode;
	}
}

void ParticleEmitter::setEmitRotationVector(Vector3 rotVector) {
	emitRotationVector = rotVector;
}

void ParticleEmitter::setEmitRotationDeviance(Vector3 rotVector) {
	emitRotationDeviance = rotVector;
}

void ParticleEmitter::enablePerlin(bool val) {
	perlinEnabled = val;
}

ParticleEmitter::~ParticleEmitter() {
	
}

void ParticleEmitter::setParticleCount(int count) {
	if(count > particles.size()) {
		int oldSize  = count-particles.size();
		Particle *particle;
		for(int i=0; i  < oldSize; i++) {
			particle = new Particle(particleType, isScreenEmitter, particleMaterial, particleTexture, pMesh);
			particle->velVector = dirVector;
			particle->dirVector = dirVector;
			particle->deviation = deviation;
			particle->lifespan = lifespan;
			particle->life = lifespan * ((Number)rand()/RAND_MAX);
			particles.push_back(particle);
			addParticleBody(particle->particleBody);
		}
	}
	numParticles = count;
	for(int i=0; i < particles.size(); i++) {
		if(i < numParticles)
			particles[i]->particleBody->visible =true;
		else
			particles[i]->particleBody->visible = false;
	}

}

void ParticleEmitter::setPerlinModSize(Number size) {
	perlinModSize = size;

}

void ParticleEmitter::enableEmitter(bool val) {
	isEmitterEnabled = val;
	if(val) {
		for(int i=0;i < numParticles; i++) {
			particles[i]->life = particles[i]->lifespan * ((Number)rand()/RAND_MAX);
		}
	}
}

void ParticleEmitter::Trigger() {
	if(!isEmitterEnabled)
		return;
	for(int i=0;i < numParticles; i++) {
			resetParticle(particles[i]);
	}
}

bool ParticleEmitter::emitterEnabled() {
	return isEmitterEnabled;
}

void ParticleEmitter::resetParticle(Particle *particle) {
	particle->particleBody->visible = true;
	particle->lifespan  = lifespan;
	Matrix4 concatMatrix = getBaseMatrix();
	Vector3	startVector;
	
//	if(emitterMesh) {
//		Polygon *randPoly = emitterMesh->getMesh()->getPolygon(rand() % emitterMesh->getMesh()->getPolygonCount());		
//		startVector = *randPoly->getVertex(rand() % 3);
//		startVector = emitterMesh->getConcatenatedMatrix() * startVector;
//	} else {
		startVector = Vector3(-(emitterRadius/2.0f)+emitterRadius*((Number)rand()/RAND_MAX),-(emitterRadius/2.0f)+emitterRadius*((Number)rand()/RAND_MAX),-(emitterRadius/2.0f)+emitterRadius*((Number)rand()/RAND_MAX));	
//	}
	
	particle->Reset(emitterType != TRIGGERED_EMITTER);	
	particle->velVector = particle->dirVector;
	Number dev = ((deviation.x/2.0f)*-1.0f) + ((deviation.x)*((Number)rand()/RAND_MAX));
	particle->velVector.x += dev;
	dev = (deviation.y/2.0f*-1.0f) + ((deviation.y)*((Number)rand()/RAND_MAX));
	particle->velVector.y += dev;
	dev = (deviation.z/2.0f*-1.0f) + ((deviation.z)*((Number)rand()/RAND_MAX));
	particle->velVector.z += dev;
	
	particle->brightnessDeviation = 1.0f - ( (-brightnessDeviation) + ((brightnessDeviation*2) * ((Number)rand()/RAND_MAX)));
	
	particle->velVector = concatMatrix.rotateVector(particle->velVector);	
	particle->particleBody->setTransformByMatrix(concatMatrix);
	particle->particleBody->Translate(startVector);
	particle->particleBody->rebuildTransformMatrix();	
	
//	particle->particleBody->setPitch(emitRotationVector.y+(emitRotationDeviance.y*((Number)rand()/RAND_MAX)));
//	particle->particleBody->setRoll(emitRotationVector.x+(emitRotationDeviance.x*((Number)rand()/RAND_MAX)));
//	particle->particleBody->setYaw(emitRotationVector.z+(emitRotationDeviance.z*((Number)rand()/RAND_MAX)));	
	
	particle->particleBody->setScale(scaleCurve.getHeightAt(0),
									 scaleCurve.getHeightAt(0),
									 scaleCurve.getHeightAt(0));

	particle->particleBody->color.setColor(colorCurveR.getHeightAt(0),
										   colorCurveG.getHeightAt(0),
										   colorCurveB.getHeightAt(0),
										   colorCurveA.getHeightAt(0));
	
			
}

void ParticleEmitter::setAllAtOnce(bool val) {
	allAtOnce = val;
	for(int i=0;i < particles.size(); i++) {
		if(allAtOnce)
			particles[i]->life = 0;
		else
			particles[i]->life = particles[i]->lifespan * ((Number)rand()/RAND_MAX);
	}
}

void ParticleEmitter::updateEmitter() {	
	
	Vector3 translationVector;
	Number elapsed = timer->getElapsedf();
	
	Particle *particle;
	Number normLife;
	
	for(int i=0;i < numParticles; i++) {				
		particle = particles[i];
		
		normLife = particle->life / particle->lifespan;
		Vector3 gVec = gravVector;
		particle->life += elapsed;
		particle->velVector -= gVec*elapsed*particleSpeedMod;
		translationVector = particle->velVector;
		translationVector = translationVector*elapsed*particleSpeedMod;
		if(perlinEnabled) {
			translationVector.x += ((perlinModSize * motionPerlin->Get((particle->life/particle->lifespan), particle->perlinPosX))*elapsed*particleSpeedMod);
			translationVector.y += ((perlinModSize * motionPerlin->Get((particle->life/particle->lifespan), particle->perlinPosY))*elapsed*particleSpeedMod);
			translationVector.z += ((perlinModSize * motionPerlin->Get((particle->life/particle->lifespan), particle->perlinPosZ))*elapsed*particleSpeedMod);
		}
		
		particle->particleBody->Translate(translationVector);
		
		if(rotationFollowsPath)  {
			particle->particleBody->lookAt(particle->particleBody->getPosition() + translationVector, Vector3(1,0,0));			
		} else {
			if(isScreenEmitter) {
				particle->particleBody->Roll(rotationSpeed*elapsed);
			} else {
				particle->particleBody->Roll(rotationSpeed*elapsed);
				particle->particleBody->Pitch(rotationSpeed*elapsed);
				particle->particleBody->Yaw(rotationSpeed*elapsed);						
			}
		}		
		
		particle->particleBody->color.setColor(colorCurveR.getHeightAt(normLife)*particle->brightnessDeviation,
											   colorCurveG.getHeightAt(normLife)*particle->brightnessDeviation,
											   colorCurveB.getHeightAt(normLife)*particle->brightnessDeviation,
											   colorCurveA.getHeightAt(normLife)*particle->brightnessDeviation);
											   		

		particle->particleBody->setScale(scaleCurve.getHeightAt(normLife),
										 scaleCurve.getHeightAt(normLife),
										 scaleCurve.getHeightAt(normLife));
		
		if(particle->life > particle->lifespan && isEmitterEnabled) {
			if(emitterType == CONTINUOUS_EMITTER) {
				resetParticle(particle);
			} else {
//				particle->particleBody->visible = false;
			}
		}
	}
}