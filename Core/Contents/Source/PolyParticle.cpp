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

#include "PolyParticle.h"
#include "PolyMesh.h"
#include "PolyPolygon.h"
#include "PolySceneMesh.h"
#include "PolyScreenShape.h"

using namespace Polycode;

Mesh *Particle::billboardMesh = 0;

Particle::Particle(int particleType, bool isScreenParticle, Material *material, Texture *texture, Mesh *particleMesh) {
	life = 0;
	if(isScreenParticle) {
		createScreenParticle(particleType, texture, particleMesh);
	} else {
		createSceneParticle(particleType, material, particleMesh);
	}

	Reset(true);
}

void Particle::createSceneParticle(int particleType, Material *material, Mesh *particleMesh) {
	switch(particleType) {
		case BILLBOARD_PARTICLE:
		{
			if(!billboardMesh) {
				billboardMesh = new Mesh(Mesh::QUAD_MESH);

				Polygon *imagePolygon = new Polygon();
				imagePolygon->addVertex(0,1,0,0,0);
				imagePolygon->addVertex(1,1,0, 1, 0);
				imagePolygon->addVertex(1,0,0, 1, 1);
				imagePolygon->addVertex(0,0,0,0,1);

				billboardMesh->addPolygon(imagePolygon);

				for(int i=0; i < billboardMesh->getPolygonCount(); i++) {
					for(int j=0; j < billboardMesh->getPolygon(i)->getVertexCount(); j++) {
						billboardMesh->getPolygon(i)->getVertex(j)->x = billboardMesh->getPolygon(i)->getVertex(j)->x - (1.0/2.0f);
						billboardMesh->getPolygon(i)->getVertex(j)->z = billboardMesh->getPolygon(i)->getVertex(j)->z - (1.0/2.0f);
					}
				}

				billboardMesh->calculateNormals();
				billboardMesh->arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;
				billboardMesh->arrayDirtyMap[RenderDataArray::COLOR_DATA_ARRAY] = true;
				billboardMesh->arrayDirtyMap[RenderDataArray::TEXCOORD_DATA_ARRAY] = true;
				billboardMesh->arrayDirtyMap[RenderDataArray::NORMAL_DATA_ARRAY] = true;

			} 
			SceneMesh *primitive = new SceneMesh(billboardMesh);
			
			primitive->setMaterial(material);
			primitive->billboardMode = true;
			primitive->billboardRoll = true;
//			primitive->alphaTest = true;
//			primitive->depthTest = false;
			primitive->depthWrite = false;
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
		default:
			assert(0);
		break;
	}
}

void Particle::createScreenParticle(int particleType, Texture *texture, Mesh *particleMesh) {

	ScreenShape *primitive = new ScreenShape(ScreenShape::SHAPE_RECT, 1.0, 1.0f);
	primitive->setTexture(texture);	
//	primitive->billboardMode = true;
//	primitive->billboardRoll = true;

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


void Particle::Reset(bool continuous) {
	if(continuous && life > lifespan) {
		life = life - lifespan;
	} else {
		life = 0;
	}

	perlinPosX = (Number)rand()/RAND_MAX;
	perlinPosY = (Number)rand()/RAND_MAX;
	perlinPosZ = (Number)rand()/RAND_MAX;

}

Particle::~Particle() {

}
