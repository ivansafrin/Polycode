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
#include "PolyCore.h"
#include "PolyMesh.h"
#include "PolyRenderer.h"

using namespace Polycode;

SceneParticleEmitter::SceneParticleEmitter(unsigned int particleCount, Number lifetime, Number speed) : SceneMesh(Mesh::POINT_MESH), particleCount(particleCount), particleSpeed(speed), lifetime(lifetime), directionVector(0.0, 1.0, 0.0), timeStep(0.01666), cyclesLeftOver(0.0), useFloorPlane(false), floorPlaneOffset(-1.0), floorDamping(0.5), particlesInWorldSpace(false), perlinEnabled(false), perlinValue(1.0,1.0,1.0), particleType(SceneParticleEmitter::PARTICLE_TYPE_POINT), particleSize(0.1), particleRotationSpeed(0.0, 0.0, 0.0), useColorCurves(false), useScaleCurve(false), loopParticles(true){
    
    core = CoreServices::getInstance()->getCore();
    motionPerlin = new Perlin(3,5,1.0,RANDOM_NUMBER);
    mesh->useVertexColors = true;
    depthWrite = false;
    setParticleCount(particleCount);
    
}

SceneParticleEmitter::~SceneParticleEmitter() {
    delete motionPerlin;
}

void SceneParticleEmitter::resetParticle(unsigned int index) {
    particles[index].lifetime = 0.0;
    q.fromAxes(-directionDeviation.x + (directionDeviation.x * RANDOM_NUMBER * 2.0), -directionDeviation.y + (directionDeviation.y * RANDOM_NUMBER * 2.0), -directionDeviation.z + (directionDeviation.z * RANDOM_NUMBER * 2.0));
    particles[index].velocity = q.applyTo(directionVector);
    particles[index].position = Vector3(-emitterSize.x + (emitterSize.x * RANDOM_NUMBER * 2.0), -emitterSize.y + (emitterSize.y * RANDOM_NUMBER * 2.0), -emitterSize.z + (emitterSize.z * RANDOM_NUMBER * 2.0));
    
    if(particlesInWorldSpace) {
        particles[index].position = systemTrasnformMatrix * particles[index].position;
        particles[index].velocity = systemTrasnformMatrix.rotateVector( particles[index].velocity);
    }
}

void SceneParticleEmitter::setParticleCount(unsigned int newParticleCount) {
    particleCount = newParticleCount;
    particles.resize(particleCount);
    for(int i=0; i < particles.size(); i++) {
        resetParticle(i);
        particles[i].lifetime = RANDOM_NUMBER * lifetime;
        particles[i].perlinPos = Vector3(RANDOM_NUMBER, RANDOM_NUMBER, RANDOM_NUMBER);
        particles[i].brightnessDeviation = 1.0;
        particles[i].scale = 1.0;
    }
}

void SceneParticleEmitter::setGravity(const Vector3 &newGravity) {
    gravity = newGravity;
}

void SceneParticleEmitter::setDirectionDeviation(const Vector3 &newDeviation) {
    directionDeviation = newDeviation;
}

void SceneParticleEmitter::setEmitterSize(const Vector3 &newSize) {
    emitterSize = newSize;
}

void SceneParticleEmitter::setParticleType(unsigned int particleType) {
    this->particleType = particleType;
}

void SceneParticleEmitter::setParticleSize(Number particleSize) {
    this->particleSize = particleSize;
}

void SceneParticleEmitter::setParticleRotationSpeed(const Vector3 &rotationSpeed) {
    particleRotationSpeed = rotationSpeed;
    for(int i=0; i < particles.size(); i++) {
        particles[i].rotation = Vector3();
    }
}

void SceneParticleEmitter::setLoopParticles(bool val) {
    loopParticles = val;
    for(int i=0; i < particles.size(); i++) {
        resetParticle(i);
        particles[i].lifetime = RANDOM_NUMBER * lifetime;
    }
}

bool SceneParticleEmitter::getLoopParticles() const {
    return loopParticles;
}


