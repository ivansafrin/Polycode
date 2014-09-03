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

#include "PolycodePluginEditor.h"
#include "PolyPluginManager.h"

using namespace Polycode;

PluginBrowser::PluginBrowser() : UIElement() {
	treeContainer = new UITreeContainer("boxIcon.png", L"Polycode Plugins", 200, 555);
	treeContainer->getRootNode()->toggleCollapsed();
	treeContainer->getRootNode()->addEventListener(this, UITreeEvent::SELECTED_EVENT);
	treeContainer->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);

	pluginNode = treeContainer->getRootNode()->addTreeChild("materialEditor/plugin_icon.png", "Plugins", NULL);

	addChild(treeContainer);
	selectedData = NULL;

	headerBg = new UIRect(10, 10);
	addChild(headerBg);
	headerBg->setAnchorPoint(-1.0, -1.0, 0.0);
	headerBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));

	newPluginButton = new UIImageButton("materialEditor/new_plugin.png", 1.0, 22, 22);
	addChild(newPluginButton);
	newPluginButton->setPosition(5, 4);

	removeButton = new UIImageButton("main/remove_icon.png", 1.0, 12, 12);
	addChild(removeButton);
	removeButton->setPosition(0, 4);

	selectedNode = NULL;
}

PluginBrowser::~PluginBrowser() {}

void PluginBrowser::removeSelected() {
	selectedNode->getParent()->removeTreeChild(selectedNode);
}

void PluginBrowser::handleEvent(Event *event) {

	if (event->getDispatcher() == treeContainer->getRootNode()) {
		if (event->getEventCode() == UITreeEvent::SELECTED_EVENT) {
			selectedNode = treeContainer->getRootNode()->getSelectedNode();
			PluginBrowserData *data = (PluginBrowserData *)selectedNode->getUserData();
			selectedData = data;
			dispatchEvent(new Event(), Event::CHANGE_EVENT);
		}
	}
	Entity::handleEvent(event);
}


UITree *PluginBrowser::addPlugin(Plugin *plugin) {
	PluginBrowserData *data = new PluginBrowserData();
	data->plugin = plugin;
	return pluginNode->addTreeChild("materialEditor/material_icon.png", plugin->getResourceName(), (void*)data);
}

void PluginBrowser::Resize(Number width, Number height) {
	treeContainer->Resize(width, height - 30);
	treeContainer->setPosition(0, 30);
	headerBg->Resize(width, 30);
	removeButton->setPosition(width - 24, 8);
}


PluginEditorPane::PluginEditorPane(ResourcePool *resourcePool) : UIElement() {

	this->resourcePool = resourcePool;
	changingPlugin = false;
	currentPlugin = NULL;

	headerBg = new UIRect(10, 10);
	addChild(headerBg);
	headerBg->setAnchorPoint(-1.0, -1.0, 0.0);
	headerBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));

	propList = new PropList("PLUGIN EDITOR");
	addChild(propList);
	propList->setPosition(0, 0);

	PropSheet *baseProps = new PropSheet("PLUGIN SETTINGS", "");
	propList->addPropSheet(baseProps);

	nameProp = new StringProp("Name");
	baseProps->addProp(nameProp);
	nameProp->addEventListener(this, Event::CHANGE_EVENT);

	addPropButton = new ButtonProp("New Prop");
	baseProps->addProp(addPropButton);
	addPropButton->getButton()->addEventListener(this, UIEvent::CLICK_EVENT);

	baseProps->propHeight = 220;

	propsSheet = new PropSheet("PROPS", "");
	propList->addPropSheet(propsSheet);

	propList->updateProps();

	enabled = false;
}

PluginEditorPane::~PluginEditorPane() {

}

void PluginEditorPane::handleEvent(Event *event) {
	if (!changingPlugin) {

		if (event->getDispatcher() == nameProp) {
			currentPlugin->setResourceName(nameProp->get());
			dispatchEvent(new Event(), Event::CHANGE_EVENT);
		}

		int maxPadding = 0;
		for (int p = 0; p < propsSheet->props.size(); p++){
			if (event->getDispatcher() == propsSheet->props[p]) {
				dispatchEvent(new Event(), Event::CHANGE_EVENT);
			}
			if (((PropEditProp*)propsSheet->props[p])->updatePadding() > maxPadding){
				maxPadding = ((PropEditProp*)propsSheet->props[p])->updatePadding();
			}
		}

		padding = maxPadding;

		if (padding < (propList->getWidth() - 320)){
			for (int p = 0; p < propsSheet->props.size(); p++){
				propsSheet->props[p]->propContents->setPositionX(padding + 20);
			}
		}

		if (event->getDispatcher() == addPropButton->getButton()) {
			PropEditProp *newProp = new PropEditProp(new PropProp("", 0));
			propsSheet->addProp(newProp);
			newProp->addEventListener(this, Event::CHANGE_EVENT);
			newProp->propContents->setPositionX(padding + 20);
			dispatchEvent(new Event(), Event::CHANGE_EVENT);
		}
	}
}

