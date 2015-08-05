
#include "polyimport.h"
#include "OSBasics.h"
#include "PolyObject.h"

#include "physfs.h"
#ifdef WIN32
#include "getopt.h"
#define getopt getopt_a
#else
#include <unistd.h>
#endif

using namespace Polycode;

const struct aiScene* scene = NULL;
bool hasWeights = false;
vector<aiBone*> bones;
unsigned int numBones = 0;

std::vector<String> materialsInFile;
std::vector<String> meshesInFile;

bool writeNormals = false;
bool writeTangents = false;
bool writeColors = false;
bool writeBoneWeights = false;
bool writeUVs = false;
bool writeSecondaryUVs = false;

bool hasMesh(String meshName) {
    for(int i=0; i < meshesInFile.size(); i++) {
        if(meshesInFile[i] == meshName) {
            return true;
        }
    }
    return false;
}

bool hasMaterial(String materialName) {
    for(int i=0; i < materialsInFile.size(); i++) {
        if(materialsInFile[i] == materialName) {
            return true;
        }
    }
    return false;
}

unsigned int addBone(aiBone *bone) {
	for(int i=0; i < bones.size(); i++) {
		if(bones[i]->mName == bone->mName)
			return i;
	}
	bones.push_back(bone);
	return bones.size()-1;
}

aiMatrix4x4 getFullTransform(const struct aiNode *nd) {
    if(nd->mParent) {
        return  getFullTransform(nd->mParent) * nd->mTransformation;
    } else {
        return nd->mTransformation;
    }
}

