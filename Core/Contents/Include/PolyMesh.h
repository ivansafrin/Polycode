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
#include "PolyRenderDataArray.h"
#include "PolyColor.h"
#include "PolyVector3.h"
#include "PolyVector2.h"
#include <vector>

class OSFILE;

namespace Polycode {
	
	class String;
	
	class _PolyExport VertexBuffer : public PolyBase {
		public:	
			VertexBuffer(){}
			virtual ~VertexBuffer(){}
		
			int getVertexCount() const { return vertexCount;}
			int getIndexCount() const { return indexCount;}
		
			int verticesPerFace;
			int meshType;
		protected:
            int vertexCount;
            int indexCount;
			
	};
		
	typedef struct {
		float x;
		float y;
		float z;
		float w;
	} Vector4_struct;
	
	typedef struct {
		float x;
		float y;
		float z;
	} Vector3_struct;

	typedef struct {
		float x;
		float y;
	} Vector2_struct;
	
	/**
	*  A mesh comprised of vertices. When data in the mesh changes, arrayDirtyMap must be set to true for the appropriate array types (color, position, normal, etc). Available types are defined in RenderDataArray.
	*/
	class _PolyExport Mesh : public PolyBase {
		public:
		
			
			/**
			* Construct with an empty mesh of specified type.
			* @param meshType Type of mesh. Possible values are: Mesh::QUAD_MESH, Mesh::TRI_MESH, Mesh::TRIFAN_MESH, Mesh::TRISTRIP_MESH, Mesh::LINE_MESH, Mesh::POINT_MESH.
			*/			
			explicit Mesh(int meshType);
					
			/**
			* Construct from a mesh loaded from a file.
			* @param fileName Path to mesh file.
			*/
			explicit Mesh(const String& fileName);

			/**
			* Construct from a mesh loaded from a file.
			* @param fileName Path to mesh file.
			*/			
			static Mesh *MeshFromFileName(String& fileName);

			virtual ~Mesh();
			
			/**
			* Loads a mesh from a file.
			* @param fileName Path to mesh file.
			*/			
			void loadMesh(const String& fileName);
			
			/**
			* Clears mesh data.
			*/
			
			void clearMesh();

			/**
			* Saves mesh to a file.
			* @param fileName Path to file to save to.
			*/			
			void saveToFile(const String& fileName, bool writeNormals = true, bool writeTangents = true, bool writeColors = true, bool writeBoneWeights = true, bool writeUVs = true, bool writeSecondaryUVs = false);

			void loadFromFile(OSFILE *inFile);

        
			void saveToFile(OSFILE *outFile, bool writeNormals = true, bool writeTangents = true, bool writeColors = true, bool writeBoneWeights = true, bool writeUVs = true, bool writeSecondaryUVs = false);
			
			
			/**
			* Returns the total vertex count in the mesh.
			* @return Number of vertices in the mesh.
			*/
			unsigned int getVertexCount();
			
					
			/**
			* Creates a plane mesh of specified size.
			* @param w Width of plane.
			* @param h Depth of plane.			
			*/ 
			void createPlane(Number w, Number h);
			
			/**
			* Creates a vertical plane mesh of specified size.
			* @param w Width of plane.
			* @param h Depth of plane.			
			*/ 
			void createVPlane(Number w, Number h);

			/**
			* Creates a 2D circle.
			* @param w Width of circle.
			* @param h Height of plane.			
			* @param numSegments Number of segments 			
			*/ 
			void createCircle(Number w, Number h, unsigned int numSegments);

            /**
             * Creates a 2D circle with normals pointing outwards from vertices.
             * @param w Width of circle.
             * @param h Height of plane.
             * @param numSegments Number of segments
             */
            void createLineCircle(Number w, Number h, unsigned int numSegments);

			/**
			* Creates a torus.
			* @param radius Radius of the torus.
			* @param tubeRadius Radious of the tube.
			* @param rSegments Number of radial segments.
			* @param tSegments Number of tube segments.
			*/ 	
			void createTorus(Number radius, Number tubeRadius, int segmentsW, int segmentsH);
			
