/*
Copyright (C) 2014 by Joachim Meyer

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

#include "PolyUITab.h"
#include "PolyInputEvent.h"
#include "PolyCoreInput.h"
#include "PolyUIEvent.h"

using namespace Polycode;

UITab::UITab(String caption, UIElement *tabContent) : UIElement() {

	tabName = caption;
	

	button = new UITabButton(caption);

	this->content = tabContent;
	addChild(content);

	this->active = false;
}

void UITab::setActive(bool val) {
	this->active = val;
	
	content->visible = val;
	content->enabled = val;

	button->setActive(val);
}

bool UITab::isActive() {
	return active;
}

String UITab::getTabName() {
	return tabName;
}

UITabButton *UITab::getTabButton(){
	return button;
}

void UITab::setTabName(String newName) {
	tabName = newName;
}

void UITab::Resize(Number width, Number height) {
	content->Resize(width, height);
	UIElement::Resize(width, height);
}

UIElement *UITab::getContent() {
	return content;
}

void UITab::setContent(UIElement *newContent){
	this->content = newContent;
}

UITab::~UITab() {

}

UITabButton::UITabButton(String caption){
	bgRect = new UIImage("main/tab_bg.png", 75, 20);
	addChild(bgRect);
	bgRect->processInputEvents = true;
	processInputEvents = true;
	bgRect->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);

	setWidth(75);
	setHeight(20);

	tabLabel = new UILabel(caption.toUpperCase(), 16, "section");
	tabLabel->setColor(0.0, 0.0, 0.0, 1.0);
	tabLabel->setPosition(getWidth() - tabLabel->getWidth() - 10.0, ((getHeight() - tabLabel->getHeight()) / 2.0) - 3.0);
	addChild(tabLabel);
}

UITabButton::~UITabButton(){

}

void UITabButton::setActive(bool val){
	if (val) {
		bgRect->color.a = 0.4;
	} else {
		bgRect->color.a = 0.2;
	}
}

void UITabButton::handleEvent(Event *event){
	if (event->getDispatcher() == bgRect) {
		if (event->getEventCode() == InputEvent::EVENT_MOUSEDOWN) {
			dispatchEvent(new Event(), Event::SELECT_EVENT);
		}
	}
	UIElement::handleEvent(event);
}

void UITabButton::updateLabel(String caption){
	tabLabel->setText(caption.toUpperCase());
	tabLabel->setPosition(getWidth() - tabLabel->getWidth() - 10.0, ((getHeight() - tabLabel->getHeight()) / 2.0) - 3.0);
}

UITabFrame::UITabFrame(UITab *tab, Number width, Number height) : UIElement(width, height) {
	tabButtonAnchor = new UIElement();
	addChild(tabButtonAnchor);
	tabButtonAnchor->setPosition(5, 5);

	tabs.push_back(tab);
	tabButtonAnchor->addChild(tab->getTabButton());
	tabButtons.push_back(tab->getTabButton());
	tab->getTabButton()->addEventListener(this, Event::SELECT_EVENT);
	tab->setPositionY(tab->getTabButton()->getHeight() + 5);
	activeTab = tab;
}

void UITabFrame::handleEvent(Event *event) {
	for (int i = 0; i < tabButtons.size(); i++) {
		if (event->getDispatcher() == tabButtons[i]) {
			if (event->getEventCode() == Event::SELECT_EVENT) {
				showTab(tabs[i]);
				break;
			} else 	if (event->getEventCode() == UIEvent::CHANGE_EVENT) {
				dispatchEvent(new UIEvent(), UIEvent::CHANGE_EVENT);
				break;
			}
		}
		
	}
	
	UIElement::handleEvent(event);
}

void UITabFrame::showTab(UITab *tab) {
	if (activeTab) {
		activeTab->setActive(false);
		activeTab->removeAllHandlersForListener(this);
		removeChild(activeTab);
	}

	addChild(tab);
	tab->setActive(true);
	tab->Resize(getWidth(), getHeight());
	activeTab = tab;
	dispatchEvent(new UIEvent(), Event::CHANGE_EVENT);
}

void UITabFrame::showTab(unsigned int tabIndex) {
	if (tabIndex < tabs.size())
	{
		if (activeTab) {
			tabs.at(tabIndex)->setActive(false);
			activeTab->removeAllHandlersForListener(this);
			removeChild(activeTab);
		}

		tabs.at(tabIndex)->setActive(true);
		tabs.at(tabIndex)->Resize(getWidth(), getHeight());
		activeTab = tabs.at(tabIndex);

		addChild(tabs.at(tabIndex));
		dispatchEvent(new UIEvent(), Event::CHANGE_EVENT);
	}
}

UITab *UITabFrame::getTabAtIndex(unsigned int index) {
	return tabs[index];
}

unsigned int UITabFrame::getActiveTabIndex() {
	int i = 0;
	while (activeTab != tabs.at(i)){
		i++;
	}
	return i;
}

unsigned int UITabFrame::getTabIndex(UITab *tab) {
	int i = 0;
	while (tab != tabs.at(i)){
		i++;
	}
	return i;
}

unsigned int UITabFrame::getNumTabs() {
	return tabs.size();
}

UITab *UITabFrame::getActiveTab() {
	return activeTab;
}

std::vector<UITab *> UITabFrame::getTabs() {
	return tabs;
}

void UITabFrame::addNewTab(UITab *newTab){
	tabs.push_back(newTab);

	tabButtonAnchor->addChild(newTab->getTabButton());
	newTab->getTabButton()->setPositionX(tabButtons[tabButtons.size() - 1]->getPosition().x + tabButtons[tabButtons.size() - 1]->getWidth());
	tabButtons.push_back(newTab->getTabButton());
	newTab->getTabButton()->addEventListener(this, Event::SELECT_EVENT);
	newTab->setPositionY(newTab->getTabButton()->getHeight() + 5);
	showTab(newTab);
}

void UITabFrame::setTabButtonAnchorPosition(Vector2 _pos){
	tabButtonAnchor->setPosition(_pos.x, _pos.y);

}

void UITabFrame::setTabButtonAnchorPosition(Number x, Number y){
	tabButtonAnchor->setPosition(x, y);
}

Vector2 UITabFrame::getTabButtonAnchorPosition(){
	return tabButtonAnchor->getPosition2D();
}

void UITabFrame::Resize(Number width, Number height) {
	activeTab->Resize(width, height);
	UIElement::Resize(width, height);
}

UITabFrame::~UITabFrame() {

}