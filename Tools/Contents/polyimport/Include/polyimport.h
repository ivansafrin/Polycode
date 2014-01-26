#include "assimp.h"

#include "assimp.h"
#include "aiPostProcess.h"
#include "aiScene.h"
#include <stdio.h>
#include "PolyMesh.h"
#include "PolyString.h"
#include <vector>

using std::vector;


class IBone {
	public:
		IBone() {
			parent = NULL;
		}

	IBone *parent;

	aiString name;
	aiMatrix4x4 t;
	aiMatrix4x4 bindMatrix;

	unsigned int boneID;

	vector<IBone*> children;
};	

class ITrack {
	public:
		ITrack(){}
        aiNodeAnim *nodeAnim;
        Polycode::String boneName;
};

class IAnimation {
	public:
		 IAnimation(){}

	Polycode::String name;
	unsigned int numTracks;
	float tps;

	float length;

	vector<ITrack*> tracks;
};

bool BonesSortPredicate(const IBone* d1, const IBone* d2)
{
  return d1->boneID < d2->boneID;
}

class ISkeleton {
	public:
		ISkeleton() {
		}

	void addIBone(IBone *bone, int boneID) {
		bone->boneID = boneID;
		bones.push_back(bone);
	}

	unsigned int getBoneID(aiString name) {
		for(int i=0; i < bones.size(); i++) {
			if(bones[i]->name == name) {
				return i;
			}
		}
		return -1;
	}

