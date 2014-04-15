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
#include "PolySceneMesh.h"
#include "PolyCore.h"
#include "PolyPerlin.h"
#include "PolyBezierCurve.h"

namespace Polycode {
    
    class SceneParticle {
        public:
            Number lifetime;
            Vector3 position;
            Vector3 velocity;
            Vector3 perlinPos;
            Vector3 rotation;
            Number brightnessDeviation;
            Number scale;
            Color color;
            int varianceIndex;
    };
    
    class SceneParticleEmitter : public SceneMesh {
        public:
            SceneParticleEmitter(unsigned int particleCount, Number lifetime, Number speed);
            virtual ~SceneParticleEmitter();
        
            void setParticleCount(unsigned int newParticleCount);
            unsigned int getParticleCount() const;
        
            void setParticleLifetime(Number lifetime);
            Number getParticleLifetime() const;
        
            void setDirectionDeviation(const Vector3 &newDeviation);
            Vector3 getDirectionDeviation() const;
        
            void setEmitterSize(const Vector3 &newSize);
            Vector3 getEmitterSize() const;
        
            void setGravity(const Vector3 &newGravity);
            Vector3 getGravity() const;
        
            void Update();
            void Render();
        
            void updateParticles();
            void rebuildParticles();
        
            void triggerParticles(bool allAtOnce);
        
            void enableParticleSystem(bool val);
        
            void setUseFloorPlane(bool val);
            void setFloorPlaneOffset(Number floorPlaneOffset);
            void setFloorDamping(Number floorDamping);
        
            void setParticlesInWorldSpace(bool val);
            bool getParticlesInWorldSpace() const;
        
            void setPerlinEnabled(bool val);
            bool getPerlinEnabled() const;
        
            Number getParticleSpeed() const;
            void setParticleSpeed(Number speed);
        
            void setPerlinValue(const Vector3 &perlinValue);
            Vector3 getPerlinValue() const;
        
            void setParticleType(unsigned int particleType);
            unsigned int getParticleType() const;
        
            void setParticleSize(Number particleSize);
            Number getParticleSize() const;
        
            void setParticleRotationSpeed(const Vector3 &rotationSpeed);
            Vector3 getParticleRotationSpeed() const;
        
            void setParticleDirection(const Vector3 &direction);
            Vector3 getParticleDirection() const;
        
            void setLoopParticles(bool val);
            bool getLoopParticles() const;
        
            static const int PARTICLE_TYPE_POINT = 0;
            static const int PARTICLE_TYPE_QUAD = 1;
            static const int PARTICLE_TYPE_MESH = 2;
        
            bool useScaleCurve;
        
            /**
             * Bezier curve that controls the scale of the particles.
             */
            BezierCurve scaleCurve;
        
            bool useColorCurves;

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
        
        
            Color colorDeviation;
        
            void addSourceMesh(Mesh *mesh);
            int getNumSourceMeshes();
            Mesh *getSourcesMeshAtIndex(int index);
            void removeSourceMeshAtIndex(int index);
        
            virtual Entity *Clone(bool deepClone, bool ignoreEditorOnly) const;
            virtual void applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly) const;
        
        protected:
        
            std::vector<Mesh*> sourceMeshes;
            void resetParticle(unsigned int index);
        
            bool systemEnabled;
            Core *core;
            unsigned int particleCount;
            std::vector<SceneParticle> particles;
            Number particleSpeed;
            Number lifetime;
            Number timeStep;
            Number cyclesLeftOver;
        
            Vector3 directionVector;
            Vector3 directionDeviation;
            Vector3 emitterSize;
            Vector3 gravity;
        
            Matrix4 systemTrasnformMatrix;
            bool useFloorPlane;
            bool particlesInWorldSpace;
            bool perlinEnabled;
            Vector3 perlinValue;
            Perlin *motionPerlin;
            Number particleSize;
            Vector3 particleRotationSpeed;
        
            Number floorPlaneOffset;
            Number floorDamping;
        
            bool loopParticles;
        
            unsigned int particleType;
            Quaternion q;
    };
    
}