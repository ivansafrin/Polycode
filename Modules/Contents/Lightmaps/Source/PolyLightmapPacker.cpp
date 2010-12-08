/*
 *  LightmapPacker.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 9/24/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */


#include "PolyLightmapPacker.h"

using namespace Polycode;

LightmapPacker::LightmapPacker(GenericScene *targetScene) {
	this->targetScene = targetScene;
	currentImageID = -1;
}

LightmapPacker::~LightmapPacker() {
	
}

void LightmapPacker::unwrapScene() {
	for(int i=0; i < targetScene->getNumStaticGeometry(); i++) {
		LightmapMesh *newLMesh = new LightmapMesh;
		newLMesh->processed = false;
		newLMesh->mesh = targetScene->getStaticGeometry(i);
		lightmapMeshes.push_back(newLMesh);
		
		for(int j=0; j < targetScene->getStaticGeometry(i)->getMesh()->getPolygonCount(); j++) {
			Polygon *poly = targetScene->getStaticGeometry(i)->getMesh()->getPolygon(j);
			Vector3 fnormal = poly->getFaceNormal();
			Polygon *flatPoly = new Polygon();
			Polygon *flatUnscaled = new Polygon();
			LightmapFace *newFace = new LightmapFace;
			fnormal.x = fabsf(fnormal.x);
			fnormal.y = fabsf(fnormal.y);
			fnormal.z = fabsf(fnormal.z);
			//			Logger::log("fnormal: %f %f %f\n", fnormal.x, fnormal.y, fnormal.z);
			if(fnormal.x > fnormal.y && fnormal.x > fnormal.z) {
				for(int k=0; k < poly->getVertexCount(); k++) {
					flatPoly->addVertex((poly->getVertex(k)->y*lightMapQuality)/lightMapRes, (poly->getVertex(k)->z*lightMapQuality)/lightMapRes, 0);
					flatUnscaled->addVertex(poly->getVertex(k)->y, poly->getVertex(k)->z, 0);
				}
				newFace->projectionAxis = LightmapFace::X_PROJECTION;
			} else if (fnormal.y > fnormal.x && fnormal.y > fnormal.z) {
				for(int k=0; k < poly->getVertexCount(); k++) {
					flatPoly->addVertex((poly->getVertex(k)->x*lightMapQuality)/lightMapRes, (poly->getVertex(k)->z*lightMapQuality)/lightMapRes, 0);
					flatUnscaled->addVertex(poly->getVertex(k)->x, poly->getVertex(k)->z, 0);
				}	
				newFace->projectionAxis = LightmapFace::Y_PROJECTION;						
			} else {
				for(int k=0; k < poly->getVertexCount(); k++) {
					flatPoly->addVertex((poly->getVertex(k)->x*lightMapQuality)/lightMapRes, (poly->getVertex(k)->y*lightMapQuality)/lightMapRes, 0);
					flatUnscaled->addVertex(poly->getVertex(k)->x, poly->getVertex(k)->y, 0);
				}
				newFace->projectionAxis = LightmapFace::Z_PROJECTION;							
			}
			
			newFace->area = flatPoly->getBounds2D();
			float offx = newFace->area.x;
			float offy = newFace->area.y;
			newFace->area.x = 0;
			newFace->area.y = 0;
			
			// now align the flat face to 0,0
			for(int k=0; k < flatPoly->getVertexCount(); k++) {
				flatPoly->getVertex(k)->x -= offx;
				flatPoly->getVertex(k)->y -= offy;
//				flatPoly->getVertex(k)->x *= 1.1;
//				flatPoly->getVertex(k)->y *= 1.2;
			}
			
			
			newFace->meshPolygon = poly;
			newFace->flatPolygon = flatPoly;
			newFace->flatUnscaledPolygon = flatUnscaled;
			
			newFace->actualArea.w = (newFace->area.w * lightMapRes) / lightMapQuality;
			newFace->actualArea.h = (newFace->area.h * lightMapRes) / lightMapQuality;
			
			float lumelScale = 1.0f;
			float maxSize = 0.4f;
			
			if(newFace->area.w > maxSize || newFace->area.h > maxSize) {
				//		Logger::log("WARNING, NORMALIZING FACE AREA (%f %f)\n", newFace->area.w, newFace->area.h);
				float tmp;
				if(newFace->area.w > newFace->area.h) {
					tmp = newFace->area.w;
					newFace->area.w = maxSize;
					newFace->area.h = newFace->area.h * (maxSize/tmp);
				} else {
					tmp = newFace->area.h;
					newFace->area.h = maxSize;
					newFace->area.w = newFace->area.w * (maxSize/tmp);			
				}
				lumelScale = (1.0f / (maxSize/tmp)) * 100;
				for(int v=0; v < newFace->flatPolygon->getVertexCount(); v++) {
					newFace->flatPolygon->getVertex(v)->x = newFace->flatPolygon->getVertex(v)->x * (maxSize/tmp);
					newFace->flatPolygon->getVertex(v)->y = newFace->flatPolygon->getVertex(v)->y * (maxSize/tmp);
				}
			}


//			newFace->area.w += (4.0f/lightMapRes);
//			newFace->area.h += (4.0f/lightMapRes);
			
			newFace->pixelArea.w = (newFace->area.w * lightMapRes)+2;
			newFace->pixelArea.h = (newFace->area.h * lightMapRes)+2;

//			newFace->area.w = newFace->pixelArea.w / lightMapRes;
//			newFace->area.h = newFace->pixelArea.h / lightMapRes;
						
			newFace->numLumels = 0;
			for(float pw =-2 ;pw < newFace->pixelArea.w+3; pw++) {
				for(float ph =-2 ;ph < newFace->pixelArea.h+3; ph++) {
					Lumel *newLumel = new Lumel;
					newLumel->face = newFace;
					newLumel->lumelScale = lumelScale;
					newLumel->u = pw/lightMapRes;
					newLumel->v = ph/lightMapRes;
					newLumel->normal = newFace->meshPolygon->getFaceNormal();
					newFace->lumels.push_back(newLumel);
					lumels.push_back(newLumel);
					newFace->numLumels++;
				}
			}
			
			newLMesh->faces.push_back(newFace);
		}
	}
}

