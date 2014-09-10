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

#pragma once
#include "PolyGlobals.h"
#include "PolyString.h"
#include "PolyMatrix4.h"
#include "PolyEntity.h"

namespace Polycode {

	class Mesh;

	/** 
	* Skeleton bone. Bones are bound to vertices of a mesh and when transformed, move the bound vertices of the mesh along with them. Bones are subclassed from Entity, but have their own hierarchy system.
	* @see Skeleton
	*/			
	class _PolyExport Bone : public Entity {
		public:
			/** 
			* Constructor.
			* @param boneName Name of the bone.
			*/				
			explicit Bone(const String& boneName);
			virtual ~Bone();
			
			/**
			* Returns the name of the bone.
			* @return Name of the bone.
			*/
			String getName() const;

			/**
			* Sets the parent bone of this bone.
			* @param bone New parent bone.
			*/
			void setParentBone(Bone *bone);
			
			/**
			* Adds another bone as the child of this bone.
			* @param bone New parent bone.
			*/			
			void addChildBone(Bone *bone);
			
			/**
			* Returns the parent bone of this bone.
			* @return Parent bone of this bone.
			*/						
			Bone* getParentBone();
			
			/**
			* Returns the number of child bones of this bone.
			* @return Number of child bones.
			*/									
			int getNumChildBones();
			
			/**
			* Returns the child bone of this bone at the specified index.
			* @param index Index of the child bone to return.
			* @return Parent bone of this bone.
			*/									
			Bone *getChildBone(unsigned int index);

			/**
			* Returns the bone matrix
			* @return Bone matrix.
			*/									
			Matrix4 getBoneMatrix() const;
			
			/**
			* Sets the bone matrix.
			* @return Bone matrix.
			*/												
			void setBoneMatrix(const Matrix4& matrix);
			
			/**
			* Returns the rest matrix of this bone.
			* @return Rest matrix.
			*/															
			Matrix4 getRestMatrix() const;
			
			/**
			* Returns the full rest matrix of this bone.
			* @return Full rest matrix.
			*/																		
			Matrix4 getFullRestMatrix() const;
			
			/**
			* Returns the rest matrix of this bone's parent.
			* @return Rest matrix of the bone's parent.
			*/																					
			Matrix4 getParentRestMatrix() const;
			
			/**
			* @see getBoneMatrix()
			*/																								
			Matrix4 getFinalMatrix() const;
			
			/**
			* Sets the rest matrix for this bone.
			* @param matrix New rest matrix.
			*/
			void setRestMatrix(const Matrix4& matrix);
			
			/**
			* Sets the base matrix for this bone.
			* @param matrix New base matrix.
			*/			
			void setBaseMatrix(const Matrix4& matrix);
			
			/**
			* Returns the base matrix of this bone.
			* @return Base matrix.
			*/			
			const Matrix4& getBaseMatrix() const { return baseMatrix; }
			
			/**
			* Returns the full base matrix of this bone.
			* @return Full base matrix.
			*/						
			Matrix4 getFullBaseMatrix() const;
        
            void rebuildFinalMatrix();
            Matrix4 buildFinalMatrix() const;
		
			/**
			* Id of the bone.
			*/								
			int parentBoneId;			

			Matrix4 boneMatrix;
			Matrix4 restMatrix;
			Matrix4 baseMatrix;
            Matrix4 finalMatrix;
		
            Quaternion baseRotation;
            Vector3 baseScale;
            Vector3 basePosition;
        
            bool disableAnimation;
        
		protected:
			Bone* parentBone;
			std::vector<Bone*> childBones;
			String boneName;
	};

}
