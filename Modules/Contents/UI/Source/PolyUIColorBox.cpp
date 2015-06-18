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

#include "PolyUIColorBox.h"
#include "PolyInputEvent.h"
#include "PolyLabel.h"
#include "PolyCoreServices.h"
#include "PolyConfig.h"
#include "PolyRenderer.h"

using namespace Polycode;

UIColorPicker::UIColorPicker() : UIWindow(L"", 300, 240) {
	closeOnEscape = true;
	
	continuous = true;
		
//	topPadding
	Config *conf = CoreServices::getInstance()->getConfig();	
    Number uiScale = conf->getNumericValue("Polycode", "uiScale");
		
	String fontName = conf->getStringValue("Polycode", "uiDefaultFontName");
	int fontSize = conf->getNumericValue("Polycode", "uiDefaultFontSize");

	String mainBgImage = conf->getStringValue("Polycode", "uiColorPickerMainBg");		
	String mainFrameImage = conf->getStringValue("Polycode", "uiColorPickerMainFrame");
	String hueFrameImage = conf->getStringValue("Polycode", "uiColorPickerHueFrame");
	String hueSelectorImage = conf->getStringValue("Polycode", "uiColorPickerHueSelector");
	String mainSelectorImage = conf->getStringValue("Polycode", "uiColorPickerMainSelector");

	mainBg = new UIImage(mainBgImage, 187, 187);
	mainBg->setPosition(padding, topPadding+padding);
	addChild(mainBg);

	mainFrame = new UIImage(mainFrameImage, 187, 187);
	mainFrame->setPosition(padding, topPadding+padding);
	
	alphaSlider = new UIHSlider(0, 1.0, mainFrame->getWidth());
	alphaSlider->setPosition(padding, mainFrame->getHeight() + mainFrame->getPosition().y + 13);
	addChild(alphaSlider);
	alphaSlider->addEventListener(this, UIEvent::CHANGE_EVENT);
	
	mainColorRect = new SceneMesh(Mesh::QUAD_MESH);
    mainColorRect->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
	mainColorRect->setWidth(mainFrame->getWidth());
	mainColorRect->setHeight(mainFrame->getWidth());
	mainColorRect->setDepth(0.001);
		
	mainColorRect->getMesh()->addVertexWithUV(-mainFrame->getWidth()/2,mainFrame->getHeight()/2.0,0,0,0);
	mainColorRect->getMesh()->addVertexWithUV(mainFrame->getWidth()/2,mainFrame->getHeight()/2.0,0, 1, 0);
	mainColorRect->getMesh()->addVertexWithUV(mainFrame->getWidth()/2,-mainFrame->getHeight()/2.0,0, 1, 1);
	mainColorRect->getMesh()->addVertexWithUV(-mainFrame->getWidth()/2,-mainFrame->getHeight()/2.0,0,0,1);
	
	mainColorRect->backfaceCulled = false;	

	mainColorRect->setAnchorPoint(-1.0, -1.0, 0.0);
	mainColorRect->setPosition(padding, topPadding+padding);
	addChild(mainColorRect);
	addChild(mainFrame);

	hueFrame = new UIImage(hueFrameImage, 20, 187);
	hueFrame->setPosition(mainFrame->getPosition().x + mainFrame->getWidth()+10, topPadding+padding);
	addChild(hueFrame);
	
	hueSelector = new UIImage(hueSelectorImage);
    hueSelector->Resize(hueSelector->getWidth() / uiScale, hueSelector->getHeight() / uiScale);
	hueSelector->setAnchorPoint(0.0, 0.0, 0.0);
	hueSelector->setPosition(hueFrame->getPosition().x + (hueFrame->getWidth()/2.0), hueFrame->getPosition().y);
	addChild(hueSelector);	

	hueSelector->setDragLimits(Polycode::Rectangle(hueSelector->getPosition().x,hueSelector->getPosition().y,0,hueFrame->getHeight()));
				
	mainSelector = new UIImage(mainSelectorImage);
    mainSelector->Resize(mainSelector->getWidth() / uiScale, mainSelector->getHeight() / uiScale);
	mainSelector->setAnchorPoint(0.0, 0.0, 0.0);
	mainSelector->setPosition(mainFrame->getPosition());
	addChild(mainSelector);	
	
	mainColorRect->getMesh()->useVertexColors = true;
	
	mainColorRect->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	mainColorRect->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	mainColorRect->addEventListener(this, InputEvent::EVENT_MOUSEUP_OUTSIDE);
	mainColorRect->processInputEvents = true;
	
	
	hueFrame->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	hueFrame->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	hueFrame->addEventListener(this, InputEvent::EVENT_MOUSEUP_OUTSIDE);
	hueFrame->processInputEvents = true;	
	
	UILabel *label = new UILabel(L"R:", fontSize, fontName);
	label->setPosition(hueFrame->getPosition().x+hueFrame->getWidth() + 15, topPadding+padding + 3);
	addChild(label);
	junkLabels.push_back(label);
	
	rTextInput = new UITextInput(false, 40, 12);
	rTextInput->setPosition(hueFrame->getPosition().x+hueFrame->getWidth() + 30, topPadding+padding);
	addFocusChild(rTextInput);
	rTextInput->addEventListener(this, UIEvent::CHANGE_EVENT);

	label = new UILabel(L"G:", fontSize, fontName);
	label->setPosition(hueFrame->getPosition().x+hueFrame->getWidth() + 15, topPadding+padding + 33);
	addChild(label);
	junkLabels.push_back(label);
	
	gTextInput = new UITextInput(false, 40, 12);
	gTextInput->setPosition(hueFrame->getPosition().x+hueFrame->getWidth() + 30, topPadding+padding + 30);
	addFocusChild(gTextInput);
	gTextInput->addEventListener(this, UIEvent::CHANGE_EVENT);
	
	label = new UILabel(L"B:", fontSize, fontName);
	label->setPosition(hueFrame->getPosition().x+hueFrame->getWidth() + 15, topPadding+padding + 63);
	addChild(label);
	junkLabels.push_back(label);
	
	bTextInput = new UITextInput(false, 40, 12);
	bTextInput->setPosition(hueFrame->getPosition().x+hueFrame->getWidth() + 30, topPadding+padding + 60);
	addFocusChild(bTextInput);
	bTextInput->addEventListener(this, UIEvent::CHANGE_EVENT);
	
	label = new UILabel(L"A:", fontSize, fontName);
	label->setPosition(hueFrame->getPosition().x+hueFrame->getWidth() + 15, topPadding+padding + 93);
	addChild(label);
	junkLabels.push_back(label);
	
	aTextInput = new UITextInput(false, 40, 12);
	aTextInput->setPosition(hueFrame->getPosition().x+hueFrame->getWidth() + 30, topPadding+padding + 90);
	addFocusChild(aTextInput);
	aTextInput->addEventListener(this, UIEvent::CHANGE_EVENT);
	
	setHue(0.0);
	setSaturationAndValue(0.0, 0.0);
	
	rTextInput->setNumberOnly(true);
	gTextInput->setNumberOnly(true);
	bTextInput->setNumberOnly(true);
	aTextInput->setNumberOnly(true);
	
	lastHueSelectorPosition = 0;
	
	mainSelector->setDragLimits(Polycode::Rectangle(mainColorRect->getPosition().x,mainColorRect->getPosition().y,mainColorRect->getWidth(), mainColorRect->getHeight()));
				
	colorAlpha = 1.0;
	
	visible = false;
	enabled = false;
	suppressTextChangeEvent = false;
}

