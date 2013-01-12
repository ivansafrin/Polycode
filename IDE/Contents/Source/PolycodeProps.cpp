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

PropList::PropList(String caption) : UIElement() {

	setPositionMode(ScreenEntity::POSITION_TOPLEFT);

	bg = new ScreenShape(ScreenShape::SHAPE_RECT, 10,10);
	bg->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	bg->setColor(0.18, 0.18, 0.18, 1.0);
	addChild(bg);
	bg->blockMouseInput = true;
	bg->processInputEvents = true;
	
	blockMouseInput = true;

	bg2 = new ScreenShape(ScreenShape::SHAPE_RECT, 10,10);
	bg2->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	bg2->setColor(0.1, 0.1, 0.1, 1.0);
	addChild(bg2);

	ScreenLabel *label = new ScreenLabel(caption, 22, "section", Label::ANTIALIAS_FULL);
	label->color.a = 0.4;
	addChild(label);
	label->setPosition(10, 0);

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
	}	
}

void PropList::addPropSheet(PropSheet *sheet) {
	propContents->addChild(sheet);
	props.push_back(sheet);
	Resize(width, height);
	sheet->addEventListener(this, Event::COMPLETE_EVENT);
}

PropSheet::PropSheet(String caption, String type) : UIElement() {
	this->caption = caption;
	this->type = type;
	
	bg = new ScreenShape(ScreenShape::SHAPE_RECT, 30,30);
	addChild(bg);
	bg->setColor(0.14, 0.14, 0.14, 1.0);
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
	Resize(width, height);
}

PropProp::PropProp(String caption) : UIElement() {
	label = new ScreenLabel(caption, 11);
	label->color.a = 0.4;
	label->setPosition(0, 5);
	addChild(label);
	
	propContents = new ScreenEntity();
	propContents->processInputEvents = true;
	addChild(propContents);
	propContents->setPosition(90, 0);
	
	setHeight(20);
}

PropProp::~PropProp() {

}

Vector2Prop::Vector2Prop(String caption) : PropProp(caption) {

	ScreenLabel *label = new ScreenLabel("X:", 11);
	label->color.a = 0.4;
	propContents->addChild(label);
	label->setPosition(-20, 6);	

	label = new ScreenLabel("Y:", 11);
	label->color.a = 0.4;
	propContents->addChild(label);
	label->setPosition(60, 6);	

	positionX = new UITextInput(false, 50, 10);
	positionX->addEventListener(this, UIEvent::CHANGE_EVENT);
	positionX->setText("0");
	positionX->setNumberOnly(true);
	propContents->addChild(positionX);
	positionX->setPosition(0, 0);

	positionY = new UITextInput(false, 50, 10);
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
			dispatchEvent(new Event(), Event::CHANGE_EVENT);
		}
	}
}

void Vector2Prop::set(Vector2 position) {
	positionX->setText(String::NumberToString(position.x));
	positionY->setText(String::NumberToString(position.y));
}

Vector2 Vector2Prop::get() {
	return Vector2(atof(positionX->getText().c_str()), atof(positionY->getText().c_str()));
}

Vector2Prop::~Vector2Prop() {

}

StringProp::StringProp(String caption) : PropProp(caption) {

	stringEntry = new UITextInput(false, 150, 10);
	stringEntry->addEventListener(this, UIEvent::CHANGE_EVENT);
	stringEntry->setText("");
	propContents->addChild(stringEntry);
	stringEntry->setPosition(0, 0);
	setHeight(30);

}

void StringProp::handleEvent(Event *event) {
	if(event->getDispatcher() == stringEntry) {
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CHANGE_EVENT) {		
			dispatchEvent(new Event(), Event::CHANGE_EVENT);
		}
	}
}

void StringProp::set(String str) {
	stringEntry->setText(str);
}

String StringProp::get() {
	return stringEntry->getText();
}
	
		
StringProp::~StringProp() {

}

SliderProp::SliderProp(String caption, Number min, Number max) : PropProp(caption) {

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
			dispatchEvent(new Event(), Event::CHANGE_EVENT);
			valueLabel->setText(String::NumberToString(slider->getSliderValue()));
		}
	}
}

void SliderProp::set(Number number) {
	slider->setSliderValue(number);
	valueLabel->setText(String::NumberToString(slider->getSliderValue()));	
}

