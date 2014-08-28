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
#include "PolyEntity.h"
#include "PolyShader.h"
#include "PolyRenderDataArray.h"

namespace Polycode {

	class Material;
	class Mesh;
	class Texture;
	class Skeleton;
	class Image;
    class ResourcePool;
	
	/**
	* 3D polygonal mesh instance. The SceneMesh is the base for all polygonal 3d geometry. It can have simple textures or complex materials applied to it.
	*/
	class _PolyExport SceneMesh : public Entity {
		public:
		
			/**
			* Construct a scene mesh from a mesh file.
			* @param fileName Path to mesh file to load.
			*/
			explicit SceneMesh(const String& fileName);
			
			/**
			* Construct an empty scene mesh with the specified type.
			* @param meshType Mesh type to create. See Mesh for possible values.
			*/			
			explicit SceneMesh(int meshType);
			
			/**
			* Construct scene mesh from an existing Mesh instance.
			*/
			explicit SceneMesh(Mesh *mesh);
			
			/**
			* Construct scene mesh from an existing Mesh instance.
			*/			
			static SceneMesh *SceneMeshFromMesh(Mesh *mesh);
			
			/**
			* Construct an empty scene mesh with the specified type.
			* @param meshType Mesh type to create. See Mesh for possible values.
			*/						
			static SceneMesh *SceneMeshWithType(int meshType);
						
			virtual ~SceneMesh();
			
			void Render();
			
            /**
             * Returns the local material binding options for this mesh.
             */
			ShaderBinding *getLocalShaderOptions();
			
			/**
			* Returns the Mesh instance of the actual mesh.
			*/
			Mesh *getMesh();
		
			/**
			* Returns the texture applied.
			*/				
			Texture *getTexture() const;
			
			/**
			* Returns the material applied.
			*/							
			Material *getMaterial();
			
			/**
			* Loads a simple texture from a file name and applies it to the mesh.
			* @param fileName Filename to load the mesh from.
			* @param clamp If true, clamps the texture to edges. See Texture for details on that.
			*/
			void loadTexture(const String& fileName);

			void loadTextureFromImage(Image *image);
			
			/**
			* Loads a skeleton from a file and applies it to the scene mesh.
			* @param fileName Filename to load the skeleton from.
			*/
			Skeleton *loadSkeleton(const String& fileName);
			
			/**
			* Sets the texture from an existing Texture instance.
			* @param texture Texture to set.
			*/			
			void setTexture(Texture *texture);

			/**
			* Clears the currently applied material
			*/
			void clearMaterial();

			/**
			* Set material from existing Material instance.
			* @param material Material to apply.
			*/												
			void setMaterial(Material *material);
			
			/**
			* Set material by name. You can create materials in material files and name them there, then use this to set a material by name to a scene mesh.
			* @param materialName Name of material to apply.
			*/									
			void setMaterialByName(const String& materialName, ResourcePool *resourcePool = NULL);
			
			/**
			* Set the mesh this scene mesh renders.
			* @param mesh Set a new mesh to render.
			*/															
			void setMesh(Mesh *mesh);
		
			/**
			* Sets a skeleton from an existing skeleton instance.
			* @param skeleton Skeleton to set to this mesh.
			*/
			void setSkeleton(Skeleton *skeleton);
			
			/**
			* Returns the skeleton applied to this scene mesh.
			*/
			Skeleton *getSkeleton();
		
			void renderMeshLocally();
			
			/**
			* If this is set to true, the mesh will be cached to a hardware vertex buffer if those are available. This can dramatically speed up rendering.
			*/
			void cacheToVertexBuffer(bool cache);
			
            /**
             * Sets the line width for line-based meshes.
             */
			void setLineWidth(Number newWidth);

            /**
             * If this mesh was loaded form file, returns the filename of the loaded mesh.
             */
            String getFilename();
        
            /**
             * Sets the filename path of the mesh.
             */
            void setFilename(String fileName);
        
            /**
             * Loads mesh from file. Deletes current mesh if ownsMesh is set to true.
             */
            void loadFromFile(String fileName);
        
            /**
             * Line width for line-based meshes.
             */
			Number lineWidth;
        
            /**
             * If set to true, will antialias the lines in a line-based mesh. Defaults to false.
             */
			bool lineSmooth;
			
            /**
             * Point size for point-based meshes.
             */
			Number pointSize;
        
            /**
             * If setto true, will antialias points in a point-based mesh. Defaults to false.
             */
			bool pointSmooth;
			
			/**
			* If true, will delete its Mesh upon destruction or mesh loading. (defaults to true)
			*/ 
			bool ownsMesh;

			/**
			* If true, will delete its Skeleton upon destruction. (defaults to true)
			*/ 			
			bool ownsSkeleton;
			
            /**
             * If set to true, will render the mesh wireframe on top of the mesh using wireFrameColor.
             * @see wireFrameColor
             */
			bool overlayWireframe;
        
            /*
             * If overlayWireframe is set to true, defines the color of the mesh wireframe.
             */
			Color wireFrameColor;	
			
            /**
             * If set to true, will check against actual geometry polygons on ray hit detection. Defaults to false.
             */
			bool useGeometryHitDetection;
			
			bool customHitDetection(const Ray &ray);
        
            /**
             * The Renderer has an ability to set an override material that is set for all rendered entities. If forceMaterial is set to true, this entity will always use its assigned material, even if an override material is set.
             */
            bool forceMaterial;
        
            virtual Entity *Clone(bool deepClone, bool ignoreEditorOnly) const;
            virtual void applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly) const;
        
            
            /**
             * Normally, translucent textures do not affect the depth buffer, but if this flag is set to true, this entity's alpha channel is written to the depth buffer at a preset threshold. This flag is set to false by default.
             */
            bool alphaTest;
            
            /**
             * If this flag is set to false, backface culling is disabled when rendering this entity, rendering both sides of each face. Set to true by default.
             */
            bool backfaceCulled;
        
            bool sendBoneMatricesToMaterial;
			
		protected:
		
			bool useVertexBuffer;
			Mesh *mesh;
			Texture *texture;
			Material *material;
			Skeleton *skeleton;
			ShaderBinding *localShaderOptions;
            String fileName;
        
            std::vector<Matrix4> materialBoneMatrices;
        
            VertexDataArray skeletalVertexPositions;
            VertexDataArray skeletalVertexNormals;
        
        
        
	};
}
