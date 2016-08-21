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

#include "polycode/ide/PolycodeGlobals.h"
#include "polycode/modules/ui/PolycodeUI.h"
#include "Polycode.h"
#include "polycode/ide/PolycodeEditor.h"

using namespace Polycode;

#define PROP_PADDING	40

class PolycodeEditorPropActionData;

class PropProp : public UIElement {
	public:
		PropProp(Core *core, ResourcePool *pool, const String &caption, String type);
		~PropProp();

		virtual void setPropData(PolycodeEditorPropActionData* data) {}
		
		virtual void setPropWidth(Number width) {}
		virtual void updateFocusVisibility() {}
		void setPropName(String newName);
	
		ResourcePool *resourcePool;
		String propType;
		UILabel *label;
		UIElement *propContents;
		
		bool suppressChangeEvent;		
		bool settingFromData;
};

class Vector3Prop : public PropProp {
	public:
		Vector3Prop(Core *core, ResourcePool *pool, const String &caption, UIElement *focusParent);
		~Vector3Prop();
		void handleEvent(Event *event);
		void set(const Vector3 &position);

		Vector3 get() const;
		void setPropData(PolycodeEditorPropActionData* data);
		
		void setPropWidth(Number width);
		
		UITextInput *xInput;
		UITextInput *yInput;
		UITextInput *zInput;
		
		UILabel *labelX;
		UILabel *labelY;
		UILabel *labelZ;
	
		Vector3 lastData;
		Vector3 currentData;
	
};


class Vector2Prop : public PropProp {
	public:
		Vector2Prop(Core *core, ResourcePool *pool, const String &caption, UIElement *focusParent);
		~Vector2Prop();		
		void handleEvent(Event *event);
		void set(Vector2 position);
		Vector2 get();
		
		void setPropData(PolycodeEditorPropActionData* data);
		
		void setPropWidth(Number width);		
				
		UITextInput *positionX;
		UITextInput *positionY; 
		
		Vector2 lastData;
		Vector2 currentData;	
		
		UILabel *labelX;
		UILabel *labelY;		
};

class SliderProp : public PropProp {
	public:
		SliderProp(Core *core, ResourcePool *pool, const String &caption, Number min, Number max);
		~SliderProp();		
		void handleEvent(Event *event);
		void set(Number number);
		Number get();
		
		void setPropWidth(Number width);		
		void setPropData(PolycodeEditorPropActionData* data);		
				
		UIHSlider *slider;
		UILabel *valueLabel;
		
		Number lastValue;
		Number currentValue;
};

class ButtonProp : public PropProp {
	public:
		ButtonProp(Core *core, ResourcePool *pool, const String &caption, UIElement *focusParent);
		~ButtonProp();
		void setPropWidth(Number width);
		UIButton *getButton();
	
	private:
	
		UIButton *button;
};


class NumberProp : public PropProp {
	public:
		NumberProp(Core *core, ResourcePool *pool, const String &caption, UIElement *focusParent);
		~NumberProp();		
		void handleEvent(Event *event);
		void set(Number number);
		Number get();
	
		void setPropWidth(Number width);
		void updateFocusVisibility();
	
		void setPropData(PolycodeEditorPropActionData* data);
				
		UITextInput *numberEntry;
		
		Number lastValue;
		Number currentValue;
};

class TargetBindingProp : public PropProp {
	public:

		TargetBindingProp(Core *core, ResourcePool *pool, std::shared_ptr<Shader> shader, std::shared_ptr<Material> material, std::shared_ptr<ShaderBinding> binding, RenderTargetBinding *targetBinding);
		~TargetBindingProp();

		void handleEvent(Event *event); 
		void setPropWidth(Number width);
						
		RenderTargetBinding *targetBinding;
		std::shared_ptr<Material> material;
		std::shared_ptr<Shader> shader;
		std::shared_ptr<ShaderBinding> binding;
		
		UIComboBox *typeComboBox;
		UIComboBox *targetComboBox;
		UIComboBox *textureComboBox;		
		UIImageButton *removeButton;					
	
};

class RenderTargetProp : public PropProp {
	public:
		RenderTargetProp(Core *core, ResourcePool *pool, ShaderRenderTarget *renderTarget, std::shared_ptr<Material> material);
		~RenderTargetProp();

		void handleEvent(Event *event); 
		void setPropWidth(Number width);
		
		void recreateRenderTarget();
		