Number SliderProp::get() {
	return slider->getSliderValue();
}
	
		
SliderProp::~SliderProp() {

}

NumberProp::NumberProp(String caption) : PropProp(caption) {

	numberEntry = new UITextInput(false, 50, 10);
	numberEntry->addEventListener(this, UIEvent::CHANGE_EVENT);
	numberEntry->setText("0");
	numberEntry->setNumberOnly(true);
	propContents->addChild(numberEntry);
	numberEntry->setPosition(0, 0);

	setHeight(30);

}

void NumberProp::handleEvent(Event *event) {
	if(event->getDispatcher() == numberEntry) {
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CHANGE_EVENT) {		
			dispatchEvent(new Event(), Event::CHANGE_EVENT);
		}
	}
}

void NumberProp::set(Number number) {
	numberEntry->setText(String::NumberToString(number));
}

Number NumberProp::get() {
	return atof(numberEntry->getText().c_str());
}
	
		
NumberProp::~NumberProp() {

}

ColorProp::ColorProp(String caption) : PropProp(caption) {

	colorEntry = new UIColorBox(globalColorPicker, Color(), 45, 25);
	colorEntry->addEventListener(this, UIEvent::CHANGE_EVENT);
	colorEntry->setPosition(0, -2);
	propContents->addChild(colorEntry);
	setHeight(30);

}

void ColorProp::handleEvent(Event *event) {
	if(event->getDispatcher() == colorEntry) {
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CHANGE_EVENT) {		
			dispatchEvent(new Event(), Event::CHANGE_EVENT);
		}
	}
}

void ColorProp::set(Color color) {
	colorEntry->setBoxColor(color);
}

Color ColorProp::get() {
	return colorEntry->getSelectedColor();
}
	
		
ColorProp::~ColorProp() {

}

ComboProp::ComboProp(String caption) : PropProp(caption) {

	comboEntry = new UIComboBox(globalMenu, 150);
	comboEntry->addEventListener(this, UIEvent::CHANGE_EVENT);
	propContents->addChild(comboEntry);
	comboEntry->setPosition(-3, 0);
	setHeight(30);

}

void ComboProp::handleEvent(Event *event) {
	if(event->getDispatcher() == comboEntry) {
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CHANGE_EVENT) {		
			dispatchEvent(new Event(), Event::CHANGE_EVENT);
		}
	}
}

void ComboProp::set(unsigned int index) {
	comboEntry->setSelectedIndex(index);
}

unsigned int ComboProp::get() {
	return comboEntry->getSelectedIndex();
}
	
		
ComboProp::~ComboProp() {

}

BoolProp::BoolProp(String caption) : PropProp(caption) {

	checkEntry = new UICheckBox("", false);
	checkEntry->addEventListener(this, UIEvent::CHANGE_EVENT);
	checkEntry->setPosition(0, 2);
	propContents->addChild(checkEntry);
	setHeight(30);

}

void BoolProp::handleEvent(Event *event) {
	if(event->getDispatcher() == checkEntry) {
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CHANGE_EVENT) {		
			dispatchEvent(new Event(), Event::CHANGE_EVENT);
		}
	}
}

void BoolProp::set(bool val) {
	checkEntry->setChecked(val);
}

bool BoolProp::get() {
	return checkEntry->isChecked();
}
	
		
BoolProp::~BoolProp() {

}