	void saveToFile(const char *fileName, bool swapZY) {
		using Polycode::String;
		String fileNameSkel = String(fileName);
		FILE *file = fopen(fileNameSkel.c_str(), "wb");
		unsigned int numBones = bones.size();
		
		fwrite(&numBones, sizeof(unsigned int), 1, file);
		
		std::sort(bones.begin(), bones.end(), BonesSortPredicate);
		for(int i=0; i < bones.size(); i++) {
			bones[i]->boneID = i;
		}

		for(int i=0; i < animations.size(); i++) {
			IAnimation *anim = animations[i];
			for(int j=0; j < anim->numTracks; j++) {
				anim->tracks[j]->boneName = anim->tracks[j]->nodeAnim->mNodeName.data;
			}
		}

		for(int i=0; i < bones.size(); i++) {
			unsigned int len = bones[i]->name.length;
			fwrite(&len, sizeof(unsigned int), 1, file);
			fwrite(bones[i]->name.data, 1, len, file);
		
			unsigned int hasParent;
			if(bones[i]->parent) {
				hasParent = 1;
				fwrite(&hasParent, sizeof(unsigned int), 1, file);
				fwrite(&bones[i]->parent->boneID, sizeof(unsigned int), 1, file);
			} else {
				hasParent = 0;
				fwrite(&hasParent, sizeof(unsigned int), 1, file);
			}

			aiVector3D scale;
			aiQuaternion rotation;
			aiVector3D position; 
			bones[i]->t.Decompose(scale, rotation, position);

			fwrite(&position.x, sizeof(float), 1, file);
			if(swapZY) {
				fwrite(&position.z, sizeof(float), 1, file);
				position.y *= -1;
				fwrite(&position.y, sizeof(float), 1, file);
			} else {
				fwrite(&position.y, sizeof(float), 1, file);
				fwrite(&position.z, sizeof(float), 1, file);
			}
			
			fwrite(&scale.x, sizeof(float), 1, file);
			if(swapZY) {
				fwrite(&scale.z, sizeof(float), 1, file);
				fwrite(&scale.y, sizeof(float), 1, file);
			} else {
				fwrite(&scale.y, sizeof(float), 1, file);
				fwrite(&scale.z, sizeof(float), 1, file);
			}
	
			fwrite(&rotation.w, sizeof(float), 1, file);
			fwrite(&rotation.x, sizeof(float), 1, file);

			if(swapZY) {
				fwrite(&rotation.z, sizeof(float), 1, file);
				rotation.y *= -1;
				fwrite(&rotation.y, sizeof(float), 1, file);
			} else {
				fwrite(&rotation.y, sizeof(float), 1, file);
				fwrite(&rotation.z, sizeof(float), 1, file);
			}

			bones[i]->bindMatrix.Decompose(scale, rotation, position);

			fwrite(&position.x, sizeof(float), 1, file);
			if(swapZY) {
				fwrite(&position.z, sizeof(float), 1, file);
				position.y *= -1;
				fwrite(&position.y, sizeof(float), 1, file);
			} else {
				fwrite(&position.y, sizeof(float), 1, file);
				fwrite(&position.z, sizeof(float), 1, file);
			}
			
			fwrite(&scale.x, sizeof(float), 1, file);
			if(swapZY) {
				fwrite(&scale.z, sizeof(float), 1, file);
				fwrite(&scale.y, sizeof(float), 1, file);
			} else {
				fwrite(&scale.y, sizeof(float), 1, file);
				fwrite(&scale.z, sizeof(float), 1, file);
			}
	
			fwrite(&rotation.w, sizeof(float), 1, file);
			fwrite(&rotation.x, sizeof(float), 1, file);

			if(swapZY) {
				fwrite(&rotation.z, sizeof(float), 1, file);
				rotation.y *= -1;
				fwrite(&rotation.y, sizeof(float), 1, file);
			} else {
				fwrite(&rotation.y, sizeof(float), 1, file);
				fwrite(&rotation.z, sizeof(float), 1, file);
			}

		}

		fclose(file);	

	//	unsigned int numAnimations = animations.size();
	//	fwrite(&numAnimations, sizeof(unsigned int), 1, file);
        
        
		for(int i=0; i < animations.size(); i++) {

			char anim_s[2];
			sprintf(anim_s, "%d", i);
			String fileNameAnim = String(fileName)+"_animation";//+anim+".anim";
			fileNameAnim += anim_s;
			fileNameAnim += ".anim";
			file = fopen(fileNameAnim.c_str(), "wb");
	
			IAnimation *anim = animations[i];

		//	unsigned int len = anim->name.size();
		//	fwrite(&len, sizeof(unsigned int), 1, file);
		//	fwrite(anim->name.c_str(), 1, len, file);
			fwrite(&anim->length, sizeof(float), 1, file);
	
			fwrite(&anim->numTracks, sizeof(unsigned int), 1, file);
            
			for(int j=0; j < anim->numTracks; j++) {
				ITrack *track = anim->tracks[j];
                
                unsigned short boneNameLen = track->boneName.length();
				fwrite(&boneNameLen, sizeof(unsigned short), 1, file);
                
                char boneNameBuffer[1024];
                memcpy(boneNameBuffer, track->boneName.c_str(), boneNameLen);
                fwrite(boneNameBuffer, 1, boneNameLen, file);
                
				aiNodeAnim *nodeAnim = track->nodeAnim;

				unsigned int curveType,numPoints;
				unsigned int numCurves = 10;

				if(nodeAnim->mNumPositionKeys < 2) {
					numCurves -= 3;
				}
				

				fwrite(&numCurves, sizeof(unsigned int), 1, file);

				curveType = 0;
				numPoints = nodeAnim->mNumScalingKeys;
				fwrite(&curveType, sizeof(unsigned int), 1, file);
				fwrite(&numPoints, sizeof(unsigned int), 1, file);
				for(int f =0; f < nodeAnim->mNumScalingKeys; f++) {
					aiVectorKey key = nodeAnim->mScalingKeys[f];
					fwrite(&key.mValue.x, sizeof(float), 1, file);
					float time = key.mTime;
					fwrite(&time, sizeof(float), 1, file);
				}


				if(swapZY) {
					curveType = 2;
				} else {
					curveType = 1;
				}
				numPoints = nodeAnim->mNumScalingKeys;
				fwrite(&curveType, sizeof(unsigned int), 1, file);
				fwrite(&numPoints, sizeof(unsigned int), 1, file);
				for(int f =0; f < nodeAnim->mNumScalingKeys; f++) {
					aiVectorKey key = nodeAnim->mScalingKeys[f];
					fwrite(&key.mValue.y, sizeof(float), 1, file);
					float time = key.mTime;
					fwrite(&time, sizeof(float), 1, file);
				}

				if(swapZY) {
					curveType = 1;
				} else {
					curveType = 2;
				}
				numPoints = nodeAnim->mNumScalingKeys;
				fwrite(&curveType, sizeof(unsigned int), 1, file);
				fwrite(&numPoints, sizeof(unsigned int), 1, file);
				for(int f =0; f < nodeAnim->mNumScalingKeys; f++) {
					aiVectorKey key = nodeAnim->mScalingKeys[f];
					fwrite(&key.mValue.z, sizeof(float), 1, file);
					float time = key.mTime;
					fwrite(&time, sizeof(float), 1, file);
				}

				curveType = 3;
				numPoints = nodeAnim->mNumRotationKeys;
				fwrite(&curveType, sizeof(unsigned int), 1, file);
				fwrite(&numPoints, sizeof(unsigned int), 1, file);
				for(int f =0; f < nodeAnim->mNumRotationKeys; f++) {
					aiQuatKey key = nodeAnim->mRotationKeys[f];
					float val = key.mValue.w;
					fwrite(&val, sizeof(float), 1, file);
					float time = key.mTime;
					fwrite(&time, sizeof(float), 1, file);
				}

				curveType = 4;
				numPoints = nodeAnim->mNumRotationKeys;
				fwrite(&curveType, sizeof(unsigned int), 1, file);
				fwrite(&numPoints, sizeof(unsigned int), 1, file);
				for(int f =0; f < nodeAnim->mNumRotationKeys; f++) {
					aiQuatKey key = nodeAnim->mRotationKeys[f];
					fwrite(&key.mValue.x, sizeof(float), 1, file);
					float time = key.mTime;
					fwrite(&time, sizeof(float), 1, file);
				}

				if(swapZY) {
					curveType = 6;
				} else {
					curveType = 5;
				}
				numPoints = nodeAnim->mNumRotationKeys;
				fwrite(&curveType, sizeof(unsigned int), 1, file);
				fwrite(&numPoints, sizeof(unsigned int), 1, file);
				for(int f =0; f < nodeAnim->mNumRotationKeys; f++) {
					aiQuatKey key = nodeAnim->mRotationKeys[f];
					float val = key.mValue.y;
					if(swapZY) {
						val *= -1;
					}
					fwrite(&val, sizeof(float), 1, file);
					float time = key.mTime;
					fwrite(&time, sizeof(float), 1, file);
				}

				if(swapZY) {
					curveType = 5;
				} else {
					curveType = 6;
				}
				numPoints = nodeAnim->mNumRotationKeys;
				fwrite(&curveType, sizeof(unsigned int), 1, file);
				fwrite(&numPoints, sizeof(unsigned int), 1, file);
				for(int f =0; f < nodeAnim->mNumRotationKeys; f++) {
					aiQuatKey key = nodeAnim->mRotationKeys[f];
					fwrite(&key.mValue.z, sizeof(float), 1, file);
					float time = key.mTime;
					fwrite(&time, sizeof(float), 1, file);
				}

				curveType = 7;
				numPoints = nodeAnim->mNumPositionKeys;
				if(numPoints > 1) {
				fwrite(&curveType, sizeof(unsigned int), 1, file);
				fwrite(&numPoints, sizeof(unsigned int), 1, file);
				for(int f =0; f < nodeAnim->mNumPositionKeys; f++) {
					aiVectorKey key = nodeAnim->mPositionKeys[f];
					fwrite(&key.mValue.x, sizeof(float), 1, file);
					float time = key.mTime;
					fwrite(&time, sizeof(float), 1, file);
				}
				}

				if(swapZY) {
					curveType = 9;
				} else {
					curveType = 8;
				}
				numPoints = nodeAnim->mNumPositionKeys;
				if(numPoints > 1) {
				fwrite(&curveType, sizeof(unsigned int), 1, file);
				fwrite(&numPoints, sizeof(unsigned int), 1, file);
				for(int f =0; f < nodeAnim->mNumPositionKeys; f++) {
					aiVectorKey key = nodeAnim->mPositionKeys[f];
					float val = key.mValue.y;
					if(swapZY) {
						val *= -1;
					}
					fwrite(&val, sizeof(float), 1, file);
					float time = key.mTime;
					fwrite(&time, sizeof(float), 1, file);
				}
				}

				if(swapZY) {
					curveType = 8;
				} else {
					curveType = 9;
				}
				numPoints = nodeAnim->mNumPositionKeys;
				if(numPoints > 1) {
				fwrite(&curveType, sizeof(unsigned int), 1, file);
				fwrite(&numPoints, sizeof(unsigned int), 1, file);
				for(int f =0; f < nodeAnim->mNumPositionKeys; f++) {
					aiVectorKey key = nodeAnim->mPositionKeys[f];
					fwrite(&key.mValue.z, sizeof(float), 1, file);
					float time = key.mTime;
					fwrite(&time, sizeof(float), 1, file);
				}
				}

		
			}
			fclose(file);	
		}


	}

	void addAnimation(IAnimation *anim) { animations.push_back(anim); }

	vector<IAnimation*> animations;
	vector<IBone*> bones;
};