		std::shared_ptr<Material> material;
		ShaderRenderTarget *renderTarget;
		
		UITextInput *nameInput;		
		UIComboBox *typeComboBox;		
		UITextInput *widthInput;
		UITextInput *heightInput;		
		UIImageButton *removeButton;					
};

class ShaderPassProp : public PropProp {
	public:
		ShaderPassProp(Core *core, ResourcePool *pool, std::shared_ptr<Material> material, int shaderIndex);
		~ShaderPassProp();
		
		void handleEvent(Event *event); 
		void setPropWidth(Number width);
		
		std::shared_ptr<Material> material;
		std::shared_ptr<Shader> shader;		
		int shaderIndex;
		UIComboBox *shaderComboBox;		
		UIImageButton *removeButton;
		
		UIButton *editButton;
		
};

class RemovableStringProp : public PropProp {
public:
	RemovableStringProp(Core *core, ResourcePool *pool, const String &caption);
	~RemovableStringProp();
	void handleEvent(Event *event);
	
	String getCaption();
	
	UILabel *label;
	UIImageButton *removeButton;
};


class LayerProp : public PropProp {
	public:
		LayerProp(Core *core, ResourcePool *pool, SceneEntityInstance *instance, SceneEntityInstanceLayer *layer);
		~LayerProp();
		void handleEvent(Event *event);
		void setPropWidth(Number width);
	
		void setInstance(SceneEntityInstance *instance);
	
	private:
	
		SceneEntityInstance *instance;
		SceneEntityInstanceLayer *layer;
		UILabel *layerName;
		UIImageButton *hideLayerButton;
		UIImageButton *showLayerButton;
		UIImageButton *moreButton;
	
		UIMenu *menu;
	
		UIImageButton *removeLayerButton;
	
		unsigned char layerID;
	
		UIRect *bgRect;
};

class CustomProp : public PropProp {
	public:
		CustomProp(Core *core, ResourcePool *pool, String key, String value);
		~CustomProp();
		void handleEvent(Event *event);
		void set(String key, String val);
		void setPropWidth(Number width);	
		String getValue();
		String getKey();
				
		UITextInput *keyEntry;
		UITextInput *valueEntry;
		UIImageButton *removeButton;
};

class StringProp : public PropProp {
	public:
		StringProp(Core *core, ResourcePool *pool, const String &caption, UIElement *focusParent);
		~StringProp();		
		void handleEvent(Event *event);
		void set(String str);
		String get();

		void setPropWidth(Number width);

		void setPropData(PolycodeEditorPropActionData* data);
				
		UITextInput *stringEntry;
		
		String lastValue;
		String currentValue;
};

class ColorProp : public PropProp {
	public:
		ColorProp(Core *core, ResourcePool *pool, const String &caption);
		~ColorProp();		
		void handleEvent(Event *event);
		
		virtual void setPropData(PolycodeEditorPropActionData* data);
		
		void set(Color color);
		Color get();
		
		Color currentColor;
		Color lastColor;
				
		UIColorBox *colorEntry;
};

class ComboProp : public PropProp {
	public:
		ComboProp(Core *core, ResourcePool *pool, const String &caption);
		~ComboProp();		
		void handleEvent(Event *event);
		
		void setPropData(PolycodeEditorPropActionData* data);

		void setPropWidth(Number width);

		void set(unsigned int index);
		unsigned int get();
				
		UIComboBox *comboEntry;
		
		int lastValue;
		int currentValue;
};

class BoolProp : public PropProp {
	public:
		BoolProp(Core *core, ResourcePool *pool, const String &caption);
		~BoolProp();		
		void handleEvent(Event *event);
		
		void setPropData(PolycodeEditorPropActionData* data);
		
		void set(bool val);
		bool get();
				
		UICheckBox *checkEntry;
		
		bool lastData;
		bool currentData;
};

class SoundProp : public PropProp {
	public:
		SoundProp(Core *core, ResourcePool *pool, const String &caption);
		~SoundProp();
		void handleEvent(Event *event);			
		
		void set(String soundPath);
		String get();
		
		void setPropData(PolycodeEditorPropActionData* data);
		
		Sound *previewSound;
		UILabel *soundFile;		
		UIButton *changeButton;
		UIButton *playButton;	
		
		String lastData;
		String currentData;
};

