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

#include "polycode/ide/SettingsWindow.h"
#include "polycode/ide/PolycodeFrame.h"
#include "polycode/ide/PolycodeTextEditor.h"

extern PolycodeFrame *globalFrame;
extern UIGlobalMenu *globalMenu;
extern SyntaxHighlightTheme *globalSyntaxTheme;

SettingsWindow::SettingsWindow(Core *core, ResourcePool *pool) : UIWindow(core, pool, L"Settings", SETTINGS_WINDOW_WIDTH, SETTINGS_WINDOW_HEIGHT) {

	closeOnEscape = true;

	UILabel *label = new UILabel(core, pool, "TEXT EDITING", 22, "section", Label::ANTIALIAS_FULL);
	addChild(label);
	label->color.a = 1.0;
	label->setPosition(padding, 50);

	useExternalTextEditorBox = new UICheckBox(core, pool, "Use external text editor", false);
	addChild(useExternalTextEditorBox); 
	useExternalTextEditorBox->setPosition(padding, 85);

	#define BUTTON_WIDTH 80
	#define BUTTON_PADDING 10
	#define EDITOR_BROWSE_POS 110
	#define TEXTBOX_HEIGHT 12

	externalTextEditorCommand = new UITextInput(core, pool, false, SETTINGS_WINDOW_WIDTH - (padding*2 + BUTTON_WIDTH + BUTTON_PADDING/2), TEXTBOX_HEIGHT);
	addChild(externalTextEditorCommand);
	externalTextEditorCommand->setPosition(padding, EDITOR_BROWSE_POS);
	
	
	label = new UILabel(core, pool, "Syntax highlighting theme", 12);
	addChild(label);
	label->color.a = 1.0;
	label->setPosition(padding, EDITOR_BROWSE_POS + 35);
	
	syntaxThemeBox = new UIComboBox(core, pool, globalMenu, 300);
	addChild(syntaxThemeBox);
	syntaxThemeBox->setPosition(padding, EDITOR_BROWSE_POS + 55);
	syntaxThemeBox->addEventListener(this, UIEvent::CHANGE_EVENT);
	
	std::vector<OSFileEntry> themes = core->parseFolder(core->getDefaultWorkingDirectory() + "/SyntaxThemes", false);
	
	for(int i=0; i < themes.size(); i++) {
		if(themes[i].extension == "xml") {
			syntaxThemeBox->addComboItem(themes[i].nameWithoutExtension);
		}
	}

	browseButton = new UIButton(core, pool, "Browse...", BUTTON_WIDTH);
	browseButton->addEventListener(this, UIEvent::CLICK_EVENT);
	addChild(browseButton);
	browseButton->setPosition(SETTINGS_WINDOW_WIDTH - (2*padding + BUTTON_WIDTH/2), EDITOR_BROWSE_POS);
	
	
	label = new UILabel(core, pool, "GENERAL", 22, "section", Label::ANTIALIAS_FULL);
	addChild(label);
	label->color.a = 1.0;
	label->setPosition(padding, 200);

	label = new UILabel(core, pool, "UI theme (requires restart)", 12);
	addChild(label);
	label->color.a = 1.0;
	label->setPosition(padding, 235);

	uiThemeBox = new UIComboBox(core, pool, globalMenu, 300);
	addChild(uiThemeBox);
	uiThemeBox->setPosition(padding, 255);
	uiThemeBox->addEventListener(this, UIEvent::CHANGE_EVENT);
	
	std::vector<OSFileEntry> uiThemes = core->parseFolder(core->getDefaultWorkingDirectory() + "/UIThemes", false);
	
	for(int i=0; i < uiThemes.size(); i++) {
		if(uiThemes[i].type == OSFileEntry::TYPE_FOLDER) {
			
			// do not list retina theme copies
			if(uiThemes[i].name.find("_retina") == -1) {
				uiThemeBox->addComboItem(uiThemes[i].name);
				if(uiThemes[i].name == core->getConfig()->getStringValue("Polycode", "uiTheme")) {
					uiThemeBox->setSelectedIndex(i);
				}
			}
		}
	}

	label = new UILabel(core, pool, "Texture filtering (requires restart)", 12);
	addChild(label);
	label->color.a = 1.0;
	label->setPosition(padding, 285);

	textureFilteringBox = new UIComboBox(core, pool, globalMenu, 300);
	addChild(textureFilteringBox);
	textureFilteringBox->setPosition(padding, 305);
	textureFilteringBox->addEventListener(this, UIEvent::CHANGE_EVENT);
	textureFilteringBox->addComboItem("Linear");
	textureFilteringBox->addComboItem("Nearest");
	
	cancelButton = new UIButton(core, pool, "Cancel", BUTTON_WIDTH);
	cancelButton->addEventListener(this, UIEvent::CLICK_EVENT);
	addChild(cancelButton);
	cancelButton->setPosition(SETTINGS_WINDOW_WIDTH - (2*padding + BUTTON_WIDTH*1.5 + BUTTON_PADDING), SETTINGS_WINDOW_HEIGHT - padding);

	okButton = new UIButton(core, pool, "OK", BUTTON_WIDTH);
	okButton->addEventListener(this, UIEvent::CLICK_EVENT);
	addChild(okButton);
	okButton->setPosition(SETTINGS_WINDOW_WIDTH - (2*padding + BUTTON_WIDTH/2), SETTINGS_WINDOW_HEIGHT - padding);
}

