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

#include "PolycodeGlobals.h"
#include "PolycodeUI.h"
#include "Polycode.h"
#include "OSBasics.h"
#include "PolycodeEditor.h"

using namespace Polycode;

#define PROP_PADDING	40

class PolycodeEditorPropActionData;

class PropProp : public UIElement {
	public:
		PropProp(String caption, String type);
		~PropProp();

		virtual void setPropData(PolycodeEditorPropActionData* data) {}
		
		virtual void setPropWidth(Number width) {}
        virtual void updateFocusVisibility() {}
        void setPropName(String newName);
    
		String propType;
		UILabel *label;
		UIElement *propContents;
		
		bool suppressChangeEvent;		
		bool settingFromData;
};

class Vector3Prop : public PropProp {
    public:
        Vector3Prop(String caption, UIElement *focusParent);
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
		Vector2Prop(String caption, UIElement *focusParent);
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
		SliderProp(String caption, Number min, Number max);
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
        ButtonProp(const String &caption, UIElement *focusParent);
        ~ButtonProp();
        void setPropWidth(Number width);
        UIButton *getButton();
    
    private:
    
        UIButton *button;
};


class NumberProp : public PropProp {
	public:
		NumberProp(String caption, UIElement *focusParent);
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

		TargetBindingProp(Shader *shader, Material *material, ShaderBinding *binding, RenderTargetBinding *targetBinding);
		~TargetBindingProp();

		void handleEvent(Event *event);	
		void setPropWidth(Number width);
						
		RenderTargetBinding *targetBinding;
		Material *material;
		Shader *shader;
		ShaderBinding *binding;
		
		UIComboBox *typeComboBox;
		UIComboBox *targetComboBox;
		UIComboBox *textureComboBox;		
		UIImageButton *removeButton;					
	
};

class RenderTargetProp : public PropProp {
	public:
		RenderTargetProp(ShaderRenderTarget *renderTarget, Material *material);
		~RenderTargetProp();

		void handleEvent(Event *event);	
		void setPropWidth(Number width);
		
		void recreateRenderTarget();
		
		Material *material;
		ShaderRenderTarget *renderTarget;
		
		UITextInput *nameInput;		
		UIComboBox *typeComboBox;		
		UITextInput *widthInput;
		UITextInput *heightInput;		
		UIImageButton *removeButton;					
};

class ShaderPassProp : public PropProp {
	public:
		ShaderPassProp(Material *material, int shaderIndex);
		~ShaderPassProp();
		
		void handleEvent(Event *event);	
		void setPropWidth(Number width);
		
		Material *material;
		Shader *shader;		
		int shaderIndex;
		UIComboBox *shaderComboBox;		
		UIImageButton *removeButton;
		
		UIButton *editButton;
		
};

class RemovableStringProp : public PropProp {
public:
    RemovableStringProp(const String &caption);
    ~RemovableStringProp();
    void handleEvent(Event *event);
    
    String getCaption();
    
    UILabel *label;
    UIImageButton *removeButton;
};


class LayerProp : public PropProp {
    public:
        LayerProp(SceneEntityInstance *instance, SceneEntityInstanceLayer *layer);
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
		CustomProp(String key, String value);
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
		StringProp(String caption, UIElement *focusParent);
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
		ColorProp(String caption);
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
		ComboProp(String caption);
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
		BoolProp(String caption);
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
		SoundProp(String caption);
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
		BezierRGBACurveProp(String caption);
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
		BezierCurveProp(String caption, String curveName);
		~BezierCurveProp();

		void handleEvent(Event *event);	
		
		String curveName;
		BezierCurve *curve;
		UIButton *changeButton;
};

class MaterialProp : public PropProp {
    public:
        MaterialProp(const String &caption);
        ~MaterialProp();
    
        void setEntityInstance(SceneEntityInstance *instance);
        void set(Material *material);
        Material *get();
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
    
        Material *currentMaterial;
};

class TextureProp : public PropProp {
	public:
		TextureProp(String caption);
		~TextureProp();
		void handleEvent(Event *event);	
		void setPropWidth(Number width);
				
		void set(Texture *texture);
		Texture* get();
		
		void setPropData(PolycodeEditorPropActionData* data);
				
		UIRect *previewShape;
		UIButton *changeButton;
		UILabel *textureLabel;
		
		String lastData;
		String currentData;
};

class SceneSpriteProp : public PropProp {
	public:
		SceneSpriteProp(String caption);
		~SceneSpriteProp();
		void handleEvent(Event *event);
		
		void setPropData(PolycodeEditorPropActionData* data);
		
        void setEntityInstance(SceneEntityInstance *instance);
    
		void set(Sprite *sprite);
		Sprite *get();
				
        SceneEntityInstance *entityInstance;
    