Vector3 LightmapPacker::getLumelPos(Lumel *lumel, LightmapFace *face) {
	
	Vector3 poly_normal = face->meshPolygon->getFaceNormal();
	
	Vector3 pointonplane = *face->meshPolygon->getVertex(0) ;
//	Vector3 pointonplane = (*face->meshPolygon->getVertex(0) + *face->meshPolygon->getVertex(1) + *face->meshPolygon->getVertex(2)) / 3.0f;		
	
	float Distance = -(poly_normal.x * pointonplane.x + poly_normal.y * pointonplane.y + poly_normal.z * pointonplane.z);
	
	float X,Y,Z;
	Vector3 UVVector, Vect1, Vect2;
	
	float	Min_U = face->flatUnscaledPolygon->getVertex(0)->x;
	float   Min_V = face->flatUnscaledPolygon->getVertex(0)->y;
	float   Max_U = face->flatUnscaledPolygon->getVertex(0)->x;
	float   Max_V = face->flatUnscaledPolygon->getVertex(0)->y;

        for (int i = 0; i < 3; i++)
        {
            if (face->flatUnscaledPolygon->getVertex(i)->x < Min_U )
                Min_U = face->flatUnscaledPolygon->getVertex(i)->x;
            if (face->flatUnscaledPolygon->getVertex(i)->y < Min_V )
                Min_V = face->flatUnscaledPolygon->getVertex(i)->y;
            if (face->flatUnscaledPolygon->getVertex(i)->x > Max_U )
                Max_U = face->flatUnscaledPolygon->getVertex(i)->x;
            if (face->flatUnscaledPolygon->getVertex(i)->y > Max_V )
                Max_V = face->flatUnscaledPolygon->getVertex(i)->y;
        }	

	switch(face->projectionAxis) {
		case LightmapFace::X_PROJECTION:
			X = - ( (poly_normal.y * Min_U) + (poly_normal.z * Min_V) + Distance )
			/ poly_normal.x;
			UVVector.x = X;
			UVVector.y = Min_U;
			UVVector.z = Min_V;
			X = - ( (poly_normal.y * Max_U) + (poly_normal.z) * Min_V + Distance )
			/ poly_normal.x;
			Vect1.x = X;
			Vect1.y = Max_U;
			Vect1.z = Min_V;
			X = - ( (poly_normal.y * Min_U) + (poly_normal.z * Max_V) + Distance )
			/ poly_normal.x;
			Vect2.x = X;
			Vect2.y = Min_U;
			Vect2.z = Max_V;
			break;
		case LightmapFace::Y_PROJECTION:
			Y = - ( poly_normal.x * Min_U + poly_normal.z * Min_V + Distance )
			/ poly_normal.y;
			UVVector.x = Min_U;
			UVVector.y = Y;
			UVVector.z = Min_V;
			Y = - ( poly_normal.x * Max_U + poly_normal.z * Min_V + Distance )
			/ poly_normal.y;
			Vect1.x = Max_U;
			Vect1.y = Y;
			Vect1.z = Min_V;
			Y = - ( poly_normal.x * Min_U + poly_normal.z * Max_V + Distance )
			/ poly_normal.y;
			Vect2.x = Min_U;
			Vect2.y = Y;
			Vect2.z = Max_V;		
			break;
		case LightmapFace::Z_PROJECTION:
			Z = - ( poly_normal.x * Min_U + poly_normal.y * Min_V + Distance )
			/ poly_normal.z;
			UVVector.x = Min_U;
			UVVector.y = Min_V;
			UVVector.z = Z;
			Z = - ( poly_normal.x * Max_U + poly_normal.y * Min_V + Distance )
			/ poly_normal.z;
			Vect1.x = Max_U;
			Vect1.y = Min_V;
			Vect1.z = Z;
			Z = - ( poly_normal.x * Min_U + poly_normal.y * Max_V + Distance )
			/ poly_normal.z;
			Vect2.x = Min_U;
			Vect2.y = Max_V;
			Vect2.z = Z;
			break;
	}
	
	Vector3 edge1,edge2,newedge1,newedge2;
	
	edge1.x = Vect1.x - UVVector.x;
    edge1.y = Vect1.y - UVVector.y;
    edge1.z = Vect1.z - UVVector.z;
    edge2.x = Vect2.x - UVVector.x;
    edge2.y = Vect2.y - UVVector.y;
    edge2.z = Vect2.z - UVVector.z;
	
	float ufactor = lumel->u/(face->area.w+(0.0f/lightMapRes));
	float vfactor = lumel->v/(face->area.h+(0.0f/lightMapRes));

//	Logger::log("edge1: %f %f %f", edge1.x, edge1.y,edge1.z);
	
	newedge1.x = edge1.x * ufactor;
	newedge1.y = edge1.y * ufactor;
	newedge1.z = edge1.z * ufactor;
	newedge2.x = edge2.x * vfactor;
	newedge2.y = edge2.y * vfactor;
	newedge2.z = edge2.z * vfactor;
		
	Vector3 retVec(UVVector.x + newedge2.x + newedge1.x,
				   UVVector.y + newedge2.y + newedge1.y,
				   UVVector.z + newedge2.z + newedge1.z);
	
	return retVec;
}