void SceneParticleEmitter::rebuildParticles() {
    mesh->clearMesh();
    
    switch(particleType) {
        case PARTICLE_TYPE_POINT:
        {
            mesh->setMeshType(Mesh::POINT_MESH);
            Polycode::Polygon *poly = new Polycode::Polygon();
            Matrix4 inverseMatrix = systemTrasnformMatrix.Inverse();
            for(int i=0; i < particles.size(); i++) {
                if(particles[i].lifetime > lifetime) {
                    continue;
                }
                Vector3 vertexPosition = particles[i].position;
                if(particlesInWorldSpace) {
                    vertexPosition = inverseMatrix * vertexPosition;
                }
                poly->addVertex(vertexPosition.x, vertexPosition.y, vertexPosition.z, 0.5, 0.5)->vertexColor = particles[i].color;
            }
            mesh->addPolygon(poly);
        }
        break;
        case PARTICLE_TYPE_QUAD:
        {
            mesh->setMeshType(Mesh::QUAD_MESH);
            Matrix4 inverseMatrix = systemTrasnformMatrix.Inverse();
            Matrix4 cameraMatrix = renderer->getCameraMatrix();
            Quaternion q;
            
            Color vertexColor;
            Number finalParticleSize;
            for(int i=0; i < particles.size(); i++) {
                if(particles[i].lifetime > lifetime) {
                    continue;
                }
                q.fromAxes(particles[i].rotation.x, particles[i].rotation.y, particles[i].rotation.z);
                vertexColor = particles[i].color;
                finalParticleSize = particleSize * particles[i].scale;
                
                Polycode::Polygon *poly = new Polycode::Polygon();
                Vector3 particlePosition = particles[i].position;
                if(particlesInWorldSpace) {
                    particlePosition = inverseMatrix * particlePosition;
                }
                
                Vector3 vertexPosition = Vector3(-finalParticleSize, -finalParticleSize, 0.0);
                vertexPosition = q.applyTo(vertexPosition);
                vertexPosition = cameraMatrix.rotateVector(vertexPosition);
                poly->addVertex(particlePosition.x+vertexPosition.x, particlePosition.y+vertexPosition.y, particlePosition.z+vertexPosition.z, 0.0, 0.0)->vertexColor = vertexColor;
                
                vertexPosition = Vector3(finalParticleSize, -finalParticleSize, 0.0);
                vertexPosition = q.applyTo(vertexPosition);
                vertexPosition = cameraMatrix.rotateVector(vertexPosition);
                poly->addVertex(particlePosition.x+vertexPosition.x, particlePosition.y+vertexPosition.y, particlePosition.z+vertexPosition.z, 1.0, 0.0)->vertexColor = vertexColor;

                vertexPosition = Vector3(finalParticleSize, finalParticleSize, 0.0);
                vertexPosition = q.applyTo(vertexPosition);
                vertexPosition = cameraMatrix.rotateVector(vertexPosition);
                poly->addVertex(particlePosition.x+vertexPosition.x, particlePosition.y+vertexPosition.y, particlePosition.z+vertexPosition.z, 1.0, 1.0)->vertexColor = vertexColor;

                vertexPosition = Vector3(-finalParticleSize, finalParticleSize, 0.0);
                vertexPosition = q.applyTo(vertexPosition);
                vertexPosition = cameraMatrix.rotateVector(vertexPosition);
                poly->addVertex(particlePosition.x+vertexPosition.x, particlePosition.y+vertexPosition.y, particlePosition.z+vertexPosition.z, 0.0, 1.0)->vertexColor = vertexColor;

                
                mesh->addPolygon(poly);

            }
        }
            break;
            
    }
  
    mesh->dirtyArrays();
//    mesh->dirtyArray(RenderDataArray::VERTEX_DATA_ARRAY);
 //   mesh->dirtyArray(RenderDataArray::COLOR_DATA_ARRAY);
}

unsigned int SceneParticleEmitter::getParticleCount() const {
    return particleCount;
}

unsigned int SceneParticleEmitter::getParticleType() const {
    return particleType;
}

void SceneParticleEmitter::setUseFloorPlane(bool val) {
    useFloorPlane = val;
}

void SceneParticleEmitter::setParticlesInWorldSpace(bool val) {
    particlesInWorldSpace = val;
}