void UIColorPicker::cancelColorListeners() {
	dispatchEvent(new Event(), Event::CANCEL_EVENT);
}

void UIColorPicker::onClose() {
	visible = false;
	enabled = false;
}

void UIColorPicker::rebuildFromTextInputs() {
	int	newR = atoi(rTextInput->getText().c_str());
	int	newG = atoi(gTextInput->getText().c_str());
	int	newB = atoi(bTextInput->getText().c_str());
	int	newA = atoi(aTextInput->getText().c_str());			
	
	
	if(newR < 0)
		newR = 0;
	if(newR > 255)
		newR = 255;

	if(newG < 0)
		newG = 0;
	if(newG > 255)
		newG = 255;

	if(newB < 0)
		newB = 0;
	if(newB > 255)
		newB = 255;

	if(newA < 0)
		newA = 0;
	if(newA > 255)
		newA = 255;	
	
	Color newColor;
	newColor.setColorRGBA(newR, newG, newB, newA);

	currentS = newColor.getSaturation();
	currentV = newColor.getValue();
	currentH = newColor.getHue();
	colorAlpha = newColor.a;
	
	updateSelectedColor(false);


}

bool UIColorPicker::isContinuous() {
	return continuous;
}
void UIColorPicker::setContinuous(bool _continuous) {
	continuous = _continuous;
	alphaSlider->setContinuous(continuous);
}

