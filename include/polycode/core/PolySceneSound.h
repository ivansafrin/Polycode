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

namespace Polycode {

	class Sound;

	/**
	* Creates a positional 3D sound listener. There can be only one listener active at any one time.
 	*/	
	class _PolyExport SceneSoundListener : public Entity {
		public:
			SceneSoundListener();
			virtual ~SceneSoundListener();			
			void Update();
	};


	/**
	* Creates a positional 3D sound.
	*/	
	class _PolyExport SceneSound : public Entity {
		public:
			SceneSound(const String& fileName, Number referenceDistance, Number maxDistance, bool directionalSound = false);
			virtual ~SceneSound();			
			void Update();
        
            virtual Entity *Clone(bool deepClone, bool ignoreEditorOnly) const;
            virtual void applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly) const;
			
            bool isDirectionalSound() const;
            void setDirectionalSound(bool val);
        
			/**
			* Returns the sound object associated with this positional sound.
			*/
			Sound *getSound();
        
            void setLoopOnLoad(bool val);
            bool getLoopOnLoad();
			
		protected:
		
            bool loopOnLoad;
			bool directionalSound;
			Sound *sound;
	};
	
}
