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
#include "PolyVector3.h"
#include "PolyVector2.h"
#include "PolyColor.h"
#include <vector>

namespace Polycode {

class Bone;

/**
* Bone assignment.
*/ 
class _PolyExport BoneAssignment {
	public:
		BoneAssignment(){
			bone = NULL;
		}
		/**
		* Id of the bone assigned.
		*/
		unsigned int boneID;

		/**
		* Assignment weight.
		*/
		Number weight;

		/**
		* Assigned bone.
		*/
		Bone *bone;
};

/**
* A mesh vertex.
*/
class _PolyExport Vertex : public Vector3 {
	public:

		/**
		* Default constructor.
		*/
		Vertex();

		/**
		* Initialize with position.
		* @param pos_x Position x.
		* @param pos_y Position y.
		* @param pos_z Position z.
		*/
		Vertex(Number x, Number y, Number z);

		/**
		* Initialize with position and normal.
		* @param pos_x Position x.
		* @param pos_y Position y.
		* @param pos_z Position z.
		* @param nor_x Normal x.
		* @param nor_y Normal y.
		* @param nor_z Normal z.
		*/
		Vertex(Number pos_x, Number pos_y, Number pos_z, Number nor_x, Number nor_y, Number nor_z);

		/**
		* Initialize with position and normal and texture coordinates.
		* @param pos_x Position x.
		* @param pos_y Position y.
		* @param pos_z Position z.
		* @param nor_x Normal x.
		* @param nor_y Normal y.
		* @param nor_z Normal z.
		* @param u Horizontal texture coordinate.
		* @param v Vertical texture coordinate.
		*/
		Vertex(Number pos_x, Number pos_y, Number pos_z, Number nor_x, Number nor_y, Number nor_z, Number u, Number v);

		/**
		* Initialize with position and texture coordinates.
		* @param pos_x Position x.
		* @param pos_y Position y.
		* @param pos_z Position z.
		* @param u Horizontal texture coordinate.
		* @param v Vertical texture coordinate.
		*/
		Vertex(Number x, Number y, Number z, Number u, Number v);

		virtual ~Vertex();

		/**
		* Assign a bone to the vertex by bone id.
		* @param boneID The bone id.
		* @param boneWeight Normalized weight of the bone assignment.
		*/ 
		void addBoneAssignment(unsigned int boneID, Number boneWeight);

		/**
		* Get total number of bone assignments.
		* @return Number of bone assignments.
		*/
		int getNumBoneAssignments();

		/**
		* Get bone assignment at index.
		* @param Index of bone assignment.
		* @return Bone assignment at index.
		*/
		BoneAssignment *getBoneAssignment(unsigned int index);

		/**
		* Normalizes all current weight assignments.
		*/
		void normalizeWeights();

		/**
		* Returns the texture coordinates.
		* @return Texture coordinates.
		*/
		Vector2 getTexCoord();

		/**
		* Sets the texture coordinates.
		* @param u New horizontal texture coordinate.
		* @param v New vertical texture coordinate.
		*/
		void setTexCoord(Number u, Number v);

		/**
		* Sets the normal
		* @param x Normal x.
		* @param y Normal y.
		* @param z Normal z.
		*/
		void setNormal(Number x, Number y, Number z);

		/**
		* Rest normal.
		*/
		Vector3 restNormal;

		/**
		* Rest position.
		*/
		Vector3 restPosition;

		/**
		* Vertex normal.
		*/
		Vector3 normal;

		/**
		* Vertex tangent.
		*/
		Vector3 tangent;

		/**
		* Vertex color.
		*/
		Color vertexColor;

		/**
		* Texture coordinates
		*/
		Vector2 texCoord;

		bool useVertexColor;

	protected:

		std::vector <BoneAssignment*> boneAssignments;

};

}
