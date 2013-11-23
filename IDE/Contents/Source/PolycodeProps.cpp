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
#include "PolyCubemap.h"

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
	data->entity = entity->Clone(false, true);
	data->entity->ownsChildren = false;
	for(int i=0; i < data->entity->getNumChildren(); i++) {
		data->entity->removeChild(data->entity->getChildAtIndex(i));
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

	setAnchorPoint(-1.0, -1.0, 0.0);

	bg = new UIRect(10,10);
	bg->setAnchorPoint(-1.0, -1.0, 0.0);
	bg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiBgColor"));
	
	addChild(bg);
	bg->blockMouseInput = true;
	bg->processInputEvents = true;
	
	blockMouseInput = true;

	bg2 = new UIRect(10,10);
	bg2->setAnchorPoint(-1.0, -1.0, 0.0);
	bg2->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));
	
	addChild(bg2);

	UILabel *label = new UILabel(caption, 18, "section", Label::ANTIALIAS_FULL);
	label->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderFontColor"));
	addChild(label);
	label->setPosition(10, 3);

	propContents = new Entity();
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
	Resize(getWidth(), getHeight());
	scrollContainer->setScrollValue(0, 0);	
}
		
void PropList::Resize(Number width, Number height) {
	setWidth(width);
	setHeight(height);
		
	scrollContainer->Resize(width, height-30);
	
	bg->Resize(width, height);
	bg2->Resize(width, 30);	
	
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
		props[i]->Resize(getWidth(), getHeight());
	}
	
	rebuildTransformMatrix();
	scrollContainer->setContentSize(width, offsetY);
}

void PropList::handleEvent(Event *event) {
	if(event->getEventType() == "" && event->getEventCode() == Event::COMPLETE_EVENT) {
		Resize(getWidth(), getHeight());
	} else if(event->getEventCode() == Event::CHANGE_EVENT) {
	
	}
}

void PropList::addPropSheet(PropSheet *sheet) {
	propContents->addChild(sheet);
	props.push_back(sheet);
	Resize(getWidth(), getHeight());
	sheet->addEventListener(this, Event::COMPLETE_EVENT);
	sheet->addEventListener(this, Event::CHANGE_EVENT);	
}

PropSheet::PropSheet(String caption, String type) : UIElement() {
	this->caption = caption;
	this->type = type;
	
	customUndoHandler = false;
	
	bg = new UIRect(30,30);
	addChild(bg);
	bg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiSmallHeaderBgColor"));
	bg->setAnchorPoint(-1.0, -1.0, 0.0);
	
	UILabel *label = new UILabel(caption, 18, "section", Label::ANTIALIAS_FULL);
	label->color.a = 1.0;
	addChild(label);
	label->setPosition(25, 3);	
	
	contents = new Entity();
	contents->processInputEvents = true;
	addChild(contents);
	contents->setPosition(20,35);
	
	collapseButton = new UIImageButton("main/collapse.png", 1.0, 12, 12);
	addChild(collapseButton);
	collapseButton->addEventListener(this, UIEvent::CLICK_EVENT);
	collapseButton->setPosition(5, 9);

	expandButton = new UIImageButton("main/expand.png", 1.0, 12, 12);
	addChild(expandButton);
	expandButton->addEventListener(this, UIEvent::CLICK_EVENT);	
	expandButton->setPosition(5, 9);
	expandButton->enabled = false;
		
	collapsed  = false;
	propTopPadding = 0;
	propHeight = 0;
}