void LightmapPacker::packMesh(LightmapMesh *mesh) {
	Color col;
	mesh->imageID = currentImageID;
	mesh->mesh->lightmapIndex = currentImageID;
	for(int n=0; n < mesh->faces.size(); n++) {
		PackNode *pNode = cNode->Insert(mesh->faces[n]);
		if(pNode != NULL) {
			col.Random();
			currentImage->drawRect(pNode->rc.x-1, pNode->rc.y-1, pNode->rc.w+2, pNode->rc.h+2, col);
			pNode->face = mesh->faces[n];
			for(int i=0; i < mesh->faces[n]->flatPolygon->getVertexCount(); i++) {
				Vertex *vert = mesh->faces[n]->flatPolygon->getVertex(i);				
				vert->x += (pNode->rc.x/lightMapRes);//-(1.0f/lightMapRes);
				vert->y += (pNode->rc.y/lightMapRes);//-(1.0f/lightMapRes);
				mesh->faces[n]->meshPolygon->addTexCoord2(vert->x,vert->y);
				mesh->mesh->getMesh()->numUVs = 2;
			}
			
			for(int nl = 0; nl < mesh->faces[n]->numLumels; nl++) {
				mesh->faces[n]->lumels[nl]->worldPos = mesh->mesh->getConcatenatedMatrix() * getLumelPos(mesh->faces[n]->lumels[nl], mesh->faces[n]);
				mesh->faces[n]->lumels[nl]->u += (pNode->rc.x/lightMapRes);
				mesh->faces[n]->lumels[nl]->v += (pNode->rc.y/lightMapRes);				
			}
			
			mesh->faces[n]->imageID = currentImageID;
			mesh->faces[n]->pixelArea.x = pNode->rc.x;
			mesh->faces[n]->pixelArea.y = pNode->rc.y;
		} else {
			Logger::log("WARNING MESH DOES NOT FIT! %d of %d completed \n", n, mesh->faces.size());
			return;
			//generateNewImage();
		}
	}	
}

void LightmapPacker::generateNewImage() {
	cNode = new PackNode();
	cNode->createRoot(lightMapRes);
	currentImage = new Image(lightMapRes,lightMapRes);
	currentImage->fill(0,0,0,1);
	images.push_back(currentImage);
	currentImageID++;
}