			/**
			* Creates a cube mesh of specified size.
			* @param w Width of cube.
			* @param d Depth of cube.			
			* @param h Height of cube.
			*/ 			
			void createBox(Number w, Number d, Number h);
			
			/**
			* Creates a sphere mesh of specified size.
			* @param radius Radius of sphere.
			* @param numRings Number of rings.	
			* @param numSegments Number of segments.
			*/ 						
			void createSphere(Number radius, int numRings, int numSegments);

			/**
			* Creates an icosphere of specified radius
			* @param radius Radius of sphere.
			* @param subdivisions 0 means you get an icosahedron, don't recommend ever going above about 4 or 5 as they get really big
			*/
			void createIcosphere(Number radius, int subdivisions);

			/**
			* Creates an octosphere of specified radius
			* @param radius Radius of sphere.
			* @param subdivisions 0 means you get an octagon, don't recommend ever going too high as they get really big
			*/
			void createOctosphere(Number radius, int subdivisions);

			/**
			* Creates a cylinder mesh.
			* @param height Height of the cylinder.
			* @param radius Radius of the cylinder.
			* @param numSegments Number of segments.
			* @param capped Create the end caps.
			*/ 								
			void createCylinder(Number height, Number radius, int numSegments, bool capped=true);

			/**
			* Creates a cone mesh.
			* @param height Height of the cone.
			* @param radius Radius of the cone.
			* @param numSegments Number of segments.
			*/ 								
			void createCone(Number height, Number radius, int numSegments);

		
			/**
			* Recenters the mesh with all vertices being as equidistant from origin as possible.
			*/
			Vector3 recenterMesh();

            void setVertexAtOffset(unsigned int offset, Number x, Number y, Number z);
        
            void addVertexWithUVAndNormal(Number x, Number y, Number z, Number u, Number v, Number nx, Number ny, Number nz);
		
            void addTexCoord(Number u, Number v);
            void addTexCoord2(Number u, Number v);
        
            void addTangent(Number x, Number y, Number z);
        
            void addVertexWithUV(Number x, Number y, Number z, Number u, Number v);
        
            void addVertex(Number x, Number y, Number z);
        
            void addNormal(Number nx, Number ny, Number nz);
            void addNormal(const Vector3 &n);

            void addBoneAssignments(Number b1Weight, unsigned int b1Index, Number b2Weight, unsigned int b2Index, Number b3Weight, unsigned int b3Index, Number b4Weight, unsigned int b4Index);
        
            void addColor(Number r, Number g, Number b, Number a);
            void addColor(const Color &color);
        
        
            Vector3 getVertexPosition(unsigned int vertexOffset);
        
            Vector3 getVertexPositionAtIndex(unsigned int index);

            Vector2 getVertexTexCoord(unsigned int vertexOffset);
        
            Vector2 getVertexTexCoordAtIndex(unsigned int index);
        
        
			/**
			* Sets the vertex buffer for the mesh.
			* @param buffer New vertex buffer for mesh.
			*/			
			void setVertexBuffer(VertexBuffer *buffer);
			
			/**
			* Returns the vertex buffer for the mesh.
			* @return The vertex buffer for this mesh.
			*/
			VertexBuffer *getVertexBuffer();
        
        
            Mesh *Copy() const;
			
			/**
			* Returns the radius of the mesh (furthest vertex away from origin).
			* @return Mesh radius.
			*/			
			Number getRadius();
			
			/**
			* Recalculates the mesh normals
			* @param smooth If true, will use smooth normals.
			* @param smoothAngle If smooth, this parameter sets the angle tolerance for the approximation function.
			*/
			void calculateNormals();

			/**
			* Recalculates the tangent space vector for all vertices.
			*/ 
			void calculateTangents();
			
			/**
			* Returns the mesh type.
			*/ 
			int getMeshType();
			
