/*
 *  PolyRadTool.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 9/25/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */


#include "PolyRadTool.h"

using namespace Polycode;

RadTool::RadTool(GenericScene *scene, LightmapPacker *packer) {
	this->scene = scene;
	this->packer = packer;
}

void RadTool::fiatLux(int radPasses) {

	Vector3 baseAmbient(0.033f, 0.033f, 0.033f);
	
	Color col;	
	for(int i=0; i < packer->lumels.size(); i++) {
		packer->lumels[i]->rEnergy.set(baseAmbient.x, baseAmbient.y, baseAmbient.z);
		packer->images[packer->lumels[i]->face->imageID]->setPixel(packer->lumels[i]->u*packer->lightMapRes, packer->lumels[i]->v*packer->lightMapRes, Color(baseAmbient.x, baseAmbient.y, baseAmbient.z, 1.0f));		
	}

//	applyLight(scene->getLight(1));
	for(int i =0; i < scene->getNumLights(); i++) {
		applyLight(scene->getLight(i));
	}

	for(int i=0; i < radPasses; i++) {
		Logger::log("doing radiosity pass %d\n", i);
		doRadiosityPass();
	}
	
}

void RadTool::doRadiosityPass() {
	for(int i=0; i < packer->lumels.size(); i+=1) {
		radLumel(packer->lumels[i], packer->images[packer->lumels[i]->face->imageID]);
	}
}

void RadTool::applyLight(SceneLight *light) {
	for(int i=0; i < packer->lumels.size(); i++) {
		lightLumel(light, packer->images[packer->lumels[i]->face->imageID], packer->lumels[i]);
	}
}

bool RadTool::rayTriangleIntersect(Vector3 ray_origin, Vector3 ray_direction, Vector3 vert0, Vector3 vert1, Vector3 vert2, Vector3 *hitPoint)
{
	float t,u,v;
	 t = 0; u = 0; v = 0;
	 
	 Vector3 edge1 = vert1 - vert0;
	 Vector3 edge2 = vert2 - vert0;
	 
	 Vector3 tvec, pvec, qvec;
	 float det, inv_det;
	 
	 
	 pvec = ray_direction.crossProduct(edge2);
	 det = edge1.dot(pvec);
	 
	 if (det > -0.00001f)
		return false;
	 
	 inv_det = 1.0f / det;
	 
	 tvec = ray_origin - vert0;

//	 hitPoint = tvec;
	 
	 u = tvec.dot(pvec) * inv_det;
	 if (u < -0.001f || u > 1.001f)
		return false;
	 
	 qvec = tvec.crossProduct(edge1);
	 
	 v = ray_direction.dot(qvec) * inv_det;
	 if (v < -0.001f || u + v > 1.001f)
		return false;
	 
	 t = edge2.dot(qvec) * inv_det;
	 
	 if (t <= 0)
		return false;

	hitPoint->x = ray_origin.x+t*ray_direction.x;
	hitPoint->y = ray_origin.y+t*ray_direction.y;
	hitPoint->z = ray_origin.z+t*ray_direction.z;	

	 
	 return true;

}


bool RadTool::worldRayTest(Vector3 origin, Vector3 destination,Poly::Polygon *hitPolygon) {
	Vector3 hitPoint,dirVec;
	dirVec = destination-origin;
	
	for(int i= 0; i < packer->lightmapMeshes.size(); i++) {
		Matrix4 meshMatrix = packer->lightmapMeshes[i]->mesh->getConcatenatedMatrix();
		for(int j=0; j < packer->lightmapMeshes[i]->faces.size(); j++) {
			if(rayTriangleIntersect(origin, dirVec,
				meshMatrix*(*packer->lightmapMeshes[i]->faces[j]->meshPolygon->getVertex(0)),
				meshMatrix*(*packer->lightmapMeshes[i]->faces[j]->meshPolygon->getVertex(1)),
				meshMatrix*(*packer->lightmapMeshes[i]->faces[j]->meshPolygon->getVertex(2)),
				&hitPoint)) {
					float dist =  hitPoint.distance(origin);
					if(dist < destination.distance(origin) && dist > 1.3f) {
						hitPolygon = packer->lightmapMeshes[i]->faces[j]->meshPolygon;
						return true;
					}
			}
		}
		
	}
	return false;
}


