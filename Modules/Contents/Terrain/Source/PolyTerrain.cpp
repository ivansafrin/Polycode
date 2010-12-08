/*
 *  PolyTerrain.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 2/20/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolyTerrain.h"

using namespace Polycode;

Terrain::Terrain(int type, string heightmapFile, bool smooth, float tileAmt, float xDensity, float zDensity, float sx, float sz, float height) : SceneMesh(Mesh::TRI_MESH) {

	switch(type) {
		case BASIC:
			createBasic(heightmapFile, smooth, tileAmt,xDensity,zDensity,sx,sz,height);
			break;
	}
}

void Terrain::createBasic(string heightmapFile, bool smooth, float tileAmt, float xDensity, float zDensity, float sx, float sz, float height) {
	
	float xStep = sx/xDensity;
	float zStep = sz/zDensity;
	
	float uStep = 1.0f / xDensity * tileAmt;
	float vStep = 1.0f / zDensity * tileAmt;
	
	
	float xOffset = -sx/2.0f;
	float zOffset = -sz/2.0f;
	
	Image *heightImage = new Image(heightmapFile);
	
	terrainDataScale.x = sx / (float)heightImage->getWidth();
	terrainDataScale.z = sz / (float)heightImage->getHeight();
	
	Polygon *poly;
	float hpos;
	
	float imageStepX = floor( (float)heightImage->getWidth()/xDensity);
	float imageStepY = floor((float)heightImage->getHeight()/zDensity);
	
	for(float i=0; i < xDensity; i+=1) {
		for(float j=0; j < zDensity; j+=1) {
			poly = new Polygon();
			
			hpos = height * heightImage->getPixel((imageStepX*i)+imageStepX, imageStepY*j).getBrightness();
			poly->addVertex((xStep*i)+xStep+xOffset, hpos, (zStep * j)+zOffset, (uStep*i) + uStep, vStep*j)->setNormal(0,1,0);
			
			hpos = height * heightImage->getPixel((imageStepX*i), (imageStepY*j)).getBrightness();
			poly->addVertex((xStep*i)+xOffset, hpos, (zStep * j)+zOffset, uStep*i, vStep*j)->setNormal(0,1,0);
			
			hpos = height * heightImage->getPixel(imageStepX*i, (imageStepY*j)+imageStepY).getBrightness();			
			poly->addVertex((xStep*i)+xOffset, hpos, ((zStep*j)+zStep)+zOffset, uStep*i, (vStep*j)+vStep)->setNormal(0,1,0);								
			
			mesh->addPolygon(poly);
			if(!smooth) {
				poly->calculateNormal();
				poly->useVertexNormals = true;
			}
			
			poly = new Polygon();			
			
			hpos = height * heightImage->getPixel(imageStepX*i, (imageStepY*j)+imageStepY).getBrightness();			
			poly->addVertex((xStep*i)+xOffset, hpos, (zStep*j)+zStep+zOffset, uStep*i, (vStep*j)+vStep)->setNormal(0,1,0);
			
			hpos = height * heightImage->getPixel((imageStepX*i)+imageStepX, (imageStepY*j)+imageStepY).getBrightness();						
			poly->addVertex((xStep*i)+xStep+xOffset, hpos, (zStep*j)+zStep+zOffset, (uStep*i) + uStep, (vStep*j)+vStep)->setNormal(0,1,0);			
			
			hpos = height * heightImage->getPixel((imageStepX*i)+imageStepX, (imageStepY*j)).getBrightness();			
			poly->addVertex((xStep*i)+xStep+xOffset, hpos, (zStep * j)+zOffset, (uStep*i) + uStep, vStep*j)->setNormal(0,1,0);
			
			mesh->addPolygon(poly);
			if(!smooth) {
				poly->calculateNormal();
				poly->useVertexNormals = true;
			}
		}
	}	
}

Terrain::~Terrain() {
	
}
