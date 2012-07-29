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
 
#include "PolycodeScreenEditor.h"

PolycodeScreenEditor::PolycodeScreenEditor() : PolycodeEditor(true){

	Config *conf = CoreServices::getInstance()->getConfig();	
	String fontName = conf->getStringValue("Polycode", "uiDefaultFontName");
	int fontSize = conf->getNumericValue("Polycode", "uiDefaultFontSize");	
	Number padding = conf->getNumericValue("Polycode", "uiWindowSkinPadding");	

	isScalingEntity = false;
	
	selectedEntity = NULL;
	isDraggingEntity = false; 
	
	grid = new ScreenImage("editorGrid.png");
	
	addChild(grid);
	grid->snapToPixels = true;
	
	baseEntity = new ScreenEntity();
	addChild(baseEntity);
	
	grid->getTexture()->clamp = false;
	grid->getTexture()->recreateFromImageData();	
		
	baseEntity->setPositionMode(ScreenEntity::POSITION_CENTER);	

	centerImage = new ScreenImage("screenCenter.png");
	centerImage->setPositionMode(ScreenEntity::POSITION_CENTER);
	addChild(centerImage);
	
	baseEntity->setPosition(256,256);
	baseEntity->setWidth(20000);
	baseEntity->setHeight(20000);
		
	centerImage->setPosition(256, 256);
				
	baseEntity->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	baseEntity->addEventListener(this, InputEvent::EVENT_MOUSEUP_OUTSIDE);
	baseEntity->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);
	baseEntity->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	baseEntity->processInputEvents = true;
									
	screenTransform = new UIBox("screenTransform.png", 16,16,16,16, 100,100);
	screenTransform->visible = false;
	addChild(screenTransform);
		
	entityInfoWindow = new UIWindow("Selected entity", 140, 100);
	addChild(entityInfoWindow);	
	entityInfoWindow->setPosition(15,15);
	
	ScreenLabel *label2 = new ScreenLabel(L"Entity color:", fontSize, fontName, Label::ANTIALIAS_FULL);
	entityInfoWindow->addChild(label2);
	label2->setPosition(padding, entityInfoWindow->topPadding+20);

	entityColorBox = new UIColorBox(Color(1.0, 1.0, 1.0, 0.0), 30,30);
	entityColorBox->setPosition(label2->getPosition().x, label2->getPosition().y+label2->getHeight());
	entityInfoWindow->addChild(entityColorBox);		
	entityColorBox->addEventListener(this, UIEvent::CHANGE_EVENT);
	
}

PolycodeScreenEditor::~PolycodeScreenEditor() {
	
}

bool PolycodeScreenEditor::openFile(String filePath) {
	
	PolycodeEditor::openFile(filePath);	
	return true;
}

void PolycodeScreenEditor::handleDroppedFile(OSFileEntry file, Number x, Number y) {
	ScreenEntity *newEntity = NULL;
	if(file.extension == "png") {
		ScreenImage *newImage = new ScreenImage(file.fullPath);
		newImage->setPositionMode(ScreenEntity::POSITION_CENTER);
		baseEntity->addChild(newImage);
		newImage->setPosition(x-baseEntity->getPosition2D().x,y-baseEntity->getPosition2D().y);
		newEntity = newImage;
		newImage->processInputEvents = true;
	}
	
	if(newEntity) {
		newEntity->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
		newEntity->blockMouseInput = true;
	}
}

void PolycodeScreenEditor::syncTransformToSelected() {
	if(!selectedEntity)
		return;
		
	screenTransform->resizeBox((selectedEntity->getWidth() * selectedEntity->getScale().x) + 5, (selectedEntity->getHeight() * selectedEntity->getScale().y) + 5);		
	screenTransform->setPosition(selectedEntity->getPosition2D().x+baseEntity->getPosition2D().x-screenTransform->getWidth()/2.0,  selectedEntity->getPosition2D().y+baseEntity->getPosition2D().y-screenTransform->getHeight()/2.0);			
}

void PolycodeScreenEditor::handleEvent(Event *event) {
	InputEvent *inputEvent = (InputEvent*) event;
	
	if(event->getDispatcher() == entityColorBox  && event->getEventType() == "UIEvent") {
		switch (event->getEventCode()) {
			case UIEvent::CHANGE_EVENT:
				if(selectedEntity) {
					selectedEntity->setColor(entityColorBox->getSelectedColor());
				}
			break;
		}
		return;
	}
	
	if(event->getDispatcher() == baseEntity) {
		switch (event->getEventCode()) {
			case InputEvent::EVENT_MOUSEDOWN:
				selectedEntity = NULL;
				screenTransform->visible = false;
			break;		
			case InputEvent::EVENT_MOUSEUP:
			case InputEvent::EVENT_MOUSEUP_OUTSIDE:			
				isDraggingEntity = false;	
				isScalingEntity = false;	
				if(selectedEntity) 					
					selectedEntity->stopDrag();
			break;
			case InputEvent::EVENT_MOUSEMOVE:
			{
				if(isDraggingEntity) {
					if(selectedEntity) 
						syncTransformToSelected();
				} else if(isScalingEntity) {
/*
					Vector2 scaleVector = Vector2(selectedEntity->getPosition2D().x + baseEntity->getPosition2D().x, selectedEntity->getPosition2D().y + baseEntity->getPosition2D().y) - inputEvent->mousePosition;
					
					scaleVector.x =	scaleVector.x / selectedEntity->getWidth() * 2.0;
					scaleVector.y =	scaleVector.y / selectedEntity->getHeight() * 2.0;					
					selectedEntity->setScale(scaleVector.x, scaleVector.y, 0);
					*/
					syncTransformToSelected();
				}
			}
			break;			
		}
		return;
	}

	for(int i=0; i < baseEntity->getNumChildren(); i++) {
		ScreenEntity* childEntity = (ScreenEntity*) baseEntity->getChildAtIndex(i);
		if(event->getDispatcher() == childEntity) {		
			screenTransform->visible = true;					
			
			selectedEntity = childEntity;
			entityColorBox->setBoxColor(selectedEntity->color);
			syncTransformToSelected();
			
			Number cornerSize = 12;
			if(false) {
				isScalingEntity = true;
			} else {
				selectedEntity->startDrag(inputEvent->getMousePosition().x, inputEvent->getMousePosition().y);
				isDraggingEntity = true;						
			}
			
			
		}
	}
}

void PolycodeScreenEditor::Resize(int x, int y) {
	grid->setImageCoordinates(0,0,x,y);	
}

