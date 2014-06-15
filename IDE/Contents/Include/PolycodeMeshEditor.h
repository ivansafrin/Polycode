/*
 Copyright (C) 2012 by Ivan Safrin
 
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

#include "PolycodeEditor.h"
#include "PolyUIElement.h"
#include "TrackballCamera.h"
#include "PolycodeUI.h"
#include <Polycode.h>

using namespace Polycode;

class PolycodeMeshEditor : public PolycodeEditor {
	public:
	
		PolycodeMeshEditor();
		virtual ~PolycodeMeshEditor();
	
		void handleEvent(Event *event);
	
		void reloadMaterials();
    
        void Activate();
        void Deactivate();
	
		bool openFile(OSFileEntry filePath);
		void Resize(int x, int y);
	
	protected:
	
		Scene *previewScene;
		
		SceneLight *mainLight;
		SceneLight *secondLight;		
		SceneRenderTexture *renderTexture;
		UIRect *previewShape;
		SceneMesh *previewMesh;
		Entity *previewBase;
		
		Material *currentMaterial;
				
		UIComboBox *materialDropDown;
		UIRect *headerBg;
		
		TrackballCamera *trackballCamera;

};

class PolycodeMeshEditorFactory : public PolycodeEditorFactory {
	public:
		PolycodeMeshEditorFactory() : PolycodeEditorFactory() { extensions.push_back("mesh"); }
		PolycodeEditor *createEditor() { return new PolycodeMeshEditor(); }
};
