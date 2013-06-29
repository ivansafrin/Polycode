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
		PolycodeScreenEditorActionDataEntry(ScreenEntity *entity);
		Vector3 vec3;
		Number number;
		ScreenEntity *entity;
		ScreenEntity *parentEntity;
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

		void setRootEntity(ScreenEntity *entity);

		void Refresh();

		Entity *selectedEntity;
		Entity *targetLayer;

		UIImageButton *newLayerButton;
		UIImageButton *targetLayerButton;


	protected:

		Entity *rootEntity;

		bool dontSendSelectionEvent;

		UITreeContainer *treeContainer;

		ScreenShape *headerBg;
		ScreenShape *bg;

};

class PropertiesSizer : public UIElement {
	public:
		PropertiesSizer();
		~PropertiesSizer();

		void Resize(Number width, Number height);

		UIVSizer *sizer;
};


class ScreenEntityNameDisplay : public ScreenEntity {
	public:
		ScreenEntityNameDisplay(ScreenEntity *targetEntity);
		~ScreenEntityNameDisplay();

		void Update();

		ScreenLabel *label;
		ScreenLabel *tagsLabel;
		ScreenEntity *targetEntity;
};

class PolycodeScreenEditorMain : public UIElement {
	public:

		PolycodeScreenEditorMain(PolycodeEditor *editor);
		virtual ~PolycodeScreenEditorMain();

		void Resize(Number width, Number height);
		void syncTransformToSelected();
		ScreenEntity *addNewLayer(String layerName);
		void updateCursor();
		void selectEntity(ScreenEntity *entity, bool doAction = true);
		void resetSelectedEntityTransforms();
		void setMode(int newMode);
		void handleEvent(Event *event);
		void resizePreviewScreen();
		void handleDroppedFile(OSFileEntry file, Number x, Number y);
		bool hasSelected(ScreenEntity *entity);

		void deleteEntity(ScreenEntity *entity);

		void applyEditorOnly(ScreenEntity *entity);
		void applyEditorOnlyChildren(ScreenEntity *entity);
		void applyEditorProperties(ScreenEntity *entity);

		void processEventForEntity(ScreenEntity *childEntity, InputEvent *inputEvent);

		void createParticleRef(ScreenParticleEmitter *target);
		void createSoundRef(ScreenSound *target);
		void createEntityRef(ScreenEntity *entity);

		void doAction(String actionName, PolycodeEditorActionData *data);

		void setRefVisibility(bool val);
		void setEntityRefVisibility(ScreenEntity *entity, bool val);

		void getCenterAndSizeForSelected(Vector2 *center, Number *width, Number *height);

		void handleMouseDown(Vector2 position);
		void handleMouseMove(Vector2 position);
		void handleMouseUp(Vector2 position);

		void setGrid(int gridSize);

		void adjustForSnap(Vector2 *position);

		void setCurrentLayer(ScreenEntity *newLayer, bool doAction = true);
		ScreenEntity *getCurrentLayer();

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

		std::vector<ScreenEntity*> layers;

		PropList *entityProps;

		ScreenEntity *layerBaseEntity;

//		ScreenEntity *selectedEntity;
		std::vector<ScreenEntity*> selectedEntities;

		Transform2DSheet *transform2dSheet;
		EntitySheet *entitySheet;
		ShapeSheet *shapeSheet;
		ScreenImageSheet *imageSheet;
		ScreenLabelSheet *labelSheet;
		SoundSheet *soundSheet;
		EntityPropSheet *entityPropSheet;
		ScreenEntityInstanceSheet *instanceSheet;
		ScreenSpriteSheet *spriteSheet;
		ScreenParticleSheet *particleSheet;
		ScreenEntitySheet *screenEntitySheet;

		EntityTreeView *treeView;

		ScreenEntity *objectBaseEntity;
		ScreenEntity *placingPreviewEntity;
		bool multiSelect;

		PolycodeEditor *editor;
		ScreenEntity *baseEntity;
	protected:

		PolycodeScreenEditorActionData *beforeData;
		ScreenEntity *currentLayer;

		int gridSize;
		bool gridSnap;

		bool pixelSnap;

		ScreenShape *previewShape;
		ScreenImage *previewImage;
		ScreenEntityInstance *previewInstance;
		ScreenLabel *previewLabel;
		ScreenEntity *previewEntity;
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
		ScreenEntity *parentingChild;
		ScreenLine *parentingLine;


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

		ScreenShape *placingShape;
		Vector2 placingAnchor;

		ScreenShape *screenPreviewShape;
		ScreenShape *sizePreviewShape;

		Vector2 dragOffset;
		bool isDraggingEntity;
		bool isScalingEntity;



		ScreenEntity *screenTransform;
		ScreenShape *screenTransformShape;
		ScreenImage *transformRotator;

		ScreenImage *transformScalerY;
		ScreenImage *transformScalerX;
		ScreenImage *transformScalerXY;

		ScreenImage *centerImage;

		ScreenEntity *properties;
		ScreenShape *propertiesBg;

		ScreenEntity *viewOptions;
		ScreenShape *viewOptionsBg;

		UITextInput *gridSizeInput;
		UICheckBox *gridCheckBox;

		UICheckBox *pixelSnapBox;
		UICheckBox *gridSnapBox;

		UICheckBox *showRefsBox;

		UITextInput *scaleInput;

		ScreenEntity *toolPalette;
		ScreenShape *toolPaletteBg;

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

		ScreenImage *selectorImage;
		int mode;
};

class ScreenEntityClipboardData {
	public:
		ScreenEntityClipboardData(){}

		std::vector<ScreenEntity*> entities;
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
		void saveEntityToObjectEntry(ScreenEntity *entity, ObjectEntry *entry);
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
