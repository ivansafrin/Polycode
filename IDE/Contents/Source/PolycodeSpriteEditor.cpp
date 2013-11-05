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


SpriteAnimationEntry::SpriteAnimationEntry(SpriteAnimation *animation) : PropProp("","") {
	
	this->animation = animation;
	
	removeButton = new UIImageButton("main/remove_icon.png", 1.0, 12, 12);
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
	
	playButton = new UIImageButton("main/play_icon.png", 1.0, 16, 16);
	playButton->setPosition(330, 3);
	playButton->addEventListener(this, UIEvent::CLICK_EVENT);
	addChild(playButton);
	
	setHeight(30);
	
}

void SpriteAnimationEntry::setPropWidth(Number width) {
	Number fieldsWidth = width - 40 - 15 - PROP_PADDING;
	
	nameInput->Resize(fieldsWidth * 0.4, nameInput->getHeight());
	framesInput->Resize(fieldsWidth * 0.4, framesInput->getHeight());
	speedInput->Resize(fieldsWidth * 0.2, speedInput->getHeight());
	
	framesInput->setPositionX(nameInput->getPosition().x + nameInput->getWidth() + 5);
	speedInput->setPositionX(framesInput->getPosition().x + framesInput->getWidth() + 5);
	playButton->setPositionX(speedInput->getPosition().x + speedInput->getWidth() + 5);
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

SpritePreviewSheet::SpritePreviewSheet() : PropSheet("SPRITE PREVIEW", ""){
	zoomProp = new ComboProp("Zoom");
	addProp(zoomProp);
	zoomProp->addEventListener(this, Event::CHANGE_EVENT);	
	
	zoomProp->comboEntry->addComboItem("No Zoom");
	zoomProp->comboEntry->addComboItem("Zoom 2x");
	zoomProp->comboEntry->addComboItem("Zoom 4x");
	zoomProp->comboEntry->addComboItem("Zoom 8x");
	zoomProp->comboEntry->addComboItem("Zoom 16x");

	zoomProp->set(0);
	
	previewProp = new SpritePreviewProp();
	addProp(previewProp);
}

void SpritePreviewSheet::handleEvent(Event *event) {
	if(event->getDispatcher() == zoomProp) {
		switch (zoomProp->get()) {
			case 1:
				previewProp->setSpriteScale(2.0);
			break;
			case 2:
				previewProp->setSpriteScale(4.0);
			break;
			case 3:
				previewProp->setSpriteScale(8.0);			
			break;
			case 4:
				previewProp->setSpriteScale(16.0);			
			break;
			default:
				previewProp->setSpriteScale(1.0);
			break;
		}
		
		if(previewProp->previewSprite) {
			propHeight = (previewProp->previewSprite->getHeight() * previewProp->previewSprite->getScale().y) + zoomProp->getHeight()+ 50;						
			dispatchEvent(new Event(), Event::COMPLETE_EVENT);
		}
	}
	PropSheet::handleEvent(event);
}

void SpritePreviewSheet::setSprite(SceneSprite *sprite) {
	previewProp->setSprite(sprite);
	propHeight = sprite->getHeight() + zoomProp->getHeight()+ 50;	
	dispatchEvent(new Event(), Event::COMPLETE_EVENT);
}

SpritePreviewProp::SpritePreviewProp() : PropProp("", "") {
	previewSprite = NULL;
}

void SpritePreviewProp::setPropWidth(Number width) {
	if(previewSprite) {
		previewSprite->setPosition(((width-(previewSprite->getWidth()* previewSprite->getScale().x))/2.0) - propContents->getPosition().x, 0.0);
	}
	propWidth = width;
}

void SpritePreviewProp::setSprite(SceneSprite *sprite) {
	previewSprite = sprite;
	propContents->addChild(sprite);	
}

void SpritePreviewProp::setSpriteScale(Number scale) {
	if(!previewSprite) {
		return;
	}
	previewSprite->setScale(scale, scale);
	setPropWidth(propWidth);
}

SpriteAnimationsSheet::SpriteAnimationsSheet() : PropSheet("ANIMATIONS", "") {
	animHelpLabel = new UILabel("Comma separated frames, ranges or repeats (e.g. 1,2,3-7,8x5)", 11);
	contents->addChild(animHelpLabel);

	propHeight = 230;
		
	addAnimationButton = new UIButton("Add Animation", 100);
	contents->addChild(addAnimationButton);
	addAnimationButton->addEventListener(this, UIEvent::CLICK_EVENT);
	
	setTopPadding(30);
	lastNumProps = 0;
	sprite = NULL;
	removeIndex = -1;
}

void SpriteAnimationsSheet::Update() {
	if(removeIndex != -1) {
		SpriteAnimationEntry *entryProp = (SpriteAnimationEntry*) props[removeIndex];
		sprite->removeAnimation(entryProp->animation);
		removeIndex = -1;
		refreshAnimationEntries();		
	}
}

void SpriteAnimationsSheet::Resize(Number width, Number height) {
	addAnimationButton->Resize(width - 60, addAnimationButton->getHeight());
	animHelpLabel->setPosition((width-animHelpLabel->getWidth())/2.0, 0.0);
	
	PropSheet::Resize(width, height);
}

void SpriteAnimationsSheet::handleEvent(Event *event) {

	if(event->getDispatcher() == addAnimationButton) {
		if(sprite) {
			sprite->addAnimation("new_animation", "0", 0.1);
			refreshAnimationEntries();
		}
	} else {
		for(int i=0; i < props.size(); i++) {
			if(event->getDispatcher() == props[i]) {
				SpriteAnimationEntry *entryProp = (SpriteAnimationEntry*) props[i];
				
				if(event->getEventCode() == Event::CANCEL_EVENT) {
					removeIndex = i;
					break;
				} else if(event->getEventCode() == Event::CHANGE_EVENT) {
					sprite->playAnimation(entryProp->nameInput->getText(), 0, false);
				}
			}
		}
	}
	
	PropSheet::handleEvent(event);
}

void SpriteAnimationsSheet::setSprite(SceneSprite *sprite) {
	this->sprite = sprite;
	refreshAnimationEntries();
}

void SpriteAnimationsSheet::refreshAnimationEntries() {

	if(!sprite) {
		return;
	}

	for(int i=0; i < props.size(); i++) {
		contents->removeChild(props[i]);
		props[i]->removeAllHandlersForListener(this);
		delete props[i];
	}
	props.clear();
	propHeight = 30;
	
	for(int i=0; i < sprite->getNumAnimations(); i++) {			
		SpriteAnimation *animation = sprite->getAnimationAtIndex(i);		
		SpriteAnimationEntry *newEntry = new SpriteAnimationEntry(animation);
		newEntry->addEventListener(this, Event::CHANGE_EVENT);
		newEntry->addEventListener(this, Event::CANCEL_EVENT);
		addProp(newEntry);
		propHeight += 30;
	}
	
	addAnimationButton->setPosition(15, propHeight);	
	propHeight += 70;	
	
	if(lastNumProps != sprite->getNumAnimations()) {
		dispatchEvent(new Event(), Event::COMPLETE_EVENT);
	}
	
	lastNumProps = sprite->getNumAnimations();		
	Resize(getWidth(), getHeight());	
}

PolycodeSpriteEditor::PolycodeSpriteEditor() : PolycodeEditor(true){
	headerBg = new UIRect(10,10);
	addChild(headerBg);
	headerBg->setAnchorPoint(-1.0, -1.0, 0.0);
	headerBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));
	
	initialLoad = false;

	propList = new PropList("SPRITE EDITOR");
	addChild(propList);
	propList->setPosition(0, 0);
		
	previewPropSheet = new SpritePreviewSheet();
	propList->addPropSheet(previewPropSheet);

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
	
	animationsSheet = new SpriteAnimationsSheet();
	propList->addPropSheet(animationsSheet);	
			
	propList->updateProps();
	
}

