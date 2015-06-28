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

SceneParticleEmitter::SceneParticleEmitter(unsigned int particleCount, Number lifetime, Number speed) : SceneMesh(Mesh::POINT_MESH), particleCount(particleCount), particleSpeed(speed), lifetime(lifetime), directionVector(0.0, 1.0, 0.0), useFloorPlane(false), floorPlaneOffset(-1.0), floorDamping(0.5), particlesInWorldSpace(false), perlinEnabled(false), perlinValue(1.0,1.0,1.0), particleType(SceneParticleEmitter::PARTICLE_TYPE_QUAD), particleSize(0.1), particleRotationSpeed(0.0, 0.0, 0.0), useColorCurves(false), useScaleCurve(false), loopParticles(true){
    
    core = CoreServices::getInstance()->getCore();
    motionPerlin = new Perlin(3,5,1.0,RANDOM_NUMBER);
    mesh->useVertexColors = true;
    depthWrite = false;
    systemEnabled = true;
    setParticleCount(particleCount);
    colorDeviation = Color(0.0, 0.0, 0.0, 0.0);
}

SceneParticleEmitter::~SceneParticleEmitter() {
    delete motionPerlin;
}

Entity *SceneParticleEmitter::Clone(bool deepClone, bool ignoreEditorOnly) const {
    SceneParticleEmitter *newEmitter = new SceneParticleEmitter(1, 1, 1);
    applyClone(newEmitter, deepClone, ignoreEditorOnly);
    return newEmitter;
}

void SceneParticleEmitter::addSourceMesh(Mesh *mesh) {
    sourceMeshes.push_back(mesh);
}

int SceneParticleEmitter::getNumSourceMeshes() {
    return sourceMeshes.size();
}

Mesh *SceneParticleEmitter::getSourcesMeshAtIndex(int index) {
    if(index > 0 && index < sourceMeshes.size()) {
        return sourceMeshes[index];
    }
	return NULL;
}

void SceneParticleEmitter::removeSourceMeshAtIndex(int index) {
    if(index > 0 && index < sourceMeshes.size()) {
        sourceMeshes.erase(sourceMeshes.begin() + index);
    }
}

void SceneParticleEmitter::applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly) const {
    
    SceneMesh::applyClone(clone, deepClone, ignoreEditorOnly);
    
    SceneParticleEmitter *cloneEmitter = (SceneParticleEmitter*) clone;
    
    cloneEmitter->setParticleCount(particleCount);
    cloneEmitter->setParticleSpeed(particleSpeed);
    cloneEmitter->setParticleLifetime(lifetime);
    cloneEmitter->setParticleDirection(directionVector);
    cloneEmitter->setDirectionDeviation(directionDeviation);
    cloneEmitter->setEmitterSize(emitterSize);
    cloneEmitter->setGravity(gravity);
    cloneEmitter->setUseFloorPlane(useFloorPlane);
    cloneEmitter->setParticlesInWorldSpace(particlesInWorldSpace);
    cloneEmitter->setPerlinEnabled(perlinEnabled);
    cloneEmitter->setPerlinValue(perlinValue);
    cloneEmitter->setParticleSize(particleSize);
    cloneEmitter->setFloorPlaneOffset(floorPlaneOffset);
    cloneEmitter->setFloorDamping(floorDamping);
    cloneEmitter->setLoopParticles(loopParticles);
    cloneEmitter->setParticleType(particleType);
    
    cloneEmitter->scaleCurve = scaleCurve;
    cloneEmitter->useScaleCurve = useScaleCurve;

    cloneEmitter->colorCurveR = colorCurveR;
    cloneEmitter->colorCurveG = colorCurveG;
    cloneEmitter->colorCurveB = colorCurveB;
    cloneEmitter->colorCurveA = colorCurveA;
    cloneEmitter->useColorCurves = useColorCurves;
    
    cloneEmitter->getMesh()->useVertexColors = true;
}

void SceneParticleEmitter::resetParticle(unsigned int index) {
    particles[index].lifetime = 0.0;
    
    if(sourceMeshes.size() > 0) {
        particles[index].varianceIndex = rand() % sourceMeshes.size();
    } else {
        particles[index].varianceIndex = 0;
    }
    
    positionParticle(index);
    
    particles[index].rotation = Vector3(RANDOM_NUMBER * 360.0 *particleRotationSpeed.x, RANDOM_NUMBER * 360.0 *particleRotationSpeed.y, RANDOM_NUMBER * 360.0 *particleRotationSpeed.z);
    
    
    particles[index].color = Color(1.0 - (RANDOM_NUMBER*colorDeviation.r),
                                   1.0 - (RANDOM_NUMBER*colorDeviation.g),
                                   1.0 - (RANDOM_NUMBER*colorDeviation.b),
                                   1.0 - (RANDOM_NUMBER*colorDeviation.a));
}

