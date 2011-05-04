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
			ParticleEmitter(String imageFile, Mesh *particleMesh, int particleType, int emitterType, Number lifespan, unsigned int numParticles, Vector3 direction, Vector3 gravity, Vector3 deviation);
			virtual ~ParticleEmitter();
		
			void createParticles();
			
			void setRotationSpeed(Number speed);
			void setStartingColor(Color c);
			void setEndingColor(Color c);
			void setParticleBlendingMode(int mode);
			void setDepthWrite(bool val);
			void setDepthTest(bool val);		
			void setAlphaTest(bool val);
		
			void enablePerlin(bool val);
			void setBillboardMode(bool mode);
			void enableEmitter(bool val);
			bool emitterEnabled();
			
			void setEmitterRadius(Number rad);
			void setStartingScaleModifier(Number mod);
			void setEndingScaleModifier(Number mod);
			void setEmitRotationVector(Vector3 rotVector);
			void setEmitRotationDeviance(Vector3 rotVector);
			void setAllAtOnce(bool val);
			
			void Trigger();
			void resetParticle(Particle *particle);
			
			void setPerlinModSize(Number size);
			void setParticleCount(int count);
		
			virtual void addParticleBody(Entity *particleBody) = 0;
			virtual Matrix4 getBaseMatrix() = 0;
		
			Number particleSpeedMod;
			Number brightnessDeviation;
			
			void updateEmitter();

			static const int CONTINUOUS_EMITTER = 0;
			static const int TRIGGERED_EMITTER = 1;
			static const int CLOUD_EMITTER = 2;
			
			Vector3 deviation;
			Vector3 dirVector;
			Vector3 gravVector;			

			Number lifespan;
		
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
			Number emitterRadius;
			Number perlinModSize;
			Perlin *motionPerlin;
			bool perlinEnabled;
			Number startingScaleMod;
			Number endingScaleMod;
			
			Color startingColor;
			Color endingColor;
			
			Number rotationSpeed;
			Number numParticles;
			vector<Particle*> particles;
			
			Number emitSpeed;
			Timer *timer;
	};

	class _PolyExport SceneParticleEmitter : public SceneEntity, public ParticleEmitter {
	public:
		SceneParticleEmitter(String imageFile, Mesh *particleMesh, SceneMesh *emitter, Scene *particleParentScene, int particleType, int emitterType, Number lifespan, unsigned int numParticles, Vector3 direction, Vector3 gravity, Vector3 deviation);
		~SceneParticleEmitter();		
		
		void addParticleBody(Entity *particleBody);
		Matrix4 getBaseMatrix();
		void Update();
		
	protected:
		SceneMesh *emitterMesh;		
		Scene *particleParentScene;
	};	
	
	
	class _PolyExport ScreenParticleEmitter : public ScreenEntity, public ParticleEmitter {
	public:
		ScreenParticleEmitter(String imageFile, Mesh *particleMesh, ScreenMesh *emitter, Screen *particleParentScreen, int particleType, int emitterType, Number lifespan, unsigned int numParticles, Vector3 direction, Vector3 gravity, Vector3 deviation);
		~ScreenParticleEmitter();		
		
		void addParticleBody(Entity *particleBody);
		Matrix4 getBaseMatrix();
		void Update();
		
	protected:
		ScreenMesh *emitterMesh;		
		Screen *particleParentScreen;
	};		
}