void RadTool::radLumel(Lumel *lumel, Image *image) {
	Lumel *lumel2;
	float numSeen = 0;
	float totalVal_r = 0;
	float totalVal_g = 0;
	float totalVal_b = 0;
	
	for(int i=0; i < packer->lumels.size(); i+=1000) {
		lumel2 = packer->lumels[i];
	//	if(!worldRayTest(lumel->worldPos, lumel2->worldPos, hitPoly)) {		
			float dist = lumel2->worldPos.distance(lumel->worldPos);
			Vector3 lightVector = lumel2->worldPos-lumel->worldPos;
			lightVector.Normalize();
			float diffuse = lumel->normal.dot(lightVector);
			float pwr = 1.3f; 
			float val = 1.0f - (dist/45.0f);
			val = val * pwr * diffuse * lumel2->lumelScale;
			totalVal_r += lumel2->rEnergy.x * val;
			totalVal_g += lumel2->rEnergy.y * val;
			totalVal_b += lumel2->rEnergy.z * val;			
			numSeen++;
	//	}
	}
	
	totalVal_r = totalVal_r / numSeen;
	totalVal_g = totalVal_g / numSeen;
	totalVal_b = totalVal_b / numSeen;
		
	if(totalVal_r < 0)
		totalVal_r = 0;
	if(totalVal_g < 0)
		totalVal_g = 0;
	if(totalVal_b < 0)
		totalVal_b = 0;
	
	Color col;
	lumel->rEnergy.x += totalVal_r;
	lumel->rEnergy.y += totalVal_g;
	lumel->rEnergy.z += totalVal_b;
	
	if(lumel->rEnergy.x > 1.0f)
		lumel->rEnergy.x = 1.0f;
	if(lumel->rEnergy.y > 1.0f)
		lumel->rEnergy.y = 1.0f;
	if(lumel->rEnergy.z > 1.0f)
		lumel->rEnergy.z = 1.0f;
	
	
	col.setColor(lumel->rEnergy.x,lumel->rEnergy.y,lumel->rEnergy.z,1.0f);
	image->setPixel(lumel->u*packer->lightMapRes, lumel->v*packer->lightMapRes, col);
				
}

void RadTool::lightLumel(SceneLight *light, Image *image, Lumel *lumel) {
	
	float dist = light->getPosition()->distance(lumel->worldPos);
	
	Vector3 lightVector = (*light->getPosition())-lumel->worldPos;
	lightVector.Normalize();
	float diffuse = lumel->normal.dot(lightVector);
	//float diffuse = 1;
	Polygon *hitPoly;


	if(worldRayTest(lumel->worldPos, *light->getPosition(), hitPoly))
		return;

	float val = ((light->getDistance()) /(dist*dist));
	if(val > 1.0f)
		val = 1.0f;
		
	float pwr = light->getIntensity();

	val = val * pwr * diffuse;
	if(val < 0)
		val = 0;
		
	Color col;
	
	lumel->rEnergy.x += light->lightColor.r*val;
	lumel->rEnergy.y += light->lightColor.g*val;
	lumel->rEnergy.z += light->lightColor.b*val;
	
	if(lumel->rEnergy.x > 1.0f)
		lumel->rEnergy.x = 1.0f;
	if(lumel->rEnergy.y > 1.0f)
		lumel->rEnergy.y = 1.0f;
	if(lumel->rEnergy.z > 1.0f)
		lumel->rEnergy.z = 1.0f;

	
	//lumel->rEnergy.Normalize();
	
	col.setColor(lumel->rEnergy.x,lumel->rEnergy.y,lumel->rEnergy.z,1.0f);
		
	image->setPixel(lumel->u*packer->lightMapRes, lumel->v*packer->lightMapRes, col);
}

RadTool::~RadTool() {
	
}