void PropSheet::setCollapsed(bool val) {
	if(collapsed != val) {
		collapsed = val;
		if(collapsed) {
			collapseButton->enabled = false;
			expandButton->enabled = true;	
			contents->enabled = false;	
			contents->visible = false;	
		} else {
			collapseButton->enabled = true;
			expandButton->enabled = false;				
			contents->enabled = true;			
			contents->visible = true;			
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
	
	if(!customUndoHandler) {
	if(event->getEventCode() == PropEvent::EVENT_PROP_CHANGE ) {
		PropEvent *propEvent = (PropEvent*) event;
		PropEvent *newEvent = new PropEvent(propEvent->prop, this, propEvent->beforeData, propEvent->afterData);		
		dispatchEvent(newEvent, PropEvent::EVENT_PROP_CHANGE);
	}
	}
}

PropSheet::~PropSheet() {

}

void PropSheet::setTopPadding(Number padding) {
	propTopPadding = padding;
}

void PropSheet::Resize(Number width, Number height) {
	setWidth(width);
	setHeight(height);
	
	bg->Resize(width, 30);
	
	Number yOffset = propTopPadding;
	
	for(int i=0; i < props.size(); i++) {
		props[i]->setPosition(0, yOffset);
		props[i]->setPropWidth(width);
		yOffset += props[i]->getHeight();
	}
}

void PropSheet::addProp(PropProp *prop) {
	contents->addChild(prop);
	props.push_back(prop);
	prop->addEventListener(this, Event::CHANGE_EVENT);
	prop->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);	
	Resize(getWidth(), getHeight());
}


void PropSheet::applyPropActionData(PolycodeEditorPropActionData *data) {
	data->prop->setPropData(data);
}

void PropProp::setPropName(String newName) {
    label->setText(newName);
}

PropProp::PropProp(String caption, String type) : UIElement() {

	suppressChangeEvent = false;
	propType = type;
	label = new UILabel(caption, 11);
	label->setPosition(0, 5);
	addChild(label);
	
	propContents = new Entity();
	propContents->processInputEvents = true;
	addChild(propContents);
	propContents->setPosition(100, 0);
	
	setHeight(20);
}

PropProp::~PropProp() {

}

Vector3Prop::Vector3Prop(String caption) : PropProp(caption, "Vector3") {
    
	labelX = new UILabel("X:", 11);
	labelX->color.a = 1.0;
	propContents->addChild(labelX);
	labelX->setPosition(-20, 5);
    
	labelY = new UILabel("Y:", 11);
	labelY->color.a = 1.0;
	propContents->addChild(labelY);
	labelY->setPosition(-20, 25);

    labelZ = new UILabel("Z:", 11);
	labelZ->color.a = 1.0;
	propContents->addChild(labelZ);
	labelZ->setPosition(-20, 45);
    
	xInput = new UITextInput(false, 50, 12);
	xInput->addEventListener(this, UIEvent::CHANGE_EVENT);
	xInput->setText("0");
	xInput->setNumberOnly(true);
	propContents->addChild(xInput);
	xInput->setPosition(0, 0);

   	yInput = new UITextInput(false, 50, 12);
	yInput->addEventListener(this, UIEvent::CHANGE_EVENT);
	yInput->setText("0");
	yInput->setNumberOnly(true);
	propContents->addChild(yInput);
	yInput->setPosition(0, 20);

    zInput = new UITextInput(false, 50, 12);
	zInput->addEventListener(this, UIEvent::CHANGE_EVENT);
	zInput->setText("0");
	zInput->setNumberOnly(true);
	propContents->addChild(zInput);
	zInput->setPosition(0, 40);

	setHeight(65);
}

void Vector3Prop::setPropWidth(Number width) {
    xInput->Resize(width-PROP_PADDING-propContents->getPosition().x, xInput->getHeight());
    yInput->Resize(width-PROP_PADDING-propContents->getPosition().x, yInput->getHeight());
    zInput->Resize(width-PROP_PADDING-propContents->getPosition().x, zInput->getHeight());
}

void Vector3Prop::handleEvent(Event *event) {

	if(event->getDispatcher() == xInput || event->getDispatcher() == yInput || event->getDispatcher() == zInput) {
		if(event->getEventCode() == UIEvent::CHANGE_EVENT) {
            
//			if(xInput && yInput && zInput) {
//				lastData = currentData;
//				currentData = Vector2(atof(positionX->getText().c_str()), atof(positionY->getText().c_str()));
//			}
			if(!suppressChangeEvent) {
				dispatchEvent(new Event(), Event::CHANGE_EVENT);
//				dispatchEvent(new PropEvent(this, NULL, PropDataVector2(lastData), PropDataVector2(currentData)), PropEvent::EVENT_PROP_CHANGE);
                
			}
		}
	}

}

void Vector3Prop::setPropData(PolycodeEditorPropActionData* data) {
//	set(data->vector2Val);
	dispatchEvent(new Event(), Event::CHANGE_EVENT);
}

void Vector3Prop::set(const Vector3 &position) {
	suppressChangeEvent = true;
	xInput->setText(String::NumberToString(position.x, 5));
	yInput->setText(String::NumberToString(position.y, 5));
	zInput->setText(String::NumberToString(position.z, 5));
	suppressChangeEvent = false;
}

Vector3 Vector3Prop::get() const {
	return Vector3(atof(xInput->getText().c_str()), atof(yInput->getText().c_str()), atof(zInput->getText().c_str()));
}

Vector3Prop::~Vector3Prop() {
    
}

Vector2Prop::Vector2Prop(String caption) : PropProp(caption, "Vector2") {

	labelX = new UILabel("X:", 11);
	labelX->color.a = 1.0;
	propContents->addChild(labelX);
	labelX->setPosition(-20, 6);	

	labelY = new UILabel("Y:", 11);
	labelY->color.a = 1.0;
	propContents->addChild(labelY);
	labelY->setPosition(60, 6);	
	
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

	setHeight(25);

}

void Vector2Prop::setPropWidth(Number width) {
	labelX->setPosition(0, 6);
	labelY->setPosition(((width-propContents->getPosition().x-PROP_PADDING)/2.0), 6);	
	
	positionX->setPositionX(labelX->getPosition().x + 20);
	positionX->Resize(floor(((width-propContents->getPosition().x-PROP_PADDING)/2.0)-25), positionX->getHeight());

	positionY->setPositionX(labelY->getPosition().x + 20);
	positionY->Resize(floor(((width-propContents->getPosition().x-PROP_PADDING)/2.0)-25), positionY->getHeight());

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
	positionX->setText(String::NumberToString(position.x, 5));
	positionY->setText(String::NumberToString(position.y, 5));
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
	
	removeButton = new UIImageButton("main/remove_icon.png", 1.0, 12, 12);
	removeButton->addEventListener(this, UIEvent::CLICK_EVENT);	
	propContents->addChild(removeButton);
	removeButton->setPosition(-110, 6);
	
	setHeight(25);

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
	setHeight(25);
}

void StringProp::setPropWidth(Number width) {
    stringEntry->Resize(width-PROP_PADDING-propContents->getPosition().x, stringEntry->getHeight());
	stringEntry->setPosition(0.0, 2);
	
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
	stringEntry->setText(str);
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
	slider->setPosition(0, 8);
	propContents->addChild(slider);
	
	valueLabel = new UILabel("0.0", 10);
	propContents->addChild(valueLabel);
	valueLabel->setPosition(120, 5);
	valueLabel->color.a = 1.0;
	setHeight(25);
}

void SliderProp::setPropWidth(Number width) {
	slider->Resize(width - propContents->getPosition().x - PROP_PADDING - 50, slider->getHeight());
	valueLabel->setPosition(width - propContents->getPosition().x - PROP_PADDING - 30, 5);
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

	numberEntry = new UITextInput(false, 50, 20);
	numberEntry->addEventListener(this, UIEvent::CHANGE_EVENT);
	numberEntry->setText("0");
	numberEntry->setNumberOnly(true);
	propContents->addChild(numberEntry);
	numberEntry->setPosition(0, 2);

	setHeight(25);

}

void NumberProp::setPropWidth(Number width) {
    numberEntry->Resize(width-PROP_PADDING-propContents->getPosition().x, numberEntry->getHeight());
	numberEntry->setPosition(0.0, 2);
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
	numberEntry->setText(String::NumberToString(number), 5);
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
	colorEntry->setPosition(-2, 0);
	propContents->addChild(colorEntry);
	setHeight(25);

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
	setHeight(25);
}

void ComboProp::setPropWidth(Number width) {
	comboEntry->Resize(width - propContents->getPosition().x - PROP_PADDING, comboEntry->getHeight());
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
	checkEntry->setPosition(0, 4);
	propContents->addChild(checkEntry);
	setHeight(25);

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

	soundFile = new UILabel("", 11);
	soundFile->setPosition(0, 5);
	propContents->addChild(soundFile);	
	soundFile->color.a = 1.0;

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

	setHeight(25);
	
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

	setHeight(25);
	
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
	previewShape = new UIRect(48, 48);
	previewShape->setAnchorPoint(-1.0, -1.0, 0.0);
	previewShape->setPosition(2, 1);
	propContents->addChild(previewShape);

	changeButton = new UIButton("Change", 80);
	propContents->addChild(changeButton);
	changeButton->setPosition(60, 5);
	changeButton->addEventListener(this, UIEvent::CLICK_EVENT);
	
	textureLabel = new UILabel("", 12, "sans");
	propContents->addChild(textureLabel);
	textureLabel->setPosition(-100, 32);
	textureLabel->color.a = 1.0;
		
	setHeight(60);	
}

void TextureProp::setPropWidth(Number width) {
	changeButton->setPosition(width-changeButton->getWidth()-PROP_PADDING-100, 5);
	previewShape->setPosition(changeButton->getPosition().x-48-10, 1);	
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

SceneSpriteProp::SceneSpriteProp(String caption) : PropProp(caption, "SceneSprite"){

		previewSprite = new SceneSprite("default/default.sprite");
        previewSprite->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
		previewSprite->setAnchorPoint(-1.0, -1.0, 0.0);
		previewSprite->setPosition(2, 1);
		previewSprite->setPrimitiveOptions(ScenePrimitive::TYPE_VPLANE, 48,48);		
		propContents->addChild(previewSprite);	

	
	changeButton = new UIButton("Change", 80);
	propContents->addChild(changeButton);
	changeButton->setPosition(60, 5);
	changeButton->addEventListener(this, UIEvent::CLICK_EVENT);
	setHeight(70);
}

SceneSpriteProp::~SceneSpriteProp() {

}

void SceneSpriteProp::handleEvent(Event *event) {

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

void SceneSpriteProp::setPropData(PolycodeEditorPropActionData* data) {
	set(data->stringVal);
	dispatchEvent(new Event(), Event::CHANGE_EVENT);	
}

void SceneSpriteProp::set(String fileName) {

	if(fileName != previewSprite->getFileName()) {
		if(previewSprite) {
			propContents->removeChild(previewSprite);
			delete previewSprite;
		}
		lastData = currentData;
		currentData = fileName;
		
		previewSprite = new SceneSprite(fileName);
		previewSprite->setAnchorPoint(-1.0, -1.0, 0.0);
		previewSprite->setPosition(2, 1);
        previewSprite->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
		previewSprite->setPrimitiveOptions(ScenePrimitive::TYPE_VPLANE, 48,48);		
		propContents->addChild(previewSprite);	
	}
}

String SceneSpriteProp::get() {
	return previewSprite->getFileName();
}

SceneEntityInstanceProp::SceneEntityInstanceProp(String caption) : PropProp(caption, "SceneEntityInstance"){
	previewInstance = new SceneEntityInstance("default/default.entity2d");
	previewInstance->setAnchorPoint(-1.0, -1.0, 0.0);
	previewInstance->setPosition(2, 1);
	propContents->addChild(previewInstance);

	changeButton = new UIButton("Change", 80);
	propContents->addChild(changeButton);
	changeButton->setPosition(60, 5);
	changeButton->addEventListener(this, UIEvent::CLICK_EVENT);
	setHeight(50);
}

SceneEntityInstanceProp::~SceneEntityInstanceProp() {

}


void SceneEntityInstanceProp::handleEvent(Event *event) {

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

void SceneEntityInstanceProp::setPropData(PolycodeEditorPropActionData* data) {
	set(data->stringVal);
	dispatchEvent(new Event(), Event::CHANGE_EVENT);
}

void SceneEntityInstanceProp::set(String fileName) {

	if(fileName != previewInstance->getFileName()) {
		propContents->removeChild(previewInstance);
		delete previewInstance;
		previewInstance = new SceneEntityInstance(fileName);
		previewInstance->setAnchorPoint(-1.0, -1.0, 0.0);
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

String SceneEntityInstanceProp::get() {
	return previewInstance->getFileName();
}

ShaderPassProp::ShaderPassProp(Material *material, int shaderIndex) : PropProp("", "ShaderPassProp") {
	this->material = material;
	this->shader = material->getShader(shaderIndex);
	this->shaderIndex = shaderIndex;
	
	removeButton = new UIImageButton("main/remove_icon.png", 1.0, 12, 12);
	removeButton->addEventListener(this, UIEvent::CLICK_EVENT);	
	propContents->addChild(removeButton);
	removeButton->setPosition(-110, 6);
	
	shaderComboBox = new UIComboBox(globalMenu, 100);
	shaderComboBox->addEventListener(this, UIEvent::CHANGE_EVENT);
	propContents->addChild(shaderComboBox);
	
	int index = 0;
	MaterialManager *materialManager = CoreServices::getInstance()->getMaterialManager();
	for(int i=0; i < materialManager->getNumShaders(); i++) {
		if(materialManager->getShaderByIndex(i)->screenShader) {
			shaderComboBox->addComboItem(materialManager->getShaderByIndex(i)->getName(), (void*)materialManager->getShaderByIndex(i));			
			if(shader == materialManager->getShaderByIndex(i)) {
				shaderComboBox->setSelectedIndex(index);
			}
			index++;
		}
	}	
	
	
	editButton = new UIButton("Options", 30);
	editButton->addEventListener(this, UIEvent::CLICK_EVENT);
	propContents->addChild(editButton);
	setHeight(25);
}

ShaderPassProp::~ShaderPassProp() {

}
		
void ShaderPassProp::handleEvent(Event *event) {
	if(event->getDispatcher() == removeButton && event->getEventCode() == UIEvent::CLICK_EVENT) {
		dispatchEvent(new Event(), Event::REMOVE_EVENT);
	} else if(event->getDispatcher() == editButton && event->getEventCode() == UIEvent::CLICK_EVENT) {
		dispatchEvent(new Event(), Event::SELECT_EVENT);		
	} else if(event->getDispatcher() == shaderComboBox) {
		Shader *selectedShader = (Shader*)shaderComboBox->getSelectedItem()->data;
		if(selectedShader) {
			if(material->getShader(shaderIndex) != selectedShader) {
				material->removeShader(shaderIndex);				
				ShaderBinding *newShaderBinding = selectedShader->createBinding();				
				material->addShaderAtIndex(selectedShader, newShaderBinding, shaderIndex);
				dispatchEvent(new Event(), Event::CHANGE_EVENT);
			}
		}
	}
}

void ShaderPassProp::setPropWidth(Number width) {
	Number adjustedWidth = width-PROP_PADDING-5;
	shaderComboBox->setPosition(-90, 0);
	shaderComboBox->Resize(floor(adjustedWidth * 0.75), shaderComboBox->getHeight());

	editButton->setPosition(-90 + shaderComboBox->getWidth() + 5, 0);
	editButton->Resize(floor(adjustedWidth * 0.25), editButton->getHeight());
}

TargetBindingProp::TargetBindingProp(Shader *shader, Material *material, ShaderBinding *binding, RenderTargetBinding *targetBinding) : PropProp("", "TargetBindingProp") {
	this->targetBinding = targetBinding;
	this->material = material;
	this->shader = shader;
	this->binding = binding;
		
	removeButton = new UIImageButton("main/remove_icon.png", 1.0, 12, 12);
	removeButton->addEventListener(this, UIEvent::CLICK_EVENT);	
	propContents->addChild(removeButton);
	removeButton->setPosition(-110, 6);

	typeComboBox = new UIComboBox(globalMenu, 100);
	typeComboBox->addComboItem("IN");		
	typeComboBox->addComboItem("OUT");
	typeComboBox->addComboItem("COLOR");
	typeComboBox->addComboItem("DEPTH");		
	typeComboBox->setSelectedIndex(targetBinding->mode);
	typeComboBox->addEventListener(this, UIEvent::CHANGE_EVENT);
	propContents->addChild(typeComboBox);

	targetComboBox = new UIComboBox(globalMenu, 100);	
	for(int i=0; i < material->getNumShaderRenderTargets(); i++) {
		ShaderRenderTarget *target = material->getShaderRenderTarget(i);		
		targetComboBox->addComboItem(target->id, (void*) target);
		if(targetBinding->texture == target->texture) {
			targetComboBox->setSelectedIndex(i);
		}
	}
	targetComboBox->addEventListener(this, UIEvent::CHANGE_EVENT);
	propContents->addChild(targetComboBox);
	
	textureComboBox = new UIComboBox(globalMenu, 100);	
	for(int i=0; i < shader->expectedTextures.size(); i++) {
		textureComboBox->addComboItem(shader->expectedTextures[i]);
		if(shader->expectedTextures[i] == targetBinding->name) {
			textureComboBox->setSelectedIndex(i);
		}
	}
		
	textureComboBox->addEventListener(this, UIEvent::CHANGE_EVENT);
	propContents->addChild(textureComboBox);
	
	setHeight(25);
	
	if(typeComboBox->getSelectedIndex() == 1) {
		textureComboBox->enabled = false;
		textureComboBox->visible = false;			
	} else {
		textureComboBox->enabled = true;
		textureComboBox->visible = true;		
	}		

	if(typeComboBox->getSelectedIndex() == 2 || typeComboBox->getSelectedIndex() == 3) {
		targetComboBox->enabled = false;
		targetComboBox->visible = false;
	} else {
		targetComboBox->enabled = true;
		targetComboBox->visible = true;
	}		
	
}

TargetBindingProp::~TargetBindingProp() {

}

void TargetBindingProp::handleEvent(Event *event) {
	if(event->getDispatcher() == removeButton && event->getEventCode() == UIEvent::CLICK_EVENT) {
		dispatchEvent(new Event(), Event::REMOVE_EVENT);
	} else if(event->getDispatcher() == typeComboBox && event->getEventCode() == UIEvent::CHANGE_EVENT) {
		binding->clearTexture(targetBinding->name);	
		
		if(typeComboBox->getSelectedIndex() == 1) {
			textureComboBox->enabled = false;
			textureComboBox->visible = false;
		} else {
			textureComboBox->enabled = true;
			textureComboBox->visible = true;
			binding->addTexture(targetBinding->name, targetBinding->texture);	
		}		
		
		if(typeComboBox->getSelectedIndex() == 2 || typeComboBox->getSelectedIndex() == 3) {
			targetComboBox->enabled = false;
			targetComboBox->visible = false;
		} else {
			targetComboBox->enabled = true;
			targetComboBox->visible = true;
		}	
		
		binding->removeRenderTargetBinding(targetBinding);		
		targetBinding->mode = typeComboBox->getSelectedIndex();		
		
		binding->addRenderTargetBinding(targetBinding);		
		
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	} else if(event->getDispatcher() == targetComboBox && event->getEventCode() == UIEvent::CHANGE_EVENT) {
		ShaderRenderTarget *target = (ShaderRenderTarget*)targetComboBox->getSelectedItem()->data;		
		targetBinding->texture = target->texture;
		targetBinding->id  = target->id;
		
		binding->removeRenderTargetBinding(targetBinding);		
		binding->addRenderTargetBinding(targetBinding);		

		binding->clearTexture(targetBinding->name);
		if(targetBinding->mode == RenderTargetBinding::MODE_IN) {
			binding->addTexture(targetBinding->name, targetBinding->texture);		
		}
		dispatchEvent(new Event(), Event::CHANGE_EVENT);		
	} else if(event->getDispatcher() == textureComboBox && event->getEventCode() == UIEvent::CHANGE_EVENT) {
		targetBinding->name = textureComboBox->getSelectedItem()->label;
		
		binding->removeRenderTargetBinding(targetBinding);		
		binding->addRenderTargetBinding(targetBinding);		

		binding->clearTexture(targetBinding->name);
		binding->addTexture(targetBinding->name, targetBinding->texture);
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}
}

void TargetBindingProp::setPropWidth(Number width) {
	Number size = width-PROP_PADDING-85-15;
	
	typeComboBox->setPosition(-90, 0);
	typeComboBox->Resize(80, typeComboBox->getHeight());

	targetComboBox->setPosition(-90 + 85, 0);
	targetComboBox->Resize(floor(size*0.5), targetComboBox->getHeight());

	textureComboBox->setPosition(-90 + 85 + targetComboBox->getWidth() + 5, 0);
	textureComboBox->Resize(floor(size*0.5), textureComboBox->getHeight());

}

RenderTargetProp::RenderTargetProp(ShaderRenderTarget *renderTarget, Material *material) : PropProp("", "RenderTargetProp") {

	this->material = material;
	this->renderTarget = renderTarget;

	removeButton = new UIImageButton("main/remove_icon.png", 1.0, 12, 12);
	removeButton->addEventListener(this, UIEvent::CLICK_EVENT);	
	propContents->addChild(removeButton);
	removeButton->setPosition(-110, 6);
	
	nameInput = new UITextInput(false, 20, 12);
	nameInput->addEventListener(this, UIEvent::CHANGE_EVENT);
	propContents->addChild(nameInput);
	nameInput->setText(renderTarget->id);
	nameInput->setCaretPosition(0);
	
	widthInput = new UITextInput(false, 20, 12);
	widthInput->setNumberOnly(true);
	widthInput->setText(String::NumberToString(renderTarget->width));
	propContents->addChild(widthInput);
	widthInput->setCaretPosition(0);
	widthInput->addEventListener(this, UIEvent::CHANGE_EVENT);
		
	heightInput = new UITextInput(false, 20, 12);
	heightInput->setNumberOnly(true);
	heightInput->setText(String::NumberToString(renderTarget->height));	
	propContents->addChild(heightInput);
	heightInput->setCaretPosition(0);
	heightInput->addEventListener(this, UIEvent::CHANGE_EVENT);
			
	typeComboBox = new UIComboBox(globalMenu, 100);
	typeComboBox->addComboItem("Pixels");		
	typeComboBox->addComboItem("Norm.");
	typeComboBox->setSelectedIndex(renderTarget->sizeMode);	
	typeComboBox->addEventListener(this, UIEvent::CHANGE_EVENT);
	propContents->addChild(typeComboBox);
	
	setHeight(25);
}

void RenderTargetProp::setPropWidth(Number width) {
	Number quarter = floor((width-PROP_PADDING- (5*3)) * 0.25);
	nameInput->setPosition(-90, 0);
	nameInput->Resize(floor(quarter * 1.8), nameInput->getHeight());

	widthInput->setPosition(-90 + 5 + (quarter * 1.8), 0);
	widthInput->Resize(floor(quarter*0.6), widthInput->getHeight());

	heightInput->setPosition(-90 + 10 + (quarter * 2.4), 0);
	heightInput->Resize(floor(quarter*0.6), heightInput->getHeight());	
	
	typeComboBox->setPosition(-90 + 15 + (quarter*3), 0);
	typeComboBox->Resize(floor(quarter), typeComboBox->getHeight());
}

RenderTargetProp::~RenderTargetProp() {

}

void RenderTargetProp::recreateRenderTarget() {
	material->recreateRenderTarget(renderTarget);
}

void RenderTargetProp::handleEvent(Event *event) {
	if(event->getEventType() == "UIEvent") {

		if(event->getDispatcher() == nameInput) {
			renderTarget->id = nameInput->getText();
		}
	
		if(event->getDispatcher() == typeComboBox) {
			renderTarget->sizeMode = typeComboBox->getSelectedIndex();
			recreateRenderTarget();
		}

		if(event->getDispatcher() == typeComboBox) {
			renderTarget->sizeMode = typeComboBox->getSelectedIndex();
			recreateRenderTarget();
		}

		if(event->getDispatcher() == widthInput) {
			renderTarget->width =  atof(widthInput->getText().c_str());
			recreateRenderTarget();
		}

		if(event->getDispatcher() == heightInput) {
			renderTarget->height =  atof(heightInput->getText().c_str());
			recreateRenderTarget();
		}

		
		if(event->getDispatcher() == removeButton) {
			dispatchEvent(new Event(), Event::CANCEL_EVENT);
		}
	}
	
	PropProp::handleEvent(event);
}

ShaderPassesSheet::ShaderPassesSheet() : PropSheet("SHADER PASSES", "shaderPasses") {
	propHeight = 70;
	addButton = new UIButton("Add Shader Pass", 150);
	addButton->addEventListener(this, UIEvent::CLICK_EVENT);
	contents->addChild(addButton);
	addButton->setPosition(15, 35);
	
	customUndoHandler = true;
	material = NULL;
	binding = NULL;
	selectedProp = NULL;
	
	removeIndex = -1;
}

ShaderPassesSheet::~ShaderPassesSheet() {

}

void ShaderPassesSheet::setMaterial(Material *material) {
	this->material = material;
	refreshPasses();
}

void ShaderPassesSheet::refreshPasses() {

	for(int i=0; i < props.size(); i++) {
		contents->removeChild(props[i]);
		props[i]->removeAllHandlersForListener(this);
		delete props[i];
	}
	props.clear();
	propHeight = 0;

	if(!material) {
		return;
	}

	for(int i=0; i < material->getNumShaders(); i++) {
		ShaderPassProp *passProp = new ShaderPassProp(material, i);
		passProp->addEventListener(this, Event::REMOVE_EVENT);
		passProp->addEventListener(this, Event::CHANGE_EVENT);		
		passProp->addEventListener(this, Event::SELECT_EVENT);
		addProp(passProp);
		propHeight += 30;	
	}
	
	addButton->setPosition(15, propHeight);	
	propHeight += 70;	

	dispatchEvent(new Event(), Event::COMPLETE_EVENT);		
	Resize(getWidth(), getHeight());	
	
}

void ShaderPassesSheet::Update() {
	if(removeIndex != -1) {
		material->removeShader(removeIndex);
		refreshPasses();
		removeIndex = -1;			
	}
}

void ShaderPassesSheet::handleEvent(Event *event) {

	if(event->getDispatcher() == addButton) {
	
		Shader *defaultShader = (Shader*)CoreServices::getInstance()->getResourceManager()->getResource(Resource::RESOURCE_SHADER, "PassThrough");
		if(defaultShader) {	
			ShaderBinding *newShaderBinding = defaultShader->createBinding();		
			material->addShader(defaultShader, newShaderBinding);
		}
		refreshPasses();
		dispatchEvent(new Event(), Event::CHANGE_EVENT);		
	} else {
		for(int i=0; i < props.size(); i++) {	
			if(event->getDispatcher() == props[i]) {
				if(event->getEventCode() == Event::CHANGE_EVENT) {
					dispatchEvent(new Event(), Event::CHANGE_EVENT);
					selectedProp = (ShaderPassProp*)props[i];
					dispatchEvent(new Event(), Event::SELECT_EVENT);					
				} else if(event->getEventCode() == Event::SELECT_EVENT) {
					selectedProp = (ShaderPassProp*)props[i];
					dispatchEvent(new Event(), Event::SELECT_EVENT);				
				} else if(event->getEventCode() == Event::REMOVE_EVENT) {
					removeIndex = i;
					dispatchEvent(new Event(), Event::REMOVE_EVENT);					
				}
			}
		}
	}

	PropSheet::handleEvent(event);
}

TargetBindingsSheet::TargetBindingsSheet() : PropSheet("TEXTURE BINDINGS", "targetBindings") {
	propHeight = 70;
	addButton = new UIButton("Add Render Target", 150);
	addButton->addEventListener(this, UIEvent::CLICK_EVENT);
	contents->addChild(addButton);
	addButton->setPosition(15, 35);	
	customUndoHandler = true;	
	material = NULL;
	binding = NULL;	
	bindingToRemove = NULL;
}

TargetBindingsSheet::~TargetBindingsSheet() {

}

void TargetBindingsSheet::setShader(Shader *shader, Material *material, ShaderBinding *binding) {
	this->shader = shader;
	this->material = material;		
	this->binding = binding;
	
	refreshTargets();
}

void TargetBindingsSheet::Update() {
	if(bindingToRemove) {
		binding->removeRenderTargetBinding(bindingToRemove);
		bindingToRemove = NULL;
		refreshTargets();
	}
}

void TargetBindingsSheet::refreshTargets() {
	for(int i=0; i < props.size(); i++) {
		contents->removeChild(props[i]);
		props[i]->removeAllHandlersForListener(this);
		delete props[i];
	}
	props.clear();
	propHeight = 0;

	if(!material) {
		return;
	}
	
	for(int i=0; i < binding->getNumRenderTargetBindings(); i++) {
		RenderTargetBinding *targetBinding = binding->getRenderTargetBinding(i);
		TargetBindingProp *bindingProp = new TargetBindingProp(shader, material, binding, targetBinding);
		bindingProp->addEventListener(this, Event::REMOVE_EVENT);	
		addProp(bindingProp);
		propHeight += 30;		
		
	}
				
	addButton->setPosition(15, propHeight);	
	propHeight += 70;	

	dispatchEvent(new Event(), Event::COMPLETE_EVENT);		
	Resize(getWidth(), getHeight());	
}

void TargetBindingsSheet::handleEvent(Event *event) {

	if(event->getDispatcher() == addButton) {
		RenderTargetBinding* newBinding = new RenderTargetBinding();
		newBinding->mode = RenderTargetBinding::MODE_COLOR;
		newBinding->texture = NULL;		
		binding->addRenderTargetBinding(newBinding);				
		refreshTargets();			
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}
	
	for(int i=0; i < props.size(); i++) {
		if(event->getDispatcher() == props[i]) {
			switch(event->getEventCode()) {						
				case Event::REMOVE_EVENT:
					bindingToRemove = ((TargetBindingProp*)props[i])->targetBinding;
				break;
				case Event::CHANGE_EVENT:
					dispatchEvent(new Event(), Event::CHANGE_EVENT);
				break;				
			}
		}
	}
	
	
	PropSheet::handleEvent(event);
}


RenderTargetsSheet::RenderTargetsSheet() : PropSheet("RENDER TARGETS", "renderTargets") {
	propHeight = 70;
	addButton = new UIButton("Add Render Target", 150);
	addButton->addEventListener(this, UIEvent::CLICK_EVENT);
	contents->addChild(addButton);
	addButton->setPosition(15, 35);
	
	customUndoHandler = true;	
	material = NULL;
	binding = NULL;
	
	removeIndex = -1;	
}

RenderTargetsSheet::~RenderTargetsSheet() {

}

void RenderTargetsSheet::refreshTargets() {
	for(int i=0; i < props.size(); i++) {
		contents->removeChild(props[i]);
		props[i]->removeAllHandlersForListener(this);
		delete props[i];
	}
	props.clear();
	propHeight = 0;

	if(!material) {
		return;
	}
	
	for(int i=0; i < material->getNumShaderRenderTargets(); i++) {
		ShaderRenderTarget *renderTarget  = material->getShaderRenderTarget(i);
		RenderTargetProp *targetProp = new RenderTargetProp(renderTarget, material);		
		targetProp->addEventListener(this, Event::CANCEL_EVENT);	
		addProp(targetProp);
		propHeight += 30;		
	}
	
	addButton->setPosition(15, propHeight);	
	propHeight += 70;	

	dispatchEvent(new Event(), Event::COMPLETE_EVENT);		
	Resize(getWidth(), getHeight());	
}

void RenderTargetsSheet::Update() {
	if(material != lastMaterial) {
		lastMaterial = material;
		refreshTargets();
	}
	
	if(removeIndex != -1) {		
		material->removeShaderRenderTarget(removeIndex);
		removeIndex = -1;
		refreshTargets();
	}
	
}

void RenderTargetsSheet::handleEvent(Event *event) {
	if(!material)
		return;

	if(event->getDispatcher() == addButton) {
		ShaderRenderTarget* newRenderTarget = new ShaderRenderTarget();
		newRenderTarget->id = "render_target";
		newRenderTarget->width = 1.0;
		newRenderTarget->height = 1.0;
		newRenderTarget->normalizedWidth = normTextureWidth;
		newRenderTarget->normalizedHeight = normTextureHeight;		
		newRenderTarget->sizeMode = ShaderRenderTarget::SIZE_MODE_NORMALIZED;		
		material->addShaderRenderTarget(newRenderTarget);
		refreshTargets();
	}
	
	for(int i=0; i < props.size(); i++) {
		if(event->getDispatcher() == props[i] && event->getEventType() == "") {
			switch(event->getEventCode()) {						
				case Event::CANCEL_EVENT:
					removeIndex = i;
				break;
				case Event::CHANGE_EVENT:
				break;				
			}
		}
	}
	
	
	PropSheet::handleEvent(event);
}


EntityPropSheet::EntityPropSheet() : PropSheet("CUSTOM PROPERTIES", "entityProps"){

	propHeight = 75;
	
	addButton = new UIButton("Add Property", 150);
	addButton->addEventListener(this, UIEvent::CLICK_EVENT);
	contents->addChild(addButton);
	addButton->setPosition(15, 35);
	
	customUndoHandler = true;
	
	entity = NULL;
	lastEntity = NULL;
	
	lastNumProps = 0;
	
	removeIndex = -1;
}

void EntityPropSheet::applyPropActionData(PolycodeEditorPropActionData *data) {
	if(!entity)
		return;
		
	entity->entityProps.clear();
	for(int i=0; i < data->entity->entityProps.size(); i++) {
			entity->entityProps.push_back(data->entity->entityProps[i]);
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
	propHeight = 0;
	
	for(int i=0; i < entity->entityProps.size(); i++) {			
		EntityProp prop = entity->entityProps[i];
		CustomProp *newProp = new CustomProp(prop.propName, prop.propValue);
		newProp->addEventListener(this, Event::CANCEL_EVENT);
		newProp->addEventListener(this, Event::CHANGE_EVENT);		
		addProp(newProp);
		propHeight += 30;
	}
	
	
	addButton->setPosition(15, propHeight);	
	propHeight += 70;	
	
	if(lastNumProps != entity->entityProps.size()) {
		dispatchEvent(new Event(), Event::COMPLETE_EVENT);
	}
	
	lastNumProps = entity->entityProps.size();
		
	Resize(getWidth(), getHeight());	
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

ShaderOptionsSheet::ShaderOptionsSheet() : PropSheet("SHADER OPTIONS", "shader_options"){
	shader = NULL;
	propHeight = 40;
    enabled = false;
}

ShaderOptionsSheet::~ShaderOptionsSheet() {

}

void ShaderOptionsSheet::handleEvent(Event *event) {

	if(event->getEventCode() == Event::CHANGE_EVENT) {
		for(int i=0 ; i < props.size(); i++) {
			if(event->getDispatcher() == props[i]) {
                
                LocalShaderParam *param = binding->getLocalParamByName(props[i]->label->getText());
                
				if(props[i]->propType == "Number") {
                    if(!param){
                        param = binding->addParam(ProgramParam::PARAM_NUMBER, props[i]->label->getText());
                    }
					(*(Number*)param->data) = ((NumberProp*)props[i])->get();
				} else if(props[i]->propType == "Color") {
                    
                    if(!param){
                        param = binding->addParam(ProgramParam::PARAM_COLOR, props[i]->label->getText());
                    }
                    
					(*(Color*)param->data) = ((ColorProp*)props[i])->get();
				
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
		if(!CoreServices::getInstance()->getRenderer()->getDataPointerForName(params[i].name)) {			
				switch (params[i].type) {
				
					case ProgramParam::PARAM_NUMBER:
					{
						String paramName = params[i].name;
						NumberProp *numberProp = new NumberProp(paramName);
						addProp(numberProp);
												
                        LocalShaderParam *param = binding->getLocalParamByName(params[i].name);
                        Number numberValue = 0.0;
                        if(param) {
                            numberValue = (*(Number*)param->data);
                        }
						numberProp->set(numberValue);
						propHeight += 30;
					}
					break;					
					case ProgramParam::PARAM_COLOR:
					{
						String paramName = params[i].name;

                        LocalShaderParam *param = binding->getLocalParamByName(params[i].name);

						ColorProp *colorProp = new ColorProp(paramName);
						addProp(colorProp);
						
						Color colorValue;
                        if(param) {
                            colorValue = (*(Color*)param->data);
                        }
						colorProp->set(colorValue);
						
						propHeight += 40;				
					}
					break;
				}	
			}
		}	
}

void ShaderOptionsSheet::setShader(Shader *shader, Material *material, ShaderBinding *binding) {
	clearShader();
	this->shader = shader;
	this->material = material;
	
    enabled = true;
    
	if(!shader || !material)
		return;
		
	this->binding = binding;
	
	setOptionsFromParams(shader->expectedParams);
	
	dispatchEvent(new Event(), Event::COMPLETE_EVENT);	
	Resize(getWidth(), getHeight());
}

ShaderTexturesSheet::ShaderTexturesSheet() : PropSheet("SHADER TEXTURES", "shader_textures"){
	shader = NULL;
	propHeight = 40;
    enabled = false;
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
		
		for(int i=0; i < cubemapProps.size(); i++) {
			if(event->getDispatcher() == cubemapProps[i]) {
				binding->clearCubemap(cubemapProps[i]->label->getText());
				Cubemap *cubemap = (Cubemap*)cubemapProps[i]->comboEntry->getSelectedItem()->data;
				binding->addCubemap(cubemapProps[i]->label->getText(), cubemap);
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
	cubemapProps.clear();
	textureProps.clear();
	
	propHeight = 30;
}

void ShaderTexturesSheet::setShader(Shader *shader, Material *material, ShaderBinding *binding) {
	clearShader();
	this->shader = shader;
	this->material = material;
	
    enabled = true;
    
	if(!shader || !material)
		return;
		
	this->binding = binding;

	for(int i=0; i < shader->expectedCubemaps.size(); i++) {
		ComboProp *comboProp = new ComboProp(shader->expectedCubemaps[i]);
		
		std::vector<Resource*> cubemaps = CoreServices::getInstance()->getResourceManager()->getResources(Resource::RESOURCE_CUBEMAP);
		
		for(int j=0; j < cubemaps.size(); j++) {
			comboProp->comboEntry->addComboItem(cubemaps[j]->getResourceName(), (void*) cubemaps[j]);
			if(material) {
				if(binding) {
					Cubemap *currentCubemap = binding->getCubemap(shader->expectedCubemaps[i]);
					if(currentCubemap) {
						if(currentCubemap->getResourceName() == cubemaps[j]->getResourceName()) {
							comboProp->set(j);
						}
					}
				}
			}
		}
				
		addProp(comboProp);
		cubemapProps.push_back(comboProp);
		propHeight += 45;
	}
	
	for(int i=0; i < shader->expectedTextures.size(); i++) {
		TextureProp *textureProp = new TextureProp(shader->expectedTextures[i]);
		
		if(material) {
			if(binding) {
				Texture *currentTexture = binding->getTexture(shader->expectedTextures[i]);
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
	Resize(getWidth(), getHeight());
}

TransformSheet::TransformSheet() : PropSheet("TRANSFORM", "entity_transform") {
    entity = NULL;
    
    positionProp = new Vector3Prop("Position");
    addProp(positionProp);
    
    scaleProp = new Vector3Prop("Scale");
    addProp(scaleProp);
    
    rotationProp = new Vector3Prop("Rotation");
    addProp(rotationProp);
    
    propHeight = 235;
    
    enabled = false;
}

TransformSheet::~TransformSheet() {

}


void TransformSheet::setEntity(Entity *entity) {
    this->entity = entity;
    if(entity) {
        enabled = true;
    } else {
        enabled = false;
    }
}

void TransformSheet::Update() {
    if(!entity) {
        return;
    }
    
    if(entity->getPosition() != lastPosition) {
        positionProp->set(entity->getPosition());
        lastPosition = entity->getPosition();
    }
    
    if(entity->getScale() != lastScale) {
        scaleProp->set(entity->getScale());
        lastScale = entity->getScale();
    }
    
    if(entity->getEulerRotation() != lastRotation) {
        rotationProp->set(entity->getEulerRotation() * TODEGREES);
        lastRotation = entity->getEulerRotation() * TODEGREES;
    }
}

void TransformSheet::handleEvent(Event *event) {
    if(event->getEventCode() == Event::CHANGE_EVENT) {
        if(event->getDispatcher() == positionProp) {
            lastPosition = positionProp->get();
            entity->setPosition(lastPosition);
        } else if(event->getDispatcher() == scaleProp) {
            lastScale = scaleProp->get();
            entity->setScale(lastScale);
        } else if(event->getDispatcher() == rotationProp) {
            lastRotation = rotationProp->get();
            entity->setRotationEuler(lastRotation);
        }
    }
    PropSheet::handleEvent(event);
}

ParticleEmitterSheet::ParticleEmitterSheet() : PropSheet("PARTICLE EMITTER", "particle_emitter") {
    emitter = NULL;

    typeProp = new ComboProp("Type");
    typeProp->comboEntry->addComboItem("Point");
    typeProp->comboEntry->addComboItem("Quad");
    addProp(typeProp);

    countProp = new NumberProp("Count");
    addProp(countProp);
    
    lifetimeProp = new NumberProp("Lifetime");
    addProp(lifetimeProp);

    particleSizeProp = new NumberProp("Size");
    addProp(particleSizeProp);
    
    worldParticlesProp = new BoolProp("World space");
    addProp(worldParticlesProp);
    
    loopingProp = new BoolProp("Loop");
    addProp(loopingProp);
    
    particleRotaionProp = new Vector3Prop("Rotation");
    addProp(particleRotaionProp);
    
    gravityProp = new Vector3Prop("Gravity");
    addProp(gravityProp);
    
    directionProp = new Vector3Prop("Direction");
    addProp(directionProp);

    deviationProp = new Vector3Prop("Deviation");
    addProp(deviationProp);

    sizeProp = new Vector3Prop("Emitter size");
    addProp(sizeProp);

    perlinProp = new BoolProp("Movement noise");
    addProp(perlinProp);
    
    perlinSizeProp = new Vector3Prop("Noise amount");
    addProp(perlinSizeProp);

    useColorCurvesProp = new BoolProp("Use color curves");
    addProp(useColorCurvesProp);
    
    colorCurveProp = new BezierRGBACurveProp("Color curves");
    addProp(colorCurveProp);

    useScaleCurvesProp = new BoolProp("Use scale curve");
    addProp(useScaleCurvesProp);
    
    scaleCurveProp = new BezierCurveProp("Scale curve", "Scale");
    addProp(scaleCurveProp);
    
    propHeight = 700;
    enabled = false;
    
}

ParticleEmitterSheet::~ParticleEmitterSheet() {
    
}

void ParticleEmitterSheet::handleEvent(Event *event) {
    if(!emitter) {
        return;
    }
    if(event->getEventCode() == Event::CHANGE_EVENT) {
        if(event->getDispatcher() == typeProp) {
            emitter->setParticleType(typeProp->get());
        } else if(event->getDispatcher() == countProp) {
                emitter->setParticleCount(countProp->get());
        } else if(event->getDispatcher() == lifetimeProp) {
            emitter->setParticleLifetime(lifetimeProp->get());
        } else if(event->getDispatcher() == particleSizeProp) {
            emitter->setParticleSize(particleSizeProp->get());
        } else if(event->getDispatcher() == worldParticlesProp) {
            emitter->setParticlesInWorldSpace(worldParticlesProp->get());
        } else if(event->getDispatcher() == loopingProp) {
            emitter->setLoopParticles(loopingProp->get());
        } else if(event->getDispatcher() == particleRotaionProp) {
            emitter->setParticleRotationSpeed(particleRotaionProp->get());
        } else if(event->getDispatcher() == gravityProp) {
            emitter->setGravity(gravityProp->get());
        } else if(event->getDispatcher() == directionProp) {
            emitter->setParticleDirection(directionProp->get());
        } else if(event->getDispatcher() == sizeProp) {
            emitter->setEmitterSize(sizeProp->get());
        } else if(event->getDispatcher() == deviationProp) {
            emitter->setDirectionDeviation(deviationProp->get());
        } else if(event->getDispatcher() == perlinProp) {
            emitter->setPerlinEnabled(perlinProp->get());
        } else if(event->getDispatcher() == perlinSizeProp) {
            emitter->setPerlinValue(perlinSizeProp->get());
        } else if(event->getDispatcher() == useColorCurvesProp) {
            emitter->useColorCurves = useColorCurvesProp->get();
        } else if(event->getDispatcher() == useScaleCurvesProp) {
            emitter->useScaleCurve = useScaleCurvesProp->get();
        }

    }
    
    PropSheet::handleEvent(event);
}

void ParticleEmitterSheet::setParticleEmitter(SceneParticleEmitter *emitter) {
    this->emitter = emitter;
    if(emitter) {
        enabled = true;
        typeProp->set(emitter->getParticleType());
        countProp->set(emitter->getParticleCount());
        lifetimeProp->set(emitter->getParticleLifetime());
        particleSizeProp->set(emitter->getParticleSize());
        worldParticlesProp->set(emitter->getParticlesInWorldSpace());
        loopingProp->set(emitter->getLoopParticles());
        particleRotaionProp->set(emitter->getParticleRotationSpeed());
        gravityProp->set(emitter->getGravity());
        directionProp->set(emitter->getParticleDirection());
        sizeProp->set(emitter->getEmitterSize());
        deviationProp->set(emitter->getDirectionDeviation());
        perlinProp->set(emitter->getPerlinEnabled());
        perlinSizeProp->set(emitter->getPerlinValue());
        useColorCurvesProp->set(emitter->useColorCurves);
        useScaleCurvesProp->set(emitter->useScaleCurve);
        
        colorCurveProp->curveR = &emitter->colorCurveR;
        colorCurveProp->curveG = &emitter->colorCurveG;
        colorCurveProp->curveB = &emitter->colorCurveB;
        colorCurveProp->curveA = &emitter->colorCurveA;
        
        scaleCurveProp->curve = &emitter->scaleCurve;
        
    } else {
        enabled = false;
    }
}

SceneLightSheet::SceneLightSheet() : PropSheet("LIGHT", "scene_light") {
    typeProp = new ComboProp("Type");
    typeProp->comboEntry->addComboItem("Area");
    typeProp->comboEntry->addComboItem("Spot");
    addProp(typeProp);
    
    lightColorProp = new ColorProp("Light color");
    addProp(lightColorProp);
    
    specularColorProp = new ColorProp("Specular color");
    addProp(specularColorProp);
    
    intensityProp = new NumberProp("Intensity");
    addProp(intensityProp);
    
    constantAttenuationProp = new SliderProp("Constant att.", 0.0, 1.0);
    addProp(constantAttenuationProp);
    
    linearAttenuationProp = new SliderProp("Linear att.", 0.0, 1.0);
    addProp(linearAttenuationProp);
    
    quadraticAttenuationProp = new SliderProp("Quadratic att.", 0.0, 1.0);
    addProp(quadraticAttenuationProp);
    
    spotlightCutoffProp = new NumberProp("Spot cutoff");
    addProp(spotlightCutoffProp);
    
    spotlightExponentProp = new SliderProp("Spot exponent", 0.0, 50.0);
    addProp(spotlightExponentProp);
    
    castShadowsProp = new BoolProp("Cast shadows");
    addProp(castShadowsProp);
    
    shadowMapFOVProp = new SliderProp("Shadow FOV", 1.0, 180.0);
    addProp(shadowMapFOVProp);
    
    shadowResolutionProp = new NumberProp("Shadowmap res.");
    addProp(shadowResolutionProp);

    propHeight = 365;
    light = NULL;
    enabled = false;
}

SceneLightSheet::~SceneLightSheet() {
    
}

void SceneLightSheet::setSceneLight(SceneLight *light) {
    this->light = light;
    
    if(light) {
        light->enableDebugDraw(true);
        typeProp->set(light->getLightType());
        lightColorProp->set(light->lightColor);
        specularColorProp->set(light->specularLightColor);
        intensityProp->set(light->getIntensity());
        constantAttenuationProp->set(light->getConstantAttenuation());
        linearAttenuationProp->set(light->getLinearAttenuation());
        quadraticAttenuationProp->set(light->getQuadraticAttenuation());
        
        spotlightCutoffProp->set(light->getSpotlightCutoff());
        spotlightExponentProp->set(light->getSpotlightExponent());
        
        castShadowsProp->set(light->areShadowsEnabled());
        shadowMapFOVProp->set(light->getShadowMapFOV());
        shadowResolutionProp->set(light->getShadowMapResolution());
        
        enabled = true;
    } else {
        enabled = false;
    }
}

void SceneLightSheet::handleEvent(Event *event) {
    if(!light) {
        return;
    }
    
    if(event->getEventCode() == Event::CHANGE_EVENT) {
        if(event->getDispatcher() == typeProp) {
            light->setLightType(typeProp->get());
        } else if(event->getDispatcher() == lightColorProp) {
            light->lightColor = lightColorProp->get();
        } else if(event->getDispatcher() == specularColorProp) {
            light->specularLightColor = specularColorProp->get();
        } else if(event->getDispatcher() == intensityProp) {
            light->setIntensity(intensityProp->get());
        } else if(event->getDispatcher() == constantAttenuationProp) {
            light->setAttenuation(constantAttenuationProp->get(), light->getLinearAttenuation(), light->getQuadraticAttenuation());
        } else if(event->getDispatcher() == linearAttenuationProp) {
            light->setAttenuation(light->getConstantAttenuation(), linearAttenuationProp->get(), light->getQuadraticAttenuation());
        } else if(event->getDispatcher() == quadraticAttenuationProp) {
            light->setAttenuation(light->getConstantAttenuation(), light->getLinearAttenuation(), quadraticAttenuationProp->get());
        } else if(event->getDispatcher() == castShadowsProp) {
            light->enableShadows(castShadowsProp->get(), shadowResolutionProp->get());
        } else if(event->getDispatcher() == shadowMapFOVProp) {
            light->setShadowMapFOV(shadowMapFOVProp->get());
        } else if(event->getDispatcher() == shadowResolutionProp) {
            light->enableShadows(castShadowsProp->get(), shadowResolutionProp->get());
        } else if(event->getDispatcher() == spotlightCutoffProp) {
            light->setSpotlightProperties(spotlightCutoffProp->get(), light->getSpotlightExponent());
        } else if(event->getDispatcher() == spotlightExponentProp) {
            light->setSpotlightProperties(light->getSpotlightCutoff(), spotlightExponentProp->get());
        }

    }
    PropSheet::handleEvent(event);
}
/*
SceneMeshSheet::SceneMeshSheet() : PropSheet("MESH FILE", "scene_mesh_file") {
    enabled = false;
    sceneMesh = NULL;
}

SceneMeshSheet::~SceneMeshSheet() {
        
}

void SceneMeshSheet::setSceneMesh(SceneMesh *mesh) {
    
}

void SceneMeshSheet::handleEvent(Event *event) {
    
}
*/

ScenePrimitiveSheet::ScenePrimitiveSheet() : PropSheet("PRIMITIVE", "scene_primitive") {
    typeProp = new ComboProp("Type");
    typeProp->comboEntry->addComboItem("Box");
    typeProp->comboEntry->addComboItem("Plane");
    typeProp->comboEntry->addComboItem("Vert. Plane");
    typeProp->comboEntry->addComboItem("Cylinder");
    typeProp->comboEntry->addComboItem("Uncapped Cylinder");
    typeProp->comboEntry->addComboItem("Sphere");
    typeProp->comboEntry->addComboItem("Torus");
    typeProp->comboEntry->addComboItem("Cone");
    typeProp->comboEntry->addComboItem("Circle");
    
    addProp(typeProp);
    
    option1Prop = new NumberProp("");
    addProp(option1Prop);
    
    option2Prop = new NumberProp("");
    addProp(option2Prop);
    
    option3Prop = new NumberProp("");
    addProp(option3Prop);
    
    option4Prop = new NumberProp("");
    addProp(option4Prop);

    option5Prop = new NumberProp("");
    addProp(option5Prop);

    propHeight = 240;
    
    enabled = false;
    primitive = NULL;
}

void ScenePrimitiveSheet::updatePrimitiveLabels() {
    if(!primitive) {
        return;
    }

    option1Prop->enabled = false;
    option1Prop->visible = false;
    option2Prop->enabled = false;
    option2Prop->visible = false;
    option3Prop->enabled = false;
    option3Prop->visible = false;
    option4Prop->enabled = false;
    option4Prop->visible = false;
    option5Prop->enabled = false;
    option5Prop->visible = false;
    

    switch(primitive->getPrimitiveType()) {
        case ScenePrimitive::TYPE_BOX:
            option1Prop->setPropName("Width");
            option2Prop->setPropName("Height");
            option3Prop->setPropName("Depth");
            
            option1Prop->enabled = true;
            option1Prop->visible = true;
            option2Prop->enabled = true;
            option2Prop->visible = true;
            option3Prop->enabled = true;
            option3Prop->visible = true;
            
            propHeight = 45 + (32 * 3);
        break;
        case ScenePrimitive::TYPE_PLANE:
            option1Prop->setPropName("Width");
            option2Prop->setPropName("Height");
            
            option1Prop->enabled = true;
            option1Prop->visible = true;
            option2Prop->enabled = true;
            option2Prop->visible = true;
            
            propHeight = 45 + (32 * 2);
        break;
        case ScenePrimitive::TYPE_VPLANE:
            option1Prop->setPropName("Width");
            option2Prop->setPropName("Height");
            
            option1Prop->enabled = true;
            option1Prop->visible = true;
            option2Prop->enabled = true;
            option2Prop->visible = true;
            
            propHeight = 45 + (32 * 2);
        break;
        case ScenePrimitive::TYPE_CYLINDER:
            option1Prop->setPropName("Length");
            option2Prop->setPropName("Radius");
            option3Prop->setPropName("Segments");
            
            option1Prop->enabled = true;
            option1Prop->visible = true;
            option2Prop->enabled = true;
            option2Prop->visible = true;
            option3Prop->enabled = true;
            option3Prop->visible = true;
            
            propHeight = 45 + (32 * 3);
        break;
        case ScenePrimitive::TYPE_UNCAPPED_CYLINDER:
            option1Prop->setPropName("Length");
            option2Prop->setPropName("Radius");
            option3Prop->setPropName("Segments");
            
            option1Prop->enabled = true;
            option1Prop->visible = true;
            option2Prop->enabled = true;
            option2Prop->visible = true;
            option3Prop->enabled = true;
            option3Prop->visible = true;
            
            propHeight = 45 + (32 * 3);
        break;
        case ScenePrimitive::TYPE_SPHERE:
            option1Prop->setPropName("Radius");
            option2Prop->setPropName("Lat. segments");
            option3Prop->setPropName("Long. segments");
            
            option1Prop->enabled = true;
            option1Prop->visible = true;
            option2Prop->enabled = true;
            option2Prop->visible = true;
            option3Prop->enabled = true;
            option3Prop->visible = true;
            
            propHeight = 45 + (32 * 3);
        break;
        case ScenePrimitive::TYPE_TORUS:
            option1Prop->setPropName("Torus radius");
            option2Prop->setPropName("Pipe radius");
            option3Prop->setPropName("Ring segments");
            option4Prop->setPropName("Pipe segments");
            
            option1Prop->enabled = true;
            option1Prop->visible = true;
            option2Prop->enabled = true;
            option2Prop->visible = true;
            option3Prop->enabled = true;
            option3Prop->visible = true;
            option4Prop->enabled = true;
            option4Prop->visible = true;
            
            propHeight = 45 + (32 * 4);
        break;
        case ScenePrimitive::TYPE_CONE:
            option1Prop->setPropName("Length");
            option2Prop->setPropName("Radius");
            option3Prop->setPropName("Segments");
            
            option1Prop->enabled = true;
            option1Prop->visible = true;
            option2Prop->enabled = true;
            option2Prop->visible = true;
            option3Prop->enabled = true;
            option3Prop->visible = true;
            
            propHeight = 45 + (32 * 3);
        break;
        case ScenePrimitive::TYPE_CIRCLE:
            option1Prop->setPropName("Width");
            option2Prop->setPropName("Height");
            option3Prop->setPropName("Segments");
            
            option1Prop->enabled = true;
            option1Prop->visible = true;
            option2Prop->enabled = true;
            option2Prop->visible = true;
            option3Prop->enabled = true;
            option3Prop->visible = true;
            
            propHeight = 45 + (32 * 3);
        break;
    }
    dispatchEvent(new Event(), Event::COMPLETE_EVENT);
}

ScenePrimitiveSheet::~ScenePrimitiveSheet() {
    
}

void ScenePrimitiveSheet::setScenePrimitive(ScenePrimitive *primitive) {
    this->primitive = primitive;
    if(primitive) {
        typeProp->set(primitive->getPrimitiveType());
        option1Prop->set(primitive->getPrimitiveParameter1());
        option2Prop->set(primitive->getPrimitiveParameter2());
        option3Prop->set(primitive->getPrimitiveParameter3());
        option4Prop->set(primitive->getPrimitiveParameter4());
        option5Prop->set(primitive->getPrimitiveParameter5());
        updatePrimitiveLabels();
        enabled = true;
    } else {
        enabled = false;
    }
}

void ScenePrimitiveSheet::handleEvent(Event *event) {
    
    if(!primitive) {
        return;
    }
    
    if(event->getEventCode() == Event::CHANGE_EVENT) {
        primitive->setPrimitiveOptions(typeProp->get(), option1Prop->get(), option2Prop->get(), option3Prop->get(), option4Prop->get(), option5Prop->get());
        if(event->getDispatcher() == typeProp) {
            updatePrimitiveLabels();
        }
    }
    
    PropSheet::handleEvent(event);
}

MaterialPropSheet::MaterialPropSheet() : PropSheet("MATERIAL", "material") {
    materialProp = new ComboProp("Material");
    addProp(materialProp);
    
    propHeight = 70;
    enabled = false;
}

MaterialPropSheet::~MaterialPropSheet() {
    
}

void MaterialPropSheet::setSceneMesh(SceneMesh *sceneMesh) {
    this->sceneMesh = sceneMesh;
    
    if(sceneMesh) {
        enabled = true;
        reloadMaterials();        
    } else {
        enabled = false;
    }
}

void MaterialPropSheet::reloadMaterials() {

	Resource *selectedMaterial = NULL;
    
    selectedMaterial = NULL;
    if(sceneMesh) {
        selectedMaterial = (Resource*)sceneMesh->getMaterial();
    }
		
	materialProp->comboEntry->clearItems();
	std::vector<Resource*> materials = CoreServices::getInstance()->getResourceManager()->getResources(Resource::RESOURCE_MATERIAL);
	for(int i=0; i < materials.size(); i++) {
        if(((Material*)materials[i])->screenMaterial) {
            continue;
        }
		materialProp->comboEntry->addComboItem(materials[i]->getResourceName(), (void*) materials[i]);
		if(selectedMaterial == materials[i]) {
			materialProp->comboEntry->setSelectedIndex(i);
		}
	}
}

void MaterialPropSheet::handleEvent(Event *event) {
    if(!sceneMesh) {
        PropSheet::handleEvent(event);
        return;
    }
        
    if(event->getDispatcher() == materialProp  && event->getEventCode() == Event::CHANGE_EVENT) {
        Material *newMaterial = (Material*)materialProp->comboEntry->getSelectedItem()->data;
        if(sceneMesh->getMaterial() != newMaterial) {
            sceneMesh->setMaterial(newMaterial);
        }
    }
    PropSheet::handleEvent(event);
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

    blendingProp->comboEntry->addComboItem("None");
	blendingProp->comboEntry->addComboItem("Normal");
	blendingProp->comboEntry->addComboItem("Lighten");
	blendingProp->comboEntry->addComboItem("Color");
	blendingProp->comboEntry->addComboItem("Premultiplied");
	blendingProp->comboEntry->addComboItem("Multiply");
	
	propHeight = 160;
	
	entity = NULL;
    enabled = false;
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


void EntitySheet::setEntity(Entity *entity) {
    this->entity = entity;
    if(entity) {
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
        
        enabled = true;
    } else {
        enabled = false;
    }
}

CameraSheet::CameraSheet() : PropSheet("CAMERA", "camera") {
    enabled = false;
    camera = NULL;
    
    
    exposureProp = new NumberProp("Exposure");
    addProp(exposureProp);

    orthoProp = new BoolProp("Orthographic");
    addProp(orthoProp);

    fovProp = new NumberProp("FOV");
    addProp(fovProp);

    orthoWidthProp = new NumberProp("Ortho width");
    addProp(orthoWidthProp);

    orthoHeightProp = new NumberProp("Ortho height");
    addProp(orthoHeightProp);

    nearClipPlane = new NumberProp("Near clip");
    addProp(nearClipPlane);

    farClipPlane = new NumberProp("Far clip");
    addProp(farClipPlane);

    
    propHeight = 220;
}

CameraSheet::~CameraSheet() {
    
}

void CameraSheet::handleEvent(Event *event) {
    if(!camera) {
        return;
    }
    
    if(event->getDispatcher() == fovProp) {
        camera->setFOV(fovProp->get());
        dispatchEvent(new Event(), Event::CHANGE_EVENT);
    } else if(event->getDispatcher() == exposureProp) {
        camera->setExposureLevel(exposureProp->get());
        dispatchEvent(new Event(), Event::CHANGE_EVENT);
    } else if(event->getDispatcher() == orthoProp) {
        camera->setOrthoMode(orthoProp->get());
        dispatchEvent(new Event(), Event::CHANGE_EVENT);
    } else if(event->getDispatcher() == orthoWidthProp) {
        camera->setOrthoSize(orthoWidthProp->get(), camera->getOrthoSizeY());
        dispatchEvent(new Event(), Event::CHANGE_EVENT);
    } else if(event->getDispatcher() == orthoHeightProp) {
        camera->setOrthoSize(camera->getOrthoSizeX(), orthoHeightProp->get());
        dispatchEvent(new Event(), Event::CHANGE_EVENT);
    } else if(event->getDispatcher() == nearClipPlane) {
        camera->setClippingPlanes(nearClipPlane->get(), camera->getFarClipppingPlane());
        dispatchEvent(new Event(), Event::CHANGE_EVENT);
    } else if(event->getDispatcher() == farClipPlane) {
        camera->setClippingPlanes(camera->getNearClipppingPlane(),farClipPlane->get());
        dispatchEvent(new Event(), Event::CHANGE_EVENT);
    }


    
    PropSheet::handleEvent(event);
}

void CameraSheet::setCamera(Camera *camera) {
    this->camera = camera;
    if(camera) {
        enabled = true;
        
        exposureProp->set(camera->getExposureLevel());
        orthoProp->set(camera->getOrthoMode());
        orthoWidthProp->set(camera->getOrthoSizeX());
        orthoHeightProp->set(camera->getOrthoSizeY());
        nearClipPlane->set(camera->getNearClipppingPlane());
        farClipPlane->set(camera->getFarClipppingPlane());
        
        fovProp->set(camera->getFOV());
    } else {
        enabled = false;
    }
}


SceneSpriteSheet::SceneSpriteSheet() : PropSheet("SPRITE", "SceneSprite") {
	sprite = NULL;
    enabled = false;
	
	spriteProp = new SceneSpriteProp("Sprite");
	spriteProp->addEventListener(this, Event::CHANGE_EVENT);
	addProp(spriteProp);	
	
	defaultAnimationProp = new ComboProp("Animation");
	defaultAnimationProp->addEventListener(this, Event::CHANGE_EVENT);
	addProp(defaultAnimationProp);
    
    spriteWidthProp = new NumberProp("Width");
	spriteWidthProp->addEventListener(this, Event::CHANGE_EVENT);
	addProp(spriteWidthProp);

    spriteHeightProp = new NumberProp("Height");
	spriteHeightProp->addEventListener(this, Event::CHANGE_EVENT);
	addProp(spriteHeightProp);

	propHeight = 190;
}

SceneSpriteSheet::~SceneSpriteSheet() {

}
		
void SceneSpriteSheet::handleEvent(Event *event) {
	if(!sprite)
		return;

	if(event->getDispatcher() == sprite->getResourceEntry()) {
		spriteProp->previewSprite->reloadSprite();
		sprite->getResourceEntry()->removeAllHandlersForListener(this);
	}

    if(event->getDispatcher() == spriteWidthProp) {
        sprite->setActualSpriteSize(spriteWidthProp->get(), sprite->getActualSpriteSize().y);
        dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}

    if(event->getDispatcher() == spriteHeightProp) {
        sprite->setActualSpriteSize(sprite->getActualSpriteSize().x, spriteHeightProp->get());
        dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}
 
    
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

void SceneSpriteSheet::setSprite(SceneSprite *sprite) {
    this->sprite = sprite;
    
	if(sprite) {
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

		enabled = true;	
		spriteProp->set(sprite->getFileName());
		sprite->getResourceEntry()->addEventListener(this, Event::RESOURCE_RELOAD_EVENT);
        
        spriteWidthProp->set(sprite->getActualSpriteSize().x);
        spriteHeightProp->set(sprite->getActualSpriteSize().y);
	} else {
		enabled = false;
	}
}

SceneEntityInstanceSheet::SceneEntityInstanceSheet() : PropSheet("ENTITY INSTANCE", "SceneEntityInstance") {
	instance = NULL;
	
	instanceProp = new SceneEntityInstanceProp("Entity file");
	instanceProp->addEventListener(this, Event::CHANGE_EVENT);
	addProp(instanceProp);
	
	propHeight = 100;
}

SceneEntityInstanceSheet::~SceneEntityInstanceSheet() {

}
		
void SceneEntityInstanceSheet::handleEvent(Event *event) {
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

void SceneEntityInstanceSheet::Update() {
	if(instance) {
		enabled = true;	
		instanceProp->set(instance->getFileName());
	} else {
		enabled = false;
	}
}

SceneLabelSheet::SceneLabelSheet() : PropSheet("LABEL", "UILabel") {
	label = NULL;
    enabled = false;
	
	caption = new StringProp("Contents");
	caption->addEventListener(this, Event::CHANGE_EVENT);
	addProp(caption);

	size = new NumberProp("Size (px)");
	size->addEventListener(this, Event::CHANGE_EVENT);
	addProp(size);	

    actualHeight = new NumberProp("Actual height");
	actualHeight->addEventListener(this, Event::CHANGE_EVENT);
	addProp(actualHeight);

	font = new ComboProp("Font");
	font->addEventListener(this, Event::CHANGE_EVENT);
	addProp(font);	
	
	
	enableAA = new BoolProp("Antialias");
	enableAA->addEventListener(this, Event::CHANGE_EVENT);
	addProp(enableAA);	
	
	propHeight = 160;
	
	refreshFonts();
}

void SceneLabelSheet::refreshFonts() {
	
	FontManager *fontManager = CoreServices::getInstance()->getFontManager();
	
	font->comboEntry->clearItems();
	
	for(int i=0; i < fontManager->getNumFonts(); i++) {
		FontEntry *entry = fontManager->getFontEntryByIndex(i);
		if(entry->fontName != "section") {
			font->comboEntry->addComboItem(entry->fontName);
		}
	}

}

void SceneLabelSheet::setSceneLabel(SceneLabel *label) {
    this->label = label;
    
	if(label) {
		enabled = true;
        caption->set(label->getText());
        enableAA->set(label->getLabel()->getAntialiasMode() == Label::ANTIALIAS_FULL);
        size->set(label->getLabel()->getSize());
        actualHeight->set(label->getLabelActualHeight());
        
        refreshFonts();
        
        for(int i=0; i < font->comboEntry->getNumItems(); i++) {
            String comboFont = font->comboEntry->getItemAtIndex(i)->label;
            
            if(comboFont == label->getLabel()->getFont()->getFontName()) {
                font->set(i);
            }
        }
        
	} else {
		enabled = false;
	}
}

SceneLabelSheet::~SceneLabelSheet() {

}

void SceneLabelSheet::handleEvent(Event *event) {
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
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}


	if(event->getDispatcher() == size) {
		int newSize= size->get();
		if(newSize < 4)
			newSize = 4;
					
		label->getLabel()->setSize(newSize);
		label->setText(caption->get());		
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}

    if(event->getDispatcher() == actualHeight) {
		label->setLabelActualHeight(actualHeight->get());
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

SoundSheet::SoundSheet() : PropSheet("SOUND", "sound") {
	sound = NULL;
    enabled = false;
	
	soundProp = new SoundProp("Sound file");
	soundProp->addEventListener(this, Event::CHANGE_EVENT);
	addProp(soundProp);
	
	referenceDistance = new NumberProp("Reference dist");
	referenceDistance->addEventListener(this, Event::CHANGE_EVENT);
	addProp(referenceDistance);

	maxDistance = new NumberProp("Max dist");
	maxDistance->addEventListener(this, Event::CHANGE_EVENT);
	addProp(maxDistance);

	volume = new SliderProp("Volume", 0.0, 1.0);
	volume->addEventListener(this, Event::CHANGE_EVENT);
	addProp(volume);
	
	pitch = new SliderProp("Pitch", 0.0, 2.0);
	pitch->addEventListener(this, Event::CHANGE_EVENT);
	addProp(pitch);
		
	propHeight = 210;
}

SoundSheet::~SoundSheet() {

}
		
void SoundSheet::handleEvent(Event *event) {
	if(!sound)
		return;

	if(event->getDispatcher() == referenceDistance  && event->getEventCode() == Event::CHANGE_EVENT) {
		sound->getSound()->setReferenceDistance(referenceDistance->get());
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}

	if(event->getDispatcher() == maxDistance  && event->getEventCode() == Event::CHANGE_EVENT) {
		sound->getSound()->setMaxDistance(maxDistance->get());
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}

	if(event->getDispatcher() == volume  && event->getEventCode() == Event::CHANGE_EVENT) {
		sound->getSound()->setVolume(volume->get());
	}

	if(event->getDispatcher() == pitch  && event->getEventCode() == Event::CHANGE_EVENT) {
		sound->getSound()->setPitch(pitch->get());
        soundProp->previewSound->setPitch(pitch->get());
	}

	if(event->getDispatcher() == soundProp  && event->getEventCode() == Event::CHANGE_EVENT) {
		sound->getSound()->loadFile(soundProp->get(), false);
	}


	PropSheet::handleEvent(event);
}

void SoundSheet::setSound(SceneSound *sound) {
    this->sound = sound;

	if(sound) {
		enabled = true;	

        soundProp->set(sound->getSound()->getFileName());
        referenceDistance->set(sound->getSound()->getReferenceDistance());
        maxDistance->set(sound->getSound()->getMaxDistance());
        volume->set(sound->getSound()->getVolume());
        pitch->set(sound->getSound()->getPitch());
        soundProp->previewSound->setPitch(sound->getSound()->getPitch());

	} else {
		enabled = false;
	}
}
