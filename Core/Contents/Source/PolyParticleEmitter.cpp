/*
 Copyright (C) 2011 by Ivan Safrin
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*/

#include "PolyParticleEmitter.h"
#include "PolyCoreServices.h"
#include "PolyParticle.h"
#include "PolyPerlin.h"
#include "PolyResource.h"
#include "PolyScene.h"
#include "PolyScreen.h"
#include "PolyTimer.h"
#include "PolyMaterialManager.h"
#include "PolyResourceManager.h"
#include "PolyScreenMesh.h"
#include "PolyRenderer.h"

using namespace Polycode;

SceneParticleEmitter::SceneParticleEmitter(const String& materialName, int particleType, int emitterType, Number lifespan, unsigned int numParticles, Vector3 direction, Vector3 gravity, Vector3 deviation, Vector3 emitterRadius, Mesh *particleMesh, SceneMesh *emitter)
: SceneEntity(),
ParticleEmitter(materialName, particleMesh, particleType, emitterType, lifespan, numParticles,  direction, gravity, deviation, emitterRadius)
{
	isScreenEmitter = false;
	emitterMesh = emitter;
	createParticles();

}

SceneParticleEmitter::~SceneParticleEmitter() {

}

void SceneParticleEmitter::respawnSceneParticles() {
	for(int i=0; i < particles.size(); i++) {
		Particle *particle = particles[i];
		removeChild((SceneEntity*)particle->particleBody);
		addParticleBody(particle->particleBody);
		resetParticle(particle);
		particle->life = lifespan * ((Number)rand()/RAND_MAX);
	}
	updateEmitter();
}

void SceneParticleEmitter::addParticleBody(Entity *particleBody) {
	addEntity((SceneEntity*)particleBody);
	particleBody->editorOnly = true;
}

void SceneParticleEmitter::dispatchTriggerCompleteEvent() {
	((EventDispatcher*)this)->dispatchEvent(new Event(Event::COMPLETE_EVENT), Event::COMPLETE_EVENT);
}

Matrix4 SceneParticleEmitter::getBaseMatrix() {
	rebuildTransformMatrix();
	return getConcatenatedMatrix();
}

void SceneParticleEmitter::Update() {
	updateEmitter();
}


ScreenParticleEmitter::ScreenParticleEmitter(const String& imageFile, int particleType, int emitterType, Number lifespan, unsigned int numParticles, Vector3 direction, Vector3 gravity, Vector3 deviation, Vector3 emitterRadius, Mesh *particleMesh, ScreenMesh *emitter)
: ScreenEntity(),
ParticleEmitter(imageFile, particleMesh, particleType, emitterType, lifespan, numParticles,  direction, gravity, deviation, emitterRadius)
{
	particleSize = 10.0; 
	isScreenEmitter = true;
	emitterMesh = emitter;
	createParticles();
}

ScreenParticleEmitter::~ScreenParticleEmitter(){ 
	for(int i=0;i < particles.size(); i++) {
		removeChild((ScreenEntity*)particles[i]->particleBody);
		delete particles[i];
	}
}

Entity *ScreenParticleEmitter::Clone(bool deepClone, bool ignoreEditorOnly) {
	ScreenParticleEmitter *newEmitter = new ScreenParticleEmitter("default.png", Particle::BILLBOARD_PARTICLE, ParticleEmitter::CONTINUOUS_EMITTER, 2.0, 0, Vector3(0.0, -40.0, 0.0), Vector3(0.0, 0.0, 0.0), Vector3(0.0, 0.0, 0.0), Vector3(10.0, 10.0, 0.0));
	applyClone(newEmitter, deepClone, ignoreEditorOnly);
	return newEmitter;
}