			/**
			* Sets a new mesh type.
			* @param newType New mesh type. Possible values are: Mesh::QUAD_MESH, Mesh::TRI_MESH, Mesh::TRIFAN_MESH, Mesh::TRISTRIP_MESH, Mesh::LINE_MESH, Mesh::POINT_MESH.
			*/ 
			void setMeshType(int newType);

			inline unsigned int getIndexGroupSize() {
				switch (meshType) {
				case QUAD_MESH: return 4;
				case TRI_MESH: return 3;
				case LINE_MESH: return 2;
				default: return 1;
				}
			}

			/**
			* Calculates the mesh bounding box.
			*/
			Vector3 calculateBBox();

			/**
			* Checks if the mesh has a vertex buffer.
			* @param True if the mesh has a vertex buffer, false if not.
			*/		
			bool hasVertexBuffer() { return meshHasVertexBuffer; }
	
			/**
			* Quad based mesh.
			*/
			static const int QUAD_MESH = 0;			
			
			/**
			* Triangle based mesh.
			*/			
			static const int TRI_MESH = 1;				
			
			/**
			* Triangle fan based mesh.
			*/						
			static const int TRIFAN_MESH = 2;

			/**
			* Line based mesh.
			*/									
			static const int LINE_MESH = 4;
			
			/**
			* Point based mesh.
			*/									
			static const int POINT_MESH = 5;
		
			/**
			* Line strip based mesh.
			*/									
			static const int LINE_STRIP_MESH = 6;
			
			/**
			* Line loop based mesh.
			*/									
			static const int LINE_LOOP_MESH = 7;
        
        
		
			/**
			* If set to true, the renderer will use the vertex colors instead of entity color transform to render this mesh.
			*/
			bool useVertexColors;
            bool indexedMesh;

            void addIndexedFace(unsigned int i1, unsigned int i2);
            void addIndexedFace(unsigned int i1, unsigned int i2, unsigned int i3);
            void addIndexedFace(unsigned int i1, unsigned int i2, unsigned int i3, unsigned int i4);
			void addIndex(unsigned int index);

			/** Removes a range of vertices starting at beginRemoveVertex. vertexRemovalCount should be a multiple of the num
			 * if you want to keep your mesh data clean. If this is an indexedMesh, will also remove any faces that reference
			 * @param beginRemoveVertex First element of the vertex array to remove
			 * @param vertexRemovalCount Number of elements to remove from the vertex array */
			void removeVertexRange(unsigned int beginRemoveVertex, int vertexRemovalCount = 3);

			/** Removes a face from the mesh. Face is defined as a quad for QUAD_MESH, a triangle for TRI_MESH, a line for LI
			 *  In indexedMesh mode this may result in orphaned vertices.
			 * @param faceIndex The 0-indexed face of the mesh (and NOT the index into the indices array!) */
			void removeFace(unsigned int faceIndex);

			/** For indexedMesh only, removes any unused vertices from the mesh. */
			int removeUnusedVertices();
        
            unsigned int getIndexCount();
        
            void subdivideToRadius(Number radius, int subdivisions);
        
            static Vector3 calculateFaceTangent(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, const Vector2 &texCoord1, const Vector2 &texCoord2, const Vector2 &texCoord3);
        
            void saveAsOBJ(const String fileName);
        
            void normalizeBoneWeights();
        
            VertexDataArray vertexPositionArray;
            VertexDataArray vertexColorArray;
            VertexDataArray vertexNormalArray;
            VertexDataArray vertexTexCoordArray;
            VertexDataArray vertexTexCoord2Array;
            VertexDataArray vertexTangentArray;
        
            VertexDataArray vertexBoneWeightArray;
            VertexDataArray vertexBoneIndexArray;
        
            IndexDataArray indexArray;
        
        protected:
        
            void loadFromFileV2(OSFILE *inFile);
            void loadFromFileLegacyV1(OSFILE *inFile);

            void writeVertexBlock(VertexDataArray *array, OSFILE *outFile);
            void writeIndexBlock(IndexDataArray *array, OSFILE *outFile);
        
            VertexBuffer *vertexBuffer;
            bool meshHasVertexBuffer;
            int meshType;

	};
}