void addToMesh(String prefix, Polycode::Mesh *tmesh, const struct aiScene *sc, const struct aiNode* nd, bool swapZY, bool addSubmeshes, bool listOnly, ObjectEntry *parentSceneObject, String overrideMaterial, ObjectEntry *materialsParent, String assetPrefixPath, String baseFileName) {
	int i, nIgnoredPolygons = 0;
	unsigned int n = 0, t;
	// draw all meshes assigned to this node

	for (; n < nd->mNumMeshes; ++n) {
	
		if(!addSubmeshes) {
			tmesh = new Polycode::Mesh(Mesh::TRI_MESH);
            tmesh->indexedMesh = true;
		}
	
		const struct aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];
        
        Vector3 bBox;
        
        String meshFileName = String(nd->mName.data);

        if(meshFileName == "") {
            meshFileName = baseFileName;
        }
        
        
        int idx = 0;
        String baseMeshFileName = meshFileName;
        
        while(hasMesh(meshFileName)) {
            meshFileName = baseMeshFileName + String::IntToString(idx);
            idx++;
        }
        
        meshesInFile.push_back(meshFileName);
        
		if(listOnly) {
			if(!addSubmeshes) {
				printf("%s%s.mesh\n", prefix.c_str(), meshFileName.c_str());
			}
		} else {
			printf("Importing mesh:%s (%d vertices) (%d faces) \n", mesh->mName.data, mesh->mNumVertices, mesh->mNumFaces);
		}
		//apply_material(sc->mMaterials[mesh->mMaterialIndex]);
        
		for (t = 0; t < mesh->mNumVertices; ++t) {

            Vector3 vPosition;
            
            int index = t;
            if(mesh->mColors[0] != NULL) {
                tmesh->addColor(mesh->mColors[0][index].r, mesh->mColors[0][index].g, mesh->mColors[0][index].b, mesh->mColors[0][index].a);
            }

            if(mesh->mTangents != NULL)  {
                if(swapZY) {
                    tmesh->addTangent(mesh->mTangents[index].x, mesh->mTangents[index].z, -mesh->mTangents[index].y);
                } else {
                    tmesh->addTangent(mesh->mTangents[index].x, mesh->mTangents[index].y, mesh->mTangents[index].z);
                }
            }

            if(mesh->mNormals != NULL)  {
                if(swapZY) {
                    tmesh->addNormal(mesh->mNormals[index].x, mesh->mNormals[index].z, -mesh->mNormals[index].y);
                } else {
                    tmesh->addNormal(mesh->mNormals[index].x, mesh->mNormals[index].y, mesh->mNormals[index].z);
                }
            }

            if(mesh->HasTextureCoords(0))
            {
                tmesh->addTexCoord(mesh->mTextureCoords[0][index].x, mesh->mTextureCoords[0][index].y);
            }

            if(mesh->HasTextureCoords(1))
            {
                tmesh->addTexCoord2(mesh->mTextureCoords[1][index].x, mesh->mTextureCoords[1][index].y);
            }

            int numAssignments = 0;
            
            float weights[4] = {0.0, 0.0, 0.0, 0.0};
            unsigned int boneIds[4] = {0, 0, 0 ,0};
            
            for( unsigned int a = 0; a < mesh->mNumBones; a++) {
                aiBone* bone = mesh->mBones[a];
                unsigned int boneIndex = addBone(bone);

                for( unsigned int b = 0; b < bone->mNumWeights; b++) {
                    if(bone->mWeights[b].mVertexId == index) {
                        if(numAssignments < 4) {
                            weights[numAssignments] = bone->mWeights[b].mWeight;
                            boneIds[numAssignments] = boneIndex;
                            numAssignments++;
                        }
                        hasWeights = true;
                    }
                }
            }
            
            
            tmesh->addBoneAssignments(weights[0], boneIds[0], weights[1], boneIds[1], weights[2], boneIds[2], weights[3], boneIds[3]);

            if(swapZY) {
					vPosition.set(mesh->mVertices[index].x, mesh->mVertices[index].z, -mesh->mVertices[index].y);
            } else {
                vPosition.set(mesh->mVertices[index].x, mesh->mVertices[index].y, mesh->mVertices[index].z);
            }
            
            if(fabs(vPosition.x) > bBox.x) {
                bBox.x = fabs(vPosition.x);
            }
            if(fabs(vPosition.y) > bBox.y) {
                bBox.y = fabs(vPosition.y);
            }
            if(fabs(vPosition.z) > bBox.z) {
                bBox.z = fabs(vPosition.z);
            }
            
            tmesh->addVertex(vPosition.x, vPosition.y, vPosition.z);
		}
        

         for (t = 0; t < mesh->mNumFaces; ++t) {
             const struct aiFace* face = &mesh->mFaces[t];
			 if (face->mNumIndices != 3) {
				 nIgnoredPolygons++;
				 continue;
			 }

             for(i = 0; i < face->mNumIndices; i++) {
                 int index = face->mIndices[i];
                 tmesh->addIndex(index);
             }
         }
		
		if(!addSubmeshes && !listOnly) {
			String fileNameMesh = prefix+meshFileName+".mesh";			
			OSFILE *outFile = OSBasics::open(fileNameMesh.c_str(), "wb");	
			tmesh->saveToFile(outFile, writeNormals, writeTangents, writeColors, writeBoneWeights, writeUVs, writeSecondaryUVs);
			OSBasics::close(outFile);
			delete tmesh;
            
            ObjectEntry *meshEntry = parentSceneObject->addChild("child");
            meshEntry->addChild("id", String(nd->mName.data));
            meshEntry->addChild("tags", "");
            meshEntry->addChild("type", "SceneMesh");
            meshEntry->addChild("cR", "1");
            meshEntry->addChild("cG", "1");
            meshEntry->addChild("cB", "1");
            meshEntry->addChild("cA", "1");
            meshEntry->addChild("blendMode", "0");
            
            aiVector3D p;
            aiVector3D s;
            aiQuaternion r;

            aiMatrix4x4 fullTransform = getFullTransform(nd);
            
            fullTransform.Decompose(s, r, p);
            
            meshEntry->addChild("sX", s.x);
            
            if(swapZY) {
                meshEntry->addChild("sY", s.z);
                meshEntry->addChild("sZ", s.y);
            } else {
                meshEntry->addChild("sY", s.y);
                meshEntry->addChild("sZ", s.z);
            }
            
            meshEntry->addChild("rX", r.x);
            
            if(swapZY) {
                meshEntry->addChild("rY", r.z);
                meshEntry->addChild("rZ", -r.y);
            } else {
                meshEntry->addChild("rY", r.y);
                meshEntry->addChild("rZ", r.z);
            }
            meshEntry->addChild("rW", r.w);
            
            meshEntry->addChild("pX", p.x);
            
            if(swapZY) {
                meshEntry->addChild("pY", p.z);
                meshEntry->addChild("pZ", -p.y);
            } else{
                meshEntry->addChild("pY", p.y);
                meshEntry->addChild("pZ", p.z);
            }
            
            bBox = bBox * 2.0;
            
            if(bBox.x == 0.0) {
                bBox.x = 0.001;
            }
            if(bBox.y == 0.0) {
                bBox.y = 0.001;
            }
            if(bBox.z == 0.0) {
                bBox.z = 0.001;
            }
            
            meshEntry->addChild("bbX", bBox.x);
            meshEntry->addChild("bbY", bBox.y);
            meshEntry->addChild("bbZ", bBox.z);
            
            ObjectEntry *sceneMeshEntry = meshEntry->addChild("SceneMesh");
            sceneMeshEntry->addChild("file", assetPrefixPath+fileNameMesh);
            
            String materialName = "Default";
            int materialIndex = mesh->mMaterialIndex;
            if(materialIndex < scene->mNumMaterials) {
                aiString name;
                scene->mMaterials[materialIndex]->Get(AI_MATKEY_NAME,name);
                if(name.length > 0) {
                    materialName = String(name.data);
                }
            }
            
            if(materialsParent && materialName != "Default") {
                if(!hasMaterial(materialName)) {
                    ObjectEntry *materialEntry = materialsParent->addChild("material");
                    materialEntry->addChild("name", materialName);
                    materialEntry->addChild("blendingMode", 0);
                    materialEntry->addChild("blendingMode", 0);
                    ObjectEntry *shaderEntry = materialEntry->addChild("shader");
                    shaderEntry->addChild("name", "DefaultShaderNoTexture");
                    materialsInFile.push_back(materialName);
                }
            }
            
            if(overrideMaterial != "") {
                sceneMeshEntry->addChild("material", overrideMaterial);
            } else {
                sceneMeshEntry->addChild("material", materialName);
            }
            
            
		}
		if (nIgnoredPolygons) {
			printf("Ignored %d non-triangular polygons\n", nIgnoredPolygons);
		}
	}
	   
	// draw all children
	for (n = 0; n < nd->mNumChildren; ++n) {
		addToMesh(prefix, tmesh, sc, nd->mChildren[n], swapZY, addSubmeshes, listOnly, parentSceneObject, overrideMaterial, materialsParent, assetPrefixPath, baseFileName);
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

int exportToFile(String prefix, bool swapZY, bool addSubmeshes, bool listOnly, bool exportEntity, bool generateMaterialFile, String overrideMaterial, String assetPrefixPath, String baseFileName) {

    Object materialObject;
    ObjectEntry *materialsParent = NULL;;
    
    if(generateMaterialFile) {
        materialObject.root.name = "polycode";
        materialsParent = materialObject.root.addChild("materials");
    }
    
    Object sceneObject;
    sceneObject.root.name = "entity";
    sceneObject.root.addChild("version", 2);
    ObjectEntry *parentEntry = sceneObject.root.addChild("root");
    
    parentEntry->addChild("id", "");
    parentEntry->addChild("tags", "");
    parentEntry->addChild("type", "Entity");
    parentEntry->addChild("cR", "1");
    parentEntry->addChild("cG", "1");
    parentEntry->addChild("cB", "1");
    parentEntry->addChild("cA", "1");
    parentEntry->addChild("blendMode", "0");
	parentEntry->addChild("sX", Number(1.0));
	parentEntry->addChild("sY", Number(1.0));
	parentEntry->addChild("sZ", Number(1.0));
    
	parentEntry->addChild("rX", Number(0.0));
	parentEntry->addChild("rY", Number(0.0));
	parentEntry->addChild("rZ", Number(0.0));
	parentEntry->addChild("rW", Number(1.0));
    
	parentEntry->addChild("pX", Number(0.0));
	parentEntry->addChild("pY", Number(0.0));
	parentEntry->addChild("pZ", Number(0.0));
    
	parentEntry->addChild("bbX", Number(0.0));
	parentEntry->addChild("bbY", Number(0.0));
	parentEntry->addChild("bbZ", Number(0.0));
    
    ObjectEntry *children = parentEntry->addChild("children");

		
	Polycode::Mesh *mesh = new Polycode::Mesh(Mesh::TRI_MESH);
    mesh->indexedMesh = true;
	addToMesh(prefix, mesh, scene, scene->mRootNode, swapZY, addSubmeshes, listOnly, children, overrideMaterial, materialsParent, assetPrefixPath, baseFileName);
    
	
	if(addSubmeshes) {
		String fileNameMesh;
		if(prefix != "") {
			fileNameMesh = prefix+".mesh";			
		} else {
			fileNameMesh = "out.mesh";
		}		

		if(listOnly) {
			printf("%s\n", fileNameMesh.c_str());
		} else {
			OSFILE *outFile = OSBasics::open(fileNameMesh.c_str(), "wb");	
			mesh->saveToFile(outFile, writeNormals, writeTangents, writeColors, writeBoneWeights, writeUVs, writeSecondaryUVs);
			OSBasics::close(outFile);
		}
	}
		
	if(hasWeights) {		
		if(listOnly) {
			printf("%s.skeleton\n", prefix.c_str());
		} else {
			printf("Mesh has weights, exporting skeleton...\n");
		}	
		
		String fileNameSkel;
        if(prefix != "") {
            fileNameSkel = prefix+".skeleton";
        } else {
            fileNameSkel = "out.skeleton";
        }
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
				
				if(listOnly) {
					printf("%s%s.anim\n", prefix.c_str(), a->mName.data);
				} else {
					printf("Importing '%s' (%d tracks)\n", a->mName.data, a->mNumChannels);					
				}	
				
			
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

		if(!listOnly) {
			skeleton->saveToFile(fileNameSkel.c_str(), swapZY);
		}
	} else {
		if(!listOnly) {
			printf("No weight data, skipping skeleton export...\n");
		}
	}
    
    String matFileName = baseFileName+".mat";
    if(!listOnly && materialsParent) {
        materialObject.saveToXML(matFileName);
    }
    
    if(!listOnly && exportEntity) {
        
        if(materialsParent) {
            ObjectEntry *settings = sceneObject.root.addChild("settings");
            ObjectEntry *matFiles = settings->addChild("matFiles");
            ObjectEntry *matFile = matFiles->addChild("matFile");
            matFile->addChild("path", assetPrefixPath+matFileName);
            
        }
        
		String entityFileName = baseFileName+".entity";
        sceneObject.saveToXML(entityFileName);
    }

	if(mesh) {
		delete mesh;
	}
	return 1;
}

int main(int argc, char **argv) {


	bool argsValid = true;
	bool showHelp = false;

	bool swapZYAxis = false;
	bool generateTangents = false;
	bool addSubmeshes = false;
	bool listOnly = false;
	bool showAssimpDebug = false;
    bool generateNormals = false;
    bool exportEntity = false;
	bool generateMaterialFile = false;
    String overrideMaterial;
    
	String prefix;
    String assetPrefixPath;
	
	int opt;
	while ((opt = getopt(argc, argv, "engcwuvadlhp:stmfo:x:")) != -1) {
		switch ((char)opt) {
            case 'e':
                exportEntity = true;
            break;
            case 'n':
                writeNormals = true;
            break;
            case 'g':
                writeTangents = true;
            break;
            case 'c':
                writeColors = true;
            break;
            case 'w':
                writeBoneWeights = true;
            break;
            case 'u':
                writeUVs = true;
            break;
            case 'v':
                writeSecondaryUVs = true;
            break;
			case 's':
				swapZYAxis = true;
			break;
			case 't':
				generateTangents = true;
			break;
			case 'm':
				generateNormals = true;
                break;
			case 'a':
				addSubmeshes = true;
			break;
			case 'd':
				showAssimpDebug = true;
			break;				
			case 'l':
				listOnly = true;
			break;				
			case 'p':
				prefix = String(optarg);
			break;
			case 'h':
				showHelp = true;
			break;
            case 'f':
                generateMaterialFile = true;
            break;
			case 'o':
				overrideMaterial = String(optarg);
            break;
			case 'x':
				assetPrefixPath = String(optarg)+"/";
            break;
			default:
				argsValid = false;
			break;
		}
	}

	if(listOnly && argc < 3) {
		argsValid = false;
	}
		
	if(!listOnly) {
		printf("Polycode import tool v"POLYCODE_VERSION_STRING"\n");	
	}
	
	if(!argsValid) {
		printf("Invalid arguments! Run with -h to see available options.\n\n");
		return 0;		
	}
	
	if(showHelp || argc < 2) {
		printf("usage: polyimport [-adhlstngcwuvmef] [-o override_material] [-p output_prefix] [-x asset_path] source_file\n\n");
		printf("Misc options:\n");
		printf("d: Show Assimp debug info.\n");
		printf("h: Show this help.\n");
		printf("l: List output files, but do not convert.\n");
		printf("p: Specify a file prefix for exported files.\n");
		printf("\nMesh import options:\n");
		printf("a: Add all meshes to a single mesh.\n");
		printf("s: Swap Z/Y axis (e.g. import from Blender)\n");
		printf("m: Generate normals.\n");
		printf("t: Generate tangents.\n");
		printf("\nMesh export options:\n");
		printf("n: Export normals\n");
		printf("g: Export tangents\n");
		printf("c: Export colors\n");
		printf("w: Export bone weights\n");
		printf("u: Export UV coordinates\n");
		printf("v: Export secondary UV coordinates\n");
		printf("\nEntity export options:\n");
		printf("e: Export entity scene\n");
		printf("f: Generate material file\n");
		printf("o: Specify override material.\n");
		printf("x: Specify asset prefix path.\n");
		printf("\n");
		return 0;
	}
	
	PHYSFS_init(argv[0]);
	
	if(showAssimpDebug) {
		struct aiLogStream stream;
		stream = aiGetPredefinedLogStream(aiDefaultLogStream_STDOUT,NULL);
		aiAttachLogStream(&stream);
	}
		
	int inputArg = argc-1;

	if(!listOnly) {
		printf("Loading %s...\n", argv[inputArg]);
	}
    
    String baseFileName = String(argv[inputArg]);

	std::vector<String> parts = baseFileName.split("/");	
	if(parts.size() > 1) {
        baseFileName = parts[parts.size()-1];
	}
    
    baseFileName = baseFileName.substr(0, baseFileName.find_last_of("."));
    
	scene = aiImportFile(argv[inputArg], aiProcess_JoinIdenticalVertices|
                         aiProcess_Triangulate);
    
    if(scene) {

        if(generateTangents && !listOnly) {
            aiApplyPostProcessing(scene, aiProcess_CalcTangentSpace);
        }
        
        if(generateNormals && !listOnly) {
            aiApplyPostProcessing(scene, aiProcess_GenSmoothNormals);
        }
        
		exportToFile(prefix, swapZYAxis, addSubmeshes, listOnly, exportEntity, generateMaterialFile, overrideMaterial, assetPrefixPath, baseFileName);
	} else {
		printf("Error opening scene (%s)\n", aiGetErrorString());
	}

	aiReleaseImport(scene);
	return 1;
}