class BezierRGBACurveProp : public PropProp {
	public:
		BezierRGBACurveProp(Core *core, ResourcePool *pool, const String &caption);
		~BezierRGBACurveProp();

		void handleEvent(Event *event); 
		
		BezierCurve *curveR;
		BezierCurve *curveG;
		BezierCurve *curveB;
		BezierCurve *curveA;					
		UIButton *changeButton;
};

class BezierCurveProp : public PropProp {
	public:
		BezierCurveProp(Core *core, ResourcePool *pool, const String &caption, String curveName);
		~BezierCurveProp();

		void handleEvent(Event *event); 
		
		String curveName;
		BezierCurve *curve;
		UIButton *changeButton;
};

class MaterialProp : public PropProp {
	public:
		MaterialProp(Core *core, ResourcePool *pool, const String &caption);
		~MaterialProp();
	
		void Render(GPUDrawBuffer *buffer);
	
		void setEntityInstance(SceneEntityInstance *instance);
		void set(std::shared_ptr<Material> material);
		std::shared_ptr<Material> get();
		void setPropWidth(Number width);
		void handleEvent(Event *event);
	
	private:
	
		Scene *previewScene;
		SceneLight *mainLight;
		SceneLight *secondLight;
		SceneRenderTexture *renderTexture;
		ScenePrimitive *previewPrimitive;
	
	
		SceneEntityInstance *entityInstance;
		UIRect *previewShape;
		UIButton *changeButton;
		UILabel *materialLabel;
	
		std::shared_ptr<Material> currentMaterial;
};

class TextureProp : public PropProp {
	public:
		TextureProp(Core *core, ResourcePool *pool, const String &caption);
		~TextureProp();
		void handleEvent(Event *event); 
		void setPropWidth(Number width);
				
		void set(std::shared_ptr<Texture> texture);
		std::shared_ptr<Texture> get();
		
		void setPropData(PolycodeEditorPropActionData* data);
				
		UIRect *previewShape;
		UIButton *changeButton;
		UILabel *textureLabel;
		
		String lastData;
		String currentData;
};

class SceneSpriteProp : public PropProp {
	public:
		SceneSpriteProp(Core *core, ResourcePool *pool, const String &caption);
		~SceneSpriteProp();
		void handleEvent(Event *event);
		
		void setPropData(PolycodeEditorPropActionData* data);
		
		void setEntityInstance(SceneEntityInstance *instance);
	
		void set(std::shared_ptr<Sprite> sprite);
		 std::shared_ptr<Sprite> get();
				
		SceneEntityInstance *entityInstance;
	
		std::shared_ptr<Sprite> sprite;
		SceneSprite *previewSprite;
		UIButton *changeButton;
		UILabel *spriteName;
	
		std::shared_ptr<Sprite>lastData;
		std::shared_ptr<Sprite>currentData;
};

class SceneEntityInstanceProp : public PropProp {
	public:
		SceneEntityInstanceProp(Core *core, ResourcePool *pool, const String &caption);
		~SceneEntityInstanceProp();
		void handleEvent(Event *event);			
		
		void setPropData(PolycodeEditorPropActionData* data);
		
		void set(String fileName);
		String get();		
				
		SceneEntityInstance *previewInstance;
		UIButton *changeButton;
		
		String lastData;
		String currentData;
		
};

class PropSheet : public UIElement {
	public:
		PropSheet(Core *core, ResourcePool *pool, const String &caption, String type);
		~PropSheet();		
		void Resize(Number width, Number height);
		
		virtual void applyPropActionData(PolycodeEditorPropActionData *data);
		void handleEvent(Event *event);
	
		void layoutProps();
		
		void setCollapsed(bool val);
		
		void addProp(PropProp *prop);
		void setTopPadding(Number padding);
				
		String caption;
		String type;
		
		Number propHeight;				
		UIElement *contents;
		
		UIRect *bg;
		
		UIImageButton *collapseButton;
		UIImageButton *expandButton;
		
		bool collapsed;
		Number propTopPadding;
		bool customUndoHandler;
		std::vector<PropProp*> props;
	
		ResourcePool *resourcePool;
};

class ShaderOptionsSheet : public PropSheet {
	public:
		ShaderOptionsSheet(Core *core, ResourcePool *pool);
		~ShaderOptionsSheet();
		
		void handleEvent(Event *event);
		void Update(Number elapsed);
		
