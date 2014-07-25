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

#include <vector>

namespace Polycode {
	
	class Scene;
	class SceneRenderTexture;
	class Renderer;
	
	/**
     * This class manages all rendered scenes in Polycode.
     */
	class _PolyExport SceneManager : public PolyBase {
		public:
		SceneManager();
		~SceneManager();
		
        /**
         * Adds a scene to the render loop. Scenes automatically add themselves to the manager on creation, so there's no need to call this manually unless you remove a scene yourself.
         */
		void addScene(Scene *newScene);

        /**
         * Removes scene from the render loop (does not delete the scene).
         */
		void removeScene(Scene *scene);
        
        // Polycode internal
		void Update();
		void fixedUpdate();
		void Render();
		void renderVirtual();
		void registerRenderTexture(SceneRenderTexture *renderTexture);
		void unregisterRenderTexture(SceneRenderTexture *renderTexture);
		void setRenderer(Renderer *renderer);
				
		private:
		
		void updateRenderTextures(Scene *scene);
		
		std::vector <Scene*> scenes;
		std::vector <SceneRenderTexture*> renderTextures;
		
		Renderer *renderer;
	};

}
