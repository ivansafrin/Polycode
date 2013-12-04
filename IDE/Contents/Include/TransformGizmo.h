/*
 Copyright (C) 2013 by Ivan Safrin
 
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

#include "Polycode.h"
#include "OSBasics.h"
#include "PolycodeUI.h"

using namespace Polycode;

class TransformGizmo : public Entity {
	public:
		TransformGizmo(Scene *targetScene, Camera *targetCamera);
		~TransformGizmo();
		
		void handleEvent(Event *event);
		void setTransformMode(int newMode);
        void setGizmoMode(int newMode);
    
		void Update();
		
		void setTransformSelection(std::vector<Entity*> selectedEntities);
		
		void transfromSelectedEntities(const Vector3 &move, const Vector3 &scale, Number rotate);
		Vector3 getTransformPlanePosition();
		
		Number getTransformPlaneAngle();
		
		static const int TRANSFORM_MOVE = 0;		
		static const int TRANSFORM_SCALE = 1;
		static const int TRANSFORM_ROTATE = 2;
    
        static const int GIZMO_MODE_3D = 0;
		static const int GIZMO_MODE_2D = 1;
    
	private:
        int transformMode;
        int gizmoMode;
    
	
		std::vector<Entity*> selectedEntities;
	
		Scene *targetScene;
		Camera *targetCamera;
    
	
		CoreInput *coreInput;
		int mode;
		bool transforming;
		
		Vector3 transformConstraint;
		Vector3 transformPlane;
				
		Vector3 startingPoint;
		Number startingAngle;
					
		Entity *trasnformDecorators;
		Entity *scaleDecorators;
		Entity *transformAndScaleLines;			
		Entity *rotateDectorators;	
							
		Entity *xTransformGrip;
		Entity *yTransformGrip;
		Entity *zTransformGrip;	
		
		ScenePrimitive *pitchGrip;
		ScenePrimitive *rollGrip;
		ScenePrimitive *yawGrip;

        ScenePrimitive *viewportRotateGrip;
        Entity *viewportRotateGripBase;
    
        SceneMesh *xLine;
        SceneMesh *yLine;
        SceneMesh *zLine;
    
        ScenePrimitive *xArrow;
        ScenePrimitive *yArrow;
        ScenePrimitive *zArrow;
    
        ScenePrimitive *xBox;
        ScenePrimitive *yBox;
        ScenePrimitive *zBox;
    
        ScenePrimitive *outerCircle;
        ScenePrimitive *bgCircle;
    
        ScenePrimitive *pitchCircle;
        ScenePrimitive *yawCircle;
        ScenePrimitive *rollCircle;
};

class TransformGizmoMenu : public UIElement {
	public:
		TransformGizmoMenu(TransformGizmo *gizmo);
		~TransformGizmoMenu();
		
		void handleEvent(Event *event);
		
	private:
	
		UIImageButton *moveModeButton;
		UIImageButton *scaleModeButton;
		UIImageButton *rotateModeButton;
		
		TransformGizmo *gizmo;
};

