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
 
#include "PolycodeProps.h"
#include "PolycodeFrame.h"

extern UIColorPicker *globalColorPicker;
extern PolycodeFrame *globalFrame;
extern UIGlobalMenu *globalMenu;

PolycodeEditorPropActionData *PropDataBool(bool val) {
	PolycodeEditorPropActionData *data = new PolycodeEditorPropActionData();
	data->boolVal = val;
	return data;
}

PolycodeEditorPropActionData *PropDataInt(int val) {
	PolycodeEditorPropActionData *data = new PolycodeEditorPropActionData();
	data->intVal = val;
	return data;
}

PolycodeEditorPropActionData *PropDataNumber(Number val) {
	PolycodeEditorPropActionData *data = new PolycodeEditorPropActionData();
	data->numVal = val;
	return data;
}

PolycodeEditorPropActionData *PropDataString(String val) {
	PolycodeEditorPropActionData *data = new PolycodeEditorPropActionData();
	data->stringVal = val;
	return data;
}

PolycodeEditorPropActionData *PropDataColor(Color val) {
	PolycodeEditorPropActionData *data = new PolycodeEditorPropActionData();
	data->colorVal = val;
	return data;
}

PolycodeEditorPropActionData *PropDataVector3(Vector3 val) {
	PolycodeEditorPropActionData *data = new PolycodeEditorPropActionData();
	data->vector3Val = val;
	return data;
}

PolycodeEditorPropActionData *PropDataVector2(Vector2 val) {
	PolycodeEditorPropActionData *data = new PolycodeEditorPropActionData();
	data->vector2Val = val;
	return data;
}

PolycodeEditorPropActionData *PropDataEntity(Entity *entity) {
	PolycodeEditorPropActionData *data = new PolycodeEditorPropActionData();
	data->entity = *entity;
	data->entity.ownsChildren = false;
	for(int i=0; i < data->entity.getNumChildren(); i++) {
		data->entity.removeChild(data->entity.getChildAtIndex(i));
	}
	return data;
}

PropEvent::PropEvent(PropProp *prop, PropSheet *sheet, PolycodeEditorPropActionData *beforeData, PolycodeEditorPropActionData *afterData) : Event() {
	this->prop = prop;
	this->sheet = sheet;
	this->beforeData = beforeData;
	this->afterData = afterData;	
	this->eventType = "PropEvent";
	
	if(this->beforeData) {
		this->beforeData->sheet = sheet;
		this->beforeData->prop = prop;
	}

	if(this->afterData) {
		this->afterData->sheet = sheet;
		this->afterData->prop = prop;
	}
		
}

void PropEvent::setSheet(PropSheet *sheet) {
	if(this->beforeData) {
		this->beforeData->sheet = sheet;
	}

	if(this->afterData) {
		this->afterData->sheet = sheet;
	}
}

PropEvent::~PropEvent() {

}

PropList::PropList(String caption) : UIElement() {

	setPositionMode(ScreenEntity::POSITION_TOPLEFT);

	bg = new ScreenShape(ScreenShape::SHAPE_RECT, 10,10);
	bg->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	bg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiBgColor"));
	
	addChild(bg);
	bg->blockMouseInput = true;
	bg->processInputEvents = true;
	
	blockMouseInput = true;

	bg2 = new ScreenShape(ScreenShape::SHAPE_RECT, 10,10);
	bg2->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	bg2->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));
	
	addChild(bg2);

	ScreenLabel *label = new ScreenLabel(caption, 18, "section", Label::ANTIALIAS_FULL);
	label->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderFontColor"));
	addChild(label);
	label->setPosition(10, 3);

	propContents = new ScreenEntity();
	propContents->processInputEvents = true;
		
	scrollContainer = new UIScrollContainer(propContents, false, true, 100, 100);
	scrollContainer->setPosition(0, 30);
	addChild(scrollContainer);
}

PropList::~PropList() {

}
		
void PropList::updateProps() {
	for(int i=0; i < props.size(); i++) {
		props[i]->Update();
	}
	updateSize();
}

void PropList::updateSize() {
	Resize(width, height);
	scrollContainer->setScrollValue(0, 0);	
}
		
void PropList::Resize(Number width, Number height) {
	setWidth(width);
	setHeight(height);
	
	scrollContainer->Resize(width, height-30);
	
	bg->setShapeSize(width, height);
	bg2->setShapeSize(width, 30);	
	
	Number offsetY = 0;
	for(int i=0; i < props.size(); i++) {
		props[i]->setPosition(0, offsetY);
		if(props[i]->enabled) {
		if(props[i]->collapsed) {
			offsetY += 30;
		} else {
			offsetY += props[i]->propHeight;
		}
		}
		props[i]->Resize(width, height);
	}
	
	rebuildTransformMatrix();
	
	scrollContainer->setContentSize(width, offsetY);
}

void PropList::handleEvent(Event *event) {
	if(event->getEventType() == "" && event->getEventCode() == Event::COMPLETE_EVENT) {
		Resize(width, height);
	} else if(event->getEventCode() == Event::CHANGE_EVENT) {
	
	}
}

void PropList::addPropSheet(PropSheet *sheet) {
	propContents->addChild(sheet);
	props.push_back(sheet);
	Resize(width, height);
	sheet->addEventListener(this, Event::COMPLETE_EVENT);
	sheet->addEventListener(this, Event::CHANGE_EVENT);	
}

PropSheet::PropSheet(String caption, String type) : UIElement() {
	this->caption = caption;
	this->type = type;
	
	bg = new ScreenShape(ScreenShape::SHAPE_RECT, 30,30);
	addChild(bg);
	bg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiSmallHeaderBgColor"));
	bg->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	
	ScreenLabel *label = new ScreenLabel(caption, 18, "section", Label::ANTIALIAS_FULL);
	label->color.a = 0.5;
	addChild(label);
	label->setPosition(25, 3);	
	
	contents = new ScreenEntity();
	contents->processInputEvents = true;
	addChild(contents);
	contents->setPosition(20,35);
	
	collapseButton = new UIImageButton("Images/collapse.png");
	addChild(collapseButton);
	collapseButton->addEventListener(this, UIEvent::CLICK_EVENT);
	collapseButton->setPosition(5, 9);

	expandButton = new UIImageButton("Images/expand.png");
	addChild(expandButton);
	expandButton->addEventListener(this, UIEvent::CLICK_EVENT);	
	expandButton->setPosition(5, 9);
	expandButton->enabled = false;
		
	collapsed  = false;
	
	propHeight = 30;
}

void PropSheet::setCollapsed(bool val) {
	if(collapsed != val) {
		collapsed = val;
		if(collapsed) {
			collapseButton->enabled = false;
			expandButton->enabled = true;	
			contents->enabled = false;		
		} else {
			collapseButton->enabled = true;
			expandButton->enabled = false;				
			contents->enabled = true;			
		}
	}
	dispatchEvent(new Event(), Event::COMPLETE_EVENT);	
}

void PropSheet::handleEvent(Event *event) {	
	if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {
		if(event->getDispatcher() == collapseButton) {

			setCollapsed(true);
		}

		if(event->getDispatcher() == expandButton) {
			setCollapsed(false);
		}
	}
	
	if(event->getEventCode() == PropEvent::EVENT_PROP_CHANGE ) {
		PropEvent *propEvent = (PropEvent*) event;
		PropEvent *newEvent = new PropEvent(propEvent->prop, this, propEvent->beforeData, propEvent->afterData);		
		dispatchEvent(newEvent, PropEvent::EVENT_PROP_CHANGE);
	}	
}

PropSheet::~PropSheet() {

}

void PropSheet::Resize(Number width, Number height) {
	setWidth(width);
	setHeight(height);
	
	bg->setShapeSize(width, 30);
	
	Number yOffset = 0;
	
	for(int i=0; i < props.size(); i++) {
		props[i]->setPosition(0, yOffset);
		yOffset += props[i]->getHeight();
	}
}

void PropSheet::addProp(PropProp *prop) {
	contents->addChild(prop);
	props.push_back(prop);
	prop->addEventListener(this, Event::CHANGE_EVENT);
	prop->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);	
	Resize(width, height);
}


void PropSheet::applyPropActionData(PolycodeEditorPropActionData *data) {
	data->prop->setPropData(data);
}


PropProp::PropProp(String caption, String type) : UIElement() {

	suppressChangeEvent = false;
	propType = type;
	label = new ScreenLabel(caption, 12);
	label->color.a = 0.4;
	label->setPosition(0, 5);
	addChild(label);
	
	propContents = new ScreenEntity();
	propContents->processInputEvents = true;
	addChild(propContents);
	propContents->setPosition(100, 0);
	
	setHeight(20);
}

PropProp::~PropProp() {

}