		void clearShader();
		void setOptionsFromParams(std::vector<ProgramParam> &params);
		void setShader(std::shared_ptr<Shader> shader, std::shared_ptr<Material> material, std::shared_ptr<ShaderBinding> binding);
				
	private:
		std::shared_ptr<Shader> shader;
		std::shared_ptr<Material> material;
		std::shared_ptr<ShaderBinding> binding;
		
};

class EntitySheet : public PropSheet {
	public:
		EntitySheet(Core *core, ResourcePool *pool);
		~EntitySheet(); 
	
		void handleEvent(Event *event);
		void setEntity(Entity *entity);
	
		void refreshLayers();
	
		void setEntityInstance(SceneEntityInstance *instance);

	protected:
		Entity *entity;
		
		SceneEntityInstance *instance;
		ComboProp *layersProp;
		StringProp *idProp;
		StringProp *tagProp;
		ColorProp *colorProp;
		ComboProp *blendingProp;
		Vector3Prop *bBoxProp;
};

class ShaderPassesSheet : public PropSheet {
	public:
		ShaderPassesSheet(Core *core, ResourcePool *pool, ResourcePool *resourcePool);
		~ShaderPassesSheet();
		void handleEvent(Event *event);			
		void refreshPasses();
		
		void Update(Number elapsed);
		
		void setMaterial(std::shared_ptr<Material> material);

		std::shared_ptr<ShaderBinding> binding;
		std::shared_ptr<Material> material;

		ShaderPassProp *selectedProp;

		ResourcePool *localPool;
	
		ButtonProp *addButton;
		int removeIndex;		
};

class TargetBindingsSheet : public PropSheet {
	public:
		TargetBindingsSheet(Core *core, ResourcePool *pool);
		~TargetBindingsSheet();
		void handleEvent(Event *event);				
		void setShader(std::shared_ptr<Shader> shader, std::shared_ptr<Material> material, std::shared_ptr<ShaderBinding> binding);
		
		void Update(Number elapsed);
		
		void refreshTargets();
		
		std::shared_ptr<ShaderBinding> binding;
		std::shared_ptr<Material> material;
		std::shared_ptr<Shader> shader;
		int shaderIndex;
		
		ButtonProp *addButton;
		RenderTargetBinding *bindingToRemove;

};

class RenderTargetsSheet : public PropSheet {
	public:
		RenderTargetsSheet(Core *core, ResourcePool *pool);
		~RenderTargetsSheet();
		void Update(Number elapsed);
		void handleEvent(Event *event);		
		
		void refreshTargets();
		
		std::shared_ptr<ShaderBinding> binding;
		std::shared_ptr<Material> material;
		std::shared_ptr<Material> lastMaterial;
		
		Number normTextureWidth;
		Number normTextureHeight;
		
		ButtonProp *addButton;
		int removeIndex;
};

class TransformSheet : public PropSheet {
	public:
		TransformSheet(Core *core, ResourcePool *pool);
		~TransformSheet();
	
		void Update(Number elapsed);
	
		void setEntity(Entity *entity);
		void handleEvent(Event *event);
	
	protected:
		Entity *entity;
	
		Vector3Prop *positionProp;
		Vector3Prop *scaleProp;
		Vector3Prop *rotationProp;
	
		Vector3 lastPosition;
		Vector3 lastScale;
		Vector3 lastRotation;
};

class ParticleEmitterSheet : public PropSheet {
	public:
		ParticleEmitterSheet(Core *core, ResourcePool *pool);
		~ParticleEmitterSheet();
	
		void handleEvent(Event *event);
		void setParticleEmitter(SceneParticleEmitter *emitter);
	
	protected:
		SceneParticleEmitter *emitter;
	
		ComboProp *typeProp;
		NumberProp *countProp;
		NumberProp *lifetimeProp;
		NumberProp *particleSizeProp;
		NumberProp *particleSpeedProp;

		BoolProp *worldParticlesProp;
		BoolProp *loopingProp;

		Vector3Prop *particleRotaionProp;
	
		Vector3Prop *gravityProp;
		Vector3Prop *directionProp;
		Vector3Prop *sizeProp;
		Vector3Prop *deviationProp;
	
		BoolProp *perlinProp;
		Vector3Prop *perlinSizeProp;
	
		BoolProp *useColorCurvesProp;
		BezierRGBACurveProp *colorCurveProp;

		BoolProp *useScaleCurvesProp;
		BezierCurveProp *scaleCurveProp;

};

