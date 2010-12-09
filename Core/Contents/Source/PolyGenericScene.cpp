/*
 *  PolyGenericScene.cpp
 *  TAU
 *
 *  Created by Ivan Safrin on 3/18/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolyGenericScene.h"

using namespace Polycode;

GenericScene::GenericScene() : Scene() {
	hasLightmaps = false;
	clearColor.setColor(0.13f,0.13f,0.13f,1.0f); 
	virtualScene = false;
	useClearColor = false;
}

GenericScene::GenericScene(bool virtualScene) {
	this->virtualScene = virtualScene;	
}

GenericScene::~GenericScene() {
}

void GenericScene::Render() {
	
	if(!defaultCamera)
		return;
	
	// prepare lights...
	for(int i=0; i<entities.size();i++) {
		entities[i]->doUpdates();		
		entities[i]->updateEntityMatrix();
	}	
	
	//make these the closest
	
	Matrix4 textureMatrix;
	Matrix4 *matrixPtr;
	
	
	defaultCamera->rebuildTransformMatrix();
	
	if(virtualScene)
		return;
	
	if(useClearColor)
		CoreServices::getInstance()->getRenderer()->setClearColor(clearColor.r,clearColor.g,clearColor.b);	
	
	CoreServices::getInstance()->getRenderer()->setAmbientColor(ambientColor.r,ambientColor.g,ambientColor.b);		

	CoreServices::getInstance()->getRenderer()->clearLights();
	
	for(int i=0; i < lights.size(); i++) {
		
		SceneLight *light = lights[i];
		
		Vector3 direction;
		Vector3 position;
		matrixPtr = NULL;				
		direction.x = 0;		
		direction.y = 1;
		direction.z = 0;

		direction = light->getConcatenatedMatrix().rotateVector(direction);
		direction.Normalize();
		
		if(light->areShadowsEnabled()) {
			if(light->getType() == SceneLight::SPOT_LIGHT) {
				textureMatrix.identity();

				Matrix4 matTexAdj(0.5f,	0.0f,	0.0f,	0.0f,
								  0.0f,	0.5f,	0.0f,	0.0f,
								  0.0f,	0.0f,	0.5f,	0.0f,
								  0.5f,	0.5f,	0.5f,	1.0f );

				textureMatrix =  defaultCamera->getConcatenatedMatrix() * light->getLightViewMatrix() * matTexAdj;
			
				matrixPtr = &textureMatrix;
				light->renderDepthMap(this);
				CoreServices::getInstance()->getRenderer()->addShadowMap(light->getZBufferTexture());
			}
		}

		position = *light->getPosition();
		if(light->getParentEntity() != NULL) {
			position = light->getParentEntity()->getConcatenatedMatrix() * position;			
		}
		CoreServices::getInstance()->getRenderer()->addLight(position, direction, light->getLightType(), light->lightColor, light->getDistance(), light->getIntensity(), matrixPtr);
	}	
	
	defaultCamera->doCameraTransform();
	defaultCamera->buildFrustrumPlanes();
	
	
	for(int i=0; i<entities.size();i++) {
		if(entities[i]->getBBoxRadius() > 0) {
			if(defaultCamera->isSphereInFrustrum((*entities[i]->getPosition()), entities[i]->getBBoxRadius()))
				entities[i]->transformAndRender();
		} else {
			entities[i]->transformAndRender();		
		}
	}
}


void GenericScene::RenderDepthOnly(Camera *targetCamera) {

	for(int i=0; i<entities.size();i++) {
		entities[i]->doUpdates();		
		entities[i]->updateEntityMatrix();
	}
	
	targetCamera->doCameraTransform();
	
	if(virtualScene)
		return;	
	
	targetCamera->buildFrustrumPlanes();

	CoreServices::getInstance()->getRenderer()->setTexture(NULL);
	CoreServices::getInstance()->getRenderer()->enableShaders(false);
	for(int i=0; i<entities.size();i++) {
		if(entities[i]->getBBoxRadius() > 0) {
			if(targetCamera->isSphereInFrustrum((*entities[i]->getPosition()), entities[i]->getBBoxRadius()))
				entities[i]->transformAndRender();
		} else {
			entities[i]->transformAndRender();		
		}
	}	
	CoreServices::getInstance()->getRenderer()->enableShaders(true);
}

void GenericScene::addLight(SceneLight *light) {
	lights.push_back(light);
	addEntity(light);
}

SceneLight *GenericScene::getNearestLight(Vector3 pos) {
	if(lights.size() > 0)
		return lights[0];
	else
		return NULL;
}


String GenericScene::readString(OSFILE *inFile) {
	char buffer[1024];
	unsigned int namelen;
	OSBasics::read(&namelen, sizeof(unsigned int), 1, inFile);
	memset(buffer, 0, 1024);
	OSBasics::read(buffer, 1, namelen, inFile);
	return string(buffer);
	
}

void GenericScene::loadScene(String fileName) {
	OSFILE *inFile = OSBasics::open(fileName.c_str(), "rb");
	if(!inFile) {
		Logger::log("Error opening scene file\n");
		return;
	}
	
	float r,g,b,a;
	
	OSBasics::read(&r, sizeof(float), 1, inFile);
	OSBasics::read(&g, sizeof(float), 1, inFile);
	OSBasics::read(&b, sizeof(float), 1, inFile);
	clearColor.setColor(r,g,b,1.0f);

	OSBasics::read(&r, sizeof(float), 1, inFile);
	OSBasics::read(&g, sizeof(float), 1, inFile);
	OSBasics::read(&b, sizeof(float), 1, inFile);
	ambientColor.setColor(r,g,b,1.0f);
	
	
	unsigned int numObjects, objectType,namelen;
	char buffer[1024];
	char flag;
	float t[3],rq[4];
	SceneEntity *newEntity;
	
	unsigned int lightmapIndex = 0;
	
	OSBasics::read(&flag, 1, 1, inFile);
	hasLightmaps = false;
	if(flag == 1)
		hasLightmaps = true;
	
	OSBasics::read(&numObjects, sizeof(unsigned int), 1, inFile);
	Logger::log("Loading scene (%d objects)\n", numObjects);
	for(int i=0; i < numObjects; i++) {
		
		OSBasics::read(t, sizeof(float), 3, inFile);
		OSBasics::read(rq, sizeof(float), 4, inFile);
		newEntity = NULL;
		
		OSBasics::read(&objectType, sizeof(unsigned int), 1, inFile);

		SceneMesh *newSceneMesh;
		Mesh *newMesh;
		Material *newMaterial;
		
		switch(objectType) {
			case ENTITY_MESH:			

				if(hasLightmaps) {
					OSBasics::read(&lightmapIndex, sizeof(unsigned int), 1, inFile);			
				} else {
					lightmapIndex = 0;
				}

			
				OSBasics::read(&namelen, sizeof(unsigned int), 1, inFile);
				memset(buffer, 0, 1024);
				OSBasics::read(buffer, 1, namelen, inFile);
				
				Logger::log("adding mesh (texture: %s)\n", buffer);
				
				OSBasics::read(&r, sizeof(float), 1, inFile);
				OSBasics::read(&g, sizeof(float), 1, inFile);
				OSBasics::read(&b, sizeof(float), 1, inFile);
				OSBasics::read(&a, sizeof(float), 1, inFile);
				
				newMaterial = (Material*) CoreServices::getInstance()->getResourceManager()->getResource(Resource::RESOURCE_MATERIAL, buffer);
				newMesh = new Mesh(Mesh::TRI_MESH);
				newMesh->loadFromFile(inFile);
				newSceneMesh = new SceneMesh(newMesh);
				
				newSceneMesh->setColor(r,g,b,a);
				newSceneMesh->lightmapIndex = lightmapIndex;
				addEntity(newSceneMesh);
				newEntity = (SceneEntity*)newSceneMesh;
				staticGeometry.push_back(newSceneMesh);
				if(newMaterial != NULL)
					newSceneMesh->setMaterial(newMaterial);
				
				break;
				case ENTITY_ENTITY: {
					Logger::log("loading entity\n");
					String entityType = readString(inFile);					
					SceneEntity *newCustomEntity = new SceneEntity();
					newCustomEntity->custEntityType = entityType;					
					newEntity = newCustomEntity;
					customEntities.push_back(newCustomEntity);					
				} break;
				case ENTITY_COLLMESH: {
					unsigned int collType,numVertices,numFaces;
					float co[3];
					OSBasics::read(&collType, sizeof(unsigned int), 1, inFile);
					OSBasics::read(&numVertices, sizeof(unsigned int), 1, inFile);

					Mesh *mesh = new Mesh(Mesh::TRI_MESH);
					
					for(int i=0; i < numVertices; i++) {
						OSBasics::read(co, sizeof(float), 3, inFile);
						Vertex *newVert = new Vertex(co[0], co[1], co[2]);
						mesh->addVertex(newVert);
					}

					OSBasics::read(&numFaces, sizeof(unsigned int), 1, inFile);
					
					unsigned int fo[3];
					for(int i=0; i < numFaces; i++) {
						OSBasics::read(fo, sizeof(unsigned int), 3, inFile);						
						Polygon *newPoly = new Polygon();
						newPoly->addVertex(mesh->getVertex(fo[0]));
						newPoly->addVertex(mesh->getVertex(fo[1]));
						newPoly->addVertex(mesh->getVertex(fo[2]));
						mesh->addPolygon(newPoly);
					}
					
					SceneMesh *newMesh = new SceneMesh(mesh);
					newEntity = newMesh;
					loadCollisionChild(newEntity);
					collisionGeometry.push_back(newMesh);
					newMesh->visible = false;
					
//					ScenePrimitive *test = new ScenePrimitive(ScenePrimitive::TYPE_BOX, newMesh->bBox.x,newMesh->bBox.y,newMesh->bBox.z);				
//					newMesh->addEntity(test);
					
				}
				break;
				case ENTITY_CAMERA:
					newEntity = (SceneEntity*)this->getDefaultCamera();
				break;
				case ENTITY_LIGHT:
				
				float col[3],e,d;
				unsigned int lType;
				OSBasics::read(&lType, sizeof(unsigned int), 1, inFile);				
				OSBasics::read(&e, sizeof(float), 1, inFile);
				OSBasics::read(&d, sizeof(float), 1, inFile);
				OSBasics::read(col, sizeof(float), 3, inFile);

				SceneLight *newLight = new SceneLight(lType, e, d, this);
				newLight->lightColor.setColor(col[0],col[1],col[2],1.0f);
				addLight(newLight);
				newEntity = (SceneEntity*)newLight;
				break;
		}
		
		
		if(newEntity != NULL) {		
			unsigned int numProps;
			OSBasics::read(&numProps, sizeof(unsigned int), 1, inFile);
			for(int i=0; i < numProps; i++) {
				String propName,propValue;
				propName = readString(inFile);
				propValue = readString(inFile);
				EntityProp prop;
				prop.propName = propName;
				prop.propValue = propValue;
				newEntity->entityProps.push_back(prop);
			}						
			
			if(objectType == ENTITY_MESH) {
				if(newEntity->getEntityProp("vertexnormals") == "false")
					((SceneMesh*)newEntity)->getMesh()->useVertexNormals(false);
				
				if(newEntity->getEntityProp("collision") != "") {
					if(newEntity->getEntityProp("collision")  == "mesh") {
						loadCollisionChild(newEntity, false, 3);
					}
				}
			}
			
			newEntity->setPosition(t[0], t[1], t[2]);
			newEntity->setRotationQuat(rq[0], rq[1], rq[2], rq[3]);
			newEntity->rebuildTransformMatrix();						
		}		
	}
	
	if(!hasLightmaps) {
		OSBasics::close(inFile);
		return;
	}
	/*
	unsigned int lmsize,numLightmaps,imageWidth, imageHeight;
	OSBasics::read(&numLightmaps, sizeof(unsigned int), 1, inFile);
	
	packer = new LightmapPacker(this);
	char *imageData;
	
	for(int i=0 ; i < numLightmaps; i++) {
		OSBasics::read(&imageWidth, sizeof(unsigned int), 1, inFile);
		OSBasics::read(&imageHeight, sizeof(unsigned int), 1, inFile);
		OSBasics::read(&lmsize, sizeof(unsigned int), 1, inFile);
		imageData = (char*)malloc(lmsize);
		OSBasics::read(imageData, 1, lmsize, inFile);
		Image *newImage = new Image(imageData, imageWidth, imageHeight);
		packer->images.push_back(newImage);	
		free(imageData);
	}
	
	packer->bindTextures();
	*/
	OSBasics::close(inFile);
}

