/*
 *  PolyMesh.h
 *  TAU
 *
 *  Created by Ivan Safrin on 3/18/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

// @package BasicTypes
 
#pragma once
#include "PolyString.h"
#include <math.h>
#include "PolyGlobals.h"
#include "PolyPolygon.h"
#include "PolyVertex.h"
#include <string>
#include <vector>
#include "OSBasics.h"

using namespace std;
 
namespace Polycode {
	
	class _PolyExport VertexBuffer {
		public:	
			VertexBuffer(){}
			virtual ~VertexBuffer(){}
		
			int getVertexCount() { return vertexCount;}
		
			int verticesPerFace;
			int meshType;
		protected:
		int vertexCount;
			
	};
	
	class _PolyExport RenderDataArray {
	public:
		int arrayType;
		int stride;
		int size;
		void *arrayPtr;
		void *rendererData;
		int count;
		
		static const int VERTEX_DATA_ARRAY = 0;
		static const int COLOR_DATA_ARRAY = 1;		
		static const int NORMAL_DATA_ARRAY = 2;				
		static const int TEXCOORD_DATA_ARRAY = 3;
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
	
	class _PolyExport Mesh {
		public:
			Mesh(String fileName);
			Mesh(int meshType);
			~Mesh();
			
			void addPolygon(Polygon *newPolygon);
			
			void loadMesh(String fileName);

			void loadFromFile(OSFILE *inFile);
			void saveToFile(OSFILE *outFile);
			
			unsigned int getPolygonCount();
			Polygon *getPolygon(unsigned int index);
					
			void createPlane(Number w, Number h);
			void createBox(Number w, Number d, Number h);
			void createSphere(Number radius, Number numRings, Number numSegments);
		
			void addVertex(Vertex* vertex);
			Vertex *getVertex(unsigned int index);
			unsigned int getNumVertices();
				
			Vector3 recenterMesh();
		
			void useVertexNormals(bool val);
			int getVertexIndex(Vertex *vertex);
			
			void setVertexBuffer(VertexBuffer *buffer);
			VertexBuffer *getVertexBuffer();
		
			bool usesFaceUV() { return useFaceUV; }
			Number getRadius();
			
			void calculateNormals();	
			
			int getMeshType();
			void setMeshType(int newType);

			Vector3 calculateBBox();
		
			bool hasVertexBuffer() { return meshHasVertexBuffer; }
	
			static const int QUAD_MESH = 0;			
			static const int TRI_MESH = 1;				
			static const int TRIFAN_MESH = 2;
			static const int TRISTRIP_MESH = 3;
			static const int LINE_MESH = 4;
			static const int POINT_MESH = 5;
		
			unsigned int numUVs;			
					
			bool arrayDirtyMap[16];
			RenderDataArray *renderDataArrays[16];
		
			bool useVertexColors;
		
		private:
		
				
		VertexBuffer *vertexBuffer;
		bool meshHasVertexBuffer;
		
		
		int meshType;
		bool useFaceUV;

		
		vector <Polygon*> polygons;
		vector <Vertex*> vertices;
	};
}