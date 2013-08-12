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
#include <Polycode.h>
#include <PolycodeUI.h>
#include "PolycodeProps.h"

#if defined(__APPLE__) && defined(__MACH__)
	#define COPYMOD_1 KEY_RALT
	#define COPYMOD_2 KEY_LALT
#elif defined _WINDOWS
	#define COPYMOD_1 KEY_RCTRL
	#define COPYMOD_2 KEY_LCTRL
#else
	#define COPYMOD_1 KEY_RCTRL
	#define COPYMOD_2 KEY_LCTRL
#endif

using namespace Polycode;

#ifdef _WINDOWS
#define round (int)
#endif

class EntityBrowserData  {
	public:
		Entity *entity;
};

class PolycodeScreenEditorActionDataEntry {
	public:
		PolycodeScreenEditorActionDataEntry(){
			entity = NULL;
			parentEntity = NULL;
		}
		PolycodeScreenEditorActionDataEntry(Vector3 vec3, Number number);	
		PolycodeScreenEditorActionDataEntry(Vector3 vec3);
		PolycodeScreenEditorActionDataEntry(Number number);
		PolycodeScreenEditorActionDataEntry(Entity *entity);
		Vector3 vec3;
		Number number;
		Entity *entity;
		Entity *parentEntity;		
};

class PolycodeScreenEditorActionData : public PolycodeEditorActionData {
	public:
		PolycodeScreenEditorActionData() {
			reverse = true;
		}
		virtual ~PolycodeScreenEditorActionData(){}
		
		std::vector<PolycodeScreenEditorActionDataEntry> entries;
		PolycodeScreenEditorActionDataEntry entry;
		bool reverse;
};

class EntityTreeView : public UIElement {
	public:
		EntityTreeView(Entity *rootEntity);
		~EntityTreeView();
		
		void Resize(Number width, Number height);
		void handleEvent(Event *event);	
		
		void syncNodeToEntity(UITree *node, Entity *entity);
		
		void setRootEntity(Entity *entity);
		
		void Refresh();

		Entity *selectedEntity;
		Entity *targetLayer;
		
		UIImageButton *newLayerButton;
		UIImageButton *targetLayerButton;
		
						
	protected:	
	
		Entity *rootEntity;
			
		bool dontSendSelectionEvent;
	
		UITreeContainer *treeContainer;
			
		ScenePrimitive *headerBg;		
		ScenePrimitive *bg;		
				
};

class PropertiesSizer : public UIElement {
	public:
		PropertiesSizer();
		~PropertiesSizer();
		
		void Resize(Number width, Number height);
		
		UIVSizer *sizer;
};


class EntityNameDisplay : public Entity {
	public:
		EntityNameDisplay(Entity *targetEntity);
		~EntityNameDisplay();
		
		void Update();
		
		SceneLabel *label;
		SceneLabel *tagsLabel;		
		Entity *targetEntity;
};

class PolycodeScreenEditorMain : public UIElement {
	public:
		
		PolycodeScreenEditorMain(PolycodeEditor *editor);
		virtual ~PolycodeScreenEditorMain();	
			
		void Resize(Number width, Number height);	
		void syncTransformToSelected();	
		Entity *addNewLayer(String layerName);	
		void updateCursor();		
		void selectEntity(Entity *entity, bool doAction = true);
		void resetSelectedEntityTransforms();
		void setMode(int newMode);	
		void handleEvent(Event *event);	
		void resizePreviewScreen();		
		void handleDroppedFile(OSFileEntry file, Number x, Number y);		
		bool hasSelected(Entity *entity);
		
		void deleteEntity(Entity *entity);
	
		void applyEditorOnly(Entity *entity);
		void applyEditorOnlyChildren(Entity *entity);
		void applyEditorProperties(Entity *entity);
			
		void processEventForEntity(Entity *childEntity, InputEvent *inputEvent);
	
		void createParticleRef(ScreenParticleEmitter *target);
		void createSoundRef(ScreenSound *target);
		void createEntityRef(Entity *entity);
		
		void doAction(String actionName, PolycodeEditorActionData *data);
		
		void setRefVisibility(bool val);
		void setEntityRefVisibility(Entity *entity, bool val);
		
		void getCenterAndSizeForSelected(Vector2 *center, Number *width, Number *height);
	
		void handleMouseDown(Vector2 position);
		void handleMouseMove(Vector2 position);
		void handleMouseUp(Vector2 position);
		
		void setGrid(int gridSize);
		
		void adjustForSnap(Vector2 *position);
		
		void setCurrentLayer(Entity *newLayer, bool doAction = true);
		Entity *getCurrentLayer();
		
		String Copy(void **data);
		void Paste(void *data, String clipboardType);
		void destroyClipboardData(void *data, String type);
		
		static const int MODE_SELECT = 0;
		static const int MODE_SHAPE = 1;
		static const int MODE_ZOOM = 2;
		static const int MODE_PAN = 3;
		static const int MODE_IMAGE = 4;
		static const int MODE_TEXT = 5;
		static const int MODE_PARENT = 6;
		static const int MODE_ENTITY = 7;
		static const int MODE_SOUND = 8;
		static const int MODE_LINK = 9;
		static const int MODE_SPRITE = 10;
		static const int MODE_PARTICLES = 11;
																
		std::vector<Entity*> layers;
		
		PropList *entityProps;
		
		Entity *layerBaseEntity;		
						
//		Entity *selectedEntity;
		std::vector<Entity*> selectedEntities;		
		