class SceneLightSheet : public PropSheet {
	public:
		SceneLightSheet(Core *core, ResourcePool *pool);
		~SceneLightSheet();
	
		void updateOptionVisibility();
	
		void setSceneLight(SceneLight *light);
		void handleEvent(Event *event);
	
	protected:
	
		SceneLight *light;
	
		ComboProp *typeProp;
		NumberProp *importanceProp;
		ColorProp *lightColorProp;
		ColorProp *specularColorProp;
		NumberProp *intensityProp;
		SliderProp *constantAttenuationProp;
		SliderProp *linearAttenuationProp;
		SliderProp *quadraticAttenuationProp;
	
		SliderProp *spotlightCutoffProp;
		SliderProp *spotlightExponentProp;
	
		BoolProp *castShadowsProp;
		SliderProp *shadowMapFOVProp;
		NumberProp *shadowResolutionProp;
};

class SceneMeshSheet : public PropSheet {
	public:
		SceneMeshSheet(Core *core, ResourcePool *pool);
		~SceneMeshSheet();
	
		void setSceneMesh(SceneMesh *mesh);
		void handleEvent(Event *event);
	
	private:
	
		BoolProp *gpuSkinningProp;
		BoolProp *backfaceCullProp;
		SceneMesh *sceneMesh;
};


class ScenePrimitiveSheet : public PropSheet {
public:
	ScenePrimitiveSheet(Core *core, ResourcePool *pool);
	~ScenePrimitiveSheet();
	
	void setScenePrimitive(ScenePrimitive *primitive);
	void handleEvent(Event *event);
	
protected:
	
	void updatePrimitiveLabels();
	
	ScenePrimitive *primitive;
	ComboProp *typeProp;
	
	NumberProp *option1Prop;
	NumberProp *option2Prop;
	NumberProp *option3Prop;
	NumberProp *option4Prop;
	NumberProp *option5Prop;
};

class MaterialPropSheet : public PropSheet {
	public:
		MaterialPropSheet(Core *core, ResourcePool *pool);
		~MaterialPropSheet();
	
		void setEntityInstance(SceneEntityInstance *instance);
		void handleEvent(Event *event);
		void setSceneMesh(SceneMesh *sceneMesh);
	
	protected:
	
	
		MaterialProp *materialProp;
		SceneMesh *sceneMesh;
};

class EntityPropSheet : public PropSheet {
	public:
		EntityPropSheet(Core *core, ResourcePool *pool);
		void handleEvent(Event *event);
		void Update(Number elapsed);
		void refreshProps();
		void applyPropActionData(PolycodeEditorPropActionData *data);
		void setEntity(Entity *entity);

		ButtonProp *addButtonProp;
		
		Entity *entity;
	
		int lastNumProps;		
		int removeIndex;
};

class SceneLabelSheet : public PropSheet {
	public:
		SceneLabelSheet(Core *core, ResourcePool *pool);
		~SceneLabelSheet();
		
		void refreshFonts();
		void handleEvent(Event *event);
	
		void setSceneLabel(SceneLabel *label);
		
	
	private:
		SceneLabel *label;
				
		StringProp *caption;
		NumberProp *size;
		NumberProp *actualHeight;
		ComboProp *font;
		BoolProp *enableAA;
};

class SceneCurveSheet : public PropSheet {
	public:
		SceneCurveSheet(Core *core, ResourcePool *pool);
		~SceneCurveSheet();
	
		void handleEvent(Event *event);
		void setCurve(SceneCurve *curve);
	
		SceneCurve *curve;
		ButtonProp *addPointProp;
		BoolProp *renderProp;
		NumberProp *numPointsProp;
	
};

class SceneSpriteSheet : public PropSheet {
	public:
		SceneSpriteSheet(Core *core, ResourcePool *pool);
		~SceneSpriteSheet();
		
		void handleEvent(Event *event);
		void setSprite(SceneSprite *sprite);
	
		void setEntityInstance(SceneEntityInstance *instance);
				
		SceneSprite *sprite;
	
		SceneSpriteProp *spriteProp;
		BoolProp *randomFrameProp;
		ComboProp *defaultStateProp;
};


class CameraSheet : public PropSheet {
	public:
		CameraSheet(Core *core, ResourcePool *pool);
		~CameraSheet();
	
		void handleEvent(Event *event);
		void setCamera(Camera *camera);
	
