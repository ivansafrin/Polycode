/*
 *  PolycodeFrame.cpp
 *  Polycode
 *
 *  Created by Ivan Safrin on 11/29/10.
 *  Copyright 2010 Local Projects. All rights reserved.
 *
 */

#include "PolycodeFrame.h"

PolycodeFrame::PolycodeFrame() : ScreenEntity() {

	modalChild = NULL;
	
	editorHolder = new ScreenEntity();
	addChild(editorHolder);
	
	
	projectBrowser = new PolycodeProjectBrowser();
	addChild(projectBrowser);
		
	topBarBg = new ScreenShape(ScreenShape::SHAPE_RECT, 2,2);
	topBarBg->setColor(0,0,0,1);
	topBarBg->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	addChild(topBarBg);
	
	logo = new ScreenImage("barlogo.png");	
	addChild(logo);		
	
	resizer = new ScreenImage("corner_resize.png");	
	addChild(resizer);
	resizer->setColor(0,0,0,0.4);
	
	modalBlocker = new ScreenShape(ScreenShape::SHAPE_RECT, 10,10);
	modalBlocker->setColor(0,0,0,0.5);
	modalBlocker->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	modalBlocker->enabled = false;	
	modalBlocker->blockMouseInput = true;
	addChild(modalBlocker);
	
	newProjectWindow = new NewProjectWindow();
	newProjectWindow->visible = false;
	
	newFileWindow = new NewFileWindow();
	newFileWindow->visible = false;
	
	currentEditor = NULL;
	
}

void PolycodeFrame::showModal(UIWindow *modalChild) {
	modalBlocker->enabled = true;
	
	this->modalChild = modalChild;
	addChild(modalChild);
	modalChild->showWindow();
	modalChild->addEventListener(this, UIEvent::CLOSE_EVENT);
	Resize(frameSizeX, frameSizeY);
}

PolycodeProjectBrowser *PolycodeFrame::getProjectBrowser() {
	return projectBrowser;
}

void PolycodeFrame::addEditor(PolycodeEditor *editor) {
	editors.push_back(editor);
	editorHolder->addChild(editor);
	editor->enabled = false;
}

void PolycodeFrame::showEditor(PolycodeEditor *editor) {
	if(currentEditor) {
		currentEditor->enabled = false;
		currentEditor = NULL;
	}
	
	currentEditor = editor;
	currentEditor->enabled = true;
	
	Resize(frameSizeX, frameSizeY);
}

void PolycodeFrame::hideModal() {
	if(modalChild) {
		modalChild->hideWindow();
		modalBlocker->enabled = false;	 
		modalChild = NULL;
	}
}

void PolycodeFrame::handleEvent(Event *event) {
	if(event->getDispatcher() == modalChild) {
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLOSE_EVENT) {
			hideModal();
		}
	}
}

void PolycodeFrame::Resize(int x, int y) {	
	
	frameSizeX = x;
	frameSizeY = y;
	
	topBarBg->setShapeSize(x, 45);
	logo->setPosition(x-logo->getWidth()-10, 6);	
	resizer->setPosition(x-resizer->getWidth()-1, y-resizer->getHeight()-1);	
	projectBrowser->Resize(200, y-45);
	modalBlocker->setShapeSize(x, y);
	
	editorHolder->setPosition(200, 45);
	
	if(currentEditor) {
		currentEditor->Resize(x-200, y-45);
	}
	
	if(this->modalChild) {
		modalChild->setPosition((x-modalChild->getWidth())/2.0f, (y-modalChild->getHeight())/2.0f);
	}
}

PolycodeFrame::~PolycodeFrame() {
	
}

