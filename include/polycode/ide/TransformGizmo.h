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


class TransformGrips : public UIElement {
public:
    TransformGrips();
    ~TransformGrips();
    
    void setGripRectangle(Polycode::Rectangle rectangle, Vector2 offset);
    
    void handleEvent(Event *event);
    Polycode::Rectangle getGripRectangle();
    
    Vector2 getAnchorPoint();
    
private:
    
    bool transforming;
    UIImage *movingTransform;
    
    Polycode::Rectangle gripRectangle;
    Vector2 anchorPoint;
    
    Vector2 mouseBase;
    
    UIRect *mainRect;
    UIImage *transformTL;
    UIImage *transformT;
    UIImage *transformTR;
    UIImage *transformR;
    UIImage *transformL;
    UIImage *transformBL;
    UIImage *transformB;
    UIImage *transformBR;
    UIImage *transformOffset;
    std::vector<UIElement*> grips;
    
};

class TrasnformGizmoEvent : public Event {
    public:
        TrasnformGizmoEvent(int mode);
    
        static const int EVENT_TRANSLATE = 0;
        static const int EVENT_SCALE = 1;
        static const int EVENT_ROTATE = 2;
    
        int mode;
};

class TransformGizmo : public Entity {
	public:
		TransformGizmo(Scene *targetScene, Camera *targetCamera);
		~TransformGizmo();
		
		void handleEvent(Event *event);
		void setTransformMode(int newMode);
        void setGizmoMode(int newMode);
    
		void Update();
    
        void enableSnap(bool val);
        void setSnapSize(Number snapSize);
    
		void setTransformSelection(std::vector<Entity*> selectedEntities);
		
		void transformSelectedEntities(const Vector3 &move, const Vector3 &scale, Number rotate);
		Vector3 getTransformPlanePosition();
		Vector3 getPositionAlongAxis();
		bool isConstrainedToSingleAxis();

		Number getTransformPlaneAngle();
		Number get2dAngle();
		Vector2 getCorrectedMousePosition();

		void resetTransform();
    
        void setTransformOrientation(int orientation);
    
        void updateOrientationForEntity(Entity *entity);
    
        void setTransformPlane(Number x, Number y, Number z, bool forceGlobal = false);
		void setTransformPlane(bool useX, bool useY, bool useZ);
        void setTransformPlaneFromView();
    
        void setCenterMode(int centerMode);

		void toggleOrientation();
		
		static const int TRANSFORM_MOVE = 0;
		static const int TRANSFORM_SCALE = 1;
		static const int TRANSFORM_ROTATE = 2;
		static const int TRANSFORM_SCALE_VIEW = 3;
		static const int TRANSFORM_ROTATE_VIEW = 4;
		static const int TRANSFORM_MOVE_VIEW = 5;
    
        static const int GIZMO_MODE_3D = 0;
		static const int GIZMO_MODE_2D_X = 1;
		static const int GIZMO_MODE_2D_Y = 2;
		static const int GIZMO_MODE_2D_Z = 3;
    
        static const int ORIENTATION_GLOBAL = 0;
        static const int ORIENTATION_LOCAL = 1;

        static const int CENTER_MODE_MEDIAN = 0;
        static const int CENTER_MODE_INDIVIDUAL = 1;
    
        bool enableGizmo;
    
	private:
    
        bool snapEnabled;
        Number snapSize;
    
        void dispatchEndEvent();
    
        int transformMode;
        int gizmoMode;
        int orientation;
		int startingOrientation;
    
        int centerMode;
	
		std::vector<Entity*> selectedEntities;
		std::vector<Vector3> entityPositions;

		std::vector<Vector3> oldPosition;
		std::vector<Vector3> oldScale;
		std::vector<Quaternion> oldRotation;
    
		Scene *targetScene;
		Camera *targetCamera;
    
        bool firstMove;
    
	
		CoreInput *coreInput;
		int mode;
        int previousMode;
		bool transforming;
		
		Vector3 transformConstraint;
		Vector3 transformPlane;
        Vector3 localTransformPlane;
    
        Number transformPlaneDistance;
    
        Matrix4 planeMatrix;
				
        Vector3 gizmoPoint;
		Vector3 startingPoint;
		Number startingAngle;

		Vector2 mouseStart2d;
    
        Number scaleAmount;
				
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
	
        UIIconSelector *transformSelector;
        UIComboBox *orientationCombo;
        UIIconSelector *centerSelector;
    
		TransformGizmo *gizmo;
};

