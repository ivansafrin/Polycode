/*
 *  PolyParticleEmitter.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 7/18/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolyParticleEmitter.h"

using namespace Polycode;

ParticleEmitter::ParticleEmitter(String imageFile, Mesh *particleMesh, SceneMesh *emitter, Scene *particleParentScene, int particleType, int emitterType, float lifespan, unsigned int numParticles,  Vector3 direction, Vector3 gravity, Vector3 deviation) 
: SceneEntity() {
	
	emitterMesh = emitter;
	dirVector = direction;
	gravVector = gravity;
	this->emitterType = emitterType;
	this->particleParentScene = particleParentScene;
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
//	particleTexture = CoreServices::getInstance()->getMaterialManager()->createTextureFromFile(imageFile);	
	particleMaterial = (Material*)CoreServices::getInstance()->getResourceManager()->getResource(Resource::RESOURCE_MATERIAL, imageFile);
	Particle *particle;
	this->numParticles = numParticles;

	this->lifespan = lifespan;
	
	for(int i=0; i < numParticles; i++) {
		particle = new Particle(particleType, particleMaterial,particleMesh);
		particle->velVector = dirVector;
		particle->dirVector = dirVector;
		particle->deviation = deviation;
		particle->lifespan = lifespan;
		particles.push_back(particle);
		particleParentScene->addEntity(particle->particleBody);		
		resetParticle(particle);
		particle->life = lifespan * ((float)rand()/RAND_MAX);		
	}
	timer = new Timer(true, 1);
	
	motionPerlin = new Perlin(3,5,1.0,rand());
	Update();
}

void ParticleEmitter::setEmitterRadius(float rad) {
	emitterRadius = rad;
}

void ParticleEmitter::setEndingColor(Color c) {
	endingColor = c;
}

void ParticleEmitter::setStartingColor(Color c) {
	startingColor = c;
}

void ParticleEmitter::setRotationSpeed(float speed) {
	rotationSpeed = speed;
}

void ParticleEmitter::setStartingScaleModifier(float mod) {
	startingScaleMod = mod;
}

void ParticleEmitter::setEndingScaleModifier(float mod) {
	endingScaleMod = mod;
}

void ParticleEmitter::setBlendingMode(int mode) {
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
		particles[i]->particleBody->setDepthWrite(true);
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
			particle = new Particle(particleType, particleMaterial, pMesh);
			particle->velVector = dirVector;
			particle->dirVector = dirVector;
			particle->deviation = deviation;
			particle->lifespan = lifespan;
			particle->life = lifespan * ((float)rand()/RAND_MAX);
			particles.push_back(particle);
			particleParentScene->addEntity(particle->particleBody);
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

void ParticleEmitter::setPerlinModSize(float size) {
	perlinModSize = size;

}

void ParticleEmitter::enableEmitter(bool val) {
	isEmitterEnabled = val;
	if(val) {
		for(int i=0;i < numParticles; i++) {
			particles[i]->life = particles[i]->lifespan * ((float)rand()/RAND_MAX);
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
	Matrix4 concatMatrix = getConcatenatedMatrix();
	Vector3	startVector;
	if(emitterMesh) {
		Polygon *randPoly = emitterMesh->getMesh()->getPolygon(rand() % emitterMesh->getMesh()->getPolygonCount());		
		startVector = *randPoly->getVertex(rand() % 3);
		startVector = emitterMesh->getConcatenatedMatrix() * startVector;
	} else {
		startVector = Vector3(-(emitterRadius/2.0f)+emitterRadius*((float)rand()/RAND_MAX),-(emitterRadius/2.0f)+emitterRadius*((float)rand()/RAND_MAX),-(emitterRadius/2.0f)+emitterRadius*((float)rand()/RAND_MAX));	
	}
	particle->Reset();	
	particle->velVector = particle->dirVector;
	float dev = ((deviation.x/2.0f)*-1.0f) + ((deviation.x)*((float)rand()/RAND_MAX));
	particle->velVector.x += dev;
	dev = (deviation.y/2.0f*-1.0f) + ((deviation.y)*((float)rand()/RAND_MAX));
	particle->velVector.y += dev;
	dev = (deviation.z/2.0f*-1.0f) + ((deviation.z)*((float)rand()/RAND_MAX));
	particle->velVector.z += dev;
	
	particle->brightnessDeviation = 1.0f - ( (-brightnessDeviation) + ((brightnessDeviation*2) * ((float)rand()/RAND_MAX)));
	
	particle->velVector = concatMatrix.rotateVector(particle->velVector);	
	particle->particleBody->setTransformByMatrix(concatMatrix);
	particle->particleBody->Translate(startVector);
	particle->particleBody->rebuildTransformMatrix();	
	
//	particle->particleBody->setPitch(emitRotationVector.y+(emitRotationDeviance.y*((float)rand()/RAND_MAX)));
//	particle->particleBody->setRoll(emitRotationVector.x+(emitRotationDeviance.x*((float)rand()/RAND_MAX)));
//	particle->particleBody->setYaw(emitRotationVector.z+(emitRotationDeviance.z*((float)rand()/RAND_MAX)));	
	
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
			particles[i]->life = particles[i]->lifespan * ((float)rand()/RAND_MAX);
	}
}

void ParticleEmitter::Update() {
	Vector3 translationVector;
	float elapsed = timer->getElapsedf();
	
	Particle *particle;
	float normLife;
	
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
			particle->particleBody->lookAt(*particle->particleBody->getPosition() + translationVector, Vector3(1,0,0));			
		} else {
			particle->particleBody->Roll(rotationSpeed*elapsed);
			particle->particleBody->Pitch(rotationSpeed*elapsed);
			particle->particleBody->Yaw(rotationSpeed*elapsed);						
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
				particle->particleBody->visible = false;
			}
		}
	}
}