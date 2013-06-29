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
#include "PolyGlobals.h"
#include "PolyString.h"
#include "PolyVector3.h"
#include "PolyMatrix4.h"
#include "PolyBezierCurve.h"
#include "PolySceneEntity.h"
#include "PolyScreenEntity.h"

namespace Polycode {

class Entity;
class Material;
class Mesh;
class Particle;
class Perlin;
class Scene;
class SceneMesh;
class Screen;
class ScreenMesh;
class Texture;
class Timer;

/** 
* Particle emitter base.
*/
class _PolyExport ParticleEmitter {
	public:
		ParticleEmitter(const String& imageFile, Mesh *particleMesh, int particleType, int emitterType, Number lifespan, unsigned int numParticles, Vector3 direction, Vector3 gravity, Vector3 deviation, Vector3 emitterRadius);
		virtual ~ParticleEmitter();

		virtual void dispatchTriggerCompleteEvent();

		void createParticles();

		/**
		* Sets the speed at which particles rotate
		* @param speed New rotation speed.
		*/ 
		void setRotationSpeed(Number speed);

		/**
		* Sets the blending mode used for the particles. See documentation for the Entity for information on blending modes.
		* @param mode New blending mode.
		*/ 
		void setParticleBlendingMode(int mode);

		int getParticleBlendingMode() const;

		/**
		* Turns depth write on and off for particles.
		*/ 
		void setDepthWrite(bool val);

		/**
		* Turns depth test on and off for particles.
		*/
		void setDepthTest(bool val);

		/**
		* Turns alpha testing on and off for particles.
		*/
		void setAlphaTest(bool val);

		/**
		* Enables perlin noise movement for particles.
		*/
		void enablePerlin(bool val);

		/**
		* Sets visibility of all particles in the system
		*/
		void setParticleVisibility(bool val);

		/**
		* Enables perlin noise movement size.
		*/
		void setPerlinModSize(Number size);

		/**
		* Enables or disables billboard mode for particles.
		*/
		void setBillboardMode(bool mode);

		/**
		* Enables or disables the emitter
		*/
		void enableEmitter(bool val);

		/**
		* Returns true if the emitter is enabled, false otherwise.
		*/
		bool emitterEnabled();

		/**
		* Sets the emitter radius on all 3 axises.
		*/
		void setEmitterRadius(Vector3 rad);

		/**
		* If set to true, will release all particles at once.
		*/
		void setAllAtOnce(bool val);


		unsigned int getNumParticles() const;

		Particle *getParticleAtIndex(unsigned int index) const;

		/**
		* If emitter mode is TRIGGERED_EMITTER, calling this method will trigger particle emission.
		*/ 

		void resetAll();

		void Trigger();

		void resetParticle(Particle *particle);

		/**
		* Changes the particle count in the emitter.
		*/
		void setParticleCount(int count);

		virtual Vector3 getParticleCompoundScale();
		virtual void addParticleBody(Entity *particleBody);
		virtual Matrix4 getBaseMatrix();

		/**
		* Particle movement speed multiplier
		*/
		Number particleSpeedMod;

		/**
		* Particle brightness deviation
		*/
		Number brightnessDeviation;

		void updateEmitter();

		/**
		* Continuous emitter setting.
		*/
		static const int CONTINUOUS_EMITTER = 0;

		/**
		* Triggered emitter setting.
		*/
		static const int TRIGGERED_EMITTER = 1;

		/**
		* Particle direction deviation
		*/
		Vector3 deviation;
		/**
		* Particle direction and emission strength vector
		*/
		Vector3 dirVector;

		/**
		* Particle gravity strength vector
		*/
		Vector3 gravVector;

		/**
		* Lifespan of particles.
		*/
		Number lifespan;

		/**
		* If set to true, particles' rotation will follow their movement.
		*/
		bool rotationFollowsPath;

		/**
		* Bezier curve that controls the scale of the particles.
		*/
		BezierCurve scaleCurve;

		/**
		* Bezier curve that controls the red component of particles' color.
		*/
		BezierCurve colorCurveR;
		/**
		* Bezier curve that controls the green component of particles' color.
		*/
		BezierCurve colorCurveG;
		/**
		* Bezier curve that controls the blue component of particles' color.
		*/
		BezierCurve colorCurveB;
		/**
		* Bezier curve that controls the alpha component of particles' color.
		*/
		BezierCurve colorCurveA;