void SettingsWindow::handleEvent(Event *event) {
	if(event->getEventType() == "UIEvent") {
		if(event->getEventCode() == UIEvent::CHANGE_EVENT) {
			if(event->getDispatcher() == syntaxThemeBox) {
				if(syntaxThemeBox->getSelectedItem()->label != globalSyntaxTheme->name) {
					globalSyntaxTheme->loadFromFile(core, syntaxThemeBox->getSelectedItem()->label);
				}
			}
		} else if(event->getEventCode() == UIEvent::CLICK_EVENT) {
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
				globalFrame->showFileBrowser(core->getUserHomeDirectory(), false, extensions, false);
				globalFrame->fileDialog->addEventListener(this, UIEvent::OK_EVENT);
#else
				vector<CoreFileExtension> extensions;
				CoreFileExtension ext;
#ifdef _WINDOWS
				ext.extension = "exe";
#elif defined(__APPLE__) && defined(__MACH__)
				ext.extension = "app";
#else
				ext.extension = "";
#endif
				ext.description = "executable";
				extensions.push_back(ext);
				std::vector<String> path = core->openFilePicker(extensions, false);

				if(path.size() == 0) {
					return;
				}

				if(path[0] != "") {
					externalTextEditorCommand->setText(path[0]);
				}
#endif	
			}
		}

		if(event->getDispatcher() == globalFrame->fileDialog && event->getEventCode() == UIEvent::OK_EVENT) {
			String path = globalFrame->fileDialog->getSelection();
			if (path != "") {
				externalTextEditorCommand->setText(path);
			}
		}
	}

	UIWindow::handleEvent(event); 
} 

void SettingsWindow::updateUI() {
	ConfigRef config = core->getConfig();
	
	useExternalTextEditorBox->setChecked(config->getStringValue("Polycode", "useExternalTextEditor") == "true");
	externalTextEditorCommand->setText(config->getStringValue("Polycode", "externalTextEditorCommand"));
	
	for(int i=0; i < syntaxThemeBox->getNumItems(); i++) {
		if(globalSyntaxTheme->name == syntaxThemeBox->getItemAtIndex(i)->label) {
			syntaxThemeBox->setSelectedIndex(i);
		} 
	}

	for(int i=0; i < uiThemeBox->getNumItems(); i++) {
		if(config->getStringValue("Polycode", "uiTheme") == uiThemeBox->getItemAtIndex(i)->label) {
			uiThemeBox->setSelectedIndex(i);
		} 
	}
	
	if(config->getStringValue("Polycode", "textureFilteringMode") == "nearest") {
		textureFilteringBox->setSelectedIndex(1);
	} else {
		textureFilteringBox->setSelectedIndex(0);	
	}
	
}
	
SettingsWindow::~SettingsWindow() {
}