vector<SceneEntity*> GenericScene::getCustomEntitiesByType(String type) {
	vector<SceneEntity*> retVector;
	for(int i=0; i < customEntities.size(); i++) {
		if(customEntities[i]->custEntityType == type) {
			retVector.push_back(customEntities[i]);
		}
	}
	return retVector;	
}

SceneEntity *GenericScene::getCustomEntityByType(String type) {
	for(int i=0; i < customEntities.size(); i++) {
		if(customEntities[i]->custEntityType == type) {
			return customEntities[i];
		}
	}
	return NULL;
}

void GenericScene::writeEntityMatrix(SceneEntity *entity, OSFILE *outFile) {
	float t[3],rq[4];
	t[0] = entity->getPosition()->x;
	t[1] = entity->getPosition()->y;
	t[2] = entity->getPosition()->z;
	
	rq[0] = entity->getRotationQuat().w;
	rq[1] = entity->getRotationQuat().x;
	rq[2] = entity->getRotationQuat().y;
	rq[3] = entity->getRotationQuat().z;						
	
	OSBasics::write(t, sizeof(float), 3, outFile);
	OSBasics::write(rq, sizeof(float), 4, outFile);
	
}

void GenericScene::saveScene(String fileName) {
	OSFILE *outFile = OSBasics::open(fileName.c_str(), "wb");
	if(!outFile) {
		Logger::log("Error opening scene file for writing\n");
		return;
	}
	
	// geometry
	unsigned int totalObjects = staticGeometry.size() + lights.size() + collisionGeometry.size() + customEntities.size();
	unsigned int objType;
	char flag = 0;
	if(hasLightmaps)
		flag = 1;
	OSBasics::write(&flag, 1, 1, outFile);
	OSBasics::write(&totalObjects, sizeof(unsigned int), 1, outFile);
	
	unsigned int stLen;
	
	for(int i=0; i <staticGeometry.size(); i++) {
		SceneMesh *mesh = staticGeometry[i];
		
		writeEntityMatrix(mesh, outFile);
		
		objType = GenericScene::ENTITY_MESH;		
		OSBasics::write(&objType, sizeof(unsigned int), 1, outFile);

		if(hasLightmaps) {
			unsigned int lightmapIndex = mesh->lightmapIndex;
			OSBasics::write(&lightmapIndex, sizeof(unsigned int), 1, outFile);			
		}

		stLen = mesh->getMaterial()->getName().length();
		OSBasics::write(&stLen, sizeof(unsigned int), 1, outFile);
		OSBasics::write(mesh->getMaterial()->getName().c_str(), 1, stLen, outFile);
		
		mesh->getMesh()->saveToFile(outFile);		
	}
	

	for(int i=0; i < collisionGeometry.size(); i++) {
		SceneMesh *mesh = collisionGeometry[i];
		writeEntityMatrix(mesh, outFile);
		objType = GenericScene::ENTITY_COLLMESH;
		OSBasics::write(&objType, sizeof(unsigned int), 1, outFile);
	
		unsigned int collType = 1;
		OSBasics::write(&collType, sizeof(unsigned int), 1, outFile);
		
		unsigned int numVertices = mesh->getMesh()->getNumVertices();
		OSBasics::write(&numVertices, sizeof(unsigned int), 1, outFile);
		float pos[3];
		for(int j=0; j < numVertices; j++) {
			Vertex *vert = mesh->getMesh()->getVertex(j);
			pos[0] = vert->x;
			pos[1] = vert->y;
			pos[2] = vert->z;			
			OSBasics::write(pos, sizeof(float),3, outFile);
		}

		unsigned int numFaces = mesh->getMesh()->getPolygonCount();
		OSBasics::write(&numFaces, sizeof(unsigned int), 1, outFile);
		unsigned int ind[3];
		for(int j=0; j < numFaces; j++) {
			Polygon *poly = mesh->getMesh()->getPolygon(j);
			ind[0] = mesh->getMesh()->getVertexIndex(poly->getVertex(0));
			ind[1] = mesh->getMesh()->getVertexIndex(poly->getVertex(1));
			ind[2] = mesh->getMesh()->getVertexIndex(poly->getVertex(2));			
			OSBasics::write(ind, sizeof(unsigned int),3, outFile);
		}
	}
	
	float col[3],e,d;
	for(int i=0; i < lights.size(); i++) {
	
		writeEntityMatrix(lights[i], outFile);
		objType = GenericScene::ENTITY_LIGHT;		
		OSBasics::write(&objType, sizeof(unsigned int), 1, outFile);
	
		col[0] = lights[i]->lightColor.r;
		col[1] = lights[i]->lightColor.g;
		col[2] = lights[i]->lightColor.b;
		e = lights[i]->getIntensity();
		d = lights[i]->getDistance();
		
		OSBasics::write(&e, sizeof(float), 1, outFile);
		OSBasics::write(&d, sizeof(float), 1, outFile);
		OSBasics::write(col, sizeof(float), 3, outFile);
	}

	for(int i=0; i < customEntities.size(); i++) {
		SceneEntity *custEnt = customEntities[i];
		
		writeEntityMatrix(custEnt, outFile);	
		objType = GenericScene::ENTITY_ENTITY;
		OSBasics::write(&objType, sizeof(unsigned int), 1, outFile);
		
		
		writeString(custEnt->custEntityType, outFile);
		unsigned int numProps = custEnt->entityProps.size();
		OSBasics::write(&numProps, sizeof(unsigned int), 1, outFile);		
		for(int j=0; j < numProps; j++) {
			writeString(custEnt->entityProps[j].propName, outFile);
			writeString(custEnt->entityProps[j].propValue, outFile);
		}
	}

	if(!hasLightmaps) {
		OSBasics::close(outFile);
		return;
	}
	
	/*
	unsigned int lmsize;
	lmsize = packer->images.size();
	OSBasics::write(&lmsize, sizeof(unsigned int), 1, outFile);
	for(int i=0; i < packer->images.size(); i++) {
		lmsize = packer->images[i]->getWidth();
		OSBasics::write(&lmsize, sizeof(unsigned int), 1, outFile);
		lmsize = packer->images[i]->getHeight();
		OSBasics::write(&lmsize, sizeof(unsigned int), 1, outFile);
		
		lmsize = packer->images[i]->getWidth() * packer->images[i]->getHeight() * 4;
		OSBasics::write(&lmsize, sizeof(unsigned int), 1, outFile);
		OSBasics::write(packer->images[i]->getPixels(), 1, lmsize, outFile);
	}
	*/
	
	OSBasics::close(outFile);
}