Vector2Prop::Vector2Prop(String caption) : PropProp(caption, "Vector2") {

	ScreenLabel *label = new ScreenLabel("X:", 11);
	label->color.a = 0.4;
	propContents->addChild(label);
	label->setPosition(-20, 6);	

	label = new ScreenLabel("Y:", 11);
	label->color.a = 0.4;
	propContents->addChild(label);
	label->setPosition(60, 6);	
	
	positionX = NULL;
	positionY = NULL;

	positionX = new UITextInput(false, 50, 12);
	positionX->addEventListener(this, UIEvent::CHANGE_EVENT);
	positionX->setText("0");
	positionX->setNumberOnly(true);
	propContents->addChild(positionX);
	positionX->setPosition(0, 0);

	positionY = new UITextInput(false, 50, 12);
	positionY->setText("0");
	positionY->addEventListener(this, UIEvent::CHANGE_EVENT);	
	positionY->setNumberOnly(true);
	propContents->addChild(positionY);
	positionY->setPosition(80, 0);

	setHeight(30);

}

void Vector2Prop::handleEvent(Event *event) {
	if(event->getDispatcher() == positionX || event->getDispatcher() == positionY) {
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CHANGE_EVENT) {
		
			if(positionX && positionY) {
				lastData = currentData;
				currentData = Vector2(atof(positionX->getText().c_str()), atof(positionY->getText().c_str()));
			}
			if(!suppressChangeEvent) {
				dispatchEvent(new Event(), Event::CHANGE_EVENT);
				dispatchEvent(new PropEvent(this, NULL, PropDataVector2(lastData), PropDataVector2(currentData)), PropEvent::EVENT_PROP_CHANGE);

			}
		}
	}
}

void Vector2Prop::setPropData(PolycodeEditorPropActionData* data) {
	set(data->vector2Val);
	dispatchEvent(new Event(), Event::CHANGE_EVENT);
}

void Vector2Prop::set(Vector2 position) {
	suppressChangeEvent = true;
	positionX->setText(String::NumberToString(position.x));
	positionY->setText(String::NumberToString(position.y));
	suppressChangeEvent = false;	
}

Vector2 Vector2Prop::get() {
	return Vector2(atof(positionX->getText().c_str()), atof(positionY->getText().c_str()));
}

Vector2Prop::~Vector2Prop() {

}

CustomProp::CustomProp(String key, String value) : PropProp("", "Custom") {
	keyEntry = new UITextInput(false, 120, 12);
	keyEntry->setText(key);
	keyEntry->addEventListener(this, UIEvent::CHANGE_EVENT);
	propContents->addChild(keyEntry);
	keyEntry->setPosition(-90, 0);

	valueEntry = new UITextInput(false, 120, 12);
	valueEntry->setText(value);	
	valueEntry->addEventListener(this, UIEvent::CHANGE_EVENT);
	propContents->addChild(valueEntry);
	valueEntry->setPosition(45, 0);
	
	removeButton = new UIImageButton("Images/remove_icon.png");
	removeButton->addEventListener(this, UIEvent::CLICK_EVENT);	
	propContents->addChild(removeButton);
	removeButton->setPosition(-110, 6);
	
	setHeight(30);

}

CustomProp::~CustomProp() {
	keyEntry->removeAllHandlersForListener(this);
	valueEntry->removeAllHandlersForListener(this);
	removeButton->removeAllHandlersForListener(this);
	delete removeButton;
	delete keyEntry;
	delete valueEntry;
}

void CustomProp::handleEvent(Event *event) {

	if(event->getEventType() == "UIEvent") {
	
		if(event->getDispatcher() == keyEntry || event->getDispatcher() == valueEntry) {
			dispatchEvent(new Event(), Event::CHANGE_EVENT);		
		}	
	
		if(event->getDispatcher() == removeButton) {
			dispatchEvent(new Event(), Event::CANCEL_EVENT);
		}
	}
}

void CustomProp::set(String key, String val) {
}

String CustomProp::getValue() {
	return valueEntry->getText();
}

String CustomProp::getKey() {
	return keyEntry->getText();
}


StringProp::StringProp(String caption) : PropProp(caption, "String") {

	stringEntry = new UITextInput(false, 150, 12);
	stringEntry->addEventListener(this, UIEvent::CHANGE_EVENT);
	stringEntry->setText("");
	propContents->addChild(stringEntry);
	stringEntry->setPosition(0, 0);
	setHeight(30);

}

void StringProp::handleEvent(Event *event) {
	if(event->getDispatcher() == stringEntry) {
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CHANGE_EVENT) {		
			lastValue = currentValue;
			currentValue = stringEntry->getText();
			if(!suppressChangeEvent) {
				dispatchEvent(new Event(), Event::CHANGE_EVENT);
				dispatchEvent(new PropEvent(this, NULL, PropDataString(lastValue), PropDataString(currentValue)), PropEvent::EVENT_PROP_CHANGE);
			}
		}
	}
}

void StringProp::setPropData(PolycodeEditorPropActionData* data) {
	set(data->stringVal);
	dispatchEvent(new Event(), Event::CHANGE_EVENT);	
}

void StringProp::set(String str) {
	suppressChangeEvent = true;
	stringEntry->setText(str, false);
	suppressChangeEvent = false;	
}

String StringProp::get() {
	return currentValue;
}
	
		
StringProp::~StringProp() {

}

SliderProp::SliderProp(String caption, Number min, Number max) : PropProp(caption, "Slider") {
	
	slider = new UIHSlider(min, max, 100);
	slider->addEventListener(this, UIEvent::CHANGE_EVENT);
	slider->setPosition(5, 8);
	propContents->addChild(slider);
	
	valueLabel = new ScreenLabel("0.0", 10);
	propContents->addChild(valueLabel);
	valueLabel->setPosition(120, 5);
	valueLabel->color.a = 0.5;
	
	setHeight(30);

}

void SliderProp::handleEvent(Event *event) {
	if(event->getDispatcher() == slider) {
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CHANGE_EVENT) {		
			lastValue = currentValue;
			currentValue = slider->getSliderValue();		
			if(!suppressChangeEvent) {
				dispatchEvent(new Event(), Event::CHANGE_EVENT);
				dispatchEvent(new PropEvent(this, NULL, PropDataNumber(lastValue), PropDataNumber(currentValue)), PropEvent::EVENT_PROP_CHANGE);
			}
			valueLabel->setText(String::NumberToString(slider->getSliderValue()));
		}
	}
}

void SliderProp::setPropData(PolycodeEditorPropActionData* data) {
	set(data->numVal);
	lastValue = currentValue;
	currentValue = slider->getSliderValue();			
	dispatchEvent(new Event(), Event::CHANGE_EVENT);	
}

void SliderProp::set(Number number) {
	suppressChangeEvent = true;
	slider->setSliderValue(number);
	lastValue = currentValue;
	currentValue = slider->getSliderValue();	
	valueLabel->setText(String::NumberToString(slider->getSliderValue()));	
	suppressChangeEvent = false;	
}

Number SliderProp::get() {
	return currentValue;
}
	
		
SliderProp::~SliderProp() {

}

NumberProp::NumberProp(String caption) : PropProp(caption, "Number") {

	numberEntry = new UITextInput(false, 50, 12);
	numberEntry->addEventListener(this, UIEvent::CHANGE_EVENT);
	numberEntry->setText("0");
	numberEntry->setNumberOnly(true);
	propContents->addChild(numberEntry);
	numberEntry->setPosition(0, 2);

	setHeight(30);

}

void NumberProp::setPropData(PolycodeEditorPropActionData* data) {
	set(data->numVal);
	dispatchEvent(new Event(), Event::CHANGE_EVENT);	
}

void NumberProp::handleEvent(Event *event) {
	if(event->getDispatcher() == numberEntry) {
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CHANGE_EVENT) {		
			lastValue = currentValue;
			currentValue = atof(numberEntry->getText().c_str());
			if(!suppressChangeEvent) {
				dispatchEvent(new Event(), Event::CHANGE_EVENT);
				dispatchEvent(new PropEvent(this, NULL, PropDataNumber(lastValue), PropDataNumber(currentValue)), PropEvent::EVENT_PROP_CHANGE);
				
			}
		}
	}
}

void NumberProp::set(Number number) {
	suppressChangeEvent = true;
	numberEntry->setText(String::NumberToString(number), false);
	suppressChangeEvent = false;	
}

Number NumberProp::get() {
	return currentValue;
}
	
		
NumberProp::~NumberProp() {

}

ColorProp::ColorProp(String caption) : PropProp(caption, "Color") {

	colorEntry = new UIColorBox(globalColorPicker, Color(), 45, 25);
	colorEntry->addEventListener(this, UIEvent::CHANGE_EVENT);
	colorEntry->setPosition(0, -2);
	propContents->addChild(colorEntry);
	setHeight(30);

}

void ColorProp::handleEvent(Event *event) {
	if(event->getDispatcher() == colorEntry) {
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CHANGE_EVENT) {
			lastColor = currentColor;
			currentColor = colorEntry->getSelectedColor();
			if(!suppressChangeEvent) {
				dispatchEvent(new Event(), Event::CHANGE_EVENT);
				dispatchEvent(new PropEvent(this, NULL, PropDataColor(lastColor), PropDataColor(currentColor)), PropEvent::EVENT_PROP_CHANGE);
			}
		}
	}
}


void ColorProp::setPropData(PolycodeEditorPropActionData* data) {
	set(data->colorVal);
	dispatchEvent(new Event(), Event::CHANGE_EVENT);
}


