/*
 Copyright (C) 2013 by Isak Andersson
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#include "SettingsWindow.h"

#include "PolycodeFrame.h"
extern PolycodeFrame *globalFrame;

SettingsWindow::SettingsWindow() : UIWindow(L"Settings", SETTINGS_WINDOW_WIDTH, SETTINGS_WINDOW_HEIGHT) {

	closeOnEscape = true;


	ScreenLabel *label = new ScreenLabel("MISC", 22, "section", Label::ANTIALIAS_FULL);
	addChild(label);
	label->color.a = 0.4;
	label->setPosition(padding, 50);


	useExternalTextEditorBox = new UICheckBox("Use external text editor?", false);
	addChild(useExternalTextEditorBox); 
	useExternalTextEditorBox->setPosition(padding, 85);

	#define BUTTON_WIDTH 80
	#define BUTTON_PADDING 10
	#define EDITOR_BROWSE_POS 110
	#define TEXTBOX_HEIGHT 12

	externalTextEditorCommand = new UITextInput(false, SETTINGS_WINDOW_WIDTH - (padding*2 + BUTTON_WIDTH + BUTTON_PADDING/2), TEXTBOX_HEIGHT);
	addChild(externalTextEditorCommand);
	externalTextEditorCommand->setPosition(padding, EDITOR_BROWSE_POS);

	browseButton = new UIButton("Browse...", BUTTON_WIDTH);
	browseButton->addEventListener(this, UIEvent::CLICK_EVENT);
	addChild(browseButton);
	browseButton->setPosition(SETTINGS_WINDOW_WIDTH - (2*padding + BUTTON_WIDTH/2), EDITOR_BROWSE_POS);
	

	cancelButton = new UIButton("Cancel", BUTTON_WIDTH);
	cancelButton->addEventListener(this, UIEvent::CLICK_EVENT);
	addChild(cancelButton);
	cancelButton->setPosition(SETTINGS_WINDOW_WIDTH - (2*padding + BUTTON_WIDTH*1.5 + BUTTON_PADDING), SETTINGS_WINDOW_HEIGHT - padding);

	okButton = new UIButton("OK", BUTTON_WIDTH);
	okButton->addEventListener(this, UIEvent::CLICK_EVENT);
	addChild(okButton);
	okButton->setPosition(SETTINGS_WINDOW_WIDTH - (2*padding + BUTTON_WIDTH/2), SETTINGS_WINDOW_HEIGHT - padding);
}

void SettingsWindow::handleEvent(Event *event) {
	if(event->getEventType() == "UIEvent") {
		if(event->getEventCode() == UIEvent::CLICK_EVENT) {
			if(event->getDispatcher() == okButton) {
				dispatchEvent(new UIEvent(), UIEvent::OK_EVENT);
			}

			if(event->getDispatcher() == cancelButton) {
				dispatchEvent(new UIEvent(), UIEvent::CLOSE_EVENT);
			}

			if(event->getDispatcher() == browseButton) {
#ifdef USE_POLYCODEUI_FILE_DIALOGS
				std::vector<String> extensions;
				extensions.push_back("");
				globalFrame->showFileBrowser(CoreServices::getInstance()->getCore()->getUserHomeDirectory(), false, extensions, false);
				globalFrame->fileDialog->addEventListener(this, UIEvent::OK_EVENT);
#else
				vector<CoreFileExtension> extensions;
				CoreFileExtension ext;
#ifdef _WINDOWS
				ext.extension = "exe"
#else
				ext.extension = "";
#endif
				ext.description = "executable";
				extensions.push_back(ext);
				std::vector<String> path = CoreServices::getInstance()->getCore()->openFilePicker(extensions, false);

				if(path.size == 0) {
					return;
				}

				if(path[0] != "") {
					externalTextEditorCommand->setText(path[0]);
				}
#endif	
			}
			// FIXME: Event never comes here even though we are listening to it.
			if(event->getDispatcher() == globalFrame->fileDialog && event->getEventCode() == UIEvent::OK_EVENT) {
				String path = globalFrame->fileDialog->getSelection();
				if (path != "") {
					externalTextEditorCommand->setText(path);
				}
			}
		}
	}

	UIWindow::handleEvent(event); 
} 

void SettingsWindow::updateUI() {
	Config *config = CoreServices::getInstance()->getConfig();
	
	useExternalTextEditorBox->setChecked(config->getStringValue("Polycode", "useExternalTextEditor") == "true");
	externalTextEditorCommand->setText(config->getStringValue("Polycode", "externalTextEditorCommand"));
}
	
SettingsWindow::~SettingsWindow() {
}