void GenericScene::writeString(String str, OSFILE *outFile) {
	unsigned int stLen = str.length();
	OSBasics::write(&stLen, sizeof(unsigned int), 1, outFile);
	OSBasics::write(str.c_str(), 1, stLen, outFile);
	
}

int GenericScene::getNumStaticGeometry() {
	return staticGeometry.size();
}

SceneMesh *GenericScene::getStaticGeometry(int index) {
	return staticGeometry[index];
}

int GenericScene::getNumLights() {
	return lights.size();
}

SceneLight *GenericScene::getLight(int index) {
	return lights[index];
}

void GenericScene::generateLightmaps(float lightMapRes, float lightMapQuality, int numRadPasses) {
/*	
	packer = new LightmapPacker(this);
	packer->generateTextures(lightMapRes, lightMapQuality);
	
	RadTool *radTool = new RadTool(this, packer);
	radTool->fiatLux(numRadPasses);
	
	packer->bindTextures();
	packer->saveLightmaps("/Users/ivansafrin/Desktop/lightmaps");
	hasLightmaps = true;
 */
}

void GenericScene::addGrid(String gridTexture) {
	ScenePrimitive *gridMesh = new ScenePrimitive(ScenePrimitive::TYPE_PLANE, 20,20,0);
	gridMesh->loadTexture(gridTexture);
	gridMesh->setPitch(-90.0f);
	addEntity(gridMesh);
}