void PluginEditorPane::setPlugin(Plugin *plugin) {
	changingPlugin = true;

	currentPlugin = plugin;

	nameProp->set(plugin->getResourceName());

	ObjectEntry *propsEntry = (*plugin->sheetEntry)["props"];
	if (propsEntry) {
		for (int p = 0; p < propsEntry->children.size(); p++) {
			ObjectEntry* propEntry = (*propsEntry)[p];
			if (propEntry && propEntry->name == "prop") {
				setProp((*propEntry)["name"]->stringVal, new PropProp((*propEntry)["name"]->stringVal, (*propEntry)["type"]->intVal));
			}
		}
	}
	
	for (int p = 0; p < propsSheet->props.size(); p++){
		propsSheet->props[p]->propContents->setPositionX(padding + 20);
	}

	enabled = true;

	changingPlugin = false;
}

void PluginEditorPane::Resize(Number width, Number height) {
	headerBg->Resize(width, 30);
	propList->Resize(width, height);
	propList->updateProps();
	
}

std::vector<PropProp*> PluginEditorPane::getProps() {
	return propsSheet->props;
}

void PluginEditorPane::setProp(const String& name, PropProp* prop){
	for (int i = 0; i < propsSheet->props.size(); i++) {
		if (propsSheet->props[i]->getPropName() == name) {
			PropEditProp *newProp = new PropEditProp(prop);
			if (((PropEditProp*)newProp)->updatePadding() > padding)
				padding = ((PropEditProp*)newProp)->updatePadding();
			newProp->addEventListener(this, Event::CHANGE_EVENT);
			return;
		}
	}

	PropEditProp *newProp = new PropEditProp(prop);
	if (((PropEditProp*)newProp)->updatePadding() > padding)
		padding = ((PropEditProp*)newProp)->updatePadding();
	propsSheet->addProp(newProp);
	newProp->addEventListener(this, Event::CHANGE_EVENT);
}

PluginMainWindow::PluginMainWindow(ResourcePool *resourcePool) : UIElement() {

	pluginPane = new PluginEditorPane(resourcePool);

	ownsChildren = true;

	addChild(pluginPane);
}

PluginMainWindow::~PluginMainWindow() {}

void PluginMainWindow::Resize(Number width, Number height) {
	Vector2 pos = getScreenPositionForMainCamera();
	scissorBox.setRect(pos.x, pos.y, width, height);
	pluginPane->Resize(width, height);
}

PolycodePluginEditor::PolycodePluginEditor() : PolycodeEditor(true) {
	selectedPluginNode = NULL;
}

PolycodePluginEditor::~PolycodePluginEditor() {
	delete resourcePool;

	mainWindow->setOwnsChildrenRecursive(true);
	delete mainWindow;
	delete mainSizer;
	delete pluginBrowser;
}

bool PolycodePluginEditor::openFile(OSFileEntry filePath) {
	this->filePath = filePath;

	mainSizer = new UIHSizer(100, 100, 200, false);
	addChild(mainSizer);

	pluginBrowser = new PluginBrowser();
	mainSizer->addRightChild(pluginBrowser);

	pluginBrowser->addEventListener(this, Event::CHANGE_EVENT);
	
	String resourceName = filePath.fullPath.replace(parentProject->getRootFolder() + "/", "");

	resourcePool = CoreServices::getInstance()->getResourceManager()->getResourcePoolByName(resourceName);

	if (!resourcePool) {
		resourcePool = new ResourcePool(resourceName, CoreServices::getInstance()->getResourceManager()->getGlobalPool());
		resourcePool->reloadResourcesOnModify = true;
		resourcePool->deleteOnUnsubscribe = true;
		CoreServices::getInstance()->getPluginManager()->loadPluginLibraryIntoPool(resourcePool, filePath.fullPath);
		CoreServices::getInstance()->getResourceManager()->addResourcePool(resourcePool);
	}

	CoreServices::getInstance()->getResourceManager()->subscribeToResourcePool(resourcePool);

	mainWindow = new PluginMainWindow(resourcePool);
	mainSizer->addLeftChild(mainWindow);

	for (int i = 0; i < resourcePool->getResources(Resource::RESOURCE_PLUGIN).size(); i++) {
		Plugin *plugin = (Plugin*)resourcePool->getResources(Resource::RESOURCE_PLUGIN)[i];
		pluginBrowser->addPlugin(plugin);
	}

	mainWindow->pluginPane->addEventListener(this, Event::CHANGE_EVENT);

	pluginBrowser->newPluginButton->addEventListener(this, UIEvent::CLICK_EVENT);
	pluginBrowser->removeButton->addEventListener(this, UIEvent::CLICK_EVENT);

	mainWindow->pluginPane->addEventListener(this, Event::CHANGE_EVENT);

	PolycodeEditor::openFile(filePath);
	return true;
}