		Transform2DSheet *transform2dSheet;
		EntitySheet *entitySheet;
		ShapeSheet *shapeSheet;
		UIImageSheet *imageSheet;
		SceneLabelSheet *labelSheet;
		SoundSheet *soundSheet;
		EntityPropSheet *entityPropSheet;
		EntityInstanceSheet *instanceSheet;
		ScreenSpriteSheet *spriteSheet;
		ScreenParticleSheet *particleSheet;
		EntitySheet *EntitySheet;
		
		EntityTreeView *treeView;
		
		Entity *objectBaseEntity;		
		Entity *placingPreviewEntity;												
		bool multiSelect;
		
		PolycodeEditor *editor;	
		Entity *baseEntity;			
	protected:
	
		PolycodeScreenEditorActionData *beforeData;
		Entity *currentLayer;	
	
		int gridSize;
		bool gridSnap;
		
		bool pixelSnap;
	
		ScenePrimitive *previewShape;
		UIImage *previewImage;
		EntityInstance *previewInstance;		
		SceneLabel *previewLabel;							
		Entity *previewEntity;
		ScreenParticleEmitter *previewEmitter;
							
		ScreenSound *previewSound;
		ScreenSprite *previewSprite;
											
		ScreenMesh *grid;

		bool firstResize;
		
		bool firstMove;

		int placementCount;
	
		
		Number previewAspectRatio;

		bool placing;
		bool moving;
		bool scalingY;
		bool scalingX;		
		bool rotating;
		bool panning;
		bool zooming;
		bool zoomingMoved;
		
		bool parenting;
		Entity *parentingChild;
		SceneLine *parentingLine;
		
		
		int lastMode;
		
		Vector2 basePanPosition;
		Vector2 zoomBasePosition;
		Vector2 zoomBaseMousePosition;
		Vector2 baseScaleScreenPosition;
				
		Number baseZoomScale;
		
		Number baseRotateAngle;
		
		int selectedEntityPositionMode;
		
		Vector3 baseScale;
		
		Vector2 mouseBase;
		std::vector<Vector2> baseEntityPositions;
		std::vector<Vector2> baseEntityScales;
		std::vector<Number> baseRotateAngles;
		Vector2 groupCenterPoint;
		Number groupRoll;
		Number baseAngle;
	
		ScenePrimitive *placingShape;	
		Vector2 placingAnchor;
		
		ScenePrimitive *screenPreviewShape;
		ScenePrimitive *sizePreviewShape;
				
		Vector2 dragOffset;
		bool isDraggingEntity;
		bool isScalingEntity;
		

		
		Entity *screenTransform;
		ScenePrimitive *screenTransformShape;
		UIImage *transformRotator;

		UIImage *transformScalerY;
		UIImage *transformScalerX;		
		UIImage *transformScalerXY;
							
		UIImage *centerImage;
		
		Entity *properties;
		ScenePrimitive *propertiesBg;

		Entity *viewOptions;
		ScenePrimitive *viewOptionsBg;
		
		UITextInput *gridSizeInput;
		UICheckBox *gridCheckBox;
		
		UICheckBox *pixelSnapBox;
		UICheckBox *gridSnapBox;
		
		UICheckBox *showRefsBox;
		
		UITextInput *scaleInput;
		
		Entity *toolPalette;
		ScenePrimitive *toolPaletteBg;
		
		UIImageButton *arrowToolButton;
		UIImageButton *shapeToolButton;
		UIImageButton *zoomToolButton;
		UIImageButton *panToolButton;
		UIImageButton *imageToolButton;
		UIImageButton *textToolButton;
		UIImageButton *parentToolButton;
		UIImageButton *entityToolButton;
		UIImageButton *soundToolButton;
		UIImageButton *spriteToolButton;
		UIImageButton *particlesToolButton;
				
		UIImageButton *linkToolButton;
						
		UIComboBox *aspectComboBox;
		UIComboBox *zoomComboBox;
		
		UIButton *moveUpButton;
		UIButton *moveDownButton;
		UIButton *moveTopButton;
		UIButton *moveBottomButton;
		UIButton *unparentButton;
								
		Number zooms[16];
						
		Number aspects[16];
				
		UIImage *selectorImage;
		int mode;	
};

class EntityClipboardData {
	public:
		EntityClipboardData(){}
		
		std::vector<Entity*> entities;
};

class PolycodeScreenEditor : public PolycodeEditor {
	public:
		PolycodeScreenEditor();
		virtual ~PolycodeScreenEditor();
	
		bool openFile(OSFileEntry filePath);
		void Resize(int x, int y);
		
		String Copy(void **data);
		void Paste(void *data, String clipboardType);
		void destroyClipboardData(void *data, String type);

		void Activate();		
		
		void saveCurveToObject(ObjectEntry *entry, BezierCurve *curve);
		void saveEntityToObjectEntry(Entity *entity, ObjectEntry *entry);
		void saveFile();
		
		void doAction(String actionName, PolycodeEditorActionData *data);
					
		void handleDroppedFile(OSFileEntry file, Number x, Number y);

		void handleEvent(Event *event);

	protected:

		UIHSizer *mainSizer;
		PropertiesSizer *propSizer;
		EntityTreeView *treeView;
		PolycodeScreenEditorMain *editorMain;
};

class PolycodeScreenEditorFactory : public PolycodeEditorFactory {
	public:
		PolycodeScreenEditorFactory() : PolycodeEditorFactory() { extensions.push_back("entity2d"); }
		PolycodeEditor *createEditor() { return new PolycodeScreenEditor(); }
};
