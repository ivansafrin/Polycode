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
 
#include "ExportProjectWindow.h"
#include "PolycodeFrame.h"

extern PolycodeFrame *globalFrame;

ExportProjectWindow::ExportProjectWindow() : UIWindow(L"Publish Project", 400, 360) {

	closeOnEscape = true;

	ScreenLabel *label = new ScreenLabel("LOCATION", 22, "section", Label::ANTIALIAS_FULL);
	addChild(label);
	label->color.a = 0.4;
	label->setPosition(padding, 50);

	projectLocationInput = new UITextInput(false, 420-(padding*2.0), 12);
	addChild(projectLocationInput);
	projectLocationInput->setPosition(padding, 80);


	locationSelectButton = new UIButton(L"Choose...", 100);
	locationSelectButton->addEventListener(this, UIEvent::CLICK_EVENT);
	addChild(locationSelectButton);
	locationSelectButton->setPosition(padding, projectLocationInput->getPosition().y+projectLocationInput->getHeight()+5);


	label = new ScreenLabel("PLATFORMS", 22, "section", Label::ANTIALIAS_FULL);
	addChild(label);
	label->color.a = 0.4;
	label->setPosition(padding, 150);

	macCheckBox = new UICheckBox("MacOS X (Intel 64-bit)", false);
	addChild(macCheckBox);
	macCheckBox->setPosition(padding, 185);

	winCheckBox = new UICheckBox("Microsoft Windows (32-bit)", false);
	addChild(winCheckBox);
	winCheckBox->setPosition(padding, 205);

	linCheckBox = new UICheckBox("Linux (Intel 32-bit)", false);
	addChild(linCheckBox);
	linCheckBox->setPosition(padding, 225);

	label = new ScreenLabel("OPTIONS", 22, "section", Label::ANTIALIAS_FULL);
	addChild(label);
	label->color.a = 0.4;
	label->setPosition(padding, 260);

	compileCheckBox = new UICheckBox("Compile Scripts (experimental)", false);
	addChild(compileCheckBox);
	compileCheckBox->setPosition(padding, 295);

	cancelButton = new UIButton(L"Cancel", 100);
	cancelButton->addEventListener(this, UIEvent::CLICK_EVENT);
	addChild(cancelButton);
	cancelButton->setPosition(400-75-padding-100-10, 360-15);


	okButton = new UIButton(L"Publish", 100);
	okButton->addEventListener(this, UIEvent::CLICK_EVENT);
	addChild(okButton);
	okButton->setPosition(400-75-padding, 360-15);

	projectLocationInput->setText(CoreServices::getInstance()->getCore()->getUserHomeDirectory()+"/Documents/Polycode");

}

ExportProjectWindow::~ExportProjectWindow() {

}

void ExportProjectWindow::resetForm() {
/*
	projectLocationInput->setText(CoreServices::getInstance()->getCore()->getUserHomeDirectory()+"/Documents/Polycode");
	macCheckBox->setChecked(false);
	winCheckBox->setChecked(false);
	linCheckBox->setChecked(false);	
*/
}

void ExportProjectWindow::handleEvent(Event *event) {
	if(event->getEventType() == "UIEvent") {
		if(event->getEventCode() == UIEvent::OK_EVENT && event->getDispatcher() == globalFrame->fileDialog) {
			String pathName = globalFrame->fileDialog->getSelection();
			if(pathName != "")
				projectLocationInput->setText(pathName);

		}

		if(enabled) {

		if(event->getEventCode() == UIEvent::CLICK_EVENT) {
			if(event->getDispatcher() == okButton) {
				dispatchEvent(new UIEvent(), UIEvent::OK_EVENT);
			}

			if(event->getDispatcher() == cancelButton) {
				dispatchEvent(new UIEvent(), UIEvent::CLOSE_EVENT);
			}

			if(event->getDispatcher() == locationSelectButton) {
#ifdef USE_POLYCODEUI_FILE_DIALOGS
				std::vector<String> exts;
				globalFrame->showFileBrowser(CoreServices::getInstance()->getCore()->getUserHomeDirectory(),  true, exts, false);
				globalFrame->fileDialog->addEventListener(this, UIEvent::OK_EVENT);
#else
				String pathName = CoreServices::getInstance()->getCore()->openFolderPicker();
				if(pathName != "")
					projectLocationInput->setText(pathName);
#endif
			}

		}

		}
	}

	UIWindow::handleEvent(event);
}