void PolycodePluginEditor::saveFile() {
	Object saveFile;
	saveFile.root.name = "plugins";
	saveFile.root.addChild("version", 1);
	for (int p = 0; p < resourcePool->getResources(Resource::RESOURCE_PLUGIN).size(); p++) {
		ObjectEntry* pluginEntry = saveFile.root.addChild("plugin");
		if (pluginEntry) {
			savePluginToObjectEntry(pluginBrowser->selectedData->plugin, pluginEntry);
		}
	}
	saveFile.saveToXML(filePath.fullPath);
	setHasChanges(false);
}

void PolycodePluginEditor::savePluginToObjectEntry(Plugin* plugin, ObjectEntry* entry) {
	entry->addChild("name", plugin->getResourceName());
	entry->addChild("fileext", plugin->ext);
	entry->addChild("type", (int)plugin->pluginType);
	
	ObjectEntry* sheetEntry = entry->addChild("sheet");
	//sheetEntry->addChild("name", plugin->getSheetName());
	ObjectEntry* propsEntry = sheetEntry->addChild("props");
	std::vector<PropProp*> props = mainWindow->pluginPane->getProps();
	for (int i = 0; i < props.size(); i++) {
		ObjectEntry* propEntry = propsEntry->addChild("prop");
		propEntry->addChild("type", ((PropEditProp*)props[i])->getPropType());
		propEntry->addChild("name", props[i]->getPropName());
	}
}

void PolycodePluginEditor::handleEvent(Event *event) {

	if (event->getDispatcher() == mainWindow->pluginPane && event->getEventType() == "" && event->getEventCode() == Event::CHANGE_EVENT) {
		if (selectedPluginNode && mainWindow->pluginPane->currentPlugin) {
			selectedPluginNode->setLabelText(mainWindow->pluginPane->currentPlugin->getResourceName());
		}
		setHasChanges(true);
	}

	if (event->getDispatcher() == pluginBrowser->newPluginButton && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {
		Plugin *newPlugin = new Plugin("New Plugin");
		pluginBrowser->addPlugin(newPlugin)->setSelected();
		resourcePool->addResource(newPlugin);
		setHasChanges(true);
	}

	if (event->getDispatcher() == pluginBrowser->removeButton && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {

		mainWindow->pluginPane->enabled = false;

		if (pluginBrowser->selectedData->plugin) {
			for (int i = 0; i < resourcePool->getResources(Resource::RESOURCE_PLUGIN).size(); i++) {
				if ((Plugin*)resourcePool->getResources(Resource::RESOURCE_PLUGIN)[i] == pluginBrowser->selectedData->plugin) {
					resourcePool->removeResource(resourcePool->getResource(Resource::RESOURCE_PLUGIN, pluginBrowser->selectedData->plugin->getResourceName()));
					pluginBrowser->removeSelected();
					break;
				}
			}
		}
	}

	if (event->getDispatcher() == pluginBrowser) {
		if (event->getEventType() == "" && event->getEventCode() == Event::CHANGE_EVENT) {
			if (pluginBrowser->selectedData) {
				mainWindow->pluginPane->enabled = false;

				if (pluginBrowser->selectedData->plugin) {
					selectedPluginNode = pluginBrowser->selectedNode;
					mainWindow->pluginPane->setPlugin(pluginBrowser->selectedData->plugin);
				}

			}
		}
	}
}

void PolycodePluginEditor::Resize(int x, int y) {
	mainSizer->Resize(((Number)x), ((Number)y));
	PolycodeEditor::Resize(((Number)x), ((Number)y));
}