bool LightmapPacker::hasRoomForMesh(LightmapMesh *mesh) {
	PackNode *copyNode = cNode->clone();
	for(int n=0; n < mesh->faces.size(); n++) {
		PackNode *pNode = copyNode->Insert(mesh->faces[n]);
		if(pNode != NULL) {
			pNode->face = mesh->faces[n];
		} else {
			delete copyNode;
			return false;
		} 
	}	
	delete copyNode;
	return true;
}

void LightmapPacker::buildTextures() {
	generateNewImage();
	
	// TODO: sort meshes by size
	
	for(int m=0; m < lightmapMeshes.size(); m++) {
		if(hasRoomForMesh(lightmapMeshes[m])) {
			Logger::log("packing mesh %d\n", m);
			packMesh(lightmapMeshes[m]);
		} else {
			Logger::log("mesh %d doesnt fit, generating new image and packing\n", m);
			generateNewImage();
			packMesh(lightmapMeshes[m]);
		}
	}
}

void LightmapPacker::generateTextures(int resolution, int quality) {
	lightMapRes = resolution;
	lightMapQuality = quality;
	unwrapScene();
	buildTextures();
}

void LightmapPacker::bindTextures() {
	// create textures and bind them for preview
	for(int i=0; i < images.size(); i++) {	
		images[i]->fastBlur(1);
		Texture* newTex = CoreServices::getInstance()->getMaterialManager()->createTextureFromImage(images[i]);
		textures.push_back(newTex);
	}
	
	for(int i=0; i < targetScene->getNumStaticGeometry(); i++) {
		Material *meshMaterial = targetScene->getStaticGeometry(i)->getMaterial();
		if(meshMaterial) {
			targetScene->getStaticGeometry(i)->getLocalShaderOptions()->addTexture("diffuse2", textures[targetScene->getStaticGeometry(i)->lightmapIndex]);
		}
	}
	

/* old way
	for(int i=0; i < lightmapMeshes.size(); i++) {
		Material *meshMaterial = lightmapMeshes[i]->mesh->getMaterial();
		if(meshMaterial) {
			lightmapMeshes[i]->mesh->getLocalShaderOptions()->addTexture("diffuse2", textures[lightmapMeshes[i]->imageID]);
		}
	}
*/

}

void LightmapPacker::saveLightmaps(string folder) {
	for(int i=0; i < images.size(); i++) {	
		std::ostringstream fileName;
		fileName << folder << "/" << "lm" << i << ".bmp";
		images[i]->writeBMP(fileName.str());
	}
}

void PackNode::createRoot(int res) {
	rc.w = res-4;
	rc.h = res-4;
	rootRes = res-4;
	rc.x = 1;
	rc.y = 1;
	
}

PackNode *PackNode::clone() {
	PackNode *cloneNode = new PackNode();
	cloneNode->rc.x = rc.x;
	cloneNode->rc.y  = rc.y;
	cloneNode->rc.w = rc.w;
	cloneNode->rc.h  = rc.h;
	
	cloneNode->face = face;
	if(child[0]) {
		cloneNode->child[0] = child[0]->clone();
	}
	if(child[1]) {
		cloneNode->child[1] = child[1]->clone();
	}	
	return cloneNode;
}

PackNode *PackNode::Insert(LightmapFace *img) {
	PackNode *newNode;	
	if(child[0]) {
		newNode = child[0]->Insert(img);
        if(newNode != NULL)
			return newNode;
        return child[1]->Insert(img);
	} else {
		if(face != NULL)
			return NULL;
		
        //(if we're too small, return)
		if(img->pixelArea.w > rc.w || img->pixelArea.h > rc.h)
            return NULL;
		
        if(img->pixelArea.w == rc.w && img->pixelArea.h == rc.h)
            return this;
        
        child[0] = new PackNode();
        child[1] = new PackNode();
        
		float dw = rc.w - img->pixelArea.w;
		float dh = rc.h - img->pixelArea.h;
        
        if(dw > dh) {
            child[0]->rc = Rectangle(rc.x, rc.y, img->pixelArea.w, rc.h);
            child[1]->rc = Rectangle(rc.x+img->pixelArea.w+4, rc.y, rc.w-img->pixelArea.w-3, rc.h);
        } else {
            child[0]->rc = Rectangle(rc.x, rc.y, rc.w, img->pixelArea.h);
            child[1]->rc = Rectangle(rc.x, rc.y+img->pixelArea.h+4, rc.w, rc.h-img->pixelArea.h-3);
        }
        return child[0]->Insert(img);	
	}
}