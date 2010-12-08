/*
 *  PolyParticle.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 7/18/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolyParticle.h"

using namespace Polycode;

Particle::Particle(int particleType, Material *texture, Mesh *particleMesh) {
	switch(particleType) {
		case BILLBOARD_PARTICLE:
		{
			ScenePrimitive *primitive = new ScenePrimitive(ScenePrimitive::TYPE_PLANE, 1.0f, 1.0f);
			primitive->setMaterial(texture);
			primitive->billboardMode = true;
			primitive->billboardRoll = true;
			primitive->setDepthWrite(false);
			primitive->backfaceCulled = false;
			particleBody = primitive;			
		}
		break;
		case MESH_PARTICLE: 
		{
			SceneMesh *primitive = new SceneMesh(particleMesh);
			if(particleMesh->getMeshType() == Mesh::TRI_MESH)
				primitive->cacheToVertexBuffer(true);
			primitive->setMaterial(texture);
			//			primitive->billboardMode = true;
			//			primitive->billboardRoll = true;
			//primitive->depthTest = false;
			//			primitive->backfaceCulled = false;
			particleBody = primitive;						
		}			
		break;
	}
	life = 0;
	Reset();
}

void Particle::Reset() {
	if(life > lifespan)
		life = 0 + (life - lifespan);
	else
		life = 0;

	perlinPosX = (float)rand()/RAND_MAX;
	perlinPosY = (float)rand()/RAND_MAX;
	perlinPosZ = (float)rand()/RAND_MAX;
	
}

Particle::~Particle() {

}