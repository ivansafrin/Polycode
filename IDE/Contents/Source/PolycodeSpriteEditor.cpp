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
 
#include "PolycodeSpriteEditor.h"
#include "PolycodeFrame.h"

extern UIColorPicker *globalColorPicker;
extern PolycodeFrame *globalFrame;
extern UIGlobalMenu *globalMenu;


SpriteAnimationEntry::SpriteAnimationEntry(SpriteAnimation *animation) : UIElement() {

	this->animation = animation;

	removeButton = new UIImageButton("Images/remove_icon.png");
	removeButton->setPosition(0, 5);
	removeButton->addEventListener(this, UIEvent::CLICK_EVENT);
	addChild(removeButton);

	nameInput = new UITextInput(false, 82, 12);
	nameInput->setText(animation->name);
	nameInput->setPosition(20, 0);
	nameInput->addEventListener(this, UIEvent::CHANGE_EVENT);
	addChild(nameInput);

	framesInput = new UITextInput(false, 142, 12);
	framesInput->setText(animation->frames);
	framesInput->setPosition(115, 0);
	framesInput->addEventListener(this, UIEvent::CHANGE_EVENT);
	addChild(framesInput);

	speedInput = new UITextInput(false, 42, 12);
	speedInput->setText(String::NumberToString(animation->speed));
	speedInput->setPosition(270, 0);
	speedInput->addEventListener(this, UIEvent::CHANGE_EVENT);
	addChild(speedInput);

	playButton = new UIImageButton("Images/play_icon.png");
	playButton->setPosition(330, 3);
	playButton->addEventListener(this, UIEvent::CLICK_EVENT);
	addChild(playButton);

}

void SpriteAnimationEntry::handleEvent(Event *event) {

	if(event->getEventCode() == UIEvent::CHANGE_EVENT && event->getEventType() == "UIEvent") {
		if(event->getDispatcher() == nameInput) {
			animation->name = nameInput->getText();
		}

		if(event->getDispatcher() == framesInput) {
			animation->setOffsetsFromFrameString(framesInput->getText());
		}

		if(event->getDispatcher() == speedInput) {
			animation->speed = atof(speedInput->getText().c_str());
		}

	}

	if(event->getEventCode() == UIEvent::CLICK_EVENT && event->getEventType() == "UIEvent") {
		if(event->getDispatcher() == removeButton) {
			dispatchEvent(new Event(), Event::CANCEL_EVENT);
		}

		if(event->getDispatcher() == playButton) {
			dispatchEvent(new Event(), Event::CHANGE_EVENT);
		}

	}
}

SpriteAnimationEntry::~SpriteAnimationEntry() {
	delete nameInput;
	delete framesInput;
	delete speedInput;
	delete removeButton;
	delete playButton;
}

PolycodeSpriteEditor::PolycodeSpriteEditor() : PolycodeEditor(true){
	headerBg = new ScreenShape(ScreenShape::SHAPE_RECT,10,10);
	addChild(headerBg);
	headerBg->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	headerBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));

	initialLoad = false;

	propList = new PropList("SPRITE EDITOR");
	addChild(propList);
	propList->setPosition(0, 0);

	PropSheet *baseProps = new PropSheet("IMAGE OPTIONS", "");
	propList->addPropSheet(baseProps);

	textureProp = new TextureProp("Base image");
	baseProps->addProp(textureProp);

	widthProp = new NumberProp("Frame width");
	widthProp->set(32);
	baseProps->addProp(widthProp);	

	heightProp = new NumberProp("Frame height");
	heightProp->set(32);
	baseProps->addProp(heightProp);	

	widthProp->addEventListener(this, Event::CHANGE_EVENT);
	textureProp->addEventListener(this, Event::CHANGE_EVENT);
	heightProp->addEventListener(this, Event::CHANGE_EVENT);

	baseProps->propHeight = 180;

	ScreenLabel *label = new ScreenLabel("PREVIEW", 18, "section", Label::ANTIALIAS_FULL);
	label->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderFontColor"));
	addChild(label);
	label->setPosition(390, 36);


	PropSheet *animationProps = new PropSheet("ANIMATIONS", "");
	propList->addPropSheet(animationProps);

	animationProps->propHeight = 200;

	animationsAnchor = new UIElement();
	animationProps->contents->addChild(animationsAnchor);

	addAnimationButton = new UIButton("Add Animation", 100);
	animationsAnchor->addChild(addAnimationButton);
	addAnimationButton->addEventListener(this, UIEvent::CLICK_EVENT);

	propList->updateProps();

	zoomBox = new UIComboBox(globalMenu, 100);
	addChild(zoomBox);
	zoomBox->setPosition(490, 37);
	zoomBox->addEventListener(this, UIEvent::CHANGE_EVENT);

	zoomBox->addComboItem("No Zoom");
	zoomBox->addComboItem("Zoom 2x");
	zoomBox->addComboItem("Zoom 4x");
	zoomBox->addComboItem("Zoom 8x");
	zoomBox->addComboItem("Zoom 16x");
}

void PolycodeSpriteEditor::refreshAnimationEntries() {
	for(int i=0; i < animationEntries.size(); i++) {
		animationEntries[i]->setPosition(0, 30*i);
	}
	addAnimationButton->setPosition(0, (animationEntries.size() * 30) + 10);
}