void UIColorPicker::setPickerColor(Color newColor) {
	currentS = newColor.getSaturation();
	currentV = newColor.getValue();
	currentH = newColor.getHue();
	colorAlpha = newColor.a;
	updateSelectedColor();
}

void UIColorPicker::setSaturationAndValue(Number S, Number V) {
	currentS = S;
	currentV = V;	
	updateSelectedColor(true, false, false);
}

void UIColorPicker::updateSelectedColor(bool updateTextFields, bool updateHue, bool updateSV) {
	
	selectedColor.setColorHSV(currentH, currentS, currentV);
	selectedColor.a = colorAlpha;
	
	int newR = floor(selectedColor.r*255.0);
	int newG = floor(selectedColor.g*255.0);
	int newB = floor(selectedColor.b*255.0);
	int newA = floor(selectedColor.a*255.0);
		
	mainColorRect->color.a = colorAlpha;
	
	if(updateTextFields) {
		suppressTextChangeEvent = true;
		rTextInput->setText(String::IntToString(newR));
		suppressTextChangeEvent = true;		
		gTextInput->setText(String::IntToString(newG));
		suppressTextChangeEvent = true;		
		bTextInput->setText(String::IntToString(newB));
		suppressTextChangeEvent = true;		
		aTextInput->setText(String::IntToString(newA));
	}
	
	Color hueCol;
	hueCol.setColorHSV(currentH, 1.0, 1.0);
	hueCol.a = colorAlpha;

    
    mainColorRect->getMesh()->vertexColorArray.data.clear();
    
    mainColorRect->getMesh()->addColor(Color((Number)1,(Number)1,(Number)1,colorAlpha));
    mainColorRect->getMesh()->addColor(hueCol);
    mainColorRect->getMesh()->addColor(Color((Number)0,(Number)0,(Number)0,colorAlpha));
    mainColorRect->getMesh()->addColor(Color((Number)0,(Number)0,(Number)0,colorAlpha));
    
	if(updateHue) {
		hueSelector->setPositionY(hueFrame->getPosition().y + hueFrame->getHeight() - ((currentH/360.0) * hueFrame->getHeight()));
		lastHueSelectorPosition = hueSelector->getPosition().y;
	}
	
	if(updateSV) {
		mainSelector->setPosition(mainColorRect->getPosition().x + (currentS * mainColorRect->getWidth()), mainColorRect->getPosition().y + mainColorRect->getHeight() - (currentV * mainColorRect->getHeight()));					
		lastMainSelectorPosition = mainSelector->getPosition2D();
	}
	
	alphaSlider->setSliderValue(colorAlpha);

	dispatchEvent(new Event(), Event::CHANGE_EVENT);
}

Color UIColorPicker::getSelectedColor() {
	return selectedColor;
}