		void updateOptionVisibility();
	
		NumberProp *exposureProp;
	
		BoolProp *orthoProp;
		NumberProp *fovProp;
		ComboProp *orthoSizeTypeProp;
		NumberProp *orthoWidthProp;
		NumberProp *orthoHeightProp;
	
		NumberProp *nearClipPlane;
		NumberProp *farClipPlane;
	
		Camera *camera;
};


class SceneEntityInstanceSheet : public PropSheet {
	public:
		SceneEntityInstanceSheet(Core *core, ResourcePool *pool);
		~SceneEntityInstanceSheet();
		
		void handleEvent(Event *event);
		void Update(Number elapsed);
				
		SceneEntityInstance *instance;
		SceneEntityInstanceProp *instanceProp;
};

class SoundSheet : public PropSheet {
	public:
		SoundSheet(Core *core, ResourcePool *pool);
		~SoundSheet();
		
		void handleEvent(Event *event);
		void setSound(SceneSound *sound);
				
		SceneSound *sound;

		SoundProp *soundProp;		
		NumberProp *referenceDistance;
		BoolProp *loopOnLoad;
		NumberProp *maxDistance;
		SliderProp *volume;
		SliderProp *pitch;
};

class LayerSheet : public PropSheet {
	public:
		LayerSheet(Core *core, ResourcePool *pool);
		~LayerSheet();
		
		void handleEvent(Event *event);
		void setEntityInstance(SceneEntityInstance *instance);
	
		void setFromEntity();
	
		void Update(Number elapsed);

	private:
		ButtonProp *addLayerProp;
		SceneEntityInstance *instance;
		int layerRemoveIndex;
};

class LinkedMaterialsSheet : public PropSheet {
	public:
		LinkedMaterialsSheet(Core *core, ResourcePool *pool);
		~LinkedMaterialsSheet();
	
		void handleEvent(Event *event);
		void setEntityInstance(SceneEntityInstance *instance);
	
		void Update(Number elapsed);
	
		void updateMaterials();
	
	
	private:
		SceneEntityInstance *instance;
		ButtonProp *addMaterialProp;
	
		int poolRemoveIndex;
	
};

class PropList : public UIElement {
	public:
		PropList(Core *core, ResourcePool *pool, const String &caption="PROPERTIES");
		~PropList();
		
		void updateProps();
		void updateSize();
	
		void setCaption(const String &newCaption);
		void addPropSheet(PropSheet *sheet);
		void handleEvent(Event *event);
		void Resize(Number width, Number height);
		
		UIScrollContainer *scrollContainer;		
	protected:
	
		UIElement *propContents;
		UILabel *label;
		std::vector<PropSheet*> props;	
		UIRect *bg;
		UIRect *bg2;				
};

class PolycodeEditorPropActionData : public PolycodeEditorActionData {
	public:
		PolycodeEditorPropActionData(){ entity = NULL; }
		virtual ~PolycodeEditorPropActionData(){
			delete entity;
		}
		
		bool boolVal;
		String stringVal;
		int intVal;
		Number numVal;
		Color colorVal;
		Vector3 vector3Val;
		Vector2 vector2Val;
		
		Entity *entity;
		
		PropSheet *sheet;
		PropProp *prop;
};


PolycodeEditorPropActionData *PropDataBool(bool val);
PolycodeEditorPropActionData *PropDataInt(int val);
PolycodeEditorPropActionData *PropDataNumber(Number val);
PolycodeEditorPropActionData *PropDataString(String val);
PolycodeEditorPropActionData *PropDataColor(Color val);
PolycodeEditorPropActionData *PropDataVector3(Vector3 val);
PolycodeEditorPropActionData *PropDataVector2(Vector2 val);
PolycodeEditorPropActionData *PropDataEntity(Entity *entity);

class PropEvent : public Event {
	public:
		PropEvent(PropProp *prop, PropSheet *sheet, PolycodeEditorPropActionData *beforeData, PolycodeEditorPropActionData *afterData);
		virtual ~PropEvent();
		
		void setSheet(PropSheet *sheet);
		
		PropProp *prop;
		PropSheet *sheet;
		
		PolycodeEditorPropActionData *beforeData;
		PolycodeEditorPropActionData *afterData;
				
		static const int EVENTBASE_PROPEVENT = 0xC00;
		static const int EVENT_PROP_CHANGE = EVENTBASE_PROPEVENT+0;

};
