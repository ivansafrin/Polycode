
#include "polyimport.h"
#include "PolyPolygon.h"
#include "OSBasics.h"

#include "physfs.h"

using namespace Polycode;

const struct aiScene* scene = NULL;
bool hasWeights = false;
vector<aiBone*> bones;
unsigned int numBones = 0;

unsigned int addBone(aiBone *bone) {
	for(int i=0; i < bones.size(); i++) {
		if(bones[i]->mName == bone->mName)
			return i;
	}
	bones.push_back(bone);
	return bones.size()-1;
}

void addToMesh(Polycode::Mesh *tmesh, const struct aiScene *sc, const struct aiNode* nd, bool swapZY) {
	int i;
	unsigned int n = 0, t;
	// draw all meshes assigned to this node

	for (; n < nd->mNumMeshes; ++n) {
		const struct aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];
		printf("Importing mesh:%s (%d vertices) (%d faces) \n", mesh->mName.data, mesh->mNumVertices, mesh->mNumFaces);

		//apply_material(sc->mMaterials[mesh->mMaterialIndex]);

		for (t = 0; t < mesh->mNumFaces; ++t) {
			const struct aiFace* face = &mesh->mFaces[t];
			Polycode::Polygon *poly = new Polycode::Polygon();			
	
			for(i = 0; i < face->mNumIndices; i++) {
				Vertex *vertex = new Vertex();

				int index = face->mIndices[i];
				if(mesh->mColors[0] != NULL) {
					vertex->vertexColor.setColorRGBA(mesh->mColors[0][index].r, mesh->mColors[0][index].g, mesh->mColors[0][index].b, mesh->mColors[0][index].a);
				}

				if(mesh->mNormals != NULL)  {
					if(swapZY)
						vertex->setNormal(mesh->mNormals[index].x, mesh->mNormals[index].z, -mesh->mNormals[index].y);
					else
						vertex->setNormal(mesh->mNormals[index].x, mesh->mNormals[index].y, mesh->mNormals[index].z);
				}

				if(mesh->HasTextureCoords(0))
				{
					vertex->setTexCoord(mesh->mTextureCoords[0][index].x, mesh->mTextureCoords[0][index].y);
				}

				for( unsigned int a = 0; a < mesh->mNumBones; a++) {
					aiBone* bone = mesh->mBones[a];
					unsigned int boneIndex = addBone(bone);

					for( unsigned int b = 0; b < bone->mNumWeights; b++) {
						if(bone->mWeights[b].mVertexId == index) {
							vertex->addBoneAssignment(boneIndex, bone->mWeights[b].mWeight);
							hasWeights = true;
						}
					}
				}
	
				if(swapZY)
					vertex->set(mesh->mVertices[index].x, mesh->mVertices[index].z, -mesh->mVertices[index].y);
				else
					vertex->set(mesh->mVertices[index].x, mesh->mVertices[index].y, mesh->mVertices[index].z);
				poly->addVertex(vertex);
			}
			tmesh->addPolygon(poly);
		}
	}

	// draw all children
	for (n = 0; n < nd->mNumChildren; ++n) {
		addToMesh(tmesh, sc, nd->mChildren[n], swapZY);
	}
}

int getBoneID(aiString name) {
	for(int i=0; i  < bones.size(); i++) {
		if(bones[i]->mName == name) {
			return i;
		}
	}
	return 666;
}

void addToISkeleton(ISkeleton *skel, IBone *parent, const struct aiScene *sc, const struct aiNode* nd) {
	IBone *bone = new IBone();
	bone->parent = parent;
	bone->name = nd->mName;
	bone->t = nd->mTransformation;

	for(int i=0; i < bones.size(); i++) {
		if(bones[i]->mName == bone->name) {
			bone->bindMatrix = bones[i]->mOffsetMatrix;
		}
	}

	for (int n = 0; n < nd->mNumChildren; ++n) {
		addToISkeleton(skel, bone, sc, nd->mChildren[n]);
	}
	skel->addIBone(bone, getBoneID(bone->name));
}

int exportToFile(const char *fileName, bool swapZY) {
	String fileNameMesh = String(fileName)+".mesh";
	OSFILE *outFile = OSBasics::open(fileNameMesh.c_str(), "wb");
	Polycode::Mesh *mesh = new Polycode::Mesh(Mesh::TRI_MESH);
	addToMesh(mesh, scene, scene->mRootNode, swapZY);
	mesh->saveToFile(outFile);
	OSBasics::close(outFile);

	if(hasWeights) {
		printf("Mesh has weights, exporting skeleton...\n");
		String fileNameSkel = String(fileName)+".skeleton";
		ISkeleton *skeleton = new ISkeleton();
	
		for (int n = 0; n < scene->mRootNode->mNumChildren; ++n) {
			if(scene->mRootNode->mChildren[n]->mNumChildren > 0) {
				addToISkeleton(skeleton, NULL, scene, scene->mRootNode->mChildren[n]);
			}
		}

		if(scene->HasAnimations()) {
			printf("Importing animations...\n");
			for(int i=0; i < scene->mNumAnimations;i++) {
				aiAnimation *a = scene->mAnimations[i];
				printf("Importing '%s' (%d tracks)\n", a->mName.data, a->mNumChannels);
			
				IAnimation *anim = new IAnimation();
				anim->tps = a->mTicksPerSecond;
				anim->name = a->mName.data;
				anim->numTracks = a->mNumChannels;
				anim->length = a->mDuration/a->mTicksPerSecond;
	
				for(int c=0; c < a->mNumChannels; c++) {
					aiNodeAnim *nodeAnim = a->mChannels[c];

					ITrack *track = new ITrack();
					track->nodeAnim = nodeAnim;
					anim->tracks.push_back(track);
				}


				skeleton->addAnimation(anim);
				
			}
		} else {
			printf("No animations in file...\n");
		}

		skeleton->saveToFile(fileName, swapZY);
	} else {
		printf("No weight data, skipping skeleton export...\n");
	}


	delete mesh;
	return 1;
}

int main(int argc, char **argv) {

	printf("Polycode import tool v0.8.2\n");

	if(argc != 4) {
		printf("\n\nInvalid arguments!\n");
		printf("usage: polyimport <source_file> <output_file> (Swap Z/Y:<true>/<false>) \n\n");
		return 0;
	}
	
	PHYSFS_init(argv[0]);
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_STDOUT,NULL);
	aiAttachLogStream(&stream);

	printf("Loading %s...\n", argv[1]);
	scene = aiImportFile(argv[1],aiProcessPreset_TargetRealtime_Quality);
	if(scene) {
		exportToFile(argv[2], strcmp(argv[3], "true") == 0);
	} else {
		printf("Error opening scene...\n");
	}

	aiReleaseImport(scene);
	return 1;
}