void UIColorPicker::handleEvent(Event *event) {

	if((event->getDispatcher() == rTextInput || event->getDispatcher() == gTextInput || event->getDispatcher() == bTextInput || event->getDispatcher() == aTextInput) && event->getEventType() == "UIEvent") {
		switch(event->getEventCode()) {
			case UIEvent::CHANGE_EVENT:
			{
				if(!suppressTextChangeEvent) {
					rebuildFromTextInputs();
				} else {
					suppressTextChangeEvent = false;
				}
			}
			break;
		}	
	}

	if(event->getDispatcher() == alphaSlider) {
		switch(event->getEventCode()) {
			case UIEvent::CHANGE_EVENT:
			{
				colorAlpha = alphaSlider->getSliderValue();
				updateSelectedColor();
			}
			break;
		}
	}

	if(event->getDispatcher() == hueFrame) {
		switch(event->getEventCode()) {
			case InputEvent::EVENT_MOUSEDOWN:
			{
				InputEvent *inputEvent = (InputEvent*) event;
				hueSelector->setPositionY(inputEvent->getMousePosition().y+hueFrame->getPosition().y);
				hueSelector->startDrag(inputEvent->mousePosition.x-hueSelector->getPosition().x,inputEvent->mousePosition.y-hueSelector->getPosition().y+hueFrame->getPosition().y);
			}
			break;
			case InputEvent::EVENT_MOUSEUP:
			case InputEvent::EVENT_MOUSEUP_OUTSIDE:			
			{
				hueSelector->stopDrag();
				updateColorFromHueSelector();	
			}
			break;	
		}
	}



	if(event->getDispatcher() == mainColorRect) {
		switch(event->getEventCode()) {
			case InputEvent::EVENT_MOUSEDOWN:
			{
				InputEvent *inputEvent = (InputEvent*) event;
				mainSelector->setPosition(inputEvent->getMousePosition().x+mainColorRect->getPosition().x, inputEvent->getMousePosition().y+mainColorRect->getPosition().y);
				mainSelector->startDrag(inputEvent->mousePosition.x-mainSelector->getPosition().x+mainColorRect->getPosition().x,inputEvent->mousePosition.y-mainSelector->getPosition().y+mainColorRect->getPosition().y);
			}
			break;
			case InputEvent::EVENT_MOUSEUP:
			case InputEvent::EVENT_MOUSEUP_OUTSIDE:			
			{
				mainSelector->stopDrag();			
				updateColorFromMainSelector();
			}
			break;	
		}
	}
	
	UIWindow::handleEvent(event);
}

void UIColorPicker::setHue(Number hueNum) {
	if(hueNum < 0.0)
		hueNum = 0.0;
	if(hueNum >= 360.0)
		hueNum = 359.9999;		
		
	currentH = hueNum;
	updateSelectedColor(true, false, false);
}

UIColorPicker::~UIColorPicker() {
	delete mainBg;
	delete mainFrame;
	delete alphaSlider;
	delete mainColorRect;
	delete hueFrame;
	delete hueSelector;
	delete mainSelector;
	delete rTextInput;
	delete gTextInput;
	delete bTextInput;
	delete aTextInput;
	
	for(int c = 0; c < junkLabels.size(); c++)
		delete junkLabels[c];
}

void UIColorPicker::updateColorFromMainSelector() {
	if(mainSelector->getPosition2D() != lastMainSelectorPosition) {
		lastMainSelectorPosition = mainSelector->getPosition2D();
		
		Number newPosX = lastMainSelectorPosition.x;
		Number newPosY = lastMainSelectorPosition.y;		
		
		Number newV = 1.0 - (newPosY - mainColorRect->getPosition().y) / mainColorRect->getHeight();

		Number newS = (newPosX - mainColorRect->getPosition().x) / mainColorRect->getWidth();
					
		setSaturationAndValue(newS, newV);	
	}
}

void UIColorPicker::updateColorFromHueSelector() {
	if(hueSelector->getPosition().y != lastHueSelectorPosition) {
		lastHueSelectorPosition = hueSelector->getPosition().y;
		
		Number newPosY = lastHueSelectorPosition;
									
		if(newPosY < hueFrame->getPosition().y)
			newPosY =  hueFrame->getPosition().y;
		if(newPosY > hueFrame->getHeight() +  hueFrame->getPosition().y)
			newPosY = hueFrame->getHeight() + hueFrame->getPosition().y;						
						
		hueSelector->setPositionY(newPosY);
					
		Number newHue = 360.0 - (((newPosY-hueFrame->getPosition().y)/((hueFrame->getPosition().y+hueFrame->getHeight())-hueFrame->getPosition().y)) * 360.0f);
		setHue(newHue);
	}
}

