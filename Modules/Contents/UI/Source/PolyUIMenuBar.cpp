
#include "PolyUIMenuBar.h"
#include "PolyLabel.h"

using namespace Polycode;

UIMenuBarEntry::UIMenuBarEntry(String name): UIElement() {
	
	label = new ScreenLabel(name, 14, "sans");
	setWidth(label->getLabel()->getTextWidth() + 20);
	bg = new ScreenShape(ScreenShape::SHAPE_RECT, width, 25);
	bg->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	addChild(bg);
	bg->color.setColorHex(0xce5a1600);
	bg->processInputEvents = true;
	addChild(label);
	label->setPosition(10, 5);
}

void UIMenuBarEntry::Select() {
	bg->color.setColorHex(0xce5a16ff);
}

void UIMenuBarEntry::Deselect() {
	bg->color.setColorHex(0xce5a1600);
}

void UIMenuBarEntry::addItem(String name, String code) {
	items.push_back(UIMenuBarEntryItem(name,code));
}

UIMenuBarEntry::~UIMenuBarEntry() {
	delete bg;
	delete label;
}

UIMenuBar::UIMenuBar(int width, UIGlobalMenu *globalMenu) : UIElement() {

	this->globalMenu = globalMenu;

	bgShape = new ScreenShape(ScreenShape::SHAPE_RECT, width, 25);
	addChild(bgShape);
	bgShape->setColor(0.0, 0.0, 0.0, 1.0);
	bgShape->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	entryOffset = 0;

	currentEntry = NULL;
	dropMenu = NULL;

	holdingMouse = false;
}

UIMenuBarEntry *UIMenuBar::addMenuBarEntry(String name) {
	UIMenuBarEntry *newEntry = new UIMenuBarEntry(name);
	entries.push_back(newEntry);
	addChild(newEntry);
	newEntry->setPosition(entryOffset, 0);
	entryOffset += newEntry->width;

	newEntry->bg->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	newEntry->bg->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	newEntry->bg->addEventListener(this, InputEvent::EVENT_MOUSEUP_OUTSIDE);
	newEntry->bg->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);

	return newEntry;
}

void UIMenuBar::showMenuForEntry(UIMenuBarEntry *entry) {
	dropMenu = globalMenu->showMenu(entry->position.x, 25, 130);
	
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
	delete bgShape;
}

void UIMenuBar::Resize(Number width, Number height) {
	bgShape->setShapeSize(width, 25);
}