void ScreenParticleEmitter::applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly) {
	ScreenParticleEmitter *_clone = (ScreenParticleEmitter*) clone;

	_clone->emitterRadius = this->emitterRadius;
	_clone->dirVector = this->dirVector;
	_clone->gravVector = this->gravVector;
	_clone->deviation = this->deviation;

	_clone->setIgnoreParentMatrix(getIgnoreParentMatrix());

	_clone->brightnessDeviation = this->brightnessDeviation;
	_clone->particleSize = this->particleSize;
	_clone->perlinModSize = this->perlinModSize;
	_clone->perlinEnabled = this->perlinEnabled;
	_clone->particleSpeedMod = this->particleSpeedMod;

	_clone->rotationSpeed = this->rotationSpeed;
	_clone->lifespan = this->lifespan;
	_clone->particleSpeedMod = this->particleSpeedMod;
	_clone->setParticleCount(this->getNumParticles());

	_clone->rotationFollowsPath = this->rotationFollowsPath;
	_clone->useScaleCurves = this->useScaleCurves;
	_clone->scaleCurve = this->scaleCurve;

	_clone->useColorCurves = this->useColorCurves;

	_clone->colorCurveR = this->colorCurveR;
	_clone->colorCurveG = this->colorCurveG;
	_clone->colorCurveB = this->colorCurveB;
	_clone->colorCurveA = this->colorCurveA;
	_clone->setParticleBlendingMode(this->getParticleBlendingMode());
	_clone->setParticleTexture(this->getParticleTexture());
	_clone->setWidth(_clone->emitterRadius.x);
	_clone->setHeight(_clone->emitterRadius.y);

	ScreenEntity::applyClone(clone, false, ignoreEditorOnly);
}

void ScreenParticleEmitter::Update() {
	updateEmitter();
}

void ScreenParticleEmitter::addParticleBody(Entity *particleBody) {
	addChild((ScreenEntity*)particleBody);
	particleBody->editorOnly = true;
}

void ScreenParticleEmitter::dispatchTriggerCompleteEvent() {
	((EventDispatcher*)this)->dispatchEvent(new Event(Event::COMPLETE_EVENT), Event::COMPLETE_EVENT);
}

Matrix4 ScreenParticleEmitter::getBaseMatrix() {
	rebuildTransformMatrix();
	return getConcatenatedMatrix();
}

ParticleEmitter::ParticleEmitter(const String& imageFile, Mesh *particleMesh, int particleType, int emitterType, Number lifespan, unsigned int numParticles,  Vector3 direction, Vector3 gravity, Vector3 deviation, Vector3 emitterRadius) {

	this->emitterRadius = emitterRadius;
	isScreenEmitter = false;
	dirVector = direction;
	gravVector = gravity;
	ignoreParentMatrix = false;
	this->emitterType = emitterType;
	// TODO: initialize emitSpeed
	this->deviation = deviation;
	pMesh = particleMesh;
	rotationFollowsPath = false;
	rotationSpeed = 100.0f;
	perlinEnabled = false;
	emitterRadius = Vector3(0.0f,0.0f,0.0f);
	perlinModSize = 0.002;
	brightnessDeviation = 0.0f;
	particleSpeedMod = 1.0f;
	isEmitterEnabled = true;
	allAtOnce = false;

	blendingMode = Renderer::BLEND_MODE_NORMAL;

	particleSize = 1.0;

	scaleCurve.addControlPoint2dWithHandles(-0.1, 0.5, 0.0, 0.5, 0.1, 0.5);
	scaleCurve.addControlPoint2dWithHandles(0.9, 0.5, 1.0, 0.5, 1.1, 0.5);	

	colorCurveR.addControlPoint2dWithHandles(-0.1, 0.5, 0.0, 0.5, 0.1, 0.5);
	colorCurveR.addControlPoint2dWithHandles(0.9, 0.5, 1.0, 0.5, 1.1, 0.5);	

	colorCurveG.addControlPoint2dWithHandles(-0.1, 0.5, 0.0, 0.5, 0.1, 0.5);
	colorCurveG.addControlPoint2dWithHandles(0.9, 0.5, 1.0, 0.5, 1.1, 0.5);	

	colorCurveB.addControlPoint2dWithHandles(-0.1, 0.5, 0.0, 0.5, 0.1, 0.5);
	colorCurveB.addControlPoint2dWithHandles(0.9, 0.5, 1.0, 0.5, 1.1, 0.5);	

	colorCurveA.addControlPoint2dWithHandles(-0.1, 0.5, 0.0, 0.5, 0.1, 0.5);
	colorCurveA.addControlPoint2dWithHandles(0.9, 0.5, 1.0, 0.5, 1.1, 0.5);	


	this->particleType = particleType;

	this->numParticles = numParticles;

	this->lifespan = lifespan;
	timer = new Timer(true, 1);
	motionPerlin = new Perlin(3,5,1.0,rand());

	textureFile = imageFile;

	useColorCurves = false;
	useScaleCurves = false;	
}