void SceneParticleEmitter::positionParticle(unsigned int index) {
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
        particles[i].lifetime = RANDOM_NUMBER * -lifetime;
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
        resetParticle(i);
        particles[i].lifetime = RANDOM_NUMBER * -lifetime;
    }
}

void SceneParticleEmitter::setLoopParticles(bool val) {
    loopParticles = val;
    for(int i=0; i < particles.size(); i++) {
        resetParticle(i);
        particles[i].lifetime = RANDOM_NUMBER * -lifetime;
    }
}

bool SceneParticleEmitter::getLoopParticles() const {
    return loopParticles;
}

void SceneParticleEmitter::enableParticleSystem(bool val) {
    if(systemEnabled == val) {
        return;
    }

    systemEnabled = val;
    if(val) {
        for(int i=0; i < particles.size(); i++) {
            resetParticle(i);
            particles[i].lifetime = RANDOM_NUMBER * -lifetime;
        }
    }
}

void SceneParticleEmitter::rebuildParticles() {
    mesh->clearMesh();
    Matrix4 inverseMatrix = systemTrasnformMatrix.Inverse();
    
    switch(particleType) {
        case PARTICLE_TYPE_POINT:
        {
            mesh->setMeshType(Mesh::POINT_MESH);
            for(int i=0; i < particles.size(); i++) {
                if(particles[i].lifetime > lifetime || particles[i].lifetime < 0.0) {
                    continue;
                }
                Vector3 vertexPosition = particles[i].position;
                if(particlesInWorldSpace) {
                    vertexPosition = inverseMatrix * vertexPosition;
                }
                mesh->addVertexWithUV(vertexPosition.x, vertexPosition.y, vertexPosition.z, 0.5, 0.5);
                mesh->addColor(particles[i].color);
            }
        }
        break;
        case PARTICLE_TYPE_MESH:
        case PARTICLE_TYPE_QUAD:
        {
            Matrix4 cameraMatrix = renderer->getCameraMatrix();
            Quaternion q;
            
            Color vertexColor;
            Number finalParticleSize;
            for(int i=0; i < particles.size(); i++) {
                if(particles[i].lifetime > lifetime || particles[i].lifetime < 0.0) {
                    continue;
                }
                q.fromAxes(particles[i].rotation.x, particles[i].rotation.y, particles[i].rotation.z);
                vertexColor = particles[i].color;
                finalParticleSize = particleSize * particles[i].scale;
                
                Vector3 particlePosition = particles[i].position;
                if(particlesInWorldSpace) {
                    particlePosition = inverseMatrix * particlePosition;
                }
                
                if(particleType == PARTICLE_TYPE_MESH) {
                    mesh->setMeshType(Mesh::TRI_MESH);
                    
                    int indexOffset = 0;

					mesh->indexedMesh = true;
                    
                    int meshIndex = particles[i].varianceIndex;
                    if(meshIndex < sourceMeshes.size()) {
                        
						indexOffset = mesh->vertexPositionArray.data.size()/3;
                        
						Mesh *sourceMesh = sourceMeshes[meshIndex];

						mesh->setMeshType(sourceMesh->getMeshType());

                        for(int v=0; v <  sourceMesh->getVertexCount(); v++) {
                           
							Vector3 vpos = Vector3(sourceMesh->vertexPositionArray.data[(v * 3)], sourceMesh->vertexPositionArray.data[(v * 3)+1], sourceMesh->vertexPositionArray.data[(v * 3)+2]) * finalParticleSize;
                            vpos = q.applyTo(vpos);
                            
                            vpos += particlePosition;
							mesh->addVertex(vpos.x, vpos.y, vpos.z);
							mesh->addTexCoord(sourceMesh->vertexTexCoordArray.data[(v * 2)], sourceMesh->vertexTexCoordArray.data[(v * 2) + 1]);
							mesh->addColor(vertexColor);
							Vector3 svNormal = Vector3(sourceMesh->vertexNormalArray.data[(v * 3)], sourceMesh->vertexNormalArray.data[(v * 3) + 1], sourceMesh->vertexNormalArray.data[(v * 3) + 2]);
							svNormal = q.applyTo(svNormal);
							mesh->addNormal(svNormal.x, svNormal.y, svNormal.z);
                        }
                        
						for (int v = 0; v < sourceMesh->indexArray.data.size(); v++) {
							mesh->addIndex(indexOffset + sourceMesh->indexArray.data[v]);
                        }
                         
                    }
                    
                } else {
                    mesh->setMeshType(Mesh::QUAD_MESH);
                    
                    Vector3 vertexPosition = Vector3(-finalParticleSize, -finalParticleSize, 0.0);
                    vertexPosition = q.applyTo(vertexPosition);
                    vertexPosition = cameraMatrix.rotateVector(vertexPosition);
                    mesh->addVertexWithUV(particlePosition.x+vertexPosition.x, particlePosition.y+vertexPosition.y, particlePosition.z+vertexPosition.z, 0.0, 0.0);
                    mesh->addColor(vertexColor);
                    
                    vertexPosition = Vector3(finalParticleSize, -finalParticleSize, 0.0);
                    vertexPosition = q.applyTo(vertexPosition);
                    vertexPosition = cameraMatrix.rotateVector(vertexPosition);
                    mesh->addVertexWithUV(particlePosition.x+vertexPosition.x, particlePosition.y+vertexPosition.y, particlePosition.z+vertexPosition.z, 1.0, 0.0);
                    mesh->addColor(vertexColor);

                    vertexPosition = Vector3(finalParticleSize, finalParticleSize, 0.0);
                    vertexPosition = q.applyTo(vertexPosition);
                    vertexPosition = cameraMatrix.rotateVector(vertexPosition);
                    mesh->addVertexWithUV(particlePosition.x+vertexPosition.x, particlePosition.y+vertexPosition.y, particlePosition.z+vertexPosition.z, 1.0, 1.0);
                    mesh->addColor(vertexColor);

                    vertexPosition = Vector3(-finalParticleSize, finalParticleSize, 0.0);
                    vertexPosition = q.applyTo(vertexPosition);
                    vertexPosition = cameraMatrix.rotateVector(vertexPosition);
                    mesh->addVertexWithUV(particlePosition.x+vertexPosition.x, particlePosition.y+vertexPosition.y, particlePosition.z+vertexPosition.z, 0.0, 1.0);
                    mesh->addColor(vertexColor);
                }

            }
        }
            break;
            
    }
    
    if(useVertexBuffer) {
		CoreServices::getInstance()->getRenderer()->createVertexBufferForMesh(mesh);
    }
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
        particles[i].lifetime = RANDOM_NUMBER * -lifetime;
    }
}

