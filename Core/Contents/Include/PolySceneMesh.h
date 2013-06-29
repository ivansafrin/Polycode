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
#include "PolySceneEntity.h"
#include "PolyShader.h"

namespace Polycode {

class Material;
class Mesh;
class Texture;
class Skeleton;

/**
* 3D polygonal mesh instance. The SceneMesh is the base for all polygonal 3d geometry. It can have simple textures or complex materials applied to it.
*/
class _PolyExport SceneMesh : public SceneEntity {
	public:

		/**
		* Construct a scene mesh from a mesh file.
		* @param fileName Path to mesh file to load.
		*/
		SceneMesh(const String& fileName);

		/**
		* Construct an empty scene mesh with the specified type.
		* @param meshType Mesh type to create. See Mesh for possible values.
		*/
		SceneMesh(int meshType);

		/**
		* Construct scene mesh from an existing Mesh instance.
		*/
		SceneMesh(Mesh *mesh);

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

		ShaderBinding *getLocalShaderOptions();

		/**
		* Returns the Mesh instance of the actual mesh.
		*/
		Mesh *getMesh();

		/**
		* Returns the texture applied.
		*/
		Texture *getTexture();

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

		/**
		* Loads a skeleton from a file and applies it to the scene mesh.
		* @param fileName Filename to load the skeleton from.
		*/
		void loadSkeleton(const String& fileName);

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
		void setMaterialByName(const String& materialName);

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

		unsigned int lightmapIndex;

		bool showVertexNormals;


		Number lineWidth;
		bool lineSmooth;

		/**
		* If true, will delete its Mesh upon destruction. (defaults to true)
		*/ 
		bool ownsMesh;

		/**
		* If true, will delete its Skeleton upon destruction. (defaults to true)
		*/
		bool ownsSkeleton;

	protected:

		bool useVertexBuffer;
		Mesh *mesh;
		Texture *texture;
		Material *material;
		Skeleton *skeleton;
		ShaderBinding *localShaderOptions;
};

}