void PolycodeSpriteEditor::handleEvent(Event *event) {

	if(event->getDispatcher() == zoomBox) {
		switch (zoomBox->getSelectedIndex()) {
			case 1:
				previewSprite->setScale(2.0, 2.0);
			break;
			case 2:
				previewSprite->setScale(4.0, 4.0);
			break;
			case 3:
				previewSprite->setScale(8.0, 8.0);
			break;
			case 4:
				previewSprite->setScale(16.0, 16.0);
			break;
			default:
				previewSprite->setScale(1.0, 1.0);
			break;
		}
	}

	if(!initialLoad) {

		if(event->getDispatcher() == textureProp) {
			previewSprite->setTexture(textureProp->get());
			previewSprite->recalculateSpriteDimensions();
			previewSprite->getTexture()->reloadOnFileModify = true;
		}

		if(event->getDispatcher() == widthProp) {
			previewSprite->setSpriteSize(widthProp->get(), heightProp->get());
			previewSprite->setShapeSize(widthProp->get(), heightProp->get());
			previewSprite->recalculateSpriteDimensions();
		}

		if(event->getDispatcher() == heightProp) {
			previewSprite->setSpriteSize(widthProp->get(), heightProp->get());
			previewSprite->setShapeSize(widthProp->get(), heightProp->get());
			previewSprite->recalculateSpriteDimensions();
		}

	}

	if(event->getDispatcher() == addAnimationButton) {
		SpriteAnimationEntry *newEntry = new SpriteAnimationEntry(previewSprite->addAnimation("default", "0", 0.5));
		newEntry->addEventListener(this, Event::CHANGE_EVENT);
		newEntry->addEventListener(this, Event::CANCEL_EVENT);
		animationsAnchor->addChild(newEntry);
		animationEntries.push_back(newEntry);
		refreshAnimationEntries();
	}

	bool doRefresh = false;
	for(int i=0; i < animationEntries.size(); i++) {
		if(event->getDispatcher() == animationEntries[i]) {
			if(event->getEventCode() == Event::CANCEL_EVENT) {
				animationsAnchor->removeChild(animationEntries[i]);
				animationEntries.erase(animationEntries.begin()+i);
				doRefresh = true;
				break;
			}

			if(event->getEventCode() == Event::CHANGE_EVENT) {
				previewSprite->playAnimation(animationEntries[i]->nameInput->getText(), 0, false);
			}
		}
	}

	if(doRefresh) {
		refreshAnimationEntries();
	}
}

PolycodeSpriteEditor::~PolycodeSpriteEditor() {
	for(int i=0; i < animationEntries.size(); i++) {
		delete animationEntries[i];
	}

	delete animationsAnchor;
	delete addAnimationButton;
	delete propList;
	delete headerBg;
	delete zoomBox;
	delete textureProp;
	delete widthProp;
	delete heightProp;
	delete previewSprite;
}

bool PolycodeSpriteEditor::openFile(OSFileEntry filePath) {

	initialLoad = true;

	previewSprite = new ScreenSprite(filePath.fullPath);
	addChild(previewSprite);
	previewSprite->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	previewSprite->setPosition(400, 80);
	zoomBox->setSelectedIndex(0);
	previewSprite->getTexture()->reloadOnFileModify = true;	

	for(int i=0;i < previewSprite->getNumAnimations(); i++) {
		SpriteAnimation *animation = previewSprite->getAnimationAtIndex(i);
		SpriteAnimationEntry *newEntry = new SpriteAnimationEntry(animation);
		newEntry->addEventListener(this, Event::CHANGE_EVENT);
		newEntry->addEventListener(this, Event::CANCEL_EVENT);
		animationsAnchor->addChild(newEntry);
		animationEntries.push_back(newEntry);
	}

	if(previewSprite->getNumAnimations() > 0) {
		previewSprite->playAnimation(previewSprite->getAnimationAtIndex(0)->name, 0, false);
	}

	widthProp->set(previewSprite->getSpriteSize().x);
	heightProp->set(previewSprite->getSpriteSize().y);

	textureProp->set(previewSprite->getTexture());

	refreshAnimationEntries();

	PolycodeEditor::openFile(filePath);

	initialLoad = false;
	return true;
}

void PolycodeSpriteEditor::saveFile() {
	Object saveObject;

	saveObject.root.name = "sprite";

	ObjectEntry *image = saveObject.root.addChild("image");
	image->addChild("frameWidth", widthProp->get());
	image->addChild("frameHeight", heightProp->get());
	image->addChild("fileName", previewSprite->getTexture()->getResourcePath());

	ObjectEntry *animations = saveObject.root.addChild("animations");

	for(int i=0; i < animationEntries.size(); i++) {
		ObjectEntry *animation = animations->addChild("animation");
		animation->addChild("name", animationEntries[i]->nameInput->getText());
		animation->addChild("frames", animationEntries[i]->framesInput->getText());
		animation->addChild("speed", atof(animationEntries[i]->speedInput->getText().c_str()));	
	}

	saveObject.saveToXML(filePath);
}

void PolycodeSpriteEditor::Resize(int x, int y) {
	headerBg->setShapeSize(x, 30);
	propList->Resize(370, y);
	propList->updateProps();
	PolycodeEditor::Resize(x,y);
}