void SceneParticleEmitter::triggerParticles(bool allAtOnce) {
    for(int i=0; i < particles.size(); i++) {
        resetParticle(i);
        if(allAtOnce) {
            particles[i].lifetime = 0.0;
        } else {
            particles[i].lifetime = RANDOM_NUMBER * -lifetime;
        }
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

Number SceneParticleEmitter::getParticleSpeed() const {
    return particleSpeed;
}

void SceneParticleEmitter::setParticleSpeed(Number speed) {
    particleSpeed = speed;
}

void SceneParticleEmitter::setPerlinValue(const Vector3 &perlinValue) {
    this->perlinValue = perlinValue;
}

void SceneParticleEmitter::updateParticles() {
    
    Matrix4 inverseMatrix = systemTrasnformMatrix.Inverse();
    
    Number normLife;
    Vector3 newBBox;
    
    Number timeStep = core->getFixedTimestep();
    
    for(int i=0; i < particles.size(); i++) {
        if(particles[i].lifetime < 0.0 && particles[i].lifetime + timeStep >= 0.0) {
            positionParticle(i);
        }

        if(particles[i].lifetime >= 0.0 || (particles[i].lifetime < 0.0 && systemEnabled)) {
            particles[i].lifetime += timeStep;
        }
        if(particles[i].lifetime > lifetime) {
            if(loopParticles && systemEnabled) {
                resetParticle(i);
            }
        }
        
        if(particles[i].lifetime < 0.0) {
            continue;
        }
        
        normLife = particles[i].lifetime / lifetime;
        if(useColorCurves) {
            particles[i].color.setColor(colorCurveR.getYValueAtX(normLife)*particles[i].brightnessDeviation,
                                        colorCurveG.getYValueAtX(normLife)*particles[i].brightnessDeviation,
                                        colorCurveB.getYValueAtX(normLife)*particles[i].brightnessDeviation,
                                        colorCurveA.getYValueAtX(normLife)*particles[i].brightnessDeviation);
        }
        
        if(useScaleCurve) {
            particles[i].scale = scaleCurve.getYValueAtX(normLife);
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
        
        Vector3 bBoxTest = particles[i].position;
        if(particlesInWorldSpace) {
            bBoxTest = inverseMatrix * bBoxTest;
        }
        
        if(fabs(bBoxTest.x) > newBBox.x) {
            newBBox.x = fabs(bBoxTest.x);
        }
        if(fabs(bBoxTest.y) > newBBox.y) {
            newBBox.y = fabs(bBoxTest.y);
        }
        if(fabs(bBoxTest.z) > newBBox.z) {
            newBBox.z = fabs(bBoxTest.z);
        }
    }
    
    setLocalBoundingBox((newBBox + Vector3(particleSize, particleSize, particleSize))* 2.0);
}

void SceneParticleEmitter::Render() {
    systemTrasnformMatrix = getConcatenatedMatrix();
    rebuildParticles();
    SceneMesh::Render();
}

void SceneParticleEmitter::fixedUpdate() {
    systemTrasnformMatrix = getConcatenatedMatrix();
    updateParticles();
    SceneMesh::Update();
}