void PolycodeSpriteEditor::handleEvent(Event *event) {

	if(!initialLoad) {	
		if(event->getDispatcher() == textureProp) {
			previewSprite->setTexture(textureProp->get());
			previewSprite->recalculateSpriteDimensions();
			previewSprite->getTexture()->reloadOnFileModify = true;
		}

		if(event->getDispatcher() == widthProp) {
			previewSprite->setSpriteSize(widthProp->get(), heightProp->get());
			previewSprite->setPrimitiveOptions(ScenePrimitive::TYPE_VPLANE, widthProp->get(), heightProp->get());
			previewSprite->recalculateSpriteDimensions();		
		}

		if(event->getDispatcher() == heightProp) {
			previewSprite->setSpriteSize(widthProp->get(), heightProp->get());
			previewSprite->setPrimitiveOptions(ScenePrimitive::TYPE_VPLANE, widthProp->get(), heightProp->get());
			previewSprite->recalculateSpriteDimensions();		
		}
	}
}

PolycodeSpriteEditor::~PolycodeSpriteEditor() {	
	delete propList;
	delete headerBg;
	delete textureProp;
	delete widthProp;
	delete heightProp;
	delete previewSprite;
}

bool PolycodeSpriteEditor::openFile(OSFileEntry filePath) {
					
	initialLoad = true;
		
	previewSprite = new SceneSprite(filePath.fullPath);
	previewSprite->setAnchorPoint(-1.0, -1.0, 0.0);
	previewSprite->setPosition(400, 80);				
	previewSprite->getTexture()->reloadOnFileModify = true;	
	previewPropSheet->setSprite(previewSprite);
	
	if(previewSprite->getNumAnimations() > 0) {
		previewSprite->playAnimation(previewSprite->getAnimationAtIndex(0)->name, 0, false);
	}
	
	animationsSheet->setSprite(previewSprite);
	
	widthProp->set(previewSprite->getSpriteSize().x);
	heightProp->set(previewSprite->getSpriteSize().y);
		
	textureProp->set(previewSprite->getTexture());
				
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

	for(int i=0; i < previewSprite->getNumAnimations(); i++) {
		ObjectEntry *animation = animations->addChild("animation");	
		SpriteAnimation *anim = previewSprite->getAnimationAtIndex(i);
		
		animation->addChild("name", anim->name);
		animation->addChild("frames", anim->frames);
		animation->addChild("speed", anim->speed);			
	}
	saveObject.saveToXML(filePath);
}

void PolycodeSpriteEditor::Resize(int x, int y) {
	headerBg->Resize(x, 30);
	propList->Resize(x, y);
	propList->updateProps();	
	PolycodeEditor::Resize(x,y);	
}