SoundProp::SoundProp(String caption) : PropProp(caption){

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

void SoundProp::set(String soundPath) {
	if(previewSound) {
		delete previewSound;
	}	
	previewSound = new Sound(soundPath);	
	soundFile->setText(soundPath);
}

String SoundProp::get() {
	if(previewSound) {
		return previewSound->getFileName();
	}
	return "";
}

BezierRGBACurveProp::BezierRGBACurveProp(String caption) : PropProp(caption) {


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

BezierCurveProp::BezierCurveProp(String caption, String curveName) : PropProp(caption) {

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

TextureProp::TextureProp(String caption) : PropProp(caption){
	previewShape = new ScreenShape(ScreenShape::SHAPE_RECT, 48, 48);
	previewShape->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	previewShape->setPosition(2, 1);
	propContents->addChild(previewShape);

	changeButton = new UIButton("Change", 80);
	propContents->addChild(changeButton);
	changeButton->setPosition(60, 5);
	changeButton->addEventListener(this, UIEvent::CLICK_EVENT);
	setHeight(60);
}

TextureProp::~TextureProp() {

}


void TextureProp::handleEvent(Event *event) {

	if(event->getDispatcher() == globalFrame->assetBrowser && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::OK_EVENT) {
		String texturePath = globalFrame->assetBrowser->getSelectedAssetPath();
		
		previewShape->loadTexture(texturePath);
		
		globalFrame->assetBrowser->removeAllHandlersForListener(this);
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
		
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
}

Texture* TextureProp::get() {
	return previewShape->getTexture();
}
ScreenSpriteProp::ScreenSpriteProp(String caption) : PropProp(caption){

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
		
		if(previewSprite) {
			propContents->removeChild(previewSprite);
			delete previewSprite;
		}
		
		previewSprite = new ScreenSprite(filePath);
		previewSprite->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
		previewSprite->setPosition(2, 1);
		previewSprite->setShapeSize(48,48);		
		propContents->addChild(previewSprite);	
		
		globalFrame->assetBrowser->removeAllHandlersForListener(this);
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
		
		globalFrame->hideModal();
	}

	if(event->getDispatcher() == changeButton && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {
		globalFrame->assetBrowser->addEventListener(this, UIEvent::OK_EVENT);
		
		std::vector<String> extensions;
		extensions.push_back("sprite");
		globalFrame->showAssetBrowser(extensions);
	}
}

void ScreenSpriteProp::set(String fileName) {

	if(fileName != previewSprite->getFileName()) {
		printf("%s != %s\n", fileName.c_str(), previewSprite->getFileName().c_str());
		if(previewSprite) {
			propContents->removeChild(previewSprite);
			delete previewSprite;
		}
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

ScreenEntityInstanceProp::ScreenEntityInstanceProp(String caption) : PropProp(caption){
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
		
		propContents->removeChild(previewInstance);
		delete previewInstance;
		previewInstance = new ScreenEntityInstance(filePath);
		previewInstance->setPosition(24, 24);
		
		Number radius = previewInstance->getCompoundBBoxRadius();
		previewInstance->setScale(48.0/(radius*2.0), 48.0/(radius*2.0));
		
		propContents->addChild(previewInstance);
		
		globalFrame->assetBrowser->removeAllHandlersForListener(this);
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
		
		globalFrame->hideModal();
	}

	if(event->getDispatcher() == changeButton && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {
		globalFrame->assetBrowser->addEventListener(this, UIEvent::OK_EVENT);
		
		std::vector<String> extensions;
		extensions.push_back("entity2d");
		globalFrame->showAssetBrowser(extensions);
	}
}

void ScreenEntityInstanceProp::set(String fileName) {

	if(fileName != previewInstance->getFileName()) {
		propContents->removeChild(previewInstance);
		delete previewInstance;
		previewInstance = new ScreenEntityInstance(fileName);
		previewInstance->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
		previewInstance->setPosition(2, 1);
		
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
		}
		
		if(lastStrokeVal != shape->strokeEnabled) {
			strokeProp->set(shape->strokeEnabled);
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
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}


	if(event->getDispatcher() == colorProp  && event->getEventCode() == Event::CHANGE_EVENT) {
		entity->color = colorProp->get();
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}

		
	if(event->getDispatcher() == idProp  && event->getEventCode() == Event::CHANGE_EVENT) {
		entity->id = idProp->get();
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}

	if(event->getDispatcher() == tagProp  && event->getEventCode() == Event::CHANGE_EVENT) {
		
		entity->clearTags();
		String cleaned =  tagProp->get().replace(" ", "");
		std::vector<String> tags = cleaned.split(",");
		for(int i=0; i < tags.size(); i++) {
			entity->addTag(tags[i]);
		}
		
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
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
	propHeight = 650;
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
		caption->set(label->getText());		
		enableAA->set(label->getLabel()->getAntialiasMode() == Label::ANTIALIAS_FULL);
		if(label->getLabel()->getSize() != lastSize) {
			size->set(label->getLabel()->getSize());
			lastSize = label->getLabel()->getSize();
		}
		
		for(int i=0; i < font->comboEntry->getNumItems(); i++) {
			String comboFont = font->comboEntry->getItemAtIndex(i)->label;
			
			if(comboFont == label->getLabel()->getFont()->getFontName()) {
				if(comboFont != lastFont) {
					font->comboEntry->setSelectedIndex(i);
					lastFont = comboFont;
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
