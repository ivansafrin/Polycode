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


class PolycodeEditorPropActionData;

class PropProp : public UIElement {
	public:
		PropProp(String caption, String type);
		~PropProp();

		virtual void setPropData(PolycodeEditorPropActionData* data) {}
		
		String propType;
		ScreenLabel *label;
		ScreenEntity *propContents;				
		
		bool suppressChangeEvent;		
		bool settingFromData;
};

class Vector2Prop : public PropProp {
	public:
		Vector2Prop(String caption);
		~Vector2Prop();		
		void handleEvent(Event *event);
		void set(Vector2 position);
		Vector2 get();
		
		void setPropData(PolycodeEditorPropActionData* data);
				
		UITextInput *positionX;
		UITextInput *positionY;	
		
		Vector2 lastData;
		Vector2 currentData;		
};

class SliderProp : public PropProp {
	public:
		SliderProp(String caption, Number min, Number max);
		~SliderProp();		
		void handleEvent(Event *event);
		void set(Number number);
		Number get();
		
		void setPropData(PolycodeEditorPropActionData* data);		
				
		UIHSlider *slider;
		ScreenLabel *valueLabel;
		
		Number lastValue;
		Number currentValue;
};


class NumberProp : public PropProp {
	public:
		NumberProp(String caption);
		~NumberProp();		
		void handleEvent(Event *event);
		void set(Number number);
		Number get();
		
		void setPropData(PolycodeEditorPropActionData* data);
				
		UITextInput *numberEntry;
		
		Number lastValue;
		Number currentValue;
};


class CustomProp : public PropProp {
	public:
		CustomProp(String key, String value);
		~CustomProp();
		void handleEvent(Event *event);
		void set(String key, String val);
		String getValue();
		String getKey();
				
		UITextInput *keyEntry;
		UITextInput *valueEntry;
		UIImageButton *removeButton;
};

class StringProp : public PropProp {
	public:
		StringProp(String caption);
		~StringProp();		
		void handleEvent(Event *event);
		void set(String str);
		String get();

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
		ScreenLabel *soundFile;		
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

class TextureProp : public PropProp {
	public:
		TextureProp(String caption);
		~TextureProp();
		void handleEvent(Event *event);	
		
		void set(Texture *texture);
		Texture* get();
		
		void setPropData(PolycodeEditorPropActionData* data);
				
		ScreenShape *previewShape;
		UIButton *changeButton;
		ScreenLabel *textureLabel;
		
		String lastData;
		String currentData;
};

class ScreenSpriteProp : public PropProp {
	public:
		ScreenSpriteProp(String caption);
		~ScreenSpriteProp();
		void handleEvent(Event *event);
		
		void setPropData(PolycodeEditorPropActionData* data);
		
		void set(String fileName);
		String get();		
				
		ScreenSprite *previewSprite;
		UIButton *changeButton;
		
		String lastData;
		String currentData;
};


class ScreenEntityInstanceProp : public PropProp {
	public:
		ScreenEntityInstanceProp(String caption);
		~ScreenEntityInstanceProp();
		void handleEvent(Event *event);			
		
		void setPropData(PolycodeEditorPropActionData* data);
		
		void set(String fileName);
		String get();		
				
		ScreenEntityInstance *previewInstance;
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
		
		void setCollapsed(bool val);
		
		void addProp(PropProp *prop);
		
		String caption;
		String type;
		
		Number propHeight;				
		ScreenEntity *contents;
		
		ScreenShape *bg;
		
		UIImageButton *collapseButton;
		UIImageButton *expandButton;
		
		bool collapsed;
		
		std::vector<PropProp*> props;
};

class ShaderOptionsSheet : public PropSheet {
	public:
		ShaderOptionsSheet(String title, String name, bool fragmentParams);
		~ShaderOptionsSheet();
		
		void handleEvent(Event *event);
		void Update();
		
		void clearShader();
		void setOptionsFromParams(std::vector<ProgramParam> &params);
		void setShader(Shader *shader, Material *material);
				
	private:
		bool fragmentParams;
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
		void setShader(Shader *shader, Material *material);
				
	private:
		Shader *shader;
		Material *material;
		ShaderBinding *binding;
						
		std::vector<TextureProp*> textureProps;
};

class EntitySheet : public PropSheet {
	public:
		EntitySheet();
		~EntitySheet();	
	
		void handleEvent(Event *event);
		void Update();
				
		Entity *entity;
		Entity *lastEntity;
		
		StringProp *idProp;
		StringProp *tagProp;
		ColorProp *colorProp;
		ComboProp *blendingProp;
};

class EntityPropSheet : public PropSheet {
	public:
		EntityPropSheet();		
		void handleEvent(Event *event);
		void Update();
		void refreshProps();

		void applyPropActionData(PolycodeEditorPropActionData *data);

		UIButton *addButton;
		
		Entity *entity;
		Entity *lastEntity;
		
		int lastNumProps;
		
		int removeIndex;		
		
};

class ShapeSheet : public PropSheet {
	public:
		ShapeSheet();
		~ShapeSheet();
		
		void handleEvent(Event *event);
		void Update();
				
		ScreenShape *shape;
	
		ComboProp *typeProp;
		Vector2Prop *shapeSize;
		BoolProp *strokeProp;
		ColorProp *strokeColorProp;
		NumberProp *strokeSize;
						