		/**
		* If set to true, will use the color curves to control particle color. False by default.
		*/
		bool useColorCurves;

		/**
		* If set to true, will use the scale curve to control particle scale. False by default.
		*/
		bool useScaleCurves;

		Number particleSize;

		Texture *getParticleTexture();

		void setParticleTexture(Texture *texture);

		Vector3 emitterRadius;

		Number perlinModSize;

		bool perlinEnabled;

		Number rotationSpeed;

		int emitterType;

		bool getIgnoreParentMatrix();
		void setIgnoreParentMatrix(bool val);

	protected:

		bool ignoreParentMatrix;

		int blendingMode;

		bool isScreenEmitter;
		Mesh *pMesh;

		bool allAtOnce;
		int particleType;
		Material *particleMaterial;
		Texture *particleTexture;

		String textureFile;

		bool isEmitterEnabled;


		Perlin *motionPerlin;

		Number numParticles;
		std::vector<Particle*> particles;

		Number emitSpeed;
		Timer *timer;
};

/**
* 3D particle emitter.
*/
class _PolyExport SceneParticleEmitter : public SceneEntity, public ParticleEmitter {
	public:
		/**
		* Constructor.
		* @param materialName Name of the material to use for particles.
		* @param particleParentScene Scene to create particles in.
		* @param particleType Type of particles to create. Can be Particle::BILLBOARD_PARTICLE or Particle::MESH_PARTICLE
		* @param emitterType Type of emitter to create. Can be ParticleEmitter::CONTINUOUS_EMITTER or ParticleEmitter::TRIGGERED_EMITTER
		* @param lifespan Lifetime of particles in seconds.
		* @param numParticles Total number of particles to create.
		* @param direction Direction of the emitter, length of this vector controls emitter strength
		* @param gravity Gravity direction and strength
		* @param deviation Emitter deviation on each axis
		* @param particleMesh If particle type is Particle::MESH_PARTICLE, this must be set to the mesh to use for each particle
		* @param emitter If this is specified, particles will be emitted from this meshe's vertices.
		*/
		SceneParticleEmitter(const String& materialName, int particleType, int emitterType, Number lifespan, unsigned int numParticles, Vector3 direction, Vector3 gravity, Vector3 deviation, Vector3 emitterRadius, Mesh *particleMesh = NULL, SceneMesh *emitter = NULL);
		virtual ~SceneParticleEmitter();

		/**
		* Returns the emitter (helper method for LUA).
		*/ 
		ParticleEmitter *getEmitter() { return this; }

		void respawnSceneParticles();
		void addParticleBody(Entity *particleBody);
		Matrix4 getBaseMatrix();
		void Update();

		Vector3 getParticleCompoundScale();

		void dispatchTriggerCompleteEvent();

			/**
			* Continuous emitter setting.
			*/
			static const int CONTINUOUS_EMITTER = 0;

			/**
			* Triggered emitter setting.
			*/
			static const int TRIGGERED_EMITTER = 1;


	protected:
		SceneMesh *emitterMesh;
	};

	/**
	* 3D particle emitter.
	*/
	class _PolyExport ScreenParticleEmitter : public ScreenEntity, public ParticleEmitter {
	public:
		ScreenParticleEmitter(const String& imageFile, int particleType, int emitterType, Number lifespan, unsigned int numParticles, Vector3 direction, Vector3 gravity, Vector3 deviation, Vector3 emitterRadius, Mesh *particleMesh = NULL, ScreenMesh *emitter = NULL);
		virtual ~ScreenParticleEmitter();

		virtual Entity *Clone(bool deepClone, bool ignoreEditorOnly);
		virtual void applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly);

		/**
		* Returns the emitter (helper method for LUA).
		*/ 
		ParticleEmitter *getEmitter() { return this; }

		void dispatchTriggerCompleteEvent();

		void addParticleBody(Entity *particleBody);
		Matrix4 getBaseMatrix();
		void Update();

		Vector3 getParticleCompoundScale();

		/**
		* Continuous emitter setting.
		*/
		static const int CONTINUOUS_EMITTER = 0;

		/**
		* Triggered emitter setting.
		*/
		static const int TRIGGERED_EMITTER = 1;


	protected:
		ScreenMesh *emitterMesh;
};

}
