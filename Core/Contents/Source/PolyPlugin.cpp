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

#include "PolyPlugin.h"
#include "PolyObject.h"
#include "PolyCoreServices.h"
#include "PolyPluginManager.h"
#include "PolyResourceManager.h"
#include "PolyLogger.h"

using namespace Polycode;

Plugin::Plugin(const String& name) : Resource(Resource::RESOURCE_PLUGIN) {
	if (!Services()->getResourceManager()->getGlobalPool()->getResource(Resource::RESOURCE_PLUGIN, name)) {
		setResourceName("");
		ext = "";
		pluginType = 0;
		type = Resource::RESOURCE_PLUGIN;
		//sheetEntry = NULL;
	}
}

Plugin::Plugin(ObjectEntry *entry) : Resource(Resource::RESOURCE_PLUGIN) {
	loadPluginFromEntry(entry);
}

Plugin::~Plugin() {}

Plugin* Plugin::loadPluginFromEntry(ObjectEntry* entry){	
	if ((*entry)["name"])
		this->setResourceName((*entry)["name"]->stringVal);
	
	if ((*entry)["fileext"])
		this->ext = (*entry)["fileext"]->stringVal;
	
	//if ((*entry)["sheet"] && (*(*entry)["sheet"])["props"])
	//	this->sheetEntry = (*entry)["sheet"];

	if ((*entry)["type"])
		this->pluginType = (*entry)["type"]->intVal;
	
	if ((*entry)["sheet"]){
		ObjectEntry* sheetEntry = (*entry)["sheet"];
		if ((*sheetEntry)["props"]){
			ObjectEntry* propsEntry = (*sheetEntry)["props"];
			if (propsEntry) {
				for (int k = 0; k < propsEntry->children.size(); k++) {
					ObjectEntry* propEntry = propsEntry->children[k];
					if (!propEntry || propEntry->name != "prop")
						continue;

					Prop *prop = new Prop(propEntry);
					this->setProp(prop);
				}
			}
		}
	}
	Logger::log("Adding plugin: [%s]\n", this->getResourceName().c_str());
	return this;
}

unsigned int Plugin::getNumProps() const {
	return props.size();
}

void Plugin::addProp(Prop *prop) {
	props.push_back(prop);
}

void Plugin::setProp(Prop *prop) {
	for (int i = 0; i < props.size(); i++) {
		if (props[i]->name == prop->name) {
			props[i] = prop;
			return;
		}
	}

	props.push_back(prop);
}

void Plugin::removeProp(Prop *propToRemove) {
	for (int i = 0; i<props.size(); i++) {
		if (props[i] == propToRemove) {
			delete props[i];
			props.erase(props.begin() + i);
			return;
		}
	}
}

void Plugin::removeProp(const String& propName) {
	for (int i = 0; i < props.size(); i++) {
		if (props[i]->name == propName) {
			delete props[i];
			props.erase(props.begin() + i);
			return;
		}
	}
}

std::vector<Prop*> Plugin::getProps() const {
	return props;
}

Prop::Prop(const String& name, const int type){
	this->type = type;
	this->name = name;
}

Prop::Prop(ObjectEntry *entry) {
	loadPropFromEntry(entry);
}

Prop::~Prop(){}

Prop* Prop::loadPropFromEntry(ObjectEntry* entry){
	if (!entry->readInt("type", &this->type))
		return NULL;

	if (!(*entry)["name"])
		return NULL;
	this->name = (*entry)["name"]->stringVal;

	if (type == Prop::PROP_COMBO){
		for (int i = 0; i < entry->children.size(); i++) {
			if (entry->children[i]->name == "prop") {
				Prop* newProp = new Prop((*entry->children[i])["name"]->stringVal, Prop::PROP_COMBO);
				newProp->value = (*entry->children[i])["value"]->intVal;
				children.push_back(newProp);
			}
		}
	}
	return this;
}