void ColorProp::set(Color color) {
	suppressChangeEvent = true;
	colorEntry->setBoxColor(color);
	lastColor = currentColor;
	currentColor = colorEntry->getSelectedColor();	
	suppressChangeEvent = false;	
}

Color ColorProp::get() {
	return currentColor;
}
	
		
ColorProp::~ColorProp() {

}

ComboProp::ComboProp(String caption) : PropProp(caption, "Combo") {
	comboEntry = new UIComboBox(globalMenu, 150);
	comboEntry->addEventListener(this, UIEvent::CHANGE_EVENT);
	propContents->addChild(comboEntry);
	comboEntry->setPosition(-3, 0);
	setHeight(30);

}

void ComboProp::setPropData(PolycodeEditorPropActionData* data) {
	set(data->intVal);
	dispatchEvent(new Event(), Event::CHANGE_EVENT);	
}

void ComboProp::handleEvent(Event *event) {
	if(event->getDispatcher() == comboEntry) {
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CHANGE_EVENT) {		
			lastValue = currentValue;
			currentValue = comboEntry->getSelectedIndex();
			if(!suppressChangeEvent) {
				dispatchEvent(new Event(), Event::CHANGE_EVENT);
				dispatchEvent(new PropEvent(this, NULL, PropDataInt(lastValue), PropDataInt(currentValue)), PropEvent::EVENT_PROP_CHANGE);
			}
		}
	}
}

void ComboProp::set(unsigned int index) {
	suppressChangeEvent = true;
	comboEntry->setSelectedIndex(index);
	suppressChangeEvent = false;	
}

unsigned int ComboProp::get() {
	return currentValue;
}
	
		
ComboProp::~ComboProp() {

}

BoolProp::BoolProp(String caption) : PropProp(caption, "Bool") {

	checkEntry = new UICheckBox("", false);
	checkEntry->addEventListener(this, UIEvent::CHANGE_EVENT);
	checkEntry->setPosition(0, 2);
	propContents->addChild(checkEntry);
	setHeight(30);

}

void BoolProp::setPropData(PolycodeEditorPropActionData* data) {
	set(data->boolVal);
	dispatchEvent(new Event(), Event::CHANGE_EVENT);	
}

void BoolProp::handleEvent(Event *event) {
	if(event->getDispatcher() == checkEntry) {
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CHANGE_EVENT) {		
			lastData = currentData;
			currentData = checkEntry->isChecked();
			dispatchEvent(new Event(), Event::CHANGE_EVENT);
			dispatchEvent(new PropEvent(this, NULL, PropDataBool(lastData), PropDataBool(currentData)), PropEvent::EVENT_PROP_CHANGE);
		}
	}
}

void BoolProp::set(bool val) {
	checkEntry->setChecked(val);
	lastData = currentData;
	currentData = checkEntry->isChecked();	
}

bool BoolProp::get() {
	return currentData;
}
	
		
BoolProp::~BoolProp() {

}


SoundProp::SoundProp(String caption) : PropProp(caption, "Sound"){

	soundFile = new ScreenLabel("", 11);
	soundFile->setPosition(0, 5);
	propContents->addChild(soundFile);	
	soundFile->color.a = 0.6;

	playButton = new UIButton("Play", 50);
	propContents->addChild(playButton);
	playButton->setPosition(0, 25);
	playButton->addEventListener(this, UIEvent::CLICK_EVENT);


	changeButton = new UIButton("Change", 80);
	propContents->addChild(changeButton);
	changeButton->setPosition(60, 25);
	changeButton->addEventListener(this, UIEvent::CLICK_EVENT);
	setHeight(70);
	
	previewSound = NULL;
	
}

SoundProp::~SoundProp() {

}


