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
#include "PolyRectangle.h"
#include <vector>

namespace Polycode {

class Vertex;

/**
* A polygon structure.
*/ 
class _PolyExport Polygon : public PolyBase {

	public:
		/**
		* Default constructor.
		*/
		Polygon();
		virtual ~Polygon();

		/**
		* Returns the number of vertices in the polygon.
		* @return Number of vertices in the polygon.
		*/ 
		unsigned int getVertexCount();

		/**
		* Returns the vertex at specified index.
		* @return Vertex at specified index.
		*/
		Vertex *getVertex(unsigned int index);

		/**
		* Adds a new vertex with the specified position coordinates and texture coordinates.
		* @param x X coordinate of new vertex.
		* @param y Y coordinate of new vertex.
		* @param z Z coordinate of new vertex.
		* @param u Horizontal texture coordinate.
		* @param v Vertical texture coordinate.
		* @return Newly added vertex.
		*/ 
		Vertex *addVertex(Number x, Number y, Number z, Number u, Number v);

		/**
		* Adds a new vertex with the specified position coordinates.
		* @param x X coordinate of new vertex.
		* @param y Y coordinate of new vertex.
		* @param z Z coordinate of new vertex.
		* @return Newly added vertex.
		*/ 
		Vertex *addVertex(Number x, Number y, Number z);


		/**
		* Adds a new vertex.
		* @param vertex New vertex.
		*/ 
		void addVertex(Vertex *vertex);

		/**
		* Removes and deletes the vertex at specified index. 
		* @param index to remove vertex at.
		*/
		void removeVertex(int index);

		/**
		* Calculates the average normal for the vertices.
		*/
		void calculateNormal();

		/**
		* Calculates the tangent space vector for the vertices.
		*/
		void calculateTangent();

		/**
		* Returns the face normal.
		* @return Face normal.
		*/ 
		Vector3 getFaceNormal();

		/**
		* Returns the face tangent vector.
		* @return Face tangent vector.
		*/ 
		Vector3 getFaceTangent();


		Rectangle getBounds2D();

		/**
		* Sets the polygon normal.
		* @param normal The new normal.
		*/
		void setNormal(Vector3 normal);

		/**
		* If true, will use vertex normals, if false will use the polygon normal.
		*/
		bool useVertexNormals;

		/**
		* Flips the texture coordinate vertically.
		*/
		void flipUVY();

	protected:

		unsigned int vertexCount;
		std::vector<Vertex*> vertices;
		Vector3 normal;
		Vector3 tangent;
};

}
