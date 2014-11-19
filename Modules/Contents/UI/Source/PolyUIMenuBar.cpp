
#include "PolyUIMenuBar.h"
#include "PolyLabel.h"
#include <PolyCoreServices.h>
#include <PolyCore.h>
#include <PolyConfig.h>
#include <PolyRenderer.h>

using namespace Polycode;

UIMenuBarEntryItem::UIMenuBarEntryItem(String name, String code, PolyKEY shortCut1, PolyKEY shortCut2) {
	this->name = name;
	this->code = code;
	this->shortCut1 = shortCut1;
	this->shortCut2 = shortCut2;
}

bool UIMenuBarEntryItem::checkShortCut(PolyKEY shortCut) {
	if(shortCut1 == KEY_UNKNOWN && shortCut2 == KEY_UNKNOWN)
		return false;

	if(CoreServices::getInstance()->getCore()->getInput()->getKeyState(KEY_RCTRL) || CoreServices::getInstance()->getCore()->getInput()->getKeyState(KEY_LCTRL)) {
		if(shortCut1 != KEY_UNKNOWN && shortCut2 != KEY_UNKNOWN) {
			if(shortCut == shortCut1 && CoreServices::getInstance()->getCore()->getInput()->getKeyState(shortCut2)) {
				return true;
			}
			if(shortCut == shortCut2 && CoreServices::getInstance()->getCore()->getInput()->getKeyState(shortCut1)) {
				return true;
			}
		} else {
			if(shortCut == shortCut1) {
				return true;
			}
		}
	}

	return false;
}

UIMenuBarEntry::UIMenuBarEntry(String name): UIElement() {
	
	label = new SceneLabel(name, 14, "sans");
	setWidth(label->getLabel()->getTextWidth() + 20);
	label->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
	bg = new UIRect(getWidth(), 25);
	bg->setAnchorPoint(-1.0, -1.0, 0.0);
	addChild(bg);
	bg->processInputEvents = true;
	bg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiMenuBarBgColor"));
	addChild(label);
	label->setPosition(10, 5);
}

void UIMenuBarEntry::Select() {
	bg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiAccentColor"));
}

void UIMenuBarEntry::Deselect() {
	bg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiMenuBarBgColor"));
}

void UIMenuBarEntry::addItem(String name, String code, PolyKEY shortCut1, PolyKEY shortCut2) {
	items.push_back(UIMenuBarEntryItem(name,code, shortCut1, shortCut2));
}

UIMenuBarEntry::~UIMenuBarEntry() {
	delete bg;
	delete label;
}

UIMenuBar::UIMenuBar(int width, UIGlobalMenu *globalMenu) : UIElement() {
	Config *conf = CoreServices::getInstance()->getConfig();

	this->globalMenu = globalMenu;

	bgShape = new UIRect(width, 25);
	addChild(bgShape);
	Color bgColor = new Color();
	bgColor.setColorHexFromString(conf->getStringValue("Polycode", "uiMenuBarBgColor"));
	bgShape->setColor(bgColor);
	bgShape->setAnchorPoint(-1.0, -1.0, 0.0);
	entryOffset = 0;

	currentEntry = NULL;
	dropMenu = NULL;

	holdingMouse = false;

	CoreServices::getInstance()->getCore()->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
}

UIMenuBarEntry *UIMenuBar::addMenuBarEntry(String name) {
	UIMenuBarEntry *newEntry = new UIMenuBarEntry(name);
	entries.push_back(newEntry);
	addChild(newEntry);
	newEntry->setPosition(entryOffset, 0);
	entryOffset += newEntry->getWidth();

	newEntry->bg->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	newEntry->bg->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	newEntry->bg->addEventListener(this, InputEvent::EVENT_MOUSEUP_OUTSIDE);
	newEntry->bg->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);

	return newEntry;
}

void UIMenuBar::showMenuForEntry(UIMenuBarEntry *entry) {
	dropMenu = globalMenu->showMenu(entry->getPosition().x, 25, 130);
	
	dropMenu->addEventListener(this, UIEvent::OK_EVENT);
	dropMenu->addEventListener(this, UIEvent::CANCEL_EVENT);

	for(int i=0; i < entry->items.size(); i++) {
		dropMenu->addOption(entry->items[i].name, entry->items[i].code);
	}

	if(currentEntry) {
		currentEntry->Deselect();
	}
	entry->Select();
	currentEntry = entry;
}

String UIMenuBar::getSelectedItem() {
	return selectedItem;
}

void UIMenuBar::handleEvent(Event *event) {

	if(event->getDispatcher() == CoreServices::getInstance()->getCore()->getInput()) {
		InputEvent *inputEvent = (InputEvent*) event;
		if(event->getEventCode() == InputEvent::EVENT_KEYDOWN) {
			for(int i=0; i < entries.size(); i++) {
				UIMenuBarEntry *entry = entries[i];
				for(int j=0; j < entry->items.size(); j++) {
					if(entry->items[j].checkShortCut(inputEvent->key)) {
						selectedItem = entry->items[j].code;
						dispatchEvent(new UIEvent(), UIEvent::OK_EVENT);
						break;
					}
				}
			}
		}
	}

	if(event->getDispatcher() == dropMenu) {
		if(event->getEventCode() == UIEvent::OK_EVENT) {
			selectedItem = dropMenu->getSelectedItem()->_id;
			dispatchEvent(new UIEvent(), UIEvent::OK_EVENT);
		}

		if(currentEntry) {
			currentEntry->Deselect();
			currentEntry = NULL;
			dropMenu = NULL;
		}
	}

	for(int i=0; i < entries.size(); i++) {
		if(event->getDispatcher() == entries[i]->bg) {
			switch(event->getEventCode()) {
				case InputEvent::EVENT_MOUSEMOVE:
					if(entries[i] != currentEntry && dropMenu) {
						showMenuForEntry(entries[i]);
					}
				break;
				case InputEvent::EVENT_MOUSEUP:
				case InputEvent::EVENT_MOUSEUP_OUTSIDE:
					holdingMouse = false;
				break;
				case InputEvent::EVENT_MOUSEDOWN:
					holdingMouse = true;
					showMenuForEntry(entries[i]);
				break;
			}
		}
	}
}

UIMenuBar::~UIMenuBar() {
	if(!ownsChildren) {
		delete bgShape;
	}
}

void UIMenuBar::Resize(Number width, Number height) {
	bgShape->Resize(width, 25);
}
