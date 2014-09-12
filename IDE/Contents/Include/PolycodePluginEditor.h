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

#pragma once
#include "PolycodeEditor.h"
#include <Polycode.h>
#include "PolycodeUI.h"
#include "PolycodeProps.h"
#include "PolyPlugin.h"

namespace Polycode {
	
	class PluginBrowserData {
	public:
		PluginBrowserData() {
			plugin = NULL;
		}
		Plugin *plugin;
	};

	class PluginBrowser : public UIElement {
	public:
		PluginBrowser();
		~PluginBrowser();

		void Resize(Number width, Number height);

		UITree *addPlugin(Plugin* plugin);

		void removeSelected();

		void handleEvent(Event *event);

		PluginBrowserData *selectedData;

		UIImageButton *newPluginButton;

		UIImageButton *removeButton;

		UITree *selectedNode;

	protected:

		UIRect *headerBg;
		UITree *pluginNode;

		UITreeContainer *treeContainer;
	};

	class PluginEditorPane : public UIElement {
	public:
		PluginEditorPane(ResourcePool* resourcePool);
		~PluginEditorPane();

		void setPlugin(Plugin *plugin);
		void handleEvent(Event *event);

		PropProp* getPropByName();
		void setProp(const String& name, PropProp* prop);
		std::vector<PropProp*> getProps();
		int getNumProps();

		void Resize(Number width, Number height);

		Plugin *currentPlugin;
	protected:
		ResourcePool *resourcePool;
		bool changingPlugin;
		UIRect *headerBg;
		PropList *propList;
		PropSheet *propsSheet;

		StringProp* nameProp;

		StringProp* newPropName;
		ButtonProp* addPropButton;

		int padding;

		//std::vector<PropEditProp*> editProps;
		//std::vector<PropProp*> props;
	};

	class PluginMainWindow : public UIElement {
	public:
		PluginMainWindow(ResourcePool *resourcePool);
		~PluginMainWindow();

		void Resize(Number width, Number height);

		PluginEditorPane *pluginPane;

		UIColorPicker *colorPicker;
	};

	class PolycodePluginEditor : public PolycodeEditor {
	public:
		PolycodePluginEditor();
		~PolycodePluginEditor();

		bool openFile(OSFileEntry filePath);
		void Resize(int x, int y);

		void saveFile();
		void savePluginToObjectEntry(Plugin *plugin, ObjectEntry *entry);

		void handleEvent(Event *event);

	protected:
		ResourcePool *resourcePool;
		OSFileEntry filePath;

		PluginBrowser *pluginBrowser;
		UIHSizer *mainSizer;

		PluginMainWindow *mainWindow;
		//std::vector<Plugin*> plugins;
		
		UITree *selectedPluginNode;
	};

	class PolycodePluginEditorFactory : public PolycodeEditorFactory {
	public:
		PolycodePluginEditorFactory() : PolycodeEditorFactory() { extensions.push_back("plugin"); }
		PolycodeEditor *createEditor() { return new PolycodePluginEditor(); }
	};
}