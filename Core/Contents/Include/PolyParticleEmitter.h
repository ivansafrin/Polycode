/*
 *  PolyParticleEmitter.h
 *  Poly
 *
 *  Created by Ivan Safrin on 7/18/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

// @package Scene

#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolyEntity.h"
#include "PolyScenePrimitive.h"
#include "PolyScreenMesh.h"
#include "PolyCoreServices.h"
#include "PolyParticle.h"
#include <vector>

using std::vector;

namespace Polycode {
	class _PolyExport ParticleEmitter {
		public:
			ParticleEmitter(String imageFile, Mesh *particleMesh, int particleType, int emitterType, float lifespan, unsigned int numParticles, Vector3 direction, Vector3 gravity, Vector3 deviation);
			virtual ~ParticleEmitter();
		
			void createParticles();
			
			void setRotationSpeed(float speed);
			void setStartingColor(Color c);
			void setEndingColor(Color c);
			void setParticleBlendingMode(int mode);
			void setDepthWrite(bool val);
			void setAlphaTest(bool val);
		
			void enablePerlin(bool val);
			void setBillboardMode(bool mode);
			void enableEmitter(bool val);
			bool emitterEnabled();
			
			void setEmitterRadius(float rad);
			void setStartingScaleModifier(float mod);
			void setEndingScaleModifier(float mod);
			void setEmitRotationVector(Vector3 rotVector);
			void setEmitRotationDeviance(Vector3 rotVector);
			void setAllAtOnce(bool val);
			
			void Trigger();
			void resetParticle(Particle *particle);
			
			void setPerlinModSize(float size);
			void setParticleCount(int count);
		
			virtual void addParticleBody(Entity *particleBody) = 0;
			virtual Matrix4 getBaseMatrix() = 0;
		
			float particleSpeedMod;
			float brightnessDeviation;
			
			void updateEmitter();

			static const int CONTINUOUS_EMITTER = 0;
			static const int TRIGGERED_EMITTER = 1;
			static const int CLOUD_EMITTER = 2;
			
			Vector3 deviation;
			Vector3 dirVector;
			Vector3 gravVector;			

			float lifespan;
		
			bool rotationFollowsPath;
		
			BezierCurve scaleCurve;
		
			BezierCurve colorCurveR;
			BezierCurve colorCurveG;
			BezierCurve colorCurveB;
			BezierCurve colorCurveA;
		
		protected:
		
			bool isScreenEmitter;
			Mesh *pMesh;
		
			bool allAtOnce;
			int emitterType;
			int particleType;
			Material *particleMaterial;
			Texture *particleTexture;
		
			String textureFile;
		
			bool isEmitterEnabled;
		
			Vector3 emitRotationVector;
			Vector3 emitRotationDeviance;
			float emitterRadius;
			float perlinModSize;
			Perlin *motionPerlin;
			bool perlinEnabled;
			float startingScaleMod;
			float endingScaleMod;
			
			Color startingColor;
			Color endingColor;
			
			float rotationSpeed;
			float numParticles;
			vector<Particle*> particles;
			
			float emitSpeed;
			Timer *timer;
	};

	
	class _PolyExport ScreenParticleEmitter : public ScreenEntity, public ParticleEmitter {
	public:
		ScreenParticleEmitter(String imageFile, Mesh *particleMesh, ScreenMesh *emitter, Screen *particleParentScreen, int particleType, int emitterType, float lifespan, unsigned int numParticles, Vector3 direction, Vector3 gravity, Vector3 deviation);
		~ScreenParticleEmitter();		
		
		void addParticleBody(Entity *particleBody);
		Matrix4 getBaseMatrix();
		void Update();
		
	protected:
		ScreenMesh *emitterMesh;		
		Screen *particleParentScreen;
	};		
}