void UIColorPicker::Update() {	
	if (continuous) {
		if (mainSelector->isDragged())
			updateColorFromMainSelector();
		
		if (hueSelector->isDragged())
			updateColorFromHueSelector();
	}
	
	UIWindow::Update();
}

UIColorBox::UIColorBox(UIColorPicker *colorPicker, Color initialColor, Number width, Number height) : UIElement() {

	Config *conf = CoreServices::getInstance()->getConfig();	

	String frameImageFile = conf->getStringValue("Polycode", "uiColorBoxFrameImage");
	String bgImageFile = conf->getStringValue("Polycode", "uiColorBoxBgImage");
	Number frameInset = conf->getNumericValue("Polycode", "uiColorBoxFrameInset");

	Number st = conf->getNumericValue("Polycode", "uiColorBoxFrameImageT");
	Number sr = conf->getNumericValue("Polycode", "uiColorBoxFrameImageR");
	Number sb = conf->getNumericValue("Polycode", "uiColorBoxFrameImageB");
	Number sl = conf->getNumericValue("Polycode", "uiColorBoxFrameImageL");


	bgImage = new UIRect(width-(frameInset*2), height-(frameInset*2));
	bgImage->setAnchorPoint(-1.0, -1.0, 0.0);
	bgImage->loadTexture(bgImageFile);
	bgImage->setPosition(frameInset, frameInset);	
	addChild(bgImage);

	bgImage->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	bgImage->processInputEvents = true;

	colorShape = new UIRect(width-(frameInset*2), height-(frameInset*2));
    colorShape->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
	colorShape->setAnchorPoint(-1.0, -1.0, 0.0);
	colorShape->setPosition(frameInset, frameInset);
	addChild(colorShape);

		
	frameImage = new UIBox(frameImageFile, st,sr,sb,sl, width, height);	
	addChild(frameImage);
	
	this->colorPicker = colorPicker;	
	colorPicker->addEventListener(this, Event::CHANGE_EVENT);	
	colorPicker->addEventListener(this, Event::CANCEL_EVENT);
	
	setWidth(width);
	setHeight(height);
	
	selectedColor = initialColor;
	colorShape->color = selectedColor;	
			
	listeningToPicker = false;
}

Color UIColorBox::getSelectedColor() {
	return selectedColor;
}

UIColorBox::~UIColorBox() {
	colorPicker->removeAllHandlersForListener(this);
	
	if(!ownsChildren) {
		delete bgImage;
		delete colorShape;
		delete frameImage;
	}
}

void UIColorBox::setBoxColor(Color newColor) {
	selectedColor = newColor;
	colorShape->color = selectedColor;
	if(listeningToPicker) {
		colorPicker->setPickerColor(newColor);	
	}
}

void UIColorBox::showColorPicker() {
	colorPicker->visible = true;
	colorPicker->enabled = true;
	colorPicker->cancelColorListeners();
	colorPicker->setPickerColor(selectedColor);
	listeningToPicker = true;
}
		
void UIColorBox::handleEvent(Event *event) {

	if(event->getDispatcher() == colorPicker && event->getEventType() == "") {
		switch(event->getEventCode()) {
			case Event::CANCEL_EVENT:
				listeningToPicker = false;
			break;
			case Event::CHANGE_EVENT:
				if(listeningToPicker) {
					selectedColor = colorPicker->getSelectedColor();
					colorShape->color = selectedColor;
					dispatchEvent(new UIEvent(), UIEvent::CHANGE_EVENT);
				}
			break;
		}		
	}

	if(event->getDispatcher() == bgImage) {
		switch(event->getEventCode()) {
			case InputEvent::EVENT_MOUSEDOWN:
				showColorPicker();
			break;
		}
	}
}