bool ParticleEmitter::getIgnoreParentMatrix() {
	return ignoreParentMatrix;
}

void ParticleEmitter::setIgnoreParentMatrix(bool val) {
	ignoreParentMatrix = val;
	for(int i=0; i < particles.size(); i++) {
		particles[i]->particleBody->ignoreParentMatrix = ignoreParentMatrix;
	}
}


Texture *ParticleEmitter::getParticleTexture() {
	return particleTexture;
}

void ParticleEmitter::setParticleTexture(Texture *texture) {
	particleTexture = texture;
	for(int i=0; i < particles.size(); i++) {
		((ScreenMesh*)particles[i]->particleBody)->setTexture(particleTexture);
	}
}

void ParticleEmitter::createParticles() {

	if(isScreenEmitter)
		particleTexture = CoreServices::getInstance()->getMaterialManager()->createTextureFromFile(textureFile);
	else
		particleMaterial = (Material*)CoreServices::getInstance()->getResourceManager()->getResource(Resource::RESOURCE_MATERIAL, textureFile);	


	Particle *particle;
	for(int i=0; i < numParticles; i++) {
		particle = new Particle(particleType, isScreenEmitter, particleMaterial, particleTexture, pMesh);
		particle->particleBody->ignoreParentMatrix = ignoreParentMatrix;
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

void ParticleEmitter::dispatchTriggerCompleteEvent() {
}

void ParticleEmitter::addParticleBody(Entity *particleBody) {
}

Matrix4 ParticleEmitter::getBaseMatrix() {
	return Matrix4();
}

void ParticleEmitter::setEmitterRadius(Vector3 rad) {
	emitterRadius = rad;
}

void ParticleEmitter::setRotationSpeed(Number speed) {
	rotationSpeed = speed;
}

void ParticleEmitter::setParticleVisibility(bool val) {
	for(int i=0;i < particles.size(); i++) {
		particles[i]->particleBody->visible = val;
	}
}

void ParticleEmitter::setParticleBlendingMode(int mode) {
	blendingMode = mode;
	for(int i=0;i < particles.size(); i++) {
		particles[i]->particleBody->setBlendingMode(mode);
	}
}

int ParticleEmitter::getParticleBlendingMode() const {
	return blendingMode;
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
			particle->particleBody->ignoreParentMatrix = ignoreParentMatrix;
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
	resetAll();
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
//	particle->particleBody->visible = true;
	particle->lifespan  = lifespan;
	Matrix4 concatMatrix = getBaseMatrix();

	Vector3	startVector;

	Vector3 compoundScale(1.0, 1.0, 1.0);
	if(ignoreParentMatrix) {
		compoundScale = getParticleCompoundScale();
	}

	particle->dirVector = dirVector;
//	if(emitterMesh) {
//		Polygon *randPoly = emitterMesh->getMesh()->getPolygon(rand() % emitterMesh->getMesh()->getPolygonCount());		
//		startVector = *randPoly->getVertex(rand() % 3);
//		startVector = emitterMesh->getConcatenatedMatrix() * startVector;
//	} else {
	startVector = Vector3(-(emitterRadius.x/2.0f)+emitterRadius.x*((Number)rand()/RAND_MAX),-(emitterRadius.y/2.0f)+emitterRadius.y*((Number)rand()/RAND_MAX),-(emitterRadius.z/2.0f)+emitterRadius.z*((Number)rand()/RAND_MAX));
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

//	particle->velVector = concatMatrix.rotateVector(particle->velVector);	

	if(ignoreParentMatrix) {
		particle->particleBody->setPosition(concatMatrix.getPosition());
	} else {
		particle->particleBody->setPosition(0.0, 0.0, 0.0);
	}

	particle->particleBody->Translate(startVector);
	particle->particleBody->rebuildTransformMatrix();

	if(useScaleCurves) {
		particle->particleBody->setScale(scaleCurve.getHeightAt(0) * particleSize * compoundScale.x,
									 scaleCurve.getHeightAt(0) * particleSize * compoundScale.y,
									 scaleCurve.getHeightAt(0) * particleSize * compoundScale.z);
	} else {
		particle->particleBody->setScale(particleSize  * compoundScale.x, particleSize * compoundScale.y, particleSize * compoundScale.z);
	}

	if(useColorCurves) {
		particle->particleBody->color.setColor(colorCurveR.getHeightAt(0),
										   colorCurveG.getHeightAt(0),
										   colorCurveB.getHeightAt(0),
										   colorCurveA.getHeightAt(0));
	} else {
		particle->particleBody->color.setColor(1.0, 1.0, 1.0, 1.0);
	}


}

Vector3 ScreenParticleEmitter::getParticleCompoundScale() {
	return getCompoundScale();
}

Vector3 SceneParticleEmitter::getParticleCompoundScale() {
	return getCompoundScale();
}


Vector3 ParticleEmitter::getParticleCompoundScale() {
	return Vector3();
}

void ParticleEmitter::resetAll() {
	for(int i=0;i < particles.size(); i++) {
		if(allAtOnce)
			particles[i]->life = 0;
		else
			particles[i]->life = particles[i]->lifespan * ((Number)rand()/RAND_MAX);
	}
}

void ParticleEmitter::setAllAtOnce(bool val) {
	allAtOnce = val;
	resetAll();
}

unsigned int ParticleEmitter::getNumParticles() const {
	return numParticles;
}

Particle *ParticleEmitter::getParticleAtIndex(unsigned int index) const {
	if(index < particles.size()) {
		return particles[index];
	} else {
		return NULL;
	}
}


void ParticleEmitter::updateEmitter() {	

	Vector3 translationVector;
	Number elapsed = timer->getElapsedf();

	Particle *particle;
	Number normLife;

	Vector3 compoundScale(1.0, 1.0, 1.0);
	if(ignoreParentMatrix) {
		compoundScale = getParticleCompoundScale();
	}

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

		if(isScreenEmitter) {
			translationVector.z = 0;
		}

		particle->particleBody->Translate(translationVector);


		if(rotationFollowsPath)  {
			if(isScreenEmitter) {
				Number angle = atan2(translationVector.x, translationVector.y);
				particle->particleBody->setRoll(360 - ((angle * TODEGREES)+180));
			
			} else {
				particle->particleBody->lookAt(particle->particleBody->getPosition() + translationVector, Vector3(1,0,0));
			}
		} else {
			if(isScreenEmitter) {
				particle->particleBody->Roll(rotationSpeed*elapsed);
			} else {
				particle->particleBody->Roll(rotationSpeed*elapsed);
				particle->particleBody->Pitch(rotationSpeed*elapsed);
				particle->particleBody->Yaw(rotationSpeed*elapsed);
			}
		}

//		if(isScreenEmitter)
//			particle->particleBody->setPositionZ(0);

		if(useColorCurves) {
			particle->particleBody->color.setColor(colorCurveR.getHeightAt(normLife)*particle->brightnessDeviation,
											   colorCurveG.getHeightAt(normLife)*particle->brightnessDeviation,
											   colorCurveB.getHeightAt(normLife)*particle->brightnessDeviation,
											   colorCurveA.getHeightAt(normLife)*particle->brightnessDeviation);
		} else {
			particle->particleBody->color.setColor(particle->brightnessDeviation,
											   particle->brightnessDeviation,
											   particle->brightnessDeviation,
											   1.0);
		}

		if(useScaleCurves) {
			particle->particleBody->setScale(scaleCurve.getHeightAt(normLife) * particleSize * compoundScale.x,
										 scaleCurve.getHeightAt(normLife) * particleSize * compoundScale.y,
										 scaleCurve.getHeightAt(normLife) * particleSize * compoundScale.z);

		} else {
			particle->particleBody->setScale(particleSize*compoundScale.x, particleSize*compoundScale.y, particleSize*compoundScale.z);
		}

		if(particle->life > particle->lifespan && isEmitterEnabled) {
			if(emitterType == CONTINUOUS_EMITTER) {
				resetParticle(particle);
			} else {
			//	dispatchTriggerCompleteEvent();
//				particle->particleBody->visible = false;
			}
		}
	}
}
