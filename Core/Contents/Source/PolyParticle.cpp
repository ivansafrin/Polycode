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

Particle::Particle(int particleType, bool isScreenParticle, Material *material, Texture *texture, Mesh *particleMesh) {
	life = 0;
	if(isScreenParticle) {
		createScreenParticle(particleType, texture, particleMesh);		
	} else {
		createSceneParticle(particleType, material, particleMesh);
	}
	
	Reset();
}

void Particle::createSceneParticle(int particleType, Material *material, Mesh *particleMesh) {
	switch(particleType) {
		case BILLBOARD_PARTICLE:
		{
			ScenePrimitive *primitive = new ScenePrimitive(ScenePrimitive::TYPE_PLANE, 1.0f, 1.0f);
			primitive->setMaterial(material);
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
			primitive->setMaterial(material);
			//			primitive->billboardMode = true;
			//			primitive->billboardRoll = true;
			//primitive->depthTest = false;
			//			primitive->backfaceCulled = false;
			particleBody = primitive;						
		}			
			break;
	}
}

void Particle::createScreenParticle(int particleType, Texture *texture, Mesh *particleMesh) {
	
	ScreenShape *primitive = new ScreenShape(ScreenShape::SHAPE_RECT, 1.0f, 1.0f);
	primitive->setTexture(texture);	
	particleBody = primitive;			
	return;
	
	switch(particleType) {
		case BILLBOARD_PARTICLE:
		{
			ScreenShape *primitive = new ScreenShape(ScreenShape::SHAPE_RECT, 1.0f, 1.0f);
//			primitive->setTexture(texture->get)
			particleBody = primitive;			
		}
			break;
		case MESH_PARTICLE: 
		{
//			ScreenMesh *primitive = new ScreenMesh(particleMesh);
//			primitive->cacheToVertexBuffer(true);
//			primitive->setMaterial(texture);
//			particleBody = primitive;						
		}			
			break;
	}	
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