void SoundProp::handleEvent(Event *event) {

	if(event->getDispatcher() == globalFrame->assetBrowser && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::OK_EVENT) {
		String newSoundPath = globalFrame->assetBrowser->getSelectedAssetPath();
		
		set(newSoundPath);
		
		globalFrame->assetBrowser->removeAllHandlersForListener(this);
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
		dispatchEvent(new PropEvent(this, NULL, PropDataString(lastData), PropDataString(currentData)), PropEvent::EVENT_PROP_CHANGE);
		globalFrame->hideModal();
		
	}

	if(event->getDispatcher() == playButton && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {
		if(previewSound) {
			previewSound->Play();
		}
	}

	if(event->getDispatcher() == changeButton && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {
		globalFrame->assetBrowser->addEventListener(this, UIEvent::OK_EVENT);
		
		std::vector<String> extensions;
		extensions.push_back("wav");
		extensions.push_back("ogg");		
		globalFrame->showAssetBrowser(extensions);
	}

}

void SoundProp::setPropData(PolycodeEditorPropActionData* data) {
	set(data->stringVal);
	dispatchEvent(new Event(), Event::CHANGE_EVENT);	
}

void SoundProp::set(String soundPath) {
	if(previewSound) {
		delete previewSound;
	}	
	
	lastData = currentData;
	currentData = soundPath;
	
	previewSound = new Sound(soundPath);	
	soundFile->setText(soundPath);
}

String SoundProp::get() {
	if(previewSound) {
		return previewSound->getFileName();
	}
	return "";
}

BezierRGBACurveProp::BezierRGBACurveProp(String caption) : PropProp(caption, "BezierRGBA") {


	changeButton = new UIButton("Edit", 120);
	propContents->addChild(changeButton);
	changeButton->setPosition(0, 0);
	changeButton->addEventListener(this, UIEvent::CLICK_EVENT);

	setHeight(30);
	
	curveR = NULL;
	curveG = NULL;
	curveB = NULL;
	curveA = NULL;			
}

BezierRGBACurveProp::~BezierRGBACurveProp() {

}

void BezierRGBACurveProp::handleEvent(Event *event) {
	if(event->getDispatcher() == changeButton && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {
		globalFrame->curveEditor->clearCurves();
		if(curveR && curveG && curveB && curveA) {
			globalFrame->curveEditor->addCurve("Red", curveR, Color(1.0, 0.0, 0.0, 1.0));
			globalFrame->curveEditor->addCurve("Green", curveG, Color(0.0, 1.0, 0.0, 1.0));
			globalFrame->curveEditor->addCurve("Blue", curveB, Color(0.0, 0.0, 1.0, 1.0));
			globalFrame->curveEditor->addCurve("Alpha", curveA, Color(1.0, 1.0, 1.0, 1.0));		
			globalFrame->showCurveEditor();
		}
	}
}

BezierCurveProp::BezierCurveProp(String caption, String curveName) : PropProp(caption, "BezierCurve") {

	this->curveName = curveName;

	changeButton = new UIButton("Edit", 120);
	propContents->addChild(changeButton);
	changeButton->setPosition(0, 0);
	changeButton->addEventListener(this, UIEvent::CLICK_EVENT);

	setHeight(30);
	
	curve = NULL;
}

BezierCurveProp::~BezierCurveProp() {

}

void BezierCurveProp::handleEvent(Event *event) {
	if(event->getDispatcher() == changeButton && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {
		globalFrame->curveEditor->clearCurves();
		if(curve) {
			globalFrame->curveEditor->addCurve(curveName, curve, Color());
			globalFrame->showCurveEditor();
		}
	}
}

TextureProp::TextureProp(String caption) : PropProp(caption, "Texture"){
	previewShape = new ScreenShape(ScreenShape::SHAPE_RECT, 48, 48);
	previewShape->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	previewShape->setPosition(2, 1);
	propContents->addChild(previewShape);

	changeButton = new UIButton("Change", 80);
	propContents->addChild(changeButton);
	changeButton->setPosition(60, 5);
	changeButton->addEventListener(this, UIEvent::CLICK_EVENT);
	
	textureLabel = new ScreenLabel("", 12, "sans");
	propContents->addChild(textureLabel);
	textureLabel->setPosition(60, 32);
	textureLabel->color.a = 0.4;
		
	setHeight(60);	
}

TextureProp::~TextureProp() {

}

void TextureProp::setPropData(PolycodeEditorPropActionData* data) {
	set(CoreServices::getInstance()->getMaterialManager()->createTextureFromFile(data->stringVal));
	dispatchEvent(new Event(), Event::CHANGE_EVENT);
}

void TextureProp::handleEvent(Event *event) {

	if(event->getDispatcher() == globalFrame->assetBrowser && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::OK_EVENT) {
		String texturePath = globalFrame->assetBrowser->getSelectedAssetPath();				
		set(CoreServices::getInstance()->getMaterialManager()->createTextureFromFile(texturePath));		
		globalFrame->assetBrowser->removeAllHandlersForListener(this);
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
		dispatchEvent(new PropEvent(this, NULL, PropDataString(lastData), PropDataString(currentData)), PropEvent::EVENT_PROP_CHANGE);
		globalFrame->hideModal();
		
	}

	if(event->getDispatcher() == changeButton && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {
		globalFrame->assetBrowser->addEventListener(this, UIEvent::OK_EVENT);
		
		std::vector<String> extensions;
		extensions.push_back("png");
		globalFrame->showAssetBrowser(extensions);
	}
}

void TextureProp::set(Texture *texture) {
	previewShape->setTexture(texture);
	
	lastData = currentData;
	currentData = texture->getResourcePath();
	
	OSFileEntry entry = OSFileEntry(texture->getResourcePath(), OSFileEntry::TYPE_FILE);		
	textureLabel->setText(entry.name);		
	
}

Texture* TextureProp::get() {
	return previewShape->getTexture();
}

ScreenSpriteProp::ScreenSpriteProp(String caption) : PropProp(caption, "ScreenSprite"){

		previewSprite = new ScreenSprite("default/default.sprite");
		previewSprite->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
		previewSprite->setPosition(2, 1);
		previewSprite->setShapeSize(48,48);		
		propContents->addChild(previewSprite);	

	
	changeButton = new UIButton("Change", 80);
	propContents->addChild(changeButton);
	changeButton->setPosition(60, 5);
	changeButton->addEventListener(this, UIEvent::CLICK_EVENT);
	setHeight(70);
}

ScreenSpriteProp::~ScreenSpriteProp() {

}

void ScreenSpriteProp::handleEvent(Event *event) {

	if(event->getDispatcher() == globalFrame->assetBrowser && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::OK_EVENT) {
		String filePath = globalFrame->assetBrowser->getSelectedAssetPath();
		
		set(filePath);
		
		globalFrame->assetBrowser->removeAllHandlersForListener(this);
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
		dispatchEvent(new PropEvent(this, NULL, PropDataString(lastData), PropDataString(currentData)), PropEvent::EVENT_PROP_CHANGE);
		globalFrame->hideModal();
	}

	if(event->getDispatcher() == changeButton && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {
		globalFrame->assetBrowser->addEventListener(this, UIEvent::OK_EVENT);
		
		std::vector<String> extensions;
		extensions.push_back("sprite");
		globalFrame->showAssetBrowser(extensions);
	}
}

void ScreenSpriteProp::setPropData(PolycodeEditorPropActionData* data) {
	set(data->stringVal);
	dispatchEvent(new Event(), Event::CHANGE_EVENT);	
}

void ScreenSpriteProp::set(String fileName) {

	if(fileName != previewSprite->getFileName()) {
		printf("%s != %s\n", fileName.c_str(), previewSprite->getFileName().c_str());
		if(previewSprite) {
			propContents->removeChild(previewSprite);
			delete previewSprite;
		}
		lastData = currentData;
		currentData = fileName;
		
		previewSprite = new ScreenSprite(fileName);
		previewSprite->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
		previewSprite->setPosition(2, 1);
		previewSprite->setShapeSize(48,48);		
		propContents->addChild(previewSprite);	
	}
}

String ScreenSpriteProp::get() {
	return previewSprite->getFileName();
}

ScreenEntityInstanceProp::ScreenEntityInstanceProp(String caption) : PropProp(caption, "ScreenEntityInstance"){
	previewInstance = new ScreenEntityInstance("default/default.entity2d");
	previewInstance->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	previewInstance->setPosition(2, 1);
	propContents->addChild(previewInstance);

	changeButton = new UIButton("Change", 80);
	propContents->addChild(changeButton);
	changeButton->setPosition(60, 5);
	changeButton->addEventListener(this, UIEvent::CLICK_EVENT);
	setHeight(50);
}

ScreenEntityInstanceProp::~ScreenEntityInstanceProp() {

}


void ScreenEntityInstanceProp::handleEvent(Event *event) {

	if(event->getDispatcher() == globalFrame->assetBrowser && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::OK_EVENT) {
		String filePath = globalFrame->assetBrowser->getSelectedAssetPath();
		
		set(filePath);
		
		globalFrame->assetBrowser->removeAllHandlersForListener(this);
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
		dispatchEvent(new PropEvent(this, NULL, PropDataString(lastData), PropDataString(currentData)), PropEvent::EVENT_PROP_CHANGE);
		globalFrame->hideModal();
	}

	if(event->getDispatcher() == changeButton && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {
		globalFrame->assetBrowser->addEventListener(this, UIEvent::OK_EVENT);
		
		std::vector<String> extensions;
		extensions.push_back("entity2d");
		globalFrame->showAssetBrowser(extensions);
	}
}

void ScreenEntityInstanceProp::setPropData(PolycodeEditorPropActionData* data) {
	set(data->stringVal);
	dispatchEvent(new Event(), Event::CHANGE_EVENT);
}

void ScreenEntityInstanceProp::set(String fileName) {

	if(fileName != previewInstance->getFileName()) {
		propContents->removeChild(previewInstance);
		delete previewInstance;
		previewInstance = new ScreenEntityInstance(fileName);
		previewInstance->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
		previewInstance->setPosition(2, 1);
		
		lastData = currentData;
		currentData = fileName;
		
		Number radius = previewInstance->getCompoundBBoxRadius();
		if(radius > 48) {
			previewInstance->setScale(48.0/(radius*2.0), 48.0/(radius*2.0));		
		}
		
		propContents->addChild(previewInstance);	
	}
}

String ScreenEntityInstanceProp::get() {
	return previewInstance->getFileName();
}

ShapeSheet::ShapeSheet() : PropSheet("SCREEN SHAPE", "ScreenShape") {
	shapeSize = new Vector2Prop("Shape size");
	addProp(shapeSize);

	typeProp = new ComboProp("Shape type");
	addProp(typeProp);
	
	typeProp->comboEntry->addComboItem("Rectangle");
	typeProp->comboEntry->addComboItem("Oval");

	strokeProp = new BoolProp("Enable stroke");
	addProp(strokeProp);

	strokeColorProp = new ColorProp("Stroke color");
	addProp(strokeColorProp);
			
	strokeSize = new NumberProp("Stroke width");
	addProp(strokeSize);		
			
	propHeight = 190;	
	
	shape = NULL;
	lastShapeType = -10;

}

ShapeSheet::~ShapeSheet() {

}
		
void ShapeSheet::handleEvent(Event *event) {

	if(!shape)
		return;

	if(event->getDispatcher() == strokeProp  && event->getEventCode() == Event::CHANGE_EVENT) {
		lastStrokeVal = strokeProp->get();
		shape->strokeEnabled = lastStrokeVal;
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}

	if(event->getDispatcher() == shapeSize  && event->getEventCode() == Event::CHANGE_EVENT) {
		lastShapeSize = shapeSize->get();
		shape->setShapeSize(lastShapeSize.x, lastShapeSize.y);
		dispatchEvent(new Event(), Event::CHANGE_EVENT);	
	}

	if(event->getDispatcher() == typeProp  && event->getEventCode() == Event::CHANGE_EVENT) {
		lastShapeType = typeProp->get();
		shape->setShapeType(lastShapeType+1);
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}
	
	if(event->getDispatcher() == strokeColorProp  && event->getEventCode() == Event::CHANGE_EVENT) {
		lastStrokeColor = strokeColorProp->get();
		shape->strokeColor = lastStrokeColor;
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}

	if(event->getDispatcher() == strokeSize  && event->getEventCode() == Event::CHANGE_EVENT) {
		lastStrokeSize = strokeSize->get();
		shape->strokeWidth = lastStrokeSize;
		dispatchEvent(new Event(), Event::CHANGE_EVENT);	
	}
	
	PropSheet::handleEvent(event);
}

void ShapeSheet::Update() {
	if(shape) {
	
		enabled = true;
			
		if(lastShapeSize.x != shape->getWidth() && lastShapeSize.y != shape->getHeight()) {
			lastShapeSize = Vector2(shape->getWidth(), shape->getHeight());
			shapeSize->set(lastShapeSize);
		}
		
		if(lastShapeType != shape->getShapeType()-1) {
			typeProp->set(shape->getShapeType()-1);			
			lastShapeType = shape->getShapeType()-1;			
		}
		
		if(lastStrokeVal != shape->strokeEnabled) {
			strokeProp->set(shape->strokeEnabled);
			lastStrokeVal = shape->strokeEnabled;
		}
		
		if(lastStrokeColor != shape->strokeColor) {
			strokeColorProp->set(shape->strokeColor);
		}
		
		if(lastStrokeSize != shape->strokeWidth) {
			strokeSize->set(shape->strokeWidth);
		}
	} else {
		enabled = false;
	}
}

EntityPropSheet::EntityPropSheet() : PropSheet("CUSTOM PROPERTIES", "entityProps"){

	propHeight = 75;
	
	addButton = new UIButton("Add Property", 150);
	addButton->addEventListener(this, UIEvent::CLICK_EVENT);
	addChild(addButton);
	addButton->setPosition(15, 35);
	
	entity = NULL;
	lastEntity = NULL;
	
	lastNumProps = 0;
	
	removeIndex = -1;
}

void EntityPropSheet::applyPropActionData(PolycodeEditorPropActionData *data) {
	if(!entity)
		return;
		
	entity->entityProps.clear();
	for(int i=0; i < data->entity.entityProps.size(); i++) {
			entity->entityProps.push_back(data->entity.entityProps[i]);
	}
	
	refreshProps();
}


void EntityPropSheet::handleEvent(Event *event) {
	if(!entity)
		return;
		
	if(event->getDispatcher() == addButton && event->getEventType() == "UIEvent") {
		PolycodeEditorPropActionData *beforeData = PropDataEntity(entity);	
		entity->entityProps.push_back(EntityProp());
		refreshProps();
		PolycodeEditorPropActionData *afterData = PropDataEntity(entity);			
		PropEvent *propEvent = new PropEvent(NULL, this, beforeData, afterData);
		dispatchEvent(propEvent, PropEvent::EVENT_PROP_CHANGE);					
		
	}
	
	for(int i=0; i < props.size(); i++) {
		if(event->getDispatcher() == props[i] && event->getEventType() == "") {
			switch(event->getEventCode()) {						
				case Event::CANCEL_EVENT:
					removeIndex = i;
				break;
				case Event::CHANGE_EVENT:
					PolycodeEditorPropActionData *beforeData = PropDataEntity(entity);
					if(i < entity->entityProps.size()) {
						entity->entityProps[i].propName = ((CustomProp*)props[i])->getKey();
						entity->entityProps[i].propValue = ((CustomProp*)props[i])->getValue();			
					}
					PolycodeEditorPropActionData *afterData = PropDataEntity(entity);			
					PropEvent *propEvent = new PropEvent(NULL, this, beforeData, afterData);
					dispatchEvent(propEvent, PropEvent::EVENT_PROP_CHANGE);					
				break;				
			}
		}
	}
	PropSheet::handleEvent(event);
}

void EntityPropSheet::refreshProps() {

	for(int i=0; i < props.size(); i++) {
		contents->removeChild(props[i]);
		props[i]->removeAllHandlersForListener(this);
		delete props[i];
	}
	props.clear();
	propHeight = 75;
	
	for(int i=0; i < entity->entityProps.size(); i++) {			
		EntityProp prop = entity->entityProps[i];
		CustomProp *newProp = new CustomProp(prop.propName, prop.propValue);
		newProp->addEventListener(this, Event::CANCEL_EVENT);
		newProp->addEventListener(this, Event::CHANGE_EVENT);		
		addProp(newProp);
		propHeight += 35;
	}
	
	
	addButton->setPosition(15, propHeight-40);	
	
	
	if(lastNumProps != entity->entityProps.size()) {
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}
	
	lastNumProps = entity->entityProps.size();
		
	Resize(width, height);	
}

void EntityPropSheet::Update() {
	if(entity) {
	
		if(removeIndex != -1) {
		
			PolycodeEditorPropActionData *beforeData = PropDataEntity(entity);
				
			if(removeIndex < entity->entityProps.size()) {
				entity->entityProps.erase(entity->entityProps.begin() + removeIndex);
			}
			removeIndex = -1;
			refreshProps();
			PolycodeEditorPropActionData *afterData = PropDataEntity(entity);			
			PropEvent *propEvent = new PropEvent(NULL, this, beforeData, afterData);
			dispatchEvent(propEvent, PropEvent::EVENT_PROP_CHANGE);
		}
	
		enabled = true;		
		if(entity != lastEntity) {
			refreshProps();
			lastEntity = entity;
		}
	} else {
		enabled = false;		
	}
}

ShaderOptionsSheet::ShaderOptionsSheet(String title, String name, bool fragmentParams) : PropSheet(title, name){
	shader = NULL;
	this->fragmentParams = fragmentParams;
	propHeight = 40;
}

ShaderOptionsSheet::~ShaderOptionsSheet() {

}

void ShaderOptionsSheet::handleEvent(Event *event) {

	if(event->getEventCode() == Event::CHANGE_EVENT) {
		for(int i=0 ; i < props.size(); i++) {
			if(event->getDispatcher() == props[i]) {
				if(props[i]->propType == "Slider") {
					(*(Number*)binding->getLocalParamByName(props[i]->label->getText())->data) = ((SliderProp*)props[i])->get();
				} else if(props[i]->propType == "Color") {
					(*(Color*)binding->getLocalParamByName(props[i]->label->getText())->data) = ((ColorProp*)props[i])->get();
				
				}
				dispatchEvent(new Event(), Event::CHANGE_EVENT);				
				return;
			}
		}
	}

	PropSheet::handleEvent(event);
}

void ShaderOptionsSheet::Update() {

}

void ShaderOptionsSheet::clearShader() {
	for(int i=0; i < props.size(); i++) {
		contents->removeChild(props[i]);
		props[i]->removeAllHandlersForListener(this);
		delete props[i];
	}
	props.clear();
	propHeight = 30;
}

void ShaderOptionsSheet::setOptionsFromParams(std::vector<ProgramParam> &params) {

	for(int i=0; i < params.size(); i++) {
			if(!params[i].isAuto) {
				switch (params[i].paramType) {
				
					case ProgramParam::PARAM_Number:
					{
						String paramName = params[i].name;
						Number paramMin = (*(Number*) params[i].minValue);
						Number paramMax = (*(Number*) params[i].maxValue);						
						SliderProp *sliderProp = new SliderProp(paramName, paramMin, paramMax);
						addProp(sliderProp);
						
						Number numberValue = (*(Number*)binding->getLocalParamByName(params[i].name)->data);
						sliderProp->set(numberValue);
						propHeight += 30;
					}
					break;					
					case ProgramParam::PARAM_Color:
					{
						String paramName = params[i].name;
						
						ColorProp *colorProp = new ColorProp(paramName);
						addProp(colorProp);
						
						Color colorValue = (*(Color*)binding->getLocalParamByName(params[i].name)->data);
						colorProp->set(colorValue);
						
						propHeight += 40;												
					}
					break;
					
				}				
														
			}
		}	
}

void ShaderOptionsSheet::setShader(Shader *shader, Material *material) {
	clearShader();
	this->shader = shader;
	this->material = material;
	
	if(!shader || !material)
		return;
		
	binding = material->getShaderBinding(0);
	
	if(fragmentParams) {	
		setOptionsFromParams(shader->expectedFragmentParams);
	} else {
		setOptionsFromParams(shader->expectedVertexParams);
	}
	
	dispatchEvent(new Event(), Event::COMPLETE_EVENT);	
	Resize(width, height);
}

ShaderTexturesSheet::ShaderTexturesSheet() : PropSheet("SHADER TEXTURES", "shader_textures"){
	shader = NULL;
	propHeight = 40;
}

ShaderTexturesSheet::~ShaderTexturesSheet() {

}

void ShaderTexturesSheet::handleEvent(Event *event) {

	if(event->getEventCode() == Event::CHANGE_EVENT) {
		for(int i=0; i < textureProps.size(); i++) {
			if(event->getDispatcher() == textureProps[i]) {
				binding->clearTexture(textureProps[i]->label->getText());
				binding->addTexture(textureProps[i]->label->getText(), textureProps[i]->get());
				dispatchEvent(new Event(), Event::CHANGE_EVENT);
			}
		}	
	}
	PropSheet::handleEvent(event);
}

void ShaderTexturesSheet::Update() {

}

void ShaderTexturesSheet::clearShader() {
	for(int i=0; i < props.size(); i++) {
		contents->removeChild(props[i]);
		props[i]->removeAllHandlersForListener(this);
		delete props[i];
	}
	props.clear();
	textureProps.clear();
	
	propHeight = 30;
}

void ShaderTexturesSheet::setShader(Shader *shader, Material *material) {
	clearShader();
	this->shader = shader;
	this->material = material;
	
	if(!shader || !material)
		return;
		
	binding = material->getShaderBinding(0);	
	
	for(int i=0; i < shader->expectedTextures.size(); i++) {
		TextureProp *textureProp = new TextureProp(shader->expectedTextures[i]);
		
		if(material) {
			if(material->getShaderBinding(0)) {
				Texture *currentTexture = material->getShaderBinding(0)->getTexture(shader->expectedTextures[i]);
				if(currentTexture) {
					textureProp->set(currentTexture);
				}
			}
		}
		
		addProp(textureProp);
		textureProps.push_back(textureProp);
		propHeight += 65;
	}

	dispatchEvent(new Event(), Event::COMPLETE_EVENT);	
	Resize(width, height);
}

ScreenEntitySheet::ScreenEntitySheet() : PropSheet("SCREEN ENTITY", "screen_entity") {

	widthProp = new NumberProp("Width");
	addProp(widthProp);
	
	heightProp = new NumberProp("Height");
	addProp(heightProp);
	
	propHeight = 100;
	entity = NULL;
	lastEntity = NULL;
}

ScreenEntitySheet::~ScreenEntitySheet() {

}
		
void ScreenEntitySheet::handleEvent(Event *event) {
	if(entity) {
		if(event->getDispatcher() == widthProp) {
			entity->setWidth(widthProp->get());
			dispatchEvent(new Event(), Event::CHANGE_EVENT);		
		} else 	if(event->getDispatcher() == heightProp) {
			entity->setHeight(heightProp->get());
			dispatchEvent(new Event(), Event::CHANGE_EVENT);		
		}

	}
	PropSheet::handleEvent(event);	
}

void ScreenEntitySheet::Update() {
	if(entity) {
		enabled = true;
		if(entity != lastEntity) {
			widthProp->set(entity->getWidth());
			heightProp->set(entity->getHeight());
			lastEntity = entity;
		}
	} else {
		enabled = false;
	}
}

EntitySheet::EntitySheet() : PropSheet("ENTITY", "entity"){
	idProp = new StringProp("ID");
	addProp(idProp);

	tagProp = new StringProp("Tags (foo,bar)");
	addProp(tagProp);

	colorProp = new ColorProp("Color");
	addProp(colorProp);
	
	blendingProp = new ComboProp("Blend mode");
	addProp(blendingProp);
	
	blendingProp->comboEntry->addComboItem("Normal");
	blendingProp->comboEntry->addComboItem("Lighten");
	blendingProp->comboEntry->addComboItem("Color");
	blendingProp->comboEntry->addComboItem("Premultiplied");
	blendingProp->comboEntry->addComboItem("Multiply");
	
	propHeight = 160;
	
	entity = NULL;
	lastEntity = NULL;
}

EntitySheet::~EntitySheet() {

}

void EntitySheet::handleEvent(Event *event) {

	if(!entity)
		return;

	if(event->getDispatcher() == blendingProp  && event->getEventCode() == Event::CHANGE_EVENT) {
		entity->blendingMode = blendingProp->get();
	} else if(event->getDispatcher() == colorProp  && event->getEventCode() == Event::CHANGE_EVENT) {
		entity->color = colorProp->get();
	}else if(event->getDispatcher() == idProp  && event->getEventCode() == Event::CHANGE_EVENT) {
		entity->id = idProp->get();
	} else if(event->getDispatcher() == tagProp  && event->getEventCode() == Event::CHANGE_EVENT) {
		
		String tagString = "";
		for(int i=0; i < entity->getNumTags(); i++) {
			if(i != 0) {
				tagString += ",";
			}
			tagString += entity->getTagAtIndex(i);
		}
		
		entity->clearTags();
		String cleaned =  tagProp->get().replace(" ", "");
		std::vector<String> tags = cleaned.split(",");
		for(int i=0; i < tags.size(); i++) {
			entity->addTag(tags[i]);
		}		
	}
	
	PropSheet::handleEvent(event);	
}

void EntitySheet::Update() {
	if(entity) {
		
		enabled = true;
		
		if(entity != lastEntity) {	
			idProp->set(entity->id);			
			
			String tagString = "";
			for(int i=0; i < entity->getNumTags(); i++) {
				if(i != 0) {
					tagString += ",";
				}
				tagString += entity->getTagAtIndex(i);
			}
			tagProp->set(tagString);
			
			colorProp->set(entity->color);			
			blendingProp->set(entity->blendingMode);
			
			lastEntity = entity;			
		}
	} else {
		enabled = false;
	}
}


ScreenParticleSheet::ScreenParticleSheet() : PropSheet("PARTICLE EMITTER", "ScreenParticleEmitter") {

	textureProp = new TextureProp("Texture");
	addProp(textureProp);

	blendingProp = new ComboProp("Blend mode");
	addProp(blendingProp);
	
	blendingProp->comboEntry->addComboItem("Normal");
	blendingProp->comboEntry->addComboItem("Lighten");
	blendingProp->comboEntry->addComboItem("Color");
	blendingProp->comboEntry->addComboItem("Premultiplied");
	blendingProp->comboEntry->addComboItem("Multiply");

	ignoreParentMatrixProp = new BoolProp("No parent matrix");
	addProp(ignoreParentMatrixProp);
	
	numParticlesProp = new NumberProp("Num particles");
	addProp(numParticlesProp);
		
	lifespanProp = new NumberProp("Lifespan (secs)");
	addProp(lifespanProp);

	particleScaleProp = new NumberProp("Size");
	addProp(particleScaleProp);
	
	sizeProp = new Vector2Prop("Emitter size");
	addProp(sizeProp);

	dirProp = new Vector2Prop("Direction");
	addProp(dirProp);

	gravProp = new Vector2Prop("Gravity");
	addProp(gravProp);

	deviationProp = new Vector2Prop("Deviation");
	addProp(deviationProp);

	brightnessDeviationProp = new SliderProp("Brightness var", 0.0, 1.0);
	addProp(brightnessDeviationProp);

	perlinEnableProp = new BoolProp("Perlin mod");
	addProp(perlinEnableProp);
	
	perlinModSizeProp = new NumberProp("Perlin size");
	addProp(perlinModSizeProp);

	speedModProp = new SliderProp("Speed mod", 0.0, 2.0);
	addProp(speedModProp);

	rotationSpeedProp = new NumberProp("Rot. speed");
	addProp(rotationSpeedProp);
	
	rotationFollowsPathProp = new BoolProp("Auto-orient");
	addProp(rotationFollowsPathProp);
	
	useScaleCurvesProp = new BoolProp("Scale curves");
	addProp(useScaleCurvesProp);
	
	scaleCurveProp = new BezierCurveProp("Edit scale", "Scale");
	addProp(scaleCurveProp);

	useColorCurvesProp = new BoolProp("Color curves");
	addProp(useColorCurvesProp);
	
	colorCurveProp = new BezierRGBACurveProp("Edit color");
	addProp(colorCurveProp);
	
	emitter = NULL;
	propHeight = 680;
}

void ScreenParticleSheet::handleEvent(Event *event) {

	if(!emitter)
		return;
		
	if(event->getDispatcher() == blendingProp  && event->getEventCode() == Event::CHANGE_EVENT) {
		emitter->setParticleBlendingMode(blendingProp->get());
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}
		

	if(event->getDispatcher() == sizeProp  && event->getEventCode() == Event::CHANGE_EVENT) {
		lastSize = Vector3(sizeProp->get().x, sizeProp->get().y, 0.0);
		emitter->emitterRadius = lastSize;
		emitter->resetAll();		
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}
	
	if(event->getDispatcher() == dirProp  && event->getEventCode() == Event::CHANGE_EVENT) {
		lastDir = Vector3(dirProp->get().x, dirProp->get().y, 0.0);
		emitter->dirVector = lastDir;
		emitter->resetAll();
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}

	if(event->getDispatcher() == gravProp  && event->getEventCode() == Event::CHANGE_EVENT) {
		lastGrav = Vector3(gravProp->get().x, gravProp->get().y, 0.0);
		emitter->gravVector = lastGrav;
		emitter->resetAll();
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}


	if(event->getDispatcher() == deviationProp  && event->getEventCode() == Event::CHANGE_EVENT) {
		lastDeviation = Vector3(deviationProp->get().x, deviationProp->get().y, 0.0);
		emitter->deviation = lastDeviation;
		emitter->resetAll();		
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}
	
	if(event->getDispatcher() == particleScaleProp  && event->getEventCode() == Event::CHANGE_EVENT) {
		lastParticleScale = particleScaleProp->get();
		emitter->particleSize = lastParticleScale;
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}	

	if(event->getDispatcher() == brightnessDeviationProp  && event->getEventCode() == Event::CHANGE_EVENT) {
		lastBrightnessDeviation = brightnessDeviationProp->get();
		emitter->brightnessDeviation = lastBrightnessDeviation;
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}
	
	if(event->getDispatcher() == perlinModSizeProp  && event->getEventCode() == Event::CHANGE_EVENT) {
		lastPerlinSize = perlinModSizeProp->get();
		emitter->perlinModSize = lastPerlinSize;
		emitter->resetAll();		
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}	
	
	if(event->getDispatcher() == speedModProp  && event->getEventCode() == Event::CHANGE_EVENT) {
		lastSpeedMod = speedModProp->get();
		emitter->particleSpeedMod = lastSpeedMod;
		emitter->resetAll();		
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}		

	if(event->getDispatcher() == perlinEnableProp  && event->getEventCode() == Event::CHANGE_EVENT) {
		lastEnableProp = perlinEnableProp->get();
		emitter->perlinEnabled = lastEnableProp;
		emitter->resetAll();		
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}	
	
	if(event->getDispatcher() == lifespanProp  && event->getEventCode() == Event::CHANGE_EVENT) {
		lastLifespan = lifespanProp->get();
		emitter->lifespan = lastLifespan;
		emitter->resetAll();
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}		

	if(event->getDispatcher() == numParticlesProp  && event->getEventCode() == Event::CHANGE_EVENT) {
		lastNumParticles = numParticlesProp->get();
		emitter->setParticleCount(lastNumParticles);
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}
	
	if(event->getDispatcher() == textureProp) {
		Texture *selectedTexture = textureProp->previewShape->getTexture();		
		emitter->setParticleTexture(selectedTexture);
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}			

	if(event->getDispatcher() == rotationSpeedProp  && event->getEventCode() == Event::CHANGE_EVENT) {
		lastRotationSpeed = rotationSpeedProp->get();
		emitter->rotationSpeed = lastRotationSpeed;		
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}	
	
	if(event->getDispatcher() == rotationFollowsPathProp  && event->getEventCode() == Event::CHANGE_EVENT) {
		lastRotationFollowsPath = rotationFollowsPathProp->get();
		emitter->rotationFollowsPath = lastRotationFollowsPath;		
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}	

	if(event->getDispatcher() == ignoreParentMatrixProp  && event->getEventCode() == Event::CHANGE_EVENT) {
		lastIgnoreParentMatrix = ignoreParentMatrixProp->get();
		emitter->setIgnoreParentMatrix(lastIgnoreParentMatrix);		
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}	
	
	if(event->getDispatcher() == useScaleCurvesProp  && event->getEventCode() == Event::CHANGE_EVENT) {
		lastUseScaleCurves = useScaleCurvesProp->get();
		emitter->useScaleCurves = lastUseScaleCurves;		
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}		

	if(event->getDispatcher() == useColorCurvesProp  && event->getEventCode() == Event::CHANGE_EVENT) {
		lastUseColorCurves = useColorCurvesProp->get();
		emitter->useColorCurves = lastUseColorCurves;		
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}		
	
	
	PropSheet::handleEvent(event);
}

void ScreenParticleSheet::Update() {
	if(emitter) {
	
		enabled = true;	
	
		if(emitter->emitterRadius != lastSize) {
			sizeProp->set(Vector2(emitter->emitterRadius.x, emitter->emitterRadius.y));
			lastSize = emitter->emitterRadius;
		}
		
		if(emitter->dirVector != lastDir) {
			dirProp->set(Vector2(emitter->dirVector.x, emitter->dirVector.y));
			lastDir = emitter->dirVector;
		}		

		if(emitter->gravVector != lastGrav) {
			gravProp->set(Vector2(emitter->gravVector.x, emitter->gravVector.y));
			lastGrav = emitter->gravVector;
		}		

		if(emitter->deviation != lastDeviation) {
			deviationProp->set(Vector2(emitter->emitterRadius.x, emitter->emitterRadius.y));
			lastSize = emitter->emitterRadius;
		}

		if(emitter->getIgnoreParentMatrix() != lastIgnoreParentMatrix) {
			ignoreParentMatrixProp->set(emitter->getIgnoreParentMatrix());
			lastIgnoreParentMatrix = emitter->getIgnoreParentMatrix();
		}
				
		if(emitter->brightnessDeviation != lastBrightnessDeviation) {
			lastBrightnessDeviation = emitter->brightnessDeviation;
			brightnessDeviationProp->set(lastBrightnessDeviation);
		}

		if(emitter->particleSize != lastParticleScale) {
			lastParticleScale = emitter->particleSize;
			particleScaleProp->set(lastParticleScale);
		}
		
		if(emitter->perlinModSize != lastPerlinSize) {
			lastPerlinSize = emitter->perlinModSize;
			perlinModSizeProp->set(lastPerlinSize);
		}

		if(emitter->perlinEnabled != lastEnableProp) {
			lastEnableProp = emitter->perlinEnabled;
			perlinEnableProp->set(lastEnableProp);
		}

		if(emitter->particleSpeedMod != lastSpeedMod) {
			lastSpeedMod = emitter->particleSpeedMod;
			speedModProp->set(lastSpeedMod);
		}

		if(emitter->rotationSpeed != lastRotationSpeed) {
			lastRotationSpeed = emitter->rotationSpeed;
			rotationSpeedProp->set(lastRotationSpeed);
		}
		
		if(emitter->lifespan != lastLifespan) {
			lastLifespan = emitter->lifespan;
			lifespanProp->set(lastLifespan);
		}
		
		if(emitter->getNumParticles() != lastNumParticles) {
			lastNumParticles = emitter->getNumParticles();
			numParticlesProp->set(lastNumParticles);
		}
		
		if(emitter->rotationFollowsPath != lastRotationFollowsPath) {
			lastRotationFollowsPath = emitter->rotationFollowsPath;
			rotationFollowsPathProp->set(lastRotationFollowsPath);
		}
		
		
		if(emitter->rotationFollowsPath != lastRotationFollowsPath) {
			lastRotationFollowsPath = emitter->rotationFollowsPath;
			rotationFollowsPathProp->set(lastRotationFollowsPath);
		}
		
		if(emitter->useScaleCurves != lastUseScaleCurves) {
			lastUseScaleCurves = emitter->useScaleCurves;
			useScaleCurvesProp->set(lastUseScaleCurves);
		}

		if((&emitter->scaleCurve) != lastScaleCurve) {
			lastScaleCurve = &emitter->scaleCurve;
			scaleCurveProp->curve = lastScaleCurve;
		}
		
		
		if(emitter->useColorCurves != lastUseColorCurves) {
			lastUseColorCurves = emitter->useColorCurves;
			useColorCurvesProp->set(lastUseColorCurves);
		}

		blendingProp->set(emitter->getParticleBlendingMode());

		colorCurveProp->curveR = &emitter->colorCurveR;
		colorCurveProp->curveG = &emitter->colorCurveG;		
		colorCurveProp->curveB = &emitter->colorCurveB;
		colorCurveProp->curveA = &emitter->colorCurveA;			
				
		textureProp->set(emitter->getParticleTexture());
		
	} else {
		enabled = false;
	}
}
		

ScreenParticleSheet::~ScreenParticleSheet() {

}

Transform2DSheet::Transform2DSheet() : PropSheet("2D TRANSFORM", "transform2d") {

	positionProp = new Vector2Prop("Position");
	addProp(positionProp);

	scaleProp = new Vector2Prop("Scale");
	addProp(scaleProp);

	rotationProp = new NumberProp("Rotation (deg)");
	addProp(rotationProp);

	topLeftProp = new BoolProp("Topleft anchor");
	addProp(topLeftProp);
	
	entity = NULL;
	propHeight = 160;
}

void Transform2DSheet::handleEvent(Event *event) {

	if(!entity)
		return;

	if(event->getDispatcher() == positionProp  && event->getEventCode() == Event::CHANGE_EVENT) {
		lastPositon = positionProp->get();
		entity->setPosition(lastPositon);
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}

	if(event->getDispatcher() == scaleProp  && event->getEventCode() == Event::CHANGE_EVENT) {
		lastScale = scaleProp->get();
		entity->setScale(lastScale);
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}

	if(event->getDispatcher() == rotationProp  && event->getEventCode() == Event::CHANGE_EVENT) {
		lastRotation = rotationProp->get();
		entity->setRotation(lastRotation);
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}

	if(event->getDispatcher() == topLeftProp  && event->getEventCode() == Event::CHANGE_EVENT) {
		if(topLeftProp->get()) {
			lastPositionMode = ScreenEntity::POSITION_TOPLEFT;
			entity->setPositionMode(lastPositionMode);
		} else {
			lastPositionMode = ScreenEntity::POSITION_CENTER;
			entity->setPositionMode(lastPositionMode);		
		}
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}


	PropSheet::handleEvent(event);
}

void Transform2DSheet::Update() {
	if(entity) {
	
		enabled = true;	
	
		if(entity->getPosition2D() != lastPositon) {
			positionProp->set(entity->getPosition2D());
			lastPositon = entity->getPosition2D();
		}
		
		if(entity->getScale2D() != lastScale) {
			scaleProp->set(entity->getScale2D());
			lastScale = entity->getScale2D();
		}

		if(entity->getPositionMode() != lastPositionMode) {
			if(entity->getPositionMode() == ScreenEntity::POSITION_TOPLEFT) {
				topLeftProp->set(true);
			} else {
				topLeftProp->set(false);			
			}
		
			lastPositionMode = entity->getPositionMode();
		}

		
		if(entity->getRotation() != lastRotation) {
			lastRotation = entity->getRotation();
			rotationProp->set(lastRotation);
		}
	} else {
		enabled = false;
	}
}
		

Transform2DSheet::~Transform2DSheet() {

}

ScreenImageSheet::ScreenImageSheet() : PropSheet("SCREEN IMAGE", "ScreenImage") {
	image = NULL;
	
	texture = new TextureProp("Texture");
	texture->addEventListener(this, Event::CHANGE_EVENT);
	addProp(texture);
	
	propHeight = 100;
}

ScreenImageSheet::~ScreenImageSheet() {

}
		
void ScreenImageSheet::handleEvent(Event *event) {
	if(!image)
		return;

	if(event->getDispatcher() == texture) {
		Texture *selectedTexture = texture->previewShape->getTexture();
		
		image->setTexture(selectedTexture);
		selectedTexture->reloadOnFileModify = true;
		image->setShapeSize(selectedTexture->getWidth(), selectedTexture->getHeight());
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}
	
	PropSheet::handleEvent(event);
}

void ScreenImageSheet::Update() {
	if(image) {
		enabled = true;	
		texture->set(image->getTexture());
	} else {
		enabled = false;
	}
}

ScreenSpriteSheet::ScreenSpriteSheet() : PropSheet("SCREEN SPRITE", "ScreenSprite") {
	sprite = NULL;
	lastAnimationCheck = NULL;
	
	spriteProp = new ScreenSpriteProp("Sprite");
	spriteProp->addEventListener(this, Event::CHANGE_EVENT);
	addProp(spriteProp);	
	
	defaultAnimationProp = new ComboProp("Animation");
	defaultAnimationProp->addEventListener(this, Event::CHANGE_EVENT);
	addProp(defaultAnimationProp);	
	
	propHeight = 140;
}

ScreenSpriteSheet::~ScreenSpriteSheet() {

}
		
void ScreenSpriteSheet::handleEvent(Event *event) {
	if(!sprite)
		return;

	if(event->getDispatcher() == defaultAnimationProp) {
		sprite->playAnimation(defaultAnimationProp->comboEntry->getSelectedItem()->label, 0, false);
		spriteProp->previewSprite->playAnimation(defaultAnimationProp->comboEntry->getSelectedItem()->label, 0, false);
	}

	if(event->getDispatcher() == spriteProp) {
		sprite->loadFromFile(spriteProp->get());
			defaultAnimationProp->comboEntry->clearItems();
			for(int i=0; i < sprite->getNumAnimations(); i++) {
				defaultAnimationProp->comboEntry->addComboItem(sprite->getAnimationAtIndex(i)->name);
			}
		
	}
	
	PropSheet::handleEvent(event);
}

void ScreenSpriteSheet::Update() {
	if(sprite) {
	
		if(lastAnimationCheck != sprite) {
			defaultAnimationProp->comboEntry->clearItems();
			for(int i=0; i < sprite->getNumAnimations(); i++) {
				defaultAnimationProp->comboEntry->addComboItem(sprite->getAnimationAtIndex(i)->name);
				if(sprite->getCurrentAnimation()) {
					if(sprite->getCurrentAnimation()->name == sprite->getAnimationAtIndex(i)->name) {
						defaultAnimationProp->comboEntry->setSelectedIndex(i);
						spriteProp->previewSprite->playAnimation(sprite->getCurrentAnimation()->name, 0, false);
					}
				}
			}
			lastAnimationCheck = sprite;
		}
	
		enabled = true;	
		spriteProp->set(sprite->getFileName());
	} else {
		enabled = false;
	}
}

ScreenEntityInstanceSheet::ScreenEntityInstanceSheet() : PropSheet("ENTITY INSTANCE", "ScreenEntityInstance") {
	instance = NULL;
	
	instanceProp = new ScreenEntityInstanceProp("Entity file");
	instanceProp->addEventListener(this, Event::CHANGE_EVENT);
	addProp(instanceProp);
	
	propHeight = 100;
}

ScreenEntityInstanceSheet::~ScreenEntityInstanceSheet() {

}
		
void ScreenEntityInstanceSheet::handleEvent(Event *event) {
	if(!instance)
		return;


	if(event->getDispatcher() == instanceProp) {

		instance->loadFromFile(instanceProp->get());
		instance->getResourceEntry()->setResourcePath(instanceProp->get());
		instance->getResourceEntry()->setResourceName(instanceProp->get());
		
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}

	PropSheet::handleEvent(event);
}

void ScreenEntityInstanceSheet::Update() {
	if(instance) {
		enabled = true;	
		instanceProp->set(instance->getFileName());
	} else {
		enabled = false;
	}
}

ScreenLabelSheet::ScreenLabelSheet() : PropSheet("SCREEN LABEL", "ScreenLabel") {
	label = NULL;
	
	caption = new StringProp("Contents");
	caption->addEventListener(this, Event::CHANGE_EVENT);
	addProp(caption);

	size = new NumberProp("Size (px)");
	size->addEventListener(this, Event::CHANGE_EVENT);
	addProp(size);	

	font = new ComboProp("Font");
	font->addEventListener(this, Event::CHANGE_EVENT);
	addProp(font);	
	
	
	enableAA = new BoolProp("Antialias");
	enableAA->addEventListener(this, Event::CHANGE_EVENT);
	addProp(enableAA);	

	lastSize = -1;
	
	propHeight = 160;
	
	refreshFonts();
}

void ScreenLabelSheet::refreshFonts() {
	
	FontManager *fontManager = CoreServices::getInstance()->getFontManager();
	
	font->comboEntry->clearItems();
	
	for(int i=0; i < fontManager->getNumFonts(); i++) {
		FontEntry *entry = fontManager->getFontEntryByIndex(i);
		if(entry->fontName != "section") {
			font->comboEntry->addComboItem(entry->fontName);
		}
	}

}

ScreenLabelSheet::~ScreenLabelSheet() {

}

void ScreenLabelSheet::handleEvent(Event *event) {
	if(!label)
		return;

	if(event->getDispatcher() == caption) {
		label->setText(caption->get());
		dispatchEvent(new Event(), Event::CHANGE_EVENT);		
	}

	if(event->getDispatcher() == font) {
		String fontName = font->comboEntry->getSelectedItem()->label;
		Font *font = CoreServices::getInstance()->getFontManager()->getFontByName(fontName);
		label->getLabel()->setFont(font);
		label->setText(caption->get());		
		lastFont = fontName;
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}


	if(event->getDispatcher() == size) {
		int newSize= size->get();
		if(newSize < 4)
			newSize = 4;
		
		lastSize = newSize;	
					
		label->getLabel()->setSize(newSize);
		label->setText(caption->get());		
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}


	if(event->getDispatcher() == enableAA) {
		if(enableAA->get()) {
			label->getLabel()->setAntialiasMode(Label::ANTIALIAS_FULL);
		} else {
			label->getLabel()->setAntialiasMode(Label::ANTIALIAS_NONE);		
		}		
		label->setText(caption->get());
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}
	
	PropSheet::handleEvent(event);
}

void ScreenLabelSheet::Update() {
	if(label) {
		enabled = true;		
		if(label != lastLabel) {
			lastLabel = label;
	
		caption->set(label->getText());		
		enableAA->set(label->getLabel()->getAntialiasMode() == Label::ANTIALIAS_FULL);
		size->set(label->getLabel()->getSize());
		
		for(int i=0; i < font->comboEntry->getNumItems(); i++) {
			String comboFont = font->comboEntry->getItemAtIndex(i)->label;
			
			if(comboFont == label->getLabel()->getFont()->getFontName()) {
				if(comboFont != lastFont) {
					font->set(i);
					lastFont = comboFont;
				}
			}
		}

		}
	} else {
		enabled = false;
	}
}

SoundSheet::SoundSheet() : PropSheet("SCREEN SOUND", "Sound") {
	sound = NULL;
	
	soundProp = new SoundProp("Sound file");
	soundProp->addEventListener(this, Event::CHANGE_EVENT);
	addProp(soundProp);
	
	referenceDistance = new NumberProp("Reference dist");
	referenceDistance->addEventListener(this, Event::CHANGE_EVENT);
	addProp(referenceDistance);

	maxDistance = new NumberProp("Max dist");
	maxDistance->addEventListener(this, Event::CHANGE_EVENT);
	addProp(maxDistance);

	volume = new NumberProp("Volume");
	volume->addEventListener(this, Event::CHANGE_EVENT);
	addProp(volume);
	
	pitch = new NumberProp("Pitch");
	pitch->addEventListener(this, Event::CHANGE_EVENT);
	addProp(pitch);
	
	lastReferenceDistance = 0.0;
	lastMaxDistance = 0.0;
	lastVolume = 0.0;
	lastPitch = 0.0;
	lastSoundPath = "";
	
	propHeight = 230;
}

SoundSheet::~SoundSheet() {

}
		
void SoundSheet::handleEvent(Event *event) {
	if(!sound)
		return;

	if(event->getDispatcher() == referenceDistance  && event->getEventCode() == Event::CHANGE_EVENT) {
		lastReferenceDistance = referenceDistance->get();
		sound->getSound()->setReferenceDistance(lastReferenceDistance);
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}

	if(event->getDispatcher() == maxDistance  && event->getEventCode() == Event::CHANGE_EVENT) {
		lastMaxDistance = maxDistance->get();
		sound->getSound()->setMaxDistance(lastMaxDistance);
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}

	if(event->getDispatcher() == volume  && event->getEventCode() == Event::CHANGE_EVENT) {
		lastVolume = volume->get();
		sound->getSound()->setVolume(lastVolume);
	}

	if(event->getDispatcher() == pitch  && event->getEventCode() == Event::CHANGE_EVENT) {
		lastPitch = pitch->get();
		sound->getSound()->setPitch(lastPitch);
	}

	if(event->getDispatcher() == soundProp  && event->getEventCode() == Event::CHANGE_EVENT) {
		lastSoundPath = soundProp->get();
		sound->getSound()->loadFile(lastSoundPath);
	}


	PropSheet::handleEvent(event);
}

void SoundSheet::Update() {
	if(sound) {
		enabled = true;	
		
		if(sound->getSound()->getFileName() != lastSoundPath) {
			lastSoundPath = sound->getSound()->getFileName();
			soundProp->set(sound->getSound()->getFileName());
		}
		
		if(sound->getSound()->getReferenceDistance() != lastReferenceDistance) {
			lastReferenceDistance = sound->getSound()->getReferenceDistance();
			referenceDistance->set(sound->getSound()->getReferenceDistance());
		}

		if(sound->getSound()->getMaxDistance() != lastMaxDistance) {
			lastMaxDistance = sound->getSound()->getMaxDistance();
			maxDistance->set(sound->getSound()->getMaxDistance());
		}

		if(sound->getSound()->getVolume() != lastVolume) {
			lastVolume = sound->getSound()->getVolume();
			volume->set(sound->getSound()->getVolume());
		}

		if(sound->getSound()->getPitch() != lastPitch) {
			lastPitch = sound->getSound()->getPitch();
			pitch->set(sound->getSound()->getPitch());
		}
		

	} else {
		enabled = false;
	}
}