        Sprite *sprite;
		SceneSprite *previewSprite;
		UIButton *changeButton;
        UILabel *spriteName;
    
        Sprite *lastData;
		Sprite *currentData;
};

class SceneEntityInstanceProp : public PropProp {
	public:
		SceneEntityInstanceProp(String caption);
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
		PropSheet(String caption, String type);
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
};

class ShaderOptionsSheet : public PropSheet {
	public:
		ShaderOptionsSheet();
		~ShaderOptionsSheet();
		
		void handleEvent(Event *event);
		void Update();
		
		void clearShader();
		void setOptionsFromParams(std::vector<ProgramParam> &params);
		void setShader(Shader *shader, Material *material, ShaderBinding *binding);
				
	private:
		Shader *shader;
		Material *material;
		ShaderBinding *binding;
		
};

class ShaderTexturesSheet : public PropSheet {
	public:
		ShaderTexturesSheet();
		~ShaderTexturesSheet();
		
		void handleEvent(Event *event);
		void Update();
		
		void clearShader();
		void setShader(Shader *shader, Material *material, ShaderBinding *binding);
				
	private:
		Shader *shader;
		Material *material;
		ShaderBinding *binding;
						
		std::vector<TextureProp*> textureProps;
		std::vector<ComboProp*> cubemapProps;		
};

class EntitySheet : public PropSheet {
	public:
		EntitySheet();
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
		ShaderPassesSheet(ResourcePool *resourcePool);
		~ShaderPassesSheet();
		void handleEvent(Event *event);			
		void refreshPasses();
		
		void Update();
		
		void setMaterial(Material *material);

		ShaderBinding *binding;
		Material *material;

		ShaderPassProp *selectedProp;

        ResourcePool *resourcePool;
    
		ButtonProp *addButton;
		int removeIndex;		
};

class TargetBindingsSheet : public PropSheet {
	public:
		TargetBindingsSheet();
		~TargetBindingsSheet();
		void handleEvent(Event *event);				
		void setShader(Shader *shader, Material *material, ShaderBinding *binding);
		
		void Update();
		
		void refreshTargets();
		
		ShaderBinding *binding;
		Material *material;
		Shader *shader;
		int shaderIndex;
		
		ButtonProp *addButton;
		RenderTargetBinding *bindingToRemove;

};

class RenderTargetsSheet : public PropSheet {
	public:
		RenderTargetsSheet();
		~RenderTargetsSheet();
		void Update();
		void handleEvent(Event *event);		
		
		void refreshTargets();
		
		ShaderBinding *binding;
		Material *material;
		Material *lastMaterial;
		
		Number normTextureWidth;
		Number normTextureHeight;
		
		ButtonProp *addButton;
		int removeIndex;
};

class TransformSheet : public PropSheet {
    public:
        TransformSheet();
        ~TransformSheet();
    
        void Update();
    
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
        ParticleEmitterSheet();
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
        SceneLightSheet();
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
        SceneMeshSheet();
        ~SceneMeshSheet();
    
        void setSceneMesh(SceneMesh *mesh);
        void handleEvent(Event *event);
    
    private:
    
        BoolProp *gpuSkinningProp;
        BoolProp *backfaceCullProp;
        BoolProp *alphaTestProp;
    
        SceneMesh *sceneMesh;
};


class ScenePrimitiveSheet : public PropSheet {
public:
    ScenePrimitiveSheet();
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
        MaterialPropSheet();
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
		EntityPropSheet();		
		void handleEvent(Event *event);
		void Update();
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
		SceneLabelSheet();
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
        SceneCurveSheet();
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
		SceneSpriteSheet();
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
        CameraSheet();
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
		SceneEntityInstanceSheet();
		~SceneEntityInstanceSheet();
		
		void handleEvent(Event *event);
		void Update();
				
		SceneEntityInstance *instance;
		SceneEntityInstanceProp *instanceProp;
};

class SoundSheet : public PropSheet {
	public:
		SoundSheet();
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
        LayerSheet();
        ~LayerSheet();
        
        void handleEvent(Event *event);
        void setEntityInstance(SceneEntityInstance *instance);
    
        void setFromEntity();
    
        void Update();

    private:
        ButtonProp *addLayerProp;
        SceneEntityInstance *instance;
        int layerRemoveIndex;
};

class LinkedMaterialsSheet : public PropSheet {
    public:
        LinkedMaterialsSheet();
        ~LinkedMaterialsSheet();
    
        void handleEvent(Event *event);
        void setEntityInstance(SceneEntityInstance *instance);
    
        void Update();
    
        void updateMaterials();
    
    
    private:
        SceneEntityInstance *instance;
        ButtonProp *addMaterialProp;
    
        int poolRemoveIndex;
    
};

class PropList : public UIElement {
	public:
		PropList(String caption="PROPERTIES");
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