void SceneParticleEmitter::setParticleLifetime(Number lifetime) {
    this->lifetime = lifetime;
    for(int i=0; i < particles.size(); i++) {
        resetParticle(i);
        particles[i].lifetime = RANDOM_NUMBER * lifetime;
    }
}

Vector3 SceneParticleEmitter::getDirectionDeviation() const {
    return directionDeviation;
}

Vector3 SceneParticleEmitter::getPerlinValue() const {
    return perlinValue;
}

bool SceneParticleEmitter::getPerlinEnabled() const {
    return perlinEnabled;
}

Vector3 SceneParticleEmitter::getEmitterSize() const {
    return emitterSize;
}

Vector3 SceneParticleEmitter::getGravity() const {
    return gravity;
}

Number SceneParticleEmitter::getParticleLifetime() const {
    return lifetime;
}

bool SceneParticleEmitter::getParticlesInWorldSpace() const {
    return particlesInWorldSpace;
}

Number SceneParticleEmitter::getParticleSize() const {
    return particleSize;
}

void SceneParticleEmitter::setFloorPlaneOffset(Number floorPlaneOffset) {
    this->floorPlaneOffset = floorPlaneOffset;
}

void SceneParticleEmitter::setParticleDirection(const Vector3 &direction) {
    directionVector = direction;
}

Vector3 SceneParticleEmitter::getParticleDirection() const {
    return directionVector;
}

void SceneParticleEmitter::setFloorDamping(Number floorDamping) {
    this->floorDamping = floorDamping;
}

Vector3 SceneParticleEmitter::getParticleRotationSpeed() const {
    return particleRotationSpeed;
}

void SceneParticleEmitter::setPerlinEnabled(bool val) {
    perlinEnabled = val;
}

void SceneParticleEmitter::setPerlinValue(const Vector3 &perlinValue) {
    this->perlinValue = perlinValue;
}

void SceneParticleEmitter::updateParticles() {
    Number normLife;
    
    for(int i=0; i < particles.size(); i++) {
        particles[i].lifetime += timeStep;
        if(particles[i].lifetime > lifetime) {
            if(loopParticles) {
                resetParticle(i);
            }
        }
        
        normLife = particles[i].lifetime / lifetime;
        if(useColorCurves) {
            particles[i].color.setColor(colorCurveR.getHeightAt(normLife)*particles[i].brightnessDeviation,
                                        colorCurveG.getHeightAt(normLife)*particles[i].brightnessDeviation,
                                        colorCurveB.getHeightAt(normLife)*particles[i].brightnessDeviation,
                                        colorCurveA.getHeightAt(normLife)*particles[i].brightnessDeviation);
        } else {
            particles[i].color = color;
        }
        
        if(useScaleCurve) {
            particles[i].scale = scaleCurve.getHeightAt(normLife);
        } else {
            particles[i].scale = 1.0;
        }
        
        particles[i].rotation += particleRotationSpeed *timeStep;
        
        particles[i].velocity += gravity * timeStep;
        particles[i].position += particles[i].velocity * timeStep * particleSpeed;
        if(perlinEnabled) {
            
            particles[i].position += Vector3(motionPerlin->Get((particles[i].lifetime/lifetime), particles[i].perlinPos.x) * perlinValue.x * timeStep, motionPerlin->Get((particles[i].lifetime/lifetime), particles[i].perlinPos.y) * perlinValue.y * timeStep , motionPerlin->Get((particles[i].lifetime/lifetime), particles[i].perlinPos.z) * perlinValue.z * timeStep);
        }
        
        if(useFloorPlane) {
            if(particles[i].position.y <= floorPlaneOffset) {
                particles[i].position.y = floorPlaneOffset;
                particles[i].velocity.y *= -1.0 * floorDamping;
            }
        }
    }
}

void SceneParticleEmitter::Render() {
    rebuildParticles();
    SceneMesh::Render();
}

void SceneParticleEmitter::Update() {
    systemTrasnformMatrix = getConcatenatedMatrix();
    Number elapsed = core->getElapsed() + cyclesLeftOver;
    
    while(elapsed > timeStep) {
        elapsed -= timeStep;
        updateParticles();
    }
    cyclesLeftOver = elapsed;
    SceneMesh::Update();
}
