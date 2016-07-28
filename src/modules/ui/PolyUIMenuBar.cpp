
#include "polycode/modules/ui/PolyUIMenuBar.h"
#include "polycode/core/PolyLabel.h"
#include <polycode/core/PolyCore.h>
#include <polycode/core/PolyConfig.h>
#include <polycode/core/PolyRenderer.h>

using namespace Polycode;

UIMenuBarEntryItem::UIMenuBarEntryItem(CoreInput *input, String name, String code, PolyKEY shortCut1, PolyKEY shortCut2) : input(input), name(name), code(code), shortCut1(shortCut1), shortCut2(shortCut2)
{
}

bool UIMenuBarEntryItem::checkShortCut(PolyKEY shortCut) {
	if(shortCut1 == KEY_UNKNOWN && shortCut2 == KEY_UNKNOWN)
		return false;

	if(input->getKeyState(KEY_RCTRL) || input->getKeyState(KEY_LCTRL)) {
		if(shortCut1 != KEY_UNKNOWN && shortCut2 != KEY_UNKNOWN) {
			if(shortCut == shortCut1 && input->getKeyState(shortCut2)) {
				return true;
			}
			if(shortCut == shortCut2 && input->getKeyState(shortCut1)) {
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

UIMenuBarEntry::UIMenuBarEntry(Core *core, ResourcePool *pool, String name, const Color &accentColor, const Color &bgColor): UIElement(core), accentColor(accentColor), bgColor(bgColor)
{
	label = new SceneLabel(pool->getMaterial("Unlit"), name, 14, pool->getFont("sans"));
	setWidth(label->getLabel()->getTextWidth() + 20);
	label->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
	bg = new UIRect(core, pool, getWidth(), 25);
	bg->setAnchorPoint(-1.0, -1.0, 0.0);
	addChild(bg);
	bg->processInputEvents = true;
	bg->color = bgColor;
	addChild(label);
	label->setPosition(10, 5);
}

void UIMenuBarEntry::Select() {
	bg->color = accentColor;
}

void UIMenuBarEntry::Deselect() {
	bg->color = bgColor;
}

void UIMenuBarEntry::addItem(String name, String code, PolyKEY shortCut1, PolyKEY shortCut2) {
	items.push_back(UIMenuBarEntryItem(core->getInput(), name,code, shortCut1, shortCut2));
}

UIMenuBarEntry::~UIMenuBarEntry() {
	delete bg;
	delete label;
}

UIMenuBar::UIMenuBar(Core *core, ResourcePool *resourcePool, CoreInput *input, int width, UIGlobalMenu *globalMenu) : UIElement(core), input(input), resourcePool(resourcePool)
{
	this->globalMenu = globalMenu;

	ConfigRef conf = core->getConfig();
	
	bgShape = new UIRect(core, resourcePool, width, 25);
	addChild(bgShape);
	Color bgColor = new Color();
	bgColor.setColorHexFromString(conf->getStringValue("Polycode", "uiMenuBarBgColor"));
	bgShape->setColor(bgColor);
	bgShape->setAnchorPoint(-1.0, -1.0, 0.0);
	entryOffset = 0;

	currentEntry = NULL;
	dropMenu = NULL;

	holdingMouse = false;

	
	accentColor.setColorHexFromString(conf->getStringValue("Polycode", "uiAccentColor"));
	bgColor.setColorHexFromString(conf->getStringValue("Polycode", "uiMenuBarBgColor"));
	
	input->addEventListener(this, InputEvent::EVENT_KEYDOWN);
}

UIMenuBarEntry *UIMenuBar::addMenuBarEntry(String name) {
	UIMenuBarEntry *newEntry = new UIMenuBarEntry(core, resourcePool, name, accentColor, bgColor);
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

	if(event->getDispatcher() == input) {
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
	input->removeAllHandlersForListener(this);
}

void UIMenuBar::Resize(Number width, Number height) {
	bgShape->Resize(width, 25);
}