		bool lastStrokeVal;
		int lastShapeType;
		Vector2 lastShapeSize;
		Color lastStrokeColor;
		Number lastStrokeSize;
};

class ScreenLabelSheet : public PropSheet {
	public:
		ScreenLabelSheet();
		~ScreenLabelSheet();
		
		void refreshFonts();
		
		void handleEvent(Event *event);
		void Update();
				
		ScreenLabel *label;
		ScreenLabel *lastLabel;	
		
		int lastSize;
		String lastFont;
		
		StringProp *caption;
		NumberProp *size;
		ComboProp *font;
		BoolProp *enableAA;
};


class ScreenImageSheet : public PropSheet {
	public:
		ScreenImageSheet();
		~ScreenImageSheet();
		
		void handleEvent(Event *event);
		void Update();
				
		ScreenImage *image;
		
		TextureProp *texture;
		
};

class ScreenSpriteSheet : public PropSheet {
	public:
		ScreenSpriteSheet();
		~ScreenSpriteSheet();
		
		void handleEvent(Event *event);
		void Update();
				
		ScreenSprite *sprite;	
		ScreenSpriteProp *spriteProp;
		ComboProp *defaultAnimationProp;
		
		ScreenSprite *lastAnimationCheck;
		
};


class ScreenEntityInstanceSheet : public PropSheet {
	public:
		ScreenEntityInstanceSheet();
		~ScreenEntityInstanceSheet();
		
		void handleEvent(Event *event);
		void Update();
				
		ScreenEntityInstance *instance;
		ScreenEntityInstanceProp *instanceProp;
};

class ScreenEntitySheet : public PropSheet {
	public:
		ScreenEntitySheet();
		~ScreenEntitySheet();
		
		void handleEvent(Event *event);
		void Update();
		
		NumberProp *widthProp;
		NumberProp *heightProp;
		
		ScreenEntity *entity;
		ScreenEntity *lastEntity;
};

class SoundSheet : public PropSheet {
	public:
		SoundSheet();
		~SoundSheet();
		
		void handleEvent(Event *event);
		void Update();
				
		ScreenSound *sound;

		SoundProp *soundProp;		
		NumberProp *referenceDistance;
		NumberProp *maxDistance;		
		NumberProp *volume;
		NumberProp *pitch;
		
		String lastSoundPath;
		Number lastReferenceDistance;
		Number lastMaxDistance;
		Number lastVolume;
		Number lastPitch;
};

class ScreenParticleSheet : public PropSheet {
	public:
		ScreenParticleSheet();
		~ScreenParticleSheet();		
		
		void handleEvent(Event *event);
		
		void Update();

		TextureProp *textureProp;
		ComboProp *blendingProp;
		BoolProp *ignoreParentMatrixProp;
		NumberProp *numParticlesProp;
		NumberProp *lifespanProp;
		NumberProp *particleScaleProp;		
		Vector2Prop *sizeProp;
		Vector2Prop *dirProp;
		Vector2Prop *gravProp;		
		Vector2Prop *deviationProp;	
		SliderProp *brightnessDeviationProp;
		BoolProp *perlinEnableProp;
		NumberProp *perlinModSizeProp;
		SliderProp *speedModProp;
		NumberProp *rotationSpeedProp;
		BoolProp *rotationFollowsPathProp;		
		BoolProp *useScaleCurvesProp;		
		BezierCurveProp *scaleCurveProp;
		
		BoolProp *useColorCurvesProp;		
		BezierRGBACurveProp *colorCurveProp;
				
		Number lastParticleScale;		
		Number lastRotationSpeed;
		Number lastNumParticles;
		Number lastLifespan;
		Vector3 lastSize;
		Vector3 lastDeviation;
		Vector3 lastDir;
		Vector3 lastGrav;				
		Number lastBrightnessDeviation;
		bool lastEnableProp;
		Number lastPerlinSize;
		Number lastSpeedMod;
		bool lastIgnoreParentMatrix;
		bool lastRotationFollowsPath;
		bool lastUseScaleCurves;
		bool lastUseColorCurves;		
		BezierCurve *lastScaleCurve;
		
		ScreenParticleEmitter *emitter;
};

class Transform2DSheet : public PropSheet {
	public:
		Transform2DSheet();
		~Transform2DSheet();		
		
		void handleEvent(Event *event);
		
		void Update();
		
		Vector2Prop *positionProp;
		Vector2Prop *scaleProp;	
		NumberProp *rotationProp;
		BoolProp *topLeftProp;
				
		Vector2 lastPositon;
		Vector2 lastScale;
		Number lastRotation;
		int lastPositionMode;
		
		ScreenEntity *entity;
};

class PropList : public UIElement {
	public:
		PropList(String caption="PROPERTIES");
		~PropList();
		
		void updateProps();
		void updateSize();
		
		void addPropSheet(PropSheet *sheet);
		void handleEvent(Event *event);
		void Resize(Number width, Number height);
		
		UIScrollContainer *scrollContainer;		
	protected:
	
		ScreenEntity *propContents;
	
		std::vector<PropSheet*> props;	
		ScreenShape *bg;
		ScreenShape *bg2;				
};

class PolycodeEditorPropActionData : public PolycodeEditorActionData {
	public:
		PolycodeEditorPropActionData(){}
		virtual ~PolycodeEditorPropActionData(){}
		
		bool boolVal;
		String stringVal;
		int intVal;
		Number numVal;
		Color colorVal;
		Vector3 vector3Val;
		Vector2 vector2Val;
		
		Entity entity;
		
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
